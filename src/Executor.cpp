//
// Created by shakil on 5/10/23.
//
#include "Executor.hpp"

std::unordered_map<std::string,std::int64_t> Executor::Register::reg_file{
        {"00000",0},
        {"00001",0},
        {"00010",0},
        {"00011",0},
        {"00100",0},
        {"00101",0},
        {"00110",0},
        {"00111",0},
        {"01000",0},
        {"01001",0},
        {"01010",0},
        {"01011",0},
        {"01100",0},
        {"01101",0},
        {"01110",0},
        {"01111",0},
        {"10000",0},
        {"10001",0},
        {"10010",0},
        {"10011",0},
        {"10100",0},
        {"10101",0},
        {"10110",0},
        {"10111",0},
        {"11000",0},
        {"11001",0},
        {"11010",0},
        {"11011",0},
        {"11100",0},
        {"11101",0},
        {"11110",0},
        {"11111",0},
};

int Executor::Register::pc=0x00000000;

void Executor::execute(std::vector<std::unique_ptr<Instruction>> &decoded_inst_vec) {
    for(auto& inst : decoded_inst_vec){
        switch (inst->instType) {
            case InstType::RType:
            {
                handleRType(inst);
                break;
            }
            case InstType::RWType:
            {
                handleRWType(inst);
                break;
            }
            case InstType::IType0000011:
            {
                handleIType0000011(inst);
                break;
            }
            case InstType::IType0010011:
            {
                handleIType0010011(inst);
                break;
            }
            case InstType::IType1100111:
            {
                handleIType1100111(inst);
                break;
            }
            case InstType::IType1110011:
            {
                handleIType1110011(inst);
                break;
            }
            case InstType::IWType:
            {
                handleIWType(inst);
                break;
            }
            case InstType::SType:
            {
                handleSType(inst);
                break;
            }
            case InstType::BType:
            {
                handleBType(inst);
                break;
            }
            case InstType::UType0010111:
            {
                handleUType0010111(inst);
                break;
            }
            case InstType::UType0110111:
            {
                handleUType0110111(inst);
                break;
            }
            case InstType::JType :
            {
                handleJType(inst);
                break;
            }

        }
    }
}

void Executor::handleRType(std::unique_ptr<Instruction>& inst){

}
void Executor::handleRWType(std::unique_ptr<Instruction>& inst){

}
void Executor::handleIType0000011(std::unique_ptr<Instruction>& inst){

}
void Executor::handleIType0010011(std::unique_ptr<Instruction>& inst){
    auto i = reinterpret_cast<ItypeInstruction*>( inst.get());
    std::cout<<"imm12 "<< i->imm12<<" rs1 "<<i->rs1<<" rd "<<i->rd << std::endl;

    //TODO
    // convert imm12 to integer from string
    // get value from rs1 register and add it to (integer)imm12
    // store the result in rd

    std::bitset<12> imm12_bt(i->imm12);
    std::bitset<12> one12_bt("000000000001");
    std::bitset<12> imm12_positive;
    int imm12;
    if(imm12_bt[11]==1){        // handle negative number
        imm12_bt=imm12_bt.flip();
        bool carry=false;
        for(int id=0;id<12;id++){
            imm12_positive[id]=(imm12_bt[id]^one12_bt[id]) ^ carry;
            carry = (imm12_bt[id] && one12_bt[id])|| (imm12_bt[id] && carry)
                    || (one12_bt[id] && carry );
        }
        imm12=(-1)*imm12_positive.to_ullong();
    }
    else{
        imm12=imm12_bt.to_ullong();
    }
    Executor::Register::reg_file[i->rd]=Executor::Register::reg_file[i->rs1] + imm12 ;
    std::cout<<Executor::Register::reg_file[i->rd]<<std::endl;

}
void Executor::handleIType1100111(std::unique_ptr<Instruction>& inst){

}
void Executor::handleIType1110011(std::unique_ptr<Instruction>& inst){

}
void Executor::handleIWType(std::unique_ptr<Instruction>& inst){

}
void Executor::handleSType(std::unique_ptr<Instruction>& inst){

}
void Executor::handleBType(std::unique_ptr<Instruction>& inst){

}
void Executor::handleUType0010111(std::unique_ptr<Instruction>& inst){

}
void Executor::handleUType0110111(std::unique_ptr<Instruction>& inst){

}
void Executor::handleJType(std::unique_ptr<Instruction>& inst){

}