//
// Created by shakil on 5/17/23.
//

#ifndef SIM_CORE_HPP
#define SIM_CORE_HPP
#include <array>
#include <cstdint>
#include "Memory.hpp"

#define MEMOERY_SIZE 2097152

class Core {

public:
    Memory<MEMOERY_SIZE>& memory=Memory<MEMOERY_SIZE>::get_instance(); //Memory of size 2 MegaByte
//    std::array<std::int32_t,32> reg_file{};
//    std::int32_t pc{};


    void decode();

    void execute();

    int start;
    int end;
public:
    Core() : /*reg_file({0}), pc{0},*/ fetched_ins{0}, start{0}, end{0} {  }

    void store_elf_memory();
    std::vector<std::string> loadelf(const std::string& text_elf);
    void store_in_memory(std::string&,int);

    unsigned long long  load_instruction();

    Executor executor;
private:
    unsigned long long fetched_ins;
    Decoder decoder;
    std::unique_ptr<Instruction> decoded_instruction;

};


#endif //SIM_CORE_HPP
