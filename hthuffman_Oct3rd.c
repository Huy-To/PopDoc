#include <stdio.h>
#include <stdlib.h>

#define cSize 256

typedef struct HuffNode {

  unsigned frequency[]; // frequency > 0
  char c[];

  struct HuffNode *left;
  struct HuffNode *right;
} HuffNode;

// Function to createNode
/*===================================================*/
HuffNode *createNode(unsigned f, char c) {
  HuffNode *newNode = malloc(sizeof(HuffNode));
  if (newNode == NULL) {
    return NULL;
  }
  newNode->frequency = f;
  newNode->c = c;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
};
// createNode(frequency, character)
/*===================================================*/

// Function to addNode
/*===================================================*/
HuffNode *addNode(HuffNode *head, unsigned f, unsigned c) {
  if (head == NULL) {
    createNode(f, c);
  }
  // Heapify
}

/*===================================================*/

/*Maybe should be used for options */
int main() {

  unsigned uniqueC[cSize];
  unsigned c;
  unsigned index = 0;
  FILE *fileOpened = fopen("completeShakespeare.txt", "r");

  if (fileOpened != NULL) {
    while ((c = fgetc(fileOpened) != EOF) && index < cSize) {
      uniqueC[index] = c;
      index++;
    }
  };
  {
    return 0;
  }
}
