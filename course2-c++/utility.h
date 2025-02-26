/*
Utility Class
This class contains utility methods that are used in the program. It is a base class for other classes in the program.

Gabriele Scorpaniti, 2025
*/

#ifndef UTILITY_H
#define UTILITY_H

#pragma region includes

#include <bits/stdc++.h>

/// @brief RapidCSV Library
/// @source: https://github.com/d99kris/rapidcsv
#include "rapidcsv.h"

using namespace std;

#pragma endregion includes

#pragma region definitions
namespace InsuraPro{

    /// @brief Utility Class, creates constants and static methods for the program.
    class Utility{
        protected:

            /// @brief Constant for the CSV Delimiter
            const char DELIMITER = ',';

            /// @brief Regular Expression for Emails
            string email_regex = R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)";
            const regex EMAIL_REGEX{email_regex};

            /// @brief Regular Expression for Phone Numbers
            string phone_regex = R"(^\+(?:[0-9] ?){6,14}[0-9]$)";
            const regex PHONE_REGEX{phone_regex};

            /// @brief Schema for the Contact CSV File
            const string CONTACTS_SCHEMA = "id,name,surname,address,email,phone,client_id";

            /// @brief Schema for the Client CSV File
            const string CLIENTS_SCHEMA = "id,name,address,vat,company_email,company_phone,interaction_ids";

            /// @brief Schema for the Interaction CSV File
            const string INTERACTIONS_SCHEMA = "id,name,type,date,description";

        public:

            /// @brief Random string generator.
            /// @source: https://medium.com/@ryan_forrester_/c-random-string-generation-practical-guide-e7e789b348d4
            /// @param length random string lenght (int)
            /// @return the generated random string
            static string generate_random_string(size_t length) {
                const string characters = "0123456789abcdefghijklmnopqrstuvwxyz";
                random_device random_device;
                mt19937 generator(random_device());
                uniform_int_distribution<> distribution(0, characters.size() - 1);
            
                string random_string;
                for (size_t i = 0; i < length; ++i) {
                    random_string += characters[distribution(generator)];
                }
            
                return random_string;
            }

            /// @brief Converts a string to lowercase.
            /// @param data string to convert
            /// @return the converted string
            static const string toLower(string data){
                string result = data;
                transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return tolower(c); });
                return result;
            }

            /// @brief Show an help menu with all possible commands.
            static void show_help(){
                cout << "\nI comandi disponibili sono i seguenti:\n";
                cout << "1. 'supporto' : mostra l'elenco delle funzioni disponibili.\n";
                cout << "2. 'aggiunta_cliente' : aggiungi un nuovo cliente nel CRM.\n";
                cout << "3. 'mostra_clienti' : visualizza l'elenco dei clienti presenti nel CRM.\n";
                cout << "4. 'modifica_cliente' : modifica i dati di un cliente presente nel CRM.\n";
                cout << "5. 'elimina_cliente' : elimina un cliente presente nel CRM.\n";
                cout << "6. 'ricerca_cliente' : ricerca un cliente per il suo contatto.\n";
                cout << "7. 'aggiunta_interazione' : aggiungi un'interazione ad un cliente presente nel CRM.\n";
                cout << "8. 'mostra_interazioni' : visualizza l'elenco delle interazioni di un cliente presente nel CRM.\n";
                cout << "9. 'cerca_interazioni' : cerca un'interazione per tipo o data.\n";
                cout << "10. 'chiudi' : chiudi il programma.\n";
            }

            static map<string, int> setup_input(){
                map<string, int> cmd_inputs;

                cmd_inputs["supporto"] = 1; 
                cmd_inputs["aggiunta_cliente"] = 2; 
                cmd_inputs["mostra_clienti"] = 3; 
                cmd_inputs["modifica_cliente"] = 4;
                cmd_inputs["elimina_cliente"] = 5;
                cmd_inputs["ricerca_cliente"] = 6;
                cmd_inputs["aggiunta_interazione"] = 7;
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

                return cmd_inputs;
            }
    };
}
#pragma endregion definitions

#endif