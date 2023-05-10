#ifndef H_DECODE
#define H_DECODE

#include "Mnemonic.hpp"
#include "Instruction.hpp"
#include <sstream>
#include <unordered_map>
#include <vector>
#include <memory>

class Decoder{
public:
    Decoder();

private:

//    enum class InstType;
    enum class Func3;
    std::unordered_map<std::string, InstType> CodeToInstType;
    std::unordered_map<std::string, Func3> CodeToFunc3;

    std::vector<std::unique_ptr<Instruction>> decoded_inst_vec;

private:

    void f3_R(const std::string& bin_str, RtypeInstruction& rtypeInstruction);
    void f3_RW(const std::string& bin_str, RtypeInstruction& rtypeInstruction);
    void f3_IType0000011(const std::string& bin_str, ItypeInstruction& itypeInstruction);
    void f3_IType0010011(const std::string& bin_str, ItypeInstruction& itypeInstruction);
    void f3_IType1100111(const std::string& bin_str, ItypeInstruction& itypeInstruction);
    void f3_IType1110011(const std::string& bin_str, ItypeInstruction& itypeInstruction);
    void f3_IW(const std::string& bin_str, ItypeInstruction& itypeInstruction);
    void f3_S(const std::string& bin_str, StypeInstruction& stypeInstruction);
    void f3_B(const std::string& bin_str, BtypeInstruction& btypeInstruction);
    static std::string to_bit_string(const std::string& ins);
    std::unique_ptr<Instruction> decode_instruction(const std::string& bin_str);


public:
    std::stringstream sstream{} ;

public:
    void decode(const std::vector<std::string>& ins_buffer);
    std::vector<std::unique_ptr<Instruction>>& get_decoded_instruction();

};


#endif