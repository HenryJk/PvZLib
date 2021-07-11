#include "pvz_pregameui.h"

void pvz::PreGameUI::SelectCard(PlantType card_type) {
    auto &selected_card      = card[(uint32_t) card_type];
    selected_card.state      = pvz::CardState::kSelected;
    selected_card.slot_index = next_slot_index;
    next_slot_index++;
}

void pvz::PreGameUI::SelectImitaterCard(PlantType imitater_type) {
    auto &selected_card         = card[(uint32_t) PlantType::kImitater];
    selected_card.state         = pvz::CardState::kSelected;
    selected_card.imitater_type = imitater_type;
    selected_card.slot_index    = next_slot_index;
    next_slot_index++;
}
