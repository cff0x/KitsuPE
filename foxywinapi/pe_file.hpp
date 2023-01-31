
#pragma once

#include <cstdint>

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16

typedef enum pe_image_machine : uint16_t {
    PE_IMAGE_MACHINE_UNKNOWN = 0,
    PE_I386 = 0x014c,  // Intel 386 or later processors and compatible processors
    PE_R3000 = 0x0162,  // MIPS little-endian, 0x160 big-endian
    PE_R4000 = 0x0166,  // MIPS little-endian
    PE_R10000 = 0x0168,  // MIPS little-endian
    PE_WCEMIPSV2 = 0x0169,  // MIPS little-endian WCE v2
    PE_ALPHA = 0x0184,  // Alpha_AXP
    PE_SH3 = 0x01a2,  // Hitachi SH3
    PE_SH3DSP = 0x01a3,  // Hitachi SH3 DSP
    PE_SH3E = 0x01a4,  // Hitachi SH3E little-endian
    PE_SH4 = 0x01a6,  // Hitachi SH4
    PE_SH5 = 0x01a8,  // Hitachi SH5
    PE_ARM = 0x01c0,  // ARM little-endian
    PE_THUMB = 0x01c2,  // Thumb
    PE_ARMNT = 0x01c4,  // Arm Thumb-2 little-endian
    PE_AM33 = 0x01d3,  // Matsushita AM33
    PE_POWERPC = 0x01f0,  // Power PC little endian
    PE_POWERPCFP = 0x01f1,  // Power PC with floating point support
    PE_IA64 = 0x0200,  // Intel Itanium processor family
    PE_MIPS16 = 0x0266,  // MIPS16
    PE_ALPHA64 = 0x0284,  // ALPHA64
    PE_MIPSFPU = 0x0366,  // MIPS with FPU
    PE_MIPSFPU16 = 0x0466,  // MIPS16 with FPU
    PE_TRICORE = 0x0520,  // Infineon
    PE_CEF = 0x0CEF,
    PE_EBC = 0x0EBC,  // EFI Byte Code
    PE_RISCV32 = 0x5032,  // RISC-V 32-bit address space
    PE_RISCV64 = 0x5064,  // RISC-V 64-bit address space
    PE_RISCV128 = 0x5128,  // RISC-V 128-bit address space
    PE_AMD64 = 0x8664,  // x64
    PE_M32R = 0x9041,  // Mitsubishi M32R little-endian
    PE_ARM64 = 0xAA64,  // ARM64 little-endian
    PE_CEE = 0xC0EE
} pe_image_machine_e;

typedef enum pe_file_characteristics {
    PE_IMAGE_FILE_RELOCS_STRIPPED = 0x0001,
    PE_IMAGE_FILE_EXECUTABLE_IMAGE = 0x0002,
    PE_IMAGE_FILE_LINE_NUMS_STRIPPED = 0x0004,
    PE_IMAGE_FILE_LOCAL_SYMS_STRIPPED = 0x0008,
    PE_IMAGE_FILE_AGGRESIVE_WS_TRIM = 0x0010,
    PE_IMAGE_FILE_LARGE_ADDRESS_AWARE = 0x0020,
    PE_IMAGE_FILE_BYTES_REVERSED_LO = 0x0080,
    PE_IMAGE_FILE_32BIT_MACHINE = 0x0100,
    PE_IMAGE_FILE_DEBUG_STRIPPED = 0x0200,
    PE_IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP = 0x0400,
    PE_IMAGE_FILE_NET_RUN_FROM_SWAP = 0x0800,
    PE_IMAGE_FILE_SYSTEM = 0x1000,
    PE_IMAGE_FILE_DLL = 0x2000,
    PE_IMAGE_FILE_UP_SYSTEM_ONLY = 0x4000,
    PE_IMAGE_FILE_BYTES_REVERSED_HI = 0x8000
} pe_file_characteristics_e;

typedef enum pe_optional_magic : uint16_t {
    PE_PE32 = 0x10b,
    PE_PE64 = 0x20b,
    PE_ROM = 0x107
} pe_optional_magic_e;

typedef enum pe_image_subsystem : uint16_t {
    PE_IMAGE_SUBSYSTEM_UNKNOWN = 0,  // Unknown subsystem
    PE_NATIVE = 1,  // Image doesn't require a subsystem
    PE_WINDOWS_GUI = 2,  // Image runs in the Windows GUI subsystem
    PE_WINDOWS_CUI = 3,  // Image runs in the Windows character subsystem
    PE_OS2_CUI = 5,  // image runs in the OS/2 character subsystem
    PE_POSIX_CUI = 7,  // image runs in the Posix character subsystem
    PE_NATIVE_WINDOWS = 8,  // image is a native Win9x driver
    PE_WINDOWS_CE_GUI = 9,  // Image runs in the Windows CE subsystem
    PE_EFI_APPLICATION = 10,
    PE_EFI_BOOT_SERVICE_DRIVER = 11,
    PE_EFI_RUNTIME_DRIVER = 12,
    PE_EFI_ROM = 13,
    PE_XBOX = 14,
    PE_WINDOWS_BOOT_APPLICATION = 16
} pe_image_subsystem_e;

typedef enum pe_dll_characteristics : uint16_t {
    PE_IMAGE_LIBRARY_PROCESS_INIT = 0x0001, // reserved
    PE_IMAGE_LIBRARY_PROCESS_TERM = 0x0002, // reserved
    PE_IMAGE_LIBRARY_THREAD_INIT = 0x0004, // reserved
    PE_IMAGE_LIBRARY_THREAD_TERM = 0x0008, // reserved
    PE_IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA = 0x0020, // image can handle a high entropy 64-bit virtual address space
    PE_IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE = 0x0040, // dll can be relocated at load time
    PE_IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY = 0x0080, // code integrity checks are enforced
    PE_IMAGE_DLLCHARACTERISTICS_NX_COMPAT = 0x0100, // image is nx compatible
    PE_IMAGE_DLLCHARACTERISTICS_NO_ISOLATION = 0x0200, // isolation aware, but do not isolate the image
    PE_IMAGE_DLLCHARACTERISTICS_NO_SEH = 0x0400, // does not use structured exception (se) handling - no se handler may be called in this image
    PE_IMAGE_DLLCHARACTERISTICS_NO_BIND = 0x0800, // do not bind the image
    PE_IMAGE_DLLCHARACTERISTICS_APPCONTAINER = 0x1000, // image must execute in an app container
    PE_IMAGE_DLLCHARACTERISTICS_WDM_DRIVER = 0x2000, // image is a wdm driver
    PE_IMAGE_DLLCHARACTERISTICS_GUARD_CF = 0x4000, // image supports control flow guard
    PE_IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE = 0x8000 // image is terminal server aware
} pe_dll_characteristics_e;

typedef enum pe_section_characteristics : uint32_t {
    PE_IMAGE_SCN_TYPE_DSECT = 0x00000001, // reserved
    PE_IMAGE_SCN_TYPE_NOLOAD = 0x00000002, // reserved
    PE_IMAGE_SCN_TYPE_GROUP = 0x00000004, // reserved
    PE_IMAGE_SCN_TYPE_NO_PAD = 0x00000008, // OBSOLETE: replaced by IMAGE_SCN_ALIGN_1BYTES (do not pad section to the next boundary)
    PE_IMAGE_SCN_TYPE_COPY = 0x00000010, // reserved
    PE_IMAGE_SCN_CNT_CODE = 0x00000020, // section contains executable code
    PE_IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040, // section contains initialized data
    PE_IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080, // section contains uninitialized data
    PE_IMAGE_SCN_LNK_OTHER = 0x00000100, // reserved
    PE_IMAGE_SCN_LNK_INFO = 0x00000200, // section contains comments or other information (only valid for object files)
    PE_IMAGE_SCN_TYPE_OVER = 0x00000400, // reserved
    PE_IMAGE_SCN_LNK_REMOVE = 0x00000800, // section will not become part of the image (only valid for object files)
    PE_IMAGE_SCN_LNK_COMDAT = 0x00001000, // section contains COMDAT data (only valid for object files)
    //0x00002000
    PE_IMAGE_SCN_NO_DEFER_SPEC_EXC = 0x00004000, // reset speculative exceptions handling bits in the TLB entries for this section
    PE_IMAGE_SCN_GPREL = 0x00008000, // section contains data referenced through the global pointer
    PE_IMAGE_SCN_MEM_SYSHEAP = 0x00010000, // OBSOLETE
    PE_IMAGE_SCN_MEM_PURGEABLE = 0x00020000, // reserved
    PE_IMAGE_SCN_MEM_LOCKED = 0x00040000, // reserved
    PE_IMAGE_SCN_MEM_PRELOAD = 0x00080000, // reserved
    PE_IMAGE_SCN_ALIGN_1BYTES = 0x00100000, // align data on 1-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_2BYTES = 0x00200000, // align data on 2-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_4BYTES = 0x00300000, // align data on 4-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_8BYTES = 0x00400000, // align data on 8-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_16BYTES = 0x00500000, // align data on 16-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_32BYTES = 0x00600000, // align data on 32-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_64BYTES = 0x00700000, // align data on 64-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_128BYTES = 0x00800000, // align data on 128-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_256BYTES = 0x00900000, // align data on 256-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_512BYTES = 0x00A00000, // align data on 512-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_1024BYTES = 0x00B00000, // align data on 1024-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_2048BYTES = 0x00C00000, // align data on 2048-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_4096BYTES = 0x00D00000, // align data on 4096-byte boundary (only valid for object files)
    PE_IMAGE_SCN_ALIGN_8192BYTES = 0x00E00000, // align data on 8192-byte boundary (only valid for object files)
    PE_IMAGE_SCN_LNK_NRELOC_OVFL = 0x01000000, // section contains extended relocations
    PE_IMAGE_SCN_MEM_DISCARDABLE = 0x02000000, // section can be discarded as needed
    PE_IMAGE_SCN_MEM_NOT_CACHED = 0x04000000, // section cannot be cached
    PE_IMAGE_SCN_MEM_NOT_PAGED = 0x08000000, // section cannot be paged
    PE_IMAGE_SCN_MEM_SHARED = 0x10000000, // section cannot be shared in memory
    PE_IMAGE_SCN_MEM_EXECUTE = 0x20000000, // section can be executed as code
    PE_IMAGE_SCN_MEM_READ = 0x40000000, // section can be read
    PE_IMAGE_SCN_MEM_WRITE = 0x80000000, // section can be written to

} pe_section_characteristics_e;

typedef enum pe_base_relocation_type : uint16_t {
    PE_IMAGE_REL_BASED_ABSOLUTE = 0,
    PE_IMAGE_REL_BASED_HIGH,
    PE_IMAGE_REL_BASED_LOW,
    PE_IMAGE_REL_BASED_HIGHLOW,
    PE_IMAGE_REL_BASED_HIGHADJ,
    PE_IMAGE_REL_BASED_MACHINE_SPECIFIC_5,
    PE_IMAGE_REL_BASED_RESERVED,
    PE_IMAGE_REL_BASED_MACHINE_SPECIFIC_7,
    PE_IMAGE_REL_BASED_MACHINE_SPECIFIC_8,
    PE_IMAGE_REL_BASED_MACHINE_SPECIFIC_9,
    PE_IMAGE_REL_BASED_DIR64
} pe_base_relocation_type_e;

typedef enum pe_image_debug_type : uint32_t {
    PE_COFF = 1,
    PE_CODEVIEW = 2,
    PE_FPO = 3,
    PE_MISC = 4,
    PE_EXCEPTION,
    PE_FIXUP,
    PE_OMAP_TO_SRC,
    PE_OMAP_FROM_SRC,
    PE_BORLAND,
    PE_RESERVED10,
    PE_CLSID,
    PE_VC_FEATURE,
    PE_POGO,
    PE_ILTCG,
    PE_MPX,
    PE_REPRO
} pe_image_debug_type_e;

typedef enum pe_image_directory_entry {
    PE_IMAGE_DIRECTORY_ENTRY_EXPORT = 0,
    PE_IMAGE_DIRECTORY_ENTRY_IMPORT = 1,
    PE_IMAGE_DIRECTORY_ENTRY_RESOURCE = 2,
    PE_IMAGE_DIRECTORY_ENTRY_EXCEPTION = 3,
    PE_IMAGE_DIRECTORY_ENTRY_SECURITY = 4,
    PE_IMAGE_DIRECTORY_ENTRY_BASERELOC = 5,
    PE_IMAGE_DIRECTORY_ENTRY_DEBUG = 6,
    PE_IMAGE_DIRECTORY_ENTRY_ARCHITECTURE = 7,
    PE_IMAGE_DIRECTORY_ENTRY_GLOBALPTR = 8,
    PE_IMAGE_DIRECTORY_ENTRY_TLS = 9,
    PE_IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG = 10,
    PE_IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT = 11,
    PE_IMAGE_DIRECTORY_ENTRY_IAT = 12,
    PE_IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT = 13,
    PE_IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR = 14
} pe_image_directory_entry_e;

typedef struct pe_dos_header {
    uint16_t magic;
    uint16_t bytes_on_last_page;
    uint16_t page_count;
    uint16_t relocation_count;
    uint16_t header_paragraphs;
    uint16_t min_extra_paragraphs;
    uint16_t max_extra_paragraphs;
    uint16_t init_relative_ss_value;
    uint16_t init_sp_value;
    uint16_t checksum;
    uint16_t init_ip_value;
    uint16_t relocation_table_address;
    uint16_t overlay_number;
    uint16_t reserved_1[4];
    uint16_t oem_id;
    uint16_t oem_info;
    uint16_t reserved_2[10];
    int32_t new_exe_header_address;
} pe_dos_header_t, *pe_dos_header_p;


typedef struct pe_image_file_header {
    pe_image_machine machine;
    uint16_t section_count;
    uint32_t timestamp;
    uint32_t symbol_table_pointer;
    uint32_t symbol_count;
    uint16_t optional_header_size;
    uint16_t characteristics;
} pe_image_file_header_t, *pe_image_file_header_p;


typedef struct pe_image_data_directory {
    uint32_t virtual_address;
    uint32_t size;
} pe_image_data_directory_t, *pe_image_data_directory_p;

typedef struct pe_image_optional_header_64 {
    pe_optional_magic magic;
    uint8_t major_linker_version;
    uint8_t minor_linker_version;
    uint32_t code_size;
    uint32_t initialized_data_size;
    uint32_t uninitialized_data_size;
    uint32_t entry_point_address;
    uint32_t code_base;
    uint64_t image_base;
    uint32_t section_alignment;
    uint32_t file_alignment;
    uint16_t major_os_version;
    uint16_t minor_os_version;
    uint16_t major_image_version;
    uint16_t minor_image_version;
    uint16_t major_subsystem_version;
    uint16_t minor_subsystem_version;
    uint32_t win32_version_value;
    uint32_t image_size;
    uint32_t headers_size;
    uint32_t checksum;
    pe_image_subsystem subsystem;
    uint16_t dll_characteristics; // pe_dll_characteristics
    uint64_t stack_reserve_size;
    uint64_t stack_commit_size;
    uint64_t heap_reserve_size;
    uint64_t heap_commit_size;
    uint32_t loader_flags;
    uint32_t data_directory_count;
    pe_image_data_directory export_directory;
    pe_image_data_directory import_directory;
    pe_image_data_directory resource_directory;
    pe_image_data_directory exception_directory;
    pe_image_data_directory security_directory;
    pe_image_data_directory base_relocation_table;
    pe_image_data_directory debug_directory;
    pe_image_data_directory architecture_directory;
    pe_image_data_directory global_pointer_directory;
    pe_image_data_directory tls_directory;
    pe_image_data_directory load_configuration_directory;
    pe_image_data_directory bound_import_directory;
    pe_image_data_directory import_address_table;
    pe_image_data_directory delay_load_import_directory;
    pe_image_data_directory com_runtime_directory;
    pe_image_data_directory reserved;
} pe_image_optional_header_64_t, *pe_image_optional_header_64_p;

typedef struct pe_nt_headers_64 {
    uint32_t signature;
    pe_image_file_header file_header;
    pe_image_optional_header_64 optional_header;

} pe_nt_headers_64_t, *pe_nt_headers_64_p;

typedef struct pe_section_header {
    uint8_t name[8];
    union {
        uint32_t physical_address;
        uint32_t virtual_size;
    } misc;
    uint32_t virtual_address;
    uint32_t raw_data_size;
    uint32_t raw_data_pointer;
    uint32_t relocations_pointer;
    uint32_t line_numbers_pointer;
    uint16_t relocations_count;
    uint16_t line_numbers_count;
    uint32_t characteristics; // pe_section_characteristics
} pe_section_header_t, *pe_section_header_p;


typedef struct pe_base_relocation_block {
    uint16_t offset;
    pe_base_relocation_type type;
} pe_base_relocation_block_t;

typedef struct pe_base_relocation {
    uint32_t virtual_address;
    uint32_t block_size;
    pe_base_relocation_type *blocks;
} pe_base_relocation_t;

typedef struct pe_image_debug_directory {
    uint32_t characteristics;
    uint32_t timestamp;
    uint16_t major_version;
    uint16_t minor_version;
    pe_image_debug_type type;
    uint32_t data_size;
    uint32_t raw_data_address;
    uint32_t raw_data_pointer;
} pe_image_debug_directory_t;

typedef struct pe_file_data {
    uint64_t* pe_address;
    size_t pe_size;

    pe_dos_header* dos_header;
    pe_nt_headers_64* nt_header;
    pe_image_data_directory* ei_data_dir;
    pe_image_data_directory* tls_data_dir;
    pe_image_data_directory* eh_data_dir;

    pe_section_header* section_header;
} pe_file_data_t;