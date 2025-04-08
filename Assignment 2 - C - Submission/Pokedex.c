//
// Created by omrih on 29/01/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pokemon.h"
#include <ctype.h>



FILE* open_file(const char *filename)
{
    FILE *fp = fopen(filename, "r"); // Open the file in read mode ("r")
    if (fp == NULL)
    {
        perror("Error opening file");
        return NULL;
    }
    return fp;
}
//-------------------------------------------------------------------------------------------
void remove_spaces(char* str)
{
    char *dst = str;
    while (*str != '\0')
    {
        if (!isspace(*str))
        {
            *dst++ = *str;
        }
        str++;
    }
    *dst = '\0';
}
//-------------------------------------------------------------------------------------------

void remove_tabs(char* str)
{
    char *dst = str;
    while (*str != '\0')
    {
        if ('\t'!=(*str) && '\n'!=(*str))
        {
            *dst++ = *str;
        }
        str++;
    }
    *dst = '\0';
}
//-------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------

/**
 * Reads Pokemon types from a file and initializes the array of Pokemon types in the Pokemon_Info struct.
 *
 * @param file Pointer to the file containing Pokemon types.
 * @param info Pointer to the Pokemon_Info struct to be populated.
 */

void handle_pokemon_types(FILE *file , Pokemon_Info *info){
    if(file==NULL || info==NULL){
        return;
    }

    char bufer[300];
    char *token;
    int size=0;
    while (fgets(bufer, sizeof(bufer), file) != NULL) {
        remove_spaces(bufer);
        token = strtok(bufer, ",");
        while( token != NULL ) {
            info->poiner_to_pokemon_type_array[size]=create_pokemon_type(token);
            if(info->poiner_to_pokemon_type_array[size]==NULL){
                printf("Memory problem");
                exit(0);
            }
            size++;
            token = strtok(NULL, ",");
        }
        return;
    }
}
//-------------------------------------------------------------------------------------------
/**
 * Finds and returns a pointer to a Pokemon type with the specified name from the given Pokemon_Info.
 *
 * @param pokemon_info Pointer to the Pokemon_Info struct containing Pokemon types.
 * @param name The name of the Pokemon type to search for.
 * @return A pointer to the found Pokemon type, or NULL if not found.
 */

Pokemon_type * find_obj_to_insert(Pokemon_Info *pokemon_info,char *name){
    if(pokemon_info==NULL || name==NULL){
        return NULL;
    }

    for(int i=0;i<pokemon_info->number_of_types_pokemon;i++){
        if(strcmp(name,pokemon_info->poiner_to_pokemon_type_array[i]->name)==0){
            return pokemon_info->poiner_to_pokemon_type_array[i];
        }
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------
/**
 * Divides the classes of Pokemon types based on their effectiveness relationships.
 *
 * @param info Pointer to the Pokemon_Info struct containing Pokemon types.
 * @param type_to_insert_array_effective Array containing names of types with effectiveness relationships.
 * @param type_pokemon_to_get Pointer to the Pokemon type to which effectiveness relationships will be added.
 * @param class_name The class name indicating the type of effectiveness relationship.
 */

void divide_class(Pokemon_Info* info, char *type_to_insert_array_effective,Pokemon_type *type_pokemon_to_get,char *class_name)
{
    if(info==NULL || type_to_insert_array_effective==NULL || type_pokemon_to_get==NULL || class_name==NULL){
        return;
    }

    char *effective_me="effective-against-me";
    Pokemon_type *obj_insert;
    type_to_insert_array_effective = strtok(NULL, ",");
    while( type_to_insert_array_effective != NULL ) {
        remove_spaces(type_to_insert_array_effective);
        obj_insert=find_obj_to_insert(info,type_to_insert_array_effective);
        if(strcmp(class_name,effective_me)==0) {
            add_effective_against_me(type_pokemon_to_get, obj_insert);
        }
        else {
            add_effective_against_others(type_pokemon_to_get, obj_insert);
        }
        type_to_insert_array_effective = strtok(NULL, ",");
    }
}

//-------------------------------------------------------------------------------------------
/**
 * Handles the effectiveness relationships between Pokemon types read from a file.
 *
 * @param file Pointer to the file containing effectiveness relationships.
 * @param pokemon_info Pointer to the Pokemon_Info struct to be updated.
 */

void handle_pokemon_effective(FILE *file , Pokemon_Info* pokemon_info){
    if(file==NULL || pokemon_info==NULL){
        return;
    }

    Pokemon_type *insert_type_obj;
    char bufer[300];
    char *type_to_insert;

    char *class_effective;
    while (fgets(bufer, sizeof(bufer), file) != NULL) {
        if(bufer[0] != '\t')
        {
            return;
        }
       remove_tabs(bufer);
        type_to_insert = strtok(bufer, " ");
        class_effective = strtok(NULL, ":");
        insert_type_obj=find_obj_to_insert(pokemon_info ,type_to_insert);
        //TODOOO if null exit
        divide_class(pokemon_info,type_to_insert,insert_type_obj,class_effective);

    }
}
//-------------------------------------------------------------------------------------------
/**
 * Handles the insertion of a Pokemon into the Pokemon_Info struct based on the provided information.
 *
 * @param info Pointer to the Pokemon_Info struct to be updated.
 * @param buffer String containing the information of the Pokemon to be inserted.
 * @param index Index at which the Pokemon will be inserted into the array of Pokemon pointers.
 */

void handel_insert_pokemon(Pokemon_Info *info,char *buffer,int index ){
    if(info==NULL || buffer==NULL){
        return;
    }
    Pokemon_type *type;
    Pokemon_bio_data *bio_data;
    char *args[6];
    char *token;
    int i=0;
    token = strtok(buffer, ",");
    while( token != NULL ) {
        args[i]=token;
        i++;
        token = strtok(NULL, ",");

    }
    int attack=atoi(args[POKEMON_ATTACK_ARG]);
    float wight=atof(args[POKEMON_WEIGHT_ARG]);
    float hight=atof(args[POKEMON_HEIGHT_ARG]);
    bio_data= create_pokemon_bio_data(hight,attack,wight);
    if(bio_data==NULL){
        printf("Memory problem");
        exit(0);
    }
    type= find_obj_to_insert(info,args[POKEMON_TYPE_ARG]);
    info->poiner_to_pokemon_array[index]=create_pokemon(args[POKEMON_NAME_ARG],args[POKEMON_SPICIES_ARG],bio_data,type);
    if(info->poiner_to_pokemon_array[index]==NULL){
        printf("Memory problem");
        exit(0);
    }
}
//-------------------------------------------------------------------------------------------


void print_menu(){
    printf("Please choose one of the following numbers:\n");
    printf("1 : Print all Pokemons\n");
    printf("2 : Print all Pokemons types\n");
    printf("3 : Add type to effective against me list\n");
    printf("4 : Add type to effective against others list\n");
    printf("5 : Remove type from effective against me list\n");
    printf("6 : Remove type from effective against others list\n");
    printf("7 : Print Pokemon by name\n");
    printf("8 : Print Pokemons by type\n");
    printf("9 : Exit\n");
}
//-------------------------------------------------------------------------------------------

void case_3(Pokemon_Info *info){
    if(info==NULL){
        return;
    }
    char name_source_a_insert[300];
    char name_source_b[300];
    Pokemon_type *my_tpye_souce_a;
    Pokemon_type *my_tpye_souce_b;
    printf("Please enter type name:\n");
    scanf("%s",name_source_a_insert);
    my_tpye_souce_a=find_obj_to_insert(info,name_source_a_insert);
    if(my_tpye_souce_a==NULL){
        printf("Type name doesn't exist.\n");
        return;
    }

    printf("Please enter type name to add to %s effective against me list:\n", name_source_a_insert);
    scanf("%s", name_source_b);
    my_tpye_souce_b = find_obj_to_insert(info, name_source_b);
    if (my_tpye_souce_b == NULL) {
        printf("Type name doesn't exist.\n");
        return;
    }
    if(add_effective_against_me(my_tpye_souce_a,my_tpye_souce_b)==false){
        printf("This type already exist in the list.\n");
        return;
    }
    print_type_pokemon(my_tpye_souce_a);

}
//-------------------------------------------------------------------------------------------

void case_4(Pokemon_Info *info) {
    if(info==NULL){
        return;
    }
    char name_source_a_insert[300];
    char name_source_b[300];
    Pokemon_type *my_tpye_souce_a;
    Pokemon_type *my_tpye_souce_b;
    printf("Please enter type name:\n");
    scanf("%s",name_source_a_insert);
    my_tpye_souce_a=find_obj_to_insert(info,name_source_a_insert);
    if(my_tpye_souce_a==NULL){
        printf("Type name doesn't exist.\n");
        return;
    }

    printf("Please enter type name to add to %s effective against others list:\n", name_source_a_insert);
    scanf("%s", name_source_b);
    my_tpye_souce_b = find_obj_to_insert(info, name_source_b);
    if (my_tpye_souce_b == NULL) {
        printf("Type name doesn't exist.\n");
        return;
    }
    if(add_effective_against_others(my_tpye_souce_a,my_tpye_souce_b)==false){
        printf("This type already exist in the list.\n");
        return;
    }
    print_type_pokemon(my_tpye_souce_a);

}
//-------------------------------------------------------------------------------------------

void case_5(Pokemon_Info *info) {
    if(info==NULL){
        return;
    }
    char name_source_a_insert[300];
    char name_source_b[300];
    Pokemon_type *my_tpye_souce_a;
    printf("Please enter type name:\n");
    scanf("%s",name_source_a_insert);
    my_tpye_souce_a=find_obj_to_insert(info,name_source_a_insert);
    if(my_tpye_souce_a==NULL){
        printf("Type name doesn't exist.\n");
        return;
    }
    printf("Please enter type name to remove from %s effective against me list:\n", name_source_a_insert);
    scanf("%s", name_source_b);


    if(remove_effective_against_me(my_tpye_souce_a,name_source_b)==failure){
        printf("Type name doesn't exist in the list.\n");
        return;
    }
    print_type_pokemon(my_tpye_souce_a);


}

//-------------------------------------------------------------------------------------------

void case_6(Pokemon_Info *info) {
    if(info==NULL){
        return;
    }
    char name_source_a_insert[300];
    char name_source_b[300];
    Pokemon_type *my_tpye_souce_a;
    printf("Please enter type name:\n");
    scanf("%s",name_source_a_insert);
    my_tpye_souce_a=find_obj_to_insert(info,name_source_a_insert);
    if(my_tpye_souce_a==NULL){
        printf("Type name doesn't exist.\n");
        return;
    }
    printf("Please enter type name to remove from %s effective against others list:\n", name_source_a_insert);
    scanf("%s", name_source_b);


    if(remove_effective_against_others(my_tpye_souce_a,name_source_b)==failure){
        printf("Type name doesn't exist in the list.\n");
        return;
    }
    print_type_pokemon(my_tpye_souce_a);

}

void case_7(Pokemon_Info *info) {
    if(info==NULL){
        return;
    }
    printf("Please enter Pokemon name:\n");
    char buferr[300];
    scanf("%s",buferr);
    for(int i=0;i<info->number_of_pokemon;i++){
        if(strcmp(buferr,info->poiner_to_pokemon_array[i]->name)==0){
            print_pokemon(info->poiner_to_pokemon_array[i]);
            return;
        }

    }
    printf("The Pokemon doesn't exist.\n");


}

//-------------------------------------------------------------------------------------------

void case_8(Pokemon_Info *info) {
    if(info==NULL){
        return;
    }
    printf("Please enter type name:\n");
    char buferr[300];
    scanf("%s", buferr);
    Pokemon_type *type = NULL;
    type = find_obj_to_insert(info, buferr);
    if (type == NULL) {
        printf("Type name doesn't exist.\n");
        return;
    }
    for (int i = 0; i < info->number_of_pokemon; i++) {
        if (strcmp(buferr, info->poiner_to_pokemon_array[i]->type->name) == 0) {
            printf("There are %d Pokemons with this type:\n",
                   info->poiner_to_pokemon_array[i]->type->number_of_pokemon);
            break;
        }
    }

        for (int i = 0; i < info->number_of_pokemon; i++) {
            if (strcmp(buferr, info->poiner_to_pokemon_array[i]->type->name) == 0) {
                print_pokemon(info->poiner_to_pokemon_array[i]);
            }

        }

    }

//-------------------------------------------------------------------------------------------

void clean_memory(Pokemon_Info *info){
    if(info==NULL){
        return;
    }

for(int i=0;i<info->number_of_pokemon;i++){
    free(info->poiner_to_pokemon_array[i]->name);
    free(info->poiner_to_pokemon_array[i]->bio);
    free(info->poiner_to_pokemon_array[i]->species);
    free(info->poiner_to_pokemon_array[i]);
}
for(int i=0;i<info->number_of_types_pokemon;i++){
    free(info->poiner_to_pokemon_type_array[i]->name);
    free(info->poiner_to_pokemon_type_array[i]->effective_against_others);
    free(info->poiner_to_pokemon_type_array[i]->effective_against_me);
    free(info->poiner_to_pokemon_type_array[i]);
}
    free(info->poiner_to_pokemon_array);
    free(info->poiner_to_pokemon_type_array);
}

//-------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {

    Pokemon_Info pokemon_info;


    int index_2=0;
    char *key_word_Types="Types";
    pokemon_info.number_of_types_pokemon = atoi(argv[1]);
    pokemon_info.number_of_pokemon = atoi(argv[2]);
    FILE *date_file=open_file(argv[3]);
    char bufer[300];
    pokemon_info.poiner_to_pokemon_type_array =(Pokemon_type **) malloc(pokemon_info.number_of_types_pokemon* sizeof(Pokemon_type*));
    if(pokemon_info.poiner_to_pokemon_type_array ==NULL){
        printf("Memory problem");
        exit(0);
    }
    pokemon_info.poiner_to_pokemon_array =(Pokemon **) malloc(pokemon_info.number_of_pokemon* sizeof(Pokemon*));
    if(pokemon_info.poiner_to_pokemon_array ==NULL){
        printf("Memory problem");
        exit(0);
    }
    while (fgets(bufer, sizeof(bufer), date_file) != NULL) {
        remove_spaces(bufer);
        if(strcmp(bufer,key_word_Types)==0){
            handle_pokemon_types(date_file,&pokemon_info);
            handle_pokemon_effective(date_file, &pokemon_info);
            continue;
        }
        // pokemon
        //handel_insert_pokemon(**)

        handel_insert_pokemon(&pokemon_info,bufer,index_2);
        index_2++;
    }
    while (true) {
        print_menu();
        int number_chose;
        int result = scanf("%d", &number_chose);
        if (result != 1) {
            printf("Please choose a valid number.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            continue; // Skip to the next iteration of the loop
        }
        //scanf("%d", &number_chose);
        switch (number_chose) {
            case 1:
                for (int i = 0; i < pokemon_info.number_of_pokemon; i++) {
                    print_pokemon(pokemon_info.poiner_to_pokemon_array[i]);
                }
                break;
            case 2:
                for (int i = 0; i < pokemon_info.number_of_types_pokemon; i++) {
                    print_type_pokemon(pokemon_info.poiner_to_pokemon_type_array[i]);
                }
                break;
            case 3:
                case_3(&pokemon_info);
                break;
            case 4:
                case_4(&pokemon_info);
                break;
            case 5:
                case_5(&pokemon_info);
                break;
            case 6:
                case_6(&pokemon_info);
                break;
            case 7:
                case_7(&pokemon_info);
                break;
            case 8:
                case_8(&pokemon_info);
                break;
            case 9:
                clean_memory(&pokemon_info);
                fclose(date_file);
                printf("All the memory cleaned and the program is safely closed.\n");
                return 0;
            default:
                printf("Please choose a valid number.\n");
                break;
        }

    }

}