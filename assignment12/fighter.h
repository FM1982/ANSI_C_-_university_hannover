#ifndef FIGHTER_H
#define FIGHTER_H

#include "base.h"
#include "character.h"

typedef struct FighterClass {
    CopyFun copy;
    FreeFun free;
    EqualFun equal;
    ToStringFun to_string;
    AttackFun attack;
    DefenseFun defense;
} FighterClass;

typedef struct Fighter {
    FighterClass* class;
    double sword_quality;
    double body_strength;
} Fighter;

// Returns the singleton instance of the class.
FighterClass* get_fighter_class(void);

// String, String, int -> Fighter*
// Create a fighter.
Fighter* new_fighter(double sword_quality, double body_strength);

// Fighter* -> Fighter*
// Create a copy of a fighter.
void* copy_fighter(void* x);

// Fighter* -> void
// Free the memory of a fighter.
void free_fighter(void* x);

// Fighter*, Fighter* -> bool
// Check if two fighters are equal.
bool fighters_equal(void* x, void* y);

// Fighter* -> String
// String representation of fighter.
String fighter_to_string(void* x);

// Fighter* -> double
// Compute the attack strength of the fighter.
double attack_fighter(void* x);

// Fighter* -> double
// Compute the defense strength of the fighter.
double defense_fighter(void* x);

#endif
