#include "pvz.hpp"

namespace pvz {
    void Plant::CobCannonFire(int32_t x, int32_t y) {
        auto p = (fun)((void *) 0x466D50);
        p(this, x, y);
    }
}
