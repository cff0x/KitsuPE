#pragma once
#include <pe_file.hpp>
#include <vector>
#include <map>
#include <string>

class pe_file {
public:
    pe_file();
    ~pe_file();

    void parse_from_file(const std::string& input_file);
    void parse_from_buffer(const std::vector<uint8_t>& buf);
    bool write_to_file(const std::string& output_file);
    std::vector<uint8_t> write_to_buffer();

    bool add_section(const std::string& name, std::vector<uint8_t> data, uint32_t characteristics = 0x00);
    bool delete_section(const std::string& name);
    bool rename_section(const std::string& orig_name, const std::string& new_name);

    bool set_section_data(const std::string& name, std::vector<uint8_t> data);
    bool set_section_characteristics(const std::string& name, uint32_t characteristics);

    std::vector<uint8_t> get_section_data(const std::string& name);
    uint32_t get_section_characteristics(const std::string& name);

    uint32_t get_first_section_pointer();
    uint32_t get_space_after_headers();
    uint32_t get_raw_header_size();
    uint32_t get_total_file_size();

    void recalculate_section_sizes();

    static inline uint32_t round_to_nearest_multiple(uint32_t multiple, uint32_t value) {
        return ((value + (multiple - 1) &(-multiple)));
    }

private:
    pe_dos_header m_dos_header;
    pe_nt_headers_64 m_nt_header;
    std::vector<pe_section_header> m_section_headers;
    std::map<std::string, std::vector<uint8_t>> m_section_data;
    std::vector<uint8_t> m_dos_stub_data;
    std::vector<uint8_t> m_input_data;
};