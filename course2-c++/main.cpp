#include <bits/stdc++.h>

namespace Math
{
    int i = 3;
    string name = "Paul";

    void inc(int& i){
        i++;
    }
    
}

using namespace std;
using namespace Math;

int main(){
    
    int i = 0;

    inc(i);
    printf("%d",i);
    return 0;
}