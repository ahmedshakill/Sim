#ifndef H_MNEMONIC
#define H_MNEMONIC

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

        /*IType0000011*/
        LB,
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

        /*SType*/
        SB,
        SH,
        SW,
        SD,

        /*BType*/
        BEQ,
        BNE,
        BLT,
        BGE,
        BLTU,
        BGEU,

    };

#endif