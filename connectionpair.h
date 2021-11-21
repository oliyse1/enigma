#ifndef CONNECTIONPAIR_H
#define CONNECTIONPAIR_H

using namespace std;

//The ConnectionPair struct stores a pair of connected alphabets (represented by integers 0-25)
//Pairs (mappings of a single alphabet to another alphabet) are found in the plugboard, reflector and rotors and are all represented by the ConnectionPair struct
struct ConnectionPair {

    int connection_point_1 = 0;
    int connection_point_2 = 0;
    //Constructor takes in 2 alphabets represented by intergers 0-25, one for each connection point
    ConnectionPair(int connectionPoint1, int connectionPoint2) : connection_point_1(connectionPoint1), connection_point_2(connectionPoint2){}

};

#endif