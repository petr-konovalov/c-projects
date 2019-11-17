#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{
    FILE *firstFile;
    FILE *secondFile;
    char *firstFileName;
    char *secondFileName;
    int splitResult;
} SplittedFileInformation;

typedef struct
{
    SplittedFileInformation fileStatus;
    FILE *sortedFile;
    int stringLength;
    char *firstString;
    char *secondString;
    char delim[2];
} SplittedStatus;

int strComp(char *firstString, char *secondString)
{
    while (*firstString != '\0' && *secondString != '\0'
           && *firstString == *secondString)
    {
        ++firstString;
        ++secondString;
    }
    return *firstString == *secondString ? 0 : *firstString > *secondString ? 1 : -1;
}

void strCopy(char *source, const char *dest)
{
    while (*dest != '\0')
    {
        *source = *dest;
        ++source;
        ++dest;
    }
    *source = '\0';
}

int strLength(char *source)
{
    int length = 0;

    while (source[length] != '\0')
        ++length;

    return length;
}

void convertString(char *string, const char endSymbol)
{
    while (*string != endSymbol && *string != '\0')
        ++string;

    *string = '\0';
}

char *strCat(char *firstString, const char *secondString, const char firstEndSymbol, char const secondEndSymbol)
{
    while (*firstString != firstEndSymbol && *firstString != '\0')
        ++firstString;
    while (*secondString != secondEndSymbol && *secondString != '\0')
    {
        *firstString = *secondString;
        ++firstString;
        ++secondString;
    }
    *firstString = '\0';
    return firstString;
}

void putSplitFile(char *delim, const char *inputString, SplittedFileInformation *status, const int fileIndex)
{
    FILE *currentFile;

    if (fileIndex)
        currentFile = status->secondFile;
    else
        currentFile = status->firstFile;

    if (delim[fileIndex] != '\0')
        fputc(delim[fileIndex], currentFile);

    fputs(inputString, currentFile);
    delim[fileIndex] = '\n';
}

void putMergeFile(char *delim, const char *string, FILE *mergeFile)
{
    if (*delim != '\0')
        fputc(*delim, mergeFile);
    fputs(string, mergeFile);
    *delim = '\n';
}

void initSplittedStatus (char *fileName, SplittedStatus *status)
{
    int length = strLength(fileName);
    status->fileStatus.firstFileName = malloc(length + 4);
    status->fileStatus.secondFileName = malloc(length + 4);
    status->fileStatus.firstFileName[0] = '~';
    status->fileStatus.secondFileName[0] = '~';
    status->fileStatus.firstFileName[1] = '\0';
    status->fileStatus.secondFileName[1] = '\0';
    strCat(strCat(status->fileStatus.firstFileName, fileName, '\0', '.'), "f1.txt", '\0', '\0');
    strCat(strCat(status->fileStatus.secondFileName, fileName, '\0', '.'), "f2.txt", '\0', '\0');
    status->fileStatus.firstFile = fopen(status->fileStatus.firstFileName, "w");
    status->fileStatus.secondFile  = fopen(status->fileStatus.secondFileName, "w");
    status->fileStatus.splitResult  = 0;
    status->firstString = malloc(status->stringLength);
    status->secondString = malloc(status->stringLength);
    status->delim[0] = '\0';
    status->delim[1] = '\0';
}

void updateSplittedFiles(SplittedStatus *status, const char *seriesDelim, int *fileIndex)
{
    char *tempString = status->secondString;
    status->secondString = fgets(status->secondString, status->stringLength, status->sortedFile);
    convertString(status->firstString, '\n');
    putSplitFile(status->delim, status->firstString, &status->fileStatus, *fileIndex);
    if (status->secondString)
    {
        if (strComp(status->firstString, status->secondString) == 1)
        {
            putSplitFile(status->delim, seriesDelim, &status->fileStatus, *fileIndex);
            *fileIndex = 1 - *fileIndex;
            status->fileStatus.splitResult = 1;
        }
        strCopy(status->firstString, status->secondString);
    }
    else
    {
        free(tempString);
        status->firstString = NULL;
    }
}

SplittedFileInformation splitFile(char *fileName, FILE *sortedFile, const char *seriesDelim, const int stringLength)
{
    int fileIndex = 0;
    SplittedStatus status;
    status.stringLength = stringLength;
    status.sortedFile = sortedFile;
    initSplittedStatus(fileName, &status);
    char *tempString = status.firstString;
    status.firstString = fgets(status.firstString, status.stringLength, sortedFile);

    while (status.firstString)
        updateSplittedFiles(&status, seriesDelim, &fileIndex);

    free(tempString);
    putSplitFile(status.delim, seriesDelim, &status.fileStatus, fileIndex);
    return status.fileStatus;
}

void mergeFiles(FILE *sortedFile, SplittedFileInformation *splittedResult, const char *seriesDelim, const int stringLength)
{
    char firstString[stringLength];
    char secondString[stringLength];
    char *b = NULL;
    char delim = '\0';
    while ((b = fgets(firstString, stringLength, splittedResult->firstFile)) &&
           fgets(secondString, stringLength, splittedResult->secondFile))
    {
        convertString(firstString, '\n');
        convertString(secondString, '\n');
        while (strComp(firstString, seriesDelim) && strComp(secondString, seriesDelim))
        {
            if (strComp(firstString, secondString) == -1)
            {
                putMergeFile(&delim, firstString, sortedFile);
                fgets(firstString, stringLength, splittedResult->firstFile);
                convertString(firstString, '\n');
            }
            else
            {
                putMergeFile(&delim, secondString, sortedFile);
                fgets(secondString, stringLength, splittedResult->secondFile);
                convertString(secondString, '\n');
            }
        }
        while (strComp(firstString, seriesDelim))
        {
            putMergeFile(&delim, firstString, sortedFile);
            fgets(firstString, stringLength, splittedResult->firstFile);
            convertString(firstString, '\n');
        }
        while (strComp(secondString, seriesDelim))
        {
            putMergeFile(&delim, secondString, sortedFile);
            fgets(secondString, stringLength, splittedResult->secondFile);
            convertString(secondString, '\n');
        }
    }
    if (b)
    {
        convertString(firstString, '\n');
        while (strComp(firstString, seriesDelim))
        {
            putMergeFile(&delim, firstString, sortedFile);
            fgets(firstString, stringLength, splittedResult->firstFile);
            convertString(firstString, '\n');
        }
    }
}

void sortFile(char *fileName)
{
    const int stringLength = 128;
    const char *seriesDelim = "----------";
    FILE *sortedFile = NULL;
    sortedFile = fopen(fileName, "r");
    SplittedFileInformation splitResult = splitFile(fileName, sortedFile, seriesDelim, stringLength);

    while (splitResult.splitResult)
    {
        fclose(sortedFile);
        fclose(splitResult.firstFile);
        fclose(splitResult.secondFile);
        sortedFile = fopen(fileName, "w");
        splitResult.firstFile = fopen(splitResult.firstFileName, "r");
        splitResult.secondFile = fopen(splitResult.secondFileName, "r");
        mergeFiles(sortedFile, &splitResult, seriesDelim, stringLength);
        fclose(sortedFile);
        fclose(splitResult.firstFile);
        fclose(splitResult.secondFile);
        sortedFile = fopen(fileName, "r");
        splitResult = splitFile(fileName, sortedFile, seriesDelim, stringLength);
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int fileNameLength = 128;
    char fileName[fileNameLength];
    printf("ֲגוהטעו טלÿ פאיכא: ");
    scanf("%s", fileName);
    sortFile(fileName);
    return 0;
}
