# Battle Simulator in C

### Overview
This project is a simple battle simulator implemented in C. Two armies fight against each other, where each unit can be equipped with one or two items from a predefined database. Items have attributes such as attack, defense, slots, range, and radius, which influence the outcome of the battle.

The battle proceeds in rounds, where each army attacks the other. Units lose health points (HP) depending on the damage dealt by their opponents’ items. The battle ends when one (or both) armies are destroyed, or when a maximum number of rounds is reached.

### Features
- Armies consist of **1–5 units**.
- Units start with **100 HP** and can hold up to **2 items** (if slot restrictions allow).
- Items are predefined in the database (`items` array) and provide **attack** and **defense** values.
- Combat mechanics:
  - Attack damage = `att - total_defense` (minimum 1 if attack is not null).
  - Defense is calculated from items equipped by the unit.
  - Range and radius determine how many units are affected by an attack.
- Damage tracking: All attacks in a round are logged and printed in grouped format.
- Error handling:
  - Invalid army size (`ERR_UNIT_COUNT`)
  - Wrong number of items per unit (`ERR_ITEM_COUNT`)
  - Nonexistent item (`ERR_WRONG_ITEM`)
  - Invalid slot configuration (`ERR_SLOTS`)
- Battle results:
  - **Winner: Army 1**
  - **Winner: Army 2**
  - **No Winner** (if both armies are destroyed at the same time)

### Input Format
1. First line: number of units in **Army 1** (between 1 and 5).
2. Following lines: each unit is defined as:
   - `<unit_name> <item1> [item2]`
     - `unit_name` → name of the unit (string without spaces)
     - `item1` → mandatory item (must exist in the database)
     - `item2` → optional second item (must exist in the database, total slots ≤ 2)
3. Repeat the same format for **Army 2**.
   
### Running the Program
1. Compile the program:
   ```bash
   gcc filename.c -o battle_sim
2. Run the program:
   ./battle_sim [max_rounds]
   [max_rounds] is optional:
  - `0` → only print armies (no battle simulation).
  - Positive number `N` → simulate up to **N rounds**.
  - If omitted → battle continues until one army is defeated.

### Example Input
- First line `2` → Army 1 has 2 units.
- `Warrior Sword Shield` → Unit named *Warrior* with items *Sword* and *Shield*.
- `Archer Bow` → Unit named *Archer* with item *Bow*.
- Next line `2` → Army 2 has 2 units.
- `Orc Axe` → Unit named *Orc* with item *Axe*.
- `Goblin Dagger Shield` → Unit named *Goblin* with items *Dagger* and *Shield*.

### Example Output
Army 1
    Unit: 0
    Name: Warrior
    HP: 100
    Item 1: Sword,10,2,1,1,0
    Item 2: Shield,0,5,1,0,0

    Unit: 1
    Name: Archer
    HP: 100
    Item 1: Bow,8,1,1,3,0

Army 2
    Unit: 0
    Name: Orc
    HP: 100
    Item 1: Axe,12,1,1,1,0

    Unit: 1
    Name: Goblin
    HP: 100
    Item 1: Dagger,5,0,1,1,0
    Item 2: Shield,0,5,1,0,0

Round 1
1: Warrior,100 Archer,100 
2: Orc,100 Goblin,100 
1,Warrior,Sword:        [Orc,7]
1,Archer,Bow:        [Orc,7]
2,Orc,Axe:        [Warrior,10]
2,Goblin,Dagger:        [Warrior,1] 

1: Warrior,89 Archer,100 
2: Orc,86 Goblin,100 

...
WINNER: 1

...
