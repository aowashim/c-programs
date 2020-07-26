#include <stdio.h>
#include <stdlib.h>

/*int main()
{
    FILE *ptr;
    int x, y, n, m, prd, i;
    ptr = fopen("input.txt", "r");

    if(ptr == NULL)
    {
        printf("Failed to open the input file.\n");
    }
    
    else
    {
        fscanf(ptr, "%d %d", &n, &m);
        prd = n * m;

        for(i = 1; i <= prd; i++)
        {
            fscanf(ptr, "%d %d", &x, &y);
            printf("x = %d, y = %d\n", x, y);
        }
    }

    fclose(ptr);

    return 0;
}*/
int main()
{
    int v, i, j, ** graph;
    FILE *ptr = fopen("input.txt", "r");
    
    if(ptr == NULL)
        printf("Failed to open the file.\n");

    else
    {
        fscanf(ptr, "%d", &v);
        graph = malloc(v * sizeof(int*));
        for(i = 0; i < v; i++)
            graph[i] = malloc(v * sizeof(int));

        for(i = 0; i < v; i++)
        {
            for(j = 0; j < v; j++)
                fscanf(ptr, "%d, ", &graph[i][j]);
        }

        for(i = 0; i < v; i++)
        {
            for(j = 0; j < v; j++)
                printf("%d ", graph[i][j]);
            
            printf("\n");
        }
    }
    

    return 0;
}
