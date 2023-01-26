set(PROJECT_NAME "basic_library")
project(${PROJECT_NAME} LANGUAGES C)

add_library(${PROJECT_NAME} SHARED "main.c")
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_link_libraries(${PROJECT_NAME} foxylib)
