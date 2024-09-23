#include "app.h"
#include "game.h"
#include "psp-include.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION

int main(int argc, char *argv[])
{
    app_init("Don't Starve", 480, 272, 0);
    app_run(game_logic);

    return 0;
}