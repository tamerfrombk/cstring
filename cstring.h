#pragma once

#include <stdbool.h>
#include <stdlib.h>

// allocates a string buffer with enough memory for len characters 
// __and__ a null terminating character.
// This means the length of the returned buffer, if not null, will be len + 1.
// This function will also null-terminate the string buffer for you.
// If a buffer could not be acquired, NULL will be returned.
char* cstr_alloc(size_t len);

// Appends up to count characters from the src string into the
// dest buffer and null terminate the destination buffer.
// To append the entire string, either pass in the length
// of the src string if it is known or 0.
// The dest_hint parameter is the size of the dest buffer if it is known. Pass
// in the length of the dest buffer if it is known or 0 to have the function figure it out.
// If the length of the dest buffer is known, this can cause potential performance gains
// since the function can immediately figure out where to start copying into the destination.
// This function expects that dest contains enough memory to hold all of
// the characters requested from src and that src and dest point to the beginning of valid string buffers.
// The function returns the number of characters actually appended to the string. 
size_t cstr_app(char *dest, const char *src, size_t count, size_t dest_hint);

// Determines if pre is a prefix of the string pointed to by base.
// This function expects that pre and base point to the beginning of valid string buffers.
bool cstr_is_prefix(const char *base, const char *pre);

// Returns a pointer to the first occurrence of str in base.
// If str is not found anywhere in base, NULL is returned.
char* cstr_find(const char *base, const char *str);

// A convenience function that returns whether str occurs in base.
// If str is not found anywhere in base, the function returns false.
// Note that this is the same as doing the following:
//     cstr_find("foo", "bar") != NULL
bool cstr_contains(const char *base, const char *str);

// Returns a pointer to a string that contains a copy of up to 
// count characters from the src string. The pointer points to a dynamically
// allocated string and the client is responsible for managing it. 
// If a copy of the full string is requested, pass in 0 for the count.
// This function expects that str points to a valid null-terminated string buffer.
char* cstr_copy(const char *str, size_t count);

// Splits the str string via the token string and updates toks to an array of tokens
// and count with the number of tokens returned.
// Note that the toks parameter will be updated with dynamically allocated memory
// which the client is responsible for handling after the function call.
// If the function fails to allocate memory at any point, the function will return
// false but will still update the toks and count parameters with as many strings
// as it could handle before failing. This means that if the function returns true,
// it guarantees that the token list is complete. If the function returns false,
// the token list is probably incomplete. See below for example usage.
// The function expects that all parameters point to valid addresses.
// Example:
//    char **tokens = NULL;
//    size_t num = 0;
//    if (!cstr_split("this is a sentence", " ", &tokens, &num)) {
//          LOG_WARN("Couldn't handle a memory request. TOken list incomplete");
//    }
//    for (size_t i = 0; i < num; ++i) {
//        puts(tokens[i]);
//        free(tokens[i]);
//    }
//    free(tokens);
bool cstr_split(const char *str, const char *token, char ***toks, size_t *count);
