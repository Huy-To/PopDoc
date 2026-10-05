








#include <stdio.h>
#include <unistd.h>
int main (int argc, char **argv){
  int code;
  while ((code = getopt(argc, argv, "cn:")) != -1) {
    switch (code) {
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
