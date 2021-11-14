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

    ifstream in_stream;
    in_stream.open(plugboard_filename);
    if (in_stream.fail()) {
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }

    in_stream >> connection_a;
    in_stream >> connection_b;

    while (!in_stream.eof()) {
        
        addConnectionPair(connection_a, connection_b);

        in_stream >> connection_a;
        in_stream >> connection_b;
        
        number_of_connection_pairs++;

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

    if (connection1 = connection2) {
        exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION)
    }
    
    for (int count = 0; count < number_of_connection_pairs; count++) {
        if (connection1 = connection_pairs[count].connection_point_1 || connection1 = connection_pairs[count].connection_point_2
            || connection2 = connection_pairs[count].connection_point_1 || connection2 = connection_pairs[count].connection_point_2) {
                exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION)
        }

    }
    connection_pairs.push_back(ConnectionPair(connection1, connection2));
}

Reflector::Reflector(string reflector_filename){
    
    int connection_a;
    int connection_b;

    ifstream in_stream;
    in_stream.open(reflector_filename);
    if (in_stream.fail()) {
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }

    in_stream >> connection_a;
    in_stream >> connection_b;

    while (!in_stream.eof()) {
        
        addConnectionPair(connection_a, connection_b);

        in_stream >> connection_a;
        in_stream >> connection_b;
        
        number_of_connection_pairs++;

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
    connection_pairs[number_of_connection_pairs] = ConnectionPair(connection1, connection2);
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
    int output1 = plugboard -> getConnectingAlphabet(input_alphabet);
    current_rotor_node -> increaseOffsetByOne();
    int output2 = current_rotor_node -> getConnectingAlphabetFromRight(output1);
    current_rotor_node = current_rotor_node -> left;
    int output3 = current_rotor_node -> getConnectingAlphabetFromRight(output2);
    current_rotor_node = current_rotor_node -> left;
    int output4 = current_rotor_node -> getConnectingAlphabetFromRight(output3);
    int output5 = reflector -> getConnectingAlphabet(output4);
    int output6 = current_rotor_node -> getConnectingAlphabetFromLeft(output5);
    current_rotor_node = current_rotor_node -> right;
    int output7 = current_rotor_node -> getConnectingAlphabetFromLeft(output6);
    current_rotor_node = current_rotor_node -> right;
    int output8 = current_rotor_node -> getConnectingAlphabetFromLeft(output7);
    int output9 = plugboard -> getConnectingAlphabet(output8);


    return output9;
}

