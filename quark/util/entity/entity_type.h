//
//  entity_type.h
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef entity_type_h
#define entity_type_h

struct EntityType {
    const char *identifier;
    
    _Bool receives_fall_damage;
    
    unsigned short no_damage_ticks_maximum;
    unsigned short fire_ticks_maximum;
    unsigned short freeze_ticks_maximum;
};

struct EntityType *entity_type_create(const char *identifier, unsigned short no_damage_ticks_maximum, unsigned short fire_ticks_maximum);
void entity_type_destroy(struct EntityType *type);

#endif /* entity_type_h */
