# Multithreaded Sorting

## Overview
This program demonstrates a multithreaded sorting approach using POSIX threads (pthreads). It divides an array of integers into 2 halves, sorts each half concurrently in separate threads using the Quick Sort algorithm, and then merges the two sorted halves into a final sorted array using a third thread.

## Sorting Algorithm
Each sorting thread uses the **Quick Sort algorithm** to sort its assigned half of the array.

**Quick Sort** is one of the most efficient and widely used sorting algorithms due to its divide-and-conquer approach. The algorithm starts by selecting a pivot element from the list, which is used to partition the array. The goal of this partitioning is to arrange the elements so that all numbers smaller than the pivot are on the left, while all numbers greater than the pivot are on the right, and the pivot is in its correct sorted position.

After partitioning, the list is divided into 2 subarrays around the pivot. Quick Sort then recursively sorts these subarrays, and the recursion continues until each subarray has been sorted. By the end of this process, the entire list is sorted. Quick Sort’s recursive nature and efficient partitioning made it an optimal choice for this program, and it typically performs faster than many other sorting algorithms, hence I chose to use it.


## Array Division and Parameter Passing
1. **Array Division**: The input array is divided into two equal parts. The first half (from index `0` to `SIZE/2 - 1`) is handled by the first sorting thread, and the second half (from index `SIZE/2` to `SIZE - 1`) is handled by the second sorting thread.
2. **Parameter Passing**: The `ThreadData` structure is used to store the `start` and `end` indices for each sorting thread, allowing each thread to know which part of the array to sort.

After both sorting threads are complete, a third thread merges the 2 sorted subarrays into the final sorted `result` array.

## Compilation and Execution Instructions
### Compiling
To compile the program with `gcc`, use the following command:

```bash
gcc -pthread -o sorting main.c
```
### Running the Program
After compilation, run the program using:
```bash
./sorting 7, 12, 19, 3, 18, 4, 2, 6, 15, 8
```
### Example Output
Below is a sample output for the above sample input:
```bash
Unsorted array: 7, 12, 19, 3, 18, 4, 2, 6, 15, 8
Sorted sublist 1: 3, 7, 12, 18, 19
Sorted sublist 2: 2, 4, 6, 8, 15
Final sorted array: 2, 3, 4, 6, 7, 8, 12, 15, 18, 19
```
