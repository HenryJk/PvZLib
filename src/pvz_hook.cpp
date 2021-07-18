#include "pvz_hook.h"

#include <memoryapi.h>
#include <processthreadsapi.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include <winnt.h>

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
    Trampoline()
            .AddCallHandler((uintptr_t) handler, 0)
            .AddCustomInstructions((uint8_t *) ON_TICK_INJECTION_ADDRESS, 5)
            .AddBackJump(ON_TICK_INJECTION_ADDRESS, 5)
            .Inject(ON_TICK_INJECTION_ADDRESS);
}

void pvz::RegisterOnZombieCreatedHook(void (*handler)(pvz::Zombie *)) {
    uint8_t push_args[] = {0x57}; // push edi;
    Trampoline()
            .AddCustomInstructions(push_args, sizeof(push_args))
            .AddCallHandler((uintptr_t) handler, 4)
            .AddCustomInstructions((uint8_t *) ON_ZOMBIE_CREATED_INJECTION_ADDRESS, 5)
            .AddBackJump(ON_ZOMBIE_CREATED_INJECTION_ADDRESS, 5)
            .Inject(ON_ZOMBIE_CREATED_INJECTION_ADDRESS);
}

void pvz::RegisterOnPlantBittenHook(void (*handler)(Plant *, Zombie *)) {
    uint8_t push_args[] = {0x55, 0x56}; // push ebp; push esi;
    Trampoline()
            .AddCustomInstructions(push_args, sizeof(push_args))
            .AddCallHandler((uintptr_t) handler, 8)
            .AddCustomInstructions((uint8_t *) ON_PLANT_BITTEN_INJECTION_ADDRESS, 6)
            .AddBackJump(ON_PLANT_BITTEN_INJECTION_ADDRESS, 6)
            .Inject(ON_PLANT_BITTEN_INJECTION_ADDRESS);
}

void pvz::RegisterOnPlantCrushedHook(void (*handler)(Plant *, Zombie *)) {
    uint8_t push_args[] = {0x57, 0x51}; // push edi; push ecx;
    Trampoline()
            .AddCustomInstructions(push_args, sizeof(push_args))
            .AddCallHandler((uintptr_t) handler, 8)
            .AddCustomInstructions((uint8_t *) ON_PLANT_CRUSHED_INJECTION_ADDRESS, 6)
            .AddBackJump(ON_PLANT_CRUSHED_INJECTION_ADDRESS, 6)
            .Inject(ON_PLANT_CRUSHED_INJECTION_ADDRESS);
}

void pvz::RegisterOnSpikerockDamaged(void (*handler)(Plant *, Zombie *)) {
    uint8_t push_args[] = {0x53, 0x56}; // push ebx; push esi;
    Trampoline()
            .AddCustomInstructions(push_args, sizeof(push_args))
            .AddCallHandler((uintptr_t) handler, 8)
            .AddCustomInstructions((uint8_t *) ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS, 9)
            .AddBackJump(ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS, 9)
            .Inject(ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS);
}

void pvz::RegisterOnSpikeweedRanOver(void (*handler)(Plant *, Zombie *)) {
    uint8_t push_args[] = {0x53, 0x55}; // push ebx; push ebp;

    uint8_t patched_code[5];
    memcpy(patched_code, (void *) ON_SPIKEWEED_RAN_OVER_INJECTION_ADDRESS, 5);
    (uintptr_t &) patched_code[1] += ON_SPIKEWEED_RAN_OVER_INJECTION_ADDRESS - (uintptr_t) patched_code;

    auto t = Trampoline()
                     .AddCustomInstructions(push_args, sizeof(push_args))
                     .AddCallHandler((uintptr_t) handler, 8)
                     .AddCustomInstructions((uint8_t *) ON_SPIKEWEED_RAN_OVER_INJECTION_ADDRESS, 5);
    (uintptr_t &) t.internal[t.next - 4] +=
            ON_SPIKEWEED_RAN_OVER_INJECTION_ADDRESS - ((uintptr_t) t.internal + t.next - 5);
    t.AddBackJump(ON_SPIKEWEED_RAN_OVER_INJECTION_ADDRESS, 5).Inject(ON_SPIKEWEED_RAN_OVER_INJECTION_ADDRESS);
}

void pvz::RegisterOnPlantBlasted(void (*handler)(Plant *, Zombie *)) {
    uint8_t push_args[] = {0xFF, 0x74, 0x24, 0x20, 0x56}; // push [esp+0x20]; push esi;
    Trampoline()
            .AddCustomInstructions(push_args, sizeof(push_args))
            .AddCallHandler((uintptr_t) handler, 8)
#if defined VERSION_1_0_0_1051_EN
            .AddCustomInstructions((uint8_t *) ON_PLANT_BLASTED_INJECTION_ADDRESS, 7)
            .AddBackJump(ON_PLANT_BLASTED_INJECTION_ADDRESS, 7)
#elif defined VERSION_1_2_0_1096_EN
            .AddCustomInstructions((uint8_t *) ON_PLANT_BLASTED_INJECTION_ADDRESS, 6)
            .AddBackJump(ON_PLANT_BLASTED_INJECTION_ADDRESS, 6)
#endif
            .Inject(ON_PLANT_BLASTED_INJECTION_ADDRESS);
}

void pvz::RegisterOnProjectileCollideHook(void (*handler)(Projectile *, Zombie *)) {
    uint8_t push_args[] = {0x50, 0x51}; // push eax; push ecx;
    Trampoline()
            .AddCustomInstructions(push_args, sizeof(push_args))
            .AddCallHandler((uintptr_t) handler, 8)
            .AddCustomInstructions((uint8_t *) ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS, 5)
            .AddBackJump(ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS, 5)
            .Inject(ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS);
}

void pvz::RegisterOnBasketballCollideHook(void (*handler)(Projectile *, Plant *)) {
    uint8_t push_args[] = {0x56, 0x55}; // push esi; push ebp;
    Trampoline()
            .AddCustomInstructions(push_args, sizeof(push_args))
            .AddCallHandler((uintptr_t) handler, 8)
            .AddCustomInstructions((uint8_t *) ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS, 6)
            .AddBackJump(ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS, 6)
            .Inject(ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS);
}

void pvz::RegisterOnFrameRenderedHook(void (*handler)(IDirect3DDevice7 *)) {
#if defined VERSION_1_0_0_1051_EN
    uint8_t push_args[] = {0x50}; // push eax;
#elif defined VERSION_1_2_0_1096_EN
    uint8_t push_args[] = {0x52}; // push edx;
#endif
    Trampoline()
            .AddCustomInstructions(push_args, sizeof(push_args))
            .AddCallHandler((uintptr_t) handler, 4)
            .AddCustomInstructions((uint8_t *) ON_FRAME_RENDERED_INJECTION_ADDRESS, 5)
            .AddBackJump(ON_FRAME_RENDERED_INJECTION_ADDRESS, 5)
            .Inject(ON_FRAME_RENDERED_INJECTION_ADDRESS);
}

void pvz::DisableAllHooks() {
    for (auto &[address, code] : original_codes)
        WriteProcessMemory(GetCurrentProcess(), (void *) address, &code[0], code.size(), nullptr);
    //    sleep(1);
    //    for (auto &trampoline : trampolines) VirtualFree(trampoline, 0, MEM_RELEASE);
}
