/*
Client Class Interface
This class represents the Client object with custom methods for manipulation.
*/

#pragma region includes

#include <bits/stdc++.h>

using namespace std;

#pragma endregion includes

#pragma region definitions
namespace InsuraPro{
    /// @brief Client Class Definition, represents the Client object with custom methods for manipulation. 
    class Client {
        private:
            string id;
            string name;
            string surname;
            string address;
            string email;
            string phone;

            /// @brief Constant for the CSV Delimiter
            const char DELIMITER = ',';
        
        public:
            Client(string _id, string _name, string _surname, string _address, string _email, string _phone){
                id = _id;
                name = _name;
                surname = _surname;
                address = _address;
                email = _email;
                phone = _phone;
            };
        
            /*
            Getters Methods
            */

            /// @brief Getter Method for the Client ID
            /// @return string
            string get_id() const{
                return id;
            };

            /// @brief Getter Method for the Client Name
            /// @return string
            string get_name() const{
                return name;
            };

            /// @brief Getter Method for the Client Surname
            /// @return string
            string get_surname() const{
                return surname;
            };

            /// @brief Getter Method for the Client Address
            /// @return string
            string get_address() const{
                return address;
            };

            /// @brief Getter Method for the Client Email
            /// @return string
            string get_email() const{
                return email;
            };

            /// @brief Getter Method for the Client Phone Number
            /// @return string
            string get_phone() const{
                return phone;
            };

            /*
            Setters Methods
            */

            /// @brief Setter Method for the Client ID
            /// @param id string
            void set_id(const string& _id){
                id = _id;
            };

            /// @brief Setter Method for the Client Name
            /// @param name string
            void set_name(const string& _name){
                name = _name;
            };

            /// @brief Setter Method for the Client Surname
            /// @param surname string
            void set_surname(const string& _surname){
                surname = _surname;
            };

            /// @brief Setter Method for the Client Address
            /// @param address string
            void set_address(const string& _address){
                address = _address;
            };

            /// @brief Setter Method for the Client Email
            /// @param email string
            void set_email(const string& _email){
                email = _email;
            };

            /// @brief Setter Method for the Client Phone Number
            /// @param phone string
            void set_phone(const string& _phone){
                phone = _phone;
            };

            /*
            Comparison Methods
            */

            /// @brief Compare Operator for the Client Class
            /// @param Client Client
            /// @return bool
            bool operator==(const Client& Client) const{
                return id == Client.id;
            };

            /// @brief Overloaded Operator for the Client Class
            /// @param Client Client
            /// @return bool
            bool operator!=(const Client& Client) const{
                return id != Client.id;
            };

            //Object string representation

            /// @brief String Representation of the Client Object
            /// @return string
            string to_string() const{
                return "Cliente ID: " + id + ". Nome: " + name + ", Cognome: " + surname + ", Indirizzo: " + address + ", Email: " + email + ", Telefono: " + phone;
            };

            /// @brief CSV Representation of the Client Object
            /// @return string
            string to_csv() const{
                return id + DELIMITER + name + DELIMITER + surname + DELIMITER + address + DELIMITER + email + DELIMITER + phone;
            };
        };
}
#pragma endregion definitions