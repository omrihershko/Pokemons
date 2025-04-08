//
// Created by omrih on 29/01/2024.
//

#ifndef HOMEWORK2_POKEMON_H
#define HOMEWORK2_POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct  {
    float height;   // Height of the Pokémon
    int attack;     // Attack power of the Pokémon
    float weight;   // Weight of the Pokémon
} Pokemon_bio_data;  // Structure representing the biological data of a Pokémon

typedef struct Pokemon_type Pokemon_type; // Forward declaration of Pokemon_type structure

typedef struct  {
    char *name;             // Name of the Pokémon
    char *species;          // Species of the Pokémon
    Pokemon_bio_data *bio;  // Biological data of the Pokémon
    Pokemon_type *type;     // Type of the Pokémon
} Pokemon;                  // Structure representing a Pokémon


typedef struct Pokemon_type Pokemon_type;  // Forward declaration of Pokemon_type structure

struct Pokemon_type {
    char *name;                             // Name of the Pokémon type
    int number_of_pokemon;                  // Number of Pokémon belonging to this type
    Pokemon_type **effective_against_me;    // Array of pointers to types that this type is effective against
    Pokemon_type **effective_against_others;// Array of pointers to types that are effective against this type
    int length_effective_against_me;        // Length of the effective_against_me array
    int length_effective_against_others;    // Length of the effective_against_others array
};


typedef struct {
    Pokemon_type **poiner_to_pokemon_type_array;  // Pointer to an array of pointers to Pokémon types
    Pokemon **poiner_to_pokemon_array;           // Pointer to an array of pointers to Pokémon
    int number_of_pokemon;                        // Total number of Pokémon
    int number_of_types_pokemon;                  // Total number of Pokémon types
} Pokemon_Info;                                   // Structure representing information about Pokémon



Pokemon *create_pokemon(char *name,char *species,Pokemon_bio_data *bio,Pokemon_type *type );

/**
 * Creates a new Pokemon with the given attributes.
 *
 * @param name The name of the Pokemon.
 * @param species The species of the Pokemon.
 * @param bio Pointer to the biological data of the Pokemon.
 * @param type Pointer to the type of the Pokemon.
 * @return Pointer to the newly created Pokemon.
 */

Pokemon_type *create_pokemon_type(char *name);
/**
 * Creates a new Pokemon type with the given name.
 *
 * @param name The name of the Pokemon type.
 * @return Pointer to the newly created Pokemon type.
 */
Pokemon_bio_data *create_pokemon_bio_data(float height,int attack,float weight);

/**
 * Creates a new Pokemon biological data structure with the given attributes.
 *
 * @param height The height of the Pokemon.
 * @param attack The attack power of the Pokemon.
 * @param weight The weight of the Pokemon.
 * @return Pointer to the newly created Pokemon biological data structure.
 */


bool add_effective_against_me(Pokemon_type *source_a,Pokemon_type *source_b);

/**
 * Adds a Pokemon type that is effective against the source_a Pokemon type.
 *
 * @param source_a Pointer to the Pokemon type to which another type will be added as effective against it.
 * @param source_b Pointer to the Pokemon type that will be added as effective against source_a.
 * @return true if the addition was successful, false if the type source_b is already listed as effective against source_a.
 */



status remove_effective_against_me(Pokemon_type *source_a,char *b);
/**
 * Removes a Pokemon type that is effective against the source_a Pokemon type.
 *
 * @param source_a Pointer to the Pokemon type from which another type will be removed as effective against it.
 * @param b The name of the Pokemon type to be removed as effective against source_a.
 * @return Success if the removal was successful, failure if source_a is NULL, b is NULL, or the type b is not listed as effective against source_a.
 */

bool add_effective_against_others(Pokemon_type *source_a,Pokemon_type *source_b);
/**
 * Adds a Pokemon type that is effective against other Pokemon types to the source_a Pokemon type.
 *
 * @param source_a Pointer to the Pokemon type to which another type will be added as effective against other types.
 * @param source_b Pointer to the Pokemon type that will be added as effective against other types.
 * @return true if the addition was successful, false if the type source_b is already listed as effective against other types for source_a.
 */

status remove_effective_against_others(Pokemon_type *source_a,char *b);
/**
 * Removes a Pokemon type that is effective against other Pokemon types from the source_a Pokemon type.
 *
 * @param source_a Pointer to the Pokemon type from which another type will be removed as effective against other types.
 * @param b The name of the Pokemon type to be removed as effective against other types for source_a.
 * @return Success if the removal was successful, failure if source_a is NULL, b is NULL, or the type b is not listed as effective against other types for source_a.
 */


status print_pokemon(Pokemon *pokemon_print);
/**
 * Prints the details of a given Pokemon.
 *
 * @param pokemon_print Pointer to the Pokemon to be printed.
 * @return Success if the Pokemon is successfully printed, failure if pokemon_print is NULL.
 */

status print_type_pokemon(Pokemon_type *pokemon_type_print);
/**
 * Prints the details of a given Pokemon type, including its effective relationships with other types.
 *
 * @param pokemon_type_print Pointer to the Pokemon type to be printed.
 * @return Success if the Pokemon type is successfully printed, failure if pokemon_type_print is NULL.
 */

#endif //HOMEWORK2_POKEMON_H
