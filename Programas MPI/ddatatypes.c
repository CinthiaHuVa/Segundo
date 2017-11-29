struct SparseElt {     /* representation of a sparse matrix element */
      int    location[2]; /* where the element belongs in the overall matrix */
      double value;       /* the value of the element */
   };

   /* a representative variable of this type */
   struct SparseElt anElement;

   /* length, displacement, and type arrays used to describe an MPI derived type */
   /* their size reflects the number of components in SparseElt */
   int          lena[2]; 
   MPI_Aint     loca[2]; 
   MPI_Datatype typa[2];

   MPI_Aint     baseaddress;

   /* a variable to hold the MPI type indicator for SparseElt */
   MPI_Datatype MPI_SparseElt;

   /* set up the MPI description of SparseElt */

   MPI_Address(&anElement, &baseaddress);
   lena[0] = 2;    /* anElement.location has length of 2 ints*/
   MPI_Address(&anElement.location,&loca[0]); 
   loca[0] -= baseaddress;  /* byte address relative to start of structure */
   typa[0] = MPI_INT;
   lena[1] = 1;     /* anElement.value has length of 1 double*/
   MPI_Address(&anElement.value   ,&loca[1]); 
   loca[1] -= baseaddress; 
   typa[1] = MPI_DOUBLE;
   MPI_Type_struct(2, lena, loca, typa, &MPI_SparseElt);
   MPI_Type_commit(&MPI_SparseElt);
