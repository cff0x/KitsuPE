set(PROJECT_NAME "basic_cpp_application")
set(PROJECT_VERSION "0.1")

project(${PROJECT_NAME} LANGUAGES CXX)


add_executable(${PROJECT_NAME} "main.cpp" "pong.cpp")
target_link_libraries(${PROJECT_NAME} foxylib)
