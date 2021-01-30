#ifndef WIZARD_H
#define WIZARD_H

#include "base.h"
#include "character.h"

typedef struct WizardClass {
    CopyFun copy;
    FreeFun free;
    EqualFun equal;
    ToStringFun to_string;
    AttackFun attack;
    DefenseFun defense;
} WizardClass;

typedef struct Wizard {
    WizardClass* class;
    double potion_quality;
    double will_strength;
} Wizard;

// Returns the singleton instance of the class.
WizardClass* get_wizard_class(void);

// String, String, int -> Wizard*
// Create a wizard.
Wizard* new_wizard(double potion_quality, double will_strength);

// Wizard* -> Wizard*
// Create a copy of a wizard.
void* copy_wizard(void* x);

// Wizard* -> void
// Free the memory of a wizard.
void free_wizard(void* x);

// Wizard*, Wizard* -> bool
// Check if two wizards are equal.
bool wizards_equal(void* x, void* y);

// Wizard* -> String
// String representation of wizard.
String wizard_to_string(void* x);

// Wizard* -> double
// Compute the attack strength of the wizard.
double attack_wizard(void* x);

// Wizard* -> double
// Compute the defense strength of the wizard.
double defense_wizard(void* x);

#endif
