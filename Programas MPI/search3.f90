PROGRAM parallel_search   
  include 'mpif.h'
  parameter (N=300)
  integer i, target
  integer b(N),a(N/3)
  integer rank,err
  integer status(MPI_STATUS_SIZE)
  integer end_cnt

  integer gi
  real ave
  common /pair/gi,ave  ! Put in common block to insure consecutive memory locations
  integer blocklengths(2)
  data blocklengths/1,1/   ! Initialize blocklengths array
  integer types(2), MPI_Pair
  data types/MPI_INTEGER,MPI_REAL/ ! Initialize types array
  integer displacements(2)
  
  CALL MPI_INIT(err)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, rank, err)

  CALL MPI_ADDRESS(gi,displacements(1),err)  ! Initialize displacements array with
  CALL MPI_ADDRESS(ave,displacements(2),err) ! memory addresses
    CALL MPI_TYPE_STRUCT(2,blocklengths,displacements,types, MPI_Pair,err) ! This routine creates the new data type MPI_Pair
  CALL MPI_TYPE_COMMIT(MPI_Pair,err) ! This routine allows it to be used in communication

  if (rank == 0) then
    open(unit=10,file="b.data")
    read(10,*) target
    do i=1,3
      CALL MPI_SEND(target,1,MPI_INTEGER,i,9,MPI_COMM_WORLD,err)
    end do

    do i=1,300
      read(10,*) b(i)
    end do

    CALL MPI_SEND(b(1),100,MPI_INTEGER,1,11,MPI_COMM_WORLD,err)
    CALL MPI_SEND(b(101),100,MPI_INTEGER,2,11,MPI_COMM_WORLD,err)
    CALL MPI_SEND(b(201),100,MPI_INTEGER,3,11,MPI_COMM_WORLD,err)

    end_cnt=0
    open(unit=11,file="dfound.data")
    do while (end_cnt .ne. 3 )

      CALL MPI_RECV(MPI_BOTTOM,1,MPI_Pair,MPI_ANY_SOURCE,MPI_ANY_TAG, &
                     MPI_COMM_WORLD,status,err)
                     
      if (status(MPI_TAG) == 52 ) then
        end_cnt=end_cnt+1
      else
        write(11,*) "P",status(MPI_SOURCE),gi,ave
      end if
    end do 

  else 
    CALL MPI_RECV(target,1,MPI_INTEGER,0,9,MPI_COMM_WORLD,status,err) 
    CALL MPI_RECV(a,100,MPI_INTEGER,0,11,MPI_COMM_WORLD,status,err) 

    do i=1,100
      if (a(i) == target) then
        gi=(rank-1)*100+i
        ave=(gi+target)/2.0
        CALL MPI_SEND(MPI_BOTTOM,1,MPI_Pair,0,19,MPI_COMM_WORLD,err)
      end if
    end do  

    gi=target ! Both are fake values
    ave=3.45  ! The point of this send is the "end" tag (See Chapter 4)
    CALL MPI_SEND(MPI_BOTTOM,1,MPI_Pair,0,52,MPI_COMM_WORLD,err)
  end if 

  CALL MPI_FINALIZE(err)

END PROGRAM parallel_search
