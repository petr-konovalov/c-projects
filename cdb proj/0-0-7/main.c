#include <stdio.h>
#include <stdlib.h>

int main()
{
    enum manth{yan, feb, mar, apr} d = yan;
    enum manth dd = feb;

    switch (dd)
    {
        case yan:
        {
            printf("yan");
            break;
        }
        case feb:
        {
            printf("feb");
        }
        case mar:
        {
            printf("mar");

        }
        case apr:
        {
            printf("apr");
            break;
        }
    }

    return 0;
}
