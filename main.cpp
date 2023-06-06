#include "Decoder.hpp"
#include "Executor.hpp"
#include "Core.hpp"


int main(){
    Core core{};
    core.store_elf_memory();
    while(core.start+Executor::pc < core.end){
        core.load_instruction();
        core.decode();
        core.execute();

    }

    return 0;
}
