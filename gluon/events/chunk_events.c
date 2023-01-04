//
//  chunk_events.c
//  gluon
//
//  Created by Evan Anderson on 11/21/22.
//

#include "chunk_events.h"

const struct Event EVENT_CHUNK_LOAD =   { .identifier = "minecraft.chunk.load", .key = "onChunkLoad" };
const struct Event EVENT_CHUNK_UNLOAD = { .identifier = "minecraft.chunk.unload", .key = "onChunkUnload" };
