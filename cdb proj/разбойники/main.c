#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct RobberInformation
{
    char *name;
    int isLive;
    int horses;
    int wites;
    int rubies;
    int necklace;
    int wifes;
    int money;
    int wealth;
};

const int maxRobberNameLength = 16;
const int maxHorsesCount = 10;
const int maxWitesCount = 30;
const int maxRubiesCount = 1000;
const int maxNecklaceCount = 5000;
const int maxWifesCount = 5;
const int maxMoneyCount = 10000;

const int horsePrice = 500;
const int witePrice = 100;
const int rubiePrice = 50;
const int necklacePrice = 10;
const int wifeCost = 200;

void updateResult(struct RobberInformation *result, struct RobberInformation *robber, const int isAdd)
{
    if (isAdd)
    {
        result->horses += robber->horses;
        result->wites += robber->wites;
        result->rubies += robber->rubies;
        result->necklace += robber->necklace;
        result->wifes += robber->wifes;
        result->money += robber->money;
        result->wealth += robber->wealth;
    }
    else
    {
        result->horses -= robber->horses;
        result->wites -= robber->wites;
        result->rubies -= robber->rubies;
        result->necklace -= robber->necklace;
        result->wifes -= robber->wifes;
        result->money -= robber->money;
        result->wealth -= robber->wealth;
    }
}

void updateWealth(struct RobberInformation *robber)
{
    robber->wealth = robber->horses * horsePrice +
                     robber->wites * witePrice +
                     robber->rubies * rubiePrice +
                     robber->necklace * necklacePrice +
                     robber->money -
                     robber->wifes * wifeCost;
}

void printTable()
{
    printf("%10s%7s%9s%7s%8s%10s%6s%8s%11s\n",
           "им€", "живой", "скакуны", "сабли", "рубины", "ожерель€", "жЄны", "деньги", "богатство");
}

void printRobberInformation(struct RobberInformation *robber)
{
    printf("%10s%7i%9i%7i%8i%10i%6i%8i%11i\n",
           robber->name, robber->isLive, robber->horses, robber->wites, robber->rubies,
           robber->necklace, robber->wifes, robber->money, robber->wealth);
}

void printResultTable()
{
    printf("%11s%9s%10s%12s%8s%10s%13s\n",
           "скакуны", "сабли", "рубины", "ожерель€", "жЄны", "деньги", "богатство");
}

void printResultInformation(struct RobberInformation *result)
{
    printf("%11i%9i%10i%12i%8i%10i%13i\n",
           result->horses, result->wites, result->rubies,
           result->necklace, result->wifes, result->money, result->wealth);
}

void printAllPossession(struct RobberInformation *result)
{
    printResultTable();
    printResultInformation(result);
}

void printAllBand(struct RobberInformation *robbers, const int robbersCount)
{
    int i = 0;
    printTable();
    for (i = 0; i < robbersCount; ++i)
        printRobberInformation(&robbers[i]);
}

void printLiveBand(struct RobberInformation *robbers, const int robbersCount)
{
    int i = 0;
    printTable();
    for (i = 0; i < robbersCount; ++i)
        if (robbers[i].isLive)
            printRobberInformation(&robbers[i]);
}

void printRichest(struct RobberInformation *robbers, const int robberCount)
{
    int richest = 0;
    int i = 0;
    for (i = 0; i < robberCount; ++i)
        if (robbers[i].isLive && robbers[i].wealth > robbers[richest].wealth)
            richest = i;
    printTable();
    for (i = 0; i < robberCount; ++i)
        if (robbers[i].wealth == robbers[richest].wealth)
            printRobberInformation(&robbers[i]);
}

void killRobber(struct RobberInformation *robbers, const int robbersCount, struct RobberInformation *result)
{
    char name[maxRobberNameLength];
    printf("¬ведите им€: ");
    scanf("%s", name);
    int i = 0;
    for (i = 0; i < robbersCount; ++i)
        if (robbers[i].isLive, strComp(name, robbers[i].name))
        {
            printf("%s был успешно убит\n", name);
            robbers[i].isLive = 0;
            updateResult(result, &robbers[i], 0);
            return;
        }
    printf("к сожалению разбойник не был найден\n");
}

void addRobber(struct RobberInformation *robbers, int *robbersCount, struct RobberInformation *result)
{
    robbers[*robbersCount].isLive = 1;
    robbers[*robbersCount].name = malloc(maxRobberNameLength);
    printf("им€: ");
    scanf("%s", robbers[*robbersCount].name);
    printf("скакуны: ");
    scanf("%i", &robbers[*robbersCount].horses);
    printf("сабли: ");
    scanf("%i", &robbers[*robbersCount].wites);
    printf("рубины: ");
    scanf("%i", &robbers[*robbersCount].rubies);
    printf("ожерель€: ");
    scanf("%i", &robbers[*robbersCount].necklace);
    printf("жЄны: ");
    scanf("%i", &robbers[*robbersCount].wifes);
    printf("деньги: ");
    scanf("%i", &robbers[*robbersCount].money);

    updateWealth(&robbers[*robbersCount]);
    updateResult(result, &robbers[*robbersCount], 1);

    *robbersCount += 1;
}

void printInformationRobberName(struct RobberInformation *robbers, const int robbersCount)
{
    char name[maxRobberNameLength];
    printf("¬ведите им€: ");
    scanf("%s", name);
    int i = 0;
    printTable();
    for (i = 0; i < robbersCount; ++i)
        if (strComp(name, robbers[i].name))
            printRobberInformation(&robbers[i]);
}

void convertName(char *name)
{
    int i = 0;
    while(name[i] != '\0')
    {
        ++i;
    }
    name[i - 2] = '\0';
}

int strComp(char *first, char *second)
{
    int i = 0;
    while (first[i] != '\0' && second[i] !='\0' && first[i] == second[i])
        ++i;
    return first[i] == second[i];
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int robbersCount = 10;
    FILE *robberListFile = fopen("robbers.txt", "r");
    struct RobberInformation robbers[64];
    struct RobberInformation result;

    result.name = NULL;
    result.isLive = 0;
    result.horses = 0;
    result.wites = 0;
    result.rubies = 0;
    result.necklace = 0;
    result.wifes = 0;
    result.money = 0;
    result.wealth = 0;

    int i = 0;

    printf("количество разбойников: ");
    scanf("%i", &robbersCount);
    //srand(time(0));
    for (i = 0; i < robbersCount; ++i)
    {
        robbers[i].name = malloc(maxRobberNameLength);
        fgets(robbers[i].name, maxRobberNameLength, robberListFile);
        convertName(robbers[i].name);
        robbers[i].isLive = 1;
        robbers[i].horses = rand() % maxHorsesCount;
        robbers[i].wites = rand() % maxWitesCount;
        robbers[i].rubies = rand() % maxRubiesCount;
        robbers[i].necklace = rand() % maxNecklaceCount;
        robbers[i].wifes = rand() % maxWifesCount;
        robbers[i].money = rand() % maxMoneyCount;

        updateWealth(&robbers[i]);
        updateResult(&result, &robbers[i], 1);
    }

    int command = -1;
    while (command)
    {
        scanf("%i", &command);
        switch (command)
        {
            case 1:
            {
                printAllPossession(&result);
                break;
            }
            case 2:
            {
                printAllBand(robbers, robbersCount);
                break;
            }
            case 3:
            {
                printLiveBand(robbers, robbersCount);
                break;
            }
            case 4:
            {
                printRichest(robbers, robbersCount);
                break;
            }
            case 5:
            {
                killRobber(robbers, robbersCount, &result);
                break;
            }
            case 6:
            {
                addRobber(robbers, &robbersCount, &result);
                break;
            }
            case 7:
            {
                printInformationRobberName(robbers, robbersCount);
                break;
            }
        }
    }
    for (i = 0; i < robbersCount; ++i)
        free(robbers[i].name);
    return 0;
}
