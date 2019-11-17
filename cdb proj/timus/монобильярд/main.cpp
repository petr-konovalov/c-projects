#include <map>
#include <stdio.h>

using namespace std;

int main()
{
    int n = 0;

    scanf("%i", &n);

    int begining[n];
    int ending[n];
    for (int i = 0; i < n; ++i)
    {
        begining[i] = -1;
        ending[i] = -1;
    }

    int prevBall = 0;
    scanf("%i", &prevBall);
    --prevBall;
    begining[prevBall] = prevBall;
    ending[prevBall] = prevBall;

    bool result = true;
    for (int i = 1; i < n; ++i)
    {
        int nextBall;
        scanf("%i", &nextBall);
        if (result)
        {
            --nextBall;
            if (nextBall == 0 || begining[nextBall - 1] == -1)
                begining[nextBall] = nextBall;
            else
                begining[nextBall] = begining[nextBall - 1];

            if (nextBall == n - 1 || ending[nextBall + 1] == -1)
                ending[nextBall] = nextBall;
            else
                ending[nextBall] = ending[nextBall + 1];

            if (nextBall < prevBall)
            {
                if(nextBall + 1 != begining[prevBall])
                    result = false;
            }

            ending[begining[nextBall]] = ending[nextBall];
            begining[ending[nextBall]] = begining[nextBall];

            prevBall = nextBall;
        }
    }
    if (result)
        printf("Not a proof");
    else
        printf("Cheater");
    return 0;
}
