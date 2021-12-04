# include <skyline.H>
# include <iostream>
//# include <stdlib>
using namespace std;

# define R 4
# define C 4
# define LVL 4 //Number of levels on tree.

	/**	
	*@brief Player vs Computer game on terminal.
	*/

void read_mv(MOVE & _mv)
{
	uint r,c;
	cout << "First dot:\n";
	cout << "R = ";
	cin >> r;
	cout << "C = ";
	cin >> c;
	get<0>(get<0>(_mv)) = r;
	get<1>(get<0>(_mv)) = c;
	cout << "Second dot:\n";
	cout << "R = ";
	cin >> r;
	cout << "C = ";
	cin >> c;
	get<0>(get<1>(_mv)) = r;
	get<1>(get<1>(_mv)) = c;
}

void printl(auto & m)
{
		for(int i = 0; i <= 40; i++)
			cout << '\n';
	
	cout << "\tDOTANDBOXES! PvC on terminal.\n\n";
	m.print_map_terminal();
	cout << "Scores: Player->" << m.get_p2_score() << "\tComputer->" 
			 << m.get_p1_score() << '\n'; 
	cout << endl;
}

int main()
{
	//
	map<R,C> game_map;
	MOVE cur_move;
	skyline sky(game_map, cur_move,4);
	size_t p1_last_score, p2_last_score;


	while(not game_map.is_full())
	{
			while(1)
			{
				do
				{
					printl(game_map);
					cout << "Player turn!\n";
					read_mv(cur_move);
				}while(not game_map.try_move(cur_move));
				
				p2_last_score = game_map.get_p2_score();
				game_map.play(cur_move,2);
				
				if(game_map.is_full())
					break;
				
				if(p2_last_score != game_map.get_p2_score())
				{
					sky.blind_move();
					continue;
				}
				else
				{
					sky.check_play(game_map,cur_move,2);
					break;
				}
			}
			
			if(game_map.is_full())
				break;
			
			while(1)
			{
				p1_last_score = game_map.get_p1_score();
				printl(game_map);
				cout << "Computer turn...";
				cur_move = sky.AI_play();
				game_map.play(cur_move,1);
				
				
				if(game_map.is_full())
					break;
				
				if(p1_last_score != game_map.get_p1_score())
				{
					sky.check_play(game_map, cur_move,1);
					continue;
				}
				else
				{
					sky.blind_move();
					break;
				}
			}
			
			if(game_map.is_full())
				break;
	
	}
	
	printl(game_map);
	cout << "Game finished!\n";
	cout << "Winner: ";
	if(game_map.get_p1_score() > game_map.get_p2_score())
		cout << "Computer.\n";
	else if(game_map.get_p1_score() < game_map.get_p2_score())
		cout << "Player.\n";
	else
		cout << "It was a tie.\n";
	
	
	return 0;
}
