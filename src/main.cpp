#include "./../include/controllers/GameController.h"
#include "./../include/Constants.h"

#include <iostream>

int main()
{
    GameController &GameController = GameController::getInstance();
    GameController.startMenuLoop();

    return 0;
}
