#include <vector>
#include <iostream>
#include <cstdlib>

enum state {DEAD = 0, ALIVE = 1};

#define ScreenWidth   800 
#define ScreenHeight  600

class game
{
   private:
   int m_row;
   int m_col;
   std::vector<std::vector<state> > m_matrix;
   std::vector<std::vector<state> > nxt_matrix;

   int elapsed_generations;

   void check_and_kill(int m, int n);
   void check_and_live(int m, int n);
   int get_number_of_live(int m, int n);
   bool is_valid_coordinate(int r, int c) {
      x++;
      return (((r>=0)&&(r<m_matrix.size()))&&((c>=0)&&(c<m_matrix[0].size())));
   }

   public:
   game(int row, int col, std::vector<std::vector<state> > init_state);
   static int x;
   static void func(void);
   void foo(game y) {
      m_row = y.m_row;
   }

   ~game();

   void print(int generations);
};

int game::x = 0;
