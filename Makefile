enigma: main.o enigma.o rotor.o reflector.o plugboard.o
	g++ main.o enigma.o rotor.o reflector.o plugboard.o -o enigma

main.o: main.cpp enigma.h connectionpair.h
	g++ -Wall -g -c main.cpp

enigma.o: enigma.cpp enigma.h connectionpair.h
	g++ -Wall -g -c enigma.cpp

rotor.o: rotor.cpp rotor.h connectionpair.h
	g++ -Wall -g -c rotor.cpp
 
reflector.o: reflector.cpp reflector.h connectionpair.h
	g++ -Wall -g -c reflector.cpp

plugboard.o: plugboard.cpp plugboard.h connectionpair.h
	g++ -Wall -g -c plugboard.cpp

.PHONY: clean
clean:
	rm -f main.o enigma.o rotor.o reflector.o plugboard.o enigma