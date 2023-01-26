#pragma once

#include <foxylib/platform.h>

#include <stdint.h>
#include <stdio.h>
#include <signal.h>


int main(int argc, char** argv);
void pong_loop();
void sigint_handler(int val);