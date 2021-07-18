#pragma once

#include "pvz_button.h"
#include "pvz_card.h"
#include "pvz_enum.h"
#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) PreGameUI {
        union {
            OF(Button *lets_rock_button_ptr, PRE_GAME_UI_LETS_ROCK_BUTTON_PTR_OFFSET);
            OF(Card card[49], PRE_GAME_UI_CARD_ARRAY_OFFSET);
            OF(uint32_t next_slot_index, PRE_GAME_UI_NEXT_SLOT_INDEX_OFFSET);
        };

        inline void LetsRock() {
            asm volatile("pushal;"
#if defined VERSION_1_0_0_1051_EN
                         "movl %0, %%ebx;"
#elif defined VERSION_1_2_0_1096_EN
                         "pushl %0;"
#endif
                         "movl %1, %%eax;"
                         "calll *%%eax;"
                         "popal;"
                         :
                         : "g"(this), "i"(LETS_ROCK_FUNC_ADDRESS)
                         : "eax", "ebx", "esp");
        }
        void SelectCard(PlantType card_type);
        void SelectImitaterCard(PlantType imitater_type);
    };
} // namespace pvz
