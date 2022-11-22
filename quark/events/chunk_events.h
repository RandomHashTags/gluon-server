//
//  chunk_events.h
//  quark
//
//  Created by Evan Anderson on 11/21/22.
//

#ifndef chunk_events_h
#define chunk_events_h

#include "event.h"
#include "../util/location/chunk.h"

extern const struct Event EVENT_CHUNK_LOAD;
extern const struct Event EVENT_CHUNK_UNLOAD;

struct ChunkEvent {
    const struct Event event;
    struct Chunk *chunk;
};
struct ChunkEventCancellable {
    const struct ChunkEvent event;
    _Bool is_cancelled;
};

#endif /* chunk_events_h */
