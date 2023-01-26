cmake_minimum_required (VERSION 3.8)

project ("FoxyTools")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CXX_STANDARD 17)

include_directories("pe_shared")
add_compile_options(
        #"/Oi-" # de-activate intrinsic functions
        #"/O1" # disable whole-program optimizations
        "-fno-builtin"
        "/O1"
)

# add lzma2 library (we build it here because it has no CMakeLists.txt)
set(LZMA2_DIR "externals/fast-lzma2")
add_library (lzma2 STATIC
        "${LZMA2_DIR}/dict_buffer.c" "${LZMA2_DIR}/fl2_common.c" "${LZMA2_DIR}/fl2_compress.c"
        "${LZMA2_DIR}/fl2_decompress.c" "${LZMA2_DIR}/fl2_pool.c" "${LZMA2_DIR}/fl2_threading.c"
        "${LZMA2_DIR}/lzma2_dec.c" "${LZMA2_DIR}/lzma2_enc.c" "${LZMA2_DIR}/radix_bitpack.c"
        "${LZMA2_DIR}/radix_mf.c" "${LZMA2_DIR}/radix_struct.c" "${LZMA2_DIR}/range_enc.c"
        "${LZMA2_DIR}/util.c" "${LZMA2_DIR}/xxhash.c")
target_include_directories(lzma2 PUBLIC "${LZMA2_DIR}")

add_subdirectory("foxylib")
add_subdirectory("foxywinapi")
add_subdirectory("basic_applications")
add_subdirectory("debug_tool")

add_subdirectory("pe_stub")

add_subdirectory("shellcode")
add_subdirectory("shellcode_test")