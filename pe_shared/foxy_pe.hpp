#pragma once
#include <pe_types.hpp>

typedef struct foxy_pe_file {
    uint32_t image_base;
    uint32_t image_size;
    uint32_t entry_point_address;
    uint32_t size_of_headers;
} foxy_pe_file_t, *foxy_pe_file_p;