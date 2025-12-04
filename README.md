# README – ASA Project 2025/2026

## Problem Description
The goal of this project is to determine the optimal order to remove a chain of amino acids a₁,…,aₙ in such a way that the **total released energy is maximized**.

When an amino acid aᵢ is removed, the released energy depends on:
- The potentials Pᵢ₋₁, Pᵢ, and Pᵢ₊₁  
- The biochemical classes of the amino acids (P, N, A, B)  
- The affinity Af(c₁, c₂), which is asymmetric  
- The artificial terminal endpoints (class T, potential 1)

The released energy when removing aᵢ is:

**E = Pᵢ₋₁ × Af(C(i−1),C(i)) × Pᵢ  +  Pᵢ × Af(C(i),C(i+1)) × Pᵢ₊₁**

The objective is:
- Compute the maximum total released energy  
- Determine the best removal order  
- If multiple optimal orders exist, choose the **lexicographically smallest**  

## Input Format
The program reads:
1. An integer n  
2. A line with n integer potentials  
3. A line with n biochemical classes  

## Output Format
1. The maximum released energy  
2. The optimal removal sequence  

## Approach
The solution uses **Dynamic Programming (DP)**.

- `best[i][j]` stores the maximum energy achievable in subchain [i,j]  
- `choice[i][j]` stores the index of the last amino acid removed in [i,j]  

For each subchain, every possible last removal k is tested:

**total = best[i][k−1] + best[k+1][j] + removal_energy(k)**

The maximum value is chosen.  
If values tie, the algorithm selects the **largest k**, ensuring lexicographical minimality after reconstruction.

### Reconstruction
The final order is obtained recursively using the `choice[][]` table.

## Complexity
- **Time:** O(n³)  
- **Memory:** O(n²)

## Compilation
C++ (recommended):
```
g++ -std=c++11 -O3 -Wall file.cpp -o proj
./proj < input.txt
```
