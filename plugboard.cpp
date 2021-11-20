#include <iostream>
#include "enigma.h"
#include <string>
#include <fstream>
#include <vector>
#include "errors.h"

using namespace std;

Plugboard::Plugboard(string plugboard_filename){
    
    //unsure
    // addConnectionPair(100, 100);


    int connection_a;
    int connection_b;

    fstream in_stream;
    in_stream.open(plugboard_filename);
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file (plugboard)" << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }
    int input_int;
    int counter = 0;
    in_stream >> input_int;

    while (!in_stream.eof()){
 
        if (in_stream.fail()) {
            cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }

        if (input_int < 0 || input_int > 25) {
                cerr << static_cast<char>(input_int) << " is not a valid input character (input characters must be upper case letters A-Z)" << endl;
                throw(INVALID_INDEX);
        }

        if (counter % 2 == 0){
            connection_a = input_int;
        }
        else {

            connection_b = input_int;
            addConnectionPair(connection_a, connection_b);
            number_of_connection_pairs++;
        }
        in_stream >> input_int;
        counter++;
    }

    if (counter % 2 != 0) {
            cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
            throw(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }

    in_stream.close();

    
}

int Plugboard::getConnectingAlphabet(int input_alphabet) {
    

    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (input_alphabet == connection_pairs[count].connection_point_1) {
            return connection_pairs[count].connection_point_2;
        }
        else if (input_alphabet == connection_pairs[count].connection_point_2){
            return connection_pairs[count].connection_point_1;
        }
    }

    return input_alphabet;
}
    

void Plugboard::addConnectionPair(int connection1, int connection2){

    if (connection1 == connection2) {
        cerr << "Impossible plugboard configuration" << endl;
        throw(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }
    
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection1 == connection_pairs[count].connection_point_1 || connection1 == connection_pairs[count].connection_point_2
            || connection2 == connection_pairs[count].connection_point_1 || connection2 == connection_pairs[count].connection_point_2) {
                cerr << "Impossible plugboard configuration" << endl;
                throw(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        }

    }
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}