#include <iostream>
#include<cstring>
char* getNumber(char firstArray[], char secondArray[], int wordSize, bool& stop)
{
	for (int j = wordSize + 1; firstArray[j] != '\0' && !stop; j++)
	{
		if ('0' <= firstArray[j] && firstArray[j] <= '9')
		{
			stop = true;
			int numberSize = 0;
			for (int n = j; firstArray[n] != '\0' && firstArray[n] != ' '; n++)
			{
				secondArray[numberSize] = firstArray[n];
				numberSize++;
			}
			secondArray[numberSize] = '\0';
		}
	}
	return secondArray;
}
char* subString(char firstArray[], int wordSize)
{
	int arrCount = 0;
	char secondArray[128]{};
	for (int i = 0; i < wordSize; i++)
	{
		if (firstArray[i] == '.')
		{
			i++;
		}
		secondArray[arrCount] = firstArray[i];
	}
	return secondArray;
}
double strtoInt(char myArray[])
{
	double myNumber = 0;
	for (int i = 0; myArray[i] != '\0'; i++)
	{
		myNumber = myNumber * 10 + (myArray[i] - '0');
	}
	return myNumber;
}
double stringToInt(char myArray[])
{
    double beforeDecimal = 0;
	double afterDecimal = 0;
	double myNumber = 0;
	int count = 0;
	int numberSize = 0;
	for (int i = 0; myArray[i] != '\0'; i++)
		numberSize++;

	for (int q = 0; (myArray[q] != '\0') && (myArray[q] != '.'); q++)
	{
		beforeDecimal = beforeDecimal * 10 + (myArray[q] - '0');
		count++;
	}
	if (myArray[count] == '.')
	{
		for (int f = numberSize - 1; myArray[f] != '.'; f--)
		{
			afterDecimal = (afterDecimal / 10 + (myArray[f] - '0'))/10;
		}
	}
	myNumber = beforeDecimal + afterDecimal;
	return myNumber;

}
int main()
{
	int objectArea = 0;
	char myArray[128]{};
	std::cin.getline(myArray, 128);
	int wordSize = 0;
	char mySecondArr[128]{};
	bool stop = false;
	for (int i = 0; myArray[i] != '\0'; i++)
	{
		if (myArray[i] != ' ')
		{
			mySecondArr[wordSize] = myArray[i];
			wordSize++;
		}
		if (strcmp(mySecondArr, "square") == 0)
		{
			char* squareSideStr = getNumber(myArray, mySecondArr, wordSize, stop);
			if (squareSideStr != nullptr)
			{
				double squareSide = stringToInt(squareSideStr);
				double squareArea = squareSide * squareSide;
				std::cout << "The area of the square is: " << squareArea;
			}
		}
		if (strcmp(mySecondArr, "circle") == 0)
		{
			char* circleSideStr = getNumber(myArray, mySecondArr, wordSize, stop);
			if (circleSideStr != nullptr)
			{
				const double pi = 3.14;
				double circleRadius = stringToInt(circleSideStr);
				double circleArea = pi * pow(circleRadius, 2);
				std::cout << "The area of the circle is: " << circleArea;
			}
		}
	}
}

