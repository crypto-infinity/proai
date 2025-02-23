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
    cmd_inputs["ricerca_cliente"] = 6;
    cmd_inputs["interazione"] = 7;
    cmd_inputs["mostra_interazioni"] = 8;
    cmd_inputs["cerca_interazioni"] = 9;
    cmd_inputs["chiudi"] = 10;

    cmd_inputs["1"] = 1;
    cmd_inputs["2"] = 2;
    cmd_inputs["3"] = 3;
    cmd_inputs["4"] = 4;
    cmd_inputs["5"] = 5;
    cmd_inputs["6"] = 6;
    cmd_inputs["7"] = 7;
    cmd_inputs["8"] = 8;
    cmd_inputs["9"] = 9;
    cmd_inputs["10"] = 10;
    #pragma endregion command_inputs

    try
    {
        cout << "Benvenuto nel sistema CRM avanzato di InsuraPro!" << endl;
        Utility::show_help();
        
        while(cmd != "chiudi"){
            cout << "\nCosa vuoi fare? (\"supporto\" o \"1\" per mostrare tutte le funzioni): ";
            getline(cin, cmd);

            vector<Client*>* found_clients;

            switch (cmd_inputs[cmd])
            {
            case 1:
                Utility::show_help();
                break;

            case 2:
                cout << "\nAggiungi uno o più clienti nel CRM." << endl;
                crm->add_client();

                break;

            case 3:
                cout << "\nVisualizza i clienti del CRM.\n" << endl;
                crm->view_clients();
                break;

            case 4:
                cout << "\nAggiorna un cliente nel CRM.\n" << endl;
                crm->update_client();
                break;
            case 5:
                cout << "\nElimina un cliente nel CRM.\n" << endl;
                crm->delete_client();
                break;
            case 6:
                cout << "\nRicerca i clienti del CRM.\n" << endl;
                found_clients = crm->search_clients();

                if(found_clients->size() > 0){
                    cout << "\nSono stati trovati " << found_clients->size() << " clienti che corrispondono alla ricerca: " << endl << endl;
                    for(Client* client : *found_clients){
                        cout << client->to_string() << endl;
                    }
                }
                else cout << "\nNessun cliente trovato con la query indicata." << endl;
                break;
            case 7:
                //crm->add_interaction();
                break;
            case 8:
                //crm->view_interactions();
                break;
            case 9:
                //crm->search_interactions();
                break;
            case 10:
                cout << "\nGrazie per aver usato InsuraPro, a presto!" << endl;
                cmd = "chiudi";
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
        InsuraPro::Contact* Contacte = new InsuraPro::Contact("Mario", "Rossi", "ViaRoma1", "); //errore?
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


    // crm->get_clients().InsertRow<string>(crm->get_clients().GetRowCount(), {customer->get_name(), customer->get_address(), customer->get_vat(), customer->get_company_email(), customer->get_company_phone(), customer->get_contact_ids_as_string()}, customer->get_id());
    // crm->get_clients().Save();

    //cout << crm->get_clients().GetRow<string>(customer->get_id());
    //crm->add_client();


/*
REferenze
https://stackoverflow.com/questions/20326356/how-to-remove-all-the-occurrences-of-a-char-in-c-string

-  Relazione 1:1 tra Contact e Client
-  Relazione 1:N tra Client e Interaction
*/