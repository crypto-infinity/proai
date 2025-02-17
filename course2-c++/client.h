/*
CRM 

*/

#pragma region includes
#include <bits/stdc++.h>

#ifndef __CLIENT_H_INCLUDED__
#define __CLIENT_H_INCLUDED__

using namespace std;
#pragma endregion includes

#pragma region interfaces
class Client {
    private:
        string client_id;
        string first_name;
        string last_name;
        string address;
        string email;
        string phone_number;
    
    public:
        Client(string id, string first_name, string last_name, string address, string email, string phone_number);
    
        // Getter and Setter Methods
        string get_client_id() const;
        void set_client_id(const string& id);
    
        string get_first_name() const;
        void set_first_name(const string& first_name);
    
        string get_last_name() const;
        void set_last_name(const string& last_name);
    
        string get_address() const;
        void set_address(const string& address);
    
        string get_email() const;
        void set_email(const string& email);
    
        string get_phone_number() const;
        void set_phone_number(const string& phone_number);
    };

#pragma endregion interfaces
#endif
    