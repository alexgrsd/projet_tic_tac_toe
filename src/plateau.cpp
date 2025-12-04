#include "plateau.hpp"
#include <iostream>

void Case::set_etat(Etat nouvel_etat) {
    etat = nouvel_etat;
}
Etat Case::get_etat() {
    return etat;
}

Etat plateau::verifier_victoire() {
    Etat c[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            c[i][j] = cases[i][j].get_etat();

    // Vérification des lignes
    for (int i = 0; i < 3; ++i)
        if (c[i][0] != Etat::VIDE && c[i][0] == c[i][1] && c[i][1] == c[i][2])
            return c[i][0];

    // Vérification des colonnes
    for (int j = 0; j < 3; ++j)
        if (c[0][j] != Etat::VIDE && c[0][j] == c[1][j] && c[1][j] == c[2][j])
            return c[0][j];

    // Vérification des diagonales
    if (c[0][0] != Etat::VIDE && c[0][0] == c[1][1] && c[1][1] == c[2][2])
        return c[0][0];

    if (c[0][2] != Etat::VIDE && c[0][2] == c[1][1] && c[1][1] == c[2][0])
        return c[0][2];

    return Etat::VIDE;
}

void plateau::activer_case(int x, int y, Etat etat) {
    if (plateau::cases[x][y].get_etat() != Etat::VIDE) {
        return; // Case déjà occupée
        
    }
    if (x >= 0 && x < largeur && y >= 0 && y < largeur) {
        cases[x][y].set_etat(etat);
    }
}
void plateau::reset() {
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            cases[i][j].set_etat(Etat::VIDE);
        }
    }
}
void plateau::afficher() {

    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            Etat etat = cases[i][j].get_etat();
            char symbole;
            switch (etat) {
                case Etat::VIDE:
                    symbole = '.';
                    break;
                case Etat::CROIX:
                    symbole = 'X';
                    break;
                case Etat::ROND:
                    symbole = 'O';
                    break;
            }
            std::cout << symbole << " ";
        }
        std::cout << std::endl;
    }
}

