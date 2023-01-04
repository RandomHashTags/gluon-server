//
//  game_rule.h
//  gluon
//
//  Created by Evan Anderson on 11/21/22.
//

#ifndef game_rule_h
#define game_rule_h

#include "../value_type.h"

struct GameRule {
    const char *identifier;
    const enum ValueType value_type;
    union {
        _Bool value_bool;
        int value_integer;
    };
};

struct GameRule *game_rule_create(const char *identifier, const enum ValueType value_type);
void game_rule_destroy(struct GameRule *game_rule);

#endif /* game_rule_h */
