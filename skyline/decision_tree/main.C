# include <d_tree_node.H>
using namespace std;
int main()
{
	
	map<3,3> map_;
	MOVE mv;

	dotandbox_tree<3,3,3> * d_t = new dotandbox_tree<3,3,3>();

	get<0>(get<0>(mv)) = 0;
	get<1>(get<0>(mv)) = 0;

	get<0>(get<1>(mv)) = 1;
	get<1>(get<1>(mv)) = 0;

	map_.play(mv,2);

	cout << "player_ move: (" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "IA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n";


	d_t->make_decision_tree(map_,mv,2);
	mv = d_t->get_next_move();
	cout << "\nIA_move_after_player_move(" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;
	d_t->reset_tree();

	map_.play(mv,1);

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,1);
	d_t->reset_tree();


	get<0>(get<0>(mv)) = 0;
	get<1>(get<0>(mv)) = 1;

	get<0>(get<1>(mv)) = 1;
	get<1>(get<1>(mv)) = 1;

	map_.play(mv,2);

	cout << "player_ move: (" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,2);
	mv = d_t->get_next_move();
	cout << "IA_move_after_player_move(" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;
	d_t->reset_tree();

	map_.play(mv,1);

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,1);
	mv = d_t->get_next_move();
	cout << "IA_move_after_point(" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;
	d_t->reset_tree();

	map_.play(mv,1);

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,1);
	d_t->reset_tree();


	get<0>(get<0>(mv)) = 1;
	get<1>(get<0>(mv)) = 2;

	get<0>(get<1>(mv)) = 0;
	get<1>(get<1>(mv)) = 2;

	map_.play(mv,2);

    cout << "player_ move: (" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;
	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,2);
	mv = d_t->get_next_move();
	cout << "IA_move_after_player_move(" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;
	d_t->reset_tree();

	map_.play(mv,1);

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,1);
	mv = d_t->get_next_move();
	cout << "IA_move_after_point(" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;
	d_t->reset_tree();

	map_.play(mv,1);

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,1);
	d_t->reset_tree();


	get<0>(get<0>(mv)) = 2;
	get<1>(get<0>(mv)) = 1;

	get<0>(get<1>(mv)) = 2;
	get<1>(get<1>(mv)) = 2;

	map_.play(mv,2);

	cout << "player_ move: (" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,2);
	mv = d_t->get_next_move();
	cout << "IA_move_after_player_move(" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;
	d_t->reset_tree();

	map_.play(mv,1);

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,1);
	d_t->reset_tree();

	get<0>(get<0>(mv)) = 1;
	get<1>(get<0>(mv)) = 1;

	get<0>(get<1>(mv)) = 2;
	get<1>(get<1>(mv)) = 1;

	map_.play(mv,2);

	cout << "player_ move: (" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";
	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";

	d_t->make_decision_tree(map_,mv,2);
	d_t->reset_tree();


	get<0>(get<0>(mv)) = 2;
	get<1>(get<0>(mv)) = 2;

	get<0>(get<1>(mv)) = 1;
	get<1>(get<1>(mv)) = 2;

	map_.play(mv,2);
	d_t->make_decision_tree(map_,mv,2);
	d_t->reset_tree();

	cout << "player_move_after_point(" << get<0>(get<0>(mv)) << "," << get<1>(get<0>(mv)) 
	     << ") - (" << get<0>(get<1>(mv)) << "," << get<1>(get<1>(mv)) << ")" << endl;

	cout << "\ncur_map: \n";
	map_.print_map_terminal();
	cout << "\n\n";

	cout << "\nIA_score: " << map_.get_p1_score() << " player_score: " << map_.get_p2_score() << "\n\n";
return 0;
}