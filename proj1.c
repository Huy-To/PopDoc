#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define buff_size 256

/*===================================================*/
// define a struct...
//
// -`unsigned`` cause we're dealing with only '+' cases
/*===================================================*/
typedef struct HuffNode {

  unsigned int frequency; // frequency > 0
  unsigned char c;

  struct HuffNode *left;
  struct HuffNode *right;
} HuffNode;

/*===================================================*/
// Function to createNode
//
//- *createNode(frequency, character) { returns @ of a FRESH node }
//- Using @ here cause why not..?
/*===================================================*/
HuffNode *createNode(unsigned int f, unsigned char c) {
  HuffNode *newNode = malloc(sizeof(HuffNode));
  if (newNode == NULL) {
    return NULL;
  }
  newNode->frequency = f;
  newNode->c = c;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}
/*===================================================*/
// Function to create a List for all of the nodes
/*===================================================*/
int buildNodeList(unsigned int f[], HuffNode *nodeList[]) {
  int count = 0;

  for (int i = 0; i < buff_size; i++) {
    if (f[i] > 0) {
      nodeList[count] = createNode((unsigned int)f[i], (unsigned char)i);
      count++;
    }
  }
  return count; //                        return #nodes in nodeList //
}

/*===================================================*/
// Function to swap Node Address
// Swaping address for conviniency
/*===================================================*/
void swap(HuffNode **address1, HuffNode **address2) {
  HuffNode *temp = *address1;
  *address1 = *address2;
  *address2 = temp;
}
/*===================================================*/
// Function to moveDown the node if parent >= children
// (frequency)
/*===================================================*/
void moveDown(HuffNode *nodeList[], int size, int i) {
  while (1) {
    int index = i;
    int left = 2 * i + 1; // Because root is already at 0
    int right = 2 * i + 2;

    if (left < size && nodeList[left]->frequency < nodeList[index]->frequency) {
      index = left;
    }
    if (right < size &&
        nodeList[right]->frequency < nodeList[index]->frequency) {
      index = right;
    }
    if (index == i) {
      return;
    }
    swap(&nodeList[i], &nodeList[index]);
    i = index;
  }
}
/*===================================================*/
// Function to moveUp the node if parent <= children (frequency)
/*===================================================*/

void moveUp(HuffNode *nodeList[], int i) {
  while (i > 0) {
    int indexParent = (i - 1) / 2;
    if (nodeList[indexParent]->frequency <= nodeList[i]->frequency) {
      return;
    }
    swap(&nodeList[i], &nodeList[indexParent]);
    i = indexParent;
  }
}
/*===================================================*/
// Function to build heap
/*===================================================*/
void buildHeap(HuffNode *nodeList[], int size) {
  for (int i = size / 2 - 1; i >= 0; i--) {
    moveDown(nodeList, size, i);
  }
}
/*===================================================*/
// Function to insert node into heap
/*===================================================*/
void insertNode(HuffNode *nodeList[], int *size, HuffNode *node) {
  nodeList[*size] = node;
  moveUp(nodeList, *size);
  (*size)++;
}
/*===================================================*/
// Function to return the smallest node
/*===================================================*/
HuffNode *minNode(HuffNode *nodeList[], int *size) {
  HuffNode *minNode = nodeList[0];
  (*size)--;
  nodeList[0] = nodeList[*size]; // move the last node to the top
  moveDown(nodeList, *size, 0);
  return minNode;
}

/*===================================================*/
// Function to build Huff Tree
/*===================================================*/
HuffNode *Tree(HuffNode *nodeList[], int size) {
  // Heapify
  buildHeap(nodeList, size);

  while (size > 1) {
    HuffNode *node1 = minNode(nodeList, &size);
    HuffNode *node2 = minNode(nodeList, &size);
    HuffNode *parent = createNode(node1->frequency + node2->frequency, '\0');
    parent->left = node1;
    parent->right = node2;

    insertNode(nodeList, &size, parent);
  }

  return nodeList[0];
}

/*===================================================*/
// Traverse The Tree
// left = 0
// right =  1
/*===================================================*/
void vroomVroom01(HuffNode *root, char ch[], int nodeIndex, char *binaries[]) {
  if (root == NULL) {
    return;
  }
  if (root->left == NULL && root->right == NULL) {
    ch[nodeIndex] = '\0'; // EOF
    binaries[root->c] = strdup(ch);
    return;
  }

  ch[nodeIndex] = '0';
  vroomVroom01(root->left, ch, nodeIndex + 1, binaries);

  ch[nodeIndex] = '1';
  vroomVroom01(root->right, ch, nodeIndex + 1, binaries);
}

void vroomVroomFree(HuffNode *root) {
  if (root == NULL) {
    return;
  }
  vroomVroomFree(root->left);
  vroomVroomFree(root->right);
  free(root);
}

/*Maybe should be used for options */
int main(int argc, char **argv) {
  char *inputFile = "completeShakespeare.txt";
  char *outputFile = "huffshake.out";

  int input;
  while ((input = getopt(argc, argv, "i:o:")) != -1) {
    switch (input) {
    case 'i':
      inputFile = optarg;
      break;
    case 'o':
      outputFile = optarg;
      break;
    }
  }

  unsigned int frequency[buff_size] = {0}; // Allocating Memory
  int c;
  FILE *fileOpened = fopen(inputFile, "r");
  if (fileOpened == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);

    // This is lowkey like teaching human's math to an alien (HARDWARE) T_T
    // Bro cant tell the difference between a character and a number @_@ (0,1)
  }
  while ((c = fgetc(fileOpened)) != EOF) {
    frequency[c]++;
  }
  fclose(fileOpened);

  HuffNode *list[buff_size];
  int count = buildNodeList(frequency, list);
  if (count == 0) {
    fprintf(stderr, "Bruh, its empty\n");
    return 0;
  }

  HuffNode *root = Tree(list, count);
  if (root == NULL) {
    return 0;
  }

  char ch[buff_size];
  char *binaries[buff_size] = {0};
  vroomVroom01(root, ch, 0, binaries);

  /* Free MEMORY */
  vroomVroomFree(root);
  // Freeing compressed code
  for (int i = 0; i < buff_size; i++) {
    free(binaries[i]);
  }
  return 0;

  // outputFile
  // binaries
  // inputFile
}
