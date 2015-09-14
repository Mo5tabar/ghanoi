/*********************************************************************
 * Program: gphanoi.c
 * Autthr : Sami Metoui
 * Description: display the issue of hanoi towers for an undefined 
 * number of disks.
 * License: GPL 3 (http://www.gnu.org/licenses/gpl.html)
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "ghanoi.h"

#define HT 5

int count = 0;

/***********************
 * MAIN 
 ***********************/

int main() {

 struct pile* tourDep = nouvellePile(HT);
 struct pile* tourArr = nouvellePile(HT);
 struct pile* tourInter = nouvellePile(HT);
 struct pile * t[3];
 int i;
 char tab[6];

 t[0] = tourDep;
 t[1] = tourInter;
 t[2] = tourArr;

 if (allegro_init() != 0) {
  allegro_message("error: %s", allegro_error); //Init Allegro
  return -1;
 }

 install_keyboard(); //install the keyboard handler

 install_mouse(); //install mouse

 set_color_depth(16);

 set_gfx_mode(GFX_SAFE, 640, 480, 0, 0);

 clear_bitmap(screen);
 background();

 for (i = HT; i > 0; i--) push(tourDep, i);

 afficherTours(t);

 Hanoi(HT, tourDep, tourArr, tourInter, t);

 sprintf(tab, "%i", count);
 textout_ex(screen, font, tab, SCREEN_W / 2, SCREEN_H / 3 * 2 + 40, makecol(0, 255, 0), -1);

 textout_ex(screen, font, "Press esc to exit.", 0, SCREEN_H - 10, makecol(0, 255, 0), -1);

 while (!key[KEY_ESC]) {
  poll_keyboard();
 }

 allegro_exit();

 return 1;

}
END_OF_MAIN();

/********************************************************
 * Function that display towers after each disk move 
 * déplacement de disque 
 * input : pointers array on stacks 
 ********************************************************/

void afficherTours(struct pile* t[]) {

 char tab[6];
 clear_bitmap(screen);
 background();

 displayPile(t[0], 1);
 displayPile(t[1], 2);
 displayPile(t[2], 3);

 sprintf(tab, "%i", count);
 textout_ex(screen, font, tab, SCREEN_W / 2, SCREEN_H / 3 * 2 + 40, makecol(0, 255, 0), -1);
 usleep(900000);
 usleep(600000);
 textout_ex(screen, font, tab, SCREEN_W / 2, SCREEN_H / 3 * 2 + 40, makecol(0, 0, 0), -1);
 count++;

}

/*************************************************************
 * Fonction Hanoi, that move disks from tower 1 to tower 3
 * using tower 2.
 * Input: maximum height of tower
 *        starting stack (tower), middle tower, arrival tower 
 *        pointers array on stacks             
 *************************************************************/

void Hanoi(int tail, struct pile* dep, struct pile* arriv, struct pile* inter, struct pile* t[]) {
 int disc;
 if (tail == 1) {
  disc = pop(dep);
  push(arriv, disc);
  afficherTours(t);
 } else {
  Hanoi(tail - 1, dep, inter, arriv, t);

  disc = pop(dep);
  push(arriv, disc);
  afficherTours(t);

  Hanoi(tail - 1, inter, arriv, dep, t);
 }

}

/************************************************
 * Function that crate a sized stack 
 * Input : stack size
 ************************************************/
struct pile* nouvellePile(int t) {
 struct pile* p;

 p = malloc(sizeof (struct pile));
 p->tab = malloc(sizeof (int)*t);
 p->index = 0;
 p->taille = t;
 return p;
}

/*****************************************************
 * Function that pop an integer from stack
 * Input : stack pointer
 * Output : returned integer
 *****************************************************/
int pop(struct pile* p) {
 if (p->index == 0) {
 }//printf("Stack is empty!\n");
 else {
  p->index--;
  return (p->tab[p->index]);
 }
 return (0);
}

/*****************************************************
 * Function that push an integer in the stack
 * Input : stack size
 *****************************************************/
void push(struct pile* p, int e) {
 if (p->index == p->taille) {
 }//printf("Stack is full!\n");
 else {
  p->tab[p->index] = e;
  p->index++;
 }
}

/*************************************************
 * Function that display the content of the stack
 * Input : stack pointer
 *************************************************/
void displayPile(struct pile* p, int pos) {
 int i, j;
 for (i = 0; i < p->index; i++) {
  for (j = 0; j < 5; j++) line(screen, pos * SCREEN_W / 4 - (p->tab[i]*5), SCREEN_H / 3 * 2 - i * 10 + j,
          pos * SCREEN_W / 4 + (p->tab[i]*5),
          SCREEN_H / 3 * 2 - i * 10 + j, makecol(100, 0, 100));
 }

 for (j = 0; j < 5; j++) line(screen, pos * SCREEN_W / 4 - (p->tab[i]*5), SCREEN_H / 3 * 2 - i * 10 + j,
         pos * SCREEN_W / 4 + (p->tab[i]*5),
         SCREEN_H / 3 * 2 - i * 10 + j, makecol(0, 0, 0));

 for (j = 0; j < 5; j++) line(screen, pos * SCREEN_W / 4, SCREEN_H / 3 * 2 - i * 10 + j, pos * SCREEN_W / 4,
         SCREEN_H / 3 * 2 - i * 10 + j, makecol(100, 100, 100));

}

/*****************************************************
 * Function that init the screen
 *****************************************************/
void background(void) {
 line(screen, SCREEN_W / 4, SCREEN_H / 3, SCREEN_W / 4, (SCREEN_H / 3)*2, makecol(100, 100, 100));
 line(screen, (SCREEN_W / 4)*2, SCREEN_H / 3, (SCREEN_W / 4)*2, SCREEN_H / 3 * 2, makecol(100, 100, 100));
 line(screen, (SCREEN_W / 4)*3, SCREEN_H / 3, (SCREEN_W / 4)*3, SCREEN_H / 3 * 2, makecol(100, 100, 100));

 textout_ex(screen, font, "TOWER1               TOWER2               TOWER3", SCREEN_W / 4 - 20, SCREEN_H / 3 * 2 + 20,
         makecol(0, 0, 255), -1);
}

