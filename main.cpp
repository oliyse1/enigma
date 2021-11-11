#include <iostream>
#include "enigma.h"
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

    //define filename variable;
    string plugboard_filename;
    string reflector_filename;
    string rotor_filenames[10];
    string rotor_pos_filename;
    string temp_string;
    int number_of_rotors = 0;

    for (int count = 0; count < argc; count++) {

        temp_string = argv[count];
        if (temp_string.find(".pb") != string::npos) {
            plugboard_filename = temp_string;
        }
        else if (temp_string.find(".rf") != string::npos) {
            reflector_filename = temp_string;
        }
        else if (temp_string.find(".rot") != string::npos) {
            rotor_filenames[number_of_rotors] = temp_string;
            number_of_rotors++;
        }
    }

    //read plugboard configuration and configure plugboard
    Plugboard plugboard(plugboard_filename);
    Reflector reflector(reflector_filename);
    RotorListNode* current_rotor_node = createRotors(rotor_filenames, number_of_rotors);


    //output command line arguments

    cout << argc << endl;

    for (int i=0; i < argc; i++){
        cout << argv[i] << endl;
    }

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
    // cout << "number of pairs= " << current_rotor_node -> rotor.number_of_connection_pairs << endl;
    
    // for (int i = 0; i < current_rotor_node -> rotor.number_of_connection_pairs; i++) {
    //     cout << current_rotor_node -> rotor.connection_pairs[i].connection_point_1 << " ";
    //     cout << current_rotor_node -> rotor.connection_pairs[i].connection_point_2 << endl;
    // }




    
int output1 = plugboard.getConnectingAlphabet(11);
int output2 = current_rotor_node -> rotor.getConnectingAlphabetFromRight(output1);
current_rotor_node = current_rotor_node -> left;
int output3 = current_rotor_node -> rotor.getConnectingAlphabetFromRight(output2);
current_rotor_node = current_rotor_node -> left;
int output4 = current_rotor_node -> rotor.getConnectingAlphabetFromRight(output3);
int output5 = reflector.getConnectingAlphabet(output4);
int output6 = current_rotor_node -> rotor.getConnectingAlphabetFromLeft(output5);
current_rotor_node = current_rotor_node -> right;
int output7 = current_rotor_node -> rotor.getConnectingAlphabetFromLeft(output6);
current_rotor_node = current_rotor_node -> right;
int output8 = current_rotor_node -> rotor.getConnectingAlphabetFromLeft(output7);
int output9 = plugboard.getConnectingAlphabet(output8);


cout << output1 <<endl;
cout << output2 <<endl;
cout << output3 <<endl;
cout << output4 <<endl;
cout << output5 <<endl;
cout << output6 <<endl;
cout << output7 <<endl;
cout << output8 <<endl;
cout << output9 <<endl;


return 0;

}