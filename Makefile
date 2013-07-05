CC=g++
CFLAGS=-I.
LIBS=-lstdc++
DEPS = Points3d.h
OBJ = sortpoints.o Point3d.o 

%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sortpoints: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
