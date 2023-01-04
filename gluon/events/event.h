//
//  event.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef event_h
#define event_h

#include "event_type.h"

struct Event {
    const char *identifier;
    const char *key;
    const _Bool is_async;
};
struct EventCancellable {
    struct Event event;
    _Bool is_cancelled;
};

/*struct Event {
    const _Bool is_async;
    const enum EventType type;
};

struct EventCancellable {
    const struct Event event;
    _Bool is_cancelled;
};*/

#endif /* event_h */
