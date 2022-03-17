#include <stdio.h>
#include <ctype.h>

#define MAX_WIDTH 60
#define MAX_HEIGHT 30
#define VERTICES_NUMBER 2

int main(void) {
  FILE * fileWithMatrix = fopen("graph.txt", "r");

  if (fileWithMatrix == NULL) {
    printf("Can't open file for reading\n");
    getchar();
    return 1;
  }
  
  int c;
  int lineIndex = 0;
  int width = 0;
  int height = 0;
  int A[MAX_HEIGHT][MAX_WIDTH];

  while((c = fgetc(fileWithMatrix)) != EOF) {
    if (c == '\n') {
      if (!height) // В первый раз вошли в этот if
        width = lineIndex;
      lineIndex = 0;
      ++height;
    } else if (isdigit(c)) {
      A[height][lineIndex++] = c;
    }
  }
  ++height;
  
  int previousColumn[VERTICES_NUMBER] = {-1, -1};
  int currentColumn[VERTICES_NUMBER] = {-1, -1};
  int elementIndex = 0;
  int graphEdgeNumber = 0;

  for (int i = 0; i != width; ++i) {
    for (int j = 0; j != height; ++j) {
      if (A[j][i] == '1') {
        currentColumn[elementIndex++] = j;
      }
    }
    elementIndex = 0;
    if ((currentColumn[0] != previousColumn[0] || 
         currentColumn[1] != previousColumn[1]) && 
         currentColumn[0] != -1 && currentColumn[1] != -1) {
      ++graphEdgeNumber;
    }
    for (int k = 0; k != VERTICES_NUMBER; ++k) {
      previousColumn[k] = currentColumn[k];
      currentColumn[k] = -1;
    }
  }
  if (graphEdgeNumber > (height - 1)*(height - 2)/2)
    printf("Yes!\n");
  else
    printf("No!\n");
  return 0;
}
