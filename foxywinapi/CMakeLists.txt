set(PROJECT_NAME "foxywinapi")
set(PROJECT_VERSION "0.1")

project(${PROJECT_NAME} LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC "foxywinapi.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC ".")
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

