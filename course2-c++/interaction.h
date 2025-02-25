/*
CRM 

*/

#pragma region includes
#include <bits/stdc++.h>

#ifndef __INTERACTION_H_INCLUDED__
#define __INTERACTION_H_INCLUDED__

#include "utility.h"

//Namespace directive
using namespace std;
#pragma endregion includes

#pragma region interfaces

namespace InsuraPro{
    
    class Interaction : Utility {

        private:
        
            string id = "int-" + generate_random_string(10);
    
            string type; // Appuntamento or Contratto
            string date;
            string description;
        
        public:

            Interaction(string type, string date="", string description=""){
    
                set_type(type);
                set_date(date);
                set_description(description);
    
            };

            Interaction(string _id, string type, string date="", string description=""){
                
                id = _id;
                set_type(type);
                set_date(date);
                set_description(description);
    
            };
        
            // Getter and Setter Methods

            /// @brief Getter Method for the Interaction ID
            /// @return string
            string get_id(){
                return id;
            };
        
            /// @brief Getter Method for the Interaction Type
            /// @return string
            string get_type(){
                return type;
            };
    
            /// @brief Setter Method for the Interaction Type
            /// @param _type string, the new type
            string set_type(string _type){
                if(
                    _type.empty() 
                    || (_type != "appuntamento" && _type != "contratto")
                ){
                    throw std::invalid_argument("Il tipo può essere solamente ""appuntamento"" o ""contratto""");
                }
                type = _type;
                return type;
            };
        
            /// @brief Getter Method for the Interaction Date
            /// @return string
            string get_date(){
                return date;
            };
    
            /// @brief Setter Method for the Interaction Date
            /// @param _date string, the new date
            string set_date(string _date){
                date = _date;
                return date;
            };
    
            /// @brief Getter Method for the Interaction Description
            /// @return string
            string get_description(){
                return description;
            };
    
            /// @brief Setter Method for the Interaction Description
            /// @param _description string, the new description
            string set_description(string _description){
                description = _description;
                return description;
            };

            /// @brief Returns a string representation of the Interaction object
            /// @return string
            string to_string(){
                return "Interazione ID: " + id + ". Tipo: " + type + ", Data: " + date + ", Descrizione: " + description;
            };
        };
}

#pragma endregion interfaces
#endif