#pragma once

// Ce fichier contient la définition de la structure représentant le plateau de jeu.

const int largeur = 3;

enum class Etat{
    VIDE,
    CROIX,
    ROND
};

struct Case{
    private :
    Etat etat = Etat::VIDE;

    public :
    void set_etat(Etat nouvel_etat);
    Etat get_etat();
};

struct plateau{
    private :
    Case cases[largeur][largeur];

    public :
    Etat verifier_victoire();
    void activer_case(int x, int y, Etat etat);
    void reset();
    void afficher();
};


