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
- [ ] Gameplay features
  - [ ] Advancements
    - [x] Implementation
    - [ ] Advancements' logic
  - [ ] Boss Bars
  - [ ] Commands
  - [ ] Game Rules
  - [ ] Gamemodes
    - [x] Implementation
    - [ ] Gamemodes' logic
  - [x] Materials
  - [ ] Particles
    - [x] Implementation
  - [x] Permissions
  - [ ] Scoreboards
    - [ ] Implementation
    - [ ] Scoreboard logic
  - [ ] Sounds
    - [x] Implementation
  - [ ] Statistics
    - [ ] Implementation
- [ ] Crafting
  - [ ] Crafting logic
  - [ ] Crafting Recipes
    - [x] Implementation
    - [ ] Crafting Recipe logic
- [ ] Enchanting
  - [x] Enchantment Types
  - [ ] Enchantments' logic
- [ ] Entities
  - [x] Implementation
  - [ ] Boundaries / Collision
    - [x] Implementation
    - [ ] Collision logic
  - [ ] Passengers / ridable
    - [x] Implementation
    - [ ] Passengers' logic
  - [ ] Pathfinding
- [x] [Events](https://github.com/RandomHashTags/quark/tree/main/quark/events)
- [ ] Hack detection
  - [ ] Anti X-ray
  - [ ] Speed / Velocity discrepancies
- [ ] Inventories
  - [x] Implementation
  - [x] Inventory Types
    - [ ] Inventory Type logic
  - [x] Inventory logic
- [ ] Items
  - [x] Implementation
  - [x] Attack Cooldown
  - [x] Durability
  - [x] ItemMeta
  - [x] Stored Enchants
  - [ ] Eatable
  - [ ] Throwable
  - [ ] NBT
- [ ] JSON
- [ ] Loot / treasure
- [ ] Plugins / Mods
  - [x] Implementation
  - [ ] Enable / disable logic
- [ ] Potion Effects
  - [x] Implementation
  - [x] Potion Effect Types
  - [ ] Potion Effects' logic
- [ ] Physics
  - [ ] Gravity
    - [ ] Block Gravity
    - [x] Entity Gravity
  - [x] Fall damage
  - [ ] Liquids
- [ ] Structures
  - [x] Implementation
  - [ ] Structure Generation
- [x] Tick handling
  - [x] Dynamic tick rate
- [ ] Worlds
  - [x] Implementation
  - [x] Difficulties
  - [x] Location
  - [ ] Seed randomizer
  - [ ] Terrain Generation / Noise
  - [ ] View distance
  - [ ] Saves to file
  - [ ] Biomes
    - [x] Implementation
    - [x] Temperature and Rainfall
    - [ ] Biome Generation
    - [ ] Structures Generation
  - [ ] Chunks
    - [x] Implementation
    - [x] ChunkData
    - [ ] Chunk Generation
    - [ ] Saves to file
    - [ ] Blocks
      - [x] Implementation
      - [ ] Boundaries / Collision
        - [x] Implementation
        - [ ] Collision logic
      - [ ] Block Entities
      - [ ] Block Resistance (to explosions)
      - [ ] Block Spawners
      - [ ] BlockState
      - [ ] BlockFace
      - [ ] Command Blocks
      - [x] Passthrough-able
      - [ ] Portals
      - [ ] Preferred materials (that break the block)
      - [ ] Pushable blocks (pistons)
      - [ ] Redstone
- [ ] Communication with Client
  - [ ] Quark Client
  - [ ] Minecraft Client

## Future Development
I'm just one dude. PRs are welcome, and need to adhere to the coding style defined in `X.txt`.
### Financial support
If this project does become usable, it definitely will need to be continually updated. There isn't a way to financially support this project at this time.

## Dependencies
* a C JSON library (still researching a worthy implementation | may need to create a custom one)
  - **Other language contenders**
    - Python - https://github.com/tiangolo/fastapi
    - C++ - https://github.com/nlohmann/json
    - C++ - https://github.com/simdjson/simdjson

## Usage
1. open terminal
2. clone repo
3. run `cd quark`
4. run `bash _compile.sh`
5. run `bash _start.sh`
