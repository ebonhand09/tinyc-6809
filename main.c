/**
 * main.c
 * Copyright (c) 2012 David Roper
 * This file is part of 'tinyc'.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define string_buffer_size 1024
#define error_buffer_size 1024

int look; // Lookahead character - int instead of char to ensure EOF is handled properly

/**
 * Error - Report an error to stderr
 */
void Error(char *error) {
    fprintf(stderr, "Error: %s.\n", error);
}

/**
 * Fail - Report an error to stderr and halt
 */
void Fail(char *error) {
    Error(error);
    exit(EXIT_FAILURE);
}

/**
 * GetChar - Read new character from input stream
 */
void GetChar() {
    look = getchar(); // note this is the system getchar()
    if (ferror(stdin)) {
        Fail("Error reading stdin");
    }
    if (feof(stdin)) {
        Error("EOF on stdin");
    }
}

/**
 * Expected - Report what was expected, and halt
 */
void Expected(char *s) {
    char error_buffer[error_buffer_size]; // string storage space
    strncpy(error_buffer, s, error_buffer_size); // copy message s into temporary buffer
    strncat(error_buffer, " Expected", error_buffer_size - strlen(" Expected")); // append rest of message
    Fail(error_buffer);
}

//--- Matchers

/**
 * Match - Match a specific input character
 */
void Match(char c) {
    char err[4] = {"' '"}; // set up error message template, just in case
    if (look == c) {
        GetChar();
    } else {
        err[1] = c; // insert the expected character into the error message
        Expected(err);
    }
}

/**
 * IsAlpha - Recognise an alpha character
 */
int IsAlpha(char c) {
    return isalpha(c); // note this is the system isalpha();
}

/**
 * IsDigit - Recognise a numeric digit character
 */
int IsDigit(char c) {
    return isdigit(c); // note this is the system isalpha();
}

//--- Grabbers

/**
 * GetName - Return an identifier
 */
char GetName() {
    char value = 0;
    if (!IsAlpha(look)) {
        Expected("Name");
    } else {
        value = toupper(look);
        GetChar();
    }
    return value;
}

/**
 * GetNum - Return a digit
 */
char GetNum() {
    char value;
    if (!IsDigit(look)) {
        Expected("Integer");
    }
    value = look;
    GetChar();
    return value;
}

//--- Emitters

/**
 * Emit - Output a string with a leading \t character
 */
void Emit(char *s) {
    printf("\t%s", s);
}

/**
 * EmitLn - Output a string followed by \n
 */
void EmitLn(char *s) {
    printf("\t%s\n", s);
}

/**
 * Init - Call any get-started functions
 */
void Init() {
    GetChar();
}

/**
 * Main - Set up environment and go
 */
int main (int argc, const char * argv[]) {
    Init();
    return 0;
}
