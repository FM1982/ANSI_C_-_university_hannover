// Public interface of token index.

#ifndef TOKEN_INDEX_H
#define TOKEN_INDEX_H

#include "token_array.h"

// Represents an index of tokens of a particular type in a token array.
typedef struct TokenIndex TokenIndex;

// Creates an empty index of the given capacity for the given token type.
TokenIndex* token_index_create(TokenArray* a, int token_type);

// Frees the token index, including its values.
void token_index_free(TokenIndex* ti);

// Re-builds the index from the underlying token array.
void token_index_update(TokenIndex* ti);

// Returns a pointer to the Token at position i (or NULL if i is out of range).
Token* token_index_get(TokenIndex* ti, int i);

// Returns the number of tokens in the index.
int token_index_count(TokenIndex* ti);

// Gets the next token of the given type in the index. 
// Returns NULL if there is no next element. 
Token* token_index_next(TokenIndex* ti, Token* t);

// Returns the position (index) of the token in the index. Returns -1, if token is not present.
int token_index_index(TokenIndex* ti, Token* t);

#endif
