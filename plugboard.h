#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include <string>
#include <vector>
#include "connectionpair.h"
using namespace std;

class Plugboard {

public:
    std::vector<ConnectionPair> connection_pairs;
    int number_of_connection_pairs = 0;
    Plugboard(string plugboard_filename);
    int getConnectingAlphabet(int inputAlphabet);
    void addConnectionPair(int connection1, int connection2);

};

#endif