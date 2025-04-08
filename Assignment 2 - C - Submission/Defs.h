//
// Created by omrih on 29/01/2024.
//

#ifndef HOMEWORK2_DEFS_H
#define HOMEWORK2_DEFS_H




#include <stdio.h>
#include <stdlib.h>


typedef enum e_bool {false,true} bool;
typedef enum e_status {success,failure} status ;

typedef enum
{
    POKEMON_NAME_ARG = 0,
    POKEMON_SPICIES_ARG = 1,
    POKEMON_HEIGHT_ARG = 2,
    POKEMON_WEIGHT_ARG = 3,
    POKEMON_ATTACK_ARG = 4,
    POKEMON_TYPE_ARG = 5,
}POKEMON_ARG;


#endif //HOMEWORK2_DEFS_H
