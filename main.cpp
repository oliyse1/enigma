#include <iostream>
#include "enigma.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {


    //output command line arguments

    cout << argc << endl;

    for (int i=0; i < argc; i++){
        cout << argv[i] << endl;
    }

    Enigma enigma(argc, argv);
    cout << enigma.map(6);

    // //output plugboard pairs
    // cout << "Plugboard"<<endl;
    // cout << "number of pairs= " << plugboard.number_of_connection_pairs << endl;
    
    // for (int i = 0; i < plugboard.number_of_connection_pairs; i++) {
    //     cout << plugboard.connection_pairs[i].connection_point_1 << " ";
    //     cout << plugboard.connection_pairs[i].connection_point_2 << endl;
    // }

    // //output plugboard pairs

    // //output reflector pairs
    // cout << "Reflector"<<endl;
    // cout << "number of pairs= " << reflector.number_of_connection_pairs << endl;
    
    // for (int i = 0; i < reflector.number_of_connection_pairs; i++) {
    //     cout << reflector.connection_pairs[i].connection_point_1 << " ";
    //     cout << reflector.connection_pairs[i].connection_point_2 << endl;
    // }

    // //output rotor pairs
    // cout << "Rotor"<<endl;
    // // current_rotor_node = current_rotor_node -> left;
    // // current_rotor_node = current_rotor_node -> left;
    // cout << "number of pairs= " << current_rotor_node -> rotor.number_of_connection_pairs << endl;
    
    // for (int i = 0; i < current_rotor_node -> rotor.number_of_connection_pairs; i++) {
    //     cout << current_rotor_node -> rotor.connection_pairs[i].connection_point_1 << " ";
    //     cout << current_rotor_node -> rotor.connection_pairs[i].connection_point_2 << endl;
    // }
    // cout << "number of notches= " << current_rotor_node -> rotor.number_of_notches << endl;

    // for (int i = 0; i < current_rotor_node -> rotor.number_of_notches; i++) {
    //     cout << current_rotor_node -> rotor.notches[i] << endl;
    // }




    



return 0;

}