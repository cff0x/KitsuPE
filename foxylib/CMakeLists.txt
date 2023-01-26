set(PROJECT_NAME "foxylib")

project(${PROJECT_NAME} LANGUAGES C)

add_library(${PROJECT_NAME} STATIC "utils/helpers.c" "utils/console/commands.c" "utils/console/console.c" "utils/logging/logging.c")
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PRIVATE "include/foxylib")
