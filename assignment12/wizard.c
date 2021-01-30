#include "wizard.h"

static WizardClass wizard_class;

// Returns the singleton instance of the class.
WizardClass* get_wizard_class(void) {
    if (wizard_class.copy == NULL) {
        wizard_class.copy = copy_wizard;
        wizard_class.free = free_wizard;
        wizard_class.equal = wizards_equal;
        wizard_class.to_string = wizard_to_string;
        wizard_class.attack = attack_wizard;
        wizard_class.defense = defense_wizard;
    }
    return &wizard_class;
}

// double, double -> Wizard*
// Create a wizard.
Wizard* new_wizard(double potion_quality, double will_strength) {
    Wizard* w = xcalloc(1, sizeof(Wizard));
    w->class = get_wizard_class();
    w->potion_quality = potion_quality;
    w->will_strength = will_strength;
    return w;
}

// Wizard* -> Wizard*
// Create a copy of a wizard.
void* copy_wizard(void* x) {
    Wizard* w = (Wizard*)x;
    return new_wizard(w->potion_quality, w->will_strength);
}

// Wizard* -> void
// Free the memory of a wizard.
void free_wizard(void* x) {
    Wizard* w = (Wizard*)x;
    free(w);
}

// Wizard*, Wizard* -> bool
// Check if two wizards are equal.
bool wizards_equal(void* x, void* y) {
    Wizard* a = (Wizard*)x;
    Wizard* b = (Wizard*)y;
    if (a == b) return true;
    if (a == NULL || b == NULL) return false;
    if (a->class != b->class) return false;
    return a->potion_quality == b->potion_quality && a->will_strength == b->will_strength;
}

// Wizard* -> String
// String representation of wizard.
String wizard_to_string(void* x) {
    Wizard* w = (Wizard*)x;
    String s = xmalloc(128);
    snprintf(s, 128, "Wizard(potion_quality=%g, will_strength=%g)", w->potion_quality, w->will_strength);
    return s;
}

// Wizard* -> double
// Compute the attack strength of the wizard.
double attack_wizard(void* x) {
    //Wizard* w = (Wizard*) x;
    double std_attack = 1.0;
    return std_attack; // todo: implement (a)
}

// Wizard* -> double
// Compute the defense strength of the wizard.
double defense_wizard(void* x) {
    Wizard* w = (Wizard*)x;
    double std_defense = 0.5;
    return std_defense * w->potion_quality * (w->will_strength * w->will_strength); // todo: implement (a)
}
