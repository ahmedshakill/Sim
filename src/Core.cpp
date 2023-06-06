//
// Created by shakil on 5/17/23.
//

#include "Decoder.hpp"
#include "Executor.hpp"
#include "Core.hpp"

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

void Core::store_in_memory(std::string& line, int pos){
    std::string substr;
    size_t * temp=nullptr;
    for(int offset=0;offset<4;offset++){
        substr = line.substr(0,2);
        line.erase(0,2);
        line.shrink_to_fit();
        unsigned long long ull_from_str = stoull(substr, temp, 16);
        memory[pos+offset]=ull_from_str;
    }
    /*
     *
     * at[ 0     1     2    3]
     *    00    40    09   13
     *
     * */

}

std::vector<std::string> Core::loadelf(const std::string& text_elf){
    std::ifstream file_handle(text_elf,std::ios_base::binary | std::ios::in);
    std::string line;
    //TODO
    //Extract start location of the program in memory from elf
    //Store in memory starting from that location
    int pc=0;
    std::vector<std::string> insts;
    while(getline(file_handle,line)){
        insts.push_back(line);
        store_in_memory(line,start+pc);
        pc=pc+4;
    }
    // start indicates location of 1st instruction in memory
    // end indicates location of last instruction in memory
    end=start+pc;
    Executor::pc=start;
    return  std::move(insts);
}

void Core::store_elf_memory() {
    std::vector<std::string> ins_buffer = loadelf("adder_od.txt");
}

unsigned long long Core::load_instruction() {
    // read 4 bytes and return an uint32;
    uint32_t ins_uint32_rep = memory[Executor::pc]<<24 ;
    ins_uint32_rep|= memory[Executor::pc+1] <<16 ;
    ins_uint32_rep|= memory[Executor::pc+2] <<8 ;
    ins_uint32_rep|= memory[Executor::pc+3] ;
//    std::cout<<std::hex<<ins_uint32_rep<<std::endl;

    return fetched_ins=ins_uint32_rep;
}

void Core::decode() {
   std::bitset<32> ins{fetched_ins};
   std::cout<<ins<<std::endl;
   decoded_instruction = {decoder.decode_instruction(ins.to_string())};

}

void Core::execute() {
    executor.execute(decoded_instruction);
    if(not executor.pc_modified){
        Executor::pc+=4;
    }else{
        executor.pc_modified=false;
    }
}

