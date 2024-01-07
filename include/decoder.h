#pragma once

#include <unordered_map>


//Decoder

class Decoder
{
	//decoding procedures
};
//endof Decoder

//OPCODE

class OPCODE
{
private:
	const char* mnemonic;
	const char* r_REGISTER;

	bool hasMODRM;
	bool hasIMM;

	bool extended_OPCODE;
	bool reduced_REGISTER;

public:
	OPCODE();
	OPCODE(const char* opcode, const char* r_register, bool hasmodrm, bool hasimm, bool extended_op, bool reduced_reg);

	const char* getSmnemonic();
	const char* getSr_REGISTER();

	bool getFMODRM();
	bool getFIMM();

	bool getFXOPCODE();
	bool getFRREGISTER();
};
//endof OPCODE

//externs
extern std::unordered_map<int, OPCODE> opcode_list;
extern const char* register_list[4][8];