#ifndef CONGAME_H
#define CONGAME_H

/******************************************************************************
 * struct for easy handling of the dimensions of the world                    *
 *****************************************************************************/
typedef struct dimension_t{
        unsigned int horizontal;
        unsigned int vertical;
} dimension;

/******************************************************************************
 * struct for easy handling of the live cells in a world                      *
 *****************************************************************************/
typedef struct live_cell_struct {
        unsigned int x,y;
        struct live_cell_struct *next;
} cell_list;

/******************************************************************************
 * Returns a new world with dimension dim                                     *
 * Arguments:   dimension dim   the size of the world                         *
 * Return:      The live cells of the newly created world                     *
 *****************************************************************************/
cell_list** init_world(dimension dim);

/******************************************************************************
 * Updates the world, calculates which cells survive, die or are born in the  *
 * new generation                                                             *
 * Arguments:   cell_list *world        The live cells of the world to update *
 * Return:      void                    Nothing to return, all is in world    *
 *****************************************************************************/
void next_generation(cell_list **world, dimension dim);

/******************************************************************************
 * Destroys the entire world                                                  *
 * Arguments:   cell_list *world        The world to destroy                  *
 * Return:      Void                    No need to return a destriyed world   *
 *****************************************************************************/
void destroy_world(cell_list **world);

#endif //CONGAME_H
