# Proyecto Computación Paralela 2019
Aplicación C++ que permite la planificación de salas y días para profesores de la UTEM.

●Se definen que el día está separado en 7 bloques de Lunes a Viernes y en 4 bloques los
días Sábados..
●La planilla de Docentes, dispone de la disponibilidad de cada profesor, por cada día de
semana.
● La planilla de Salas, contiene la información de las salas disponibles.
● La planilla de Cursos, tiene la información de los profesores que dictan las asignaturas,
junto a los bloques que a la semana se requieren cubrir.

### Instalación librería:
* $ git clone https://github.com/tfussell/xlnt.git
* $ cd xlnt
* $ cmake .
* $ make -j 2
* $ sudo make install
* $ sudo ldconfig
* (Se reemplaza la carpeta xlnt que se subió vacía)

### Compilación y ejecución:

* g++ excel.cpp -o tarea -std=c++14 -xlnt/include -lxlnt

* ./tarea -c Cursos.xlsx -d Docencia.xlsx -s Salas.xlsx

