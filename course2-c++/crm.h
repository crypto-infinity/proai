/*
CRM Class, represents the CRM program with custom methods for client/interaction manipulation.

Gabriele Scorpaniti, 2025
*/

#pragma region includes
#ifndef __CRM_H_INCLUDED__
#define __CRM_H_INCLUDED__

#include <bits/stdc++.h>
#include <filesystem>

#include "input.h"

using namespace std;
namespace fs = std::filesystem;

#pragma endregion includes

#pragma region CRM
namespace InsuraPro {

    /// @brief CRM Class, represents the CRM program with custom methods for client/interaction manipulation.
    class CRM : Utility, Input {
        private:

            /// @brief Client file path
            const string CLIENTS_FILE = "./clients.csv";

            /// @brief Interactions file path
            const string INTERACTIONS_FILE = "./interactions.csv";

            /// @brief Contacts file path
            const string CONTACTS_FILE = "./contacts.csv";

            /// @brief A list of clients in the CRM, streamed from a CSV file.
            rapidcsv::Document clients;

            /// @brief A list of interactions in the CRM, streamed from a CSV file.
            rapidcsv::Document interactions;

            /// @brief A list of contacts in the CRM, streamed from a CSV file.
            rapidcsv::Document contacts;
        
        public:

            /// @brief Default constructor for the CRM class, initializes the CSV files and handles exceptions.
            CRM(){
                try{
                    if(fs::exists(CONTACTS_FILE)) contacts = rapidcsv::Document(CONTACTS_FILE, rapidcsv::LabelParams(0, 0));
                    else throw fstream::failure("Contacts file not readable or found.");
                    
                }
                catch(fstream::failure& e){
                    ofstream file(CONTACTS_FILE);
                    file << CONTACTS_SCHEMA << endl;
                    file.close();
                    contacts = rapidcsv::Document(CONTACTS_FILE, rapidcsv::LabelParams(0, 0));
                }
                
                try{
                    if(fs::exists(CLIENTS_FILE)) clients = rapidcsv::Document(CLIENTS_FILE, rapidcsv::LabelParams(0, 0));
                    else throw fstream::failure("Client file not readable or found.");
                }
                catch(fstream::failure& e){
                    ofstream file(CLIENTS_FILE);
                    file << CLIENTS_SCHEMA << endl;
                    file.close();
                    clients = rapidcsv::Document(CLIENTS_FILE, rapidcsv::LabelParams(0, 0));
                }
                
                try{
                    if(fs::exists(INTERACTIONS_FILE)) interactions = rapidcsv::Document(INTERACTIONS_FILE, rapidcsv::LabelParams(0, 0));
                    else throw fstream::failure("Interactions file not readable or found.");
                }
                catch(fstream::failure& e){
                    ofstream file(INTERACTIONS_FILE);
                    file << INTERACTIONS_SCHEMA << endl;
                    file.close();   
                    interactions = rapidcsv::Document(INTERACTIONS_FILE, rapidcsv::LabelParams(0, 0));
                }
            };

            #pragma region Getters

            /// @brief Getter Method for Contact CSV rapidcsv::document
            /// @return rapidcsv::Document
            rapidcsv::Document& get_contacts(){
                return contacts;
            };

            /// @brief Getter Method for Client CSV rapidcsv::document
            /// @return rapidcsv::Document
            rapidcsv::Document& get_clients(){
                return clients;
            };

            /// @brief Getter Method for Interaction CSV rapidcsv::document
            /// @return rapidcsv::Document
            rapidcsv::Document& get_interactions(){
                return interactions;
            };

            #pragma endregion Getters

            #pragma region ClientMgmt
            // Client Management Methods

            /// @brief Adds a new client to the CRM. Handles user input.
            /// @return bool, true if the client was added successfully, false otherwise.
            /// @throws exception if an error occurs.
            /// @see get_client_input for user input.
            bool add_clients(){
                try{
                    auto [clients_to_add, contacts_to_add] = get_client_input();

                    string ack;

                    cout << "\nVuoi davvero aggiungere " << clients_to_add->size() << " clienti nel CRM? (si/no): ";

                    getline(cin, ack);
                    while(ack != "si" && ack != "no"){
                        cout << "Comando non valido.";
                        cout << "\nVuoi davvero aggiungere " << clients_to_add->size() << " clienti nel CRM? (si/no): ";
                        getline(cin, ack);
                    }

                    if(ack == "si"){

                        for(int i = 0; i < clients_to_add->size(); i++){
                            clients.InsertRow<string>(
                                    clients.GetRowCount(), 
                                        {
                                            (*clients_to_add)[i]->get_name(), 
                                            (*clients_to_add)[i]->get_address(), 
                                            (*clients_to_add)[i]->get_vat(), 
                                            (*clients_to_add)[i]->get_company_email(), 
                                            (*clients_to_add)[i]->get_company_phone()
                                        }, 
                                            (*clients_to_add)[i]->get_id()
                                );
                            contacts.InsertRow<string>(
                                contacts.GetRowCount(), 
                                    {
                                        (*contacts_to_add)[i]->get_name(), 
                                        (*contacts_to_add)[i]->get_surname(), 
                                        (*contacts_to_add)[i]->get_address(), 
                                        (*contacts_to_add)[i]->get_email(), 
                                        (*contacts_to_add)[i]->get_phone(), 
                                        (*contacts_to_add)[i]->get_client_id()
                                    }, 
                                        (*contacts_to_add)[i]->get_id()
                                );
                        }

                        clients.Save();
                        contacts.Save();

                        cout << "\nClienti aggiunti con successo!" << endl;
                        return true;
                    }else{
                        cout << "\nOperazione annullata." << endl;
                        return false;
                    }
                }
                catch(exception& e){
                    cout << "\nErrore nell'aggiunta del cliente: " << e.what() << endl;
                    return false;
                }
            }

            /// @brief Prints all clients in the CRM. Iterates CSV Document.
            void view_clients(){
                unsigned int rowCount = clients.GetRowCount();
                vector<string> rowIds = clients.GetRowNames();

                if(rowCount == 0){
                    cout << "Nessun cliente presente nel CRM." << endl;
                    return;
                }

                //prints all CSV row, without endlines between attributes
                for (string id : rowIds){
                    cout 
                        << "Cliente: " << id
                        << " | Nome: " << clients.GetCell<string>("name", id) 
                        << " | Indirizzo Az.: " << clients.GetCell<string>("address", id) 
                        << " | VAT: " << clients.GetCell<string>("vat", id) 
                        << " | Email Az.: " << clients.GetCell<string>("company_email", id) 
                        << " | Telefono Az.: " << clients.GetCell<string>("company_phone", id) 
                        << endl;
                }
            }

            /// @brief Updates a client in the CRM and its associated contact.
            /// @return bool, true if the client/contact was updated successfully, false otherwise.
            bool update_client(){
                vector<Client*>* clients_to_update = search_clients();

                if(clients_to_update->size() == 0){
                    cout << "Nessun cliente trovato." << endl;
                    return false;
                }

                cout << "Clienti trovati: " << endl;

                vector<tuple<int,string>> client_data(clients_to_update->size());

                for(int i = 0; i < clients_to_update->size(); i++){
                    cout << (i + 1) << ". " << (*clients_to_update)[i]->get_name() << " " << (*clients_to_update)[i]->get_address() << endl;
                    client_data[i] = {i ,(*clients_to_update)[i]->get_id()};
                }

                string input = "";
                string client_id_to_modify = "";
                int index;
                cout << "\nQuale vuoi modificare? Inserisci il numero corrispondente: ";
                getline(cin, input);

                while(true){
                    try{
                        index = stoi(input) - 1;
                        client_id_to_modify = get<1>(client_data[index]);
                        break;
                    }
                    catch(exception& e){
                        cout << "Indice non valido. Riprova.";
                        getline(cin, input);
                    }
                }

                cout << "\nInserisci i nuovi dati del cliente: " << endl;
                auto [clients_to_add, contacts_to_add] = get_client_input(false,true);

                string ack;

                cout << "\nVuoi davvero aggiornare il cliente " << clients.GetCell<string>("name",client_id_to_modify) << " ? (si/no): ";
                getline(cin, ack);

                while(ack != "si" && ack != "no"){
                    cout << "Comando non valido.";
                    cout << "\nVuoi davvero aggiornare il cliente? (si/no): ";
                    getline(cin, ack);
                }

                if(ack == "si"){

                    clients.SetRow<string>(client_id_to_modify, {
                        (*clients_to_add)[0]->get_name(), 
                        (*clients_to_add)[0]->get_address(), 
                        (*clients_to_add)[0]->get_vat(), 
                        (*clients_to_add)[0]->get_company_email(), 
                        (*clients_to_add)[0]->get_company_phone()
                    });

                    for(int i = 0; i < contacts.GetRowCount(); i++){
                        if(contacts.GetCell<string>("client_id", i) == client_id_to_modify){
                            contacts.SetRow<string>(i, {
                                (*contacts_to_add)[0]->get_name(), 
                                (*contacts_to_add)[0]->get_surname(), 
                                (*contacts_to_add)[0]->get_address(), 
                                (*contacts_to_add)[0]->get_email(), 
                                (*contacts_to_add)[0]->get_phone()
                            });
                        }
                    }

                    clients.Save();
                    contacts.Save();

                    cout << "\nCliente aggiornato con successo!" << endl;
                    return true;
                }else{
                    cout << "\nOperazione annullata." << endl;
                    return false;
                }

                return false;
            }

            /// @brief Deletes a client from the CRM and its associated contact.
            /// @return bool, true if the client/contact was deleted successfully, false otherwise.
            bool delete_client(){
                vector<Client*>* clients_to_delete = search_clients();

                if(clients_to_delete->size() == 0){
                    cout << "Nessun cliente trovato." << endl;
                    return false;
                }

                cout << "Clienti trovati: " << endl;

                vector<tuple<int,string>> client_data(clients_to_delete->size());

                for(int i = 0; i < clients_to_delete->size(); i++){
                    cout << (i + 1) << ". " << (*clients_to_delete)[i]->get_name() << " " << (*clients_to_delete)[i]->get_address() << endl;
                    client_data[i] = {i ,(*clients_to_delete)[i]->get_id()};
                }

                string input = "";
                string client_id_to_delete = "";
                int index;
                cout << "\nQuale vuoi eliminare? Inserisci il numero corrispondente: ";
                getline(cin, input);

                while(true){
                    try{
                        index = stoi(input) - 1;
                        client_id_to_delete = get<1>(client_data[index]);
                        break;
                    }
                    catch(exception& e){
                        cout << "Indice non valido. Riprova.";
                        getline(cin, input);
                    }
                }

                cout << "\nVuoi davvero eliminare il cliente " << clients.GetCell<string>("name",client_id_to_delete) << " con contatti e interazioni ad esso associate? (si/no): ";
                getline(cin, input);

                while(input != "si" && input != "no"){
                    cout << "Comando non valido.";
                    cout << "\nVuoi davvero eliminare il cliente? (si/no): ";
                    getline(cin, input);
                }

                if(input == "si"){

                    //removes client
                    clients.RemoveRow(client_id_to_delete);

                    //remove clients associated
                    int rowCount = contacts.GetRowCount();
                    for(int i = 0; i < rowCount; i++) if(contacts.GetCell<string>("client_id", i) == client_id_to_delete) contacts.RemoveRow(i);
                    
                    //remove interactions associated
                    vector<string>* interaction_ids_to_delete = Client::get_interaction_ids_from_csv(clients.GetCell<string>("interaction_ids", client_id_to_delete));

                    for(string interaction_id : *interaction_ids_to_delete) interactions.RemoveRow(interaction_id);

                    clients.Save();
                    contacts.Save();

                    cout << "\nCliente eliminato con successo!" << endl;
                    return true;

                }else{
                    cout << "\nOperazione annullata." << endl;
                    return false;
                }
                return false;
            }

            /// @brief Searches for a Client in the CRM by various criterias (Contact Name, Contact Surname, Client Name).
            /// @return pointer to std::vector<Client> populated by matching criterias on contact/client objects.
            vector<Client*>* search_clients(){

                string search_key = "";
                cout << "Inserisci i parametri di ricerca: ";
                getline(cin, search_key);

                vector<Client*>* found_clients = new vector<Client*>();

                try{
                    for(int i = 0; i < clients.GetRowCount(); i++){
    
                        if( //Search criterias, can be adapted as needed
                            toLower(contacts.GetCell<string>("name", i)).find(toLower(search_key)) != string::npos || 
                            toLower(contacts.GetCell<string>("surname", i)).find(toLower(search_key)) != string::npos ||
                            toLower(clients.GetCell<string>("name", i)).find(toLower(search_key)) != string::npos
                          ){

                            string client_id = contacts.GetCell<string>("client_id", i);
                            
                            if (clients.GetRow<string>(client_id).size() > 0){
                                Client* found_client = new Client(
                                    client_id,
                                    clients.GetCell<string>("name", client_id),
                                    clients.GetCell<string>("address", client_id),
                                    clients.GetCell<string>("vat", client_id),
                                    clients.GetCell<string>("company_email", client_id),
                                    clients.GetCell<string>("company_phone", client_id)
                                );

                                found_clients->push_back(found_client);
                            }
                        }
    
                    }
                }
                catch(exception& e){
                    cout << "Errore nella ricerca del cliente: " << e.what() << endl;
                }

                return found_clients;
            }

            #pragma endregion ClientMgmt

            #pragma region InteractionMgmt
            // Interaction Management Methods

            /// @brief Adds a new interaction to the CRM.
            /// @return bool, true if the interaction was added successfully, false otherwise.
            /// @throws exception if an error occurs.
            bool add_interactions(){
                try{
                    vector<Interaction*>* interactions_to_add = get_interaction_input();
    
                    cout << "\nRicerca ora il cliente al quale collegare le interazioni inserite." << endl;
                    //TO DO: aggiungere collegamento con 1 o più clienti.
                    vector<Client*>* updated_clients = search_clients();

                    if(updated_clients->size() == 0){
                        cout << "Nessun cliente trovato, riprova l'aggiunta." << endl;
                        return false;
                    }
    
                    cout << "Clienti trovati: " << endl;
    
                    for(int i = 0; i < updated_clients->size(); i++){
                        cout << (i + 1) << ". " << (*updated_clients)[i]->get_name() << " " << (*updated_clients)[i]->get_address() << endl;
                    }
    
                    string input = "";
                    int index;

                    cout << "\nA quale di questi vuoi associare le interazioni inserite? Inserisci il numero corrispondente: ";
                    getline(cin, input);

                    while(true){
                        try{
                            index = stoi(input) - 1;
                            break;
                        }
                        catch(exception& e){
                            cout << "Indice non valido. Riprova: ";
                            getline(cin, input);
                        }
                    }

                    string ack;
    
                    cout << "\nVuoi davvero aggiungere " << interactions_to_add->size() << " interazioni nel CRM? (si/no): ";
                    getline(cin, ack);
    
                    while(ack != "si" && ack != "no"){
                        cout << "Comando non valido.";
                        cout << "\nVuoi davvero aggiungere " << interactions_to_add->size() << " interazioni nel CRM? (si/no): ";
                        getline(cin, ack);
                    }
                    
                    if(ack == "si"){
                        try{
                            string ids_to_set = clients.GetCell<string>("interaction_ids", index);
                            for(Interaction* i : *interactions_to_add){
                                
                                ids_to_set =  i->get_id() + ";" + ids_to_set;

                                interactions.InsertRow<string>(
                                    interactions.GetRowCount(), 
                                        {
                                            i->get_name(),
                                            i->get_type(), 
                                            i->get_date(), 
                                            i->get_description()
                                        }, 
                                            i->get_id()
                                );
                            }

                            clients.SetCell<string>("interaction_ids", index, ids_to_set);
                        }
                        catch(out_of_range& e){
                            cout << "Out of range: " << e.what() << endl;
                        }
    
                        clients.Save();
                        interactions.Save();
    
                        cout << "\nInterazioni aggiunte con successo!" << endl;
                        return true;
                    }else{
                        cout << "\nOperazione annullata." << endl;
                        return false;
                    }
                }catch(exception& e){
                    cout << "\nErrore nell'aggiunta delle interazioni: " << e.what() << endl;
                    return false;
                }
            };

            /// @brief Prints all interactions in the CRM.
            /// @return bool, true if the interactions were printed successfully, false otherwise.
            bool view_interactions(){
                unsigned int rowCount = interactions.GetRowCount();
                vector<string> rowIds = interactions.GetRowNames();

                if(rowCount == 0){
                    cout << "\nNessuna interazione presente nel CRM." << endl;
                    return true;
                }

                for (int i = 0; i < clients.GetRowCount(); i++){
                    cout << "Interazioni del Cliente " << clients.GetCell<string>("name", i) << " :" << endl;
                    vector<string>* interaction_ids = Client::get_interaction_ids_from_csv(clients.GetCell<string>("interaction_ids", i));
                    bool correspondence = false;

                    if(interaction_ids == NULL){
                        cout << "\nNessuna interazione." << endl;
                        continue;
                    }
                    else{ //DA DEBUGGARE
                        //prints all CSV row associated to the specific customer
                        for (string id : rowIds){
                            for(int j = 0; j < interaction_ids->size(); j++){
                                if(id == (*interaction_ids)[j]){
                                    cout 
                                        << endl
                                        << "Interazione: " << id
                                        << " | Nome: " << interactions.GetCell<string>("name", id)
                                        << " | Tipo: " << interactions.GetCell<string>("type", id) 
                                        << " | Data: " << interactions.GetCell<string>("date", id) 
                                        << " | Descrizione: " << interactions.GetCell<string>("description", id) 
                                        << endl;
                                    correspondence = true;
                                }
                            }
    
                        }
                    }
                    if(!correspondence) cout << "\nNessuna interazione." << endl;
                }
                return true;
            }

            /// @brief Searches for an Interaction in the CRM by various criterias (Type, Date).
            /// @return pointer to std::vector<Interaction> populated by matching criterias on interaction objects.
            vector<Interaction*>* search_interactions(){
                
                string search_key = "";
                cout << "Inserisci i parametri di ricerca: ";
                getline(cin, search_key);

                vector<Interaction*>* found_interactions = new vector<Interaction*>();

                try{
                    for(int i = 0; i < interactions.GetRowCount(); i++){
    
                        if( //Search criterias, can be adapted as needed
                            toLower(interactions.GetCell<string>("name", i)).find(toLower(search_key)) != string::npos ||
                            toLower(interactions.GetCell<string>("type", i)).find(toLower(search_key)) != string::npos || 
                            toLower(interactions.GetCell<string>("date", i)).find(toLower(search_key)) != string::npos ||
                            toLower(interactions.GetCell<string>("description", i)).find(toLower(search_key)) != string::npos ||
                            toLower(clients.GetCell<string>("name", i)).find(toLower(search_key)) != string::npos
                          ){

                            Interaction* found_interaction = new Interaction(
                                interactions.GetRowName(i), //segmentation fault
                                interactions.GetCell<string>("name", i),
                                interactions.GetCell<string>("type", i),
                                interactions.GetCell<string>("date", i),
                                interactions.GetCell<string>("description", i)
                            );

                            found_interactions->push_back(found_interaction);
                        }
                    }
                }
                catch(exception& e){
                    cout << "Errore nella ricerca dell'interazione: " << e.what() << endl;
                }

                return found_interactions;
            }

            #pragma endregion InteractionMgmt

        };
}
#pragma endregion CRM

#endif