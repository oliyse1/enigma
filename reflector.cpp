#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "reflector.h"
#include "connectionpair.h"
#include "errors.h"

using namespace std;


Reflector::Reflector(string const& reflector_filename){
    
    //declare temporary variables
    int input_int;
    int connection_a;
    int connection_b;
    int counter = 0;

    //open reflector configuration file
    fstream in_stream;
    in_stream.open(reflector_filename);

    //check if file failes to open
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file reflector.rf" << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }

    //read in numbers from reflector configuration file in pairs
    in_stream >> input_int;

    while (!in_stream.eof()){

        //check if file contains a non-numeric character
        if (in_stream.fail()) {
            cerr << "Non-numeric character in reflector file reflector.rf" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }

        //check if file contains numbers apart from 0-25
        if (input_int < 0 || input_int > 25) {
                cerr << static_cast<char>(input_int) << " is not a valid input character (input characters must be upper case letters A-Z) in reflector.rf" << endl;
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
    if ((counter % 2) != 0) {
        cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
        throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }

    //check if file contains 26 numbers or 13 pairs of numbers
    if (number_of_connection_pairs != 13) {
            cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
            throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }

    //close configuration file
    in_stream.close();
}


void Reflector::addConnectionPair(int connection1, int connection2){

    //check if configuration file attempts to connect a contact with itself
    if (connection1 == connection2) {
        cerr << "Invalid reflector mapping in reflector file: reflector.rf (check for duplicate numbers)" << endl;
        throw(INVALID_REFLECTOR_MAPPING);
    }
    
    //check if configuration file attempts to connect a contact with more than one other contact
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection1 == connection_pairs[count].connection_point_1 || connection1 == connection_pairs[count].connection_point_2
            || connection2 == connection_pairs[count].connection_point_1 || connection2 == connection_pairs[count].connection_point_2) {
                cerr << "Invalid reflector mapping in reflector file: reflector.rf (check for duplicate numbers)" << endl;
                throw(INVALID_REFLECTOR_MAPPING);
        }
    }

    //add this pair to connection_pairs
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}


int Reflector::map(int input_alphabet) const {

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
    