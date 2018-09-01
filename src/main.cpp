#include "main.hpp"
#include <array>
#include <boost/program_options.hpp>

// for SIGFAULT
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <iostream>
#include <streambuf>
#include <fstream>
#include <string>

#include "CLI.hpp"

std::string	fileName;
int	verboseLevel = 0;

void sigFaultHandler(int sig) {
	void *array[10];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, 10);

	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

int		main(int argc, char **argv) {
	try {
		CLI				cli(argc, argv);

		signal(SIGSEGV, sigFaultHandler);

		if (cli.isFlagSet("help"))
			return (0);
		if (argc == 2) {
			cli.startLogic();
			return (0);
		}
		else {
			std::cerr << "Error: invalid arguments" << std::endl;
			std::cout << "Usage: " << argv[0] << " [input file]\n" << std::endl;
			return (-1);	
		}
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
