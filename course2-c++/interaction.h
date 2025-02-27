/*
Interaction Class, represents an interaction between the company and the client.

Gabriele Scorpaniti, 2025
*/

#pragma region includes
#include <bits/stdc++.h>

#ifndef __INTERACTION_H_INCLUDED__
#define __INTERACTION_H_INCLUDED__

#include "utility.h"

//Namespace directive
using namespace std;
#pragma endregion includes

#pragma region Interaction

namespace InsuraPro{

    /// @brief Interaction Class, represents an interaction between the company and the client.
    class Interaction : Utility {
        private:
        
            /// @brief Interaction ID, generated automatically
            string id = "int-" + generate_random_string(10);
    
            /// @brief Interaction Name
            string name;

            /// @brief Interaction Type, can be "appuntamento" or "contratto"
            string type;

            /// @brief Interaction Date
            string date;

            /// @brief Interaction Description
            string description;
        
        public:

            /// @brief Constructor, instantiates a new Interaction object
            /// @param _name Interaction Name, required
            /// @param _type Type, can be "appuntamento" or "contratto", defaults to "appuntamento"
            /// @param _date Date, defaults to ""
            /// @param _description Description, defaults to ""
            Interaction(string _name, string _type="appuntamento", string _date="", string _description=""){
    
                set_name(_name);
                set_type(_type);
                set_date(_date);
                set_description(_description);
    
            };

            /// @brief Constructor, instantiates a new Interaction object with an ID
            /// @param _id Interaction ID, required
            /// @param _name Interaction Name, required
            /// @param _type Type, can be "appuntamento" or "contratto", defaults to "appuntamento"
            /// @param _date Date, defaults to ""
            /// @param _description Description, defaults to ""
            Interaction(string _id, string _name, string _type="appuntamento", string _date="", string _description=""){
                
                id = _id;
                set_type(_type);
                set_date(_date);
                set_description(_description);
    
            };
        
            #pragma region Getters

            /// @brief Getter Method for the Interaction ID
            /// @return string
            string get_id(){
                return id;
            };

            /// @brief Getter Method for Name
            /// @return string
            string get_name(){
                return name;
            };
        
            /// @brief Getter Method for the Interaction Type
            /// @return string
            string get_type(){
                return type;
            };

            /// @brief Getter Method for the Interaction Date
            /// @return string
            string get_date(){
                return date;
            };

            /// @brief Getter Method for the Interaction Description
            /// @return string
            string get_description(){
                return description;
            };
    
            #pragma endregion Getters

            #pragma region Setters

            /// @brief Setter Method for Name
            /// @param _name string, the new name
            string set_name(string _name){
                if(_name.empty()){
                    throw std::invalid_argument("Il nome non può essere vuoto");
                }
                name = _name;
                return name;
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
        
            /// @brief Setter Method for the Interaction Date
            /// @param _date string, the new date
            string set_date(string _date){
                date = _date;
                return date;
            };
    
            /// @brief Setter Method for the Interaction Description
            /// @param _description string, the new description
            string set_description(string _description){
                description = _description;
                return description;
            };

            #pragma endregion Setters

            /// @brief Returns a string representation of the Interaction object
            /// @return string
            string to_string(){
                return "Interazione ID: " + id + ", Nome: " + name + ". Tipo: " + type + ", Data: " + date + ", Descrizione: " + description;
            };

        };
}

#pragma endregion Interaction

#endif