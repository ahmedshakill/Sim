//
// Created by shakil on 5/17/23.
//

#ifndef SIM_MEMORY_HPP
#define SIM_MEMORY_HPP
#include <array>
#include <cstdint>

template<std::size_t N>
class Memory{
private:
    std::array<std::uint8_t,N> at{};

private:
    Memory() {
        at = {0};
    };
public:
    Memory(const Memory&)=delete;
    Memory(Memory&&)=delete;
    Memory& operator=(const Memory&)=delete;
    Memory& operator=(Memory&&)=delete;

    static Memory& get_instance(){
        static Memory instance;
        return instance;
    }
public:

    std::uint8_t operator[] (int pos) const {
        return at[pos];
    }
    std::uint8_t& operator[](int pos){
        return at[pos];
    }
};

#endif //SIM_MEMORY_HPP
