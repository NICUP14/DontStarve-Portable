#include "psp-include.h"
#include "logic/utils.h"

#define PLAYER_SPEED 100

typedef struct
{
    int x;
    int y;
    enum direction_type dir;
} player_t;

void move_player(player_t *player, enum direction_type dir, float delta_time)
{
    if (dir == DTYPE_SAME)
        return;

    int x_off = 0;
    int y_off = 0;

    if (dir == DTYPE_UP || dir == DTYPE_LEFT_UP || dir == DTYPE_RIGHT_UP)
        y_off = -PLAYER_SPEED;
    else if (dir == DTYPE_DOWN || dir == DTYPE_LEFT_DOWN || dir == DTYPE_RIGHT_DOWN)
        y_off = PLAYER_SPEED;

    if (dir == DTYPE_LEFT || dir == DTYPE_LEFT_UP || dir == DTYPE_LEFT_DOWN)
        x_off = -PLAYER_SPEED;
    else if (dir == DTYPE_RIGHT || dir == DTYPE_RIGHT_UP || dir == DTYPE_RIGHT_DOWN)
        x_off = PLAYER_SPEED;

    app_log("x_off: %d, y_off: %d, delta: %f", x_off, y_off, delta_time);
    player->dir = dir;
    player->x += (int)(x_off * delta_time);
    player->y += (int)(y_off * delta_time);
}

sprite_t draw_player(player_t *player)
{
    int width;
    int height;
    int access;
    Uint32 format;
    SDL_QueryTexture(resources.wilson_front_tex, &format, &access, &width, &height);

    SDL_Texture *texture = resources.wilson_front_tex;
    if (player->dir == DTYPE_DOWN || player->dir == DTYPE_LEFT_DOWN || player->dir == DTYPE_RIGHT_DOWN)
        texture = resources.wilson_front_tex;
    else if (player->dir == DTYPE_UP || player->dir == DTYPE_LEFT_UP || player->dir == DTYPE_RIGHT_UP)
        texture = resources.wilson_back_tex;
    else if (player->dir == DTYPE_LEFT)
        texture = resources.wilson_left_tex;
    else if (player->dir == DTYPE_RIGHT)
        texture = resources.wilson_right_tex;

    return (sprite_t){
        .height = height,
        .width = width,
        .x = player->x,
        .y = player->y,
        .texture = texture};
}
