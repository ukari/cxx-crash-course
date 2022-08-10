#include <cstdio>

bool read_from(char* str, size_t size, size_t index, char* c) {
  if (index < size - 1) {
    *c = str[index];
    return true;
  } else {
    return false;
  }
}

bool write_to(char* str, size_t size, size_t index, char writec) {
  if (index < size - 1) {
    str[index] = writec;
    return true;
  } else {
    return false;
  }
}

int main() {
  char lower[] = "abc?e";
  char upper[] = "ABC?E";
  char* upper_ptr = upper;  // Equivalent: &upper[0]
  lower[3] = 'd';  // lower now contains a b c d e \0
  upper_ptr[3] = 'D'; // upper now contains A B C D E \0
  char letter_d = lower[3];  // letter_d equals 'd'
  char letter_D = upper_ptr[3]; // letter_D equals 'D'
  printf("lower: %s\nupper: %s\n", lower, upper);
  char readc;
  if (read_from(lower, sizeof(lower) / sizeof(char), 5, &readc)) {
    printf("read lower char: %c\n", readc);
  } else {
    printf("out of range\n");
  }

  if (write_to(upper, sizeof(upper) / sizeof(char), 4, 'g')) {
    printf("upper: %s\n", upper);
  } else {
    printf("out of range\n");
  }
  
  //lower[7] = 'g';  // Super bad. You must never do this.
}

