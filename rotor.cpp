#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "rotor.h"
#include "connectionpair.h"
#include "errors.h"

using namespace std;

Rotor::Rotor(string const& rotor_filename, int rotor_pos){

    //set initial rotor position
    this -> rotor_pos = rotor_pos;

    //declare temporary variables
    int input_int;
    int counter = 0;

    //open plugboard configuration file
    fstream in_stream;
    in_stream.open(rotor_filename);

    //check if file failes to open
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file rotor.rot" << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }
    
    //read in numbers from rotor configuration file up to 26 numbers
    in_stream >> input_int;

    //only configure rotor mappings using first 26 numebrs in configuration file
    while (number_of_connection_pairs < 26){
        
        //check if there are less than 26 numbers in cofiguration file
        if (in_stream.eof()) {
            cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
            throw(INVALID_ROTOR_MAPPING);
        }

        //check if file contains a non-numeric character
        if (in_stream.fail()) {
            cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }

        //check if file contains numbers apart from 0-25
        if (input_int < 0 || input_int > 25) {
                cerr << static_cast<char>(input_int) << " is not a valid input character (input characters must be upper case letters A-Z) in rotor.rot" << endl;
                throw(INVALID_INDEX);
        }

        //add a pair to connection_pairs
        //based on configuration file, the number in the file represents a number on the left of the rotor, and the index of that number represents the number on the right of the rotor
        addConnectionPair(counter, input_int);
        counter++;
        number_of_connection_pairs++;
        
        in_stream >> input_int;

    }

    //after the first 26 numbers in the configuration file, the remaining numbers are notches
    //read in notches if there are any and add them to the notch vector
    int notch = input_int;
    
    while (!in_stream.eof()) {
        notches.push_back(notch);
        in_stream >> notch;
        number_of_notches++;
    }

    //close configuration file
    in_stream.close();
}


void Rotor::addConnectionPair(int connection1, int connection2){
    
    //check if the file attempts to map more than one input to the same output, or does not provide a mapping for some input
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection2 == connection_pairs[count].connection_point_2) {
                cerr << "Invalid mapping of input "<< connection1 << " to output " << connection2 <<" (output " << connection2 << " is already mapped to from input " << connection_pairs[count].connection_point_1 << ") in rotor file: rotor.rot" << endl;
                throw(INVALID_ROTOR_MAPPING );
        }
    }

    //add this pair to connection_pairs
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}


void Rotor::rotate() {
    
    //position of current rotor increases by one
    rotor_pos = (rotor_pos + 1) % 26;

    //check if any notches are hit, if so rotate the left rotor once, if a left rotor exists
    for (int count = 0; count < number_of_notches; count++) {
        if ((this -> left != nullptr) && (rotor_pos == notches[count])) {
            this -> left -> rotate();
        }
    }
}


int Rotor::mapForward(int input_alphabet) {

    //temporary variable
    int output_alphabet;

    //get the alphabet at which current enters the rotor
    input_alphabet = (input_alphabet + rotor_pos) % 26;
    
    //map alphabets within the rotor from left to right
    //connectoin_point_1 is on the right of the rotor, connection_point_2 is on the left of the rotor
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (input_alphabet == connection_pairs[count].connection_point_1) {
            output_alphabet = connection_pairs[count].connection_point_2;
        }
    }

    //get the absolute position at which current leaves the rotor
    output_alphabet = (26 + output_alphabet - rotor_pos) % 26;

    return output_alphabet;
}


int Rotor::mapBackward(int input_alphabet) {

    //temporary variable
    int output_alphabet;

    //get the alphabet at which current enters the rotor
    input_alphabet = (input_alphabet + rotor_pos) % 26;
    
    //map alphabets within the rotor from right to left
    //connectoin_point_1 is on the right of the rotor, connection_point_2 is on the left of the rotor
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (input_alphabet == connection_pairs[count].connection_point_2) {
            output_alphabet = connection_pairs[count].connection_point_1;
        }
    }

    //get the absolute position at which current leaves the rotor
    output_alphabet = (26 + output_alphabet - rotor_pos) % 26;

    return output_alphabet;    
}