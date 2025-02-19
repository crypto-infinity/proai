/*
Client Class Interface
This class represents the Client object with custom methods for manipulation.
*/

#ifndef CLIENT_H
#define CLIENT_H

#pragma region includes

#include <bits/stdc++.h>

using namespace std;

#pragma endregion includes

#pragma region definitions
namespace InsuraPro{

    /// @brief Utility Class Definition, represents the Client object with custom methods for manipulation.
    class Utility{
        public:
            /// @brief Constant for the CSV Delimiter
            const char DELIMITER = ',';

            /// @brief Regular Expression for Emails
            string email_regex = R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)";
            const regex EMAIL_REGEX{email_regex};

            /// @brief Regular Expression for Phone Numbers
            string phone_regex = R"(^\+(?:[0-9] ?){6,14}[0-9]$)";
            const regex PHONE_REGEX{phone_regex};

            /// @brief Random string generator, source: https://medium.com/@ryan_forrester_/c-random-string-generation-practical-guide-e7e789b348d4
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

            /// @brief Show an help menu with all possible commands.
            static void show_help(){
                cout << "\nI comandi disponibili sono i seguenti:\n";
                cout << "1. 'supporto' : mostra l'elenco delle funzioni disponibili.\n";
                cout << "2. 'aggiunta_cliente' : aggiungi un nuovo cliente nel CRM.\n";
                cout << "3. 'mostra_clienti' : visualizza l'elenco dei clienti presenti nel CRM.\n";
                cout << "4. 'modifica_cliente' : modifica i dati di un cliente presente nel CRM.\n";
                cout << "5. 'elimina_cliente' : elimina un cliente presente nel CRM.\n";
                cout << "6. 'interazione' : aggiungi un'interazione ad un cliente presente nel CRM.\n";
                cout << "7. 'mostra_interazioni' : visualizza l'elenco delle interazioni di un cliente presente nel CRM.\n";
                cout << "8. 'chiudi' : chiudi il programma.\n";
            }

    };
}
#pragma endregion definitions

#endif