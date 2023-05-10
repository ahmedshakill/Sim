#ifndef H_INSTRUCTION
#define H_INSTRUCTION

//#include "Mnemonic.hpp"
#include <string>
#include <utility>
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
//    Mnemonic mnemonic;
    InstType instType;
    std::string bin_str;
    Instruction()=default;
    Instruction(InstType _instType, std::string _opcode) :instType(_instType),opcode(std::move(_opcode)){}
    virtual ~Instruction()= default;
};

class RtypeInstruction : public Instruction
{
public:
    enum class Mnemonic{
        /*RType*/
        ADD=-100,
        SUB,
        MUL,
        SLL,
        MULH,
        SLT,
        MULHSU,
        SLTU,
        MULHU,
        XOR,
        DIV,
        SRL,
        SRA,
        DIVU,
        OR,
        REM,
        AND,
        REMU,

        /*RWType*/
        ADDW,
        SUBW,
        MULW,
        SLLW,
        DIVW,
        SRLW,
        SRAW,
        DIVUW,
        REMW,
        REMUW,
        NOT_SET
    };
    Mnemonic mnemonic;
    std::string rd,f3,rs1,rs2,f7;
    RtypeInstruction()=default;
    RtypeInstruction(InstType _instType, std::string _opcode) ;
};
class ItypeInstruction : public Instruction
{
public:

    enum class Mnemonic{
        /*IType0000011*/
        LB=-100,
        LH,
        LW,
        LD,
        LBU,
        LHU,
        LWU,

        /*IType0010011*/
        ADDI,
        SLLI,
        SLTI,
        SLTIU,
        XORI,
        SRLI,
        SRAI,
        ORI,
        ANDI,

        /*IType1100111*/
        JALR,

        /*IType1110011*/
        ECALL,
        EBREAK,
        CSRRW,
        CSRRS,
        CSRRC,
        CSRRWI,
        CSRRSI,
        CSRRCI,

        /*IWType*/
        ADDIW,
        SLLIW,
        SRLIW,
        SRAIW,
        NOT_SET
    };
    Mnemonic mnemonic;
    std::string rd,f3,rs1,imm12,f7,shamt,csr,zimm;
    ItypeInstruction()=default;
    ItypeInstruction(InstType _instType, std::string _opcode) ;
};
class StypeInstruction : public Instruction
{
public:
    enum class Mnemonic{
        /*SType*/
        SB=-100,
        SH,
        SW,
        SD,
        NOT_SET
    };
    Mnemonic mnemonic;
    std::string f3,rs1,rs2,imm12;
    StypeInstruction()=default;
    StypeInstruction(InstType _instType, std::string _opcode);
};
class BtypeInstruction : public Instruction
{
public:
    enum class Mnemonic{
        BEQ=-100,
        BNE,
        BLT,
        BGE,
        BLTU,
        BGEU,
        NOT_SET
    };
    Mnemonic mnemonic;
    std::string f3,rs1,rs2,imm12;
    BtypeInstruction()=default;
    BtypeInstruction(InstType _instType, std::string _opcode);
};
class UtypeInstruction : public Instruction
{
public:
    enum class Mnemonic{
        /*Utype*/
        LUI=-100,
        AUIPC,
        NOT_SET
    };
    Mnemonic mnemonic;
    std::string rd,imm20;
    UtypeInstruction()=default;
    UtypeInstruction(InstType _instType, std::string _opcode) ;
};
class JtypeInstruction : public Instruction
{
public:
    enum class Mnemonic{
        /**/
        JAL=-100,
        NOT_SET
    };
    Mnemonic mnemonic;
    std::string rd,imm20;
    JtypeInstruction()=default;
    JtypeInstruction(InstType _instType, std::string _opcode);
};

#endif