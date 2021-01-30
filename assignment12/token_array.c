#include "base.h"
#include "token_array.h"

// todo: add structure definitions and function definitions of the module

#if 1
struct Token {
    char* value; // '\0'-terminated string, owned by Token
    int type;
};

struct TokenArray {
    int count;
    Token tokens[]; // array of tokens (flexible array member must be last)
};
#endif // 0

// API functions for Token.

// The value of a token.
char* token_value(Token* t) {
    return t->value;
}

// The type of a token.
int token_type(Token* t) {
    return t->type;
}

// Print a token and its type.
void token_print(Token* t) {
    printf("%s (%d)\n", t->value, t->type);
}

// API functions for TokenArray.

// todo: explain how this function works
/*
*   It returns a TokenArray with the size of a Token and its count.
*   It reserves this memory in dynamic storage and sets each byte
*   to 0.
*/
// Creates an empty array of the given capacity.
TokenArray* token_array_create(int count) {
    if (count < 0) {
        printf("invalid count: %d\n", count);
        exit(1);
    }
    int n = sizeof(TokenArray) + count * sizeof(Token);
    TokenArray* a = xmalloc(n);
    memset(a, 0, n); // set each byte to 0
    a->count = count;
    return a;
}

// Frees the token array, including its values.
void token_array_free(TokenArray* a) {
    if (a == NULL) return;
    for (int i = 0; i < a->count; i++) {
        Token* t = a->tokens + i;
        if (t->value) free(t->value);
    }
    free(a);
}

// Sets the value of the token at index. The value must have been dynamically
// allocated with xmalloc/xcalloc. Does not duplicate the value.
// Token array owns the value (i.e., is responsible for deletion).
void token_array_set(TokenArray* a, int index, char* value, int type) {
    if (index < 0 || index >= a->count) return;
    Token* t = a->tokens + index;
    t->value = value;
    t->type = type;
}

// Returns a pointer to the Token at i (or NULL if i is not a valid index).
Token* token_array_get(TokenArray* a, int index) {
    if (index < 0 || index >= a->count) return NULL;
    return a->tokens + index;
}

// Returns the number of tokens in the array.
int token_array_count(TokenArray* a) {
    return a->count;
}

// The index of the token in the array. Returns -1, if token is not in the array.
int token_array_index(TokenArray* a, Token* t) {
    int i = t - a->tokens;
    if (i < 0 || i >= a->count) return -1;
    return i;
}

// Gets the next token of the given type in the index.
// Returns NULL if there is no next element.
Token* token_array_next(TokenArray* a, Token* t) {
    if (t == NULL) return NULL;
    int i = t - a->tokens;
    if (i < 0 || i >= a->count - 1) return NULL;
    return t + 1;
}

// Print the array of tokens, one token per line.
void token_array_print(TokenArray* a) {
    for (int i = 0; i < a->count; i++) {
        Token* t = a->tokens + i;
        token_print(t);
    }
}
