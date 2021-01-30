// Public interface of token array.

#ifndef TOKEN_ARRAY_H
#define TOKEN_ARRAY_H

// todo: add typedefs and function declarations (including documentation strings) of the public interface of the module

// Represents an instance of a token of a certain type.
typedef struct Token Token;

// Represents an array of tokens.
typedef struct TokenArray TokenArray;

#if 0
struct Token {
    char* value; // '\0'-terminated string, owned by Token
    int type;
};

struct TokenArray {
    int count;
    Token tokens[]; // array of tokens (flexible array member must be last)
};
#endif // 0

// The value of a token.
char* token_value(Token* t);

// The type of a token.
int token_type(Token* t);

// Print a token and its type.
void token_print(Token* t);

// Creates an empty array of the given capacity.
TokenArray* token_array_create(int count);

// Frees the token array, including its values.
void token_array_free(TokenArray* a);

// Sets the value of the token at index. The value must have been dynamically
// allocated with xmalloc/xcalloc. Does not duplicate the value.
// Token array owns the value (i.e., is responsible for deletion).
void token_array_set(TokenArray* a, int index, char* value, int type);

// Returns a pointer to the Token at i (or NULL if i is not a valid index).
Token* token_array_get(TokenArray* a, int index);

// Returns the number of tokens in the array.
int token_array_count(TokenArray* a);

// The index of the token in the array. Returns -1, if token is not in the array.
int token_array_index(TokenArray* a, Token* t);

// Gets the next token of the given type in the index.
// Returns NULL if there is no next element.
Token* token_array_next(TokenArray* a, Token* t);

// Print the array of tokens, one token per line.
void token_array_print(TokenArray* a);

#endif
