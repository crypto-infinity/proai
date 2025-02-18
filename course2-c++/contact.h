/*
Contact Class Interface
This class represents the Contact object with custom methods for manipulation.
*/

#pragma region includes

#include <bits/stdc++.h>
#include <regex>
#include <cctype>
#include <climits>
#include <iomanip>
#include <iostream>
#include "utility.h"
#include <ctype.h>

using namespace std;

#pragma endregion includes

#pragma region definitions
namespace InsuraPro{
    /// @brief Contact Class Definition, represents the Contact object with custom methods for manipulation.
    class Contact : Utility
    {
        private:
            const string id = "ctc-" + generate_random_string(10);
            string name;
            string surname;
            string address;
            string email;
            string phone;
        
        public:
            /// @brief Constructor. Initializes the Contact object.
            /// @param _name Contact Name, mandatory
            /// @param _surname Contact Surname
            /// @param _address Contact Address
            /// @param _email Contact Email
            /// @param _phone Contact Phone Number
            Contact(string _name, string _surname = NULL, string _address = NULL, string _email = NULL, string _phone = NULL){

                set_name(_name);
                set_surname(_surname);
                set_address(_address);
                set_email(_email);
                set_phone(_phone);

            };
        
            /*
            Getters Methods
            */

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

            /*
            Setters Methods
            */

            /// @brief Setter Method for the Contact Name
            /// @param name string, the new name
            string set_name(string _name){
                if(_name.empty()){
                    throw std::invalid_argument("Il nome deve essere valido!");
                }
                name = _name;
                return name;
            };

            /// @brief Setter Method for the Contact Surname
            /// @param surname string
            string set_surname(string _surname){
                if(_surname.empty()){
                    throw std::invalid_argument("Il cognome deve essere valido!");
                }
                surname = _surname;
                return surname;
            };

            /// @brief Setter Method for the Contact Address
            /// @param address string
            string set_address(string _address){
                if(_address.empty()){
                    throw std::invalid_argument("L'indirizzo deve essere valido!");
                }
                address = _address;
                return address;
            };

            /// @brief Setter Method for the Contact Email, applies a regex check
            /// @param email string
            string set_email(string _email){
                if( _email.empty() ||
                    !regex_match(_email, EMAIL_REGEX)
                  )
                {
                    throw std::invalid_argument("L'email non è valida.");
                }
                email = _email;
                return email;
            };

            /// @brief Setter Method for the Contact Phone Number
            /// @param phone string
            string set_phone(string _phone){
                if( _phone.empty() ||
                    !regex_match(_phone, PHONE_REGEX)
                  )
                {
                    throw std::invalid_argument("Il telefono non è valido.");
                }
                phone = _phone;
                return phone;
            };

            /*
            Comparison Methods
            */

            /// @brief Compare Operator for the Contact Class
            /// @param Contact Contact
            /// @return bool
            bool operator==(const Contact& Contact) const{
                return id == Contact.id;
            };

            /// @brief Overloaded Operator for the Contact Class
            /// @param Contact Contact
            /// @return bool
            bool operator!=(const Contact& Contact) const{
                return id != Contact.id;
            };

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
#pragma endregion definitions