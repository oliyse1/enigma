#ifndef ENIGMA_H
#define ENIGMA_H
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include "connectionpair.h"
#include <string>
#include <vector>
using namespace std;


class Enigma {
    string plugboard_filename;
    string reflector_filename;
    std::vector<string> rotor_filenames;
    string rotor_pos_filename;
    string temp_string;
    int number_of_rotors = 0;

    Plugboard* plugboard;
    Reflector* reflector;
    Rotor* current_rotor_node;

   
public:
    Enigma(int argc, char** argv);
    void createComponents ();
    Rotor* createRotors();
    int map(int input_alphabet);


};


#endif