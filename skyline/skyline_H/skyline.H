# ifndef SKYLINE_H
# define SKYLINE_H


# include "../decision_tree/d_tree_node.H"
# include <vector>
# include <iostream>
# include <cstdlib>
# include <ctime>

/**
 *@file skyline.H
 *
 *@brief Skyline class is the top-level class for dotandbox AI implementation.
        Skyline is responsible for build the ideal map and generate moves for AI.
*
*/

/**
 *@brief skyline class contains its own dotandbox_tree, and a vector<MOVE>.
 *This vector works to build the ideal map.
 *@param lvl is the difficult of skyline AI.
 */
class skyline
{

private:

        dotandbox_tree<4,4,4> *decision_tree;
        std::vector<MOVE> ideal_moves;
				unsigned short lvl;

        /**
         *@brief equal_moves is used by skyline class.
        */
        bool equal_moves(MOVE & m1, MOVE & m2)
        {
            if(
                (std::get<0>(std::get<0>(m1)) == std::get<0>(std::get<0>(m2))
                        and
                std::get<1>(std::get<0>(m1)) == std::get<1>(std::get<0>(m2))
                        and
                std::get<0>(std::get<1>(m1)) == std::get<0>(std::get<1>(m2))
                        and
                std::get<1>(std::get<1>(m1)) == std::get<1>(std::get<1>(m2)))

                or

                (std::get<0>(std::get<0>(m1)) == std::get<0>(std::get<1>(m2))
                        and
                std::get<1>(std::get<0>(m1)) == std::get<1>(std::get<1>(m2))
                        and
                std::get<0>(std::get<1>(m1)) == std::get<0>(std::get<0>(m2))
                        and
                std::get<1>(std::get<1>(m1)) == std::get<1>(std::get<0>(m2)))
                )
             return true;
            else
             return false;
        }

        /**
         *@brief sk_human_turn is used by skyline class.
        */
        void sk_human_turn(MOVE & human_move)
        {
            for(int i = 0; i < ideal_moves.size(); i++)
            {
                if(equal_moves(ideal_moves[i], human_move))
                {
                    ideal_moves.erase(ideal_moves.begin()+i);
                }
            }
        }


public:

        /**
        *@brief constructor for skyline class.
        *@param game_map is the board of the main game.
        *@param cur_move is the last move played.
        */
        skyline(const map<4,4> & game_map, MOVE cur_move,unsigned short _lvl)
        {
						lvl = _lvl;
            decision_tree = new dotandbox_tree<4,4,4>(game_map, cur_move);
            MOVE move;

            std::get<0>(std::get<0>(move)) = 1;
            std::get<1>(std::get<0>(move)) = 2;

            std::get<0>(std::get<1>(move)) = 0;
            std::get<1>(std::get<1>(move)) = 2;

            ideal_moves.push_back(move);
            if (lvl == 1)
   				return;

            std::get<0>(std::get<0>(move)) = 2;
            std::get<1>(std::get<0>(move)) = 2;

            std::get<0>(std::get<1>(move)) = 2;
            std::get<1>(std::get<1>(move)) = 3;

            ideal_moves.push_back(move);
            if (lvl == 2)
   				return;

            std::get<0>(std::get<0>(move)) = 2;
            std::get<1>(std::get<0>(move)) = 1;

            std::get<0>(std::get<1>(move)) = 3;
            std::get<1>(std::get<1>(move)) = 1;

            ideal_moves.push_back(move);
            if (lvl == 3)
   				return;

            std::get<0>(std::get<0>(move)) = 1;
            std::get<1>(std::get<0>(move)) = 0;

            std::get<0>(std::get<1>(move)) = 1;
            std::get<1>(std::get<1>(move)) = 1;

            ideal_moves.push_back(move);
        }

        /**
        *@brief destructor for skyline class.
        */
        ~skyline()
        {
        	delete decision_tree;
        }

        /**
         *@brief human_turn is used to discount the ideal_moves made by the user.
         */
        void human_turn(const map<4,4> & game_map ,MOVE cur_move)
        {
            sk_human_turn(cur_move);
            return;
        }

        /**
         *@brief AI_play return the most convenient move for AI.
         */
        MOVE AI_play()
        {
                //AI turn.
          for(size_t i = 0; i < this->decision_tree->moves_number() ; i++)
          {
	            if(this->decision_tree->get_root()->get_children()[i].get_map().
	              was_point(
	              this->decision_tree->get_root()->get_children()[i].get_move()))
	            {
	                return this->decision_tree->get_root()->get_children()[i].get_move();
	            }
          }

			if(ideal_moves.size() != 0)
			{
		        srand(time(0));
		        size_t pos = rand() % ideal_moves.size();
		        MOVE ret = ideal_moves[pos];
		        ideal_moves.erase(ideal_moves.begin()+pos);
		        return ret;
			}


                return this->decision_tree->get_next_move();
        }

        /**
         *@brief check_play is responsible for the count of plays left.
         *
         * check_play is responsible for the count of plays left. It must be used
                 everytime a play is made in the main board. Doing so,
                 the dotandbox tree of skyline keeps updated.
         *@param game_map is the board of the main game.
         *@param cur_move is the last move played
         *@player is an identifier of the player who did the las play.
         */
        void check_play(const map<4,4>& game_map, MOVE cur_move, size_t player)
        {
        		this->decision_tree->reset_tree();
            if(player == 2 and ideal_moves.size() != 0) //Human turn
            {
                human_turn(game_map, cur_move);
                this->decision_tree->make_decision_tree(game_map,
                											cur_move,player);
                return;
            }
            else if(player == 2)
            {
                this->decision_tree->make_decision_tree(game_map,
                											cur_move,player);
                return;
            }
            else // AI turn
            {
                this->decision_tree->make_decision_tree(game_map,
                											cur_move,player);
                return;
            }
        }

        /**
         *@brief blind_move is used for discount a move.
         *It must be used when a play has been made, and AI does not need to build
         *a predictive tree. (For example, player plays again, or player comes next).
         */
        void blind_move()
        {
        	this->decision_tree->moves_number()--;
        }
};

# endif
