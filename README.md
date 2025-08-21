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
