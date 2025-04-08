//
// Created by omrih on 29/01/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "Pokemon.h"



Pokemon_bio_data *create_pokemon_bio_data(float height,int attack,float weight){
    Pokemon_bio_data* pokemon_bio;
    pokemon_bio = (Pokemon_bio_data*)malloc(sizeof(Pokemon_bio_data));
    if(pokemon_bio==NULL){
        return pokemon_bio;
    }
    pokemon_bio->height=height;
    pokemon_bio->attack=attack;
    pokemon_bio->weight=weight;
    //free
    return pokemon_bio;

}


Pokemon* create_pokemon(char *name,char *species,Pokemon_bio_data *bio,Pokemon_type *type ){
    if(name==NULL || species==NULL || bio==NULL || type==NULL){// check  if the pointer is null
        return NULL;
    }
    Pokemon* pokemon;
    pokemon = (Pokemon*)malloc(sizeof(Pokemon));
    if(pokemon==NULL){
        return pokemon;
    }
    pokemon->bio=bio;
    pokemon->type=type;
    pokemon->type->number_of_pokemon++;
    pokemon->name = (char*)malloc(strlen(name) + 1);
    if(pokemon->name==NULL){
        pokemon=NULL;
        return pokemon;
    }
    strcpy(pokemon->name, name);
    pokemon->species = (char*)malloc(sizeof(char) * strlen(species) + 1);
    if(pokemon->species==NULL){
        pokemon=NULL;
        return pokemon;
    }
    strcpy(pokemon->species, species);
    return pokemon;
}

Pokemon_type* create_pokemon_type(char *name){
    if(name==NULL){// check if the pointer is null
        return NULL;
    }
    Pokemon_type *pokemon_type_pointer;
    pokemon_type_pointer= (Pokemon_type*)malloc(sizeof(Pokemon_type));
    if(pokemon_type_pointer==NULL){
        return pokemon_type_pointer;
    }

    pokemon_type_pointer->name= malloc(strlen(name)+1);
    if(pokemon_type_pointer->name==NULL){
        pokemon_type_pointer=NULL;
        return pokemon_type_pointer;
    }
    strcpy(pokemon_type_pointer->name,name);
    pokemon_type_pointer->number_of_pokemon=0;
    pokemon_type_pointer->effective_against_me = NULL;
    pokemon_type_pointer->effective_against_others = NULL;

    pokemon_type_pointer->length_effective_against_me=0;
    pokemon_type_pointer->length_effective_against_others=0;

    return pokemon_type_pointer;
}

bool add_effective_against_me(Pokemon_type *source_a,Pokemon_type *source_b)
{
    if(source_a==NULL || source_b==NULL){
        return false;
    }
    // Check if source_b is already listed as effective against source_a
    for(int i=0;i<source_a->length_effective_against_me;i++){
        if(strcmp(source_a->effective_against_me[i]->name,source_b->name)==0){
            return false;

        }

    }
    // Allocate memory for the effective_against_me array if it's empty
    if (source_a->length_effective_against_me == 0) {
        source_a->effective_against_me = (Pokemon_type **)malloc(sizeof(Pokemon_type *));
        if(source_a->effective_against_me ==NULL){
            printf("Memory problem");
            exit(0);
        }
        source_a->effective_against_me[0] = source_b;
    } else {
        // Resize the effective_against_me array and add source_b to it
        source_a->effective_against_me = realloc(source_a->effective_against_me,
                                                 sizeof(Pokemon_type *) * (source_a->length_effective_against_me + 1));
        if(source_a->effective_against_me ==NULL){
            printf("Memory problem");
            exit(0);
        }
        source_a->effective_against_me[source_a->length_effective_against_me] = source_b;
    }
    // Increment the length of the effective_against_me array and return true
    (source_a->length_effective_against_me)++;
    return true;


}

bool add_effective_against_others(Pokemon_type *source_a,Pokemon_type *source_b) {

    if(source_a==NULL || source_b==NULL){
        return false;
    }
    // Check if source_b is already listed as effective against others for source_a
    for (int i = 0; i<source_a->length_effective_against_others; i++) {
        if (strcmp(source_a->effective_against_others[i]->name, source_b->name) == 0) {
            return false;

        }
    }
    // Allocate memory for the effective_against_me array if it's empty
    if (source_a->length_effective_against_others == 0) {
            source_a->effective_against_others = (Pokemon_type **) malloc(sizeof(Pokemon_type *));//costing
        if(source_a->effective_against_others ==NULL){
            printf("Memory problem");
            exit(0);
        }
            source_a->effective_against_others[0] = source_b;
        } else {
        // Resize the effective_against_me array and add source_b to it
        source_a->effective_against_others = realloc(source_a->effective_against_others,
                                                         sizeof(Pokemon_type *) *
                                                         (source_a->length_effective_against_others + 1));
        if(source_a->effective_against_others ==NULL){
            printf("Memory problem");
            exit(0);
        }
            source_a->effective_against_others[source_a->length_effective_against_others] = source_b;
        }
    // Increment the length of the effective_against_me array and return true
    (source_a->length_effective_against_others)++;
        return true;

    }

    status remove_effective_against_me(Pokemon_type *source_a, char *b) {


        // Check if source_a is NULL, b is NULL, or effective_against_me array is NULL or empty
        if (source_a == NULL || b == NULL || source_a->effective_against_me == NULL ||
            source_a->length_effective_against_me == 0) {
            return failure;
        }
        // Iterate through the effective_against_me array to find the type to be removed
        for (int i = 0; i < source_a->length_effective_against_me; i++) {
            if (source_a->effective_against_me[i] != NULL && strcmp(source_a->effective_against_me[i]->name, b) == 0) {
                // Found the type to be removed, shift the rest of the elements
                for (int j = i; j < source_a->length_effective_against_me - 1; j++) {
                    source_a->effective_against_me[j] = source_a->effective_against_me[j + 1];
                }
                source_a->length_effective_against_me--;
                return success;
            }
        }
        return failure; // Type not found
    }

    status remove_effective_against_others(Pokemon_type *source_a, char *b) {
        // Check if source_a is NULL, b is NULL, or effective_against_others array is NULL or empty

        if (source_a == NULL || b == NULL || source_a->effective_against_others == NULL ||
            source_a->length_effective_against_others == 0) {
            return failure;
        }
        // Iterate through the effective_against_others array to find the type to be removed

        for (int i = 0; i < source_a->length_effective_against_others; i++) {
            if (source_a->effective_against_others[i] != NULL &&
                strcmp(source_a->effective_against_others[i]->name, b) == 0) {
                // Found the type to be removed, shift the rest of the elements
                for (int j = i; j < source_a->length_effective_against_others - 1; j++) {
                    source_a->effective_against_others[j] = source_a->effective_against_others[j + 1];
                }
                source_a->length_effective_against_others--;
                return success;
            }
        }
        return failure; // Type not found
    }

    status print_pokemon(Pokemon *pokemon_print) {
        if (pokemon_print == NULL) {
            return failure;
        } else {
            printf("%s :\n", pokemon_print->name);
            printf("%s, %s Type.\n", pokemon_print->species, pokemon_print->type->name);
            printf("Height: %0.2f m    Weight: %0.2f kg    Attack: %d\n\n", pokemon_print->bio->height,
                   pokemon_print->bio->weight, pokemon_print->bio->attack);
            return success;
        }
    }

    status print_type_pokemon(Pokemon_type *pokemon_type_print) {
        if (pokemon_type_print == NULL) {
            return failure;
        }

        printf("Type %s -- %d pokemons\n", pokemon_type_print->name, pokemon_type_print->number_of_pokemon);
        if(pokemon_type_print->length_effective_against_others==0 && pokemon_type_print->length_effective_against_me==0){
            printf("\n");
        }
        if (pokemon_type_print->length_effective_against_me != 0) {
            printf("\tThese types are super-effective against %s:", pokemon_type_print->name);
            for (int i = 0; i<pokemon_type_print->length_effective_against_me; i++) {
                if (pokemon_type_print->length_effective_against_me - 1 == i) {
                    printf("%s\n", pokemon_type_print->effective_against_me[i]->name);
                    break;

                }
                printf("%s ,", pokemon_type_print->effective_against_me[i]->name);
            }
        }
        if (pokemon_type_print->length_effective_against_others != 0) {
            printf("\t%s moves are super-effective against:", pokemon_type_print->name);
            for (int i = 0; i<pokemon_type_print->length_effective_against_others; i++) {
                if (pokemon_type_print->length_effective_against_others - 1 == i) {
                    printf("%s\n\n", pokemon_type_print->effective_against_others[i]->name);
                    break;

                }
                printf("%s ,", pokemon_type_print->effective_against_others[i]->name);
            }
        }

        return success;

    }


