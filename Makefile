CXX = mpic++
CXXFLAGS = -g3 -Wall
MKDIR = mkdir -p

LIBS=-lmpi -lxlsxio_read -lxlsxwriter

directorios: 
	$(MKDIR) build

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

DisponibilidadHoraria.o: directorios DisponibilidadHoraria.cpp DisponibilidadHoraria.h
	$(CXX) $(CXXFLAGS) -c DisponibilidadHoraria.cpp -o build/DisponibilidadHoraria.o

DocenteCurso.o: directorios DocenteCurso.cpp DocenteCurso.h
	$(CXX) $(CXXFLAGS) -c DocenteCurso.cpp -o build/DocenteCurso.o

HorarioSala.o: directorios HorarioSala.cpp HorarioSala.h
	$(CXX) $(CXXFLAGS) -c HorarioSala.cpp -o build/HorarioSala.o

funciones.o: directorios funciones.cpp funciones.h
	$(CXX) $(CXXFLAGS) -c funciones.cpp -o build/funciones.o


#utilidades.o: directorios utilidades.c utilidades.h
#	$(CXX) $(CXXFLAGS) -c utilidades.c -o build/utilidades.o

all: clean main.o DisponibilidadHoraria.o DocenteCurso.o funciones.o HorarioSala.o


	$(CXX) $(CXXFLAGS) -o programa build/main.o build/funciones.o build/DisponibilidadHoraria.o build/DocenteCurso.o build/HorarioSala.o $(LIBS)
	rm -fr build

clean:
	rm -fr *.o a.out programa dist build

.DEFAULT_GOAL := all