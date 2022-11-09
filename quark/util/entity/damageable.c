//
//  damageable.c
//  quark
//
//  Created by Evan Anderson on 11/4/22.
//

#include "damageable.h"

void freeDamageable(Damageable *damageable) {
    freeEntity(damageable->entity);
    free(damageable);
}

enum EntityDamageResult damageDamageable(Damageable *damageable, double amount) {
    printf("damagableDamageable;damaging damagable with uuid %d %f units\n", *damageable->entity->uuid, amount);
    double new_amount = damageable->health - amount;
    enum EntityDamageResult result = ENTITY_DAMAGE_RESULT_SUCCESS;
    if (new_amount <= 0.00) {
        new_amount = 0;
        result = ENTITY_DAMAGE_RESULT_KILLED_VICTIM;
    }
    damageable->health = new_amount;
    return result;
}

_Bool isDead(Damageable *damageable) {
    return damageable->health == 0.00;
}
