// Include statements

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

// main function

int execution(int *i){
    (*i)++;
    return *i;
}

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
    

    int vector[10] = {0,1,2,3,4,5,6,7,8,9};

    double* pointer2 = &pi;

    printf("Pointer: %p", pointer2);

    

    printf("\nIncremented: %d", execution(&i));

    //input
    char array[5];
    printf("\nInput: ");
    fgets(array, sizeof(array) + 1, stdin);
    //gets(array);
    //scanf("%s", array);
    printf("\nIl tuo input: %s", array);

    //files
    FILE *file;
    const char* file_name = "test.txt";

    file = fopen(file_name, "w");

    

    if (file != NULL){
        fprintf(file, "Articolo,Quantità,Prezzo\n", file_name);
        fprintf(file, "%s,%s,%s\n", file_name, file_name, file_name);
        fclose(file);
    }
    else{
        printf("Error reading file %p", file);
    }



    return 0;

}
