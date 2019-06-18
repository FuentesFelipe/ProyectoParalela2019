CXX = mpic++
CXXFLAGS = -g3 -Wall
MKDIR = mkdir -p

LIBS=-lmpi -lxlsxio_read -lxlsxwriter

directorios: 
	$(MKDIR) build

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

disponibilidad_horaria.o: directorios disponibilidad_horaria.cpp disponibilidad_horaria.h
	$(CXX) $(CXXFLAGS) -c disponibilidad_horaria.cpp -o build/disponibilidad_horaria.o

docente_curso.o: directorios docente_curso.cpp docente_curso.h
	$(CXX) $(CXXFLAGS) -c docente_curso.cpp -o build/docente_curso.o

MatrizSala.o: directorios MatrizSala.cpp MatrizSala.h
	$(CXX) $(CXXFLAGS) -c MatrizSala.cpp -o build/MatrizSala.o

funciones.o: directorios funciones.cpp funciones.h
	$(CXX) $(CXXFLAGS) -c funciones.cpp -o build/funciones.o


#utilidades.o: directorios utilidades.c utilidades.h
#	$(CXX) $(CXXFLAGS) -c utilidades.c -o build/utilidades.o

all: clean main.o disponibilidad_horaria.o docente_curso.o funciones.o MatrizSala.o


	$(CXX) $(CXXFLAGS) -o programa build/main.o build/funciones.o build/disponibilidad_horaria.o build/docente_curso.o build/MatrizSala.o $(LIBS)
	rm -fr build

clean:
	rm -fr *.o a.out programa dist build

.DEFAULT_GOAL := all