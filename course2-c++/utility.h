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

    /// @brief Utility Class Definition, represents the Client object with custom methods for manipulation.
    class Utility{
        public:
            /// @brief Constant for the CSV Delimiter
            const char DELIMITER = ',';

            /// @brief Regular Expression for the Email
            string email_regex = R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)";
            const regex EMAIL_REGEX{email_regex};

            /// @brief Regular Expression for the Phone Number
            string phone_regex = R"(^\+(?:[0-9] ?){6,14}[0-9]$)";
            const regex PHONE_REGEX{phone_regex};

            /// @brief Random string generator, source: https://medium.com/@ryan_forrester_/c-random-string-generation-practical-guide-e7e789b348d4
            /// @param length random string lenght (int)
            /// @return the generated random string
            string generate_random_string(size_t length) {
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
    };
}
#pragma endregion definitions