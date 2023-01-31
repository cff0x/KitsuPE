#include "main.hpp"
#include "pe/pe_file.hpp"
#include <lazy_importer.hpp>


int WinMain(int argc, char** argv) {
    pe_file target_pe{};
    target_pe.parse_from_file("E:/Development/FoxyTools/dist/release/bin/pe_stub.exe");
    std::cout << "raw header size: " << target_pe.get_raw_header_size() << std::endl;

    std::ifstream input_stream{"E:/basic_c_application.exe", std::ios::binary};
    input_stream.seekg(0, std::ios::end);
    std::streamsize input_size = input_stream.tellg();
    input_stream.seekg(0, std::ios::beg);

    std::vector<uint8_t> packed_pe_data(input_size);
    if(!input_stream.read(reinterpret_cast<char*>(packed_pe_data.data()), input_size)) {
        std::cout << "error while reading exe file!" << std::endl;
        return 1;
    }

    input_stream.close();

    target_pe.add_section(".packed", packed_pe_data, pe_section_characteristics::PE_IMAGE_SCN_MEM_READ | pe_section_characteristics::PE_IMAGE_SCN_CNT_INITIALIZED_DATA);
    target_pe.write_to_file("E:/basic_c_application.packed.exe");
    /*std::filesystem::path test{"E:/basic_c_application.exe"};

    pe_dos_header dos_header{0};
    pe_nt_headers_64 nt_header{0};
    std::vector<pe_section_header> section_headers{};
    std::map<std::string, uint8_t*> section_data{};

    uint64_t first_section_pointer{0};

    size_t dos_stub_size;
    char* dos_stub_buffer;

    size_t space_after_headers;
    size_t raw_header_size;
    size_t total_file_size{0};

    std::ifstream file_stream{test, std::ios::binary};
    if(!file_stream.is_open()) {
        std::cout << "failed to open file!\n";
        return 1;
    } else {
        file_stream.read(reinterpret_cast<char*>(&dos_header), sizeof(dos_header));
        dos_stub_size = dos_header.new_exe_header_address - sizeof(dos_header);
        dos_stub_buffer = reinterpret_cast<char*>(malloc(dos_stub_size));
        file_stream.read(dos_stub_buffer, dos_stub_size);
        file_stream.read(reinterpret_cast<char*>(&nt_header), sizeof(nt_header));

        for(int i = 0; i < nt_header.file_header.section_count; ++i) {
            pe_section_header tmp_header{0};
            file_stream.read(reinterpret_cast<char*>(&tmp_header), sizeof(tmp_header));
            section_headers.push_back(tmp_header);

            if(i == 0) {
                first_section_pointer = tmp_header.raw_data_pointer;
            }
        }

        raw_header_size = sizeof(dos_header) + dos_stub_size + sizeof(nt_header) + (sizeof(pe_section_header) * section_headers.size());
        space_after_headers = first_section_pointer - raw_header_size;
        file_stream.seekg(raw_header_size + space_after_headers);

        total_file_size += raw_header_size + space_after_headers;

        std::cout << "sizeof dos_header: " << sizeof(dos_header) << std::endl;
        std::cout << "dos stub size: " << dos_stub_size << std::endl;
        std::cout << "raw header size: " << raw_header_size << std::endl;
        std::cout << "first section ptr: " << first_section_pointer << std::endl;
        std::cout << "space after headers: " << space_after_headers << std::endl;

        for(auto &el: section_headers) {
            uint8_t* tmp_data = reinterpret_cast<uint8_t*>(malloc(el.raw_data_size));
            file_stream.read(reinterpret_cast<char*>(tmp_data), el.raw_data_size);
            section_data.insert(std::pair<std::string, uint8_t*>((char*)el.name, tmp_data));
            total_file_size += el.raw_data_size;

        }

        file_stream.close();
    }



    std::cout << "dos_header 1: " << std::hex << dos_header.magic << std::endl;
    for(int i = 0; i < dos_stub_size; ++i) {
        std::cout << std::hex << (uint8_t)dos_stub_buffer[i];
    }
    std::cout << std::endl;
    std::cout << "nt header 1: " << std::hex << nt_header.signature << std::endl;

    for(auto &el: section_headers) {
        std::cout << "section: " << el.name << std::endl;
    }

    pe_section_header new_section{0};

    uint8_t test_data[8192*10] = {0};

    strcpy((char*)new_section.name, ".fox");
    new_section.virtual_address = nt_header.optional_header.image_size;
    new_section.raw_data_size = roundToNearestMultiple(512, sizeof(test_data));
    new_section.raw_data_pointer = total_file_size;
    section_headers.push_back(new_section);

    nt_header.optional_header.image_size = roundToNearestMultiple(4096, new_section.raw_data_size + nt_header.optional_header.image_size);

    space_after_headers -= sizeof(new_section);


    section_data.insert(std::pair<std::string, uint8_t*>(".fox", test_data));

    nt_header.file_header.section_count += 1;

    std::ofstream outfile{"E:/out.exe", std::ios::binary};
    std::ofstream outfile_foxy{"E:/out.fox", std::ios::binary};

    outfile.write(reinterpret_cast<char*>(&dos_header), sizeof(dos_header));
    outfile.write(reinterpret_cast<char*>(dos_stub_buffer), dos_stub_size);
    outfile.write(reinterpret_cast<char*>(&nt_header), sizeof(nt_header));
    for(auto &el: section_headers) {
        std::cout << "writing section header: " << el.name << std::endl;
        outfile.write(reinterpret_cast<char*>(&el), sizeof(el));
    }

    for(int i = 0; i < space_after_headers; ++i) {
        outfile.put(0x00);
    }

    for(auto &el: section_headers) {
        std::cout << "writing section data: " << el.name << " (size: " <<  (int)el.raw_data_size << ")" << std::endl;

        outfile.write(reinterpret_cast<char*>(section_data[(char*)el.name]), el.raw_data_size);

        FOXY_PE_HEADER out_header{0};
        memcpy(out_header.section_name, el.name, sizeof(el.name));
        out_header.section_size = el.raw_data_size;
        out_header.section_data = section_data[(char*)el.name];

        outfile_foxy.write(reinterpret_cast<char*>(&out_header), sizeof(out_header));
        outfile_foxy.write(reinterpret_cast<char*>(out_header.section_data), out_header.section_size);

    }

    outfile.close();
    outfile_foxy.close();*/



    return 0;
}