#include <mpi.h>
int main(int argc, char ** argv)
{
	int pid, np;
	int hayTrabajo=1; //Bool que indica si hay algo que hacer 
	
	//Inicializamos el MPI
	MPI_Init();
	MPI_Comm_rank(MPI_COMM_WORLD, &pid); //Proceso actual
	MPI_Comm_size(MPI_COMM_WORLD, &np);  //Total de procesos
	
	if(pid == 0) //Proceso Padre -> inicializa las coordenadas
	{
		int i;
		int coordsDisp = 1000; //Datos para procesar
		MPI_Request * estadoNodos = (MPI_Request *)malloc(sizeof(MPI_Request)*np); 
		//Creamos grafo. 
		//Enviamos grafo. MPI_Send/ MPI_Isend
		for(i = 1; i < np; i++)
		{
			//Envia por primera vez los trabajos.
			MPI_Send(&hayTrabajo, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
			MPI_Send(/*coords*/, /*N datos*/, /*tipo dato*/, i, 0, MPI_COMM_WORLD);
			coordsDisp--;
			MPI_Irecv(/*ruta*/, /*N datos*/, /*tipo dato*/, i, 0, MPI_COMM_WORLD, &estadoNodos[i], MPI_STATUS_IGNORE);
		}
		while(1) //Bucle infinito
		{
			for(i = 1; i < np; i++)
			{
				if(MPI_Request_get_status(estadoNodos[i], 0, MPI_STATUS_IGNORE)) //Comprueba que cada nodo haya completado la tarea.
				{
					if(coordsDisp < 1)
						hayTrabajo=0;
					MPI_Send(&hayTrabajo, 1, MPI_INT, i, 1, MPI_COMM_WORLD); //Envia que no hay trabajo y termina proceso
					
					//Vuelve a mandar trabajos hasta que se acaben y se cierre:
					if(hayTrabajo) 
					{
						MPI_Send(/*coords*/, /*N datos*/, /*tipo dato*/, i, 0, MPI_COMM_WORLD);
						coordsDisp--;
						MPI_Irecv(/*ruta*/, /*N datos*/, /*tipo dato*/, i, 0, MPI_COMM_WORLD, &estadoNodos[i], MPI_STATUS_IGNORE);
					}
				}
			}
		}
	}
	else //Proceso hijo -> Organiza los trabajos
	{
		//Recibimos grafo. MPI_Recv
		while(hayTrabajo)
		{
			MPI_Recv(&hayTrabajo, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(/*coords*/, /*N datos*/, /*tipo dato*/, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			ruta = algoritmoAstar(coords); //tratar datos
			MPI_Send(/*ruta*/, /*N datos*/, /*tipo dato*/, 0, 0, MPI_COMM_WORLD);
		}
	}
}
