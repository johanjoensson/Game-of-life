#include <stdio.h>
#include <stdlib.h>

#include "congame.h"
#include "print_nc.h"

#define NBGEN 10000


void print_world_trial(cell_list **world)
{
        cell_list *curr, *next;

        curr = *world;
        next = curr->next;

        int cnt = 0;
        while(next != NULL){
                printf("l");
                if(cnt % 10 == 0){
                        printf("\n");
                }
                cnt++;
                curr = next;
                next = curr->next;
        }

        return;
}

int main(){
        dimension dim;
        dim.horizontal = 10;
        dim.vertical = 10;

        init_screen(dim);

        cell_list **world = init_world(dim);
        cell_list **w = world;
        print_world(w, dim);
        for(int i = 0; i < NBGEN; i++){
                next_generation(world, dim);
                w = world;
                print_world(w, dim);
        }
        exit_screen();
        destroy_world(world);

        return 0;
}
