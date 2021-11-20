#include <iostream>
#include "enigma.h"
#include <string>
#include <fstream>
#include <vector>
#include "errors.h"

using namespace std;

Rotor::Rotor(string& rotor_filename, int rotor_pos){
    this -> rotor_pos = rotor_pos;

    fstream in_stream;
    in_stream.open(rotor_filename);
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file (rotor)" << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }
    int input_int;
    int counter = 0;

    in_stream >> input_int;

    while (number_of_connection_pairs < 26){
        //unsure
        if (in_stream.eof()) {
            cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
            throw(INVALID_ROTOR_MAPPING);
        }
        if (in_stream.fail()) {
            cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }
        if (input_int < 0 || input_int > 25) {
                cerr << "Invalid index (rotor)" << endl;
                throw(INVALID_INDEX);
        }

        addConnectionPair(counter, input_int);
        number_of_connection_pairs++;
        
        in_stream >> input_int;

        counter++;
    }

    int notch = input_int;
    

    while (!in_stream.eof()) {
        notches.push_back(notch);
        in_stream >> notch;
        number_of_notches++;
    }

    in_stream.close();
}


void Rotor::increaseOffsetByOne() {
    
    rotor_pos = (rotor_pos + 1) % 26;
    
    for (int count = 0; count < number_of_notches; count++) {

        if ((this -> left != nullptr) && (rotor_pos == notches[count])) {
            this -> left -> increaseOffsetByOne();
        }
    }
}

int Rotor::getConnectingAlphabetFromRight(int input_alphabet) {
    int output_alphabet;

    input_alphabet = (input_alphabet + rotor_pos) % 26;
    

    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (input_alphabet == connection_pairs[count].connection_point_1) {
            output_alphabet = connection_pairs[count].connection_point_2;
        }
    }

    output_alphabet = (26 + output_alphabet - rotor_pos) % 26;

    return output_alphabet;
}

int Rotor::getConnectingAlphabetFromLeft(int input_alphabet) {

    int output_alphabet;

    input_alphabet = (input_alphabet + rotor_pos) % 26;
    

    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (input_alphabet == connection_pairs[count].connection_point_2) {
            output_alphabet = connection_pairs[count].connection_point_1;
        }
    }

    output_alphabet = (26 + output_alphabet - rotor_pos) % 26;

    return output_alphabet;    
}
    

void Rotor::addConnectionPair(int connection1, int connection2){
    
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection2 == connection_pairs[count].connection_point_2) {
                cerr << "Invalid mapping of input "<< connection1 << " to output " << connection2 <<" (output " << connection2 << " is already mapped to from input " << connection_pairs[count].connection_point_1 << ") in rotor file: rotor.rot" << endl;
                throw(INVALID_ROTOR_MAPPING );
        }

    }
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}