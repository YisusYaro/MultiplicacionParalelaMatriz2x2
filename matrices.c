#include <stdio.h>
#include <mpi.h>
int main(int argc, char* argv[]){
	int rank, size, len;//rank es el id del core y size el numero de cores que tengo
	MPI_Status stat;
	int n[4], res;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);//almacena el id de cada proceso
	MPI_Comm_size(MPI_COMM_WORLD, &size);//almacena cantidad de procesos
	
	if(rank==0){
		int m1[2][2], m2[2][2], m3[2][2];
		m1[0][0]=3500;
		m1[0][1]=7400;
		m1[1][0]=9800;
		m1[1][1]=4100;

		m2[0][0]=2900;
		m2[0][1]=4500;
		m2[1][0]=5100;
		m2[1][1]=2000;
		
		n[0] = m1[0][0];
		n[1] = m1[0][1];
		n[2] = m2[0][0];
		n[3] = m2[1][0];
		MPI_Send(n,4,MPI_INT,1,0,MPI_COMM_WORLD);
		n[0] = m1[0][0];
		n[1] = m1[0][1];
		n[2] = m2[0][1];
		n[3] = m2[1][1];
		MPI_Send(n,4,MPI_INT,2,0,MPI_COMM_WORLD);
		n[0] = m1[1][0];
		n[1] = m1[1][1];
		n[2] = m2[0][0];
		n[3] = m2[1][0];
		MPI_Send(n,4,MPI_INT,3,0,MPI_COMM_WORLD);
		n[0] = m1[1][0];
		n[1] = m1[1][1];
		n[2] = m2[0][1];
		n[3] = m2[1][1];
		MPI_Send(n,4,MPI_INT,4,0,MPI_COMM_WORLD);
		//Recibo datos
		MPI_Recv(&res,1,MPI_INT,1,0,MPI_COMM_WORLD, &stat);
		//printf("resultado 1: %d\t",res);
		m3[0][0] = res;
		MPI_Recv(&res,1,MPI_INT,2,0,MPI_COMM_WORLD, &stat);
		//printf("resultado 2: %d\n",res);
		m3[0][1] = res;
		MPI_Recv(&res,1,MPI_INT,3,0,MPI_COMM_WORLD, &stat);
		//printf("resultado 3: %d\t",res);
		m3[1][0] = res;
		MPI_Recv(&res,1,MPI_INT,4,0,MPI_COMM_WORLD, &stat);
		//printf("resultado 4: %d\n",res);
		m3[1][1] = res;
		for(int x=0;x<2;x++){
			for(int y=0;y<2;y++){
				printf("%d ",m3[x][y]);
			}
			printf("\n");
		}
	}else{
		//Esperar a maestro
		MPI_Recv(n,4,MPI_INT,0,0,MPI_COMM_WORLD, &stat);
		//printf("Soy el proceso 1 mi dato es: %d \n",n[2]);
		//Calcular
		int r = n[0]*n[2]+n[1]*n[3];
		res = r;
		//printf("Primer valor matriz: %d\n",r);
		//Envio resultado
		MPI_Send(&res,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}
