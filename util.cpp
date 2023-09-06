#include <stdio.h>
#include <string.h>
#include "util.h"

// Function to read the next instruction from the user with input validation
int nextInstruction(char *Word, double *Key) {
    int returnV;

    std::cout << "a)nimate, t)ick, s)creenshot, q)uit?";
    std::cin >> Word;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (strcmp(Word, "a") == 0) return 1;
    if (strcmp(Word, "t") == 0) return 1;
    if (strcmp(Word, "s") == 0) return 1;
    if (strcmp(Word, "q") == 0) return 1;

    return 0;
}
