/*
CRM 

*/

#pragma region includes
#include <bits/stdc++.h>

#ifndef __INTERACTION_H_INCLUDED__
#define __INTERACTION_H_INCLUDED__

//Namespace directive
using namespace std;
#pragma endregion includes

#pragma region interfaces
class Interaction {

    private:
    
        string id;
        string type; // Appointment or Contract
        string date;
        string description;
    
    public:
        Interaction(string id, string type, string date, string description);
    
        // Getter and Setter Methods
        string get_interaction_id() const;
        void set_interaction_id(const string& id);
    
        string get_type() const;
        void set_type(const string& type);
    
        string get_date() const;
        void set_date(const string& date);
    
        string get_description() const;
        void set_description(const string& description);
    };

#pragma endregion interfaces
#endif