#ifndef H_EXECUTOR
#define H_EXECUTOR

#include "Instruction.hpp"
#include <unordered_map>
#include <iostream>
#include <cstdint>
#include <vector>
#include <bitset>
#include <memory>

class Executor{

    class Register{
        private:
            Register()=default;
        public:
            Register(const Register&)=delete;
            Register(Register&&)=delete;
            Register& operator=(const Register&)=delete;
            Register& operator=(Register&&)=delete;

            static std::unordered_map<std::string,std::int64_t> reg_file;
            static int pc;

            static Register& get_instance(){
                static Register instance;
                return instance;
            }
    };

public:
    Register& reg=Register::get_instance();
    Executor()=default;
    void execute(std::vector<std::unique_ptr<Instruction>>& decoded_inst_vec);
    void handleRType(std::unique_ptr<Instruction>& inst);
    void handleRWType(std::unique_ptr<Instruction>& inst);
    void handleIType0000011(std::unique_ptr<Instruction>& inst);
    void handleIType0010011(std::unique_ptr<Instruction>& inst);
    void handleIType1100111(std::unique_ptr<Instruction>& inst);
    void handleIType1110011(std::unique_ptr<Instruction>& inst);
    void handleIWType(std::unique_ptr<Instruction>& inst);
    void handleSType(std::unique_ptr<Instruction>& inst);
    void handleBType(std::unique_ptr<Instruction>& inst);
    void handleUType0010111(std::unique_ptr<Instruction>& inst);
    void handleUType0110111(std::unique_ptr<Instruction>& inst);
    void handleJType(std::unique_ptr<Instruction>& inst);
private:

};


#endif