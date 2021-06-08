#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int r = (size * (size + 3)) / 2;
	int sum = 0;
	std::vector<int> n(r);
	std::vector<int> scounts(size);
	std::vector<int> displs(size);
	if (rank == 0) {
		for (int i = 0; i < r; ++i)
			pt >> n[i];
		for (int i = 0; i < size; i++) {
			displs[i] = sum;
			sum += i + 2;
			scounts[i] = i + 2;
		}
	}
	std::vector<int> t(rank + 2);
	MPI_Scatterv(&n[0], &scounts[0], &displs[0], MPI_INT, &t[0], rank + 2, MPI_INT, 0, MPI_COMM_WORLD);
	for (auto& i : t)
		pt << i;
}
