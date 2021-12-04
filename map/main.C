# include <map.H>
# include <tuple>
# include <iostream>

using namespace std;

int main()
{

	dot<3,3> dot_1;
	dot<3,3> dot_2 = dot_1;
	map<3,3> map_;

	MOVE mv;

	get<0>(get<0>(mv)) = 0;
	get<1>(get<0>(mv)) = 0;

	get<0>(get<1>(mv)) = 0;
	get<1>(get<1>(mv)) = 1;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

	cout << "was_point: " << map_.was_point(mv) << "\n";

	get<0>(get<0>(mv)) = 0;
	get<1>(get<0>(mv)) = 1;

	get<0>(get<1>(mv)) = 1;
	get<1>(get<1>(mv)) = 1;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

	cout << "was_point: " << map_.was_point(mv) << "\n";

	get<0>(get<0>(mv)) = 1;
	get<1>(get<0>(mv)) = 0;

	get<0>(get<1>(mv)) = 0;
	get<1>(get<1>(mv)) = 0;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

cout << "was_point: " << map_.was_point(mv) << "\n";

	get<0>(get<0>(mv)) = 1;
	get<1>(get<0>(mv)) = 0;

	get<0>(get<1>(mv)) = 1;
	get<1>(get<1>(mv)) = 1;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";


	cout << "was_point: " << map_.was_point(mv) << "\n";

	cout << "score player 1: " << map_.get_p1_score() << "\n";


	/*get<0>(get<0>(mv)) = 0;
	get<1>(get<0>(mv)) = 1;

	get<0>(get<1>(mv)) = 0;
	get<1>(get<1>(mv)) = 2;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";



	cout << "score player 1: " << map_.get_p1_score() << "\n";

	get<0>(get<0>(mv)) = 0;
	get<1>(get<0>(mv)) = 2;

	get<0>(get<1>(mv)) = 1;
	get<1>(get<1>(mv)) = 2;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";



	cout << "score player 1: " << map_.get_p1_score() << "\n";

	get<0>(get<0>(mv)) = 1;
	get<1>(get<0>(mv)) = 2;

	get<0>(get<1>(mv)) = 1;
	get<1>(get<1>(mv)) = 1;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

	cout << "score player 1: " << map_.get_p1_score() << "\n";

	get<0>(get<0>(mv)) = 1;
	get<1>(get<0>(mv)) = 2;

	get<0>(get<1>(mv)) = 2;
	get<1>(get<1>(mv)) = 2;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

	cout << "score player 1: " << map_.get_p1_score() << "\n";


	get<0>(get<0>(mv)) = 2;
	get<1>(get<0>(mv)) = 1;

	get<0>(get<1>(mv)) = 2;
	get<1>(get<1>(mv)) = 2;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

	cout << "score player 1: " << map_.get_p1_score() << "\n";


	get<0>(get<0>(mv)) = 1;
	get<1>(get<0>(mv)) = 1;

	get<0>(get<1>(mv)) = 2;
	get<1>(get<1>(mv)) = 1;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

	cout << "score player 1: " << map_.get_p1_score() << "\n";


	get<0>(get<0>(mv)) = 1;
	get<1>(get<0>(mv)) = 0;

	get<0>(get<1>(mv)) = 2;
	get<1>(get<1>(mv)) = 0;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

	cout << "score player 1: " << map_.get_p1_score() << "\n";


	get<0>(get<0>(mv)) = 2;
	get<1>(get<0>(mv)) = 0;

	get<0>(get<1>(mv)) = 2;
	get<1>(get<1>(mv)) = 1;

	if(map_.play(mv,1))
		cout << "valid move" << "\n";
	else
		cout << "invalid move" << "\n";

	cout << "score player 1: " << map_.get_p1_score() << "\n";


	cout << "map_full : " << map_.is_full() << "\n";

	map_.reset();

	cout << "after reset map_full : " << map_.is_full() << "\n";*/
}