// Include statements

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

// main function

int main(){

    printf("Ciao Gabriele!\n");
    printf("Ciao per 2!");

    //data types
    int i = 0;
    printf("\nCiao per: %d", i);
    float f = 0.8997;
    printf("\nCiao ciao ciao! Float: %f", f);
    bool flag = true;
    printf("\nBool: %s", flag ? "Vero":"falso");
    printf("\nHello!");

    //pointers
    int* pointer = &i;
    printf("\nPointer: %d", *pointer);

    //arrays:
    float array_float[1];



    char string[] = "Hello There!"; // \0 terminator char
    printf("\nString: %s, dimensione: %d", string, sizeof(string));

    double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089; //ca 20 cifre decimali

    printf("\nPI: %.1000f, dimensione: %d", pi, sizeof(pi));
    return 0;

}
