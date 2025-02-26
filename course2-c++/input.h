/*
Input Header Class
Representents the Input class with methods for handling user input and creating objects.

Gabriele Scorpaniti, 2025
*/

#pragma region includes

#ifndef __INPUT_H_INCLUDED__
#define __INPUT_H_INCLUDED__

#include <bits/stdc++.h>
#include <tuple>

#include "client.h"
#include "interaction.h"
#include "contact.h"

using namespace std;

#pragma endregion includes

#pragma region Input
namespace InsuraPro {

    /// @brief Input Class, used for handling user input and creating objects.
    class Input{
        protected:

            /// @brief Gets User Input and creates a Contact object, validating input.
            /// @return Contact*, a pointer to the created Contact object.
            vector<Contact*>* get_contact_input(bool multiple_entry=true){
                try{
                    string user_key = "";
                    vector<Contact*>* contacts_to_add = new vector<Contact*>();

                    do
                    {
                        Contact* contact = NULL;

                        //name input
                        while(true){
                            try{
                                string name = "";
                                cout << "Nome (obbligatorio): ";
                                getline(cin, name);
                                contact = new Contact(name);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        //other fields input
                        while(true){
                            try{
                                string surname = "";
                                cout << "Cognome: ";
                                getline(cin, surname);
                                contact->set_surname(surname);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        while(true){
                            try{
                                string address = "";
                                cout << "Indirizzo: ";
                                getline(cin, address);
                                contact->set_address(address);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        while(true){
                            try{
                                string email = "";
                                cout << "Email: ";
                                getline(cin, email);
                                contact->set_email(email);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        while(true){
                            try{
                                string phone = "";
                                cout << "Telefono (con prefisso): ";
                                getline(cin, phone);
                                contact->set_phone(phone);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        contacts_to_add->push_back(contact);

                        if(multiple_entry){
                            cout << "Vuoi aggiungere un altro contatto? (si/no): ";
                            getline(cin, user_key);
                            while(user_key != "si" && user_key != "no"){
                                cout << "Comando non valido.";
                                cout << "Vuoi aggiungere un altro contatto? (si/no): ";
                                getline(cin, user_key);
                            }
                        }else{
                            break;
                        }
                    }
                    while(user_key != "no");

                    return contacts_to_add;

                }catch(exception& e){
                    cout << "Errore nella creazione del contatto: " << e.what() << endl;
                    return NULL;
                }
            };

            /// @brief Gets User Input and creates a Client object with associated contact, if specified, validating input.
            /// @return tuple< vector<Client*> , vector<Contact*> >, a tuple containing the created Client and Contact objects linked together.
            tuple< vector<Client*>* , vector<Contact*>* > get_client_input(bool multiple_entry=true, bool connect_contact=true){
                try{
                    string user_key = "";
                    vector<Client*>* clients_to_add = new vector<Client*>();
                    vector<Contact*>* contacts_to_add = new vector<Contact*>();

                    do
                    {
                        Client* client = NULL;

                        cout << "\nInserisci i dati dell'azienda: " << endl;

                        //name input
                        while(true){
                            try{
                                string name = "";
                                cout << "Nome Azienda (obbligatorio): ";
                                
                                getline(cin, name);
                                client = new Client(name);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        //other fields input
                        while(true){
                            try{
                                string address = "";
                                cout << "Indirizzo Sede: ";
                                getline(cin, address);
                                client->set_address(address);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        while(true){
                            try{
                                string vat = "";
                                cout << "Partita IVA: ";
                                getline(cin, vat);
                                client->set_vat(vat);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        while(true){
                            try{
                                string company_email = "";
                                cout << "Email Aziendale: ";
                                getline(cin, company_email);
                                client->set_company_email(company_email);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        while(true){
                            try{
                                string company_phone = "";
                                cout << "Telefono Aziendale (con prefisso): ";
                                getline(cin, company_phone);
                                client->set_company_phone(company_phone);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        clients_to_add->push_back(client);

                        //Connects a Contact object to a Client object by its ID
                        if(connect_contact){
                            cout << "\nAggiungi ora il contatto del cliente: " << endl;
                            vector<Contact*>* new_contact_results = get_contact_input(false);
                            Contact* new_contact = new_contact_results->front();

                            if(contacts_to_add != NULL){
                                new_contact->set_client_id(client->get_id());
                                contacts_to_add->push_back(new_contact);
                            }
                        }

                        if(multiple_entry){ 
                            cout << "Vuoi aggiungere un altro cliente? (si/no): ";
                            getline(cin, user_key);
                            while(user_key != "si" && user_key != "no"){
                                cout << "Comando non valido.";
                                cout << "Vuoi aggiungere un altro cliente? (si/no): ";
                                getline(cin, user_key);
                            }
                        }
                    }
                    while(user_key != "no");

                    return {clients_to_add, contacts_to_add};

                }catch(exception& e){
                    cout << "Errore nella creazione del cliente: " << e.what() << endl;
                    return {};
                }
            }


            /// @brief Gets User Input and creates an Interaction object, validating input.
            /// @return std::vector<Interaction*>*, a vector representing the created Interaction objects.
            vector<Interaction*>* get_interaction_input(bool multiple_entry=true){
                try{
                    string user_key = "";
                    vector<Interaction*>* interactions_to_add = new vector<Interaction*>();

                    do
                    {
                        Interaction* interaction = NULL;

                        //name input
                        while(true){
                            try{
                                string name = "";
                                cout << "Nome (obbligatorio): ";
                                getline(cin, name);
                                interaction = new Interaction(name=name);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        //other fields input
                        while(true){
                            try{
                                string type = "";
                                cout << "Tipo (appuntamento/contratto) - obbligatorio: ";
                                getline(cin, type);
                                Utility::toLower(type);
                                interaction->set_type(type);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        //other fields input
                        while(true){
                            try{
                                string date = "";
                                cout << "Data dell'interazione: ";
                                getline(cin, date);
                                interaction->set_date(date);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        while(true){
                            try{
                                string description = "";
                                cout << "Descrizione: ";
                                getline(cin, description);
                                interaction->set_description(description);
                                break;
                            }
                            catch(exception& e){
                                cout << "\nErrore: " << e.what() << ". Riprova." << endl;
                            }
                        }

                        interactions_to_add->push_back(interaction);

                        if(multiple_entry){
                            cout << "Vuoi aggiungere un'altra interazione? (si/no): ";
                            getline(cin, user_key);
                            while(user_key != "si" && user_key != "no"){
                                cout << "Comando non valido.";
                                cout << "Vuoi aggiungere un'altra interazione? (si/no): ";
                                getline(cin, user_key);
                            }
                        }
                    }
                    while(user_key != "no");

                    return interactions_to_add;

                }catch(exception& e){
                    cout << "Errore nella creazione dell'interazione: " << e.what() << endl;
                    return NULL;
                }
            }

    };
}
#pragma endregion Input

#endif