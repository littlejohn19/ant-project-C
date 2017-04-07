#include "menu.h"

//definicje funkcji interfejsowych

//ustawienie tekstu
void br(int ilosc)
{
    int i;
    for(i = 0; i < ilosc; i++)
        printf("\n");
}

//zmiana koloru /indeks_koloru to liczba całkowita
void kolor(int indeks_koloru)
{
    /*
      Kolorowanie skladni
        0 - czarny
        1 - niebieski
        2 - zielony
        3 - błękitny
        4 - czerwony
        5 - purpurowy
        6 - żółty
        7 - biały
        8 - szary
        9 - jasnoniebieski
        10 - jasnozielony
        11 - jasnobłękitny
        12 - jasnoczerwony
        13 - jasnopurpurowy
        14 - jasnożółty
        15 - jaskrawobiały
    */

        if((indeks_koloru < 1) && (indeks_koloru > 15))
        {
            my_printf("Wybierz kolor z dostepnych:\n\n");
            printf("Kolorowanie skladni\n0 - czarny\n1 - niebieski\n2 - zielony\n3 - błękitny\n4 - czerwony\n5 - purpurowy\n6 - żółty\n7 - biały\n8 - szary\n9 - jasnoniebieski\n10 - jasnozielony\n11 - jasnobłękitny\n12 - jasnoczerwony\n13 - jasnopurpurowy\n14 - jasnożółty\n15 - jaskrawobiały");
        }

    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , indeks_koloru );
}

//pobieranie znaku
int my_scanf(int low,int high)//podanie zakresu
{
    int temp;
    int var;

    while((temp = scanf("%d", &var) != 1) || var < low || var > high ) //dopóki nie uda się wczytać
    {
        if(temp != 1){
            printf("Liczba musi byc z przedzialu <%d:%d>. Podaj liczbe: ",low,high);
        }else{
            printf("Zly format. Podaj liczbe: ");
        }

        int c;
        while((c = getchar()) != '\n' && c != EOF); //pętla wyciągająca znaki z bufora
    }
    return var;
}
//wysrodkowanie napisu
void my_printf(char *slowo)//argument - wskaznik na pierwszy element slowa
{
    int i, j, dl_slowa;

    //zliczanie dlugosci slowa, az do napotkania znaku konca linii - '\0'
    for(j = 0; slowo[j] != '\0' ;j++);

    dl_slowa = j;
    //80 - szerokosc standardowego okienka(-1, zeby byla liczba nieparzysta)
    for(i = 0; i <  ((159 - dl_slowa) /2); i++)
            printf(" ");//wydrukowanie odpowiedniej ilosci spacji

    printf("%s\n", slowo);
}

//interfejs programu
int menu()
{
    int znak;
    int licznik = 1;
    char *menu[] = {"  Start\0", "  O programie\0", "  O autorach\0", "  Wyjscie\0", "  Tryb z pojedynczym krokiem\0", "  Tryb z zadana liczba krokow\0", "  Powrot\0"};
    char *menu_a[] = {"> Start\0", "> O programie\0", "> O autorach\0", "> Wyjscie\0", "> Tryb z pojedynczym krokiem\0", "> Tryb z zadana liczba krokow\0", "> Powrot\0"};

    //etykieta
    powrot:

    while(1)
    {
        system("cls");
        br(4);
        kolor(3);
        my_printf("*** MROWKA ***");
        kolor(7);
        br(4);
        switch (licznik)
        {
        case 1:
            kolor(9);
            my_printf(menu_a[0]);
            kolor(7);
            my_printf(menu[1]);
            my_printf(menu[2]);
            my_printf(menu[3]);
            break;
        case 2:
            my_printf(menu[0]);
            kolor(9);
            my_printf(menu_a[1]);
            kolor(7);
            my_printf(menu[2]);
            my_printf(menu[3]);
            break;
        case 3:
            my_printf(menu[0]);
            my_printf(menu[1]);
            kolor(9);
            my_printf(menu_a[2]);
            kolor(7);
            my_printf(menu[3]);
            break;
        case 4:
            my_printf(menu[0]);
            my_printf(menu[1]);
            my_printf(menu[2]);
            kolor(12);
            my_printf(menu_a[3]);
            kolor(7);
            break;
        default:
            printf("blad");
            break;
        }
        br(20);
        my_printf("v. 1.1                                 Copyright | Tarnow 2014/2015");
        znak = getch();
        if(znak == 80)
        {
            if(licznik == 4)
            {
                licznik = 4;
            }
            else
            {
                licznik++;
            }

        }

        else if(znak == 72)
        {
            if(licznik == 1)
            {
                licznik = 1;
            }
            else
            {
                licznik--;
            }
        }

        else if(znak == 13)
        {
            break;
        }
        else
        {
            continue;
        }

    }
    if(licznik == 2)
    {
        while(1)
        {
            system("cls");
            switch (licznik) {
            case 2:
                kolor(10);
                my_printf("MROWKA\n");
                kolor(7);
                my_printf("Mamy pole o rozmiarze M x N(wielkosc pola podajemy z klawiatury). Nasza tytulowa mrowka posiada kod genetyczny o danej ilosci bitow\n(dlugosc podajemy z klawiatury). Kazda komorka pole moze przyjac tyle roznych wartosci ile bitow ma kod genetyczny mrowki. Jezeli mrowka bedzie miala\n kod 3 bitowy to wartosci moze przyjac:");
                kolor(12);
                printf("001\n");
                kolor(7);
                my_printf("Jezeli mrowka stanie na jakims polu, to wartosc tego pola zwieksza sie o 1\nlub staje sie rowna 0, jesli przekroczy dlugosc kodu genetycznego mrowki.\nJesli bit kodu genetycznego na pozycji roznej wartosci pola na ktorym stoi\nmrowka jest rowny 0:");
                kolor(15);
                printf("W naszym przypadku bit na zerowej i pierwszej pozycji jest rowny 0, wiec mrowka skreca 90* w lewo, gdy wartosc pola bedzie rowna 2, a w naszym przypadku\nna drugiej pozycji jest 1, wiec mrowka skreca 90* w prawo.\nAnalogicznie dla wiekszej ilosci bitow.\n");
                printf("\nWszystkie wartosci poczatkowe tj. kod mrowki i wartosci poszczegolnych pol\nna ktore moze stanac mrowka sa generowane losowo.\n");
                br(6);
                kolor(12);
                my_printf(menu_a[6]);
                break;
            default:
                printf("blad");
                break;
            }
            znak = getch();

            if(znak == 13)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }

    else if(licznik == 3){

        while(1)
        {
            system("cls");
            switch (licznik) {
            case 3:
                kolor(10);
                my_printf("AUTORZY\n");
                printf("\n");
                my_printf("Zbyszek Kuras");
                kolor(7);
                my_printf("Zapalony koder i webmaster. Postawil pierwsza funkcje w naszym projekcie.");
                printf("\n");
                kolor(10);
                my_printf("Michal Kulig");
                kolor(7);
                my_printf("Wielbiciej muzyki, koduje w wolnym czasie. Poztywna postac w naszym team'ie.");
                printf("\n");
                kolor(10);
                my_printf("Darek Piwko");
                kolor(7);
                my_printf("Amator koszykowki i wysokich dziewczyn. Poplynal podczas pisania projektu.");
                br(7);
                kolor(12);
                my_printf(menu_a[6]);
                break;
            default:
                printf("blad");
                break;
            }
            znak = getch();

            if(znak == 13)
            {
                break;
            }
            else
            {
                continue;
            }
        }

    }

    else if(licznik == 1)
    {
        licznik = 5;
        while(1)
        {
            system("cls");
            br(4);
            kolor(3);
            my_printf("*** MROWKA ***");
            kolor(7);
            br(4);
            switch (licznik)
            {
            case 5:
                kolor(9);
                my_printf(menu_a[4]);
                kolor(7);
                my_printf(menu[5]);
                my_printf(menu[6]);
                break;
            case 6:
                my_printf(menu[4]);
                kolor(9);
                my_printf(menu_a[5]);
                kolor(7);
                my_printf(menu[6]);
                break;
            case 7:
                my_printf(menu[4]);
                my_printf(menu[5]);
                kolor(12);
                my_printf(menu_a[6]);
                kolor(7);
                break;

            default:
                printf("blad");
                break;
            }
            br(21);
            my_printf("v. 1.1                                 Copyright | Tarnow 2014/2015");

            znak = getch();

            if(znak == 80)
            {
                if(licznik == 7)
                {
                    licznik = 7;
                }
                else
                {
                    licznik++;
                }

            }

            else if(znak == 72)
            {
                if(licznik == 5)
                {
                    licznik = 5;
                }
                else
                {
                    licznik--;
                }
            }

            else if(znak == 13)
            {
                break;
            }

            else
            {
                continue;
            }
        }
    }

    if(licznik == 5)//jest wybrana opcja w pojedynczym krokiem
    {
        system("cls");
        return 1;
    }
    if(licznik == 6)//jesli wybrana opcja w zadana iloscia krokow
    {
        system("cls");
        return 2;
    }


    if(licznik == 7)//jesli wybrany powrot w podmenu
    {
        licznik = 1;
        //powrot do poczatku funkcji
        goto powrot;
    }

    if(licznik == 4)//jesli wybrane wyjscie
    {
         return 0;
    }

    //powrot do poczatku funckcji
    goto powrot;
}
