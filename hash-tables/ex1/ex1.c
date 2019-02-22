#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  // HASH TABLE
  HashTable *ht = create_hash_table(16);

  // INIT ANSWER STRUCT
  Answer *answers = malloc(sizeof(Answer));
  // -1 default for conditional tests
  answers->index_1 = -1;
  answers->index_2 = -1;

  for (int i = 0; i < length; i++)
  {
    // Store key: weights[i], value: i in ht
    hash_table_insert(ht, weights[i], i);
  }

  // FIND INDECIES THAT ADD UP TO WEIGHT
  for (int i = 0; i < length; i++)
  {
    int retrieved = hash_table_retrieve(ht, limit - weights[i]);
    // if in hash table
    if (retrieved != -1)
    {
      // if first index found
      if (answers->index_2 == -1)
      {
        answers->index_2 = i;
      }
      // it's the second index
      else
      {
        answers->index_1 = i;
      }
    }
  }

  // REMOVE HT FROM MEMORY
  destroy_hash_table(ht);

  // If only one index is found in hash table
  if (answers->index_1 == -1)
  {
    return NULL;
  }

  return answers;
}

void print_answer(Answer *answer)
{
  if (answer != NULL)
  {
    printf("%d %d\n", answer->index_1, answer->index_2);
  }
  else
  {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{

  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1); // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer *answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2); // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer *answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3); // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer *answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4); // {6, 2}

  return 0;
}
#endif
