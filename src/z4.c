#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h" // NEMENIT, inak vas kod neprejde testom !!!

// chybove hlasenia
#define ERR_UNIT_COUNT "ERR_UNIT_COUNT"
#define ERR_ITEM_COUNT "ERR_ITEM_COUNT"
#define ERR_WRONG_ITEM "ERR_WRONG_ITEM"
#define ERR_SLOTS "ERR_SLOTS"

#define MAX_DAMAGE_RECORDS 100

typedef struct {
    int army;
    char attacker[MAX_NAME + 1];
    char item[MAX_NAME + 1];
    char target[MAX_NAME + 1];
    int damage;
    int attack_id;
} DAMAGE_INFO;

DAMAGE_INFO damages[MAX_DAMAGE_RECORDS];
int damages_count = 0;
int tracking_attack_id = 0;

int is_battle_over(const UNIT *army1, int army1_size, const UNIT *army2, int army2_size) {
    return (army1_size == 0 || army2_size == 0);
}

void print_units(const UNIT *army1, int army1_size, const UNIT *army2, int army2_size) {
    printf("1: ");
    for (int i = 0; i < army1_size; i++) {
        if (i > 0) printf(" ");
        printf("%s,%d", army1[i].name, army1[i].hp);
    }
    printf(" \n");

    printf("2: ");
    for (int i = 0; i < army2_size; i++) {
        if (i > 0) printf(" ");
        printf("%s,%d", army2[i].name, army2[i].hp);
    }
    printf(" \n");
}

void add_damage(int army, const char *attacker, const char *item, const char *target, int damage, int attack_id) {
    if (damages_count < MAX_DAMAGE_RECORDS) {
        damages[damages_count].army = army;
        strncpy(damages[damages_count].attacker, attacker, MAX_NAME);
        damages[damages_count].attacker[MAX_NAME] = '\0';
        strncpy(damages[damages_count].item, item, MAX_NAME);
        damages[damages_count].item[MAX_NAME] = '\0';
        strncpy(damages[damages_count].target, target, MAX_NAME);
        damages[damages_count].target[MAX_NAME] = '\0';
        damages[damages_count].damage = damage;
        damages[damages_count].attack_id = attack_id;
        damages_count++;
    }
}

void print_damage(void) {
    int unique_attack_ids[MAX_DAMAGE_RECORDS];
    int unique_count = 0;

    for (int i = 0; i < damages_count; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (unique_attack_ids[j] == damages[i].attack_id) {
                found = 1;
                break;
            }
        }
        if (!found) {
            unique_attack_ids[unique_count++] = damages[i].attack_id;
        }
    }

    for (int i = 0; i < unique_count; i++) {
        int attack_id = unique_attack_ids[i];

        for (int j = 0; j < damages_count; j++) {
            if (damages[j].attack_id == attack_id) {
                printf("%d,%s,%s:        ",
                       damages[j].army, damages[j].attacker, damages[j].item);

                int first_target = 1;
                for (int k = 0; k < damages_count; k++) {
                    if (damages[k].attack_id == attack_id) {
                        if (!first_target) printf(" ");
                        printf("[%s,%d]", damages[k].target, damages[k].damage);
                        first_target = 0;
                    }
                }

                printf(" \n");
                break;
            }
        }
    }

    damages_count = 0;
    tracking_attack_id = 0;
}

int calculate_damage(const ITEM *item, int total_defense) {
    return (item == NULL) ? 0 : (item->att > total_defense) ? (item->att - total_defense) : 1;
}

int calculate_defense(const UNIT *unit) {
    int total_def = 0;
    if (unit->item1 != NULL) {
        total_def += unit->item1->def;
    }
    if (unit->item2 != NULL) {
        total_def += unit->item2->def;
    }
    return total_def;
}

void unit_attack(const UNIT *attacker, UNIT *defender_army, int attacker_position, int defender_size, int army_number, const ITEM *item) {
    if (item == NULL) return;

    if (item->range >= attacker_position) {
        tracking_attack_id++;

        for (int r = 0; r <= item->radius && r < defender_size; r++) {
            UNIT *target = &defender_army[r];
            int defense = calculate_defense(target);
            int damage = calculate_damage(item, defense);
            add_damage(army_number, attacker->name, item->name, target->name, damage, tracking_attack_id);
            target->hp -= damage;
        }
    }
}

void attack_army(const UNIT *attacker_army, int attacker_size, UNIT *defender_army, int defender_size, int army_number) {
    for (int i = 0; i < attacker_size; i++) {
        if (defender_size > 0) {
            const UNIT *attacker = &attacker_army[i];

            unit_attack(attacker, defender_army, i, defender_size, army_number, attacker->item1);
            unit_attack(attacker, defender_army, i, defender_size, army_number, attacker->item2);
        }
    }
}

void update_army(UNIT **army, int *size) {
    int new_size = 0;

    for (int i = 0; i < *size; i++) {
        if ((*army)[i].hp > 0) {
            if (new_size != i) {
                (*army)[new_size] = (*army)[i];
            }
            new_size++;
        }
    }

    *size = new_size;
}

void print_result(const UNIT *army1, int army1_size, const UNIT *army2, int army2_size) {
    if (army1_size == 0 && army2_size == 0) {
        printf("\nNO WINNER\n");
    } else if (army2_size == 0) {
        printf("\nWINNER: 1\n");
    } else if (army1_size == 0) {
        printf("\nWINNER: 2\n");
    }
}

const ITEM *find_item(const char *item_name) {
    for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
        if (strcmp(items[i].name, item_name) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

const ITEM *validate_item(const char *item_name) {
    const ITEM *item = find_item(item_name);
    if (item == NULL) {
        printf("%s\n", ERR_WRONG_ITEM);
        return NULL;
    }
    return item;
}

int validate_slots(const ITEM *item1, const ITEM *item2) {
    if (item1->slots + item2->slots > 2) {
        printf("%s\n", ERR_SLOTS);
        return -1;
    }
    return 0;
}


int parse_unit_line(const char *line, char *name, char *item1_name, char *item2_name) {
    char line_copy[MAX_NAME * 3];
    strncpy(line_copy, line, sizeof(line_copy) - 1);
    line_copy[sizeof(line_copy) - 1] = '\0';

    int count = 0;
    char *token = strtok(line_copy, " \n\r\t");

    if (token != NULL) {
        strcpy(name, token);
        count++;

        token = strtok(NULL, " \n\r\t");
        if (token != NULL) {
            strcpy(item1_name, token);
            count++;

            token = strtok(NULL, " \n\r\t");
            if (token != NULL) {
                strcpy(item2_name, token);
                count++;

                token = strtok(NULL, " \n\r\t");
                if (token != NULL) {
                    printf("%s\n", ERR_ITEM_COUNT);
                    return -1;
                }
            }
        }
    }

    if (count == 1) {
        printf("%s\n", ERR_ITEM_COUNT);
        return -1;
    } else if (count == 2) {
        return 1;
    } else if (count == 3) {
        return 2;
    } else {
        return -1;
    }
}

int load_unit(UNIT *unit) {
    char line[MAX_NAME * 3];
    char item1_name[MAX_NAME + 1] = {0};
    char item2_name[MAX_NAME + 1] = {0};

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return -1;
    }

    memset(unit->name, 0, MAX_NAME + 1);
    unit->item1 = NULL;
    unit->item2 = NULL;
    unit->hp = 100;

    int items_count = parse_unit_line(line, unit->name, item1_name, item2_name);
    if (items_count < 0) {
        return -1;
    }

    unit->item1 = validate_item(item1_name);
    if (unit->item1 == NULL) {
        return -1;
    }

    if (items_count == 2) {
        unit->item2 = validate_item(item2_name);
        if (unit->item2 == NULL) {
            return -1;
        }

        if (validate_slots(unit->item1, unit->item2) < 0) {
            return -1;
        }
    }

    return 0;
}

int load_army(UNIT **army, int *size) {
    if (scanf("%d", &(*size)) != 1) {
        return -1;
    }

    if (*size < MIN_ARMY || *size > MAX_ARMY) {
        printf("%s\n", ERR_UNIT_COUNT);
        return -1;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    *army = (UNIT *) malloc((*size) * sizeof(UNIT));
    if (*army == NULL) {
        return -1;
    }

    for (int i = 0; i < *size; i++) {
        if (load_unit(&((*army)[i])) != 0) {
            free(*army);
            return -1;
        }
    }

    return 0;
}

void print_item(int index, const ITEM *item) {
    if (item == NULL) return;

    printf("    Item %d: %s,%d,%d,%d,%d,%d\n",
           index, item->name, item->att, item->def, item->slots, item->range, item->radius);
}

void print_unit(int index, const UNIT *unit) {
    printf("    Unit: %d\n", index);
    printf("    Name: %s\n", unit->name);
    printf("    HP: %d\n", unit->hp);

    if (unit->item1 != NULL) {
        print_item(1, unit->item1);
    }

    if (unit->item2 != NULL) {
        print_item(2, unit->item2);
    }

    printf("\n");
}


void print_army(const UNIT *army, int size, int army_number) {
    printf("Army %d\n", army_number);

    for (int i = 0; i < size; i++) {
        print_unit(i, &army[i]);
    }
}

void print_armies(const UNIT *army1, int army1_size, const UNIT *army2, int army2_size) {
    print_army(army1, army1_size, 1);
    print_army(army2, army2_size, 2);
}

int main(const int argc, char *argv[]) {
    int max_rounds = -1;
    UNIT *army1 = NULL;
    UNIT *army2 = NULL;
    int army1_size = 0;
    int army2_size = 0;

    if (argc > 1) {
        max_rounds = atoi(argv[1]);
    }

    if (load_army(&army1, &army1_size) != 0) {
        return 0;
    }

    if (load_army(&army2, &army2_size) != 0) {
        free(army1);
        return 0;
    }

    print_armies(army1, army1_size, army2, army2_size);

    if (max_rounds == 0) {
        free(army1);
        free(army2);
        return 0;
    }

    int round = 1;
    while (!is_battle_over(army1, army1_size, army2, army2_size)) {
        if (max_rounds > 0 && round > max_rounds) {
            break;
        }

        if (round > 1) {
            printf("\n");
        }
        printf("Round %d\n", round);

        print_units(army1, army1_size, army2, army2_size);

        attack_army(army1, army1_size, army2, army2_size, 1); // Armáda 1 útočí na armádu 2
        attack_army(army2, army2_size, army1, army1_size, 2); // Armáda 2 útočí na armádu 1

        print_damage();

        update_army(&army1, &army1_size);
        update_army(&army2, &army2_size);

        print_units(army1, army1_size, army2, army2_size);

        round++;
    }

    print_result(army1, army1_size, army2, army2_size);

    free(army1);
    free(army2);

    return 0;
}
