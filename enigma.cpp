#include <iostream>
#include "enigma.h"
#include <string>
#include <fstream>
#include <vector>
#include "errors.h"

using namespace std;



Enigma::Enigma(int argc, char** argv) {

    for (int count = 0; count < argc; count++) {

        temp_string = argv[count];
        if (temp_string.find(".pb") != string::npos) {
            plugboard_filename = temp_string;
        }
        else if (temp_string.find(".rf") != string::npos) {
            reflector_filename = temp_string;
        }
        else if (temp_string.find(".rot") != string::npos) {
            rotor_filenames.push_back(temp_string);
            number_of_rotors++;
        }
        else if (temp_string.find(".pos") != string::npos) {
            rotor_pos_filename = temp_string;
        }
    }

    if (plugboard_filename == "" || reflector_filename == "" || rotor_pos_filename == "") {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
        throw(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

   createComponents();
  
}

void Enigma::createComponents () {
    plugboard = new Plugboard(plugboard_filename);
    reflector = new Reflector(reflector_filename);
    current_rotor_node = createRotors();
}

Rotor* Enigma::createRotors() {
    current_rotor_node = nullptr;

    ifstream in_stream;
    in_stream.open(rotor_pos_filename);
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file (rotor position)" << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }
 
    int rotor_pos = 0;

    in_stream >> rotor_pos;

    for (int count = 0; count < number_of_rotors; count++) {
        //crate new rotor object
        if (in_stream.eof()) {
            cerr << "No starting position for rotor " << count << " in rotor position file: rotor.pos" << endl;
            throw(NO_ROTOR_STARTING_POSITION);
        }

        if (in_stream.fail()) {
            cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }
        if (rotor_pos < 0 || rotor_pos > 25) {
                cerr << "Invalid index (rotor position)" << endl;
                throw(INVALID_INDEX);
        }

        if (current_rotor_node == nullptr){
            current_rotor_node = new Rotor(rotor_filenames[count], rotor_pos);;
        }
        else {
            Rotor* left = current_rotor_node;
            current_rotor_node = new Rotor(rotor_filenames[count], rotor_pos);
            left -> right = current_rotor_node;
            current_rotor_node -> left = left;
        }
        in_stream >> rotor_pos; 
    }

    while (!in_stream.eof()) {
        if (in_stream.fail()) {
            cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }
        in_stream >> rotor_pos; 
    }

    in_stream.close();
    return current_rotor_node;
}

int Enigma::map(int input_alphabet){
    int output;
    output = plugboard -> getConnectingAlphabet(input_alphabet);
    if (current_rotor_node != nullptr) {
        current_rotor_node -> increaseOffsetByOne();
        output = current_rotor_node -> getConnectingAlphabetFromRight(output);
        while (current_rotor_node-> left != nullptr) {
            current_rotor_node = current_rotor_node -> left;
            output = current_rotor_node -> getConnectingAlphabetFromRight(output);
        }
    }
    output = reflector -> getConnectingAlphabet(output);
    if (current_rotor_node != nullptr) {
        output = current_rotor_node -> getConnectingAlphabetFromLeft(output);
        while (current_rotor_node-> right != nullptr) {
            current_rotor_node = current_rotor_node -> right;
            output = current_rotor_node -> getConnectingAlphabetFromLeft(output);
        }
    }
    output = plugboard -> getConnectingAlphabet(output);


    return output;
}

