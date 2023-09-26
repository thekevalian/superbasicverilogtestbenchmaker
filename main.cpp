#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "msgfiles.h"
#include <stdint.h>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <math.h>

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
	EXIT_OUTPUT_FILE_ALREADY_EXISTS,
	EXIT_NOT_ENOUGH_OUTPUT_ARGS
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
	unsigned long long iterations = powl(2, (long unsigned)inputs);
	std::vector<boost::dynamic_bitset<>> output_arr; 
	if(input_opt == 0){
		/* Process Input type 0 */
		for (int i = 0; i < outputs; i++){
			output_arr.push_back(boost::dynamic_bitset<>(std::string((char*)argv[INPUT_DATA+i])));
		}
	}		

	if(input_opt == 1){
		/* Process Input type 1*/
		int args_to_check = INPUT_DATA;
		int num_outputs_recieved = 0;
		while(args_to_check < argc){
			if(strcmp(argv[args_to_check], "-o") == 0){
				/* -o flag indicates the following are outputs*/
				args_to_check++;
				output_arr.push_back(boost::dynamic_bitset<>(iterations));
				while (args_to_check < argc && strcmp(argv[args_to_check], "-o"))
				{
					/* code */
					output_arr[num_outputs_recieved].set(iterations-std::stoi(argv[args_to_check])-1);
					args_to_check++;
				}
				
				num_outputs_recieved++;
				std::cout << output_arr[num_outputs_recieved-1] << "\n";
				
			}else{
				std::cout << "Error: NOT ENOUGH OUTPUT ARGS\n";
				return EXIT_NOT_ENOUGH_OUTPUT_ARGS;
			}
		}
	}



	if(module_name.empty()) module_name = std::string("default");
	std::string output_tb_file_name = std::string("tb_").append(module_name).append(".v");
	/* Check if file exists, if it does error*/
	std::ifstream potential_tb_file(output_tb_file_name);
	if(potential_tb_file.good()){
		std::cout << "Output File Already Exists! Please remove before running\n";
		return EXIT_OUTPUT_FILE_ALREADY_EXISTS;
	}

	std::ofstream output_tb_file;
	output_tb_file.open(output_tb_file_name);

	output_tb_file << "`timescale 1ns / 1ps\n\n";
	output_tb_file << "module " << module_name << ";\n";
	output_tb_file << "\t// Inputs, defined as registers\n";
	output_tb_file << "reg ";
	std::string input_prefix("in");
	for(int i = 0; i < inputs; i++){
		if(i == inputs - 1){
			output_tb_file << input_prefix << i << ";\n\n";
			break;
		}
		output_tb_file << input_prefix << i << ", ";
	}

	output_tb_file << "\t// Outputs, defined as wires\n";
	std::string output_prefix("out");
	output_tb_file << "wire ";
	for(int j = 0 ; j< outputs; j++){
		if(j == outputs - 1){
			output_tb_file << output_prefix << j << ";\n\n";
			break;
		}
		output_tb_file << output_prefix << j << ", ";
	}

	    
    output_tb_file << "\t// Instantiate the UUT (unit under test)\n";
	output_tb_file << "\t"<< module_name << " uut(\n";
	for(int i = 0; i< inputs; i++){
		output_tb_file << "\t" << input_prefix << i << ",\n";
	}
	for(int j = 0; j< outputs; j++){
		if(j == outputs-1){
			output_tb_file << "\t" << output_prefix << j << "\n);\n";
			break;
		}
		output_tb_file << "\t" << output_prefix << j << ",\n";
	}

	output_tb_file << "\tinitial begin\n\n";

	// Initialize Inputs
	output_tb_file << "\t // Initialize Inputs\n";
	for(int i = 0; i< inputs; i++){
		output_tb_file << "\t" << input_prefix << i << " = 0;\n";
	}
	output_tb_file << "\t" << "#50;\n";
	
	for(long long unsigned i = 0; i< iterations;i++){
		output_tb_file << "\n";
		for(int j = 0; j<inputs;j++){
			output_tb_file << "\t" << input_prefix << i << " = " << ((i>>(inputs-1-j))&1) << ";\n";
		}
		
		output_tb_file << "\t$display(\"TC" << i << "\");\n";
		for(int j = 0; j< outputs; j++){
			output_tb_file << "\tif ( " << output_prefix << j << " != " << "1'b" << output_arr[j].test(iterations-i-1) << " ) $display(\"Result is wrong\");\n";
			
		}
		output_tb_file << "\t" << "#50;\n";
	}

	output_tb_file << "\n\n\n\tend\n\n\nendmodule";
	output_tb_file.close();

	return EXIT_SUCCESSFUL;
}

