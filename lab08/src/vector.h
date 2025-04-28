#ifndef VECTOR_H
#define VECTOR_H

#include <x86intrin.h>
#include <stdint.h>
#include <stdio.h>

/*
Wrapper function for Intel Vector Intrinsics (using 256-bit vectors).

If you're interested in leraning more about vector intrinsics/the different types of instructions that you can use,
please look at the Intel Intrinsics Guide: https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html

Author: Anto Kam
*/

typedef __m256i vector;

// Loads 8 integers at memory address A into a vector
static inline vector vec_load(vector *A) {
  return _mm256_loadu_si256((vector*)A);
}


// Stores the vector at SRC to DST. Each vector element gets stored in a 
// different index of the array passed into DST.
static inline void vec_store(vector *dst, vector src) {
  _mm256_storeu_si256((vector*)dst, src);
}


// Creates a vector where every element is equal to num
static inline vector vec_set_num(int32_t num) {
  return _mm256_set1_epi32(num);
}


// Computes whether each element in A is greater than the corresponding element in B
// and returns a new vector with the results 
// (0xFFFFFFFF if true, 0 otherwise, for each element in the vector)
static inline vector vec_cmpgt(vector A, vector B) {
  return _mm256_cmpgt_epi32(A, B);
}


// Computes the bitwise and between each pair of corresponding vector elements in A and B, 
// and returns a new vector with the result
static inline vector vec_and(vector A, vector B) {
  return _mm256_and_si256(A, B);
}


// Computes the bitwise xor between each pair of corresponding vector elements in A and B, 
// and returns a new vector with the result
static inline vector vec_xor(vector A, vector B) {
  return _mm256_xor_si256(A, B);
}


// Computes the bitwise or between each pair of corresponding vector elements in A and B, 
// and returns a new vector with the result
static inline vector vec_or(vector A, vector B) {
  return _mm256_or_si256(A, B);
}


// Computes and returns a vector containing the bits of V flipped
static inline vector vec_not(vector v) {
  return vec_xor(v, vec_set_num(-1));
}


// Adds A and B together elementwise, and returns a new vector with the result
static inline vector vec_add(vector A, vector B) {
  return _mm256_add_epi32(A, B);
}


// Multiplies A and B together elementwise, and returns a new vector with the result
// Takes the lower bits if multiplication overflows
static inline vector vec_mul(vector A, vector B) {
  return _mm256_mullo_epi32(A, B);
}


// Provided for debugging: prints out the elements of a 256-bit vector
static inline void vec_print(vector v) {
  int32_t temp[8];
  _mm256_storeu_si256((vector*)temp, v);
  for (int i = 0; i < 8; ++i) {
    printf("%d, ", temp[i]);
  }
  printf("\n");
}

#endif
