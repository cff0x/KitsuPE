set(PROJECT_NAME "basic_gui_application")
set(PROJECT_VERSION "0.1")

project(${PROJECT_NAME} LANGUAGES C)

add_executable(${PROJECT_NAME} WIN32 "main.c" )
target_link_libraries(${PROJECT_NAME} foxylib basic_library)
