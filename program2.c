








#include <stdio.h>
#include <unistd.h>
int main (int argc, char **argv){
  int code;
  while ((code = getopt(argc, argv, "cna:")) != -1) {
    switch (code) {
    case 'a':
      printf("I love Pokemon!! \n");
      break;
    case 'c':
      printf("unassigned option c\n");
      break;
    case 'n':
      printf("Howdy, %s\n", optarg);
      break;
    default: //invalid options handled inside getopt() call
    }
  }
}
