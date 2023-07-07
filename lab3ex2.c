#include <stdio.h>

int main()
{
    int M, n, out, resultn, resultk, nmenusk, resultnmenusk;
    printf("Quantas linhas queres do triangulo de pascal?");
    scanf("%d", &M);
    for (int i = 0; i < M; i++)
    {
        n = i;
        for (int j = 0; j <= i; j++)
        {
            int k = j;
            int nmenusk = n - k;
             resultn = 1;
            resultk = 1;
            resultnmenusk = 1;
          for (int o = 1; o <= nmenusk; o++) {
                resultnmenusk *= o;
            }

            for (int l = 1; l <= k; l++) {
                resultk *= l;
            }

            for (int m = 1; m <= n; m++) {
                resultn *= m;
            }

            out = resultn / (resultk * resultnmenusk);

            printf("\t");
            printf("%d", out);
        }
                printf("\n");
    }
    return 0;
}