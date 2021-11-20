#ifndef ROTOR_H
#define ROTOR_H
#include <string>
#include <vector>
#include "connectionpair.h"
using namespace std;


class Rotor { //reflector can use the same class

public:
    Rotor* left = nullptr;
    Rotor* right = nullptr;
    Rotor(string& rotor_filename, int rotor_pos);
    std::vector<int> notches;
    int number_of_notches = 0;
    int rotor_pos = 0;
    std::vector<ConnectionPair> connection_pairs;
    int number_of_connection_pairs = 0;
    void increaseOffsetByOne();
    int getConnectingAlphabetFromRight(int inputAlphabet);
    int getConnectingAlphabetFromLeft(int inputAlphabet);
    void addConnectionPair(int connection1, int connection2);
};

#endif