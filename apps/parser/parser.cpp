#include "parser.hpp"
#include <iostream>

int main() {
	Parser   parser;

	parser.parse("USER name hostname servername ");

	Args A = parser.getArgument();

	std::cout << parser.getCommand() << std::endl;
	std::cout << parser.getRaw() << std::endl;
	std::cout << A.arg1 << std::endl;
	std::cout << A.arg2 << std::endl;
	std::cout << A.arg3 << std::endl;
	std::cout << A.arg4 << std::endl;

	std::cout << parser << std::endl;

}
