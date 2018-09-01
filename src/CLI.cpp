#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "main.hpp"
#include "CLI.hpp"

#define INPUT_FILE_EXAMPLE															\
"\t# this is a comment\n"															\
"\t# all the required rules and symbols, along with the bonus ones, will be\n"		\
"\t# shown here. spacing is not important\n"										\
"\tC => E          # C implies E\n"													\
"\tA + B + C => D  # A and B and C implies D\n"										\
"\tA | B => C      # A or B implies C\n"											\
"\tA + !B => F     # A and not B implies F\n"										\
"\tC | !G => H     # C or not G implies H\n"										\
"\tV ^ W => X      # V xor W implies X\n"											\
"\tA + B => Y + Z  # A and B implies Y and Z\n"										\
"\tC | D => X | V  # C or D implies X or V\n"										\
"\tE + F => !V     # E and F implies not V\n"										\
"\tA + B <=> C     # A and B if and only if C\n"									\
"\tA + B <=> !C    # A and B if and only if not C\n"								\
"\t=ABG            # Initial facts : A, B and G are true. All others are false.\n"	\
"\t                # If no facts are initially true, then a simple '=' followed\n"	\
"\t                # by a newline is used\n"										\
"\t?GVX            # Queries : What are G, V and X ?\n"								\

bool	CLI::isFlagSet(const std::string &flag) const {
	if (this->vm.count(flag))
		return (true);
	return (false);
}

bool	CLI::getFlag(const std::string &flag, int &result) const {
	if (this->vm.count(flag)) {
		try {
			result = this->vm[flag].as<int>();
		}
		catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return (false);
		}
		return (true);
	}
	return (false);
}

bool	CLI::getFlag(const std::string &flag, std::string &result) const {
	if (this->vm.count(flag)) {
		try {
			result = this->vm[flag].as<std::string>();
		}
		catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return (false);
		}
		return (true);
	}
	return (false);
}

bool	CLI::processArguments(int argc, char **argv) {
	namespace po = boost::program_options;
	try {
		po::store(po::parse_command_line(argc, argv, this->desc), this->vm);
		po::notify(this->vm);

		if (this->vm.count("help")) {
			std::cout << "Usage: " << argv[0] << " [input file]\n" << std::endl;
			std::cout << desc << std::endl;
		}
	}
	catch (po::error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << desc << std::endl;
		return (false);
	}
	return (true);
}

CLI::CLI(int argc, char **argv) : desc("Options") {
	namespace po = boost::program_options;
	this->desc.add_options()
			("help,h", "Print help\n"
						"\t*** Example of input file\n"
						INPUT_FILE_EXAMPLE);

	if (!processArguments(argc, argv))
		throw CLI_invalidArguments();
}

CLI::~CLI() {}

void	runEngine() {
	
}

void	CLI::startLogic() const {
	// std::vector<int>	resultVector;
	// std::vector<int>	map;
	// std::string			fileName;
	// std::ifstream		file;
	// std::string			line;
	// NP_retVal			result;
	// int					mapSize, heuristic = 0, solutionType = 0;

	// this->getFlag("file", fileName);
	// file = std::ifstream(fileName);

	// if (!file.good())
	// 	throw CLI_InvalidFile();

	// while(std::getline(file, line)) {
	// 	// split line by whitespaces
	// 	std::istringstream iss(line);
	// 	std::vector<std::string> strings {
	// 		std::istream_iterator<std::string>(iss), {}
	// 	};

	// 	try {
	// 		int numberCount = 0;
	// 		for (auto str : strings) {
	// 			if (str.find('#') == std::string::npos) {
	// 				resultVector.push_back(boost::lexical_cast<int>(str));
	// 				numberCount++;
	// 			}
	// 			else
	// 				break;
	// 		}
	// 		if (resultVector.size() > 1 && numberCount &&
	// 			numberCount / resultVector.at(0) != 1)
	// 			throw CLI_InvalidMap();
	// 	}
	// 	catch(boost::bad_lexical_cast &e) {
	// 		std::cerr << "Error: " << e.what() << std::endl;
	// 		throw CLI_InvalidMap();
	// 	}
	// }
	// file.close();

	// if (resultVector.size() < 2)
	// 	throw CLI_InvalidMap();

	// this->getFlag("heuristic", heuristic);
	// this->getFlag("solution", solutionType);
	// this->getFlag("optimisation", optimisationByTime);

	// mapSize = resultVector[0];
	// for (unsigned i = 1; i < resultVector.size(); i++)
	// 	map.push_back(resultVector[i]);
	// result = solvePuzzle(map.data(), mapSize, heuristic, solutionType);
}
