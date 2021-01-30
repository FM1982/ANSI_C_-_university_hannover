#ifndef CHARACTER_H
#define CHARACTER_H

#include "base.h"
#include "object.h"

typedef double (*AttackFun)(void* x);
typedef double (*DefenseFun)(void* x);

typedef struct CharacterClass {
    CopyFun copy;
    FreeFun free;
    EqualFun equal;
    ToStringFun to_string;
    AttackFun attack;
    DefenseFun defense;
} CharacterClass;

typedef struct Character {
    CharacterClass* class;
} Character;

#endif
