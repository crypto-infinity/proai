/*
CRM 

*/

#pragma region includes
#ifndef __CRM_H_INCLUDED__
#define __CRM_H_INCLUDED__


#include <bits/stdc++.h>
#include "client.h"
#include "interaction.h"

using namespace std;
#pragma endregion includes

#pragma region interfaces
namespace InsuraPro {

    /// @brief CRM Class, represents the CRM program with custom methods for client/interaction manipulation.
    class CRM {

        private:

            /// @brief A list of clients in the CRM, represented as a vector of Client objects.
            vector<Client> clients;

            /// @brief A list of interactions in the CRM, represented as a vector of Interaction objects.
            vector<Interaction> interactions;
        
        public:

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

        };
}
#pragma endregion interfaces

#endif