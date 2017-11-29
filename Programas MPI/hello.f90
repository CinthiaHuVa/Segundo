
      program main 
              use mpi
              integer :: ierr
              call MPI_INIT(ierr)
              write(*,*) 'hello word'
              call MPI_FINALIZE(ierr)
              end program main 

