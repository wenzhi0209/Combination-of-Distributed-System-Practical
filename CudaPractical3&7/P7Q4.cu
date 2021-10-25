#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <math.h>
#define THREADS_PER_BLOCK 128

void matrixMultiplyCPU(float *a, float *b, float *c, int width) {
     float result;

     for (int row = 0; row < width; row++) {
          for (int col = 0; col < width; col++) {
               result = 0;
               for (int k = 0; k < width; k++) {
                    result += a[row * width + k] * b[k * width + col];
               }
               c[row * width + col] = result;
          }
     }
}

__global__ void matrixMultiplySimple(float *a, float *b, float *c, int width) {
     
    int col = threadIdx.x + blockIdx.x + blockDim.x;
    int row = threadIdx.y + blockIdx.y + blockDim.y;

     float result = 0;

     if (col < width && row < width) {
          for (int k = 0; k < width; k++) {
               result += a[row * width + k] * b[k * width + col];
          }
          c[row * width + col] = result;
     }
}

int main() {
     int width = 200; // Define width of square matrix
                      // Initialise grid and block variables
     int sqrtThreads = sqrt(THREADS_PER_BLOCK);
     int nBlocks = width / sqrtThreads;
     if (width % sqrtThreads != 0) { // Add an extra block if necessary
          nBlocks++;
     }
     dim3 grid(nBlocks, nBlocks, 1);
     dim3 block(sqrtThreads, sqrtThreads, 1); // Max number of threads per block

                                              // Initialise host pointers (dynamically allocated memory) and device pointers
     float *a_h;
     float *b_h;
     float *c_h; // GPU results
     float *d_h; // CPU results
     float *a_d;
     float *b_d;
     float *c_d;

     int size; // Number of bytes required by arrays

               // Create timer
     cudaEvent_t start;
     cudaEvent_t stop;
     float elapsed1, elapsed2, elapsed3;

     // Print out information about blocks and threads
     printf("Number of threads: %i (%ix%i)\n", block.x*block.y, block.x, block.y);
     printf("Number of blocks: %i (%ix%i)\n", grid.x*grid.y, grid.x, grid.y);

     // Dynamically allocate host memory
     size = width * width * sizeof(float);

     a_h = (float*)malloc(size);
     b_h = (float*)malloc(size);
     c_h = (float*)malloc(size);
     d_h = (float*)malloc(size);

     // Load host arrays with data
     for (int i = 0; i < width; i++) {
          for (int j = 0; j < width; j++) {
               a_h[i * width + j] = i;
               b_h[i * width + j] = i;
          }
     }

     //@@ Allocate device memory
     

     //@@ Copy host memory to device memory
     

     // Start timer for GPU
     cudaEventCreate(&start);
     cudaEventCreate(&stop);
     cudaEventRecord(start, 0);

     //@@ Launch kernel
     

     // Stop timer
     cudaEventRecord(stop, 0);
     cudaEventSynchronize(stop);
     cudaEventElapsedTime(&elapsed1, start, stop);

     // Print execution time
     printf("Time to calculate results on GPU: %f ms\n", elapsed1);

     // Copy results to host
    

     // Start timer for CPU
     cudaEventRecord(start, 0);

     // Launch CPU code
     matrixMultiplyCPU(a_h, b_h, d_h, width);

     // Stop timer
     cudaEventRecord(stop, 0);
     cudaEventSynchronize(stop);
     cudaEventElapsedTime(&elapsed2, start, stop);

     // Print execution time
     printf("Time to calculate results on CPU: %f ms\n", elapsed2);

     // Compare results
     for (int i = 0; i < width*width; i++) {
          if (c_h[i] != d_h[i]) {
               printf("Error: CPU and GPU results do not match\n");
               break;
          }
     }


     //@@ Free memory
    

     cudaEventDestroy(start);
     cudaEventDestroy(stop);

     return 0;
}
