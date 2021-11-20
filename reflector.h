#ifndef REFLECTOR_H
#define REFLECTOR_H
#include <string>
#include <vector>
#include "connectionpair.h"
using namespace std;

class Reflector {

public:
    std::vector<ConnectionPair> connection_pairs;
    int number_of_connection_pairs = 0;
    Reflector(string reflector_filename);
    int getConnectingAlphabet(int inputAlphabet);
    void addConnectionPair(int connection1, int connection2);
};

#endif