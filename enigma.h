#ifndef ENIGMA_H
#define ENIGMA_H
#include <string>
#include <vector>
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include "connectionpair.h"

using namespace std;

//Enigma class creates an enigma machine object
class Enigma {
private:
    string plugboard_filename;
    string reflector_filename;
    std::vector<string> rotor_filenames;
    string rotor_pos_filename;
    int number_of_rotors = 0;
    Plugboard* plugboard = nullptr;
    Reflector* reflector = nullptr;
    Rotor* current_rotor = nullptr;

   
public:
    //constructor takes in command line arguments and call createComponents function
    Enigma(int argc, char** argv);
    //destructor deletes the plugboard, reflector and rotors if any as they are created using dynamic memory
    ~Enigma();
    //createComponents function will create the plugboard, relfector and configure them using the configuration files and call createRotors function
    void createComponents();
    //createRotors function will create the rotors (if there are any) and configure them using the configuration files
    Rotor* createRotors();
    //map function maps an input alphabet through the whole enigma machine and returns the output from the enigma machine
    int map(int input_alphabet);

};


#endif