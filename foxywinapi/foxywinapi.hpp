#ifndef __FOXY_WINAPI_H__
#define __FOXY_WINAPI_H__
#include <lazy_importer.hpp>

// FoxyCRT - minimal Win32 CRT replacement
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdint>

// disable warnings for failed #pragma intrinsic directives
#pragma warning(disable : 4163)

extern "C" {
int strcmp(char const *str1, char const *str2) {
    for (; *str1 == *str2; str1++, str2++) {
        if (*str1 == '\0')
            return 0;
    }

    return ((*(char *) str1 < *(char *) str2) ? -1 : +1);
}

int w_strcmp(wchar_t const *cmp, wchar_t const *other) {
    WORD *w_cmp = (WORD *) cmp;
    WORD *w_other = (WORD *) other;
    while (*w_other != 0) {
        WORD lowercase_other = ((*w_other >= 'A' && *w_other <= 'Z')
                                ? *w_other - 'A' + 'a'
                                : *w_other);
        if (*w_cmp != lowercase_other) {
            return 0;
        }
        w_cmp++;
        w_other++;
    }
    return (*w_cmp == 0);
}

void *malloc(size_t Size) {
    return LI_FN(HeapAlloc)(LI_FN(GetProcessHeap)(), HEAP_ZERO_MEMORY, Size);
}

void free(void *ptr) {
    LI_FN(HeapFree)(LI_FN(GetProcessHeap)(), 0, ptr);
}

void *realloc(void *ptr, size_t new_size) {
    uint8_t *d = nullptr;
    uint8_t *s = nullptr;
    size_t size;

    if (new_size == 0)
        return nullptr;

    if (ptr == nullptr)
        return malloc(new_size);


    size_t old_size = LI_FN(HeapSize)(LI_FN(GetProcessHeap)(), 0, ptr);

    if (old_size == new_size) {
        return ptr;
    }

    // allocating new ptr and moving data to it (from ptr)
    void *new_ptr = malloc(new_size);

    d = (uint8_t *) new_ptr;
    s = (uint8_t *) ptr;
    size = old_size;
    for (volatile int i = 0; i < size; i++) {
        ((BYTE *) d)[i] = ((BYTE *) s)[i];
    }

    // setting ptr to 0
    uint64_t *dest = (uint64_t *) ptr;
    size = old_size / sizeof(uint64_t);
    while (size > 0) {
        *((uint8_t *) dest) = 0;
        dest++;
        size--;
    }
    free(ptr);

    return new_ptr;
}

#pragma function(memset)
void *memset(void *dest, int c, size_t count)
{
    char *bytes = (char *)dest;
    while (count--)
    {
        *bytes++ = (char)c;
    }
    return dest;
}

#pragma function(memcpy)
void *memcpy(void *dest, const void *src, size_t count)
{
    char *dest8 = (char *)dest;
    const char *src8 = (const char *)src;
    while (count--)
    {
        *dest8++ = *src8++;
    }
    return dest;
}

void *memmove(void *destination, const void *source, size_t num) {
    for (volatile int i = 0; i < num; i++) {
        ((uint8_t *) destination)[i] = ((uint8_t *) source)[i];
    }
    return destination;
}

#define printf(format, ...) ({ \
    char buf[1024]; \
    int result = 0; \
    LI_FN(wsprintfA).forwarded()(buf, format, __VA_ARGS__); \
    DWORD done; \
    LI_FN(WriteFile)(LI_FN(GetStdHandle)(STD_OUTPUT_HANDLE), buf, (DWORD) LI_FN(strlen)(buf), &done, nullptr); \
    result; \
})


/*int printf(const char *format, ...) {
    char buf[1024];
    va_list argList;
    va_start(argList, format);
    int result = 0;
    LI_FN(wvsprintfA).forwarded()(buf, format, argList);
    va_end(argList);
    DWORD done;
    LI_FN(WriteFile)(LI_FN(GetStdHandle)(STD_OUTPUT_HANDLE), buf, (DWORD) LI_FN(strlen)(buf), &done, nullptr);
    return result;
}*/

int puts(const char *s) {
    return printf("%s\n", s);
}

int sprintf(char *buf, const char *format, ...) {
    va_list argList;
        va_start(argList, format);
    int result = 0;
    LI_FN(wvsprintfA).forwarded()(buf, format, argList);
        va_end(argList);
    return result;
}

}

#endif //__FOXY_WINAPI_H__