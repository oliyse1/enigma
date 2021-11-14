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
    while (in_stream >> input_int){
        //unsure
        if (!in_stream) {
            cerr << "Non numeric character (plugboard)" << endl;
            exit(NON_NUMERIC_CHARACTER);
        }

        if (input_int < 0 || input_int > 25) {
                cerr << "Invalid index (plugboard)" << endl;
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
    }

    if (counter % 2 != 0) {
            cerr << "Incorrect number of plugboard parameters (plugboard)" << endl;
            exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }

    in_stream.close();

    // ifstream in_stream;
    // in_stream.open(plugboard_filename);
    // if (in_stream.fail()) {
    //     exit(ERROR_OPENING_CONFIGURATION_FILE);
    // }

    // if(!in_stream.eof()) {

    //     if(in_stream.peek() != EOF && !isdigit(in_stream.peek())) {
    //         cerr << "Non numeric character" << endl;
    //         exit(NON_NUMERIC_CHARACTER);
    //     }
    //     in_stream >> connection_a;

    //     if(in_stream.eof()) {
    //         cerr << "Incorrect number of plugboard parameters" << endl;
    //         exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    //     }

    //     if(in_stream.peek() != EOF && !isdigit(in_stream.peek())) {
    //         cerr << "Non numeric character" << endl;
    //         exit(NON_NUMERIC_CHARACTER);
    //     }

    //     in_stream >> connection_b;

    //     while (!in_stream.eof()) {

    //         if (connection_a < 0 || connection_a > 25 || connection_b < 0 || connection_b > 25) {
    //             cerr << "Invalid index" << endl;
    //             exit(INVALID_INDEX);
    //         }
        
    //         addConnectionPair(connection_a, connection_b);
    //         number_of_connection_pairs++;

    //         if(in_stream.peek() != EOF && !isdigit(in_stream.peek())) {
    //             cerr << "Non numeric character" << endl;
    //             exit(NON_NUMERIC_CHARACTER);
    //         }
    //         in_stream >> connection_a;

    //         if(in_stream.eof()) {
    //             cerr << "Incorrect number of plugboard parameters" << endl;
    //             exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    //         }

    //          if(in_stream.peek() != EOF && !isdigit(in_stream.peek())) {
    //             cerr << "Non numeric character" << endl;
    //             exit(NON_NUMERIC_CHARACTER);
    //         }

    //         in_stream >> connection_b;

    //     }
    // }


    // in_stream.close();
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
    while (in_stream >> input_int){
        //unsure
        if (!in_stream) {
            cerr << "Non numeric character (reflector)" << endl;
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
    }

    if (counter % 2 != 0 || number_of_connection_pairs != 13) {
            cerr << "Incorrect number of reflector parameters (relfector)" << endl;
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

    int connection_a;
    
    ifstream in_stream;
    in_stream.open(rotor_filename);
    if (in_stream.fail()) {
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }

    in_stream >> connection_a;

    int index = 0;

    while (number_of_connection_pairs < 26) {
        
        addConnectionPair(index, connection_a);

        in_stream >> connection_a;
        
        number_of_connection_pairs++;
        index++;

    }

    int notch = connection_a;
    

    while (!in_stream.eof()) {
        notches.push_back(notch);
        in_stream >> notch;
        number_of_notches++;
    }

    in_stream.close();

}

void Rotor::increaseOffsetByOne() {
    rotor_pos++ ;
    for (int count = 0; count < number_of_notches; count++) {

        if ((this -> left != nullptr) && (rotor_pos == notches[count])) {
            this -> left -> increaseOffsetByOne();
        }
    }
}

int Rotor::getConnectingAlphabetFromRight(int input_alphabet) {

    input_alphabet = (input_alphabet + rotor_pos) % 26;

    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (input_alphabet == connection_pairs[count].connection_point_1) {
            return connection_pairs[count].connection_point_2;
        }
    }

    return input_alphabet;
}

int Rotor::getConnectingAlphabetFromLeft(int input_alphabet) {

    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (input_alphabet == connection_pairs[count].connection_point_2) {
            return connection_pairs[count].connection_point_1;
        }
    }

    return input_alphabet;
}
    

void Rotor::addConnectionPair(int connection1, int connection2){
    connection_pairs[number_of_connection_pairs] = ConnectionPair(connection1, connection2);
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
            rotor_filenames[number_of_rotors] = temp_string;
            number_of_rotors++;
        }
        else if (temp_string.find(".pos") != string::npos) {
            rotor_pos_filename = temp_string;
        }
    }

    if (plugboard_filename == "" || reflector_filename == "" || rotor_pos_filename == "") {
        cerr << "Insufficient number of command line arguments provided as parameters" << endl;
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
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }
    int rotor_pos = 0;

    in_stream >> rotor_pos;

    for (int count = 0; count < number_of_rotors && !in_stream.eof(); count++) {
        //crate new rotor object
        

        if (current_rotor_node == nullptr){
            current_rotor_node = new Rotor(rotor_filenames[count], rotor_pos);;
            in_stream >> rotor_pos; 
        }
        else {
            Rotor* left = current_rotor_node;
            current_rotor_node = new Rotor(rotor_filenames[count], rotor_pos);
            left -> right = current_rotor_node;
            current_rotor_node -> left = left;
        }

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

