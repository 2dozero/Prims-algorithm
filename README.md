# Minimum Spanning Tree (MST) Algorithm Performance Comparison

This project implements Prim's Algorithm for finding the Minimum Spanning Tree (MST) of a graph, using both a Heap-based and an Array-based approach. The code compares these approaches based on MST cost, execution time, and the number of operations performed.

## Results

Below are the performance results for both approaches with parameters:
- **Number of Vertices (V)**: 1000
- **Number of Edges (E)**: 3000

| Approach            | MST Cost | Time (seconds) | Operations |
|---------------------|----------|----------------|------------|
| **Heap-based**      | 2080     | 0.00210936     | 5300       |
| **Array-based**     | 2080     | 0.030659       | 1,002,150  |

## Description

This project demonstrates the trade-offs between different data structures in Prim’s Algorithm:

- **Heap-based MST**: Uses a min-heap for efficiently selecting the minimum-cost edge, leading to faster execution and fewer operations due to efficient updates.
- **Array-based MST**: Uses a simple array-based implementation, resulting in significantly more operations and longer execution time, particularly in large graphs.

### Key Observations

- Both methods yield the same MST cost (2080).
- The Heap-based approach is considerably faster and requires fewer operations, especially advantageous as the graph size grows.
