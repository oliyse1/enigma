# Enigma machine simulator

Mimics an Enigma cipher machine in C++ using object oriented programming concepts.

The below summarizes the mechanics of an Enigma machine (Wheel refers to Rotor in diagram). Diagram and descriptions below taken from http://www.cs.cornell.edu/courses/cs3110/2019sp/a1/

![image](https://user-images.githubusercontent.com/98164941/215463987-62a2880b-1829-4567-85ba-7889922f8623.png)

* Each rotor implements its own, distinct substitution cipher by wires that connect the 26 contacts on its left side with the 26 contacts on its right side. The combination of many rotors together on the spindle creates an even more sophisticated substitution cipher. The original Enigma machines used at the beginning of World War II had three rotors, known by the Roman-numeral designations I, II, and III, which could be placed on the spindle in any order. Later, other rotors with different wirings were manufactured, as were machines that could accept up to five rotors on the spindle.

* The reflector also implements a substitution cipher, though a less sophisticated one. It has 26 contacts only on its right side, but none on its left. Current that it receives from the right side is wired to be reflected back out that side, but in a different position. The reflector was always inserted at the leftmost side of the spindle. A keypress caused current to flow right-to-left through the rotors, through the reflector, then back through the rotors, left-to-right. The reflector’s substitution pattern caused the entire circuit to be symmetric, meaning that if ‘E’ mapped to ‘Q’ in a particular machine state, then ‘Q’ would likewise be mapped to ‘E’ in that same state. The minor advantage of this design was that the machine did not need separate modes of operation for decryption and encryption. But it turned out to be a major cryptographic weakness, enabling the code to be cracked.

* The plugboard implements yet another substitution cipher, which simply swaps pairs of letters. Though the wiring of the rotors and reflector was pre-determined by how they were manufactured, the wiring of the plugboard could easily be changed by the operator by plugging cables into ports. The plugboard could have up to 13 cables inserted in it. A cable inserted between two letters caused those letters to be swapped. Even though it seems simpler than a rotor, the plugboard was a major source of cryptographic strength for the Enigma cipher.
