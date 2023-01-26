#pragma once
#include <foxylib/platform.h>

// returns a unix timestamp in seconds since epoch
size_t get_unix_timestamp(char* dest);

// creates a formatted timestamp based on the current time and a given format string
size_t get_formatted_timestamp(char* dest , const char* fmt);

// counts all occurrences of char "find" in the given string and returns the number
size_t count_char_occurrences_in_string(const char* str, const char find);

// counts all occurrences of whitespaces (including newline and tab) in a given string
size_t count_whitespaces_in_string(const char* str);
