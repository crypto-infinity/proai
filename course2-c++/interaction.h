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
        
            const string id = "int-" + generate_random_string(10);
    
            string type; // Appointment or Contract
            string date;
            string description;
        
        public:
            Interaction(string type, string date="", string description=""){
    
                set_type(type);
                set_date(date);
                set_description(description);
    
            };
        
            // Getter and Setter Methods
        
            /// @brief Getter Method for the Interaction Type
            /// @return string
            string get_type(){
                return type;
            };
    
            /// @brief Setter Method for the Interaction Type
            /// @param _type string, the new type
            void set_type(const string& _type){
                if(
                    _type.empty() 
                    || (_type != "Appointment" && _type != "Contract")
                ){
                    throw std::invalid_argument("Il tipo può essere ""Appointment"" o ""Contract"".");
                }
                type = _type;
            };
        
            /// @brief Getter Method for the Interaction Date
            /// @return string
            string get_date(){
                return date;
            };
    
            /// @brief Setter Method for the Interaction Date
            /// @param _date string, the new date
            void set_date(const string& _date){
                if(_date.empty()){
                    throw std::invalid_argument("La data deve essere valida!");
                }
                date = _date;
            };
    
            /// @brief Getter Method for the Interaction Description
            /// @return string
            string get_description(){
                return description;
            };
    
            /// @brief Setter Method for the Interaction Description
            /// @param _description string, the new description
            void set_description(const string& _description){
                if(_description.empty()){
                    throw std::invalid_argument("La descrizione deve essere valida!");
                }
                description = _description;
            };
        };
}

#pragma endregion interfaces
#endif