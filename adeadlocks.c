/* depends on buffering */
#include <stdio.h>
#include <mpi.h>
void main (int argc, char **argv) {
   int myrank;
   MPI_Status status;
   double a[100], b[100];
   MPI_Init(&argc, &argv);  /* Initialize MPI */
   MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* Get rank */
   if( myrank == 0 ) {
     /* Send a message, then receive one */
     MPI_Send( a, 100, MPI_DOUBLE, 1, 17, MPI_COMM_WORLD );
     MPI_Recv( b, 100, MPI_DOUBLE, 1, 19, MPI_COMM_WORLD, &status );
   }
   else if( myrank == 1 ) {
     /* Send a message, then receive one */
     MPI_Send( a, 100, MPI_DOUBLE, 0, 19, MPI_COMM_WORLD );
     MPI_Recv( b, 100, MPI_DOUBLE, 0, 17, MPI_COMM_WORLD, &status );   
   }
   MPI_Finalize();          /* Terminate MPI */
   }
