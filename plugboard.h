#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include <string>
#include <vector>
#include "connectionpair.h"

using namespace std;

//The Plugboard class represents the plugboard in an enigma machine. 
//The plugboard's function is to swap connected alphabets (represented by integers 0-25), and if an input alphabet is not connected to another alphabet, returns the input alphabet
class Plugboard {
private:
    std::vector<ConnectionPair> connection_pairs;
    int number_of_connection_pairs = 0;

public:
    //constructor takes in the name of the plugboard configuration file
    Plugboard(string const& plugboard_filename);
    //addConnectionPair adds a pair of alphabets (represented by integers 0-25) to the connectionr_pairs vector, representing a connected pair in the plugboard
    void addConnectionPair(int connection1, int connection2);
    //map returns the alphabet connected to the input alphabet (represented by integers 0-25), and if not found returns the input alphabet
    int map(int inputAlphabet) const;
};

#endif