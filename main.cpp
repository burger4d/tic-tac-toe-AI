#include <iostream>
#include <algorithm>
#include "morpion.h"

int minimax(Board b){
	if (b.verification() >= 0){
		// si b est une feuille
		if (b.verification() == 2){
			return -1;
		}
		else {
			return b.verification();		}
	}
	int val = 0;
	if (b.turn() == 1){
		// si X de jouer (maximizing player)
		val = -1;
		for (int i = 0; i < 9; i++){
			if (b.can_play(i)){//parmi les coups legaux
				Board child = b;
				child.play(i);
				val = std::max(val, minimax(child));
			}
		}
	}
	else {
		val = 1;
		for (int i = 0; i < 9; i++){
			if (b.can_play(i)){//parmi les coups legaux
				Board child = b;
				child.play(i);
				val = std::min(val, minimax(child));
			}
		}
	}
	return val;
}

int playO(Board coord){
	int val = 1;
	int val2 = 1;
	int new_move = 0;
	for (int i = 0; i < 9; i++){
		if (coord.can_play(i) == 1){//parmi les coups legaux
			Board child = coord;
			child.play(i);
			val2 = minimax(child);
			if (val2 <= val){
				val = val2;
				new_move = i;
				}
			}
		}
	return new_move;
}
int playX(Board coord){
	int val = -1;
	int val2 = -1;
	int new_move = 0;
	for (int i = 0; i < 9; i++){
		if (coord.can_play(i) == 1){//parmi les coups legaux
			Board child = coord;
			child.play(i);
			val2 = minimax(child);
			if (val2 >= val){
				val = val2;
				new_move = i;
				}
			}
		}
	return new_move;
}

int main(){
	int c = 1;
	int config = 1;
	std::cout << "Avant de jouer, choisissez l'une des deux configurations:\n1)|7|8|9| 2)|1|2|3|\n  |4|5|6|   |4|5|6|\n  |1|2|3|   |7|8|9|" << std::endl;
	std::cin >> config;
	if (config != 2){
		config = 1;
	}
	while (true){
		std::cout << "1) player vs player\n2) player vs AI\n3) AI vs player" << std::endl;
		std::cin >> c;
		Board coord = Board();
		coord.configuration(config);
		switch (c){
			case 2:
			while (coord.verification() == -1){
				coord.draw();
				int n;
				std::cin >> n;
				coord.play(coord.position(n));
				if (coord.verification() != -1){
					break;
				}
				else {
					coord.draw();
					coord.play(playO(coord));
				}
			}
			break;
			case 3:
			while (coord.verification() == -1){
				coord.draw();
				coord.play(playX(coord));
				if (coord.verification() != -1){
					break;
				}
				else {
					coord.draw();
					int n;
					std::cin >> n;
					coord.play(coord.position(n));
				}
			}
			break;
			default:
			while (coord.verification() == -1){
				coord.draw();
				int n;
				std::cin >> n;
				coord.play(coord.position(n));
			}
		}
		coord.draw();
		switch (coord.verification()){
			case 0:
			std::cout << "match nul" << std::endl;
			break;
			case 1:
			std::cout << "le joueur X gagne" << std::endl;
			break;
			default:
			std::cout << "le joueur O gagne" << std::endl;
		}
		c = 1;
		std::cout << "Rejouer?\n1) oui\n2) non" << std::endl;
		std::cin >> c;
		if (c == 2){
			break;
		}
	}
	return 0;
}