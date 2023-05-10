#include "Decoder.hpp"
#include <bitset>


enum class Decoder::Func3{
        F000=-100,
        F001,
        F010,
        F011,
        F100,
        F101,
        F110,
        F111
    };

Decoder::Decoder(){
  
    Decoder::CodeToInstType = {
        {"0b0000011",   InstType::IType0000011},
        {"0b0010011",   InstType::IType0010011},
        {"0b0010111",   InstType::UType0010111},
        {"0b0011011",   InstType::IWType},
        {"0b0100011",   InstType::SType},
        {"0b0110011",   InstType::RType},
        {"0b0110111",   InstType::UType0110111},
        {"0b0111011",   InstType::RWType},
        {"0b1100011",   InstType::BType},
        {"0b1100111",   InstType::IType1100111},
        {"0b1101111",   InstType::JType},
        {"0b1110011",   InstType::IType1110011},
    };

    Decoder::CodeToFunc3={
        {"0b000",   Func3::F000},
        {"0b001",   Func3::F001},
        {"0b010",   Func3::F010},
        {"0b011",   Func3::F011},
        {"0b100",   Func3::F100},
        {"0b101",   Func3::F101},
        {"0b110",   Func3::F110},
        {"0b111",   Func3::F111},
    };

}

void Decoder::decode(const std::vector<std::string>& ins_buffer){
    
    for(const auto& str : ins_buffer){
        // std::cout<<str<<"\n";
        std::string bin_str{to_bit_string(str)};
        sstream << bin_str << std::endl;
        std::unique_ptr<Instruction> decoded_instruction {decode_instruction(bin_str)};
        if(not decoded_instruction->opcode.empty())
        decoded_inst_vec.push_back(std::move(decoded_instruction));
    }
}

std::unique_ptr<Instruction> Decoder::decode_instruction(const std::string& bin_str){
    int off = 7; 
    std::string oc_str = "0b" + bin_str.substr(32-off,off);
    InstType inst_type = CodeToInstType[oc_str];

    std::unique_ptr<Instruction> decoded_instruction_ptr;

    switch (inst_type)
    {
        case InstType::RType :
            {
                sstream<<"RType ";
                RtypeInstruction rinst{InstType::RType,oc_str};
                f3_R(bin_str,rinst);
                rinst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<RtypeInstruction>(std::move(rinst));
                break;
            }
        case InstType::RWType :
            {
                sstream<<"RWType ";
                RtypeInstruction rinst{InstType::RWType,oc_str };
                f3_RW(bin_str,rinst);
                rinst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<RtypeInstruction>(std::move(rinst));
                break;
            }
        case InstType::IType0000011:
            {
                ItypeInstruction iinst{  InstType::IType0000011,oc_str};
                f3_IType0000011(bin_str,iinst);
                iinst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<ItypeInstruction>(std::move(iinst));
                break;
            }
        case InstType::IType0010011:
            {
                // sstream<<"IType0010011 "<<std::endl;
                ItypeInstruction iinst{ InstType::IType0010011,oc_str };
                f3_IType0010011(bin_str,iinst);
                iinst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<ItypeInstruction>(std::move(iinst));
                break;
            }
        case InstType::IType1100111:
            {
                // sstream<<"IType1100111 "<<std::endl;
                ItypeInstruction iinst{ InstType::IType1100111,oc_str };
                f3_IType1100111(bin_str,iinst);
                iinst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<ItypeInstruction>(std::move(iinst));
                break;
            }
        case InstType::IType1110011:
            {
                // sstream<<"IType1110011 "<<std::endl;
                ItypeInstruction iinst{  InstType::IType1110011, oc_str};
                f3_IType1110011(bin_str,iinst);
                iinst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<ItypeInstruction>(std::move(iinst));
                break;
            }
        case InstType::IWType:
            {   
                sstream<<"IWType OC 0b0011011";
                ItypeInstruction iinst{  InstType::IWType, oc_str};
                f3_IW(bin_str,iinst);
                iinst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<ItypeInstruction>(std::move(iinst));
                break;
            }
        case InstType::SType :
            {
                sstream<<"SType ";
                StypeInstruction sinst{  InstType::SType, oc_str};
                f3_S(bin_str,sinst);
                sinst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<StypeInstruction>(std::move(sinst));
                break;
            }
        case InstType::BType :
            {
                sstream<<"BType ";
                BtypeInstruction binst{ InstType::BType, oc_str };
                f3_B(bin_str,binst);
                binst.bin_str= bin_str;
                decoded_instruction_ptr = std::make_unique<BtypeInstruction>(std::move(binst));
                break;
            }
        case InstType::UType0010111 :
            {
                std::string rd = bin_str.substr(20,5);
                std::string imm20 = bin_str.substr(0,20);
                sstream<<"UType AUIPC rd="<<rd<<" imm20="<<imm20<<" "<<std::endl;
                
                UtypeInstruction uinst{InstType::UType0010111,oc_str};
                uinst.bin_str= bin_str;
                uinst.rd=rd;
                uinst.imm20=imm20;
                decoded_instruction_ptr = std::make_unique<UtypeInstruction>(std::move(uinst));
                break;
            }
        case InstType::UType0110111 :
            {
                std::string rd = bin_str.substr(20,5);
                std::string imm20 = bin_str.substr(0,20);
                sstream<<"UType LUI rd="<<rd<<" imm20="<<imm20<<" "<<std::endl;
                
                UtypeInstruction uinst{InstType::UType0110111, oc_str};
                uinst.bin_str= bin_str;
                uinst.rd=rd;
                uinst.imm20=imm20;
                decoded_instruction_ptr = std::make_unique<UtypeInstruction>(std::move(uinst));
                break;
            }
        case InstType::JType :
            {
                std::string rd = bin_str.substr(20,5);
                std::string imm20 = bin_str.substr(1,10)+bin_str.substr(11,1)+bin_str.substr(12,8)+bin_str.substr(0,1);
                sstream<<"JType JAL rd="<<rd<<" imm20="<<imm20<<" "<<std::endl;
                
                JtypeInstruction jinst{InstType::JType, oc_str};
                jinst.bin_str= bin_str;
                jinst.rd=rd;
                jinst.imm20=imm20;
                decoded_instruction_ptr = std::make_unique<JtypeInstruction>(std::move(jinst));
                break;
            }
        default:
            break;
    }
    // unique_ptr_instruction
    return std::move(decoded_instruction_ptr);
}

void Decoder::f3_R(const std::string& bin_str, RtypeInstruction& rtypeInstruction){
        std::string f3_str = "0b" + bin_str.substr(17,3);
        std::string f7_str = "0b" + bin_str.substr(0,7);

        std::string rd  = bin_str.substr(20,5);
        std::string rs1 = bin_str.substr(12,5);
        std::string rs2 = bin_str.substr(7,5);
        Mnemonic mnemonic;
        
        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    sstream<<"F000 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::ADD; sstream<<"ADD ";}
                    if(f7_str == "0b0100000") { mnemonic=Mnemonic::SUB; sstream<<"SUB ";}
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::MUL; sstream<<"MUL ";}
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F001:
                {
                    sstream<<"F001 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::SLL ; sstream<<"SLL ";}
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::MULH ; sstream<<"MULH ";}
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F010:
                {
                    sstream<<"F010 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::SLT ; sstream<<"SLT ";}
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::MULHSU ; sstream<<"MULHSU ";}
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    sstream<<"F011 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::SLTU ; sstream<<"SLTU "; }
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::MULHU ; sstream<<"MULHU "; }
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    sstream<<"F100 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::XOR ; sstream<<"XOR "; }
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::DIV ; sstream<<"DIV "; }
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F101:
                {
                    sstream<<"F101 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::SRL ; sstream<<"SRL "; }
                    if(f7_str == "0b0100000") { mnemonic=Mnemonic::SRA ; sstream<<"SRA "; }
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::DIVU ; sstream<<"DIVU "; }
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F110:
                {
                    sstream<<"F110 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::OR ; sstream<<"OR ";}
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::REM ; sstream<<"REM ";}
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    sstream<<"F111 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::AND ; sstream<<"AND ";}
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::REMU ; sstream<<"REMU ";}
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
        
            default:
                break;
        }

        rtypeInstruction.rd=rd;
        rtypeInstruction.f3=f3_str;
        rtypeInstruction.rs1=rs1;
        rtypeInstruction.rs2=rs2;
        rtypeInstruction.f7=f7_str;
        rtypeInstruction.mnemonic=mnemonic;
}

void Decoder::f3_RW(const std::string& bin_str, RtypeInstruction& rtypeInstruction) {
        std::string f3_str = "0b" + bin_str.substr(17,3);
        std::string f7_str = "0b" + bin_str.substr(0,7);
        
        std::string rd = bin_str.substr(20,5);
        std::string rs1 = bin_str.substr(12,5);
        std::string rs2=bin_str.substr(7,5);

        Mnemonic mnemonic;

        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    sstream<<"F000 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::ADDW ; sstream<<"ADDW "; }
                    if(f7_str == "0b0100000") { mnemonic=Mnemonic::SUBW ; sstream<<"SUBW "; }
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::MULW ; sstream<<"MULW "; }
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F001:
                {
                    mnemonic=Mnemonic::SLLW ; 
                    sstream<<"F001 SLLW rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl ; 
                    break;
                }
            case Func3::F010:
                {
                    sstream<<"F010 "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    sstream<<"F011 "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    mnemonic=Mnemonic::DIVW ; 
                    sstream<<"F100 DIVW rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl ;
                    break;
                }
            case Func3::F101:
                {
                    sstream<<"F101 ";
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::SRLW ; sstream<<"SRLW "; }
                    if(f7_str == "0b0100000") { mnemonic=Mnemonic::SRAW ; sstream<<"SRAW "; }
                    if(f7_str == "0b0000001") { mnemonic=Mnemonic::DIVUW ; sstream<<"DIVUW "; }
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F110:
                {
                    mnemonic=Mnemonic::REMW ; 
                    sstream<<"F110 REMW rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    mnemonic=Mnemonic::REMUW ; 
                    sstream<<"F111 REMUW rd="<<rd<<" rs1="<<rs1<<" rs2="<<rs2<<" "<<std::endl; 
                    break;
                }
        
            default:
                break;
        }
        
//        RtypeInstruction rinst{};
        rtypeInstruction.rd=rd;
        rtypeInstruction.f3=f3_str;
        rtypeInstruction.rs1=rs1;
        rtypeInstruction.rs2=rs2;
        rtypeInstruction.f7=f7_str;
        rtypeInstruction.mnemonic=mnemonic;
//        return std::move(rinst);
}

void Decoder::f3_IType0000011(const std::string& bin_str, ItypeInstruction& itypeInstruction){
        std::string f3_str = "0b" + bin_str.substr(17,3);
        
        std::string rd = bin_str.substr(20,5);
        std::string rs1 = bin_str.substr(12,5);
        std::string imm12=bin_str.substr(0,12);
        
        Mnemonic mnemonic;
        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    mnemonic=Mnemonic::LB ;
                    sstream<<"IType0000011 F000 LB rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F001:
                {
                    mnemonic=Mnemonic::LH ;
                    sstream<<"IType0000011 F001 LH rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F010:
                {
                    mnemonic=Mnemonic::LW ;
                    sstream<<"IType0000011 F010 LW rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    mnemonic=Mnemonic::LD ;
                    sstream<<"IType0000011 F011 LD rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    mnemonic=Mnemonic::LBU ;
                    sstream<<"IType0000011 F100 LBU rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F101:
                {
                    mnemonic=Mnemonic::LHU ;
                    sstream<<"IType0000011 F101 LHU rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F110:
                {
                    mnemonic=Mnemonic::LWU ;
                    sstream<<"IType0000011 F110 LWU rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    sstream<<"IType0000011 F111 "<<std::endl;
                    break;
                }
        
            default:
                break;
        }

        itypeInstruction.rd=rd;
        itypeInstruction.f3=f3_str;
        itypeInstruction.rs1=rs1;
        itypeInstruction.imm12=imm12;
        itypeInstruction.mnemonic=mnemonic;

}

void Decoder::f3_IType0010011(const std::string& bin_str, ItypeInstruction& itypeInstruction){
        std::string f3_str = "0b" + bin_str.substr(17,3);
        std::string rd = bin_str.substr(20,5);
        std::string rs1 = bin_str.substr(12,5);
        std::string imm12{};
        std::string shamt{};
        std::string f7_str{};

        Mnemonic mnemonic;

        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    imm12 = bin_str.substr(0,12);
                    mnemonic=Mnemonic::ADDI ;
                    sstream<<"IType0010011 F000 ADDI rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F001:
                {   
                    shamt = bin_str.substr(7,5);
                    mnemonic=Mnemonic::SLLI ;
                    sstream<<"IType0010011 F001 SLLI rd="<<rd<<" rs1="<<rs1<<" shamt="<<shamt<<" "<<std::endl;
                    break;
                }
            case Func3::F010:
                {   
                    imm12 = bin_str.substr(0,12);
                    mnemonic=Mnemonic::SLTI ;
                    sstream<<"IType0010011 F010 SLTI rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    imm12 = bin_str.substr(0,12);
                    mnemonic=Mnemonic::SLTIU ;
                    sstream<<"IType0010011 F011 SLTIU rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    imm12 = bin_str.substr(0,12);
                    mnemonic=Mnemonic::XORI ;
                    sstream<<"IType0010011 F100 XORI rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F101:
                {
                    sstream<<"IType0010011 F101 "<<std::endl;
                    shamt = bin_str.substr(7,5);
                    f7_str = "0b" + bin_str.substr(0,7);
                    if(f7_str=="0b0000000") { mnemonic=Mnemonic::SRLI ; sstream<<"SRLI"<<std::endl;}
                    if(f7_str=="0b0100000") { mnemonic=Mnemonic::SRAI ; sstream<<"SRAI"<<std::endl;}
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" shamt="<<shamt<<" "<<std::endl;
                    break;
                }
            case Func3::F110:
                {
                    imm12 = bin_str.substr(0,12);
                    mnemonic=Mnemonic::ORI ;
                    sstream<<"IType0010011 F110 ORI  rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    imm12 = bin_str.substr(0,12);
                    mnemonic=Mnemonic::ANDI ;
                    sstream<<"IType0010011 F111 ANDI  rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
        
            default:
                break;
        }

//        ItypeInstruction iinst{};
        itypeInstruction.rd=rd;
        itypeInstruction.f3=f3_str;
        itypeInstruction.rs1=rs1;
        itypeInstruction.imm12=imm12;
        itypeInstruction.shamt=shamt;
        itypeInstruction.f7=f7_str;
        itypeInstruction.mnemonic=mnemonic;
//        return std::move(iinst);

}

void Decoder::f3_IType1100111(const std::string& bin_str, ItypeInstruction& itypeInstruction){
        std::string f3_str = "0b" + bin_str.substr(17,3);

        std::string rd = bin_str.substr(20,5);
        std::string rs1 = bin_str.substr(12,5);
        std::string imm12=bin_str.substr(0,12);
        
        Mnemonic mnemonic;
        
        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    mnemonic=Mnemonic::JALR;
                    sstream<<"IType1100111 F000 JALR rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F001:
                {
                    sstream<<"IType1100111 F001 "<<std::endl;
                    break;
                }
            case Func3::F010:
                {
                    sstream<<"IType1100111 F010 "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    sstream<<"IType1100111 F011 "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    sstream<<"IType1100111 F100 "<<std::endl;
                    break;
                }
            case Func3::F101:
                {
                    sstream<<"IType1100111 F101 "<<std::endl;
                    
                    break;
                }
            case Func3::F110:
                {
                    sstream<<"IType1100111 F110 "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    sstream<<"IType1100111 F111 "<<std::endl;
                    break;
                }
        
            default:
                break;
        }

        itypeInstruction.rd=rd;
        itypeInstruction.f3=f3_str;
        itypeInstruction.rs1=rs1;
        itypeInstruction.imm12=imm12;
        itypeInstruction.mnemonic=mnemonic;

}

void Decoder::f3_IType1110011(const std::string& bin_str, ItypeInstruction& itypeInstruction){
        std::string f3_str = "0b" + bin_str.substr(17,3);
        
        std::string rd = bin_str.substr(20,5);
        std::string csr = bin_str.substr(0,12);
        std::string rs1{};
        std::string zimm{};

        Mnemonic mnemonic;

        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    sstream<<"IType1110011 F000 ";
                    std::string last12bits ="0b" + bin_str.substr(0,12);
                    if(last12bits == "0b000000000000") { mnemonic=Mnemonic::ECALL; sstream<< "ECALL"<<std::endl;}
                    if(last12bits == "0b000000000001") { mnemonic=Mnemonic::EBREAK; sstream<< "EBREAK"<<std::endl;}
                    break;
                }
            case Func3::F001:
                {
                    rs1 = bin_str.substr(12,5);
                    mnemonic=Mnemonic::CSRRW ;
                    sstream<<"IType1110011 F001 CSRRW rd="<<rd<<" rs1="<<rs1<<" csr="<<csr<<" "<<std::endl;
                    break;
                }
            case Func3::F010:
                {
                    rs1 = bin_str.substr(12,5);
                    mnemonic=Mnemonic::CSRRS ;
                    sstream<<"IType1110011 F010 CSRRS rd="<<rd<<" rs1="<<rs1<<" csr="<<csr<<" "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    rs1 = bin_str.substr(12,5);
                    mnemonic=Mnemonic::CSRRC ;
                    sstream<<"IType1110011 F011 CSRRC rd="<<rd<<" rs1="<<rs1<<" csr="<<csr<<" "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    sstream<<"IType1110011 F100 "<<std::endl;
                    break;
                }
            case Func3::F101:
                {
                    zimm = bin_str.substr(12,5);
                    mnemonic=Mnemonic::CSRRWI ;
                    sstream<<"IType1110011 F101 CSRRWI rd="<<rd<<" zimm="<<zimm<<" csr="<<csr<<" "<<std::endl;
                    break;
                }
            case Func3::F110:
                {
                    zimm = bin_str.substr(12,5);
                    mnemonic=Mnemonic::CSRRSI ;
                    sstream<<"IType1110011 F110 CSRRSI rd="<<rd<<" zimm="<<zimm<<" csr="<<csr<<" "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    zimm = bin_str.substr(12,5);
                    mnemonic=Mnemonic::CSRRCI ;
                    sstream<<"IType1110011 F111 CSRRCI rd="<<rd<<" zimm="<<zimm<<" csr="<<csr<<" "<<std::endl;
                    break;
                }
        
            default:
                break;
        }

        itypeInstruction.rd=rd;
        itypeInstruction.f3=f3_str;
        itypeInstruction.rs1=rs1;
        itypeInstruction.zimm=zimm;
        itypeInstruction.csr=csr;
        itypeInstruction.mnemonic=mnemonic;

}

void Decoder::f3_IW(const std::string& bin_str, ItypeInstruction& itypeInstruction){
        std::string f3_str = "0b" + bin_str.substr(17,3);
        std::string f7_str = "0b" + bin_str.substr(0,7);
        
        std::string rd = bin_str.substr(20,5);
        std::string rs1 = bin_str.substr(12,5);
        std::string imm12{};
        std::string shamt{};
        
        Mnemonic mnemonic;
        
        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    imm12=bin_str.substr(0,12);
                    mnemonic=Mnemonic::ADDIW ;
                    sstream<<"F000 ADDIW rd="<<rd<<" rs1="<<rs1<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F001:
                {
                    shamt=bin_str.substr(7,5);
                    mnemonic=Mnemonic::SLLIW ;
                    sstream<<"F001 SLLIW rd="<<rd<<" rs1="<<rs1<<" shamt="<<shamt<<" "<<std::endl;
                    break;
                }
            case Func3::F010:
                {
                    sstream<<"F010 "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    sstream<<"F011 "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    sstream<<"F100 "<<std::endl;
                    break;
                }
            case Func3::F101:
                {
                    sstream<<"F101 ";
                    shamt=bin_str.substr(7,5);
                    if(f7_str == "0b0000000") { mnemonic=Mnemonic::SRLIW ; sstream<<" SRLIW "<<std::endl;}
                    if(f7_str == "0b0100000") { mnemonic=Mnemonic::SRAIW ; sstream<<" SRAIW "<<std::endl;}
                    sstream<<" rd="<<rd<<" rs1="<<rs1<<" shamt="<<shamt<<" "<<std::endl;
                    break;
                }
            case Func3::F110:
                {
                    sstream<<"F110 "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    sstream<<"F111 "<<std::endl;
                    break;
                }
        
            default:
                break;
        }

        itypeInstruction.rd=rd;
        itypeInstruction.f3=f3_str;
        itypeInstruction.rs1=rs1;
        itypeInstruction.imm12=imm12;
        itypeInstruction.shamt=shamt;
        itypeInstruction.mnemonic=mnemonic;

}

void Decoder::f3_S(const std::string& bin_str, StypeInstruction& stypeInstruction){
        std::string f3_str = "0b" + bin_str.substr(17,3);
        
        std::string rs1 = bin_str.substr(12,5);
        std::string rs2 =bin_str.substr(7,5);
        std::string imm12 = bin_str.substr(20,5)+bin_str.substr(0,7);
        
        Mnemonic mnemonic;
        
        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    mnemonic=Mnemonic::SB ;
                    sstream<<"F000 SB rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F001:
                {
                    mnemonic=Mnemonic::SH ;
                    sstream<<"F001 SH rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F010:
                {
                    mnemonic=Mnemonic::SW ;
                    sstream<<"F010 SW rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    mnemonic=Mnemonic::SD ;
                    sstream<<"F011 SD rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    sstream<<"F100 "<<std::endl;
                    break;
                }
            case Func3::F101:
                {
                    sstream<<"F101 "<<std::endl;
                    break;
                }
            case Func3::F110:
                {
                    sstream<<"F110 "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    sstream<<"F111 "<<std::endl;
                    break;
                }
        
            default:
                break;
        }

        stypeInstruction.f3=f3_str;
        stypeInstruction.rs1=rs1;
        stypeInstruction.rs2=rs2;
        stypeInstruction.imm12=imm12;
        stypeInstruction.mnemonic= mnemonic;

}

void Decoder::f3_B(const std::string& bin_str, BtypeInstruction& btypeInstruction){
        std::string f3_str = "0b" + bin_str.substr(17,3);
        
        std::string rs1 = bin_str.substr(12,5);
        std::string rs2 =bin_str.substr(7,5);
        std::string imm12 = bin_str.substr(20,4)+bin_str.substr(1,6)+bin_str.substr(24,1)+bin_str.substr(0,1);
        
        Mnemonic mnemonic;

        Func3 f3 = CodeToFunc3[f3_str];
        switch (f3)
        {
            case Func3::F000:
                {
                    mnemonic=Mnemonic::BEQ ;
                    sstream<<"F000 BEQ rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F001:
                {
                    mnemonic=Mnemonic::BNE ;
                    sstream<<"F001 BNE rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F010:
                {
                    sstream<<"F010 "<<std::endl;
                    break;
                }
            case Func3::F011:
                {
                    sstream<<"F011 "<<std::endl;
                    break;
                }
            case Func3::F100:
                {
                    mnemonic=Mnemonic::BLT ;
                    sstream<<"F100 BLT rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F101:
                {
                    mnemonic=Mnemonic::BGE ;
                    sstream<<"F101 BGE rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    
                    break;
                }
            case Func3::F110:
                {
                    mnemonic=Mnemonic::BLTU ;
                    sstream<<"F110 BLTU rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
            case Func3::F111:
                {
                    mnemonic=Mnemonic::BGEU ;
                    sstream<<"F111 BGEU rs1="<<rs1<<" rs2="<<rs2<<" imm12="<<imm12<<" "<<std::endl;
                    break;
                }
        
            default:
                break;
        }
        
        btypeInstruction.f3=f3_str;
        btypeInstruction.rs1=rs1;
        btypeInstruction.imm12=imm12;
        btypeInstruction.mnemonic=mnemonic;

}

std::string Decoder::to_bit_string(const std::string& ins){
    std::stringstream sstream_1{};
    sstream_1<<std::hex<<ins;
    unsigned long unum;   
    sstream_1>>unum;
    std::bitset<32> binstr(unum);
   
    auto bin_str = binstr.to_string();
    return std::move (bin_str);
}

std::vector<std::unique_ptr<Instruction>>& Decoder::get_decoded_instruction(){
    return decoded_inst_vec; // return reference
}