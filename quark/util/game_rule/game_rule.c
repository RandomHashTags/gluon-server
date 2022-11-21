//
//  game_rule.c
//  quark
//
//  Created by Evan Anderson on 11/21/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_rule.h"
#include "../../utilities.h"

struct GameRule *game_rule_create(const char *identifier, const enum ValueType value_type) {
    struct GameRule *game_rule = malloc(sizeof(struct GameRule));
    if (!game_rule) {
        printf("failed to allocate memory for a GameRule\n");
        return NULL;
    }
    const char *target_identifier = malloc_string(identifier);
    if (!target_identifier) {
        printf("failed to allocate memory for a GameRule *target_identifier\n");
        free(game_rule);
        return NULL;
    }
    game_rule->identifier = identifier;
    memcpy((enum ValueType *) &game_rule->value_type, &value_type, sizeof(enum ValueType));
    return game_rule;
}
void game_rule_destroy(struct GameRule *game_rule) {
    free((char *) game_rule->identifier);
    free(game_rule);
}
