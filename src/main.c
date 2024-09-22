#include "app.h"
#include "logic.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION

int main(int argc, char *argv[]) {
    app_init("Don't Starve", 272, 480, 0);
    app_run(game_logic);
    app_exit();

    return 0;
}