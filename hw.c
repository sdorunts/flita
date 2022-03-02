#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 10

int decimalToBinary (int decimalNumber);
void print (int Array[], int length);

int main (void) {
  int setOfDecimalNumbers[MAX_LENGTH];
  
  for (int i = 0; i != MAX_LENGTH; ++i)
    setOfDecimalNumbers[i] = i;
  
  int setOfBinaryNumbers[MAX_LENGTH];

  for (int i = 0; i != MAX_LENGTH; ++i)
    setOfBinaryNumbers[i] = decimalToBinary(setOfDecimalNumbers[i]);
  
  print(setOfDecimalNumbers, MAX_LENGTH);
  print(setOfBinaryNumbers, MAX_LENGTH);
  
  return 0;
}

int decimalToBinary (int decimalNumber) {
  int binaryNumber = 0; 
  int discharge = 0;
  
  while (decimalNumber > 0) {
    binaryNumber += (int) powf(10, discharge++) * (decimalNumber % 2);
    decimalNumber /= 2;
  }

  return binaryNumber;
}

void print (int Array[], int length) {
  for (int i = 0; i != length; ++i)
    printf("%d ", Array[i]);
  printf("\n");
}

