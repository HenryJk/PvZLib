#include "pvz.hpp"

namespace pvz {
    typedef void(__thiscall *__CobCannonFire)(Plant *, int32_t, int32_t);

    void Plant::CobCannonFire(int32_t x, int32_t y) { ((__CobCannonFire) 0x466D50)(this, x, y); }
} // namespace pvz
