#pragma once

#include <memoryapi.h>
#include <processthreadsapi.h>

namespace pvz {
    class Trampoline {
    private:
        uint8_t *mCode;
        uint32_t mNext = 0;

    public:
        Trampoline();

        Trampoline &Pushad();
        Trampoline &Popad();
        Trampoline &AddCustom(uint8_t *instructions, uint32_t length);
        Trampoline &Jump(uintptr_t address);
        void Inject(uintptr_t injection_address) const;

        template<typename T>
        Trampoline &Push(T t) {
            mCode[mNext]                   = 0x68; // push
            (uintptr_t &) mCode[mNext + 1] = *(uintptr_t *) &t;
            mNext += 5;
            return *this;
        }

        template<typename T, typename... Args>
        Trampoline &Push(T t, Args... params) {
            Push(params...);
            mCode[mNext]                   = 0x68; // push
            (uintptr_t &) mCode[mNext + 1] = *(uintptr_t *) &t;
            mNext += 5;
            return *this;
        }

        template<typename F, typename... Args>
        Trampoline &Call(F function, Args... params) {
            if (function == nullptr) return *this;
            Push(params...);
            mCode[mNext]                   = 0xE8; // call
            (uintptr_t &) mCode[mNext + 1] = (uintptr_t) function - (uintptr_t) &mCode[mNext + 5];
            mCode[mNext + 5]               = 0x83; // add esp, 0x04 * nArgs
            mCode[mNext + 6]               = 0xC4;
            mCode[mNext + 7]               = 0x04 * (uint8_t) (sizeof...(Args));
            mNext += 8;
            return *this;
        }
    };
} // namespace pvz
