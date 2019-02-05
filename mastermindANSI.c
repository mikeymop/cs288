/* Program mastermind.c
Emulates the old Mastermind codebreaking game.
Run the game with a 4 character argument.
Define the difficulty and number of guesses
before compiling.

Michael A. DeFrancesco II, NJIT, Feb 4, 2019
*/
/*
enum Color {
    B = "Blue",
    G = "Green",
    O = "Orange",
    P = "Purple",
    R = "Red",
    Y = "Yellow"
}
*/
#include <stdio.h>

#define MAX_GUESSES 12;
#define DIFFICULTY 4;

/* return 1 if a is in array b, 0 if not */
int isIn(char a, char* b) {
    int i;
    for(i = 0; b[i] != '\0'; i++) {
        if(a == b[i]) return 1;
    }
    return 0;
}
/* DONT NEED
*  check if char a is in array b, return the occurance */
int idxCt(char a, char* b) {
    int i, count = 0;
    for(i=0; b[i] != '\0'; i++) {
        if(a == b[i]) count++;
    }
    return count;
}
/*returns the number hits */
int testCode(char* c, char* g, int nG, int nPos, int nExist) {
    /* take the color code into c */
    int i = 0;
    for(i=0; g[i]!= '\0'; i++) {
        if(c[i] == g[i]) nPos++;
        else if(isIn(c[i], g)) nExist++;
        /*(c[i] == g[i]) ? nPos++ : (!isIn(c[i], g)) ?: nExist++;
        see: http://gg.gg/ternaryC */
    }
    nG = nG - 1;
    printf("%8sFeedback: %d, %d\n","", nPos, nExist);
    return nPos;
};

void prompt(char* guess, int tries) {
    printf("\nNo. Guesses Left: %d", tries);
    printf("\nEnter your guess: ");
    scanf("%5s", guess); /* synonym to &guess[0] */
}

int main(int argc, char *argv[]) {

    int diff = DIFFICULTY;
    int tries = MAX_GUESSES;
    int numPosition = 0;
    int numExisting = 0;
    char guess[tries+1];
    char *code = NULL;

    if(argc < 2) {
        printf("Please pick a four-color code using the provided colors\n");
        return 1;
    } else if(argc == 2) { code = argv[1]; }

    printf("Available colors: (B)lue (G)reen (O)range (P)urple (R)ed (Y)ellow\n");

    while (tries > 0) {
        prompt(guess, tries);
        if(testCode(code, guess, tries, numPosition, numExisting) == diff) {
            printf("YOU WIN!\n");
            return 0;
        }
        --tries;
    }
    printf("YOU LOSE! The code is %s\n", code);
    return 0;
}