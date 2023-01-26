#pragma once

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(x)
#else
#include <unistd.h>
#endif

#ifndef __cplusplus
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
