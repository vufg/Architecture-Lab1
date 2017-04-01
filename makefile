objects = main.o instructions.o io.o one_cycle_simulator.o

single_cycle : $(objects)
	g++ -std=c++11 $(objects) -o single_cycle -O2

instructions.o: instructions.h io.h
io.o: io.h
one_cycle_simulator.o: one_cycle_simulator.h io.h instructions.h

.PHONY : clean
clean:
	-rm single_cycle $(objects)
