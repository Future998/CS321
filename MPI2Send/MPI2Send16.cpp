#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send16");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n;
    double num;
    pt >> n;
    if (n) {
        for (int i = 0; i < size; ++i) {
            if (i == rank) continue;
            pt >> num;
            MPI_Send(&num, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(&num, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        pt << num;
    }
}
