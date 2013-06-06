#include "game.h"
#include <allegro.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>


game::game(int row, int col, std::vector<std::vector<state> > init_state)
   : m_row(row), m_col(col), elapsed_generations(0)
{
   m_matrix = init_state;
   nxt_matrix = init_state;
}

game::~game()
{
}

/*
 *       (m-1, n-1)   (m-1, n-1)  (m-1, n-1)
 *       (m+0, n+0)   (m+0, n+0)  (m+0, n+0)
 *       (m+1, n+1)   (m+1, n+1)  (m+1, n+1)
 */

int game::get_number_of_live(int m, int n)
{
   int count = 0;
   for(int i=m-1; i<=m+1; i++) {
      for(int j=n-1; j<=n+1; j++) {
         if (is_valid_coordinate(i, j) && (m_matrix[i][j] == ALIVE)) {
            count++;
         }
      }
   }

   return count;
}

void game::func(void)
{
   //std::cout << "Hello! - " << x << std::endl;
}


/*
 * 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
 * 2. Any live cell with more than three live neighbours dies, as if by overcrowding.
 */

void game::check_and_kill(int m, int n)
{
   if(m_matrix[m][n] == ALIVE) {
      if(get_number_of_live(m, n) < 2) {
         //m_matrix[m][n] = DEAD;
         nxt_matrix[m][n] = DEAD;
      }
      if(get_number_of_live(m, n) > 3) {
         //m_matrix[m][n] = DEAD;
         nxt_matrix[m][n] = DEAD;
      }
   }
}

/*
 * 1. Any live cell with two or three live neighbours lives on to the next generation.
 * 2. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
void game::check_and_live(int m, int n)
{
   if(m_matrix[m][n] == ALIVE) {
      if( (get_number_of_live(m, n) == 3)||(get_number_of_live(m, n) == 2)) {
         //m_matrix[m][n] = ALIVE;
         nxt_matrix[m][n] = ALIVE;
      }
   }
   if(m_matrix[m][n] == DEAD) {
      if(get_number_of_live(m, n) == 3) {
         //m_matrix[m][n] = ALIVE;
         nxt_matrix[m][n] = ALIVE;
      }
   }
}

void game::print(int generations)
{
   elapsed_generations = generations;
   for(int k=0; k<elapsed_generations; k++) {
      for(int i=0; i<m_matrix.size(); i++) {
         for(int j=0; j<m_matrix[0].size(); j++) {
            check_and_live(i, j);
            check_and_kill(i, j);
         }
      }

     /* Previous Gen */
     std::cout << "Current Gen: " << k << std::endl;
     for(int i=0; i<m_matrix.size(); i++) {
       for(int j=0; j<m_matrix[0].size(); j++) {
         std::cout << " " << m_matrix[i][j] << " ";
       }
       std::cout << std::endl;
     }  

      int val = 0; 
     /* NXT Gen */
     std::cout << "Next Gen: " << k << std::endl;
     for(int i=0; i<nxt_matrix.size(); i++) {
       for(int j=0; j<nxt_matrix[0].size(); j++) {
         std::cout << " " << nxt_matrix[i][j] << " ";
         val = nxt_matrix[i][j];
         if (val == 1) {
           al_draw_filled_rectangle((i*20),(j*20), (i*20)+20, (j*20)+20, al_map_rgb(0, 255, 0));
         } else {
           al_draw_filled_rectangle((i*20),(j*20), (i*20)+20, (j*20)+20, al_map_rgb(0, 0, 0));
         }
       }
       al_flip_display();
       std::cout << std::endl;
     }
     m_matrix = nxt_matrix;
    al_rest(1.0);
   }
}

int main(int argc, char *argv[])
{
   std::vector<std::vector<state> > init_state;
   int sizeOfMatrix = 3;
   int noOfGen = 4;

   ALLEGRO_DISPLAY *display; 
     
   if(!al_init())
   {
     std::cout << "Could not initialize Allegro 5" << std::endl; 
       return -1;
   }
   al_init_primitives_addon();

   display = al_create_display(ScreenWidth, ScreenHeight); 
   if(!display)
   {
     std::cout << "Could not create Allegro 5 display" << std::endl; 
     return -1;
   }
         
   al_set_new_display_flags(ALLEGRO_NOFRAME);
   al_set_window_title(display, "  Game Of Life  ");

   if (argc == 3) {
     sizeOfMatrix = std::atoi(argv[1]);
     noOfGen = std::atoi(argv[2]);
   } else {
     std::cout << "Usage: " << argv[0] << " <Size Of Matrix> <No Of Generations> " << std::endl; 
     std::cout << "Using Default Values" << std::endl; 
   }
     
   std::cout << "Size Of Matrix: " << sizeOfMatrix << " No Of Generations: " << noOfGen << std::endl; 

   init_state.resize(sizeOfMatrix);
   for(int i=0; i<sizeOfMatrix; i++) {
      init_state[i].resize(sizeOfMatrix);
      for(int j=0; j<sizeOfMatrix; j++) {
         init_state[i][j] =  ((i + j) % 2 == 0)? ALIVE:DEAD;
      }
   }

   game::func();

   game g(sizeOfMatrix, sizeOfMatrix, init_state);
   g.print(noOfGen);

   game::func();

   /*
    game h(3, 3, init_state);

    game::func();
    h.print(10);
    game::func();
   */
     
    al_rest(3.0);
    al_destroy_display(display);
     
   return 0;
}
