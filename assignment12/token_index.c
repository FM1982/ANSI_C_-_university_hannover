#include "base.h"
#include "token_array.h"
#include "token_index.h"

// todo: implement the functions of the module
// todo: OK to change structure definition, if you want

 struct TokenIndex {
    TokenArray* array; // does not own the array, i.e., does not need to free it
    int* token2type; // owner, converts token index to index of type token
    int* type2token; // owner, converts type index to corresponding token index
    int type; // type of token that this index considers
    int count; // number of tokens of the given type, number of elements in type2token
};

#if 0
static int count_tokens_of_type(TokenArray* a, int type) {
    int result = 0;
    int n = token_array_count(a);
    for (int i = 0; i < n; i++) {
        Token* t = token_array_get(a, i);
        if (token_type(t) == type) result++;
    }
    return result;
}
#endif

TokenIndex* token_index_create(TokenArray* a, int token_type) {
    return NULL;
}

void token_index_free(TokenIndex* ti) {
}

void token_index_update(TokenIndex* ti) {
}

Token* token_index_get(TokenIndex* ti, int index) {
    return NULL;
}

int token_index_count(TokenIndex* ti) {
    return 0;
}

Token* token_index_next(TokenIndex* ti, Token* t) {
    return NULL;
}

int token_index_index(TokenIndex* ti, Token* t) {
    return -1;
}

