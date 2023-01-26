#include "pong.hpp"

pong::pong(const std::string& exit_phrase) :
	m_is_running{ false },
	m_exit_phrase{ exit_phrase } {

}

pong::~pong() {

}

void pong::start_loop() {
	this->m_is_running = true;
	
	// start input loop
	while (this->m_is_running) {
		// variable used to store the user input
		std::string input_buffer{};

		// retrieve user input
		std::cout << "\nTell me something (say \"" << m_exit_phrase << "\" and I'll stop): ";
		std::getline(std::cin, input_buffer);

		// stop if user wants us to, otherwise repeat what he said
		if (input_buffer.compare(m_exit_phrase) == 0) {
			this->m_is_running = false;
			std::cout << "Oh noooo! Bai baii~ QwQ\n\n";
		} else if (input_buffer.length() > 0) {
			std::cout << "That's what you said: " << input_buffer << "\n";
		}

		sleep(10);
	}
}

void pong::stop_loop() {
	this->m_is_running = false;
}