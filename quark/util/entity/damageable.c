//
//  damageable.c
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#include "damageable.h"

void damageable_destroy(Damageable *damageable) {
    entity_destroy(damageable->entity);
    free(damageable);
}

enum EntityDamageResult damageable_damage(Damageable *damageable, double amount) {
    printf("damagableDamageable;damaging damagable with uuid %d %f units\n", damageable->entity->uuid, amount);
    double new_amount = damageable->health - amount;
    enum EntityDamageResult result = ENTITY_DAMAGE_RESULT_SUCCESS;
    if (new_amount <= 0.00) {
        new_amount = 0;
        result = ENTITY_DAMAGE_RESULT_KILLED_VICTIM;
    }
    damageable->health = new_amount;
    return result;
}

_Bool damageable_is_dead(Damageable *damageable) {
    return damageable->health == 0.00;
}
