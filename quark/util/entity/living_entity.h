//
//  living_entity.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef living_entity_h
#define living_entity_h

#include "damageable.h"
#include "entity_equipment.h"
#include "../potion/potion_effect.h"

struct LivingEntity {
    struct Damageable *damageable;
    struct EntityEquipment *equipment;
    
    _Bool can_pickup_items;
    _Bool has_ai;
    
    _Bool is_collidable;
    _Bool is_invisible;
    _Bool is_leashed;
    _Bool is_swimming;
    _Bool is_riptiding;
    
    unsigned short potion_effect_count;
    struct PotionEffect *potion_effects;
    
    double eye_height;
    
    unsigned short no_damage_ticks;
    unsigned short no_damage_ticks_maximum;
    
    unsigned short air_remaining;
    unsigned short air_maximum;
    
    struct LivingEntity *killer;
};

void living_entity_destroy(struct LivingEntity *entity);

enum EntityDamageResult living_entity_damage(struct LivingEntity *entity, double amount);

void living_entity_tick(struct LivingEntity *entity);

void living_entity_swing_main_hand(struct LivingEntity *entity);
void living_entity_swing_off_hand(struct LivingEntity *entity);

struct PotionEffect *living_entity_get_potion_effect(struct LivingEntity *entity, struct PotionEffectType type);
void living_entity_add_potion_effect(struct LivingEntity *entity, struct PotionEffectType type, unsigned short amplifier, unsigned short duration, _Bool has_icon, _Bool has_particles, _Bool is_ambient);
void living_entity_remove_potion_effect(struct LivingEntity *entity, struct PotionEffectType type);

void living_entity_damage_item_in_main_hand(struct LivingEntity *entity, unsigned short amount);

#endif /* living_entity_h */
