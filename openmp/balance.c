#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <omp.h>

// 模拟不同计算负载的函数
double compute_work(int i, bool balanced) {
    if (balanced) {
        // 均衡负载：所有任务计算量相同
        return sqrt(i) + log(i + 100);
    } else {
        // 不均衡负载：计算量随任务ID变化
        if (i % 10000 == 0) {
            // 每1000个任务有一个重负载任务
            double result = 0.0;
            for (int j = 0; j < 500000; j++) {
                result += sqrt(i + j) * log(i + j + 1);
            }
            return result;
        } else {
            // 普通负载任务
            return sqrt(i) + log(i + 100);
        }
    }
}

void run_experiment(bool balanced, const char* mode_name) {
    const int N = 10000000;    // 任务总数
    const int chunk = 100;    // 任务块大小
    double sum = 0.0;         // 计算结果

    printf("\n===== %s负载实验 =====\n", mode_name);

    // 静态调度
    sum = 0.0;
    double start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(static, chunk)
    for (int i = 0; i < N; i++) {
        sum += compute_work(i, balanced);
    }
    double end = omp_get_wtime();
    printf("Static  : 时间 = %.4f秒\n", end - start);

    // 动态调度
    sum = 0.0;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(dynamic, chunk)
    for (int i = 0; i < N; i++) {
        sum += compute_work(i, balanced);
    }
    end = omp_get_wtime();
    printf("Dynamic : 时间 = %.4f秒\n", end - start);

    // 引导调度
    sum = 0.0;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(guided, chunk)
    for (int i = 0; i < N; i++) {
        sum += compute_work(i, balanced);
    }
    end = omp_get_wtime();
    printf("Guided  : 时间 = %.4f秒\n", end - start);
}

int main() {
    // 设置线程数（可根据需要调整）
    omp_set_num_threads(4);
    printf("使用OpenMP线程数: %d\n", omp_get_max_threads());

    // 运行负载均衡实验
    run_experiment(true, "均衡");

    // 运行负载不均衡实验
    run_experiment(false, "不均衡");

    return 0;
}