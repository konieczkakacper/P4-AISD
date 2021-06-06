#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//-------------------------Generowanie grafu z cyklem hamiltona i eulera-----------------------------

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


void generateHamiltonEuler(int n, int** G, double b)
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
    for(int j = 0; j < n; j++)                      //wypełniamy tablicę liczbami od 0 do n-1 (to są nasze wierzchołki)
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


    int k,l,m;
    double ds = (b * n * (n - 1)) / 2;
    int edges = n;
    while (edges < ds) {
        do
        {                           //szukamy trzech wierzchołków pomiędzy którymi nie ma krawędzi...
            k = Random(0, n);
            l = Random(0, n);
            m = Random(0, n);

        } while(G[k][l] == 1 || G[l][m] == 1 || G[k][m] == 1 || k == m || l == m || l == k);

        G[k][l] = 1;                //...i tworzymy między nimi krawędzie
        G[l][k] = 1;
        G[l][m] = 1;
        G[m][l] = 1;
        G[k][m] = 1;
        G[m][k] = 1;
        edges += 3;
    }
}





//-----------------------------algorytm Fleury'ego--------------------------------------------
/*

void DFSVisit(int** G, int i, int n, int* colours, int* vertexCount)                  //colours: 0 = white, 1 = grey, 2 = black
{
    colours[i] = 1;                                 //grey
    for (int j = 0; j < n; j++)
    {
        if (colours[j] == 0 && G[i][j]==1)          //jeśli sąsiad jest biały i sąsiad rzeczywiscie jest sąsiadem (ma połączenie z obecnym wierzchołkiem)...
        {
            DFSVisit(G, j, n, colours, vertexCount);
        }
    }
    colours[i] = 2;                                 //black
    ++vertexCount;
}

int DFS(int** G, int n)                //DFS - wersja zliczająca ilość odwiedzonych wierzchołków i zwracająca tę ilość
{
    int vertexCount = 0;

    int* colours = calloc(sizeof(*colours), n);     //(wersja c++: new int[n];)
    for (int i = 0; i < n; i++)
    {
        colours[i] = 0;             //white - kolorujemy każdy wierzcohłek na biało
    }
    for (int i = 0; i < n; i++)
    {
        if (colours[i] == 0)
        {
            DFSVisit(G, i, n, colours, &vertexCount);
        }
    }

    return vertexCount;
}


bool isBridge(int** G, int u, int v, int n)         //u i v to wierzchołki połączone krawędzią. Funkcja zwróci true jeśli krawędź (u,v) jest mostem
{
    if(G[u][v] == 1)                                //jeśli wgl istnieje krawędź (u,v)
    {
        int a = DFS(G, n);                              //sprawdzamy ile wierzchołków przeszliśmy
        G[u][v] = 0;                                    //usuwamy tymczasowo krawędź (u,v)
        G[v][u] = 0;
        int b = DFS(G, n);                              //sprawdzamy czy po usunięciu tej krawędzi przeszliśmy mniej wierzchołków czy tyle samo
        G[u][v] = 1;
        G[v][u] = 1;

        if(a != b)                                      //jak mniej to znaczy ze to był most
            return true;
        else
            return false;
    }

    return false;                               //krawędź nie jest mostem bo wgl nie ma takiej krawędzi (G[u][v] == 0)
}


void Fleury()
{

}





//----------------------------------------algorytm Hierholzera------------------------------------

void push(int *stack, int *topOfStack, int x)
{
    stack[*topOfStack] = x;
    topOfStack++;
}

int pop(int *stack, int *topOfStack)
{
    topOfStack--;
    return stack[*topOfStack];
}

bool stackIsEmpty(int *topOfStack)
{
    if(*topOfStack == 0)
        return true;
    return false;
}


void Hierholzer(int **G, int n)
{

    int *array = calloc(sizeof(*array), n);         //alokujemy tablicę o rozmiarze n

    for(int j = 0; j < n; j++)                      //wypełniamy tablicę liczbami od 0 do n-1 (to są nasze wierzchołki)
    {
        array[j] = j;
    }

    int *stack = calloc(sizeof(*stack), n);
    int topOfStack = 0;
    int temp = 0;

    push(stack, &topOfStack, array[0]);         //dodanie na stos pierwszego wierzchołka z tablicy wierzchołków


    do                                              //YYY no przy tej pętli sie zawiesiłem xdd
    {
        int u = stack[topOfStack - 1];
        int v;

        for(int i = 0; i < n; i++)
        {
            v = i;
            if(G[u][v] == 1)
            {
                G[u][v] = 0;
                G[v][u] = 0;
                push(stack, &topOfStack, v);
                u = v;
            }
        }


    }while(!stackIsEmpty(&topOfStack));







    }








*/













int ns[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};         //liczby wierzchołków
double bs[] = {0.125, 0.250, 0.375, 0.500, 0.625, 0.750, 0.875};      //gestosc grafu ale chyba nie jest tu potrzebna


int main()
{
    for(int k = 0; k < sizeof(ns) / sizeof(*ns); k++)
    {
        for(int j = 0; j < sizeof(bs) / sizeof(*bs); j++)
        {
            int n = ns[k];
            double b = bs[j];
            int** G = calloc(n, sizeof(int*));

            for(int i = 0; i < n; ++i)
            {
                G[i] = calloc(n, sizeof(int));
            }

            clock_t begin = clock();
            generateHamiltonEuler(n, G, b);
            clock_t end = clock();

            double seconds = (double) (end - begin) / (double) CLOCKS_PER_SEC;

            printf("generateHamiltonEuler \t n = %d \t b = %lf \t time = %lf \n", n, b, seconds);

            for (int i = 0; i < n; i++) {
                free(G[i]);
            }
            free(G);
        }


    }

    return 0;


}