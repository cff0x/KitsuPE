#pragma once
#include <foxylib/platform.h>
#include <iostream>
#include <string>

class pong {
public:
	pong(const std::string& exit_phrase);
	~pong();

	void start_loop();
	void stop_loop();
private:
	bool m_is_running;
	std::string m_exit_phrase;
};