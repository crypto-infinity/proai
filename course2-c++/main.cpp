#include <bits/stdc++.h>
using namespace std;

namespace Math
{

    struct complex{
        string nome;
        string cognome;
    };

    int i = 3;
    string name = "Paul";

    void inc(int& i){
        i++;
    }
    
    void print_with_cout(){
        cout << "Hello There!";
    }

    complex print_struct(){
        struct complex struct1;
        struct1.nome = "Hello There";
        return struct1;
    }
}


using namespace Math;

int main(){
    
    int i = 0;

    inc(i);
    printf("%d",i);
    return 0;
}