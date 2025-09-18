#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    //==== TODO：初始化MPI环境 ====
    MPI_Init(&argc, &argv);

    //==== TODO：获取总进程数与当前进程排名 ====
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int* data = NULL;  //实际数据
    int data_size;     //数据大小

    if (world_rank == 0) {
        // 主进程初始化数据
        data_size = 5;
        data = (int*)malloc(data_size * sizeof(int));
        for (int i = 0; i < data_size; i++) data[i] = i + 1;

        printf("进程 0 广播数据: ");
        for (int i = 0; i < data_size; i++) printf("%d ", data[i]);
        printf("\n");
    }

    //==== TODO：广播数据大小 ====
    MPI_Bcast(&data_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // 分配缓冲区
    if (world_rank != 0) {
        data = (int*)malloc(data_size * sizeof(int));
    }

    //==== TODO：广播实际数据 ====
    MPI_Bcast(data, data_size, MPI_INT, 0, MPI_COMM_WORLD);

    //==== TODO：所有进程打印自己的rank和接收到的数据 ====
    printf("进程 %d 接收数据: ", world_rank);
    for (int i = 0; i < data_size; i++) printf("%d ", data[i]);
    printf("\n");

    free(data);

    //==== TODO：清理MPI环境 ====
    MPI_Finalize();

    return 0;
}