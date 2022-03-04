#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 100

int decimalToBinary (int decimalNumber);
void print (int Array[], int length);

int main (void) {
  int setOfDecimalNumbers[MAX_LENGTH];
  
  int countOfNumbers = 0;
  printf("Сколько чисел вы хотите ввести?\n>> ");
  scanf("%d", &countOfNumbers);
  
  for (int i = 0; i != countOfNumbers; ++i)
    setOfDecimalNumbers[i] = i;
  
  int setOfBinaryNumbers[MAX_LENGTH];

  for (int i = 0; i != countOfNumbers; ++i)
    setOfBinaryNumbers[i] = decimalToBinary(setOfDecimalNumbers[i]);
  
  print(setOfDecimalNumbers, countOfNumbers);
  print(setOfBinaryNumbers, countOfNumbers);
  
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

