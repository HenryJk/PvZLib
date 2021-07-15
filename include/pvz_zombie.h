#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) Zombie {
        union {
            EXACT_SIZE(ZOMBIE_STRUCT_SIZE);
            OF(bool is_visible, ZOMBIE_IS_VISIBLE_OFFSET);
            OF(uint32_t row_index, ZOMBIE_ROW_INDEX_OFFSET);
            OF(ZombieType type, ZOMBIE_TYPE_OFFSET);
            OF(uint32_t state, ZOMBIE_STATE_OFFSET);
            OF(float xpos, ZOMBIE_XPOS_OFFSET);
            OF(float ypos, ZOMBIE_YPOS_OFFSET);
            OF(float animation_speed, ZOMBIE_ANIMATION_SPEED_OFFSET);
            OF(bool is_biting, ZOMBIE_IS_BITING_OFFSET);
            OF(uint32_t age, ZOMBIE_AGE_OFFSET);
            OF(uint32_t movement_status, ZOMBIE_MOVEMENT_STATUS_OFFSET);
            OF(uint32_t ability_countdown, ZOMBIE_ABILITY_COUNTDOWN_OFFSET);
            OF(uint32_t bungee_target_column, ZOMBIE_BUNGEE_TARGET_COLUMN_OFFSET);
            OF(uint32_t extra_height, ZOMBIE_EXTRA_HEIGHT_OFFSET);
            OF(int32_t projectile_collision_box[4], ZOMBIE_PROJECTILE_COLLISION_BOX_OFFSET);
            OF(int32_t attack_collision_box[4], ZOMBIE_ATTACK_COLLISION_BOX_OFFSET);
            OF(uint32_t slow_countdown, ZOMBIE_SLOW_COUNTDOWN_OFFSET);
            OF(uint32_t stun_countdown, ZOMBIE_STUN_COUNTDOWN_OFFSET);
            OF(uint32_t freeze_countdown, ZOMBIE_FREEZE_COUNTDOWN_OFFSET);
            OF(bool is_hypnotized, ZOMBIE_IS_HYPNOTIZED_OFFSET);
            OF(bool is_blown, ZOMBIE_IS_BLOWN_OFFSET);
            OF(bool has_head, ZOMBIE_HAS_HEAD_OFFSET);
            OF(bool has_consumable, ZOMBIE_HAS_CONSUMABLE_OFFSET);
            OF(bool is_swimming, ZOMBIE_IS_SWIMMING_OFFSET);
            OF(bool is_climbing, ZOMBIE_IS_CLIMBING_OFFSET);
            OF(bool is_disgusted, ZOMBIE_IS_DISGUSTED_OFFSET);
            OF(uint32_t disgusted_countdown, ZOMBIE_DISGUSTED_COUNTDOWN_OFFSET);
            OF(HelmetType helmet_type, ZOMBIE_HELMET_TYPE_OFFSET);
            OF(int32_t hp, ZOMBIE_HP_OFFSET);
            OF(int32_t helmet_hp, ZOMBIE_HELMET_HP_OFFSET);
            OF(ShieldType shield_type, ZOMBIE_SHIELD_TYPE_OFFSET);
            OF(int32_t shield_hp, ZOMBIE_SHIELD_HP_OFFSET);
            OF(int32_t balloon_hp, ZOMBIE_BALLOON_HP_OFFSET);
            OF(uint32_t animation_id, ZOMBIE_ANIMATION_ID_OFFSET);
            OF(uint32_t id, ZOMBIE_ID_OFFSET);
        };
    };
} // namespace pvz
