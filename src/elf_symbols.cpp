#include "esp_elf.h"
#include "elf_symbols.h"

/*
This file is required for the api between the firmware and the user program to work. 
It also adds the C++ compatibility layer. 

If you can't tell I needed to use some chatgpt for this. I didn't even know SYMBOLS existed...

What I do know is that if you get an error that looks like: E (568) ELF: Can't find symbol _ZdlPvj
Then you should copy the part after symbol: _ZdlPvj
Add in a new line that says: extern "C" void elf_throw_IDK_2_error(const char*) asm("_ZdlPvj"); The function can be any name
Then add it into custom_symbols[] as seen below:
{
    "_ZdlPvj",
    reinterpret_cast<const void*>(&elf_throw_IDK_2_error)
},
Then upload and check the debug again...
*/

extern "C" void* os_api;


//C++ Compatibility layer. 
extern "C" void elf_throw_length_error(const char*) asm("_ZSt20__throw_length_errorPKc");
extern "C" void elf_throw_bad_allocv_error(const char*) asm("_ZSt17__throw_bad_allocv");
extern "C" void elf_throw_IDK_error(const char*) asm("_Znwj");
extern "C" void elf_throw_IDK_2_error(const char*) asm("_ZdlPvj");
extern "C" void elf_throw_logic_error(const char*) asm("_ZSt19__throw_logic_errorPKc");
extern "C" void elf_throw_xQueueGenericSend_error(const char*) asm("xQueueGenericSend");
extern "C" void elf_throw_memcpy_error(const char*) asm("memcpy");
extern "C" void elf_throw_strlen_error(const char*) asm("strlen");

static const struct esp_elfsym custom_symbols[] = {
    { "os_api", &os_api },
    {
        "_ZSt20__throw_length_errorPKc",
        reinterpret_cast<const void*>(&elf_throw_length_error)
    },
    {
        "_ZSt17__throw_bad_allocv",
        reinterpret_cast<const void*>(&elf_throw_bad_allocv_error)
    },
    {
        "_Znwj",
        reinterpret_cast<const void*>(&elf_throw_IDK_error)
    },
    {
        "_ZdlPvj",
        reinterpret_cast<const void*>(&elf_throw_IDK_2_error)
    },
    {
        "_ZSt19__throw_logic_errorPKc",
        reinterpret_cast<const void*>(&elf_throw_logic_error)
    },
    {
        "xQueueGenericSend",
        reinterpret_cast<const void*>(&elf_throw_xQueueGenericSend_error)
    },
    {
        "memcpy",
        reinterpret_cast<const void*>(&elf_throw_memcpy_error)
    },
    {
        "strlen",
        reinterpret_cast<const void*>(&elf_throw_strlen_error)
    },
    { nullptr, 0 }
};

void register_custom_elf_symbols() {
    esp_elf_register_symbol(custom_symbols);
}