#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char* name;
} Student;

Student* create_student_1(int id) {
  Student* student_ptr = malloc(sizeof(Student));

  student_ptr->id = id;

  return student_ptr;
}

void create_student_2(Student** student_double_ptr, int id) {
  *student_double_ptr = malloc(sizeof(Student));

  (*student_double_ptr)->id = id;
}


int main() {
  Student* student1_ptr = create_student_1(5);

  printf("Student 1's ID: %d\n", student1_ptr->id);

  free(student1_ptr);

  Student* student2_ptr = malloc(sizeof(Student));

  create_student_2(&student2_ptr, 6);

  printf("Student 2's ID: %d\n", student2_ptr->id);

  free(student2_ptr);

  return 0;
}