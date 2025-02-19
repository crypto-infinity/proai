#pragma region includes

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

// includes each class header file
#include "crm.h"

using namespace std;
using namespace InsuraPro;

#pragma endregion includes

#pragma region main
/// @brief Main program loop, handles program execution
/// @return 
int main(){

    InsuraPro::CRM* crm = new InsuraPro::CRM();

    #pragma region command_inputs
    string cmd = "";
    map<string, int> cmd_inputs; 

    cmd_inputs["supporto"] = 1; 
    cmd_inputs["aggiunta_cliente"] = 2; 
    cmd_inputs["mostra_clienti"] = 3; 
    cmd_inputs["modifica_cliente"] = 4;
    cmd_inputs["elimina_cliente"] = 5;
    cmd_inputs["interazione"] = 6;
    cmd_inputs["mostra_interazioni"] = 7;
    cmd_inputs["chiudi"] = 8;

    cmd_inputs["1"] = 1;
    cmd_inputs["2"] = 2;
    cmd_inputs["3"] = 3;
    cmd_inputs["4"] = 4;
    cmd_inputs["5"] = 5;
    cmd_inputs["6"] = 6;
    cmd_inputs["7"] = 7;
    cmd_inputs["8"] = 8;
    #pragma endregion command_inputs

    try
    {
        cout << "Benvenuto nel sistema CRM avanzato di InsuraPro!" << endl;
        Utility::show_help();
        
        while(cmd != "chiudi" || cmd != "8"){
            cout << "\nCosa vuoi fare? (\"supporto\" o \"1\" per mostrare tutte le funzioni): ";
            cin >> cmd;

            switch (cmd_inputs[cmd])
            {
            case 1:
                Utility::show_help();
                break;
            case 2:
                //crm->add_client();
                break;
            case 3:
                //crm->view_clients();
                break;
            case 4:
                //crm->update_client();
                break;
            case 5:
                //crm->delete_client();
                break;
            case 6:
                //crm->add_interaction();
                break;
            case 7:
                //crm->view_interactions();
                break;
            case 8:
                cout << "\nGrazie per aver usato InsuraPro, a presto!" << endl;
                break;
            default:
                cout << "\nComando non riconosciuto." << endl;
                Utility::show_help();
                break;
            }
        }
    }
    catch(exception& e)
    {
        cout << "Si è verificato un errore: " << e.what() << ". Chiudi il programma e riprova" << endl;
    }
    
    return 0;
}
#pragma endregion main

    
    // InsuraPro::Contact* Contact = new InsuraPro::Contact("Mario", "Rossi", "ViaRoma1", "test@email.com", "+393322749965");
    // cout << Contact->to_string() << endl;

    /*
    try{
        InsuraPro::Contact* Contacte = new InsuraPro::Contact("Mario", "Rossi", "ViaRoma1", ");
    }
    catch(std::invalid_argument& e){
        cout << "Errore: " << e.what() << endl;
    }
    */
    
    //cout << Contact->to_csv() << endl;

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