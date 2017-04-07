// plik main.c

#include "menu.h"
#include "mrowka.h"


int main()
{
    system("mode 160,160");

    int tryb;
    main:
    tryb = menu();

    if(tryb == 0)//jezeli z menu wybrane wyjscie
    {
        return 0;
    }

    int i_start, j_start;
    int **tab, **znak;
    struct ant mruf;
    int n,m,k,il;
    int q,q1;

    printf("podaj wielkosc pola: NxM\noraz kod genetyczny mrowki\n");
    printf("Nacisnij enter...");
    getchar();
    printf("Podaj N = ");

    n = my_scanf(0,50);
    printf("Podaj M = ");
    m = my_scanf(0,50);

    printf("Podaj dlugosc kodu genetycznego mrowki: ");
    k = my_scanf(0,100);

    mruf.il_bit=k;
    mruf = create(mruf, n,m, &i_start, &j_start);
    tab = create_field(n,m);
    znak = create_field(n,m);
    for(q = 0; q < m; q++)
    {
        for(q1 = 0; q1 < n; q1++)
        {
            znak[q][q1] = 32;
        }

    }
    fill(tab,n,m,k);
    //struktura, tablica, wspolrzedne:x,y, il bitow, rozmiar tablicy: n,m, ilosc krokow

    if(tryb == 1)
    {
        il = 0;
        printf("Nacisnij enter, aby kontynuowac");
        getchar();
        getchar();
        system("cls");
        path(mruf, znak,tab,i_start,j_start,n,m,il,tryb,0);
    }
    else if(tryb == 2)
    {
        printf("Podaj ilosc krokow: ");
        il = my_scanf(0,9999);
        printf("Nacisnij enter, aby kontynuowac");
        getchar();
        getchar();
        system("cls");
        path(mruf, znak,tab,i_start,j_start,n,m,il,tryb,0);
    }

    free_memory(tab,m);
    free_memory(znak,m);
    free_memory_code(mruf.dna_tab);
    system("cls");
    if(tryb != 4)
    {
        goto main;
    }
    printf("koniec");
    getchar();
    return 0;
}
