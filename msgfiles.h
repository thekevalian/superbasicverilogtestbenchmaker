#ifndef MSGFILES_H
#define MSGFILES_H

const char* invalidCallMessage = "\nGeneral Function Call\nverilogtestBench [output_file] [num_inputs] [num_outputs] [input_feed_opt] [input]\n\noutput_file - name of testbench file with inputs in order\nnum_inputs - Number of Inputs going into the module\nnum_outputs - Number of Outputs going out of the module\n\ninput_feed_opt and input:\n\t0 - string of 0s, and 1s with output in order per output\n\t	ie. \n\t	verilogtestBench 2 2 0 0001 0111 ; first output is an AND gates and second is an OR gate\n\t1 - string of minterms with sentinels of -o per output (including the first one)\n\t	ie. \n\t	verilogtestBench 2 2 1 -o 1 -o 1 2 3\n\t2 - CSV\n\t	tbd\n\t3 - write a function:\n\t	to generate the outputs (goal)";


#endif
