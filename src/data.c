/*
 *  Definicie
 */

#include "data.h"

// databaza predmetov, ktore moze mat bojova jednotka v inventari
const ITEM items[NUMBER_OF_ITEMS] = {
        // predmety, ktore zaberaju 1 slot, zoradene podla atributu 'att'
        {.name = "wand", .att = 12, .def = 4, .slots = 1, .range = 4, .radius = 2}, // kuzelna palica
        {.name = "fireball", .att = 11, .def = 0, .slots = 1, .range = 3, .radius = 3}, // ohniva gula
        {.name = "sword", .att = 9, .def = 2, .slots = 1, .range = 0, .radius = 0}, // mec
        {.name = "spear", .att = 6, .def = 1, .slots = 1, .range = 1, .radius = 1}, // ostep
        {.name = "dagger", .att = 4, .def = 0, .slots = 1, .range = 0, .radius = 0}, // dyka
        {.name = "rock", .att = 3, .def = 0, .slots = 1, .range = 2, .radius = 1}, // skala
        {.name = "armor", .att = 2, .def = 7, .slots = 1, .range = 0, .radius = 0}, // brnenie
        {.name = "shield", .att = 2, .def = 6, .slots = 1, .range = 0, .radius = 0}, // stit
        {.name = "gloves", .att = 1, .def = 4, .slots = 1, .range = 0, .radius = 0}, // rukavice
        {.name = "helmet", .att = 1, .def = 5, .slots = 1, .range = 0, .radius = 0}, // helma
        {.name = "aura", .att = 0, .def = 8, .slots = 1, .range = 0, .radius = 0}, // ochranna aura

        // predmety, ktore zaberaju 2 sloty, zoradene podla atributu 'att'
        {.name = "cannon", .att = 12, .def = 0, .slots = 2, .range = 4, .radius = 4}, // kanon
        {.name = "axe", .att = 10, .def = 2, .slots = 2, .range = 1, .radius = 1}, // sekera
        {.name = "hammer", .att = 8, .def = 2, .slots = 2, .range = 1, .radius = 2}, // kladivo
        {.name = "crossbow", .att = 5, .def = 1, .slots = 2, .range = 3, .radius = 0}, // kusa
        {.name = "slingshot", .att = 2, .def = 0, .slots = 2, .range = 2, .radius = 1} // prak
};
