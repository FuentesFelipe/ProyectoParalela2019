# Tarea5Paralela
Tarea 5 ayudantia computacion paralela

### Instalación librería:
* $ git clone https://github.com/tfussell/xlnt.git
* $ cd xlnt
* $ cmake .
* $ make -j 2
* $ sudo make install
* $ sudo ldconfig
* (Se reemplaza la carpeta xlnt que se subió vacía)

### Compilación y ejecución:

* g++ excel.cpp -o tarea -std=c++14 -Ixlnt/include -lxlnt
* ./tarea -c Cursos.xlsx -d Docencia.xlsx -s Salas.xlsx

