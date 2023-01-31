# KitsuPE
In this repository, you'll find some sort of playground I use for my PE (portable executable) file modification stuff.
The code should be compiled using LLVM for Windows because I replace/redefine some intrinsic functions (i.e. memset)
for substituting usage of the regular Win32 CRT.

## shellcode
The project `shellcode` contains shellcode which will be compiled into a .exe file. The `extract.py` script extracts the compiled code
from the .exe file into a `shellcode.bin` file, ready to be loaded as shellcode from a native Win32 application.

`shellcode_test` implements a default shellcode loader to test this one.

## foxywinapi
In these files I added some basic support headers used for Win32 API stuff and as a basic CRT replacement.

## foxylib
Contains some helper functions for logging and a debug console (including executable commands). These have no special
use yet, but I'm sure I will find a purpose for this.

## pe_stub
Stub PE file which will later be used for writing a .exe file packer (this will be the loader).

## basic_applications
Contains basic C/C++ applications which I will use to test my PE packer with.