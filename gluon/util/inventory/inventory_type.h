//
//  inventory_type.h
//  gluon
//
//  Created by Evan Anderson on 11/3/22.
//

#ifndef inventory_type_h
#define inventory_type_h

struct InventoryType {
    const char *identifier;
    const unsigned short size;
};

void inventory_type_destroy(struct InventoryType *type);

extern struct InventoryType INVENTORY_TYPE_MINECRAFT_ANVIL;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_BARREL;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_BEACON;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_BLAST_FURNACE;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_BREWING;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_CARTOGRAPHY;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_CHEST;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_CRAFTING;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_CREATIVE;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_DISPENSER;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_DROPPER;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_ENCHANTING;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_ENDER_CHEST;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_FURNACE;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_GRINDSTONE;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_HOPPER;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_LECTERN;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_LOOM;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_MERCHANT;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_PLAYER;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_SHULKER_BOX;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_SMITHING;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_SMOKER;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_STONECUTTER;
extern struct InventoryType INVENTORY_TYPE_MINECRAFT_WORKBENCH;

#endif /* inventory_type_h */
