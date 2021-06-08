#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI3Coll16");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int sz = (size * (size + 1)) / 2;
	std::vector<int> n(sz);
	std::vector<int> scount(size);
	std::vector<int> sdispls(size);
	std::vector<int> rcount(size, rank + 1);
	std::vector<int> rdispls(size);
	for (int i = 0; i < sz; ++i)
		pt >> n[i];
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < size; ++i) {
		scount[i] = i + 1;
		sdispls[i] = sum1;
		rcount[i] = size * (i + 1);
		rdispls[i] = sum2;
		sum1 += i + 1;
		sum2 += rank + 1;
	}
	int sz_re = size * (rank + 1);
	std::vector<int> re(sz_re);
	MPI_Alltoallv(&n[0], &scount[0], &sdispls[0], MPI_INT, &re[0], &rcount[0], &rdispls[0], MPI_INT, MPI_COMM_WORLD);
	for (auto& i : re)
		pt << i;
}
