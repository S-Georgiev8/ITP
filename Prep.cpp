#include <iostream>
int strToNum(char* myString);
char* subString(char* myString, int startIndex, int endIndex);
int strToDigit(const char* myString);

char* subString(char* myString, int startIndex, int endIndex) // Creating a function to extract a substring from the user input so we can work easier.
{
	int length = strlen(myString); // Getting the length of the substring
	if (endIndex >= length)
		endIndex = length - 1; // In case the endIndex exceeds the user input, we extract a substring from the startIndex up until the end of the input string.

	char* subStr = new char[endIndex - startIndex + 2] {}; // Making a new C-style array to store our substring
	for (int i = 0; i < endIndex - startIndex + 1; i++)
	{
		subStr[i] = myString[startIndex+i]; // Loop that stores the characters in the array
	}
	return subStr; // Returning the substring.
}
int strToNum(char* myString) // Creating a function that works on the extracted substring.
{
	int myNum = 0; // Variable that stores the value of a substring.
	int length = strlen(myString); // Length of the substring
	int numIndex = 0; // Variable that keeps track of our progress when working with the substring.
	while (numIndex < length) // loop that continues as long as we are not done with the substring
	{
		char* numString = subString(myString, numIndex, numIndex + 2); // C-style array that uses the subString function to store the first 3 characters.
		int myDigit = strToDigit(numString); // Variable that stores the digit value of a substring.

		if (myDigit != -1) // checking if the current 3 characters spell out a digit's name. If yes...
		{
			myNum = myNum * 10 + myDigit; // Formula to get the substring value in int.
			numIndex += 3; // Updating our progression through the substring
			delete[] numString;
			continue; // no need to check the other IFs if we already found a match.
		}
		else // If the current 3 characters don't find a match, we take the, we get the next one as well.
		{
			delete[] numString;
			numString = subString(myString, numIndex, numIndex + 3);
			myDigit = strToDigit(numString);
		}
		if (myDigit != -1)
		{
			myNum = myNum * 10 + myDigit;
			if (myNum == 0 && (myString[numIndex + 4] != '\0')) // Checking if zero+<any_number> defines the substring. If so, return an erroneous value.
				return -1;
			numIndex += 4;
			delete[] numString;
			continue;
		}
		else
		{
			delete[] numString;
			numString = subString(myString, numIndex, numIndex + 4);
			myDigit = strToDigit(numString);
		}
		if (myDigit != -1)
		{
			myNum = myNum * 10 + myDigit;
			numIndex += 5;
			delete[] numString;
			continue;
		}
		else
		{
			delete[] numString; // making sure we delete the dynamically allocated memory even if we dont find a match.
			return -1;
		}
	}
	return myNum; // return the value of the substring.
}
int strToDigit(const char* myString) // Self-explanetory function. Converts a digit written in string to an int value.
{
	const char* digitArray[] = {"zero","one","two","three","four","five","six","seven","eight","nine"}; // C-style array to store the "strings"
	for (int n = 0; n <= 9; n++) // loop that checks if a string matches any of the 10 strings in the array. If so, returns the value in int.
	{
		if (strcmp(digitArray[n], myString) == 0)
			return n;
	}
	return -1; // If not match has been found, return an erroneous value.
}
int calculateExp(char* myString) // Our "main" function in this code. Uses the other 3 to give out the final result.
{
	int length = strlen(myString); // gets the length of the input string
	int startIndex = 0;
	int endIndex = 0;
	int sum = 0; // final value
	bool add = true; // bool variable that helps us decide if we should add or substract the next number.
	for (int n = startIndex; n <= length; n++)
	{
		if (myString[n] == 'p') // p is only found in plus among the digits and plus/minus.
		{
			if (strcmp(subString(myString, n, n + 3), "plus") != 0) // checking if its actually plus, not a fraction of it. ex: pl.
				return INT_MAX; // if not, return a specific value;
			else if (myString[n + 4] == '\0') // checking if theres something after the "plus" so we dont end up with: "threeplus"
				return INT_MAX;
			endIndex = n - 1;
			char* mySubStr = subString(myString, startIndex, endIndex); // getting the substring between the plus/minus/n = 0/'\0'.
			int myNum = strToNum(mySubStr); // checking if said substring returns a valid value.
			if (myNum == -1)
				return INT_MAX;

			if (add)
			{
				sum += myNum;
			}
			else
			{
				sum -= myNum;
			}

			add = true; // changing the value of "add" in case we found a plus
			startIndex = n + 4; // updating our progression over the index;
			n += 4; // updating the value of n so we dont go over the character of plus
			delete[] mySubStr;
		}
		else if (myString[n] == 'm')
		{
			if (strcmp(subString(myString, n, n + 4), "minus") != 0)
				return INT_MAX;
			else if (myString[n + 5] == '\0')
				return INT_MAX;
			endIndex = n - 1;
			char* mySubStr = subString(myString, startIndex, endIndex);
			int myNum = strToNum(mySubStr);
			if (myNum == -1)
				return INT_MAX;

			if (add)
			{
				sum += myNum;
			}
			else
			{
				sum -= myNum;
			}

			add = false;
			startIndex = n + 5;
			n += 5;
			delete[] mySubStr;
		}
		else if (myString[n] == '\0')
		{
			endIndex = n - 1;
			char* mySubStr = subString(myString, startIndex, endIndex);
			int myNum = strToNum(mySubStr);
			if (myNum == -1)
				return INT_MAX;

			if (add)
			{
				sum += myNum;
			}
			else
			{
				sum -= myNum;
			}

			delete[] mySubStr;
		}
	}
	return sum;
}
int main()
{
	std::cout << "Enter array size: ";
	int size;
	std::cin >> size;

	std::cout << "\nEnter a string: ";
	char* myExp = new char[size];

	std::cin >> myExp;
	int result = calculateExp(myExp);
	if (result == INT_MAX)
		std::cout << "You've entered an invalid input. Please try again!";
	else
	std::cout << "\nThe sum of the numbers is: " << result;

}


