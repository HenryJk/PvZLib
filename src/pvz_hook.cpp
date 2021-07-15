#include "pvz_hook.h"

#include <memoryapi.h>
#include <processthreadsapi.h>
#include <unordered_map>
#include <vector>
#include <winnt.h>

namespace {
    std::unordered_map<uintptr_t, std::vector<uint8_t>> original_codes;
    std::vector<uint8_t *> trampolines;
    void SaveOriginalCode(uint8_t *address, uint32_t length) {
        for (int i = 0; i < length; i++) original_codes[(uintptr_t) address].push_back(address[i]);
    }
} // namespace

void pvz::RegisterOnTickHook(void (*handler)()) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0xE8; // call handler
    (uintptr_t &) trampoline[2] = (uintptr_t) handler - ((uintptr_t) trampoline + 6);
    trampoline[6]               = 0x61; // popad;
    memcpy(&trampoline[7], (void *) ON_TICK_INJECTION_ADDRESS, 5);
    trampoline[12]               = 0xE9; // jmp ON_TICK_INJECTION_ADDRESS+5;
    (uintptr_t &) trampoline[13] = (ON_TICK_INJECTION_ADDRESS + 5) - ((uintptr_t) trampoline + 17);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline;
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_TICK_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_TICK_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_TICK_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::RegisterOnZombieCreatedHook(void (*handler)(pvz::Zombie *)) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0xFF; // push [ebp+0x08];
    trampoline[2]               = 0x75;
    trampoline[3]               = 0x08;
    trampoline[4]               = 0xE8; // call handler;
    (uintptr_t &) trampoline[5] = (uintptr_t) handler - ((uintptr_t) trampoline + 9);
    trampoline[9]               = 0x58; // pop eax;
    trampoline[10]              = 0x61; // popad;
    memcpy(&trampoline[11], (void *) ON_ZOMBIE_CREATED_INJECTION_ADDRESS, 6);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_ZOMBIE_CREATED_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_ZOMBIE_CREATED_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_ZOMBIE_CREATED_INJECTION_ADDRESS, patch, sizeof(patch),
                       nullptr);
}

void pvz::RegisterOnPlantBittenHook(void (*handler)(Plant *, Zombie *)) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0x56; // push esi;
    trampoline[2]               = 0xE8; // call handler;
    (uintptr_t &) trampoline[3] = (uintptr_t) handler - ((uintptr_t) trampoline + 7);
    trampoline[7]               = 0x5E; // pop esi;
    trampoline[8]               = 0x61; // popad;
    memcpy(&trampoline[9], (void *) ON_PLANT_BITTEN_INJECTION_ADDRESS, 6);
    trampoline[15]               = 0xE9; // jmp ON_PLANT_BITTEN_INJECTION_ADDRESS + 6;
    (uintptr_t &) trampoline[16] = (ON_PLANT_BITTEN_INJECTION_ADDRESS + 6) - ((uintptr_t) trampoline + 20);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_PLANT_BITTEN_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_PLANT_BITTEN_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_PLANT_BITTEN_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::RegisterOnPlantCrushedHook(void (*handler)(Plant *, Zombie *)) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0x57; // push edi;
    trampoline[2]               = 0x51; // push ecx;
    trampoline[3]               = 0xE8; // call handler;
    (uintptr_t &) trampoline[4] = (uintptr_t) handler - ((uintptr_t) trampoline + 8);
    trampoline[8]               = 0x58; // pop eax;
    trampoline[9]               = 0x58; // pop eax;
    trampoline[10]              = 0x61; // popad;
    memcpy(&trampoline[11], (void *) ON_PLANT_CRUSHED_INJECTION_ADDRESS, 6);
    trampoline[17]               = 0xE9; // jmp ON_PLANT_SQUASHED_INJECTION_ADDRESS + 6;
    (uintptr_t &) trampoline[18] = (ON_PLANT_CRUSHED_INJECTION_ADDRESS + 6) - ((uintptr_t) trampoline + 22);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_PLANT_CRUSHED_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_PLANT_CRUSHED_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_PLANT_CRUSHED_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::RegisterOnSpikerockDamaged(void (*handler)(Plant *, Zombie *)) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0x53; // push ebx;
    trampoline[2]               = 0x56; // push esi;
    trampoline[3]               = 0xE8; // call handler;
    (uintptr_t &) trampoline[4] = (uintptr_t) handler - ((uintptr_t) trampoline + 8);
    trampoline[8]               = 0x58; // pop eax;
    trampoline[9]               = 0x58; // pop eax;
    trampoline[10]              = 0x61; // popad;
    memcpy(&trampoline[11], (void *) ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS, 9);
    trampoline[20]               = 0xE9; // jmp ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS + 9;
    (uintptr_t &) trampoline[21] = (ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS + 9) - ((uintptr_t) trampoline + 25);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_SPIKEROCK_DAMAGED_INJECTION_ADDRESS, patch, sizeof(patch),
                       nullptr);
}

void pvz::RegisterOnSpikeplantRanOver(void (*handler)(Plant *, Zombie *)) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0x53; // push ebx;
    trampoline[2]               = 0x55; // push ebp;
    trampoline[3]               = 0xE8; // call handler;
    (uintptr_t &) trampoline[4] = (uintptr_t) handler - ((uintptr_t) trampoline + 8);
    trampoline[8]               = 0x58; // pop eax;
    trampoline[9]               = 0x58; // pop eax;
    trampoline[10]              = 0x61; // popad;
    memcpy(&trampoline[11], (void *) ON_SPIKEPLANT_RAN_OVER_INJECTION_ADDRESS, 9);
    trampoline[20]               = 0xE9; // jmp ON_SPIKEPLANT_RAN_OVER_INJECTION_ADDRESS + 9;
    (uintptr_t &) trampoline[21] = (ON_SPIKEPLANT_RAN_OVER_INJECTION_ADDRESS + 9) - ((uintptr_t) trampoline + 25);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_SPIKEPLANT_RAN_OVER_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_SPIKEPLANT_RAN_OVER_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_SPIKEPLANT_RAN_OVER_INJECTION_ADDRESS, patch, sizeof(patch),
                       nullptr);
}

void pvz::RegisterOnProjectileCollideHook(void (*handler)(Projectile *, Zombie *)) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0x50; // push eax;
    trampoline[2]               = 0x51; // push ecx;
    trampoline[3]               = 0xE8; // call handler;
    (uintptr_t &) trampoline[4] = (uintptr_t) handler - ((uintptr_t) trampoline + 8);
    trampoline[8]               = 0x59; // pop ecx;
    trampoline[9]               = 0x58; // pop eax;
    trampoline[10]              = 0x61; // popad;
    memcpy(&trampoline[11], (void *) ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS, 5);
    trampoline[16]               = 0xE9; // jmp ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS + 5;
    (uintptr_t &) trampoline[17] = (ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS + 5) - ((uintptr_t) trampoline + 21);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS, patch, sizeof(patch),
                       nullptr);
}

void pvz::RegisterOnBasketballCollideHook(void (*handler)(Projectile *, Plant *)) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0x56; // push esi;
    trampoline[2]               = 0x55; // push ebp;
    trampoline[3]               = 0xE8; // call handler;
    (uintptr_t &) trampoline[4] = (uintptr_t) handler - ((uintptr_t) trampoline + 8);
    trampoline[8]               = 0x5D; // pop ebp;
    trampoline[9]               = 0x5E; // pop esi;
    trampoline[10]              = 0x61; // popad;
    memcpy(&trampoline[11], (void *) ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS, 6);
    trampoline[17]               = 0xE9; // jmp ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS + 6;
    (uintptr_t &) trampoline[18] = (ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS + 6) - ((uintptr_t) trampoline + 22);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_BASKETBALL_COLLIDE_INJECTION_ADDRESS, patch, sizeof(patch),
                       nullptr);
}

void pvz::RegisterOnFrameRenderedHook(void (*handler)(IDirect3DDevice7 *)) {
    auto trampoline = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    trampolines.push_back(trampoline);
    trampoline[0]               = 0x60; // pushad;
    trampoline[1]               = 0x50; // push eax;
    trampoline[2]               = 0xE8; // call handler;
    (uintptr_t &) trampoline[3] = (uintptr_t) handler - ((uintptr_t) trampoline + 7);
    trampoline[7]               = 0x58; // pop eax;
    trampoline[8]               = 0x61; // popad;
    memcpy(&trampoline[9], (void *) ON_FRAME_RENDERED_INJECTION_ADDRESS, 5);
    trampoline[14]               = 0xE9; // jmp ON_FRAME_RENDERED_INJECTION_ADDRESS + 5;
    (uintptr_t &) trampoline[15] = (ON_FRAME_RENDERED_INJECTION_ADDRESS + 5) - ((uintptr_t) trampoline + 19);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp trampoline
    (uintptr_t &) patch[1] = (uintptr_t) trampoline - (ON_FRAME_RENDERED_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_FRAME_RENDERED_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) ON_FRAME_RENDERED_INJECTION_ADDRESS, patch, sizeof(patch),
                       nullptr);
}

void pvz::DisableAllHooks() {
    for (auto &[address, code] : original_codes)
        WriteProcessMemory(GetCurrentProcess(), (void *) address, &code[0], code.size(), nullptr);
    for (auto &trampoline : trampolines) VirtualFree(trampoline, 0, MEM_RELEASE);
}
