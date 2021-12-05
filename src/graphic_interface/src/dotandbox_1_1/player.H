# ifndef PLAYER_H
# define PLAYER_H

# include <string>
# include <iostream>
# include <utility>

//using namespace std;
/**
 *@file player.H
 *@brief Declarations on C++ of class player, game dot and boxes.
 *@author CODEMAKERS
 *@date 03/11/2016
*/
class player
{
private:

	std::string id;   //name of player
	uint score;	 //points on current game
	uint record; //number of games won

public:

	/**
	 *@brief Constructor, sets values of player attributes.
	*/
	player() : id(""),score(0),record(0){/*empty*/}


	/**
	 *@brief Copy constructor, sets values of player attributes with values of a player.
	*/
	player(const player & player_) : id(player_.id),score(player_.score),record(player_.record)
	{
		/*empty*/
	}

	player(player && player_)
	{
		std::swap(id,player_.id);
		std::swap(score,player_.score);
		std::swap(record,player_.record);
	}

	/**
	 *@brief Basic destructor.
	*/
	~player(){/*empty*/}

	/**
	 *@brief to see player id.
	 *@return player id.
	*/
	const std::string & get_id() const
	{
		return id;
	}

	/**
	 *@brief to see player score.
     *@return player score.
	*/
	uint get_score()
	{
		return score;
	}

	/**
	 *@brief to see player record.
     *@return player record.
	*/
	uint get_record()
	{
		return record;
	}

	/**
	 *@brief sets player id.
	 *@param name of player.
	*/
	void set_id(std::string id_)
	{
		id = id_;
		return;
	}

	/**
	 *@brief sets player score
	 *@param score of player
	*/
	void set_score(uint scr)
	{
		score = scr;
		return;
	}

	/**
	 *@brief sets player record
	 *@param record of player
	*/
	void set_record(uint rec)
	{
		record = rec;
		return;
	}
};

#endif
