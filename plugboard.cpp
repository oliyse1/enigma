#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "plugboard.h"
#include "connectionpair.h"
#include "errors.h"

using namespace std;

Plugboard::Plugboard(string const& plugboard_filename){

    //declare temporary variables
    int input_int;
    int connection_a;
    int connection_b;
    int counter = 0;

    //open plugboard configuration file
    fstream in_stream;
    in_stream.open(plugboard_filename);

    //check if file failes to open
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file plugboard.pb" << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }

    //read in numbers from plugboard configuration file in pairs
    in_stream >> input_int;

    while (!in_stream.eof()){
        
        //check if file contains a non-numeric character
        if (in_stream.fail()) {
            cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }

        //check if file contains numbers apart from 0-25
        if (input_int < 0 || input_int > 25) {
                cerr << static_cast<char>(input_int) << " is not a valid input character (input characters must be upper case letters A-Z)" << endl;
                throw(INVALID_INDEX);
        }

        //set first value of a pair
        if (counter % 2 == 0){
            connection_a = input_int;
        }
        else {

            //set second value of a pair
            connection_b = input_int;
            //add the pair to connection_pairs
            addConnectionPair(connection_a, connection_b);
            number_of_connection_pairs++;
        }
        counter++;

        in_stream >> input_int;
        
    }

    //check if file contains an odd number of numbers (should be even as in pairs)
    if (counter % 2 != 0) {
            cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
            throw(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }

    //close configuration file
    in_stream.close();
   
}
  

void Plugboard::addConnectionPair(int connection1, int connection2){

    //check if configuration file attempts to connect a contact with itself
    if (connection1 == connection2) {
        cerr << "Impossible plugboard configuration in plugboard file plugboard.pb (check for duplicate numbers)" << endl;
        throw(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }
    
    //check if configuration file attempts to connect a contact with more than one other contact
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection1 == connection_pairs[count].connection_point_1 || connection1 == connection_pairs[count].connection_point_2
            || connection2 == connection_pairs[count].connection_point_1 || connection2 == connection_pairs[count].connection_point_2) {
                cerr << "Impossible plugboard configuration in plugboard file plugboard.pb (check for duplicate numbers)" << endl;
                throw(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        }
    }

    //add this pair to connection_pairs
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}


int Plugboard::map(int input_alphabet) const {

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