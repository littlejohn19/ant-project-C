#include "mrowka.h"
#include "menu.h"

// funkcja alokujaca pamiec tablicy przechowujacej kod genetyczny mrowki
int *create_code(int size)
{
    int *tab;

    //alokacja pamieci
    tab = (int *)malloc(size * sizeof(int*));

    //sprawdzenie powodzenia alokacji
    if(tab == NULL)
    {
        printf("Nie mozna przydzielic pamieci!\n");
        return NULL;
    }
    return tab;
}

//funkcja zwalniania pamieci tablicy przechowujacej kod genetyczny mrowki
void free_memory_code(int *tab)
{
    free(tab);
}

//alokacja pamieci do tablicy przechowujacej wartosci pola po ktorym porusza sie mrowka
int **create_field(int n, int m)
{
    int i;
    int **tab;

    //alokacja pamieci
    tab = (int **)malloc(m * sizeof(int*));
    if(tab == NULL)//sprawdzenie powodzenia alokacji
    {
       printf("Nie mozna przydzielic pamieci!\n");
       return NULL;//jesli nie udalo sie zaalokowac
    }

    else//gdy alokacja przechodzi bez problemow
    {
        for (i = 0; i < m; i++)
        {
          //alokacja(i sprawdzenie) elementow tablicy
          tab[i] = (int *)malloc(n * sizeof(int));
          if(tab[i] == NULL)
          {
             printf("Nie mozna przydzielic pamieci!\n");
             return  NULL;// jesli sie nie udalo
          }
        }
    }

    return tab;
}

//zwolnienie pamieci tablicy przechowujacej wartosi pola
void free_memory(int **tab , int m)
{
    int i;
    for (i = 0; i < m; i++)
    {
      free(tab[i]);
    }
    free(tab);
}

//funkcja generujaca losowe/poczatkowe wartosci kodu genetycznego mrowki, jej zwrotu oraz wspolrzedne
struct ant create(struct ant mrowka, int n, int m, int *indeks_i, int *indeks_j)
{
    int i, size = mrowka.il_bit;//rozmiar kodu genetycznego mrowki
    struct ant c = mrowka;
    int zwrot[4] = {N, S, E, W};//24 - /\, 25 - \/, 26 - ->, 27 - <-


    srand( time( 0 ) );//inicjacja generatora liczb pseudolosowych aktualnym czasem,
    //dzięki czemu przy uruchomieniu programu w różnym czasie sprawi,
    //że funkcja 'rand' będzie dawała różne wartości pseudolosowe.

    *indeks_j = rand()%n;//wylosowanie wspolrzednej y
    *indeks_i = rand()%m;//wylosowanie wspolrzednej x

    c.dna_tab = create_code(size);

    for (i = 0; i < size; i++)
    {
         c.dna_tab[i]=(rand()%2);//ustalanie kodu mrowki
    }

    //wykluczenie dwoch zer/dwoch jedynek przy dwubitowym kodzie
    if(size == 2)
    {
        if(((c.dna_tab[0]) == 0) && ((c.dna_tab[1] == 0)))
        {
            c.dna_tab[rand()%2] = 1;
        }
        else if(((c.dna_tab[0]) == 1) && ((c.dna_tab[1] == 1)))//wykluczenie pesymistycznego losowania przy 2 bitach kodu
        {
            c.dna_tab[rand()%2] = 0;
        }
    }


    c.zwrot = zwrot[(rand()%4)];//wylosowanie poczatkowego zwrotu

    return c;
}

//zmiana wartosci odwiedzonego pola
void change_value(int **tab, int i, int j, int k)
{
    //wyzerowanie gdy pole rowne dlugosci kodu
    if(((tab[i][j]) == (k-1)))
    {
        tab[i][j] = 0;
    }
    else//zwiekszenie wartosci pola
    {
        tab[i][j] += 1;
    }

}

// wypelnienie tablicy
void fill(int **tab ,int n, int m, int k)
{
    int i,j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
           tab[i][j] = rand()%k;
        }
    }

}
//wyswietlanie aktualnych wartosci tablicy liczbowej
void show(int **tab, int n, int m, int i_c, int j_c)
{
    int i,j;

    for (i = 0; i < m; i++)
    {
        printf("|");
        for(j = 0; j < n; j++)
        {
            if((i == i_c) && (j == j_c))
            {
                kolor(9);
                printf("%2d ", tab[i][j]);
                kolor(7);
            }
            else
                printf("%2d ", tab[i][j]);
        }
        printf("|\n");
    }
}

//wyswietlanie aktualnych znakow tablicy znakowej
void show_path(int **tab, int n, int m, int i_c, int j_c)
{
    int i,j;

    for (i = 0; i < m; i++)
    {
        printf("|");
        for(j = 0; j < n; j++)
        {
            if((i == i_c) && (j == j_c))
            {
                kolor(13);
                printf("%2c ", tab[i][j]);
                kolor(7);
            }
            else
                printf("%2c ", tab[i][j]);
        }
        printf("|\n");
    }
}

//glowna funkcja wyznaczajaca kierunek ruchu mrowki, zwiekszajaca wartosc pol oraz rysujaca sciezke
void path(struct ant mrowka, int **znak, int **tab, int i, int j, int n, int m, int ilosc_krokow, int tryb, int w_kroki)
{
    struct ant c = mrowka;
    int i_new, j_new, znak_;
    int k = c.il_bit;

    i_new = i;
    j_new = j;

    znak[i_new][j_new] = 15;
    zonk:
    printf("Aktualne wspolrzedne: %d  %d\n", i_new, j_new);
    printf("Kod genetyczny mrowki: ");
    for(i = 0 ; i < c.il_bit; i++)
    {
        printf("%d",c.dna_tab[i]);
    }
    printf("\n");
    printf("Aktualny zwrot: %c", c.zwrot);
    printf("\n");


    show(tab,n,m,i_new,j_new);
    printf("\n");
    show_path(znak,n,m,i_new,j_new);


    if(tryb == 1)//tryb pojedynczego kroku
    {
        kolor(9);
        my_printf("ENTER - nastepny krok\n");
        kolor(12);
        my_printf("ESC - wyjscie");
        kolor(7);

        znak_ = getch();
        if(znak_ == 13)
        {
            w_kroki++;
        }
        else if(znak_ == 27)
        {
            printf("Mrowka wykonala %d krokow", w_kroki);
            sleep(3);
            return;
        }
        else if((znak_ != 13) && (znak_ != 27))
        {
            system("cls");
            goto zonk;
        }

    }
    else if(tryb == 2)//tryb zadanej ilosci krokow
    {
        if(ilosc_krokow == 0)//po wykonaniu zadanej ilosci krokow
        {
            kolor(12);
            my_printf("> Powrot");
            kolor(7);
            getchar();
            return;
        }
        printf("Pozostalo krokow: %d\n", ilosc_krokow);
        sleep(1);
        //dekrementacja ilosci krokow
        ilosc_krokow--;
    }
    system("cls");
    switch(c.zwrot)
    {

    case N://jezeli mrowka ma zwrot na polnoc
        //skret w lewo o 90*
        if((c.dna_tab[tab[i_new][j_new]]) == 0)
        {
            change_value(tab, i_new, j_new, k);
            if(j_new == 0)
            {
                znak[i_new][j_new] = W;
                j_new = (n - 1);
            }
            else
            {
                znak[i_new][j_new] = W;
                j_new -= 1;
            }

            c.zwrot = W;

        }
        //skret w prawo o 90*
        else if((c.dna_tab[tab[i_new][j_new]]) == 1)
        {
            change_value(tab, i_new, j_new, k);
            if(j_new == (n - 1))
            {
                znak[i_new][j_new] = E;
                j_new = 0;
            }
            else
            {
                znak[i_new][j_new] = E;
                j_new += 1;
            }

            c.zwrot = E;
        }
        break;

    case E://jezeli mrowka ma zwrot na wschod
        //skret w lewo
        if((c.dna_tab[tab[i_new][j_new]]) == 0)
        {
            change_value(tab, i_new, j_new, k);
            if(i_new == 0)
            {
                znak[i_new][j_new] = N;
                i_new = (m - 1);
            }
            else
            {
                znak[i_new][j_new] = N;
                i_new -= 1;
            }

            c.zwrot = N;
        }
        //skret w prawo
        else if((c.dna_tab[tab[i_new][j_new]]) == 1)
        {
            change_value(tab, i_new, j_new, k);
            if(i_new == (m - 1))
            {
                znak[i_new][j_new] = S;
                i_new = 0;
            }
            else
            {
                znak[i_new][j_new] = S;
                i_new += 1;
            }

            c.zwrot = S;
        }
        break;

    case S://jezeli mrowka ma zwrot na poludnie
        //skret w lewo o 90*
        if((c.dna_tab[tab[i_new][j_new]]) == 0)
        {
            change_value(tab, i_new, j_new, k);
            if(j_new == (n - 1))
            {
                znak[i_new][j_new] = E;
                j_new = 0;
            }
            else
            {
                znak[i_new][j_new] = E;
                j_new += 1;
            }

            c.zwrot = E;
        }
        //skret w prawo 90*
        else if((c.dna_tab[tab[i_new][j_new]]) == 1)
        {
            change_value(tab, i_new, j_new, k);
            if(j_new == 0)
            {
                znak[i_new][j_new] = W;
                j_new = (n - 1);
            }
            else
            {
                znak[i_new][j_new] = W;
                j_new -= 1;
            }

            c.zwrot = W;
        }
        break;

    case W://jezeli mrowka ma zwrot na zachod
        //skret w lewo o 90*
        if((c.dna_tab[tab[i_new][j_new]]) == 0)
        {
            change_value(tab, i_new, j_new, k);
            if(i_new == (m - 1))
            {
                znak[i_new][j_new] = S;
                i_new = 0;
            }
            else
            {
                znak[i_new][j_new] = S;
                i_new += 1;
            }

            c.zwrot = S;
        }
        //skret w prawo o 90*
        else if((c.dna_tab[tab[i_new][j_new]]) == 1)
        {
            change_value(tab, i_new, j_new, k);
            if(i_new == 0)
            {
                znak[i_new][j_new] = N;
                i_new = (m - 1);
            }
            else
            {
                znak[i_new][j_new] = N;
                i_new -= 1;
            }

            c.zwrot = N;
        }
        break;
    }

    //rekurencyjne wywolanie funkcji z aktualnymi wartosciami
    return path(c, znak,tab,i_new,j_new,n,m,ilosc_krokow,tryb,w_kroki);
}
