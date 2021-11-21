#ifndef ROTOR_H
#define ROTOR_H
#include <string>
#include <vector>
#include "connectionpair.h"

using namespace std;

//The Rotor class represents a rotor in an enigma machine. 
//The rotor's function is to map an alphabet to another connected alphabet (represented by integers 0-25)
//All 26 alphabets are connected to an alphabet on the other side of the rotor, so there are 26 pairs of alphabets exactly
//The rightmost rotor rotates once each time a key is pressed (before current flows)
//Rotors have initial positions and notches. If a notch of a rotor is hit during rotation, the rotor to its right also rotates once.
class Rotor {
private:
    std::vector<ConnectionPair> connection_pairs;
    int number_of_connection_pairs = 0;
    int rotor_pos = 0;
    std::vector<int> notches;
    int number_of_notches = 0;

public:
    
    //constructor takes in the name of the plugboard configuration file and initial rotor position
    Rotor(string const& rotor_filename, int rotor_pos);
    //addConnectionPair adds a pair of alphabets (represented by integers 0-25) to the connectionr_pairs vector, representing a connected pair in the rotor
    void addConnectionPair(int connection1, int connection2);
    //rotate causes a rotor to rotate by one position, thus rotor_pos increases by one
    //This is because rotors rotate in the opposite direction to the order in which the alphabet letters are inscribed on the rotor's ring
    void rotate();
    //mapForward returns the alphabet (represented by integers 0-25) on the left of the rotor connected to the input alphabet on the right of the rotor 
    int mapForward(int inputAlphabet);
    //mapBackward returns the alphabet (represented by integers 0-25) on the right of the rotor connected to the input alphabet on the left of the rotor 
    int mapBackward(int inputAlphabet);

     //A rotor contrains pointers which point to the left and/or right rotor if they exist
    Rotor* left = nullptr;
    Rotor* right = nullptr;

};

#endif