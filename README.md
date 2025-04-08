# 🧬 Pokémon Type Management System

## Overview
This project simulates a simplified **Pokémon data management system** written in C. It supports the creation, organization, and display of Pokémon data, including their biological properties, types, and type effectiveness (which types are strong/weak against others).

## Features
- 🧪 Create and manage Pokémon with:
  - Name
  - Species
  - Biological data (height, weight, attack)
  - Type
- 🔁 Add and remove **type effectiveness** (effective against others or weak against others).
- 📊 Print full Pokémon data and type effectiveness relations.
- 🧠 Dynamically manages memory and uses structured, modular C code.

---

## File Structure

| File         | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| `Pokemon.c`  | Core implementation of Pokémon creation, type management, effectiveness logic |
| `Pokemon.h`  | Header file for Pokémon structures and function declarations                |
| `Defs.h`     | Shared constants, enums, and utility types                                  |
| `Pokedex.c`  | (Assumed) Handles storage and organization of multiple Pokémon and types    |

---

## Key Data Structures

### `Pokemon`
- `name`, `species`
- `bio`: A `Pokemon_bio_data` struct (height, weight, attack)
- `type`: A pointer to a `Pokemon_type` struct

### `Pokemon_type`
- `name`
- Number of Pokémon of this type
- Lists of other types it's effective against or weak to

---

## Example Usage

```c
Pokemon_type *fire = create_pokemon_type("Fire");
Pokemon_type *water = create_pokemon_type("Water");
add_effective_against_me(fire, water);      // Water is effective against Fire
add_effective_against_others(water, fire);  // Water is strong against Fire

Pokemon_bio_data *bio = create_pokemon_bio_data(1.5, 120, 40.2);
Pokemon *charmander = create_pokemon("Charmander", "Lizard Pokémon", bio, fire);
print_pokemon(charmander);
print_type_pokemon(fire);
