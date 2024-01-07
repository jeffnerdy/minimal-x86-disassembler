#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <format>

#include "decoder.h"


int main()
{
	//buffers
	std::string string_buffer;
	std::vector<int> byte_buffer;
	std::set<char> hexadecimals = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
							        'A', 'B', 'C', 'D', 'E', 'F',
							        'a', 'b', 'c', 'd', 'e', 'f' };

	//buffers size
	size_t string_buffer_size = 0, byte_buffer_size = 0;

	//temporary buffers
	const char* opcode = "";
	const char* reg = "";
	std::string immediate, temp;

	//main loop
	while (std::getline(std::cin, string_buffer))
	{
		//INPUT

		string_buffer_size = string_buffer.size();

		for (std::string::size_type i = 0; i < string_buffer_size; i++)
		{
			if (hexadecimals.count(string_buffer[i]))
			{
				temp += string_buffer[i];

				if (temp.size() == 2)
				{
					byte_buffer.emplace_back(std::stoi(temp, 0, 16));
					temp.clear();
				}
			}

			if (byte_buffer.size() == 15) break; // the decoder only takes one instruction at a time, which is a maximum of 15 bytes.
		}


		//DECODING

		// check if opcode is supported
		if (!byte_buffer.empty() && opcode_list.find(byte_buffer[0]) != opcode_list.end())
		{
			if (opcode_list[byte_buffer[0]].getFXOPCODE())
			{
				opcode = opcode_list[byte_buffer[0] + ((byte_buffer[1] & 56) >> 3)].getSmnemonic();
			}
			else {
				opcode = opcode_list[byte_buffer[0]].getSmnemonic();
			}
		}
		else {
			std::cerr << "error: invalid instruction or opcode not supported.\n" << std::endl;

			// reset buffers
			string_buffer.clear();
			byte_buffer.clear();
			temp.clear();
			
			// return execution to INPUT
			continue;
		}

		// check the existance of a register
		if (opcode_list[byte_buffer[0]].getFMODRM())
		{
			reg = register_list[byte_buffer[1] >> 6][byte_buffer[1] & 7];
		}
		else if (opcode_list[byte_buffer[0]].getFRREGISTER())
		{
			reg = opcode_list[byte_buffer[0]].getSr_REGISTER();
		}

		// check the existance of an immediate
		byte_buffer_size = byte_buffer.size();

		if (opcode_list[byte_buffer[0]].getFIMM())
		{
			for (size_t i = byte_buffer_size - 1; i > (byte_buffer_size - 5); i--)
			{
				if (byte_buffer[i] < 10) immediate += '0';
				immediate += std::format("{:x}", byte_buffer[i]);
			}
		}


		//OUTPUT

		std::cout << opcode;

		if (reg != "" && immediate != "")
		{
			std::cout << " " << reg << ", " << "0x" << immediate;
		}
		else if (reg != "")
		{
			std::cout << " " << reg;
		}
		else if (immediate != "")
		{
			std::cout << " " << "0x" << immediate;
		}

		std::cout << "\n" << std::endl;
		//endof OUTPUT
		
		// reset buffers
		string_buffer.clear();
		byte_buffer.clear();
		temp.clear();
		immediate.clear();
		opcode = "";
		reg = "";
	}

	return 0;
}