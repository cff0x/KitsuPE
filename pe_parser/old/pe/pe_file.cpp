#include "pe_file.hpp"

#include <utility>
#include <fstream>
#include <iostream>

pe_file::pe_file() :
    m_dos_header{0},
    m_nt_header{0},
    m_section_data{},
    m_section_headers{},
    m_input_data{} {

}

pe_file::~pe_file() = default;

void pe_file::parse_from_file(const std::string& input_file) {
    std::ifstream input_stream{input_file, std::ios::binary};

    // get size of the input file
    input_stream.seekg(0, std::ios::end);
    std::streamsize input_size = input_stream.tellg();
    input_stream.seekg(0, std::ios::beg);

    // read file into buffer
    std::vector<uint8_t> buffer(input_size);
    if(input_stream.read(reinterpret_cast<char*>(buffer.data()), input_size)) {
        parse_from_buffer(buffer);
    }

    input_stream.close();
}

void pe_file::parse_from_buffer(const std::vector<uint8_t>& buf) {
    uint32_t offset{0};

    // read dos header from buffer
    memcpy(&m_dos_header, buf.data(), sizeof(m_dos_header));
    offset += sizeof(m_dos_header);

    // read dos stub from buffer
    m_dos_stub_data = std::vector<uint8_t>(m_dos_header.new_exe_header_address - sizeof(m_dos_header));
    memcpy(m_dos_stub_data.data(), buf.data() + offset, m_dos_stub_data.size());
    offset += m_dos_stub_data.size();

    // read nt header from buffer
    memcpy(&m_nt_header, buf.data() + offset, sizeof(m_nt_header));
    offset += sizeof(m_nt_header);

    // read each section header from buffer
    for(int i = 0; i < m_nt_header.file_header.section_count; ++i) {
        pe_section_header tmp_header{0};
        memcpy(&tmp_header, buf.data() + offset, sizeof(tmp_header));
        offset += sizeof(tmp_header);

        m_section_headers.push_back(tmp_header);
    }

    // skip the padding between headers and section data
    offset += get_space_after_headers();

    // read data for each section
    for(auto &el: m_section_headers) {
        std::vector<uint8_t> tmp_data(el.raw_data_size);
        memcpy(tmp_data.data(), buf.data() + offset, el.raw_data_size);
        offset += el.raw_data_size;

        m_section_data.insert(std::pair<std::string, std::vector<uint8_t>>((char*)el.name, tmp_data));
    }
}

bool pe_file::write_to_file(const std::string& output_file) {
    // open output file
    std::ofstream file_stream{output_file, std::ios::binary};
    if(!file_stream.is_open()) {
        return false;
    }

    // build pe data and write to output file
    std::vector<uint8_t> buf{write_to_buffer()};
    if(!file_stream.write(reinterpret_cast<char*>(buf.data()), buf.size())) {
        return false;
    }

    file_stream.close();
    return true;
}

std::vector<uint8_t> pe_file::write_to_buffer() {
    // buffer to hold the pe file data
    std::vector<uint8_t> buf(get_total_file_size());
    uint32_t offset{0};

    // write dos header
    memcpy(buf.data(), reinterpret_cast<char*>(&m_dos_header), sizeof(m_dos_header));
    offset += sizeof(m_dos_header);

    // write dos stub
    memcpy(buf.data() + offset, reinterpret_cast<char*>(m_dos_stub_data.data()), m_dos_stub_data.size());
    offset += m_dos_stub_data.size();

    // write nt header
    memcpy(buf.data() + offset, reinterpret_cast<char*>(&m_nt_header), sizeof(m_nt_header));
    offset += sizeof(m_nt_header);

    // write section headers
    for(auto &el: m_section_headers) {
        std::cout << "writing section header: " << el.name << std::endl;
        memcpy(buf.data() + offset, reinterpret_cast<char*>(&el), sizeof(el));
        offset += sizeof(el);
    }

    // append padding after header data
    offset += get_space_after_headers();

    // write data for each section
    for(auto &el: m_section_headers) {
        std::cout << "writing section data: " << el.name << std::endl;
        memcpy(buf.data() + offset, reinterpret_cast<char*>(m_section_data[(char*)el.name].data()), el.raw_data_size);
        offset += el.raw_data_size;
    }

    return buf;
}

uint32_t pe_file::get_first_section_pointer() {
    // return raw data address of first section
    if(!m_section_headers.empty()) {
        return m_section_headers[0].raw_data_pointer;
    }

    return 0;
}

uint32_t pe_file::get_space_after_headers() {
    // calculate padding which will be added after the headers
    return get_first_section_pointer() - get_raw_header_size();
}

uint32_t pe_file::get_raw_header_size() {
    // calculate raw data size of the headers
    return sizeof(m_dos_header) + m_dos_stub_data.size() + sizeof(m_nt_header) + (sizeof(pe_section_header) * m_section_headers.size());
}

uint32_t pe_file::get_total_file_size() {
    // calculate size of the whole pe file including section data
    uint32_t result = get_raw_header_size() + get_space_after_headers();
    for(auto &el: m_section_data) {
        result += el.second.size();
    }

    return result;
}

void pe_file::recalculate_section_sizes() {
    // address pointing to the raw section data (first section starts right after headers + header padding)
    uint32_t current_data_address = get_raw_header_size() + get_space_after_headers();

    // image size calculation starts at the code base specified in the nt header
    m_nt_header.optional_header.image_size = m_nt_header.optional_header.code_base;

    // calculate sizes and addresses for each section
    for(auto &el: m_section_headers) {
        auto& section_data = m_section_data[(char*)el.name];

        std::cout << "=== SECTION: " << el.name << " ===" << std::endl;
        std::cout << "section_data.size(): " << section_data.size() << ", old el.raw_data_size: " << el.raw_data_size << ", new el.raw_data_size: ";

        // calculate aligned size of the raw section data
        el.raw_data_size = round_to_nearest_multiple(m_nt_header.optional_header.file_alignment, section_data.size());
        std::cout << el.raw_data_size << std::endl;

        // virtual section address based on the currently calculated image size
        el.virtual_address = m_nt_header.optional_header.image_size;

        // raw file address pointing to the section data
        el.raw_data_pointer = current_data_address;
        current_data_address += el.raw_data_size;

        // add aligned virtual section size to the total image size
        m_nt_header.optional_header.image_size += round_to_nearest_multiple(m_nt_header.optional_header.section_alignment, section_data.size());
    }

    m_nt_header.file_header.section_count = m_section_headers.size();
}

bool pe_file::add_section(const std::string &name, std::vector<uint8_t> data, uint32_t characteristics) {
    if(m_section_data.count(name)) {
        return false;
    }

    size_t real_data_size = data.size();
    data.resize(round_to_nearest_multiple(m_nt_header.optional_header.file_alignment, data.size()), 0x00);

    pe_section_header new_section{0};
    new_section.misc.virtual_size = real_data_size;
    new_section.misc.physical_address = real_data_size;
    new_section.raw_data_size = data.size();

    memcpy(new_section.name, name.c_str(), sizeof(new_section.name));
    new_section.characteristics = characteristics;

    m_section_headers.push_back(new_section);
    m_section_data.insert(std::pair<std::string, std::vector<uint8_t>>(name, data));

    recalculate_section_sizes();
    return true;
}

bool pe_file::delete_section(const std::string &name) {
    if(!m_section_data.count(name)) {
        return false;
    }

    // remove section header
    for(int i = 0; i < m_section_headers.size(); ++i) {
        if(name == (char*)m_section_headers[i].name) {
            m_section_headers.erase(m_section_headers.begin() + i);
            break;
        }
    }

    // remove section data
    m_section_data.erase(name);

    recalculate_section_sizes();

    return true;
}

bool pe_file::rename_section(const std::string &orig_name, const std::string &new_name) {
    if(!m_section_data.count(orig_name) || m_section_data.count(new_name)) {
        return false;
    }

    // remove section header
    for(auto &el: m_section_headers) {
        if(orig_name == (char*)el.name) {
            memcpy(el.name, new_name.c_str(), sizeof(el.name));
            break;
        }
    }

    // replace section data element
    m_section_data.insert(std::pair<std::string, std::vector<uint8_t>>(new_name, m_section_data[orig_name]));
    m_section_data.erase(orig_name);

    recalculate_section_sizes();

    return true;
}

bool pe_file::set_section_data(const std::string &name, std::vector<uint8_t> data) {
    if(!m_section_data.count(name)) {
        return false;
    }

    m_section_data.erase(name);
    m_section_data.insert(std::pair<std::string, std::vector<uint8_t>>(name, data));

    recalculate_section_sizes();

    return true;
}

bool pe_file::set_section_characteristics(const std::string &name, uint32_t characteristics) {
    if(!m_section_data.count(name)) {
        return false;
    }

    for(auto &el: m_section_headers) {
        if(name == (char*)el.name) {
            el.characteristics = characteristics;
            break;
        }
    }

    return true;
}

std::vector<uint8_t> pe_file::get_section_data(const std::string &name) {
    if(!m_section_data.count(name)) {
        return {};
    }

    return m_section_data[name];
}

uint32_t pe_file::get_section_characteristics(const std::string &name) {
    for(auto &el: m_section_headers) {
        if(name == (char*)el.name) {
            return el.characteristics;
        }
    }

    return 0x00;
}
