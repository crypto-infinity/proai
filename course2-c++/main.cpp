#pragma region includes

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

#include "contact.h"
#include "rapidcsv.h"

using namespace std;
using namespace rapidcsv;
using namespace InsuraPro;

#pragma endregion includes

#pragma region main
int main(){
    InsuraPro::Contact* Contact = new InsuraPro::Contact("Mario", "Rossi", "ViaRoma1", "test@email.com", "+393322749965");
    cout << Contact->to_string() << endl;

    /*
    try{
        InsuraPro::Contact* Contacte = new InsuraPro::Contact("Mario", "Rossi", "ViaRoma1", ");
    }
    catch(std::invalid_argument& e){
        cout << "Errore: " << e.what() << endl;
    }
    */
    
    //cout << Contacte->to_csv() << endl;

    // try{
    //     Document doc("contacts.csv", LabelParams(0, 0));
    //     string name = doc.GetCell<string>("name", 2);
    //     cout << name << endl;
    //     doc.SetCell<string>("name", 2, "Giovanni"); -> modifica il valore della cella
    //     doc.Save(); -> salva le modifiche
    // }
    // catch(fstream::failure& e){
    //     cout << "Errore: " << e.what() << endl;
    // }
    


    //vector<string> getRow = doc.GetRow<string>(0);
    //cout << getRow[0] << endl;


    // ifstream file("Contacts.csv");

    // int i = 0;
    // string text;
    // while(getline(file, text)){
    //     cout << text << endl;
    //     i++;
    // }

    
    return 0;
}
#pragma endregion main