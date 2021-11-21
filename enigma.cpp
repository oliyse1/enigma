#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "enigma.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include "connectionpair.h"
#include "errors.h"

using namespace std;


Enigma::Enigma(int argc, char** argv) {

    //temporary variable to store filename string
    string temp_string;

    //allocate command line inputs to relevant component filename variables using the file extension of configuration files
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
            //record number of .rot files passed in
            number_of_rotors++;
        }
        else if (temp_string.find(".pos") != string::npos) {
            rotor_pos_filename = temp_string;
        }
    }

    //check if plugboard, reflector and rotor position configuration files have definitely been specified
    if (plugboard_filename == "" || reflector_filename == "" || rotor_pos_filename == "") {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
        throw(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

   createComponents();
  
}


void Enigma::createComponents () {
    plugboard = new Plugboard(plugboard_filename);
    reflector = new Reflector(reflector_filename);
    current_rotor = createRotors();
}


Rotor* Enigma::createRotors() {

    //temporary variable
    int rotor_pos = 0;

    //open rotor position configuration file
    ifstream in_stream;
    in_stream.open(rotor_pos_filename);

    //check if file failes to open
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file (rotor position)" << endl;
        throw(ERROR_OPENING_CONFIGURATION_FILE);
    }
 
    //read in numbers from rotor position (.pos) configuration file
    in_stream >> rotor_pos;

    for (int count = 0; count < number_of_rotors; count++) {

        //check if starting position is provided for each rotor
        if (in_stream.eof()) {
            cerr << "No starting position for rotor " << count << " in rotor position file: rotor.pos" << endl;
            throw(NO_ROTOR_STARTING_POSITION);
        }

        //check if file contains a non-numeric character
        if (in_stream.fail()) {
            cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }

        //check if file contains numbers apart from 0-25
        if (rotor_pos < 0 || rotor_pos > 25) {
                cerr << static_cast<char>(rotor_pos) << " is not a valid input character (input characters must be upper case letters A-Z) in rotor.pos" << endl;
                throw(INVALID_INDEX);
        }

        //create rotors and set pointers within rotors to link to each other correctly
        if (current_rotor == nullptr){
            current_rotor = new Rotor(rotor_filenames[count], rotor_pos);;
        }
        else {
            Rotor* left = current_rotor;
            current_rotor = new Rotor(rotor_filenames[count], rotor_pos);
            left -> right = current_rotor;
            current_rotor -> left = left;
        }
        in_stream >> rotor_pos; 
    }

    //check if the rest of the file contains a non-numeric character
    while (!in_stream.eof()) {
        if (in_stream.fail()) {
            cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
            throw(NON_NUMERIC_CHARACTER);
        }
        in_stream >> rotor_pos; 
    }

    //close configuration file
    in_stream.close();
    return current_rotor;
}


int Enigma::map(int input_alphabet){
    //temporary variable
    int output;

    //going through plugboard
    output = plugboard -> map(input_alphabet);

    //going through rotors (forward) if they exist
    if (current_rotor != nullptr) {
        //rotate before each input is mapped
        current_rotor -> rotate();
        output = current_rotor -> mapForward(output);
        while (current_rotor-> left != nullptr) {
            current_rotor = current_rotor -> left;
            output = current_rotor -> mapForward(output);
        }
    }

    //going through reflector
    output = reflector -> map(output);

    //going through rotors (backward) if they exist
    if (current_rotor != nullptr) {
        output = current_rotor -> mapBackward(output);
        while (current_rotor-> right != nullptr) {
            current_rotor = current_rotor -> right;
            output = current_rotor -> mapBackward(output);
        }
    }

    //going through plugboard
    output = plugboard -> map(output);

    return output;
}

Enigma::~Enigma() {

    //delete plugboard object
    delete plugboard;
    plugboard = nullptr;

    //delete reflector object
    delete reflector;
    reflector = nullptr;

    //delete rotor objects
    Rotor* right = nullptr;
    while (current_rotor != nullptr) {
        right = current_rotor;
        current_rotor = current_rotor -> left;
        delete right;
    }

    right = nullptr;
    current_rotor = nullptr;

}

