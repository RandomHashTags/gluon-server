# Quark
## Background
This project was created for multiple reasons:
- further my knowledge in C programming (this is my first C project)
- maximize performance for a great server and client experience
- give server owners (even more) control over their servers, instead of third-parties ;)

## Current Features
This is a standalone server. Some features may be limited in functionality, and some features will be expanded in the future.

- [ ] Maintainable server experience
  - [ ] Logging
  - [ ] Authentication / SSL / HTTPS / Secure connection
  - [ ] Encryption
- [ ] Blocks
  - [x] Implementation
  - [ ] Boundaries / Collision
  - [ ] Block Entities
  - [ ] Block Resistance (to explosions)
  - [ ] Block Spawners
  - [ ] BlockState
  - [ ] BlockFace
  - [ ] Command Blocks
  - [ ] Pushable blocks (pistons)
  - [ ] Redstone
- [ ] Crafting
  - [x] Implementation
  - [ ] Crafting logic
- [x] Difficulties
- [ ] Enchanting
  - [x] Enchantment Types
  - [ ] Enchantments' logic
- [ ] Entities
  - [x] Implementation
  - [ ] Boundaries / Collision
  - [ ] Passengers / ridable
  - [ ] Pathfinding
- [x] [Events](https://github.com/RandomHashTags/quark/tree/main/quark/events)
- [ ] Gamemodes
  - [x] Implementation
  - [ ] Gamemodes' logic
- [ ] Inventories
  - [x] Implementation
  - [ ] Inventories' logic
- [ ] Items
  - [x] Implementation
  - [x] Durability
  - [x] ItemMeta
  - [x] Stored Enchants
  - [ ] NBT
- [ ] JSON
- [ ] Loot / treasure
- [x] Materials
- [ ] Potion Effects
  - [x] Potion Effect Types
  - [ ] Potion Effects' logic
- [ ] Physics
  - [ ] Gravity
- [ ] Structures
  - [ ] Structure Generation
- [x] Tick handling
  - [x] Dynamic tick rate changing
  - [ ] x
- [ ] Worlds
  - [x] Implementation
  - [ ] Seed randomizer
  - [ ] Terrain Generation / Noise
  - [ ] Biomes
    - [x] Implementation
    - [x] Temperature and Rainfall
    - [ ] Biome Generation
  - [ ] Chunks
    - [x] Implementation
    - [ ] Chunk Generation
- [ ] Communication with Quark Client
  - [ ] Communication with the Minecraft Client

## Future Development
I'm just one dude. PRs are welcome, and need to adhere to the coding style defined in `X.txt`.
### Financial support
If this project does become usable, it definitely will need to be continually updated. There isn't a way to financially support this project at this time.

## Dependencies
* [cJSON](https://github.com/DaveGamble/cJSON)

## Usage
1. clone repo
2. open repo in terminal
3. edit server files
4. run `bash _compile.sh`
5. run `bash _start.sh`
