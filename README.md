# MultiplicacionParalelaMatriz2x2
Usando MPI se realiza una multiplicación de matrices de 2x2 paralela.

Compilar: 

mpicc -o matrices matrices.c

Ejec (necesario 5 procesos): 

mpirun -np 5 ./matrices


