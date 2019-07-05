# ProyectoParalela2019
Aplicación en C++ para planificación academica por salas y días bajo el paradigma de computación paralela

Requisitos

OpenMpi
CMake
Librería xlsxio para lectura de archivos
LIbrería libxlsxwriter para escritura de archivos

##Instalación

#### OpenMpi

    *$ sudo apt-get install libopenmpi-dev

#### Cmake

    *$ sudo apt-get install cmake.


#### XLSXIO

*Instalación de dependencias

    *$ sudo apt install libexpat1-dev
    *$ sudo apt install libzip-dev
    *$ sudo apt install libminizip-dev
    *$ sudo apt install doxygen
    *$ sudo apt install graphviz

*Se clona el repositorio de la librería y se entra en la carpeta xlsxio/
    * git clone https://github.com/brechtsanders/xlsxio
cd xlsxio/

*Se instala la librería (instalar cmake)
    *cmake -G"Unix Makefiles" 
    *make
    *sudo make install

*Si da algún error, es porque no encuentra la librería
    *sudo sh -c "echo '/usr/local/lib' >> /etc/ld.so.conf"
    *sudo ldconfig


## Compilación

    *$ make

## Ejecución

* Versión Paralela en la rama ParalelismoAlternativo

    *$ mpirun -np "numero de procesadores" ./programa -c Cursos.xlsx -s Salas.xlsx -d Docentes.xlsx

 

