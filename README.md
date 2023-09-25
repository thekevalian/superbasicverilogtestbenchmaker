IN PROGRESS with 0

MOTIVATION:
	tired of copy pasting to check if program works correctly in Vivado

LINKED TO boost

General Function Call
verilogtestBench [output_file] [num_inputs] [num_outputs] [input_feed_opt] [input]

output_file - name of testbench file with inputs in order
num_inputs - Number of Inputs going into the module
num_outputs - Number of Outputs going out of the module

input_feed_opt and input:
	0 - string of 0s, and 1s with output in order per output
		ie. 
		verilogtestBench 2 2 0 0001 0111 ; first output is an AND gates and second is an OR gate
	1 - string of minterms with sentinels of -o per output (including the first one)
		ie. 
		verilogtestBench 2 2 1 -o 1 -o 1 2 3
	2 - CSV
		tbd
	3 - write a function:
		to generate the outputs (goal)

I need a class that basically takes my inputs and converts it into how it wants it
so, for efficiency, assuming i store my results in bitsets and ideally, i would use m*2^(n-3) bytes

