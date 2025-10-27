#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
5 6 #define ASSERT(expr) 7 ┆ {
  8 ┆ ┆ if (!(expr)) {
    9 ┆ ┆ ┆ fprintf(stderr, "Assertion failed: %s\n", #expr);
    10 ┆ ┆ ┆ exit(1);
    11 ┆ ┆
  }
  12 ┆
}
13 14 #define TEST(expr) 15 ┆ {
  16 ┆ ┆ if (!(expr)) {
    17 ┆ ┆ ┆ fprintf(stderr, "Test failed: %s\n", #expr);
    18 ┆ ┆ ┆ exit(1);
    19 ┆ ┆
  }
  else {
    20 ┆ ┆ ┆ printf("Test passed: %s\n", #expr);
    21 ┆ ┆
  }
  22 ┆
}
23 24 typedef struct node {
  25 ┆ uint64_t data;
  26 ┆ struct node *next;
  27
} node_t;
28 29 node_t *head = NULL;
30 31 void insert_sorted(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  33 ┆ new_node->data = data;
  34 ┆ new_node->next = NULL;
  35 ┆ 36 ┆ if (head == NULL) {
    37 ┆ ┆ head = new_node;
    38 ┆
  }
  else if (data < head->data) {
    39 ┆ ┆ new_node->next = head;
    40 ┆ ┆ head = new_node;
    41 ┆
  }
  else {
    42 ┆ ┆ node_t *curr = head;
    43 ┆ ┆ node_t *prev = NULL;
    44 ┆ ┆ 45 ┆ ┆ bool inserted = false;
    46 ┆ ┆ while (curr != NULL && !inserted) {
      47 ┆ ┆ ┆ if (data < curr->data) {
        48 ┆ ┆ ┆ ┆ prev->next = new_node;
        49 ┆ ┆ ┆ ┆ new_node->next = curr;
        50 ┆ ┆ ┆ ┆ inserted = true;
        51 ┆ ┆ ┆
      }
      52 ┆ ┆ ┆ prev = curr;
      53 ┆ ┆ ┆ curr = curr->next;
      54 ┆ ┆
    }
    55 ┆ ┆ 56 ┆ ┆ if (!inserted) {
      57 ┆ ┆ ┆ prev->next = new_node;
      58 ┆ ┆
    }
    59 ┆
  }
  60
}
61 62 int index_of(uint64_t data) {
  node_t *curr = head;
  64 ┆ int index = 0;
  65 ┆ 66 ┆ while (curr != NULL) {
    67 ┆ ┆ if (curr->data == data) {
      68 ┆ ┆ ┆ return index;
      69 ┆ ┆
    }
    70 ┆ ┆ 71 ┆ ┆ curr = curr->next;
    72 ┆ ┆ index++;
    73 ┆
  }
  74 ┆ 75 ┆ return -1;
  76
}
77 78 int main() {
  79 ┆ insert_sorted(1);
  80 ┆ insert_sorted(2);
  81 ┆ insert_sorted(5);
  82 ┆ insert_sorted(3);
  83 ┆ 84 ┆ TEST(index_of(3) == 2);
  85 ┆ 86 ┆ insert_sorted(0);
  87 ┆ insert_sorted(4);
  88 ┆ 89 ┆ TEST(index_of(4) == 4);
  90 ┆ 91 ┆ return 0;
  92
}

// part 2
//
#include <stdint.h>
2 #include < stdio.h > 3 #include < stdlib.h > 4 5 #define ASSERT(expr) 6 ┆ {
  7 ┆ ┆ if (!(expr)) {
    8 ┆ ┆ ┆ fprintf(stderr, "Assertion failed: %s\n", #expr);
    9 ┆ ┆ ┆ exit(1);
    10 ┆ ┆
  }
  11 ┆
}
12 13 #define TEST(expr) 14 ┆ {
  15 ┆ ┆ if (!(expr)) {
    16 ┆ ┆ ┆ fprintf(stderr, "Test failed: %s\n", #expr);
    17 ┆ ┆ ┆ exit(1);
    18 ┆ ┆
  }
  19 ┆
}
20 21 typedef struct node {
  22 ┆ uint64_t data;
  23 ┆ struct node *next;
  24
} node_t;
25 26 typedef struct info {
  27 ┆ uint64_t sum;
  28
} info_t;
29 30 node_t *head = NULL;
31 info_t info = {0};
uint64_t compute_sum() {
  34 ┆ node_t *curr = head;
  35 ┆ uint64_t sum = 0;
  36 ┆ 37 ┆ while (curr != NULL) {
    38 ┆ ┆ sum += curr->data;
    39 ┆ ┆ curr = curr->next;
    40 ┆
  }
  41 ┆ 42 ┆ return sum;
  43
}
44 45 void insert_sorted(uint64_t data) {
  46 ┆ node_t *new_node = malloc(sizeof(node_t));
  47 ┆ new_node->data = data;
  48 ┆ new_node->next = NULL;
  49 ┆ 50 ┆ if (head == NULL) {
    51 ┆ ┆ head = new_node;
    52 ┆
  }
  else if (data < head->data) {
    53 ┆ ┆ new_node->next = head;
    54 ┆ ┆ head = new_node;
    55 ┆
  }
  else {
    56 ┆ ┆ node_t *curr = head;
    57 ┆ ┆ node_t *prev = NULL;
    58 ┆ ┆ 59 ┆ ┆ while (curr != NULL) {
      60 ┆ ┆ ┆ if (data < curr->data) {
        61 ┆ ┆ ┆ ┆ break;
        62 ┆ ┆ ┆
      }
      prev = curr;
      65 ┆ ┆ ┆ curr = curr->next;
      66 ┆ ┆
    }
    67 ┆ ┆ 68 ┆ ┆ prev->next = new_node;
    69 ┆ ┆ new_node->next = curr;
    70 ┆
  }
  71 ┆ 72 ┆ info.sum += data;
  73
}
74 75 int index_of(uint64_t data) {
  76 ┆ node_t *curr = head;
  77 ┆ int index = 0;
  78 ┆ 79 ┆ while (curr != NULL) {
    80 ┆ ┆ if (curr->data == data) {
      81 ┆ ┆ ┆ return index;
      82 ┆ ┆
    }
    83 ┆ ┆ 84 ┆ ┆ curr = curr->next;
    85 ┆ ┆ index++;
    86 ┆
  }
  87 ┆ 88 ┆ return -1;
  89
}
90 91 int main() {
  92 ┆ insert_sorted(1);
  insert_sorted(3);
  94 ┆ insert_sorted(5);
  95 ┆ insert_sorted(2);
  96 ┆ 97 ┆ ASSERT(head != NULL);
  98 ┆ ASSERT(head->data == 1);
  99 ┆ ASSERT(head->next != NULL);
  100 ┆ 101 ┆ TEST(info.sum == 1 + 3 + 5 + 2);
  102 ┆ TEST(index_of(2) == 1);
  103 ┆ 104 ┆ uint64_t computed_sum = compute_sum();
  105 ┆ ASSERT(computed_sum == info.sum);
  106 ┆ ASSERT(index_of(1) == 0);
  107 ┆ ASSERT(index_of(3) == 2);
  108 ┆ ASSERT(index_of(5) == 3);
  109 ┆ 110 ┆ return 0;
  111
}
