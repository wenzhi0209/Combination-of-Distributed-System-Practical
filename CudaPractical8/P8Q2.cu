#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/sort.h>
#include <thrust/copy.h>
#include <algorithm>
#include <cstdlib>

int main2(void)
{
    //@@ generate random data serially
    thrust::host_vector<int> h_vec(200);
    std::generate(h_vec.begin(), h_vec.end(), rand);

    //@@ transfer to device and compute sum
    thrust::device_vector<int> d_vec = h_vec;

    //Parallel Vector Addition
    int x = thrust::reduce(d_vec.begin(), d_vec.end(), 0, thrust::plus<int>());

    //@@ Display the sum
    std::cout << x << std::endl;

    return 0;
}