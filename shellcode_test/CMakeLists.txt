set(PROJECT_NAME "shellcode_test")
set(PROJECT_VERSION "0.1")

project(${PROJECT_NAME} LANGUAGES CXX)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} foxywinapi)


target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/sdl-" # disable SDL checks
        "/GS-" # disable security checks
        "/MT" # multi-threaded runtime
        "/O1" # optimize for fast code
        "/fp:except-" # disable floating point exceptions
        "/Oy" # suppress frame pointers
#        "/GT" # optimize
)


target_link_options(${PROJECT_NAME}
        PRIVATE
        "/SUBSYSTEM:CONSOLE" # link for windows subsystem
        "/MACHINE:X64" # target 64bit
        "/DYNAMICBASE:NO" # disable dynamic base address (removes reloc table)
        "/MAP" # generate mapping file
        "/NXCOMPAT:NO" # disables DEP support
        "/SAFESEH:NO" # disable safe exception handlers
        "/OPT:REF"
        "/MANIFEST:NO"
        "/DEBUG:NONE"

)






