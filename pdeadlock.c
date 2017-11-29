/* probable deadlock */
#include <stdio.h>
#include <mpi.h>
void main (int argc, char **argv) {
  int myrank;
  MPI_Status status;
  #define N 100000000
  double a[N], b[N];
  MPI_Init(&argc, &argv);  /* Initialize MPI */
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* Get rank */
  if( myrank == 0 ) {
    /* Send a message, then receive one */
    MPI_Send( a, N, MPI_DOUBLE, 1, 17, MPI_COMM_WORLD );
    MPI_Recv( b, N, MPI_DOUBLE, 1, 19, MPI_COMM_WORLD, &status );
  }
  else if( myrank == 1 ) {
    /* Send a message, then receive one */
    MPI_Send( a, N, MPI_DOUBLE, 0, 19, MPI_COMM_WORLD );
    MPI_Recv( b, N, MPI_DOUBLE, 0, 17, MPI_COMM_WORLD, &status );   
  }
  MPI_Finalize();          /* Terminate MPI */
  }
