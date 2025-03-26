#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"



typedef struct map our_map;
typedef struct point a_point;
typedef struct storage a_storage;


//important functions
a_point* create_point(int origin, int destination);
void add_value(our_map* the_map, int key, int value);
int get_value(our_map* the_map, int key);
struct point {
    int origin;
    int destination;
};


struct map{
    int length;
    int occupied;
    a_storage** a_storage;
    int divisor;

};
our_map *create_map(){
    our_map *new_map = malloc(sizeof(our_map));
    new_map->length=10;
    new_map->a_storage = calloc(new_map->length, sizeof(a_storage*));
    new_map->occupied = 0;
    new_map->divisor = 151;

    return new_map;
    
}

struct storage{
    a_point* stored;
    a_storage* next_storage;
};

a_storage* create_storage(a_point* point){
    a_storage *new = malloc(sizeof(a_storage));
    new->stored=point;
    new->next_storage=NULL;
    return new;
};

void update_tree(our_map* map){
    a_storage** old_list = map->a_storage;
    int old_length = map->length;
    map->a_storage =  calloc(map->length*2,sizeof(a_storage*));
    map->length*=2;
    map->occupied=0;
    
    a_storage* storage;
    a_storage* old_storage = NULL;
    for(int i = 0; i < old_length; i++){
        storage = old_list[i];
        while(storage!=NULL){
            add_value(map, storage->stored->origin, storage->stored->destination);
            old_storage = storage;
            storage= storage->next_storage;
            free(storage);
            
            
        }

    }
    free(old_list);

   
}
int get_value(our_map* the_map, int key){
    a_storage* storage = the_map->a_storage[key%the_map->length];

    while(storage->stored->origin!=key){
        storage = storage->next_storage;

    }
    return storage->stored->destination;
}
void add_value(our_map* the_map, int key, int value ){
    a_point* new_point = create_point(key, value);
    int storage_loc = new_point->origin % the_map->length;
    a_storage**  new_location = &the_map->a_storage[storage_loc];
    while((*new_location)!=NULL){
        new_location = &((*new_location)->next_storage);
    }
    *new_location = create_storage(new_point);
    the_map->occupied++;
    if(the_map->length/2 <the_map->occupied){
        update_tree(the_map);
    }

}
a_point* create_point(int origin, int destination){
    a_point* new_point = malloc(sizeof(a_point));
    new_point->origin = origin;
    new_point->destination = destination;

    return new_point;
}
int main(){
    int startpoints[10] = {9, 16,18,32,48,50,63,74,86,99};
    int end_points[10] = {31,45,64,6, 66, 93,81,22,51,39};
    
    our_map* map = create_map();
    printf("%d", map->length);
    for (int i = 0; i <10; i++){
        printf("%d", map->occupied);

        add_value(map,startpoints[i],end_points[i]);

    }
    for(int i= 0; i < 10; i++){
        printf("%d recieved value %d, %d expected\n",startpoints[i], get_value(map,startpoints[i]), end_points[i]);
    }
    return 0;
     
};