#include "fighter.h"

static FighterClass fighter_class;

// Returns the singleton instance of the class.
FighterClass* get_fighter_class(void) {
    if (fighter_class.copy == NULL) {
        fighter_class.copy = copy_fighter;
        fighter_class.free = free_fighter;
        fighter_class.equal = fighters_equal;
        fighter_class.to_string = fighter_to_string;
        fighter_class.attack = attack_fighter;
        fighter_class.defense = defense_fighter;
    }
    return &fighter_class;
}

// double, double -> Fighter*
// Create a fighter.
Fighter* new_fighter(double sword_quality, double body_strength) {
    Fighter* f = xcalloc(1, sizeof(Fighter));
    f->class = get_fighter_class();
    f->sword_quality = sword_quality;
    f->body_strength = body_strength;
    return f;
}

// Fighter* -> Fighter*
// Create a copy of a fighter.
void* copy_fighter(void* x) {
    Fighter* f = (Fighter*)x;
    return new_fighter(f->sword_quality, f->body_strength);
}

// Fighter* -> void
// Free the memory of a fighter.
void free_fighter(void* x) {
    Fighter* f = (Fighter*)x;
    free(f);
}

// Fighter*, Fighter* -> bool
// Check if two fighters are equal.
bool fighters_equal(void* x, void* y) {
    Fighter* a = (Fighter*)x;
    Fighter* b = (Fighter*)y;
    if (a == b) return true;
    if (a == NULL || b == NULL) return false;
    if (a->class != b->class) return false;
    return a->sword_quality == b->sword_quality && a->body_strength == b->body_strength;
}

// Fighter* -> String
// String representation of fighter.
String fighter_to_string(void* x) {
    Fighter* f = (Fighter*)x;
    String s = xmalloc(128);
    snprintf(s, 128, "Fighter(sword_quality=%g, body_strength=%g)", f->sword_quality, f->body_strength);
    return s;
}

// Fighter* -> double
// Compute the attack strength of the fighter.
double attack_fighter(void* x) {
    Fighter* f = (Fighter*) x;
    double std_attack = 0.9;
    return std_attack * f->body_strength * f->sword_quality; // todo: implement (a)
}

// Fighter* -> double
// Compute the defense strength of the fighter.
double defense_fighter(void* x) {
    //Fighter* f = (Fighter*) x;
    double std_defense = 0.8;
    return std_defense; // todo: implement (a)
}
