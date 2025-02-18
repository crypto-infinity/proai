#pragma region includes

#include <bits/stdc++.h>

#include "client.h"
#include "rapidcsv.h"

using namespace std;
using namespace InsuraPro;

#pragma endregion includes

#pragma region main
int main(){
    InsuraPro::Client* cliente = new InsuraPro::Client("1", "Mario", "Rossi", "Via Roma 1", "email", "telefono");

    cout << cliente->to_string() << endl;

    cerr << "Test" << endl;
    
    return 0;
}
#pragma endregion main