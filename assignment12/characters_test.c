// make characters_test && ./characters_test

#include "character.h"
#include "fighter.h"
#include "wizard.h"
#include "object_list.h"

// (c) todo: implement
// Aggregate a list: state is the intermediary aggregation result, element is the current element.
void add_attack(void* state, void* element, int index) {
    double* d = (double*) state;
    Fighter* f = (Fighter*) element;
    *d = *d + f->class->attack(f);
    // implement
}

// (d) todo: implement
// Check whether element satisfies a predicate.
bool is_wizard(void* element, int i, void* x) {
    double val = 1.0;
    Wizard* w = (Wizard*) element; //x;
    if(w->class->attack(w) == val){//o->class->equal((Object*) o, (Wizard*) w)){
        return true;
    }
    else{
        return false;
    }
    //return false; // implement
}

int main(void) {
    base_init();
    base_set_memory_check(true);

    Fighter* f1 = new_fighter(1.2, 3.4);
    Fighter* f2 = new_fighter(4.3, 2.1);
    Wizard* w1 = new_wizard(6.5, 1.1);
    Wizard* w2 = new_wizard(5.4, 2.2);

    // (a) uncomment when you have implemented the respective functions in fighter.c and wizard.c
    double a, d;

    String s1 = f1->class->to_string(f1);
    a = f1->class->attack(f1);
    d = f1->class->defense(f1);
    printf("%s: attack=%.2f, defense=%.2f\n", s1, a, d);
    free(s1);

    // output attack and defense in the same way for f2, w1, and w2
    // ...
    String s2 = f2->class->to_string(f2);
    a = f2->class->attack(f2);
    d = f2->class->defense(f2);
    printf("%s: attack=%.2f, defense=%.2f\n", s2, a, d);
    free(s2);

    String s3 = w1->class->to_string(w1);
    a = w1->class->attack(w1);
    d = w1->class->defense(w1);
    printf("%s: attack=%.2f, defense=%.2f\n", s3, a, d);
    free(s3);

    String s4 = w2->class->to_string(w2);
    a = w2->class->attack(w2);
    d = w2->class->defense(w2);
    printf("%s: attack=%.2f, defense=%.2f\n", s4, a, d);
    free(s4);

    // (b) todo: implement

    Node* list = new_node(f1, new_node(f2, new_node(w1, new_node(w2, NULL))));
    a = 0;
    d = 0;
    for(Node* my_list = list; my_list != NULL; my_list = my_list->next){
        Fighter* f = my_list->value;
        Object* o = my_list->value;
        if(o->class->equal(o, f)){
            a = a + f->class->attack(f);
            d = d + f->class->defense(f);
        }
    }
    printf("group attack = %.2f, group defense = %.2f (using a for-loop)\n", a, d);

    // (c) todo: implement

    a = 0;
    reduce_list(list, add_attack, &a);
    printf("group attack = %.2f (using reduce list)\n", a);

    // (d) todo: implement

    // Produce a list of those elements of list that satisfy the predicate.
    Node* wizards = filter_list(list, is_wizard, NULL);
    println_list(wizards);
    free_list(wizards, false);

    free_list(list, true);

    return 0;
}
