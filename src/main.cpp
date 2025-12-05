#include "main.hpp"
#include "plateau.hpp"
#include "player.hpp"
#include <iostream>

int play_turn(Player current_player, Board &board){
        
    std::string input;
    int x, y;    
    std::vector<int> coordinates;
    int num;
    std::cout << "Enter coordinates (x y): ";
    while (std::cin >> num) {
        coordinates.push_back(num);
        if (std::cin.peek() == '\n') {
            break;
        }
        for (size_t i = 0; i < coordinates.size(); ++i) {
            std::cout << "Coordinate " << i << " : " << coordinates[i] << std::endl;
        }
    }
    std::cin.clear(); // Clear the fail state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (coordinates.size() != 2) {
        std::cout << "Please enter exactly two integers for coordinates." << std::endl;
        board.print_board();
        return 1;
    }
    x = coordinates[0];
    y = coordinates[1];
    int verif = board.activate_case(y, x, current_player.get_symbol());
    if (verif == 1) {
        std::cout << "Case déjà occupée. Reessayez." << std::endl;
        board.print_board();
        return 1;
    }
    else if (verif == 2) {
        std::cout << "Coordonnées invalides. Reessayez." << std::endl;
        board.print_board();
        return 1;
    }
    board.print_board();
    coordinates.clear();
    return 0;
}



int main() {
    std::cout << game_name_ascii << std::endl;
    
    Board board;
    board.print_board();
    int tour = 0;

    while (board.verify_victory() == 0){
        int joueur_courant = (tour % 2 == 0) ? 1 : 2;
        std::cout << "Tour du joueur " << ((joueur_courant == 1) ? "CROIX" : "ROND") << std::endl;
        int result = play_turn(joueur_courant, board);
        if (result != 0) {
            continue; // Rejouer le même joueur en cas d'erreur
        }
        tour++;
    }
    int gagnant = board.verify_victory();
    if (gagnant != 0) {
        std::cout << "Le joueur " << ((gagnant == 1) ? "CROIX" : "ROND") << " a gagné!" << std::endl;
    } else {
        std::cout << "Match nul!" << std::endl;
    }


    return 0;
}