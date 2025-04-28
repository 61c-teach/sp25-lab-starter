#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <stdbool.h>

#include "vector.h"

bool test_and_print(char *label, bool (*run_test)()) {
  printf("\nTesting %s...\n", label);
  bool result = run_test();
  if (result) {
    printf("All %s tests passed!\n", label);
  } else {
    printf("Not all %s tests passed.\n", label);
  }
  return result;
}

bool test_vec_load() {
  int32_t *arr = {1, 2, 3, 4, 5, 6, 7, 8};
  vector v = vec_load(arr);

  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);
  return !memcmp(test, arr, 8 * sizeof(int32_t));
}

bool test_vec_store() {
  int32_t *arr = {1, 2, 3, 4, 5, 6, 7, 8};
  vector v = _mm256_loadu_si256((vector*)arr);

  int32_t test[8];
  vec_store((vector*)test, v);
  return !memcmp(test, arr, 8 * sizeof(int32_t));
}

bool test_vec_set_num() {
  vector v = vec_set_num(5);
  int32_t *arr = {5, 5, 5, 5, 5, 5, 5, 5};

  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);
  return !memcmp(test, arr, 8 * sizeof(int32_t));
}
bool test_vec_cmpgt() {
  int32_t *arr1 = {5, 5, 5, 5, 5, 5, 5, 5};
  vector v1 = _mm256_loadu_si256((vector*)arr1);
  int32_t *arr2 = {1, 2, 3, 4, 5, 6, 7, 8};
  vector v2 = _mm256_loadu_si256((vector*)arr2);

  vector v = vec_cmpgt(v1, v2);
  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);

  int32_t *ans = {0, 0, 0, 0, 0, 4294967295, 4294967295, 4294967295};
  return !memcmp(test, ans, 8 * sizeof(int32_t));
}

bool test_vec_and() {
  int32_t *arr1 = {5, 5, 5, 5, 5, 5, 5, 5};
  vector v1 = _mm256_loadu_si256((vector*)arr1);
  int32_t *arr2 = {0, 0, 0, 0, 0, 0, 2, 5};
  vector v2 = _mm256_loadu_si256((vector*)arr2);

  vector v = vec_and(v1, v2);
  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);

  int32_t *ans = {0, 0, 0, 0, 0, 0, 0, 5};
  return !memcmp(test, ans, 8 * sizeof(int32_t));
}

bool test_vec_xor() {
  int32_t *arr1 = {5, 5, 5, 5, 5, 5, 5, 5};
  vector v1 = _mm256_loadu_si256((vector*)arr1);
  int32_t *arr2 = {0, 0, 0, 0, 0, 0, 2, 5};
  vector v2 = _mm256_loadu_si256((vector*)arr2);

  vector v = vec_xor(v1, v2);
  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);

  int32_t *ans = {5, 5, 5, 5, 5, 5, 7, 0};
  return !memcmp(test, ans, 8 * sizeof(int32_t));
}


bool test_vec_or() {
  int32_t *arr1 = {5, 5, 5, 5, 5, 5, 5, 5};
  vector v1 = _mm256_loadu_si256((vector*)arr1);
  int32_t *arr2 = {0, 0, 0, 0, 0, 0, 2, 5};
  vector v2 = _mm256_loadu_si256((vector*)arr2);

  vector v = vec_or(v1, v2);
  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);

  int32_t *ans = {5, 5, 5, 5, 5, 5, 7, 5};
  return !memcmp(test, ans, 8 * sizeof(int32_t));
}

bool test_vec_not() {
  int32_t *arr = {0, 0, 0, 0, 0, 0, 1, 4294967295};
  vector v = _mm256_loadu_si256((vector*)arr);
  v = vec_not(v);

  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);
  int32_t *ans = {4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967294, 0};
  return !memcmp(test, ans, 8 * sizeof(int32_t));
}

bool test_vec_add() {
  int32_t *arr1 = {5, 5, 5, 5, 5, 5, 5, 5};
  vector v1 = _mm256_loadu_si256((vector*)arr1);
  int32_t *arr2 = {1, 2, 3, 4, 5, 6, 7, 8};
  vector v2 = _mm256_loadu_si256((vector*)arr2);

  vector v = vec_add(v1, v2);
  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);

  int32_t *ans = {6, 7, 8, 9, 10, 11, 12, 13};
  return !memcmp(test, ans, 8 * sizeof(int32_t));
}

bool test_vec_mul() {
  int32_t *arr1 = {5, 5, 5, 5, 5, 5, 5, 5};
  vector v1 = _mm256_loadu_si256((vector*)arr1);
  int32_t *arr2 = {0, 0, 0, 0, 0, 0, 2, 5};
  vector v2 = _mm256_loadu_si256((vector*)arr2);

  vector v = vec_mul(v1, v2);
  int32_t test[8];
  _mm256_storeu_si256((vector*)test, v);

  int32_t *ans = {0, 0, 0, 0, 0, 0, 10, 25};
  return !memcmp(test, ans, 8 * sizeof(int32_t));
}

int main(int argc, char **argv) {
    if (!test_and_print("vec_load", test_vec_load)) {
      return 0;
    }
    if (!test_and_print("vec_store", test_vec_store)) {
      return 0;
    }
    if (!test_and_print("vec_set_num", test_vec_set_num)) {
      return 0;
    }
    if (!test_and_print("vec_cmpgt", test_vec_cmpgt)) {
      return 0;
    }
    if (!test_and_print("vec_and", test_vec_and)) {
      return 0;
    }
    if (!test_and_print("vec_xor", test_vec_xor)) {
      return 0;
    }
    if (!test_and_print("vec_or", test_vec_or)) {
      return 0;
    }
    if (!test_and_print("vec_not", test_vec_not)) {
      return 0;
    }
    if (!test_and_print("vec_add", test_vec_add)) {
      return 0;
    }
    if (!test_and_print("vec_mul", test_vec_mul)) {
      return 0;
    }
}