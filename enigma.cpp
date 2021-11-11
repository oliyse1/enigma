#include <iostream>
#include "enigma.h"
#include <string>
#include <fstream>

using namespace std;

Plugboard::Plugboard(string plugboard_filename){
    
    int connection_a;
    int connection_b;

    ifstream in_stream;
    in_stream.open(plugboard_filename);

    in_stream >> connection_a;
    in_stream >> connection_b;

    while (!in_stream.eof()) {
        
        addConnectionPair(connection_a, connection_b);

        in_stream >> connection_a;
        in_stream >> connection_b;
        
        number_of_connection_pairs++;

    }
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
    connection_pairs[number_of_connection_pairs] = ConnectionPair(connection1, connection2);
}

Reflector::Reflector(string reflector_filename){
    
    int connection_a;
    int connection_b;

    ifstream in_stream;
    in_stream.open(reflector_filename);

    in_stream >> connection_a;
    in_stream >> connection_b;

    while (!in_stream.eof()) {
        
        addConnectionPair(connection_a, connection_b);

        in_stream >> connection_a;
        in_stream >> connection_b;
        
        number_of_connection_pairs++;

    }
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

Rotor::Rotor(string rotor_filename){
    
    int connection_a;
    
    ifstream in_stream;
    in_stream.open(rotor_filename);

    in_stream >> connection_a;

    int index = 0;

    while (!in_stream.eof() && number_of_connection_pairs < 26) {
        
        addConnectionPair(index, connection_a);

        in_stream >> connection_a;
        
        number_of_connection_pairs++;
        index++;

    }
}

int Rotor::getConnectingAlphabetFromRight(int input_alphabet) {

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

RotorListNode* createRotors(string rotor_filenames[], int number_of_rotors) {
    Rotor* rotor;
    RotorListNode* rotor_list_node = nullptr;
    for (int count = 0; count < number_of_rotors; count++) {
        //crate new rotor object
        rotor = new Rotor(rotor_filenames[count]);

        if (rotor_list_node == nullptr){
            rotor_list_node = new RotorListNode(*rotor);
        }
        else {
            RotorListNode* left = rotor_list_node;

            rotor_list_node = new RotorListNode(*rotor);
            left -> right = rotor_list_node;
            rotor_list_node -> left = left;
        }

    }

    return rotor_list_node;
}

