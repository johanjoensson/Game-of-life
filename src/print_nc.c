#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "congame.h"

unsigned int height, width;

WINDOW *win;

void init_screen(dimension dim)
{
        initscr();
        start_color();
        noecho();

        getmaxyx(stdscr, height, width);

        if(dim.horizontal > width || dim.vertical > height){
                fprintf(stderr, "Dimension of world larger than window!\n");
                endwin();
                assert(0);
        } 

        win = newwin(dim.vertical, dim.horizontal, 0, 0);
        wborder(win, '*', '*', '|', '|',  '/', '\\', '\\', '/');

        wrefresh(win);
        return;
}

void exit_screen()
{
        endwin();
        return;
}

void print_world(cell_list **world, dimension dim)
{
        cell_list *curr = *world;
        for(unsigned int j = 0; j < dim.vertical; j++){
                for(unsigned int i = 0; i < dim.horizontal; i++){
                        if(curr != NULL){
                                if( i == curr->x && j ==  curr->y){
                                        mvwaddch(win, j, i, '@');
                                        curr = curr->next;
                                } else {
                                        mvwaddch(win, j, i, '0');
                                }
                        } else {
                                mvwaddch(win, j, i, '0');
                        } 
                }
        }

        return;
}

