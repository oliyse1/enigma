#include <iostream>
#include <fstream>
#include "enigma.h"
#include "errors.h"

using namespace std;

int main(int argc, char** argv) {

    try {
        //create enigma object
        Enigma enigma(argc, argv);
 
        //temporary variables for input and output characters
        char output;
        char input;

        while (cin >> input) {
            //remove any whitespaces
            if (input == ' '){
                continue;
            }

            //check if input is valid
            else if (input < 'A' || input > 'Z') {
                cerr << input << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
                throw(INVALID_INPUT_CHARACTER);
            }

            //obtain output character from enigma machine based on input character
            output = static_cast<char>(enigma.map(static_cast<int>(input - 'A')) + static_cast<int>('A'));
            cout << output ;
        }

    }

    //catch and return any errors thrown
    catch (int e) {
        return e;
    }


return NO_ERROR;

}