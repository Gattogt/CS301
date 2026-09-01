#include <iostream>
#include <stdexcept>

using namespace std;

void Johnson_Trotter(const int n)
{

    // create 2D array
    int **directionAndArray = new int *[2];
    bool allPermutaionsSet = false;
    int biggestMobileIndex;
    int biggestMobile;
    int totalPermutations = 1;

    for (int i = 1; i < n + 1; i++)
    {
        totalPermutations *= i;
    }

    int temp; // for swaping later

    for (int i = 0; i < 2; i++)
    {
        directionAndArray[i] = new int[n];
    }

    // initialize the first row with 0s
    // 0 is left, 1 is right
    for (int i = 0; i < n; i++)
    {
        directionAndArray[0][i] = 0;
    }

    // initialize the second row with the numbers up to n
    for (int i = 0; i < n; i++)
    {
        directionAndArray[1][i] = i + 1;
    }

    cout << "There are a total of " << totalPermutations << " permutations of the set {";
    for (int i = 0; i < n - 1; i++)
    {
        cout << i + 1 << ", ";
    }
    cout << n << "}:" << endl;

    // actually start going through the permutations
    while (allPermutaionsSet == false)
    {
        // print current permutation
        for (int i = 0; i < n; i++)
        {
            cout << directionAndArray[1][i] << " ";
        }
        cout << endl;

        biggestMobileIndex = -1;
        biggestMobile = -1;
        // find the biggest mobile element
        for (int i = 0; i < n; i++)
        {
            // see if pointing left or right
            if (directionAndArray[0][i] == 0)
            {

                if (i != 0)
                {
                    if (directionAndArray[1][i] > directionAndArray[1][i - 1])
                    { // this means that the element is mobile
                        if (directionAndArray[1][i] > biggestMobile)
                        {
                            biggestMobile = directionAndArray[1][i];
                            biggestMobileIndex = i;
                        }
                    }
                }
            }
            else
            { // check if pointing to the right
                if (i != n - 1)
                {
                    if (directionAndArray[1][i] > directionAndArray[1][i + 1])
                    { // this means that the element is mobile
                        if (directionAndArray[1][i] > biggestMobile)
                        {
                            biggestMobile = directionAndArray[1][i];
                            biggestMobileIndex = i;
                        }
                    }
                }
            }
        }

        if (biggestMobileIndex == -1)
        {
            allPermutaionsSet = true;
            break;
        }

        // swapping biggest mobile item left or right
        if (directionAndArray[0][biggestMobileIndex] == 0)
        { // pointing left
            temp = directionAndArray[1][biggestMobileIndex];
            directionAndArray[1][biggestMobileIndex] = directionAndArray[1][biggestMobileIndex - 1];
            directionAndArray[1][biggestMobileIndex - 1] = temp;

            temp = directionAndArray[0][biggestMobileIndex];
            directionAndArray[0][biggestMobileIndex] = directionAndArray[0][biggestMobileIndex - 1];
            directionAndArray[0][biggestMobileIndex - 1] = temp;
        }
        else
        { // pointing right
            temp = directionAndArray[1][biggestMobileIndex];
            directionAndArray[1][biggestMobileIndex] = directionAndArray[1][biggestMobileIndex + 1];
            directionAndArray[1][biggestMobileIndex + 1] = temp;

            temp = directionAndArray[0][biggestMobileIndex];
            directionAndArray[0][biggestMobileIndex] = directionAndArray[0][biggestMobileIndex + 1];
            directionAndArray[0][biggestMobileIndex + 1] = temp;
        }

        for (int i = 0; i < n; i++)
        {
            if (directionAndArray[1][i] > biggestMobile)
            {
                if (directionAndArray[0][i] == 0)
                {
                    directionAndArray[0][i] = 1;
                }
                else
                {
                    directionAndArray[0][i] = 0;
                }
            }
        }
    }

    // delete the coloums
    for (int i = 0; i < 2; i++)
    {
        delete[] directionAndArray[i];
    }
    // delete the row
    delete[] directionAndArray;
}

int main()
{

    Johnson_Trotter(3);

    return 0;
}