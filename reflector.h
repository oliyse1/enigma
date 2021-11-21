#ifndef REFLECTOR_H
#define REFLECTOR_H
#include <string>
#include <vector>
#include "connectionpair.h"

using namespace std;

//The Reflector class represents the reflector in an enigma machine. 
//The reflector's function is to map an alphabet to another connected alphabet (represented by integers 0-25)
//All 26 alphabets are connected to one other alphabet apart from itself, so there are 13 pairs of alphabets exactly
class Reflector {
private:
    std::vector<ConnectionPair> connection_pairs;
    int number_of_connection_pairs = 0;

public:

    //constructor takes in the name of the reflector configuration file
    Reflector(string const& reflector_filename);
    //addConnectionPair adds a pair of alphabets (represented by integers 0-25) to the connectionr_pairs vector, representing a connected pair in the reflector
    void addConnectionPair(int connection1, int connection2);
    //map returns the alphabet connected to the input alphabet (represented by integers 0-25)
    int map(int inputAlphabet) const;
};

#endif