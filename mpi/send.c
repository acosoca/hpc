#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size < 2) {
        if (world_rank == 0) {
            printf("需要至少2个进程\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (world_rank == 0) {
        int send_value = 42;
        MPI_Send(&send_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("进程 0 发送了值: %d 给进程 1\n", send_value);
    } else if (world_rank == 1) {
        int recv_value;
        MPI_Recv(&recv_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("进程 1 收到了值: %d\n", recv_value);
    }

    MPI_Finalize();
    return 0;
}