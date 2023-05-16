#include "Decoder.hpp"
#include "Executor.hpp"

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

std::vector<std::string> loadelf(std::string text_elf){
    std::ifstream file_handle(text_elf,std::ios_base::binary | std::ios::in);
    std::string line;
    
    std::vector<std::string> insts;
    while(getline(file_handle,line)){
        insts.push_back(line);
    }
    
   return  std::move(insts);
}

void ttest(){
    //jal instruction
    auto bin_str{"10000101010100100000000001101111"};
    std::vector<std::string> ins_buffer;
    ins_buffer.push_back(bin_str);
    Decoder decoder{};
    decoder.sstream << bin_str << std::endl;
    decoder.decode(ins_buffer);
}

int main(){
    std::vector<std::string> ins_buffer = loadelf("adder_od.txt");
    
    Decoder decoder{};
    decoder.decode(ins_buffer);
    
    std::vector<std::unique_ptr<Instruction>>& decoded_inst_vec = decoder.get_decoded_instruction();
    std::cout<<decoder.sstream.str()<<std::endl;
//    Executor executor{};
//    executor.execute(decoded_inst_vec);

    return 0;
}
