//
// Created by shakil on 5/11/23.
//
#include "Instruction.hpp"
#include <utility>

RtypeInstruction::RtypeInstruction(InstType _instType, std::string _opcode) : mnemonic(Mnemonic::NOT_SET), Instruction(_instType,std::move(_opcode)){}

ItypeInstruction::ItypeInstruction(InstType _instType, std::string _opcode) : mnemonic(Mnemonic::NOT_SET), Instruction(_instType,std::move(_opcode)){}

StypeInstruction::StypeInstruction(InstType _instType, std::string _opcode) : mnemonic(Mnemonic::NOT_SET), Instruction(_instType,std::move(_opcode)){}

BtypeInstruction::BtypeInstruction(InstType _instType, std::string _opcode) : mnemonic(Mnemonic::NOT_SET), Instruction(_instType,std::move(_opcode)){}

UtypeInstruction::UtypeInstruction(InstType _instType, std::string _opcode) : mnemonic(Mnemonic::NOT_SET), Instruction(_instType,std::move(_opcode)){}

JtypeInstruction::JtypeInstruction(InstType _instType, std::string _opcode) : mnemonic(Mnemonic::NOT_SET), Instruction(_instType,std::move(_opcode)){}