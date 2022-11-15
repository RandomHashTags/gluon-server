//
//  inventory_type.c
//  quark
//
//  Created by Evan Anderson on 11/12/22.
//

#include <stdlib.h>
#include "inventory_type.h"

void inventory_type_destroy(struct InventoryType *type) {
    free((char *) type->identifier);
    free(type);
}

struct InventoryType INVENTORY_TYPE_MINECRAFT_ANVIL =         { .identifier = "minecraft.anvil" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_BARREL =        { .identifier = "minecraft.barrel" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_BEACON =        { .identifier = "minecraft.beacon" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_BLAST_FURNACE = { .identifier = "minecraft.blast_furnace" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_BREWING =       { .identifier = "minecraft.brewing" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_CARTOGRAPHY =   { .identifier = "minecraft.cartography" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_CHEST =         { .identifier = "minecraft.chest" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_CRAFTING =      { .identifier = "minecraft.crafting" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_CREATIVE =      { .identifier = "minecraft.creative" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_DISPENSER =     { .identifier = "minecraft.dispenser" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_DROPPER =       { .identifier = "minecraft.dropper" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_ENCHANTING =    { .identifier = "minecraft.enchanting" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_ENDER_CHEST =   { .identifier = "minecraft.ender_chest" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_FURNACE =       { .identifier = "minecraft.furnace" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_GRINDSTONE =    { .identifier = "minecraft.grindstone" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_HOPPER =        { .identifier = "minecraft.hopper" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_LECTERN =       { .identifier = "minecraft.lectern" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_LOOM =          { .identifier = "minecraft.loom" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_MERCHANT =      { .identifier = "minecraft.merchant" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_PLAYER =        { .identifier = "minecraft.player" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_SHULKER_BOX =   { .identifier = "minecraft.shulker_box" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_SMITHING =      { .identifier = "minecraft.smithing" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_SMOKER =        { .identifier = "minecraft.smoker" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_STONECUTTER =   { .identifier = "minecraft.stonecutter" };
struct InventoryType INVENTORY_TYPE_MINECRAFT_WORKBENCH =     { .identifier = "minecraft.workbench" };
