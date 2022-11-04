//
//  player.c
//  quark
//
//  Created by Evan Anderson on 11/3/22.
//

#include "player.h"

enum PlayerDamageResult damage(struct Player *player, double amount) {
    double new_amount = player->living_entity.health - amount;
    enum PlayerDamageResult result = PLAYER_DAMAGE_RESULT_SUCCESS;
    if (new_amount <= 0.00) {
        new_amount = 0;
        result = PLAYER_DAMAGE_RESULT_KILLED_VICTIM;
    }
    player->living_entity.health = new_amount;
    return result;
}

_Bool isDead(struct Player *player) {
    return player->living_entity.health <= 0.00;
}
