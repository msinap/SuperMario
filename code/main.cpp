#include "utility.h"
#include "../src/rsdl.hpp"
#include "Game.h"
using namespace std;

void checkArgc(int argc) {
    if (argc != 2) {
        cout << "Expected Map Address" << endl;
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    checkArgc(argc);

    Camera cam;
    Speaker speaker;
    Keyboard keyboard;
    Player player(argv[1]);
    while (true) {
        try {
            Game game(&player, &cam, &speaker, &keyboard);
            cam.resetPos();
            player.setGame(&game);
            game.run();
        }catch(LoseCondition e) {
            player.decreaseLiveCount();
            if (player.getLiveCount() == 0)
                break;
        }catch(WinCondition e) {
            break;
        }
    }
    if (player.getLiveCount() == 0) {
        player.showMessage(textType::GameOver, &cam);
    }else {
        player.showMessage(textType::Win, &cam);
    }
}
