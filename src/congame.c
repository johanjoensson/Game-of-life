/******************************************************************************
 * Conway's game of life, B3/S23                                              *
 *                                                                            *
 * Date: 31 - 10 - 12                                                         *
 * Author: Johan Jönsson                                                      *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "congame.h"

#define WIDTH 45
#define HEIGHT 45

#define FREQUENCY 70

cell_list** init_world(dimension dim)
{
        unsigned int horizontal, vertical;

        horizontal = (dim.horizontal <= 0) ? WIDTH : dim.horizontal;
        vertical = (dim.vertical <= 0) ? HEIGHT : dim.vertical;

        cell_list *sentinel = malloc(sizeof(cell_list));
        cell_list *curr = sentinel;
        cell_list *next;

        srand( time( NULL ) );
        int count = 0;
        for(unsigned int j = 0; j < vertical; j++){
                for(unsigned int i = 0; i < horizontal; i++){
                        if((rand() % 100) < 30){
                                next = malloc(sizeof(cell_list));
                                next->x = i; 
                                next->y = j;
                                curr->next = next;
                                curr = curr->next;
                                count++;
                        }
                }
        }

        cell_list **world = &sentinel->next;
        free(sentinel);

        return world;
}

void print_plane(dimension dim, int plane[dim.vertical][dim.horizontal]){
        for(unsigned int j = 0; j < dim.vertical; j++){
                for(unsigned int i = 0; i < dim.horizontal; i++){
                        printf("%d", plane[j][i]);
                }
                printf("\n");
        }
        printf("\n");

        return;
}

void init_plane(dimension dim, int plane[dim.vertical][dim.horizontal])
{
        for(unsigned int i = 0; i < dim.vertical; i++){
                for(unsigned int j=0; j < dim.horizontal; j++){
                        plane[i][j] = 0;
                }
        }

        return;
}

void find_neighbours(cell_list **world, dimension dim, int plane[dim.vertical][dim.horizontal])
{
        cell_list *curr = *world;

        while(curr != NULL){

                // Upper Left corner
                if((curr->x == 0) && (curr->y == 0)){      
                        plane[curr->y + 1][curr->x]++; 
                        plane[curr->y][curr->x + 1]++;
                        plane[curr->y + 1][curr->x + 1]++;
                // Upper right corner
                }else if((curr->y == 0) && (curr->x == dim.horizontal - 1)){
                        plane[curr->y][curr->x - 1]++;
                        plane[curr->y + 1][curr->x]++; 
                        plane[curr->y + 1][curr->x - 1]++;
                // Lower left corner
                }else if((curr->x == 0) && (curr->y == dim.vertical - 1)){
                        plane[curr->y][curr->x + 1]++;
                        plane[curr->y - 1][curr->x]++; 
                        plane[curr->y - 1][curr->x + 1]++;
                // Lower right corner
                }else if((curr->x == dim.horizontal - 1) && (curr->y == dim.vertical -1)){
                        plane[curr->y][curr->x - 1]++;
                        plane[curr->y - 1][curr->x]++; 
                        plane[curr->y - 1][curr->x - 1]++;
                // Top row, no corners
                }else if(curr->y == 0){
                        plane[curr->y][curr->x - 1]++;
                        plane[curr->y][curr->x + 1]++;
                        plane[curr->y + 1][curr->x]++;
                        plane[curr->y + 1][curr->x - 1]++;
                        plane[curr->y + 1][curr->x + 1]++;
                // Bottom row, no corners
                }else if(curr->y == dim.vertical - 1){
                        plane[curr->y][curr->x - 1]++;
                        plane[curr->y][curr->x + 1]++;
                        plane[curr->y - 1][curr->x]++;
                        plane[curr->y - 1][curr->x - 1]++;
                        plane[curr->y - 1][curr->x + 1]++;
                // Leftmost row, no corners
                }else if(curr->x == 0){
                        plane[curr->y - 1][curr->x]++;
                        plane[curr->y + 1][curr->x]++;
                        plane[curr->y][curr->x + 1]++;
                        plane[curr->y - 1][curr->x + 1]++;
                        plane[curr->y + 1][curr->x + 1]++;
                // Rightmost row, no corners
                }else if(curr->x == dim.horizontal - 1){
                        plane[curr->y - 1][curr->x]++;
                        plane[curr->y + 1][curr->x]++;
                        plane[curr->y - 1][curr->x - 1]++;
                        plane[curr->y][curr->x - 1]++;
                        plane[curr->y + 1][curr->x - 1]++;
                // All other cells
                } else {
                        plane[curr->y - 1][curr->x - 1]++;
                        plane[curr->y][curr->x - 1]++;
                        plane[curr->y + 1][curr->x - 1]++;
                        plane[curr->y - 1][curr->x]++;
                        plane[curr->y + 1 ][curr->x]++;
                        plane[curr->y - 1][curr->x + 1]++;
                        plane[curr->y][curr->x + 1]++;
                        plane[curr->y + 1][curr->x + 1]++;
                }
                curr = curr->next;
        }
        return;
}

void set_live_cells(cell_list **world, dimension dim, int plane[dim.vertical][dim.horizontal])
{
        cell_list *sentinel = malloc(sizeof(cell_list));

        sentinel->next = *world;

        cell_list *curr = *world;
        cell_list *next = curr->next;
        cell_list *prev = sentinel;
        cell_list *new, *tmp;

                for(unsigned int j = 0; j < dim.vertical; j++){
                        for(unsigned int i = 0; i < dim.horizontal; i++){
                                if(curr != NULL){
                                        /**************************************
                                         * We found a live cell               *
                                         *************************************/
                                        if(i == curr->x && j == curr->y){
                                                /******************************
                                                 * kill it? fire is optional  *
                                                 *****************************/
                                                if(!(plane[j][i] == 2 || plane[j][i] == 3)){
                                                        tmp = curr;

                                                        prev->next = next;
                                                        curr = next;
                                                        if(curr != NULL){
                                                                next = curr->next;
                                                        }

                                                        free(tmp);
                                                }else{
                                                        prev = curr;
                                                        curr = next;
                                                        if(curr != NULL){
                                                                next = curr->next;
                                                        }
                                                }
                                        /**************************************
                                         * Birth of a cell                    *
                                         *************************************/
                                        }else if(plane[j][i] == 3){
                                                new = malloc(sizeof(cell_list));
                                                new->x = i;
                                                new->y = j;
                                                prev->next = new;
                                                new->next = curr;
                                                prev = prev->next;
                                        }
                                /**********************************************
                                 * Birth of a cell, but at the end of the list*
                                 *********************************************/
                                } else if(plane[j][i] == 3){
                                        new = malloc(sizeof(cell_list));
                                        new->x = i;
                                        new->y = j;
                                        prev->next = new;
                                        prev = new;
                                        new->next = NULL;
                                }
                        }
                }            
                *world = sentinel->next;
                free(sentinel);

        return;
}

void next_generation(cell_list **world, dimension dim)
{
        int plane[dim.vertical][dim.horizontal];
        init_plane(dim, plane);
        find_neighbours(world, dim, plane);
        set_live_cells(world, dim, plane);

        return;
}

void destroy_world(cell_list **world)
{
        if(world == NULL){
                return;
        }

        cell_list *curr = *world;
        cell_list *next = curr->next;
        cell_list *tmp;
        while(curr != NULL){
                tmp = curr;
                curr = next;
                if(curr != NULL){
                        next = curr->next;
                }
                free(tmp);
        }

        return;
}
