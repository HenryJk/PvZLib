#include "pvz.hpp"

namespace pvz {
    Trampoline::Trampoline() { mCode = (uint8_t *) VirtualAlloc(nullptr, 128, MEM_COMMIT, PAGE_EXECUTE_READWRITE); }

    Trampoline &Trampoline::Pushad() {
        mCode[mNext] = 0x60; // pushad;
        mNext        = mNext + 1;
        return *this;
    }

    Trampoline &Trampoline::Popad() {
        mCode[mNext] = 0x61; // popad;
        mNext        = mNext + 1;
        return *this;
    }

    Trampoline &Trampoline::AddCustom(uint8_t *instructions, uint32_t length) {
        memcpy(&mCode[mNext], instructions, length);
        mNext += length;
        return *this;
    }

    Trampoline &Trampoline::Jump(uintptr_t address) {
        mCode[mNext]                   = 0xE9; // jmp back_address;
        (uintptr_t &) mCode[mNext + 1] = address - (uintptr_t) &mCode[mNext + 5];
        mNext += 5;
        return *this;
    }

    void Trampoline::Inject(uintptr_t injection_address) const {
        uint8_t patch[5];
        patch[0]               = 0xE9; // jmp trampoline;
        (uintptr_t &) patch[1] = (uintptr_t) mCode - (injection_address + 5);
        WriteProcessMemory(GetCurrentProcess(), (void *) injection_address, patch, sizeof(patch), nullptr);
    }
} // namespace pvz
