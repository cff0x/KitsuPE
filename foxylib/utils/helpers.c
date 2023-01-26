#include <foxylib/utils/helpers.h>

size_t get_unix_timestamp(char* dest) {
    size_t result = 0;

    // if destination char pointer is not empty, we fill it with
    // a unix timestamp (seconds since epoch)
    if(dest != NULL) {
        sprintf_s(dest, 16, "%lu", (unsigned long)time(NULL));
        result = strlen(dest);
    }

    return result;
}

size_t get_formatted_timestamp(char* dest , const char* fmt) {
    // create variables
    size_t result = 0;
    time_t timestamp;
    struct tm time_info;

    // retrieve current time data
    time(&timestamp);
    localtime_s(&time_info, &timestamp);

    // build formatted timestamp string and store it in dest char pointer
    // as long as it's not NULL
    if(dest != NULL) {
        strftime(dest, strlen(fmt) * 2, fmt, &time_info);
        result = strlen(dest);
    }

    return result;
}

size_t count_char_occurrences_in_string(const char* str, const char find) {
    // get input string length
    size_t len = strlen(str);

    // iterate through the input string and count all occurences of "find"
    int nchar = 0;
    for (int i = 0; i != len; i++) {
        if(str[i] != find) {
            nchar++;
        }
    }

    // return number of found chars
    return nchar;
}


size_t count_whitespaces_in_string(const char* str) {
    // get input string length
    size_t len = strlen(str);

    // iterate through the input string and count all whitespaces
    // (including newline and tab)
    int nchar = 0;
    for (int i = 0; i != len; ++i) {
        if(isspace(str[i])) {
            nchar++;
        }
    }

    // return number of found whitespace chars
    return nchar;
}

size_t convert_to_uppercase(char* dest, const char* src) {
    // get length of input string
    size_t len = strlen(src);

    // allocate destination buffer
    dest = malloc(len);

    // iterate through the input string and write uppercase
    // string to dest buffer
    for(int i = 0; i != len; ++i) {
        dest[i] = toupper(src[i]);
    }

    // return string length
    return len;
}

size_t convert_to_lowercase(char* dest, const char* src) {
    // get length of input string
    size_t len = strlen(src);

    // allocate destination buffer
    dest = malloc(len);

    // iterate through the input string and write lowercase
    // string to dest buffer
    for(int i = 0; i != len; ++i) {
        dest[i] = tolower(src[i]);
    }

    // return string length
    return len;
}