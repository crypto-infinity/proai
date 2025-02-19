/*
CRM 

*/

#pragma region includes
#ifndef __CRM_H_INCLUDED__
#define __CRM_H_INCLUDED__

#include <bits/stdc++.h>

#include "client.h"
#include "interaction.h"
#include "contact.h"

using namespace std;
#pragma endregion includes

#pragma region CRM
namespace InsuraPro {

    /// @brief CRM Class, represents the CRM program with custom methods for client/interaction manipulation.
    class CRM : Utility {

        private:

            /// @brief Client file path
            const string CLIENTS_FILE = "clients.csv";

            /// @brief Interactions file path
            const string INTERACTIONS_FILE = "interactions.csv";

            /// @brief Contacts file path
            const string CONTACTS_FILE = "contacts.csv";

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
                    clients = rapidcsv::Document(CLIENTS_FILE, rapidcsv::LabelParams(0, 0));
                    interactions = rapidcsv::Document(INTERACTIONS_FILE, rapidcsv::LabelParams(0, 0));
                    contacts = rapidcsv::Document(CONTACTS_FILE, rapidcsv::LabelParams(0, 0));
                }
                catch(exception& e){
                    cout << "Errore nella lettura dei file: " << e.what() << endl;
                }
            };

            // Client Management Methods

            void add_client(const Client& client);
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

            /// @brief Converts a CSV line into a Client Object.
            /// @param csv_line the CSV line parsed from a file to convert.
            /// @return a pointer to the Client object created.
            Client* csv_to_client(string csv_line);

            /// @brief Converts a CSV line into an Interaction Object.
            /// @param csv_line the CSV line parsed from a file to convert.
            /// @return a pointer to the Interaction object created.
            Interaction* csv_to_interaction(string csv_line);

        };
}
#pragma endregion CRM

#endif