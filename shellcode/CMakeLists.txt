set(PROJECT_NAME "shellcode")
set(PROJECT_VERSION "0.1")

project(${PROJECT_NAME} LANGUAGES CXX)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} foxywinapi)

set(CMAKE_VERBOSE_MAKEFILE on)

target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/sdl-" # disable SDL checks
        "/GS-" # disable security checks
        "/MT" # multi-threaded runtime
        "/fp:except-" # disable floating point exceptions
)


target_link_options(${PROJECT_NAME}
        PRIVATE
        "/NODEFAULTLIB" # ignore all default libraries
        "/ENTRY:shellcode" # set custom entry point
        "/SUBSYSTEM:WINDOWS" # link for windows subsystem
        "/MACHINE:X64" # target 64bit
        "/DYNAMICBASE:NO" # disable dynamic base address (removes reloc table)
        "/MAP" # generate mapping file
        "/NXCOMPAT:NO" # disables DEP support
        "/SAFESEH:NO" # disable safe exception handlers
        "/MANIFEST:NO"
        "/merge:.rdata=base"
        "/merge:.pdata=base"
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND python "${CMAKE_CURRENT_SOURCE_DIR}/extract.py" -f "$<TARGET_FILE:${PROJECT_NAME}>" -o "${CMAKE_CURRENT_SOURCE_DIR}/x64/${PROJECT_NAME}.bin"
    COMMENT "This command extracts the shellcode binary data from the PE file"
    VERBATIM
)






