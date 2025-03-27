typedef struct map our_map;


our_map* create_map();
void add_value(our_map* the_map, int key, int value);
int get_value(our_map* the_map, int key);