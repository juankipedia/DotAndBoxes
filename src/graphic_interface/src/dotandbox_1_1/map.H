# ifndef MAP_H
# define MAP_H

# include <dot.H>
# include <utility>
# include <tuple>
# include <iostream>
/**
 *@file map.H
 *
 *@brief implementation on C++ of map for game dot and boxes, map
	 has score of two players and a matrix that saves dots.
	 Logic of game is implemented  here, with this first version
	 users can play one aganist each others.
*
*@author CodeMakers.
*@version 1.0.
*@date 11/3/2016
*/

/**
 *@brief macros to have a better code readability.
   PLAYER1 = represents first player in the game.
   PLAYER2 = represents first player in the game.
   DOT1 = represents first dot into a move.
   DOT2 = represents second dot into a move.
*/
# define PLAYER1 1
# define PLAYER2 2
# define DOT1 boxes[std::get<0>(std::get<0>(cur_move))][std::get<1>(std::get<0>(cur_move))]
# define DOT2 boxes[std::get<0>(std::get<1>(cur_move))][std::get<1>(std::get<1>(cur_move))]
# define MOVE std::tuple<std::pair<size_t,size_t>,std::pair<size_t,size_t> >

/**
 *@brief macros to have a better code readability.
  where each represents to watch diagonal dot, these macros
  are used by check_box to make necessary considerations.
*/
# define MOVE_DOWN_RIGTH 																\
if (boxes[std::get<0>(dot_1->get_pos()) + 1][std::get<1>(dot_1->get_pos()) + 1]->has_up() and 	\
	boxes[std::get<0>(dot_1->get_pos()) + 1][std::get<1>(dot_1->get_pos()) + 1]->has_left()) 		\
{																						\
	increase_score(player); 	     													\
}

# define MOVE_DOWN_LEFT 																\
if (boxes[std::get<0>(dot_1->get_pos()) + 1][std::get<1>(dot_1->get_pos()) - 1]->has_up() and 	\
	boxes[std::get<0>(dot_1->get_pos()) + 1][std::get<1>(dot_1->get_pos()) - 1]->has_right()) 	\
{																						\
	increase_score(player);      														\
}

# define MOVE_UP_LEFT 																	\
if (boxes[std::get<0>(dot_1->get_pos()) - 1][std::get<1>(dot_1->get_pos()) - 1]->has_down() and 	\
	boxes[std::get<0>(dot_1->get_pos()) - 1][std::get<1>(dot_1->get_pos()) - 1]->has_right()) 	\
{																						\
	increase_score(player); 	     													\
}

# define MOVE_UP_RIGTH 																	\
if (boxes[std::get<0>(dot_1->get_pos()) - 1][std::get<1>(dot_1->get_pos()) + 1]->has_down() and	\
	boxes[std::get<0>(dot_1->get_pos()) - 1][std::get<1>(dot_1->get_pos()) + 1]->has_left()) 	    \
{																						\
	increase_score(player); 	     													\
}



/**
 *@brief map class
 *
 *map class is a template.
 *@param R is the number of rows of matrix.
 *@param C is the number of columns of matrix.
 */
template<size_t R = 4, size_t C = 4> class map
{

private:

	typedef std::tuple<std::pair<size_t,size_t>,std::pair<size_t,size_t> > move;
	size_t p1_score, p2_score;
	dot<R,C>* boxes[R][C];

public:

	/**
	 *@brief constructor of class map, sets entire map by giving memory
		to every single dot into the map and seting scores with 0.
	*/
	map() : p1_score(0), p2_score(0)
	{
		for (size_t i = 0; i < R ; ++i)
			for (size_t j = 0; j < C; ++j)
				boxes[i][j] = new dot<R,C>(std::pair<size_t,size_t>(i,j));
	}

	/**
	 *@brief destructor of class map, unsets entire map by deleting memory
		of every single dot into the map.
	*/
	~map()
	{
		for (size_t i = 0; i < R ; ++i)
			for (size_t j = 0; j < C; ++j)
				delete boxes[i][j];
	}


	map(const map & map_)
	{
		copy_map(map_);
	}

	const map & operator = (const map & map_)
	{
		copy_map(map_);
		return *this;
	}

	void copy_map(const map & map_)
	{
		p1_score = map_.p1_score;
		p2_score = map_.p2_score;

		for (size_t i = 0; i < R ; ++i)
			for (size_t j = 0; j < C; ++j)
				*boxes[i][j] = *map_.boxes[i][j];
	}

	/**
	 *@brief gives player one score.
	 *@return player one score.
	*/
	size_t get_p1_score()
	{
		return p1_score;
	}

	/**
	 *@brief gives player two score.
	 *@return player two score.
	*/
	size_t get_p2_score()
	{
		return p2_score;
	}

	/**
	 *@brief increases player score.
	 *@return true if player is valid.
	*/
	bool increase_score(unsigned short player)
	{
		switch(player)
		{
			case PLAYER1:

				p1_score ++;
				return true;
				break;

			case PLAYER2:

				p2_score ++;
				return true;
				break;

			default :
				break;
		}

		return false;
	}

	/**
	 *@brief tells if map was completely full by checking if
	  "p1_score + p2_score" is equal to maximiun number of boxes.
	 *@return bool telling if map is full.
	*/
	bool is_full() const
	{
		return p1_score + p2_score == (R - 1) * (C - 1);
	}

	/**
	 *@brief allows player to make a move.
	   if move was correct then
	   function sets necessary flags to represent move on the map.
	   function evalutes if both dots are in range by checking their
	   positions, therefore if dots are in range function sets the move.
	 *
	 *@return bool telling if move could be set or not.
	*/
	unsigned short play_(dot<R,C>* dot_1,dot<R,C>* dot_2)
	{
		if (dot_1->is_full())
			return 0;

		if (dot_2->is_full())
			return 0;

		if (*dot_1 == *dot_2)
			return 0;

		//dot_2 is left side
		if (std::get<0>(dot_1->get_pos()) - std::get<0>(dot_2->get_pos()) == 0 and
			std::get<1>(dot_1->get_pos()) - std::get<1>(dot_2->get_pos()) == 1)
		{
			if (dot_1->is_ul_corner() or dot_1->is_l_border() or
				dot_1->has_left() or dot_1->is_dl_corner())
				return 0;

			dot_1->mark_left();
			dot_2->mark_right();
			return 1;
		}

		//dot_2 is right side
		if (std::get<0>(dot_1->get_pos()) - std::get<0>(dot_2->get_pos()) == 0 and
			std::get<1>(dot_1->get_pos()) - std::get<1>(dot_2->get_pos()) == -1)
		{
			if (dot_1->is_ur_corner() or dot_1->is_r_border() or
				dot_1->has_right() or dot_1->is_dr_corner())
				return 0;

			dot_1->mark_right();
			dot_2->mark_left();
			return 2;
		}

		//dot_2 is down side
		if ( std::get<0>(dot_1->get_pos()) - std::get<0>(dot_2->get_pos()) == -1 and
			 std::get<1>(dot_1->get_pos()) - std::get<1>(dot_2->get_pos()) == 0)
		{
			if (dot_1->is_dl_corner() or dot_1->is_dr_corner() or
				dot_1->is_d_border() or dot_1->has_down())
				return 0;

			dot_1->mark_down();
			dot_2->mark_up();
			return 3;
		}

		//dot_2 is up side
		if ( std::get<0>(dot_1->get_pos()) - std::get<0>(dot_2->get_pos()) == 1 and
			 std::get<1>(dot_1->get_pos()) - std::get<1>(dot_2->get_pos()) == 0)
		{
			if (dot_1->is_ul_corner() or dot_1->is_ur_corner() or
				dot_1->is_u_border() or dot_1->has_up())
				return 0;

			dot_1->mark_up();
			dot_2->mark_down();
			return 4;
		}
		else
			return 0;
		//dot_2 is off side;
	}

	/**
	 *@brief gives point to player.
	   if player enclose a box function gives point to him.
	   function check if dot where move were done is a corner, border or
	   a simple dot, therefore function has to make necessary considerations.
	*/
	void check_box(dot<R,C>* dot_1, unsigned short player, unsigned short case_)
	{
		if (dot_1->is_ul_corner())
		{
			if(not dot_1->has_right() or not dot_1->has_down())
				return;

			MOVE_DOWN_RIGTH;
			return;
		}

		if (dot_1->is_ur_corner())
		{
			if(not dot_1->has_left() or not dot_1->has_down())
				return;

			MOVE_DOWN_LEFT;
			return;
		}

		if (dot_1->is_dr_corner())
		{
			if(not dot_1->has_left() or not dot_1->has_up())
				return;

			MOVE_UP_LEFT;
			return;
		}

		if (dot_1->is_dl_corner())
		{
			if(not dot_1->has_right() or not dot_1->has_up())
				return;

			MOVE_UP_RIGTH;
			return;
		}

		if(dot_1->is_u_border())
		{
			if(not dot_1->has_right() and not dot_1->has_left())
				return;

			if (case_ == 1)
			{
				MOVE_DOWN_LEFT;
				return;
			}

			if (case_ == 2)
			{
				MOVE_DOWN_RIGTH;
				return;
			}

			if(case_ == 3)
			{
				if (not dot_1->has_right())
				{
					MOVE_DOWN_LEFT;
					return;
				}

				if (not dot_1->has_left())
				{
					MOVE_DOWN_RIGTH;
					return;
				}

				MOVE_DOWN_LEFT;
				MOVE_DOWN_RIGTH;
				return;
			}
		}

		if(dot_1->is_d_border())
		{
			if(not dot_1->has_right() and not dot_1->has_left())
				return;

			if (case_ == 1)
			{
				MOVE_UP_LEFT;
				return;
			}

			if (case_ == 2)
			{
				MOVE_UP_RIGTH;
				return;
			}

			if (case_ == 4)
			{
				if (not dot_1->has_right())
				{
					MOVE_UP_LEFT;
					return;
				}

				if (not dot_1->has_left())
				{
					MOVE_UP_RIGTH;
					return;
				}
				MOVE_UP_RIGTH;
				MOVE_UP_LEFT;
				return;
			}
		}

		if(dot_1->is_l_border())
		{
			if(not dot_1->has_up() and not dot_1->has_down())
				return;

			if (case_ == 4)
			{
				MOVE_UP_RIGTH;
				return;
			}

			if (case_ == 3)
			{
				MOVE_DOWN_RIGTH;
				return;
			}

			if (case_ == 2)
			{
				if (not dot_1->has_up())
				{
					MOVE_DOWN_RIGTH;
					return;
				}

				if (not dot_1->has_down())
				{
					MOVE_UP_RIGTH;
					return;
				}
				MOVE_UP_RIGTH;
				MOVE_DOWN_RIGTH;
				return;
			}
		}

		if(dot_1->is_r_border())
		{
			if(not dot_1->has_up() and not dot_1->has_down())
				return;

			if (case_ == 4)
			{
				MOVE_UP_LEFT;
				return;
			}

			if (case_ == 3)
			{
				MOVE_DOWN_LEFT;
				return;
			}

			if (case_ == 1)
			{
				if (not dot_1->has_up())
				{
					MOVE_DOWN_LEFT;
					return;
				}

				if (not dot_1->has_down())
				{
					MOVE_UP_LEFT;
					return;
				}

				MOVE_UP_LEFT;
				MOVE_DOWN_LEFT;
				return;
			}
		}

		if (case_ == 4)
		{
			if (not dot_1->has_left() and not dot_1->has_right())
				return;

			if (not dot_1->has_right())
			{
				MOVE_UP_LEFT;
				return;
			}

			if (not dot_1->has_left())
			{
				MOVE_UP_RIGTH;
				return;
			}

			MOVE_UP_RIGTH;
			MOVE_UP_LEFT;
			return;
		}

		if (case_ == 3)
		{
			if (not dot_1->has_left() and not dot_1->has_right())
				return;

			if (not dot_1->has_right())
			{
				MOVE_DOWN_LEFT;
				return;
			}

			if (not dot_1->has_left())
			{
				MOVE_DOWN_RIGTH;
				return;
			}

			MOVE_DOWN_LEFT;
			MOVE_DOWN_RIGTH;
			return;
		}

		if(case_ == 2)
		{
			if(not dot_1->has_up() and not dot_1->has_down())
				return;

			if (not dot_1->has_up())
			{
				MOVE_DOWN_RIGTH;
				return;
			}

			if (not dot_1->has_down())
			{
				MOVE_UP_RIGTH;
				return;
			}

			MOVE_UP_RIGTH;
			MOVE_DOWN_RIGTH;
			return;
		}

		if(case_ == 1)
		{
			if(not dot_1->has_up() and not dot_1->has_down())
				return;

			if (not dot_1->has_up())
			{
				MOVE_DOWN_LEFT;
				return;
			}

			if (not dot_1->has_down())
			{
				MOVE_UP_LEFT;
				return;
			}

			MOVE_UP_LEFT;
			MOVE_DOWN_LEFT;
			return;
		}

		return;
	}

	/**
	 *@brief makes sure move is into range and also works as interface of
	 	function play_, first evaluates if move can be done and then gives point
	 	to player by calling function "check_box".
	 *
	 *@return bool telling if move could be set or not.
	*/
	bool play(move cur_move, unsigned short player)
	{
		if(player != PLAYER1 and player != PLAYER2 )
			throw std::out_of_range("player out of range");

		if (  std::get<0>(std::get<0>(cur_move)) >= R or std::get<0>(std::get<1>(cur_move)) >= C or
		 	  std::get<1>(std::get<0>(cur_move)) >= R or std::get<1>(std::get<1>(cur_move)) >= C   )
			throw std::out_of_range("move out of range");

		unsigned short case_ = play_(DOT1,DOT2);
		if (case_ and not is_full())
		{
			check_box(DOT1,player,case_);
			return true;
		}
		else
			return false;
	}

	/**
	 *@brief resets entire map by reseting each dot after reset is done both
	 players
	 have "0" as score.
	*/
	void reset()
	{
		for (size_t i = 0; i < R ; ++i)
			for (size_t j = 0; j < C; ++j)
				boxes[i][j]->reset_dot();

		p1_score = 0;
		p2_score = 0;
	}

	/**
	*@brief prints the map on the terminal.
	*/
	void print_map_terminal() const
	{
		for (size_t i = 0; i < R - 1; ++i)
		{
			for (size_t j = 0; j < C - 1; ++j)
			{
				std::cout << '*';
				if(boxes[i][j]->has_right())
					std::cout << "--";
				else
					std::cout << "  ";
			}
			std::cout << "*\n"; //Last point in the row.
			for (size_t j = 0; j < C ; ++j)
			{
				if(boxes[i][j]->has_down())
					std::cout << "|  ";
				else
					std::cout << "   ";
			}
			std::cout << '\n';
		}

		for(size_t j = 0; j < C - 1; ++j)//last row
		{
			std::cout << "*";
				if(boxes[R-1][j]->has_right())
					std::cout << "--";
				else
					std::cout << "  ";
		}
		std::cout << "*\n"; //Last point in the row.
	}


	unsigned short try_(dot<R,C>* dot_1,dot<R,C>* dot_2) const
	{
		if (dot_1->is_full())
			return 0;

		if (dot_2->is_full())
			return 0;

		if (*dot_1 == *dot_2)
			return 0;

		//dot_2 is left side
		if (std::get<0>(dot_1->get_pos()) - std::get<0>(dot_2->get_pos()) == 0 and
			std::get<1>(dot_1->get_pos()) - std::get<1>(dot_2->get_pos()) == 1)
		{
			if (dot_1->is_ul_corner() or dot_1->is_l_border() or
				dot_1->has_left() or dot_1->is_dl_corner())
				return 0;

			return 1;
		}

		//dot_2 is right side
		if (std::get<0>(dot_1->get_pos()) - std::get<0>(dot_2->get_pos()) == 0 and
			std::get<1>(dot_1->get_pos()) - std::get<1>(dot_2->get_pos()) == -1)
		{
			if (dot_1->is_ur_corner() or dot_1->is_r_border() or
				dot_1->has_right() or dot_1->is_dr_corner())
				return 0;

			return 2;
		}

		//dot_2 is down side
		if ( std::get<0>(dot_1->get_pos()) - std::get<0>(dot_2->get_pos()) == -1 and
			 std::get<1>(dot_1->get_pos()) - std::get<1>(dot_2->get_pos()) == 0)
		{
			if (dot_1->is_dl_corner() or dot_1->is_dr_corner() or
				dot_1->is_d_border() or dot_1->has_down())
				return 0;

			return 3;
		}

		//dot_2 is up side
		if ( std::get<0>(dot_1->get_pos()) - std::get<0>(dot_2->get_pos()) == 1 and
			 std::get<1>(dot_1->get_pos()) - std::get<1>(dot_2->get_pos()) == 0)
		{
			if (dot_1->is_ul_corner() or dot_1->is_ur_corner() or
				dot_1->is_u_border() or dot_1->has_up())
				return 0;

			return 4;
		}
		else
			return 0;
		//dot_2 is off side;
	}

	bool try_move(move cur_move) const
	{
		if (  std::get<0>(std::get<0>(cur_move)) >= R or std::get<0>(std::get<1>(cur_move)) >= C or
		 	  std::get<1>(std::get<0>(cur_move)) >= R or std::get<1>(std::get<1>(cur_move)) >= C   )
			throw std::out_of_range("move out of range");

		if (try_(DOT1,DOT2))
			return true;
		else
			return false;
	}

};

#endif
