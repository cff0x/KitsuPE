#include "main.hpp"
#include "pong.hpp"





static const std::string EXIT_PHRASE = "go away";
pong app{ EXIT_PHRASE };

int main(int argc, char** argv) {
	// register SIGINT handler (CTRL+C)
	signal(SIGINT, sigint_handler);

	std::cout << "Henlo! I'm a smol and basic application written in C++.\n";

    //std::cout;
	//app.start_loop();

	return 0;
}

void sigint_handler(int val)
{
	app.stop_loop();
	std::cout << "\nOH NO OH NO HELP! WHY ARE YOU DOING THIS TO ME? :C\n";
	exit(val);
}
