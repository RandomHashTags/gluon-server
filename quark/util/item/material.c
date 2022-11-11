//
//  material.c
//  quark
//
//  Created by Evan Anderson on 11/5/22.
//

#include "material.h"

_Bool material_is_armor(enum Material material) {
    switch (material) {
        case MATERIAL_LEATHER_HELMET:
        case MATERIAL_LEATHER_CHESTPLATE:
        case MATERIAL_LEATHER_LEGGINGS:
        case MATERIAL_LEATHER_BOOTS:
            
        case MATERIAL_CHAINMAIL_HELMET:
        case MATERIAL_CHAINMAIL_CHESTPLATE:
        case MATERIAL_CHAINMAIL_LEGGINGS:
        case MATERIAL_CHAINMAIL_BOOTS:
            
        case MATERIAL_IRON_HELMET:
        case MATERIAL_IRON_CHESTPLATE:
        case MATERIAL_IRON_LEGGINGS:
        case MATERIAL_IRON_BOOTS:
            
        case MATERIAL_GOLDEN_HELMET:
        case MATERIAL_GOLDEN_CHESTPLATE:
        case MATERIAL_GOLDEN_LEGGINGS:
        case MATERIAL_GOLDEN_BOOTS:
            
        case MATERIAL_DIAMOND_HELMET:
        case MATERIAL_DIAMOND_CHESTPLATE:
        case MATERIAL_DIAMOND_LEGGINGS:
        case MATERIAL_DIAMOND_BOOTS:
            
        case MATERIAL_NETHERITE_HELMET:
        case MATERIAL_NETHERITE_CHESTPLATE:
        case MATERIAL_NETHERITE_LEGGINGS:
        case MATERIAL_NETHERITE_BOOTS:
            return 1;
        default:
            return 0;
    }
}

_Bool material_is_ore(enum Material material) {
    switch (material) {
        case MATERIAL_COAL_ORE:
        case MATERIAL_COPPER_ORE:
        case MATERIAL_DIAMOND_ORE:
        case MATERIAL_GOLD_ORE:
            return 1;
        default:
            return 0;
    }
}

_Bool material_is_tool(enum Material material) {
    switch (material) {
        case MATERIAL_SHEARS:
        case MATERIAL_FISHING_ROD:
        case MATERIAL_TRIDENT:
            
        case MATERIAL_BOW:
        case MATERIAL_CROSSBOW:
            
        case MATERIAL_WOODEN_AXE:
        case MATERIAL_WOODEN_HOE:
        case MATERIAL_WOODEN_PICKAXE:
        case MATERIAL_WOODEN_SHOVEL:
        case MATERIAL_WOODEN_SWORD:
            
        case MATERIAL_STONE_AXE:
        case MATERIAL_STONE_HOE:
        case MATERIAL_STONE_PICKAXE:
        case MATERIAL_STONE_SHOVEL:
        case MATERIAL_STONE_SWORD:
            
        case MATERIAL_IRON_AXE:
        case MATERIAL_IRON_HOE:
        case MATERIAL_IRON_PICKAXE:
        case MATERIAL_IRON_SHOVEL:
        case MATERIAL_IRON_SWORD:
            
        case MATERIAL_GOLDEN_AXE:
        case MATERIAL_GOLDEN_HOE:
        case MATERIAL_GOLDEN_PICKAXE:
        case MATERIAL_GOLDEN_SHOVEL:
        case MATERIAL_GOLDEN_SWORD:
            
        case MATERIAL_DIAMOND_AXE:
        case MATERIAL_DIAMOND_HOE:
        case MATERIAL_DIAMOND_PICKAXE:
        case MATERIAL_DIAMOND_SHOVEL:
        case MATERIAL_DIAMOND_SWORD:
            
        case MATERIAL_NETHERITE_AXE:
        case MATERIAL_NETHERITE_HOE:
        case MATERIAL_NETHERITE_PICKAXE:
        case MATERIAL_NETHERITE_SHOVEL:
        case MATERIAL_NETHERITE_SWORD:
            return 1;
        default:
            return 0;
    }
}

_Bool material_can_be_enchanted(enum Material material) {
    return material_is_armor(material) || material_is_tool(material);
}
