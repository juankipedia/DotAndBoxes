# ifndef D_TREE_NODE_H
# define D_TREE_NODE_H

# include <map.H>
# include <iostream>
/**
 *@file d_tree_node.H
 *
 *@brief implementation on C++ of a decision tree for game dot and boxes, it is
 	a dimensioned tree, because moves into a map are a finite number depending
 	on the map, that number of moves is going to increase exponentially 
 	depending on map. that is why this tree is implemented with arrays on each
 	level.  
*
*/

/**
 *@brief macro to have a better code readability.
   POS = represents position into map.
*/
# define POS std::pair<size_t,size_t>

/**
 *@brief move_bucket class
 *
 *move_bucket class is a template. 
 *@param R is the number of rows in the map.
 *@param C is the number of columns in the map.
 */
template <size_t R = 4, size_t C = 4> 
class move_bucket
{

private:

	MOVE actual_move;
	map<R,C> actual_map;
	long utility  = 0;
	move_bucket<R,C> * children;

public:
	
	/**
	 *@brief default constructor of class move_bucket, sets move_bucket with
	  default values.
	*/
	move_bucket() : actual_move(), actual_map(), children(nullptr) 
	{
		/*empty*/
	}

	/**
	 *@brief constructor of class move_bucket, sets move_bucket with values
	 		 given by user.
	 		 map move_bucket is going to be set with has got to have move passed
	 		 by parameter into its current moves.
	*/
	move_bucket(const map<R,C> & new_map, const MOVE & new_move,
				move_bucket<R,C> *children_)
	{
		actual_move = new_move;
		actual_map = new_map;
		children = children_;
		return;
	}

	/**
	 *@brief destructor of class move_bucket, it is empty because memory is 
	 		 manage by decision tree.
	*/
	~move_bucket(){/*empty*/}

	/**
	 *@brief sets bucket with parameter values after being instanciated.
	*/
	void set_bucket(const map<R,C> & new_map, const MOVE & new_move,
					move_bucket<R,C> *children_)
	{
		actual_move = new_move;
		actual_map = new_map;
		children = children_;
		return;
	}

	/**
	 *@brief definition of operator = for class move_bucket that allows 
	 		 move_bucket to be copied.
	*/
	const move_bucket & operator = (const move_bucket & bucket)
	{
		set_bucket(bucket.actual_map,bucket.actual_move,bucket.children);

	}

	/**
	 *@brief returns current move into move_bucket.
	*/
	MOVE & get_move() 
	{
		return actual_move;
	}

	/**
	 *@brief returns current map into move_bucket.
	*/
	map<R,C> & get_map()
	{
		return actual_map;
	}

	/**
	 *@brief sets move into move_bucket.
	*/
	void set_move(const MOVE &move_)
	{
		actual_move = move_;
		return;
	}

	/**
	 *@brief sets map into move_bucket.
	*/
	void set_map(const map<R,C> &map_)
	{
		actual_map = map_;
		return;
	}

	/**
	 *@brief returns utility of move_bucket, utility is used for skyline to
	 		 select best move for next movement.
	*/
	long get_utility()
	{
		return utility;
	}

	/**
	 *@brief sets utility of move_bucket, utility is used for skyline to
	 		 select best move for next movement.
	*/
	void set_utility(const long & utility_)
	{
		utility = utility_;
		return;
	}

	/**
	 *@brief returns reference pointer to children, with this pointer every 
	 	     single child can be used.
	*/
	move_bucket<R,C> *& get_children()
	{
		return children;
	}

	/**
	 *@brief resets move_bucket to default values.
	*/
	void reset()
	{
		actual_map.reset();
		std::get<0>(std::get<0>(actual_move)) = 0;
		std::get<1>(std::get<0>(actual_move)) = 0;
		std::get<0>(std::get<1>(actual_move)) = 0;
		std::get<1>(std::get<1>(actual_move)) = 0;
		children = nullptr;
	}

};

/**
 *@brief dotandbox_tree class.
 *
 *move_bucket class is a template. 
 *@param R is the number of rows in the map.
 *@param C is the number of columns in the map.
 *@param lvl number of generations tree will have.
 */
template <size_t R = 4, size_t C = 4, size_t lvl = 3> 
class dotandbox_tree
{

private:

	move_bucket<R,C> * root;
	size_t a_moves;

public:

	/**
	 *@brief default constructor of class dotandbox_tree, sets dotandbox_tree
	  		 with default values.
	*/
	dotandbox_tree() : a_moves(2 * (C - 1) * C)
	{
		root = new move_bucket<R,C>;
		return;
	}

	/**
	 *@brief constructor of class dotandbox_tree, it is used to set 
	 	     dotandbox_tree with first move, giving parameters to root, also
	 	     seting max number of moves.
	*/	
	dotandbox_tree(const map<R,C> & new_map, const MOVE & new_move)
	{
		root = new move_bucket<R,C>(new_map,new_move,nullptr);
		a_moves = 2 * (C - 1) * C;
		return;
	}

	/**
	 *@brief destructor of class dotandbox_tree, function deletes level by level
	 		 starting form the botton.
	*/
	~dotandbox_tree()
	{
		reset(root,a_moves);
		delete root;
	}

	/**
	 *@brief resets dotandbox_tree by deleting each level except for root.
	*/
	void reset(move_bucket<R,C> *root_,size_t a_moves_)
	{
		if (root_->get_children() == nullptr)
			return;

		for (size_t i = 0; i < a_moves_; ++i)
		{
			reset(&root_->get_children()[i],a_moves_ - 1);
			delete [] root_->get_children()[i].get_children();
		}
	
		return;
	}

	/**
	 *@brief resets dotandbox_tree by deleting each level except for root, root 
	 		 is reset with default values.
	*/
	void reset_tree()
	{
		reset(root,a_moves);
		root->reset();
		return;
	}

	/**
	 *@brief resets dotandbox_tree by deleting each level except for root, root
	 		 is reset with default values and avalible moves with max number of 
	 		 moves into map.
	*/
	void delete_tree()
	{
		reset(root,a_moves);
		root->reset();
		a_moves = 2 * (C - 1) * C;
		return;
	}

	/**
	 *@brief sets tree after being reset with a new map and move.
	*/
	void set(const map<R,C> & new_map, const MOVE & new_move)
	{
		root->set_bucket(new_map,new_move,nullptr);
		a_moves -= 1;
		return;
	}
	
	/**
	 *@brief returns moves contained by this tree.
	**/
	size_t & moves_number()
	{
		return a_moves;
	}

	/**
	 *@brief returns root of tree.
	*/
	move_bucket<R,C> *& get_root()
	{
		return root;
	}

	/**
	 *@brief creates array with children of a move, param a_moves_ tells number
	 		 of children.
	*/
	move_bucket<R,C> * gen_children(const map<R,C> & new_map, unsigned short 
									player, size_t a_moves_)
	{
		move_bucket<R,C> * children_ = new move_bucket<R,C>[a_moves_];
		size_t pos = 0;
		MOVE mv;
		POS pos_aux;
		std::get<0>(pos_aux) = 0;
		std::get<1>(pos_aux) = 0;

		for (size_t i = 0; i < R; ++i)
		{	
			for (size_t j = 1; j < C; ++j)
			{
				
				if (i != 0)
				{
					std::get<0>(std::get<0>(mv)) = std::get<0>(pos_aux);
					std::get<1>(std::get<0>(mv)) = std::get<1>(pos_aux);
					std::get<0>(std::get<1>(mv)) = i - 1;
					std::get<1>(std::get<1>(mv)) = j - 1;

					if(new_map.try_move(mv))
					{ 
						children_[pos].set_bucket(new_map,mv,nullptr); 
						children_[pos].get_map().play(mv,player);
						pos ++;
					}
				}					

				std::get<0>(std::get<0>(mv)) = std::get<0>(pos_aux);
				std::get<1>(std::get<0>(mv)) = std::get<1>(pos_aux);
				std::get<0>(pos_aux) = std::get<0>(std::get<1>(mv)) = i;
				std::get<1>(pos_aux) = std::get<1>(std::get<1>(mv)) = j;

				if(new_map.try_move(mv))
				{	
					children_[pos].set_bucket(new_map,mv,nullptr); 
					children_[pos].get_map().play(mv,player);
					pos ++;
				}
			}

			if (i != 0)
			{
				std::get<0>(std::get<0>(mv)) = std::get<0>(pos_aux);
				std::get<1>(std::get<0>(mv)) = std::get<1>(pos_aux);
				std::get<0>(std::get<1>(mv)) = i - 1; 
				std::get<1>(std::get<1>(mv)) = std::get<1>(pos_aux);
				
				if(new_map.try_move(mv))
				{
					children_[pos].set_bucket(new_map,mv,nullptr); 
					children_[pos].get_map().play(mv,player);
					pos ++;
				}
			}					

			std::get<0>(pos_aux) = i + 1;
			std::get<1>(pos_aux) = 0;
		}

		return children_;	
	}

	/**
	 *@brief creates entire children generation of root.
	*/
	void make_tree(move_bucket<R,C> *root_,const map<R,C> & new_map, 
				   size_t cur_lvl, size_t a_moves_, unsigned short player)
	{
		if (cur_lvl >= lvl or a_moves_ == 0)	
			return;

		if(root_->get_map().was_point(root_->get_move()))
			root_->get_children() = gen_children(new_map,player,a_moves_);
		else
		{	
			if (player == 1)
				player = 2;
			else
				player = 1;

			root_->get_children() = gen_children(new_map,player,a_moves_);
		}
		
		long utility = 0;

	    for (size_t i = 0; i < a_moves_; i++)
		{
			make_tree(&root_->get_children()[i],
			root_->get_children()[i].get_map(),cur_lvl + 1,a_moves_ - 1,player);

			if (root_->get_children()[i].get_children() == nullptr)
				root_->get_children()[i].set_utility(
					root_->get_children()[i].get_map().get_p1_score() - 
					root_->get_children()[i].get_map().get_p2_score() );

				utility += root_->get_children()[i].get_utility();
		}
		
		root_->set_utility(utility);		
		return;
	}

	/**
	 *@brief creates entire children generation of root and sets root with a new
	 		 move.
	*/
	void make_decision_tree(const map<R,C> & new_map, const MOVE & new_move,
							unsigned short player)
	{
		set(new_map,new_move);
		make_tree(root,new_map,0,a_moves, player);

		return;
	}

	/**
	 *@brief selects best move to play, wich is child of root with biggest 
	 		 utility.
	 *return move to be play.
	*/
	MOVE get_next_move()
	{
		MOVE best_move;
		long biggest_utility = root->get_children()[0].get_utility();
		best_move = root->get_children()[0].get_move();

		long add_sub = 0;

		for (size_t i = 0; i < a_moves; i++)
		{
			if (root->get_children()[i].get_map().
					was_point(
					root->get_children()[i].get_move()))
			{
				best_move = root->get_children()[i].get_move();
				break;
			}
			if (root->get_children()[i].get_utility() > biggest_utility)
			{
				best_move = root->get_children()[i].get_move();
				biggest_utility = root->get_children()[i].get_utility();
			}
		}

		return best_move;
	}
};

# endif
