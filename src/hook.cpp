#include "hook.hpp"
#include "pvz_reference.hpp"

#include <cstdint>
#include <memoryapi.h>
#include <processthreadsapi.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include <winnt.h>

#include <bits/stdc++.h>
using namespace std;

namespace {
    std::unordered_map<uintptr_t, std::vector<uint8_t>> original_codes;
    std::vector<uint8_t *> trampolines;

    struct Trampoline {
        uint8_t *internal;
        uint32_t next;

        Trampoline() {
            internal = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
            trampolines.push_back(internal);
            internal[0] = 0x60; // pushad;
            next        = 1;
        }

        Trampoline &AddCustomInstructions(uint8_t *instructions, uint32_t length) {
            memcpy(&internal[next], instructions, length);
            next += length;
            return *this;
        }

        Trampoline &AddCallHandler(uintptr_t handler, uint8_t args_size) {
            internal[next]                   = 0xE8;
            (uintptr_t &) internal[next + 1] = handler - (uintptr_t) &internal[next + 5];
            internal[next + 5]               = 0x83; // add esp, arg_size
            internal[next + 6]               = 0xC4;
            internal[next + 7]               = args_size;
            internal[next + 8]               = 0x61; // popad;
            next += 9;
            return *this;
        }

        Trampoline &AddBackJump(uintptr_t injection_address, uint32_t code_length) {
            internal[next]                   = 0xE9; // jmp injection_address+code_length;
            (uintptr_t &) internal[next + 1] = injection_address + code_length - (uintptr_t) &internal[next + 5];
            next += 5;
            return *this;
        }

        void Inject(uintptr_t injection_address) {
            for (int i = 0; i < 5; i++) original_codes[injection_address].push_back(((uint8_t *) injection_address)[i]);
            uint8_t patch[5];
            patch[0]               = 0xE9; // jmp trampoline;
            (uintptr_t &) patch[1] = (uintptr_t) internal - (injection_address + 5);
            WriteProcessMemory(GetCurrentProcess(), (void *) injection_address, patch, sizeof(patch), nullptr);
        }
    };
} // namespace

void pvz::RegisterOnTickHook(void (*handler)()) {

    cout << "asfd" << endl;

    Trampoline()
            .AddCallHandler((uintptr_t) handler, 0)
            .AddCustomInstructions((uint8_t *) ON_TICK_INJECTION_ADDRESS, 5)
            .AddBackJump(ON_TICK_INJECTION_ADDRESS, 5)
            .Inject(ON_TICK_INJECTION_ADDRESS);
}
