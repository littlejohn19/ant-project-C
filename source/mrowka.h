// plik mrowka.h
#ifndef MROWKA_H
#define MROWKA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#define N 24 //strzalka do gory
#define S 25 //strzalka w dol
#define E 26 //strzalka w prawo
#define W 27 //strzalka w lewo

//denifnicja struktury

//struktura mrowki
struct ant
{
  int il_bit; //dlugosc kodu genetycznego
  int *dna_tab; // tablica przechowujaca kod genetyczny mrowki
  int zwrot; // aktualny zwrot, w ktory mrowka jest skierowana
};


//definicje funckji


// funkcja alokujaca pamiec tablicy przechowujacej kod genetyczny mrowki
int *create_code(int size);

//funkcja zwalniania pamieci tablicy przechowujacej kod genetyczny mrowki
void free_memory_code(int *tab);

//alokacja pamieci do tablicy przechowujacej wartosci pola po ktorym porusza sie mrowka
int **create_field(int n, int m);

//zwolnienie pamieci tablicy przechowujacej wartosi pola
void free_memory(int **tab , int m);

//funkcja generujaca losowe/poczatkowe wartosci kodu genetycznego mrowki, jej zwrotu oraz wspolrzedne
struct ant create(struct ant mrowka, int n, int m, int *indeks_i, int *indeks_j);

//zmiana wartosci odwiedzonego pola
void change_value(int **tab, int i, int j, int k);

// wypelnienie tablicy
void fill(int **tab ,int n, int m, int k);

//wyswietlanie aktualnych wartosci tablicy liczbowej
void show(int **tab, int n, int m, int i_c, int j_c);

//wyswietlanie aktyalnych znakow tablicy znakowej
void show_path(int **tab, int n, int m, int i_c, int j_c);

//glowna funkcja wyznaczajaca kierunek ruchu mrowki
void path(struct ant mrowka, int **znak, int **tab, int i, int j, int n, int m, int ilosc_krokow, int tryb, int w_kroki);

#endif // MROWKA_H
