#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

int inputText(char * string, int index, char * vst);
int inputSymbol(char * string, int index, char sym);

#define MAX_WIDTH 20
#define MAX_HEIGHT 20

int main (void) {
  FILE * fileWithMatrix;

  if ((fileWithMatrix = fopen("graph.txt", "r")) == NULL) {
    printf("Can't open file for reading\n");
    getchar();
    return 0;
  }

  char line[3*MAX_WIDTH];

  int width = 0;
  int height = 0;

  fgets(line, 3*MAX_WIDTH, fileWithMatrix);

  int A[MAX_HEIGHT][MAX_WIDTH];

  for (int i = 0; line[i] != '\0'; ++i) {
    if (line[i] != ' ' && line[i] != '\n') {
      A[0][i] = line[i] - '0';
      ++width;
    }
  }
  ++height;

  while(fgets(line, 3*MAX_WIDTH, fileWithMatrix) != NULL) {
    for (int i = 0; line[i] != '\0'; ++i) {
      if (line[i] != ' ' && line[i] != '\n') {
        A[height][i] = line[i] - '0';
      }
    }
    ++height;
  }

  system(
          "if ls -l | grep graph1.gv; then"
          "  rm graph1.gv;"
          "fi;"
          "touch graph1.gv"
        );


  char * command = (char *) malloc (sizeof(char)*MAX_LENGTH);
  int length = 0;
  
  char vertex[] = "ABCDEFGHIJK";

  length = inputText(command, length, "echo \"graph G {");
  
  for (int j = 0; j != width; ++j) {
    int flag = 1;
    for (int i = 0; i != height; ++i) {
      if (A[i][j] == 1) {
        if (flag) {
          length = inputSymbol(command, length, vertex[i]);
          length = inputText(command, length, " -- ");
          flag = 0;
        } else {
          length = inputSymbol(command, length, vertex[i]);
          length = inputText(command, length, "; ");
        }
      }
    }
  }
  
  length = inputText(command, length, "}\" >> graph1.gv");

  system(command);

  system("dot -Tpng graph1.gv -o file.png && sxiv file.png");
  return 0;
}

int inputText(char * string, int index, char * vst) {
  int i = 0;
  while (vst[i] != '\0') {
    string[index++] = vst[i++];
  }
  return index;
}

int inputSymbol(char * string, int index, char sym) {
  string[index++] = sym;
  return index;
}
