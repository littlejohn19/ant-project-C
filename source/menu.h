// plik menu.h
#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "mrowka.h"

//definicje funcji interfejsu

//tworzenie odpowiednich odestepow
void br(int ilosc);

//ustawienie koloru
void kolor(int indeks_koloru);

//ponieranie znaku
int my_scanf(int low, int high);

//wysrodkowanie napisu
void my_printf(char *slowo);

//menu interfejsowe
int menu();

#endif // MENU_H
