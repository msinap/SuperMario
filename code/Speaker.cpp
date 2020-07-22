#include "Speaker.h"
using namespace std;

const string Speaker::baseAddress = "assets/sounds/sound_effects/";
const string Speaker::themeMusicAddress = "assets/sounds/Super Mario Bros. theme music.mp3";

Speaker::Speaker(){
}

void Speaker::play(SoundType s) {
    bool delayAfterSound = false;
    string address = baseAddress;
    switch (s) {
        case SoundType::marioJump:
            address += "jump-super";
            break;
        case SoundType::marioPowerUp:
            address += "powerup";
            break;
        case SoundType::mushroomAppear:
            address += "powerup-appears";
            break;
        case SoundType::marioDeath:
            address += "mario-death";
            delayAfterSound = true;
            break;
        case SoundType::coinAppear:
            address += "coin";
            break;
        case SoundType::brickBroken:
            address += "brick-smash";
            break;
        case SoundType::enemyHit:
            address += "enemy-stomp";
            break;
        case SoundType::gameOver:
            address += "gameover";
            delayAfterSound = true;
            break;
        case SoundType::win:
            address += "level-clear";
            delayAfterSound = true;
            break;
    }
    address += ".wav";
    win->play_sound_effect(address);
    if (delayAfterSound) {
        win->stop_music();
        delay(3000);
    }
}

void Speaker::setWindow(Window* w) {
    win = w;
}

void Speaker::playThemeMusic() {
    win->play_music(themeMusicAddress);
}
