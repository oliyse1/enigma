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
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
    int input_int;
    int counter = 0;
    in_stream >> input_int;

    while (!in_stream.eof()){
 
        if (in_stream.fail()) {
            cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
            exit(NON_NUMERIC_CHARACTER);
        }

        if (input_int < 0 || input_int > 25) {
                cerr << static_cast<char>(input_int) << " is not a valid input character (input characters must be upper case letters A-Z)" << endl;
                exit(INVALID_INDEX);
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
            exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
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
        exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }
    
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection1 == connection_pairs[count].connection_point_1 || connection1 == connection_pairs[count].connection_point_2
            || connection2 == connection_pairs[count].connection_point_1 || connection2 == connection_pairs[count].connection_point_2) {
                cerr << "Impossible plugboard configuration" << endl;
                exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        }

    }
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}

Reflector::Reflector(string reflector_filename){
    
    int connection_a;
    int connection_b;

    fstream in_stream;
    in_stream.open(reflector_filename);
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file (reflector)" << endl;
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
    int input_int;
    int counter = 0;
    in_stream >> input_int;

    while (!in_stream.eof()){
        //unsure
        if (in_stream.fail()) {
            cerr << "Non-numeric character in reflector file reflector.rf" << endl;
            exit(NON_NUMERIC_CHARACTER);
        }

        if (input_int < 0 || input_int > 25) {
                cerr << "Invalid index (reflector)" << endl;
                exit(INVALID_INDEX);
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
        exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }

    if (number_of_connection_pairs < 13) {
            cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
            exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
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
        exit(INVALID_REFLECTOR_MAPPING);
    }
    
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection1 == connection_pairs[count].connection_point_1 || connection1 == connection_pairs[count].connection_point_2
            || connection2 == connection_pairs[count].connection_point_1 || connection2 == connection_pairs[count].connection_point_2) {
                cerr << "Invalid reflector mapping" << endl;
                exit(INVALID_REFLECTOR_MAPPING);
        }

    }
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}

Rotor::Rotor(string& rotor_filename, int rotor_pos){
    this -> rotor_pos = rotor_pos;

    fstream in_stream;
    in_stream.open(rotor_filename);
    if (in_stream.fail()) {
        cerr << "Error opening congifuration file (rotor)" << endl;
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
    int input_int;
    int counter = 0;

    in_stream >> input_int;

    while (number_of_connection_pairs < 26){
        //unsure
        if (in_stream.eof()) {
            cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
            exit(INVALID_ROTOR_MAPPING);
        }
        if (in_stream.fail()) {
            cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
            exit(NON_NUMERIC_CHARACTER);
        }
        if (input_int < 0 || input_int > 25) {
                cerr << "Invalid index (rotor)" << endl;
                exit(INVALID_INDEX);
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
                exit(INVALID_ROTOR_MAPPING );
        }

    }
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}

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
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
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
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
 
    int rotor_pos = 0;

    in_stream >> rotor_pos;

    for (int count = 0; count < number_of_rotors; count++) {
        //crate new rotor object
        if (in_stream.eof()) {
            cerr << "No starting position for rotor " << count << " in rotor position file: rotor.pos" << endl;
            exit(NO_ROTOR_STARTING_POSITION);
        }

        if (in_stream.fail()) {
            cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
            exit(NON_NUMERIC_CHARACTER);
        }
        if (rotor_pos < 0 || rotor_pos > 25) {
                cerr << "Invalid index (rotor position)" << endl;
                exit(INVALID_INDEX);
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
            exit(NON_NUMERIC_CHARACTER);
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

