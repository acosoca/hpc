#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    // 初始化MPI环境
    MPI_Init(&argc, &argv);

    int world_size;  // 总进程数
    int world_rank;  // 当前进程的排名（ID）
    char processor_name[MPI_MAX_PROCESSOR_NAME]; // 处理器名称
    int name_len;    // 名称长度

    // 获取总进程数
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // 获取当前进程的排名
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // 获取处理器名称
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Hello world from processor %s, rank %d out of %d processors\n",
        processor_name, world_rank, world_size);

    // 清理MPI环境
    MPI_Finalize();
}