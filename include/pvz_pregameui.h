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
                         "movl %0, %%ebx;"
                         "movl %1, %%esi;"
                         "movl $0x1, %%edi;"
                         "movl $0x1, %%ebp;"
                         "movl %2, %%eax;"
                         "calll *%%eax;"
                         "popal;"
                         :
                         : "g"(this), "i"(BASE_PTR_ADDRESS), "i"(LETS_ROCK_FUNC_ADDRESS)
                         : "eax", "ebx", "esi", "edi", "esp");
        }
        void SelectCard(PlantType card_type);
        void SelectImitaterCard(PlantType imitater_type);
    };
} // namespace pvz
