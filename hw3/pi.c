#include <stdio.h>
#include <mpi.h>

double f(double y)
{
   return (4.0 / (1.0 + y * y));
}

int main(int argc, char *argv[])
{
   double w, x, sum, locpi, pi, start_time, end_time;
   int i, rank, size;
   unsigned int limit = 4000000000;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Barrier(MPI_COMM_WORLD);

   start_time = MPI_Wtime();
   w = 1.0 / (double)limit;
   sum = 0.0;
   for (i = rank + 1; i <= limit; i += size)
   {
      x = w * (i - 0.5);
      sum = sum + f(x);
   }
   locpi = w * sum;

   MPI_Reduce(&locpi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
   MPI_Barrier(MPI_COMM_WORLD);
   end_time = MPI_Wtime();

   if (rank == 0)
   {
      printf("Number of processes=%d, pi = %f9, Time=%lf \n", size, pi, end_time - start_time);
   }

   MPI_Finalize();
}