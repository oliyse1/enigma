#include <iostream>
#include "enigma.h"
#include <fstream>
#include <string>
#include <vector>
#include "errors.h"

using namespace std;

int main(int argc, char** argv) {

    try {
        Enigma enigma(argc, argv);
 
        char output;

        char input;

        while (cin >> input) {
            if (input == ' '){
                continue;
            }
            else if (input < 'A' || input > 'Z') {
                cerr << input << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
                throw(INVALID_INPUT_CHARACTER);
            }
            output = static_cast<char>(enigma.map(static_cast<int>(input - 'A')) + static_cast<int>('A'));
            cout << output ;
        }

    }

    catch (int e) {
        return e;
    }


return NO_ERROR;

}