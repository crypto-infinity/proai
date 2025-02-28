/*
Contact Class Interface
This class represents the Contact object with custom methods for manipulation.
*/

#pragma region includes

#ifndef __CONTACT_H_INCLUDED__
#define __CONTACT_H_INCLUDED__

#include <bits/stdc++.h>
#include <regex>

#include "utility.h"

using namespace std;

#pragma endregion includes

#pragma region Contact
namespace InsuraPro{
    /// @brief Contact Class Definition, represents the Contact object with custom methods for manipulation.
    class Contact : Utility
    {
        private:
            /// @brief Contact ID, generated randomly
            const string id = "ctc-" + generate_random_string(10);

            /// @brief Name Attribute
            string name;

            /// @brief Surname Attribute
            string surname;

            /// @brief Address Attribute
            string address;

            /// @brief Email Attribute, must be a valid email
            string email;

            /// @brief Phone Attribute, must be a valid phone number
            string phone;

            /// @brief foreign key, 1:1 relationship with Client
            string client_id;
        
        public:
            /// @brief Constructor. Initializes the Contact object.
            /// @param _name Contact Name, mandatory
            /// @param _surname Contact Surname
            /// @param _address Contact Address
            /// @param _email Contact Email
            /// @param _phone Contact Phone Number
            Contact(string _name, string _surname = "", string _address = "", string _email = "", string _phone = "", string _client_id = ""){
                    set_name(_name);
                    set_surname(_surname);
                    set_address(_address);
                    set_email(_email);
                    set_phone(_phone);
                    set_client_id(_client_id);

            };
        
            #pragma region Getters

            /// @brief Getter Method for the Contact ID
            /// @return string
            string get_id() const{
                return id;
            };

            /// @brief Getter Method for the Contact Name
            /// @return string
            string get_name() const{
                return name;
            };

            /// @brief Getter Method for the Contact Surname
            /// @return string
            string get_surname() const{
                return surname;
            };

            /// @brief Getter Method for the Contact Address
            /// @return string
            string get_address() const{
                return address;
            };

            /// @brief Getter Method for the Contact Email
            /// @return string
            string get_email() const{
                return email;
            };

            /// @brief Getter Method for the Contact Phone Number
            /// @return string
            string get_phone() const{
                return phone;
            };

            /// @brief Getter Method for the Contact Client ID
            /// @return string
            string get_client_id() const{
                return client_id;
            };

            #pragma endregion Getters

            #pragma region Setters

            /// @brief Setter Method for the Contact Name
            /// @param name string, the new name
            string set_name(string _name){
                if(_name.empty()){
                    throw std::invalid_argument("Il nome deve essere valido");
                }
                name = _name;
                return name;
            };

            /// @brief Setter Method for the Contact Surname
            /// @param surname string
            string set_surname(string _surname){
                surname = _surname;
                return surname;
            };

            /// @brief Setter Method for the Contact Address
            /// @param address string
            string set_address(string _address){
                address = _address;
                return address;
            };

            /// @brief Setter Method for the Contact Email, applies a regex check
            /// @param email string
            string set_email(string _email){
                if( !_email.empty() &&
                    !regex_match(_email, EMAIL_REGEX)
                  )
                {
                    throw std::invalid_argument("L'email non è valida");
                }
                email = _email;
                return email;
            };

            /// @brief Setter Method for the Contact Phone Number
            /// @param phone string
            string set_phone(string _phone){
                if( !_phone.empty() &&
                    !regex_match(_phone, PHONE_REGEX)
                  )
                {
                    throw std::invalid_argument("Il telefono non è valido");
                }
                phone = _phone;
                return phone;
            };

            /// @brief Setter Method for the Contact Client ID
            /// @param client_id string
            string set_client_id(string _client_id){
                client_id = _client_id;
                return client_id;
            };

            #pragma endregion Setters

            //Object string representation

            /// @brief String Representation of the Contact Object
            /// @return string
            string to_string() const{
                return "Contatto ID: " + id + ". Nome: " + name + ", Cognome: " + surname + ", Indirizzo: " + address + ", Email: " + email + ", Telefono: " + phone;
            };

            /// @brief CSV Representation of the Contact Object
            /// @return string
            string to_csv() const{
                return id + DELIMITER + name + DELIMITER + surname + DELIMITER + address + DELIMITER + email + DELIMITER + phone;
            };
        };
}

#pragma endregion Contact

#endif