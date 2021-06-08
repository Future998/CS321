#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI2Send7");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		int n;
		pt >> n;
		int c = 0;
		double z;
		for (int i = 1; i < size; ++i) {
			if ((i == size - 1)) {
				int a;
				a = n - c;
				std::vector<double> l(a);
				for (int i = 0; i < a; ++i) {
					pt >> l[i];
				}
				MPI_Send(&l[0], a, MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD);
			}
			else {
				pt >> z;
				MPI_Send(&z, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			}
			++c;
		}
	}
	else {
		MPI_Status status;
		double h;
		int b;
		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &b);
		if (rank == size - 1) {
			std::vector<double> lst(b);
			MPI_Recv(&lst[0], b, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
			for (int i = 0; i < b / 2; ++i) {
				pt << lst[i];
			}
		}
		else {
			MPI_Recv(&h, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
			pt << h;
		}
	}
}
