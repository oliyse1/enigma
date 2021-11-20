#include <iostream>
#include "enigma.h"
#include <string>
#include <fstream>
#include <vector>
#include "errors.h"

using namespace std;


Reflector::Reflector(string reflector_filename){
    
    int connection_a;
    int connection_b;

    fstream in_stream;
    in_stream.open(reflector_filename);
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file (reflector)" << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }
    int input_int;
    int counter = 0;
    in_stream >> input_int;

    while (!in_stream.eof()){
        //unsure
        if (in_stream.fail()) {
            cerr << "Non-numeric character in reflector file reflector.rf" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }

        if (input_int < 0 || input_int > 25) {
                cerr << "Invalid index (reflector)" << endl;
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
        counter++;
        in_stream >> input_int;
        
    }


    if ((counter % 2) != 0) {
        cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
        throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }

    if (number_of_connection_pairs < 13) {
            cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
            throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }



    in_stream.close();
}

int Reflector::getConnectingAlphabet(int input_alphabet) {

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
    

void Reflector::addConnectionPair(int connection1, int connection2){
    if (connection1 == connection2) {
        cerr << "Invalid reflector mapping" << endl;
        throw(INVALID_REFLECTOR_MAPPING);
    }
    
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection1 == connection_pairs[count].connection_point_1 || connection1 == connection_pairs[count].connection_point_2
            || connection2 == connection_pairs[count].connection_point_1 || connection2 == connection_pairs[count].connection_point_2) {
                cerr << "Invalid reflector mapping" << endl;
                throw(INVALID_REFLECTOR_MAPPING);
        }

    }
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}