#include <stdio.h>
#include <stdlib.h>

#include "print.h"

void print_world(cell_list **world, dimension dim)
{
        cell_list *curr = *world;
        for(unsigned int j = 0; j < dim.vertical; j++){
                for (unsigned int i = 0; i < dim.horizontal; i++){
                        if(curr != NULL){
                                if(i == curr->x && j == curr->y){
                                        fprintf(stdout,"@");
                                        curr = curr->next;
                                } else {
                                        fprintf(stdout,"0");
                                }
                        }else{
                                fprintf(stdout,"0");
                        }
                }
                printf("\n");
        }
        return;
}
