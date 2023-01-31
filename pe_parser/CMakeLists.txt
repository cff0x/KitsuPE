set(PROJECT_NAME "pe_parser")
set(PROJECT_VERSION "0.1")

project(${PROJECT_NAME} LANGUAGES CXX)
set(CXX_STANDARD 17)

include_directories("../foxywinapi")

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} kernel32.lib ucrt)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
