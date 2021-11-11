#ifndef ENIGMA_H
#define ENIGMA_H
#include <string>
using namespace std;

class ConnectionPair {
   
public:
    int connection_point_1 = 0;
    int connection_point_2 = 0;
    ConnectionPair(){}
    ConnectionPair(int connectionPoint1, int connectionPoint2) : connection_point_1(connectionPoint1), connection_point_2(connectionPoint2){}
};

class Plugboard { //reflector can use the same class

public:
    ConnectionPair connection_pairs[13];
    int number_of_connection_pairs = 0;
    Plugboard(string plugboard_filename);
    int getConnectingAlphabet(int inputAlphabet);
    void addConnectionPair(int connection1, int connection2);

};

class Reflector { //reflector can use the same class

public:
    ConnectionPair connection_pairs[13];
    int number_of_connection_pairs = 0;
    Reflector(string reflector_filename);
    int getConnectingAlphabet(int inputAlphabet);
    void addConnectionPair(int connection1, int connection2);
};

class Rotor { //reflector can use the same class

public:
    ConnectionPair connection_pairs[26];
    int number_of_connection_pairs = 0;
    Rotor(string rotor_filename);
    int getConnectingAlphabetFromRight(int inputAlphabet);
    int getConnectingAlphabetFromLeft(int inputAlphabet);
    void addConnectionPair(int connection1, int connection2);
};

class RotorListNode {

public:
    Rotor rotor;
    RotorListNode(Rotor& rotor):rotor(rotor){}
    RotorListNode* left = nullptr;
    RotorListNode* right = nullptr;
};

RotorListNode* createRotors(string rotor_filenames[], int number_of_rotors); 


#endif