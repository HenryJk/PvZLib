#include "pvz_hook.h"

#include <memoryapi.h>
#include <processthreadsapi.h>
#include <unordered_map>
#include <vector>
#include <winnt.h>

namespace {
    std::unordered_map<uintptr_t, std::vector<uint8_t>> original_codes;
    std::vector<uint8_t *> hooks;
    void SaveOriginalCode(uint8_t *address, uint32_t length) {
        for (int i = 0; i < length; i++) original_codes[(uintptr_t) address].push_back(address[i]);
    }
} // namespace

void pvz::RegisterOnTickHook(void (*handler)(Game *)) {
    auto hook = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    hooks.push_back(hook);
    hook[0]               = 0x53; // push ebx;
    hook[1]               = 0xE8; // call [handler];
    (uintptr_t &) hook[2] = (uintptr_t) handler - ((uintptr_t) hook + 6);
    hook[6]               = 0x5B; // pop ebx;
    hook[7]               = 0xE8; // call [MAIN_LOOP_FUNC_ADDRESS];
    (uintptr_t &) hook[8] = MAIN_LOOP_FUNC_ADDRESS - ((uintptr_t) hook + 12);
    hook[12]              = 0xC3; // ret;

    uint8_t patch[5];
    patch[0]               = 0xE8; // call [hook]
    (uintptr_t &) patch[1] = (uintptr_t) hook - (MAIN_LOOP_CALL_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) MAIN_LOOP_CALL_ADDRESS, sizeof(patch));
    WriteProcessMemory(GetCurrentProcess(), (void *) MAIN_LOOP_CALL_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::RegisterOnZombieCreatedHook(void (*handler)(pvz::Zombie *)) {
    auto hook = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    hooks.push_back(hook);
    hook[0]               = 0x8B; // mov esp, ebp;
    hook[1]               = 0xE5;
    hook[2]               = 0x5D; // pop ebp;
    hook[3]               = 0x60; // pushad;
    hook[4]               = 0xFF; // push [esp+24];
    hook[5]               = 0x74;
    hook[6]               = 0x24;
    hook[7]               = 0x24;
    hook[8]               = 0xE8; // call [handler];
    (uintptr_t &) hook[9] = (uintptr_t) handler - ((uintptr_t) hook + 13);
    hook[13]              = 0x83; // add esp, 4;
    hook[14]              = 0xC4;
    hook[15]              = 0x04;
    hook[16]              = 0x61; // popad;
    hook[17]              = 0xC2; // retn 0x14;
    (uint16_t &) hook[18] = 0x14;

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp [hook]
    (uintptr_t &) patch[1] = (uintptr_t) hook - (ON_ZOMBIE_CREATED_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_ZOMBIE_CREATED_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(
            GetCurrentProcess(), (void *) ON_ZOMBIE_CREATED_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::RegisterOnProjectileCollideHook(void (*handler)(Projectile *, Zombie *)) {
    auto hook = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    hooks.push_back(hook);
    hook[0]                = 0x60; // pushad;
    hook[1]                = 0x50; // push eax;
    hook[2]                = 0x51; // push ecx;
    hook[3]                = 0xE8; // call handler;
    (uintptr_t &) hook[4]  = (uintptr_t) handler - ((uintptr_t) hook + 8);
    hook[8]                = 0x59; // pop ecx;
    hook[9]                = 0x58; // pop eax;
    hook[10]               = 0x61; // popad;
    hook[11]               = 0x83; // sub esp, 0x14;
    hook[12]               = 0xEC;
    hook[13]               = 0x14;
    hook[14]               = 0x53; // push ebx;
    hook[15]               = 0x55; // push ebp;
    hook[16]               = 0xE9; // jmp [ON_ZOMBIE_HIT_INJECTION_ADDRESS + 5];
    (uintptr_t &) hook[17] = (ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS + 5) - ((uintptr_t) hook + 21);

    uint8_t patch[5];
    patch[0]               = 0xE9; // jmp [hook]
    (uintptr_t &) patch[1] = (uintptr_t) hook - (ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS + 5);
    SaveOriginalCode((uint8_t *) ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS, sizeof(patch));
    WriteProcessMemory(
            GetCurrentProcess(), (void *) ON_PROJECTILE_COLLIDE_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::DisableAllHooks() {
    for (auto &[address, code] : original_codes)
        WriteProcessMemory(GetCurrentProcess(), (void *) address, &code[0], code.size(), nullptr);
    for (auto &hook : hooks) VirtualFree(hook, 0, MEM_RELEASE);
}
