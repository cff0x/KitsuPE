#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import pefile
import argparse
import os

if __name__ in "__main__":
    try:
        parser = argparse.ArgumentParser(description="Extracts shellcode from a PE.")
        parser.add_argument("-f", required=True, help="Path to the source executable", type=str)
        parser.add_argument("-o", required=True, help="Path to store the output raw binary", type=str)
        option = parser.parse_args()

        pe_exe = pefile.PE(option.f)
        pe_section = pe_exe.sections[0].get_data()

        if pe_section.find(b"base"):
            section_raw = pe_section[:pe_section.find(b"base")]
            section_data = section_raw[:pe_exe.sections[0].Misc_VirtualSize]

            splitted_bin_path = os.path.split(option.o)
            filename_bin = splitted_bin_path[len(splitted_bin_path)-1].replace(".", "_")

            f = open(option.o, "wb")
            f.write(section_data)
            f.close()

            f = open(option.o + ".h", "w")
            f.write(f"#ifndef __{filename_bin.upper()}_H__\n#define __{filename_bin.upper()}_H__\n\n")
            f.write(f"const unsigned char {filename_bin}[{len(section_data)}] = ""{""\n")
            n = 0
            max_n = 16
            for i in range(len(section_data)):
                if n == 0:
                    f.write("    ")

                f.write("0x{:02X}".format(section_data[i]))

                if n <= max_n and i != len(section_data)-1:
                    f.write(", ")

                if n == max_n:
                    f.write("\n")
                    n = -1
                n += 1
            f.write("\n""}"f";\n\n#endif //__{filename_bin.upper()}_H__")
            f.close()
        else:
            print("[!] error: no ending tag")
    except Exception as e:
        print("[!] error: {}".format(e))
