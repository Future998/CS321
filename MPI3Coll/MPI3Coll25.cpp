#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI3Coll25");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double* d = (double*)malloc((size * 2) * sizeof(double));
    double* res = (double*)malloc(2 * sizeof(double));
    int* count = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size * 2; ++i)
        pt >> *(d + i);
    for (int i = 0; i < size; ++i)
        *(count + i) = 2;
    MPI_Reduce_scatter(d, res, count, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    for (int i = 0; i < 2; ++i)
        pt << *(res + i);
    free(d);
    free(res);
}
