/*
	This is a test for PVP game.
*/

# include <iostream>
# include <map.H>

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
	cout << "\tDOTANDBOXES! PVP on terminal.\n\n";
	m.print_map_terminal();
	cout << "Scores: Player1->" << m.get_p1_score() << "\tPlayer2->" 
			 << m.get_p2_score() << '\n'; 
}



int main()
{	
	
	map<3,3> _map;
	MOVE cur_mv;
	uint p1_last_score = 0;
	uint p2_last_score = 0;
	
	while(not _map.is_full())
	{
		while(1)
		{
			p1_last_score = _map.get_p1_score();
			printl(_map);
			cout << "Player 1 turn:\n";
			read_mv(cur_mv);
			_map.play(cur_mv,1);
		
			if(_map.is_full())
				break;
		
			if(p1_last_score == _map.get_p1_score())
				break;
		}
		
		if(_map.is_full())
				break;
		
		while(1)
		{
			p2_last_score = _map.get_p2_score();
			printl(_map);
			cout << "Player 2 turn:\n";
			read_mv(cur_mv);
			_map.play(cur_mv,2);
			
			if(_map.is_full())
			break;
			
			if(p2_last_score == _map.get_p2_score())
				break;
		}
		
		if(_map.is_full())
				break;
	}
	
	printl(_map);
	cout << "\nGame finished!\n";
	cout << "Winner: ";
	if(_map.get_p1_score() > _map.get_p2_score())
		cout << "Player 1.\n";
	else if(_map.get_p1_score() < _map.get_p2_score())
		cout << "Player 2.\n";
	else
		cout << "It was a tie.\n";
	return 0;
}

