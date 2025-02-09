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
    printf("Ciao ciao ciao! Float: %f", f);
    bool flag = true;
    printf("Bool: %s", flag ? "Vero":"falso");
    printf("\nHello!");

    //pointers
    int* pointer = &i;
    printf("Pointer: %d", *pointer);

    //arrays:
    float array_float[1];



    char string[] = "Hello!\0"; // \0 terminator char
    printf("String: %s", string);

    return 0;

}
