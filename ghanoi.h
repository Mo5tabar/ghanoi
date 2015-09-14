/**************************************************************
 * File: ghanoi.h 
 * Author: Sami Metoui
 * Description: ghanoi header file
 * License: GPL 3 (http://www.gnu.org/licenses/gpl.html)
 ***************************************************************/

#ifndef GHANOI_INCLUDED
#define GHANOI_INCLUDED

struct pile {
 int *tab;
 int index;
 int taille;
};

void background(void);

int pop(struct pile*);
void push(struct pile*, int);
struct pile* nouvellePile(int);
void displayPile(struct pile*, int);

void Hanoi(int, struct pile*, struct pile*, struct pile*, struct pile* t[]);
void afficherTours(struct pile* t[]);

#endif // GHANOI_INCLUDED
