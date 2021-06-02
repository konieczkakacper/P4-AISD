#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int ns[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
double bs[] = {0.125, 0.250, 0.375, 0.500, 0.625, 0.750, 0.875};



int Random(int x, int y)
{
    int z = x + rand() % (y - x);
    return z;
}

void shuffle(int *A, int n)
{
    for(int i = n - 1; i > 0; i--)
    {
        int j = rand() % i;
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
}


void generateHamiltonEuler(int n, double b, int** G)
{
    for (int u = 0; u < n; u++)                          //te dwa fory: stworzenie n wierzchołków...
    {
        for (int i = 0; i < n; i++)
        {
            G[u][i] = 0;                                //...bez połączeń - macierz sąsiedztwa wypełniona zerami
        }
    }

    int u, v;

    int *array = calloc(sizeof(*array), n);         //alokujemy tablicę o rozmiarze n
    for(int j = 0; j < n; j++)                      //wypełniamy tablicę liczbami od 0 do n (to są nasze wierzchołki)
    {
        array[j] = j;
    }

    shuffle(array, n);                             //shufflujemy wierzchołki

    for(int i = 0; i < n; i++)
    {
        if(i == n - 1)                              //jeśli dochodzimy do ostatniej iteracji (budujemy ostatnią krawędź) to łączymy ostatni wierzchołek z tablicy z pierwszym wierzchołkiem tablicy (indek 0). "Łączymy koniec z początkiem" aby był to cykl
        {
            u = array[i];
            v = array[0];
        }
        else                                    //tworzymy krawędzie po kolei, między następującymi po sobie w wymieszanej tablicy wierzchołkami. Dzięki temu mamy pewność, że każdy wierzchołek odwiedzimy tylko raz (będzie drugiego stopnia)
        {
            u = array[i];
            v = array[i + 1];
        }

        G[u][v] = 1;
        G[v][u] = 1;
    }

                //na tym etapie mamy już cykl hamiltona


    int k, l, m;

    do
    {                           //szukamy trzech wierzchołków pomiędzy którymi nie ma krawędzi...
        k = Random(0, n);
        l = Random(0, l);
        m = Random(0, m);

    }while(G[k][l] == 1 || G[l][m] == 1 || G[k][m] == 1);

    G[k][l] = 1;                //...i tworzymy między nimi krawędzie
    G[l][m] = 1;
    G[k][m] = 1;
}



























int main()
{

return 0;


}
