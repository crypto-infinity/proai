/*
CRM 

*/

#pragma region includes
#ifndef __CRM_H_INCLUDED__
#define __CRM_H_INCLUDED__

#include <bits/stdc++.h>

#include "input.h"

using namespace std;
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

            // Constructor
            CRM(){
                try{
                    contacts = rapidcsv::Document(CONTACTS_FILE, rapidcsv::LabelParams(0, 0));
                    clients = rapidcsv::Document(CLIENTS_FILE, rapidcsv::LabelParams(0, 0));
                    interactions = rapidcsv::Document(INTERACTIONS_FILE, rapidcsv::LabelParams(0, 0));
                }
                catch(exception& e){
                    cout << "Errore nella lettura dei file: " << e.what() << endl;
                }
            };

            #pragma region Getters
            //Getters

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

            // Client Management Methods

            /// @brief Adds a new client to the CRM. Handles user input.
            /// @return bool, true if the client was added successfully, false otherwise.
            /// @throws exception if an error occurs.
            /// @see get_client_input for user input.
            bool add_client(){
                try{
                    vector<Client*>* clients_to_add = get_client_input();

                    string ack;

                    cout << "Vuoi davvero aggiungere " << clients_to_add->size() << " clienti nel CRM? (si/no)" << endl;

                    getline(cin, ack);
                    while(ack != "si" && ack != "no"){
                        cout << "Comando non valido.";
                        cout << "Vuoi davvero aggiungere " << clients_to_add->size() << " clienti nel CRM? (si/no): ";
                        getline(cin, ack);
                    }

                    if(ack == "si"){
                        for(Client* client : *clients_to_add){
                            clients.InsertRow<string>(clients.GetRowCount(), {client->get_name(), client->get_address(), client->get_vat(), client->get_company_email(), client->get_company_phone(), client->get_contact_ids_as_string()}, client->get_id());
                        }

                        clients.Save();
                        cout << "Aggiunti con successo!" << endl;
                        return true;
                    }else{
                        cout << "Operazione annullata." << endl;
                        return false;
                    }
                }
                catch(exception& e){
                    cout << "Errore nell'aggiunta del cliente: " << e.what() << endl;
                    return false;
                }
            };

            void view_clients() const;
            void update_client(const string& client_id, const Client& updated_client);
            void delete_client(const string& client_id);
            Client* search_client(const string& client_id);
        
            // Interaction Management Methods

            void add_interaction(const Interaction& interaction);
            void view_interactions(const string& client_id) const;            
            void update_interaction(const string& interaction_id, const Interaction& updated_interaction);
            void delete_interaction(const string& interaction_id);
            Interaction* search_interaction(const string& interaction_id);
        
            // Data Saving and Loading Methods

            void save_data(const string& file_name) const;
            void load_data(const string& file_name);

            // Data conversion from CSVs

            /// @brief Converts a CSV line into a Contact Object.
            /// @param csv_line the CSV line parsed from a file to convert.
            /// @return a pointer to the Contact object created.
            Contact* csv_to_contact(string csv_line){
                stringstream sstream(csv_line);
                rapidcsv::Document doc(sstream, rapidcsv::LabelParams(0, 0));
                try{
                    return new Contact
                                    (   
                                        doc.GetCell<string>("name", 0), 
                                        doc.GetCell<string>("surname", 0), 
                                        doc.GetCell<string>("address", 0), 
                                        doc.GetCell<string>("email", 0), 
                                        doc.GetCell<string>("phone", 0)
                                    );
                }
                catch(exception& e){
                    cout << "Errore nella conversione del contatto: " << e.what() << endl;
                    return NULL;
                }
            };

            /// @brief Converts a std::string id into a Contact Object, fetched from CSV.
            /// @param id the id parsed from file.
            /// @return a pointer to the Contact object created, or null if it's not found.
            Contact* csv_id_to_contact(string id){
                try{
                    if(contacts.GetRow<string>(id).size() != 0){
                        return new Contact
                        (   
                            contacts.GetCell<string>("name", id), 
                            contacts.GetCell<string>("surname", id), 
                            contacts.GetCell<string>("address", id), 
                            contacts.GetCell<string>("email", id), 
                            contacts.GetCell<string>("phone", id)
                        );
                    }else{
                        return NULL;
                    }

                }
                catch(exception& e){
                    cout << "Errore nella conversione del contatto: " << e.what() << endl;
                    return NULL;
                }
            };

            // /// @brief Converts a CSV line into a Client Object.
            // /// @param csv_line the CSV line parsed from a file to convert.
            // /// @return a pointer to the Client object created.
            // Client* csv_to_client(string csv_line){
            //     stringstream sstream(csv_line);
            //     rapidcsv::Document doc(sstream, rapidcsv::LabelParams(0, 0));
            //     try{
            //         string contact_ids_csv = doc.GetCell<string>("contacts", 0);
            //         vector<string> contacts_ids_string;
            //         boost::erase_all(contact_ids_csv, "["); //[ctc-1;ctc-2] > ctc1;ctc-2
            //         boost::erase_all(contact_ids_csv, "]"); //[ctc-1;ctc-2] > ctc1;ctc-2
            //         boost::split(contacts_ids_string,contact_ids_csv,boost::is_any_of(";"));
            //         int test;

            //         return new Client
            //                         (   
            //                             doc.GetCell<string>("name", 0), 
            //                             doc.GetCell<string>("address", 0), 
            //                             doc.GetCell<string>("vat", 0), 
            //                             doc.GetCell<string>("company_email", 0), 
            //                             doc.GetCell<string>("company_phone", 0)
            //                         );
            //     }
            //     catch(exception& e){
            //         cout << "Errore nella conversione del cliente: " << e.what() << endl;
            //         return NULL;
            //     }
            // };

            /// @brief Converts a CSV line into an Interaction Object.
            /// @param csv_line the CSV line parsed from a file to convert.
            /// @return a pointer to the Interaction object created.
            Interaction* csv_to_interaction(string csv_line);

        };
}
#pragma endregion CRM

#endif