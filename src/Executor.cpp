//
// Created by shakil on 5/10/23.
//
#include "Executor.hpp"
#include "Instruction.hpp"
std::unordered_map<std::string,int> Executor::Register::reg_file{
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

int Executor::pc=0x00000000;

std::unordered_map<int,int> Executor::Memory={{0,0}};

void Executor::execute(std::unique_ptr<Instruction>& inst) {
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

void Executor::handleRType(std::unique_ptr<Instruction>& inst){
    auto rinst = reinterpret_cast<RtypeInstruction*> (inst.get());
    std::cout<<"rd "<<rinst->rd <<" rs1 "<<rinst->rs1 <<" rs2 "<<rinst->rs2<<std::endl;
    using Mnemonic= RtypeInstruction::Mnemonic ;
    switch(rinst->mnemonic){
        case Mnemonic::ADD  :
        {
            std::cout<<"before ADD  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            Executor::Register::reg_file[rinst->rd] = Executor::Register::reg_file[rinst->rs1] + Executor::Register::reg_file[rinst->rs2];
            std::cout<<"after ADD  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::SUB:
        {
            std::cout<<"before SUB  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            Executor::Register::reg_file[rinst->rd] = Executor::Register::reg_file[rinst->rs1] - Executor::Register::reg_file[rinst->rs2];
            std::cout<<"after SUB  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::AND:
        {
            std::cout<<"before AND  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            Executor::Register::reg_file[rinst->rd] = Executor::Register::reg_file[rinst->rs1] & Executor::Register::reg_file[rinst->rs2];
            std::cout<<"after AND  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::OR:
        {
            std::cout<<"before OR  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            Executor::Register::reg_file[rinst->rd] = Executor::Register::reg_file[rinst->rs1] | Executor::Register::reg_file[rinst->rs2];
            std::cout<<"after OR  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::XOR:
        {
            std::cout<<"before XOR  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            Executor::Register::reg_file[rinst->rd] = Executor::Register::reg_file[rinst->rs1] ^ Executor::Register::reg_file[rinst->rs2];
            std::cout<<"after XOR  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::SLL:
        {
            std::cout<<"before SLL  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            std::bitset<32> bt_rs1 (Executor::Register::reg_file[rinst->rs1]);
            bt_rs1<<= Executor::Register::reg_file[rinst->rs2];
            Executor::Register::reg_file[rinst->rd] = bt_rs1.to_ulong();
            std::cout<<"after SLL  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::SRL:
        {
            std::cout<<"before SRL  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            std::bitset<32> bt_rs1 (Executor::Register::reg_file[rinst->rs1]);
            bt_rs1>>= Executor::Register::reg_file[rinst->rs2];
            Executor::Register::reg_file[rinst->rd] = bt_rs1.to_ulong();
            std::cout<<"after SRL  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::SRA:
        {
            std::cout<<"before SRA  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            std::bitset<32> bt_rs1 (Executor::Register::reg_file[rinst->rs1]);
            std::cout<<"bt_rs1 before sign extended shift "<<bt_rs1<<std::endl;
            bt_rs1[31]==1 ? bt_rs1 = ~( (~bt_rs1)>>= Executor::Register::reg_file[rinst->rs2])  :  bt_rs1>>= Executor::Register::reg_file[rinst->rs2]  ;
            std::cout<<"bt_rs1 after sign extended shift "<<bt_rs1<<std::endl;
            Executor::Register::reg_file[rinst->rd] = bt_rs1.to_ulong();
            std::cout<<"after SRA  rd="<<Executor::Register::reg_file[rinst->rd]<<std::endl;
            break;
        }


    }
}
void Executor::handleRWType(std::unique_ptr<Instruction>& inst){

}
void Executor::handleIType0000011(std::unique_ptr<Instruction>& inst){
    auto iinst = reinterpret_cast<ItypeInstruction*>( inst.get());
    std::cout<<"imm12 "<< iinst->imm12<<" rs1 "<<iinst->rs1<<" rd "<<iinst->rd << std::endl;
    using Mnemonic= ItypeInstruction::Mnemonic ;
    switch(iinst->mnemonic){
        case Mnemonic::LW:
        {
            int imm12 = string_to_integer<12>(iinst->imm12);        //get integer value of the 12 digit binary string
            Executor::Register::reg_file[iinst->rd]=Executor::Memory[ Executor::Register::reg_file[iinst->rs1] + imm12 ];
            std::cout<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            break;
        }
    }
}
void Executor::handleIType0010011(std::unique_ptr<Instruction>& inst){
    auto iinst = reinterpret_cast<ItypeInstruction*>( inst.get());
    std::cout<<"imm12 "<< iinst->imm12<<" rs1 "<<iinst->rs1<<" rd "<<iinst->rd << std::endl;
    using Mnemonic= ItypeInstruction::Mnemonic ;
    switch(iinst->mnemonic){
        case Mnemonic::ADDI:
        {
            //TODO
            // convert imm12 to integer from string
            // get value from rs1 register and add it to (integer)imm12
            // store the result in rd

            int imm12 = string_to_integer<12>(iinst->imm12);        //get integer value of the 12 digit binary string
            Executor::Register::reg_file[iinst->rd]=Executor::Register::reg_file[iinst->rs1] + imm12 ;
            std::cout<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::XORI:
        {
            int imm12 = string_to_integer<12>(iinst->imm12);        //get integer value of the 12 digit binary string
            Executor::Register::reg_file[iinst->rd]=Executor::Register::reg_file[iinst->rs1] ^ imm12 ;
            std::cout<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::ORI:
        {
            int imm12 = string_to_integer<12>(iinst->imm12);        //get integer value of the 12 digit binary string
            Executor::Register::reg_file[iinst->rd]=Executor::Register::reg_file[iinst->rs1] | imm12 ;
            std::cout<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::ANDI:
        {
            int imm12 = string_to_integer<12>(iinst->imm12);        //get integer value of the 12 digit binary string
            Executor::Register::reg_file[iinst->rd]=Executor::Register::reg_file[iinst->rs1] & imm12 ;
            std::cout<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::SLLI:
        {
            std::cout<<"before SLLI  rd="<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            std::bitset<32> bt_rs1 (Executor::Register::reg_file[iinst->rs1]);
            int shamt = string_to_integer<5>(iinst->shamt);
            bt_rs1<<= shamt;
            Executor::Register::reg_file[iinst->rd] = bt_rs1.to_ulong();
            std::cout<<"after SLLI  rd="<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::SRLI:
        {
            std::cout<<"before SLLI  rd="<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            std::bitset<32> bt_rs1 (Executor::Register::reg_file[iinst->rs1]);
            int shamt = string_to_integer<5>(iinst->shamt);
            bt_rs1>>= shamt;
            Executor::Register::reg_file[iinst->rd] = bt_rs1.to_ulong();
            std::cout<<"after SLLI  rd="<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            break;
        }
        case Mnemonic::SRAI:
        {
            std::cout<<"before SRAI  rd="<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            int shamt = string_to_integer<5>(iinst->shamt);
            Executor::Register::reg_file[iinst->rd] = Executor::Register::reg_file[iinst->rs1] >>shamt;
            std::cout<<"after SRAI  rd="<<Executor::Register::reg_file[iinst->rd]<<std::endl;
            break;
        }
    }


}
void Executor::handleIType1100111(std::unique_ptr<Instruction>& inst){

}
void Executor::handleIType1110011(std::unique_ptr<Instruction>& inst){

}
void Executor::handleIWType(std::unique_ptr<Instruction>& inst){

}
void Executor::handleSType(std::unique_ptr<Instruction>& inst){
    auto sinst = reinterpret_cast<StypeInstruction*>( inst.get());
    std::cout<<sinst->bin_str<<std::endl;
    std::cout<<"imm12 "<< sinst->imm12<<" rs1 "<<sinst->rs1<<" rs2 "<<sinst->rs2 << std::endl;

    int imm12 = string_to_integer<12>(sinst->imm12);        //get integer value of the 12 digit binary string
    using Mnemonic= StypeInstruction::Mnemonic ;
    switch(sinst->mnemonic){
        case Mnemonic::SD:
        {
            std::cout<<"before sd "<<Executor::Memory[Executor::Register::reg_file[sinst->rs1] + imm12]<<std::endl;
            Executor::Memory[Executor::Register::reg_file[sinst->rs1] + imm12] = Executor::Register::reg_file[sinst->rs2];
            std::cout<<"after sd "<<Executor::Memory[Executor::Register::reg_file[sinst->rs1] + imm12]<<std::endl;
            break;
        }
        case Mnemonic::SW:
        {
            std::cout<<"before sw "<<Executor::Memory[Executor::Register::reg_file[sinst->rs1] + imm12]<<std::endl;
            Executor::Memory[Executor::Register::reg_file[sinst->rs1] + imm12] = Executor::Register::reg_file[sinst->rs2]; //TODO take lower 32bits
            std::cout<<"after sw "<<Executor::Memory[Executor::Register::reg_file[sinst->rs1] + imm12]<<std::endl;
            break;
        }
    }
}
void Executor::handleBType(std::unique_ptr<Instruction>& inst){
    auto binst = reinterpret_cast<BtypeInstruction*>( inst.get());
    std::cout<<"btype imm13 "<<binst->imm13<<std::endl;
    int imm13= string_to_integer<13>(binst->imm13);
    std::cout<<"btype imm13 "<<imm13<<std::endl;
    std::cout<<"rs1 "<<binst->rs1 << " rs2 "<< binst->rs2 << std::endl;
    std::cout<<"rs1 "<<Executor::Register::reg_file[binst->rs1]<<" rs2 "<<Executor::Register::reg_file[binst->rs2]<<std::endl;
    if(Executor::Register::reg_file[binst->rs2]==Executor::Register::reg_file[binst->rs1]) {
        Executor::pc+=imm13;
        pc_modified=true;
    }

}
void Executor::handleUType0010111(std::unique_ptr<Instruction>& inst){

}
void Executor::handleUType0110111(std::unique_ptr<Instruction>& inst){

}
void Executor::handleJType(std::unique_ptr<Instruction>& inst){

}

template<size_t N>
int Executor::string_to_integer(const std::string& immediate){
    std::bitset<N> immN_bt(immediate);
    std::bitset<N> oneN_bt(1);
    std::bitset<N> immN_positive;
    int immN;
    if(immN_bt[N-1]==1){        // handle negative number
        immN_bt=immN_bt.flip();
        bool carry=false;
        for(int id=0;id<N;id++){
            immN_positive[id]=(immN_bt[id]^oneN_bt[id]) ^ carry;
            carry = (immN_bt[id] && oneN_bt[id])|| (immN_bt[id] && carry)
                    || (oneN_bt[id] && carry );
        }
        immN=(-1)*immN_positive.to_ullong();
    }
    else{
        immN=immN_bt.to_ullong();
    }
    return  immN;
}