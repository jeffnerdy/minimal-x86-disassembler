#include <iostream>

#include "decoder.h"


//OPCODE

// procedure definition
OPCODE::OPCODE() : mnemonic(""), r_REGISTER(""), hasMODRM(0), hasIMM(0), extended_OPCODE(0), reduced_REGISTER(0) {}
OPCODE::OPCODE(const char* opcode, const char* r_register, bool hasmodrm, bool hasimm, bool extended_op, bool reduced_reg) : mnemonic(opcode), r_REGISTER(r_register), hasMODRM(hasmodrm), hasIMM(hasimm), extended_OPCODE(extended_op), reduced_REGISTER(reduced_reg) {}

const char* OPCODE::getSmnemonic() { return mnemonic; }
const char* OPCODE::getSr_REGISTER() { return r_REGISTER; }

bool OPCODE::getFMODRM() { return hasMODRM; }
bool OPCODE::getFIMM(){ return hasIMM; }

bool OPCODE::getFXOPCODE() { return extended_OPCODE; }
bool OPCODE::getFRREGISTER() { return reduced_REGISTER; }
//endof OPCODE

// list initialization
const char* register_list[4][8] = { {"[eax]", "[ecx]", "[edx]", "[ebx]", "[esp]", "[ebp]", "[esi]", "[edi]"},
				    {}, {},
				    {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"} };

std::unordered_map<int, OPCODE> opcode_list = { { 0xE9, OPCODE("jmp", "", 0, 1, 0, 0)},
						{ 0x90, OPCODE("nop", "", 0, 0, 0, 0) },

						// OPCODE + r (r = REG)
						{ 0X81 + 0X00, OPCODE("add", "", 1, 1, 1, 0) },
						{ 0X81 + 0X01, OPCODE("or", "", 1, 1, 1, 0) },
						{ 0X81 + 0X04, OPCODE("and", "", 1, 1, 1, 0) },
						{ 0X81 + 0X05, OPCODE("sub", "", 1, 1, 1, 0) },
						{ 0X81 + 0X07, OPCODE("cmp", "", 1, 1, 1, 0) },

						// OPCODE + r (r = 0)
						{ 0XB8 + 0x00, OPCODE("mov", "eax", 0, 1, 0, 1) },
						{ 0X40 + 0x00, OPCODE("inc", "eax", 0, 0, 0, 1) },
						{ 0X48 + 0x00, OPCODE("dec", "eax", 0, 0, 0, 1) },
						{ 0X50 + 0x00, OPCODE("push", "eax", 0, 0, 0, 1) },
						{ 0x58 + 0x00, OPCODE("pop", "eax", 0, 0, 0, 1) },

						// OPCODE + r (r = 1)
						{ 0XB8 + 0x01, OPCODE("mov", "ecx", 0, 1, 0, 1) },
						{ 0X40 + 0x01, OPCODE("inc", "ecx", 0, 0, 0, 1) },
						{ 0X48 + 0x01, OPCODE("dec", "ecx", 0, 0, 0, 1) },
						{ 0X50 + 0x01, OPCODE("push", "ecx", 0, 0, 0, 1) },
						{ 0x58 + 0x01, OPCODE("pop", "ecx", 0, 0, 0, 1) },

						// OPCODE + r (r = 2)
						{ 0XB8 + 0x02, OPCODE("mov", "edx", 0, 1, 0, 1) },
						{ 0X40 + 0x02, OPCODE("inc", "edx", 0, 0, 0, 1) },
						{ 0X48 + 0x02, OPCODE("dec", "edx", 0, 0, 0, 1) },
						{ 0X50 + 0x02, OPCODE("push", "edx", 0, 0, 0, 1) },
						{ 0x58 + 0x02, OPCODE("pop", "edx", 0, 0, 0, 1) },

						// OPCODE + r (r = 3)
						{ 0XB8 + 0x03, OPCODE("MOV", "ebx", 0, 1, 0, 1) },
						{ 0X40 + 0x03, OPCODE("inc", "ebx", 0, 0, 0, 1) },
						{ 0X48 + 0x03, OPCODE("dec", "ebx", 0, 0, 0, 1) },
						{ 0X50 + 0x03, OPCODE("push", "ebx", 0, 0, 0, 1) },
						{ 0x58 + 0x03, OPCODE("pop", "ebx", 0, 0, 0, 1) },

						// OPCODE + r (r = 4)
						{ 0XB8 + 0x04, OPCODE("mov", "esp", 0, 1, 0, 1) },
						{ 0X40 + 0x04, OPCODE("inc", "esp", 0, 0, 0, 1) },
						{ 0X48 + 0x04, OPCODE("dec", "esp", 0, 0, 0, 1) },
						{ 0X50 + 0x04, OPCODE("push", "esp", 0, 0, 0, 1) },
						{ 0x58 + 0x04, OPCODE("pop", "esp", 0, 0, 0, 1) },

						// OPCODE + r (r = 5)
						{ 0XB8 + 0x05, OPCODE("mov", "ebp", 0, 1, 0, 1) },
						{ 0X40 + 0x05, OPCODE("inc", "ebp", 0, 0, 0, 1) },
						{ 0X48 + 0x05, OPCODE("dec", "ebp", 0, 0, 0, 1) },
						{ 0X50 + 0x05, OPCODE("push", "ebp", 0, 0, 0, 1) },
						{ 0x58 + 0x05, OPCODE("pop", "ebp", 0, 0, 0, 1) },

						// OPCODE + r (r = 6)
						{ 0XB8 + 0x06, OPCODE("mov", "esi", 0, 1, 0, 1) },
						{ 0X40 + 0x06, OPCODE("inc", "esi", 0, 0, 0, 1) },
						{ 0X48 + 0x06, OPCODE("dec", "esi", 0, 0, 0, 1) },
						{ 0X50 + 0x06, OPCODE("push", "esi", 0, 0, 0, 1) },
						{ 0x58 + 0x06, OPCODE("pop", "esi", 0, 0, 0, 1) },

						// OPCODE + r (r = 7)
						{ 0XB8 + 0x07, OPCODE("mov", "edi", 0, 1, 0, 1) },
						{ 0X40 + 0x07, OPCODE("inc", "edi", 0, 0, 0, 1) },
						{ 0X48 + 0x07, OPCODE("dec", "edi", 0, 0, 0, 1) },
						{ 0X50 + 0x07, OPCODE("push", "edi", 0, 0, 0, 1) },
						{ 0x58 + 0x07, OPCODE("pop", "edi", 0, 0, 0, 1) }, };
