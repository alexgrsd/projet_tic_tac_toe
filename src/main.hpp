#pragma once
#include "player.hpp"
#include "plateau.hpp"
#include <string>

std::string game_name_ascii = R"(

 __     __    __     ______     ______     ______   ______     ______   
/\ \   /\ "-./  \   /\  __ \   /\  ___\   /\__  _\ /\  __ \   /\  ___\  
\ \ \  \ \ \-./\ \  \ \  __ \  \ \ \____  \/_/\ \/ \ \ \/\ \  \ \  __\  
 \ \_\  \ \_\ \ \_\  \ \_\ \_\  \ \_____\    \ \_\  \ \_____\  \ \_____\
  \/_/   \/_/  \/_/   \/_/\/_/   \/_____/     \/_/   \/_____/   \/_____/

)";

int jouer_tour(Player player, Board &board);


