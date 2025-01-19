#include <iostream>
void enlargement(char**& myArr, int& arrSize)
{
    char** myNewArr = new char* [arrSize * 2];
    for (int i = 0; i < arrSize; i++)
    {
        myNewArr[i] = myArr[i];
    }
    delete[] myArr;
    myArr = myNewArr;
    arrSize *= 2;
}

bool ignoreSpace(char* myLine, int currentIndex)
{
    if (myLine[currentIndex] == ' ')
        return true;
    else
        return false;
}

int isCommand(char* myLine, int strLen)
{
    for (int i = 0; i < strLen; i++)
    {
        if (ignoreSpace(myLine, i) == 1)
            continue;
        else if (myLine[i] == ':')
        {
            return i;
        }
        else
            return -1;
    }
}

char** extractCommand(char* myLine, int strLen,int& lineCount)
{
    int commandStartPos = isCommand(myLine, strLen);
    char** myCommand = new char* [strLen - commandStartPos];
    int spaceCount = 0;
    for (int i = commandStartPos + 1; i < strLen; i++)
    {
        if (ignoreSpace(myLine, i) == 1)
            continue;
        else
        {
            myCommand[lineCount] = new char[10];
            int n;
            for (n = i; ((ignoreSpace(myLine, n) != 1) && myLine[n] != '\0'); n++)
            {
                myCommand[lineCount][spaceCount] = myLine[n];
                spaceCount++;
            }
            myCommand[lineCount][spaceCount] = '\0';
            lineCount++;
            spaceCount = 0;
            i = n;
        }
    }
    return myCommand;
}
int correctText(int rowCount)
{
    int digits = 1;
    while (rowCount >= 10)
    {
        rowCount /= 10;
        digits++;
    }
    return digits;
}
void Print(char** myArray, int rowCount)
{
    int digits = correctText(rowCount);
    for (int i = 0; i < rowCount; i++)
    {
        int zeros = digits - correctText(i);
        while (zeros > 0)
        {
            std::cout << "0";
            zeros /= 10;
        }
        std::cout << i << " ";
        std::cout << myArray[i] << std::endl;
    }
}
int main()
{
    char myEntry[1024];
    int arrSize = 2;
    int rowCount = 0;
    char** myArray = new char* [arrSize];
    while (true)
    {
        std::cin.getline(myEntry, 1024, '\n');
        int len = strlen(myEntry);

        if (isCommand(myEntry, len) != -1)
        {
            int lineCount = 0;
            char** myCommand = (extractCommand(myEntry, len,lineCount));
            if (myCommand[lineCount-1][0] == 'P')
            {
                Print(myArray, rowCount);
            }
            continue;
        } 

        if (strcmp(myEntry,"Q") == 0)
        {
            for (int n = 0; n < rowCount; n++)
            {
                std::cout << myArray[n] << std::endl;
            }
            break;
        }
        if (rowCount == arrSize)
        {
            enlargement(myArray, arrSize);
        }
        myArray[rowCount] = new char[len+1];
        for (int i = 0; i < len; i++)
        {
            myArray[rowCount][i] = myEntry[i];
        }
        myArray[rowCount][len] = '\0';
        rowCount++;
    }
    for (int i = 0; i < rowCount; i++)
    {
        delete[] myArray[i];
    }
    delete[] myArray;
}

