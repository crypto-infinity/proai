/*
Main file for the InsuraPro CRM system, a simple CRM system for managing clients and interactions.

This file contains the main program loop, which handles the program execution and user input.
The program is structured in a way that allows for easy extensibility and maintainability, with a focus on modularity and reusability.
The program is divided into 3 main classes: Client, Contact, and Interaction, each with its own set of methods and properties.
The program uses the RapidCSV library for handling CSV files, which allows for easy reading and writing of CSV files.

Gabriele Scorpaniti, 2025
*/

#pragma region includes

#include <bits/stdc++.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

// includes each other class header file
#include "crm.h"

using namespace std;
using namespace InsuraPro;

#pragma endregion includes

#pragma region Main
/// @brief Main program loop, handles program execution
int main(){

    // Instantiates a new CRM object, ready for multiple CRM support with multiple CSVs
    InsuraPro::CRM* crm = new InsuraPro::CRM();

    //Variables setup
    vector<Client*>* found_clients;
    vector<Interaction*>* found_interactions;
    string cmd = "";

    //Setup input commands
    map<string, int> cmd_inputs = Utility::setup_input(); 

    try
    {
        cout << "Benvenuto nel sistema CRM avanzato di InsuraPro!" << endl;
        Utility::show_help();
        
        while(cmd != "chiudi"){
            cout << "\nCosa vuoi fare? (\"supporto\" o \"1\" per mostrare tutte le funzioni): ";
            getline(cin, cmd);

            switch (cmd_inputs[cmd])
            {
            case 1:
                Utility::show_help();
                break;

            case 2:
                cout << "\nAggiungi uno o piu' clienti nel CRM." << endl;
                crm->add_clients();
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
                else cout << "\nNessun cliente trovato con le informazioni indicate." << endl;

                found_clients->clear();
                break;

            case 7:
                cout << "\nAggiungi nuove interazioni nel CRM.\n" << endl;
                crm->add_interactions();
                break;

            case 8:
                cout << "\nVisualizza le interazioni presenti. Ricerca per cliente: \n" << endl;
                crm->view_interactions();
                break;

            case 9:
                cout << "\nRicerca le interazioni presenti nel CRM.\n" << endl;
                found_interactions = crm->search_interactions();

                if(found_interactions->size() > 0){
                    cout << "\nSono stati trovati " << found_interactions->size() << " interazioni che corrispondono alla ricerca: " << endl << endl;
                    for(Interaction* interaction : *found_interactions){
                        cout << interaction->to_string() << endl;
                    }
                }
                else cout << "\nNessuna interazione trovata con le informazioni indicate." << endl;

                found_interactions->clear();
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
        cout << "Si e' verificato un errore: " << e.what() << ". Chiudi il programma e riprova" << endl;
    }
    
    return 0;
}

#pragma endregion Main