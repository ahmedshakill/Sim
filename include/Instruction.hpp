#ifndef H_INSTRUCTION
#define H_INSTRUCTION

#include "Mnemonic.hpp"
#include <string>
enum class InstType{
    RType=-100,
    RWType,
    IType0000011,
    IType0010011,
    IType1100111,
    IType1110011,
    IWType,
    SType,
    BType,
    UType0010111,
    UType0110111,
    JType
};
class Instruction
{
public:
    std::string opcode{};
    Mnemonic mnemonic;
    InstType instType;
    std::string bin_str;
    Instruction()=default;
    Instruction(InstType _instType, std::string _opcode) :instType(_instType),opcode(_opcode){}
    virtual ~Instruction(){};
};

class RtypeInstruction : public Instruction
{
public:
    std::string rd,f3,rs1,rs2,f7;
    RtypeInstruction()=default;
    RtypeInstruction(InstType _instType, std::string _opcode) : Instruction(_instType,_opcode){};
};
class ItypeInstruction : public Instruction
{
public:
    std::string rd,f3,rs1,imm12,f7,shamt,csr,zimm;
    ItypeInstruction()=default;
    ItypeInstruction(InstType _instType, std::string _opcode) : Instruction(_instType,_opcode){};
};
class StypeInstruction : public Instruction
{
public:
    std::string f3,rs1,rs2,imm12;
    StypeInstruction()=default;
    StypeInstruction(InstType _instType, std::string _opcode) : Instruction(_instType,_opcode){};
};
class BtypeInstruction : public Instruction
{
public:
    std::string f3,rs1,rs2,imm12;
    BtypeInstruction()=default;
    BtypeInstruction(InstType _instType, std::string _opcode) : Instruction(_instType,_opcode){};
};
class UtypeInstruction : public Instruction
{
public:
    std::string rd,imm20;
    UtypeInstruction()=default;
    UtypeInstruction(InstType _instType, std::string _opcode) : Instruction(_instType,_opcode){};
};
class JtypeInstruction : public Instruction
{
public:
    std::string rd,imm20;
    JtypeInstruction()=default;
    JtypeInstruction(InstType _instType, std::string _opcode) : Instruction(_instType,_opcode){};
};

#endif