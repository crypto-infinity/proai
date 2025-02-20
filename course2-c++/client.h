/*
Client Class Interface
This class represents the Client object with custom methods for manipulation.
*/

#pragma region includes

#include <bits/stdc++.h>

#include "utility.h"

using namespace std;

#pragma endregion includes

#pragma region definitions
namespace InsuraPro{
    /// @brief Client Class Definition, represents the Client object with custom methods for manipulation. 
    class Client : Utility {
        private:
            const string id = "cli-" + generate_random_string(10);

            string name;
            string address;
            string vat;
            string company_email;
            string company_phone;

            vector<string> contact_ids;

            string append_contact_ids() const {
                string ids = "[";
                for(string contact : contact_ids){
                    ids += contact;
                    ids += ";";
                }
                ids += "]";
                return ids;
            }
        
        public:

            Client(string _name, string _address, string _vat, string _company_email, string _company_phone, vector<string> _contact_ids){
                
                set_name(_name);
                set_address(_address);
                set_vat(_vat);
                set_company_email(_company_email);
                set_company_phone(_company_phone);

                set_contacts(_contact_ids);

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

            /// @brief Getter Method for the Client Address
            /// @return string
            string get_address() const{
                return address;
            };

            /// @brief Getter Method for the Client VAT
            /// @return string
            string get_vat() const{
                return vat;
            };

            /// @brief Getter Method for the Client Company Email
            /// @return string
            string get_company_email() const{
                return company_email;
            };

            /// @brief Getter Method for the Client Company Phone
            /// @return string
            string get_company_phone() const{
                return company_phone;
            };

            /// @brief Getter Method for the Client Contacts
            /// @return vector<Contact>
            vector<string> get_contact_ids() const{
                return contact_ids;
            };


            /*
            Setters Methods
            */

            /// @brief Setter Method for the Client Name
            /// @param _name string, the new name
            string set_name(string _name){
                if(_name.empty()){
                    throw std::invalid_argument("Il nome deve essere valido!");
                }
                name = _name;
                return name;
            };

            /// @brief Setter Method for the Client Address
            /// @param _address string, the new address
            string set_address(string _address){
                if(_address.empty()){
                    throw std::invalid_argument("L'indirizzo deve essere valido!");
                }
                address = _address;
                return address;
            };

            /// @brief Setter Method for the Client VAT
            /// @param _vat string, the new VAT
            string set_vat(string _vat){
                if(_vat.empty()){
                    throw std::invalid_argument("La partita IVA deve essere valida!");
                }
                vat = _vat;
                return vat;
            };

            /// @brief Setter Method for the Client Company Email
            /// @param _company_email string, the new company email
            string set_company_email(string _company_email){
                if( _company_email.empty() ||
                    !regex_match(_company_email, EMAIL_REGEX)
                  )
                {
                    throw std::invalid_argument("L'email non è valida.");
                }
                company_email = _company_email;
                return company_email;
            };

            /// @brief Setter Method for the Client Company Phone
            /// @param _company_phone string, the new company phone
            string set_company_phone(string _company_phone){
                if( _company_phone.empty() ||
                    !regex_match(_company_phone, PHONE_REGEX)
                  )
                {
                    throw std::invalid_argument("Il numero di telefono non è valido.");
                }
                company_phone = _company_phone;
                return company_phone;
            };

            /// @brief Setter Method for the Client Contacts
            /// @param _contacts vector<string>, the new contact ids list
            vector<string> set_contacts(vector<string> _contact_ids){
                contact_ids = _contact_ids;
                return contact_ids;
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
                return "Cliente ID: " + id + ". Nome: " + name + ", Indirizzo: " + address + ", VAT: " + vat + ", Email: " + company_email + ", Telefono: " + company_phone;
            };

            /// @brief CSV Representation of the Client Object
            /// @return string
            string to_csv() const{
                return id + DELIMITER + name + DELIMITER + address + DELIMITER + vat + DELIMITER + company_email + DELIMITER + company_phone + append_contact_ids();
            };

        };
}
#pragma endregion definitions