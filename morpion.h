#include <iostream>
#include <vector>
#include <string>


class Board{
private:
	std::vector<int> board;
	int option_config = 1;
public:
	Board(std::vector<int> b = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }){
		board = b;
	}

	void configuration(int c){
		if (c == 1){
			option_config = 1; // si 789456123
		}
		else {
			option_config = 2; // ou 123456789
		}
	}

	int position(int pos){
		// traduit entree user en position dans board
		if (option_config ==  1){
			switch(pos){
				case 7:
				return 0;
				case 8:
				return 1;
				case 9:
				return 2;
				case 4:
				return 3;
				case 5:
				return 4;
				case 6:
				return 5;
				case 1:
				return 6;
				case 2:
				return 7;
				default:
				return 8;
			}
		}
		else {
			return pos-1;
		}
	}

	int value_in(int pos){
		return board[pos];
	}

	std::string str_value(int pos){
		// chaque val numerique associee a u symbole: 0 " ", 1 "X", 2 "O"
		if (board[pos] == 0){
			return " ";
		}
		else if (board[pos] == 1){
			return "X";
		}
		else {
			return "O";
		}
	}

	void draw(){
		// affiche la partie en cours
		for (int i = 0; i < 9; i++){
			std::cout << "|" << str_value(i);
			if ((i + 1) % 3 == 0){
				std::cout << "|\n";
			}
		}
		std::cout<<"\n"<<std::endl;
	}

	bool can_play(int m){
		// verifie si c'est un coup legal
		//int m = position(move);
		return board[m] == 0;

	}

	int turn(){
		int nb_de_zeros = 0;
		for (int i = 0; i < 9; i++){
			nb_de_zeros += (board[i] == 0);
		}
		if (nb_de_zeros % 2 == 0){
			return 2;
		}
		else {
			return 1;
		}
	}

	void play(int move){
		// modifie (donc joue dans) board si...

		if (can_play(move)){
			// ... si le coup est legal
			board[move] = turn();
		}
	}

	int verification(){
		// 2 si O gagne, 1 si X gagne, 0 si nulle, -1 si rien(pas de nulle on peut encore jouer)
		for (int i = 0; i < 3; i++){
			if (board[i*3] == board[i*3+1]  && board[i*3+1] == board[i*3+2] && board[i*3] != 0){ // alignement horizontal
				return board[i*3];
			}
			if (board[i] == board[i+3] && board[i+3] == board[i+6] == 1 && board[i] != 0){ // alignement vertical
				return board[i];
			}
		}
		if (board[0] == board[4] && board[4] == board[8] && board[0] != 0){ // alignement diagonal gauche haut vers droite bas
			return board[0];
		}
		if (board[2] == board[4] && board[4] == board[6] && board[2] != 0){ // alignement diagonal droite bas vers gauche haut
			return board[2];
		}
		int nb_de_zeros = 0;
			for (int i = 0; i < 9; i++){
				nb_de_zeros += (board[i] == 0);
			}
		if (nb_de_zeros == 0){
			return 0;
		}
		return -1;
	}
};