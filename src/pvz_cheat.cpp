#include "pvz_cheat.h"

#include "pvz_reference.h"

#include <cstdint>
#include <memoryapi.h>
#include <processthreadsapi.h>

void pvz::EnableSpeedUnlock() {
    uint8_t patch[] = SPEED_UNLOCK_CHEAT_CODE;
    WriteProcessMemory(GetCurrentProcess(), (void *) SPEED_UNLOCK_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::DisableSpeedUnlock() {
    uint8_t patch[] = SPEED_UNLOCK_ORIGINAL_CODE;
    WriteProcessMemory(GetCurrentProcess(), (void *) SPEED_UNLOCK_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::EnableAutoCollect() {
    uint8_t patch[] = AUTO_COLLECT_CHEAT_CODE;
    WriteProcessMemory(GetCurrentProcess(), (void *) AUTO_COLLECT_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::DisableAutoCollect() {
    uint8_t patch[] = AUTO_COLLECT_ORIGINAL_CODE;
    WriteProcessMemory(GetCurrentProcess(), (void *) SPEED_UNLOCK_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::EnableNoDrop() {
    uint8_t patch[] = NO_DROP_CHEAT_CODE;
    WriteProcessMemory(GetCurrentProcess(), (void *) NO_DROP_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::DisableNoDrop() {
    uint8_t patch[] = NO_DROP_ORIGINAL_CODE;
    WriteProcessMemory(GetCurrentProcess(), (void *) NO_DROP_INJECTION_ADDRESS, patch, sizeof(patch), nullptr);
}

void pvz::DisableAllCheats() {
    // always crashed when cleaning up this cheat, cheat has no effect in normal gameplay otherwise.
    // pvz::DisableSpeedUnlock();
    pvz::DisableAutoCollect();
    pvz::DisableNoDrop();
}
