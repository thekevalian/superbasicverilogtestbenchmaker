#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "msgfiles.h"
#include <stdint.h>
#include <boost/dynamic_bitset.hpp>
#include <vector>

typedef enum{
	EXECUTABLE_NAME = 0,
	OUTPUT_FILE = 1,
	INPUT_NUM = 2,
	OUTPUT_NUM = 3,
	INPUT_OPT = 4,
	INPUT_DATA = 5,
	MIN_ARGS
}arg_type;

typedef enum{
	EXIT_SUCCESSFUL,
	EXIT_NOT_ENOUGH_INPUTS,
	EXIT_INPUT_TYPE_NOT_SUPPORTED,
	EXIT_OUTPUT_FILE_ALREADY_EXISTS
}exit_type;


int main(int argc, char** argv){
		
	if (argc < MIN_ARGS) {
		std::cout << "Not Enough Inputs\n";
		std::cout << invalidCallMessage;
		return EXIT_NOT_ENOUGH_INPUTS;
	}
	std::string module_name(argv[OUTPUT_FILE]);
	int inputs = std::stoi(argv[INPUT_NUM]);
	int outputs = std::stoi(argv[OUTPUT_NUM]);

	int input_opt = std::stoi(argv[INPUT_OPT]);	
	if(input_opt > 2 || input_opt < 0){
		std::cout << "Input type not supported yet\n";
		return EXIT_INPUT_TYPE_NOT_SUPPORTED;
	}
	
	std::vector<boost::dynamic_bitset<>> output_arr; 
	if(input_opt == 0){
		/* Process Input type 0 */
		for (int i = 0; i < outputs; i++){
			output_arr.push_back(boost::dynamic_bitset<>(std::string((char*)argv[INPUT_DATA+i])));
		}
	}		

	if(module_name.empty()) module_name = std::string("tb_default");

	/* Check if file exists, if it does error*/
	std::ifstream potential_tb_file(module_name);
	if(potential_tb_file.good()){
		std::cout << "Output File Already Exists! Please remove before running\n";
		return EXIT_OUTPUT_FILE_ALREADY_EXISTS;
	}

	// std::ofstream output_tb_file;
	// output_tb_file.open(module_name);
	// output_tb_file.close();

	return EXIT_SUCCESSFUL;
}

