#include <psp-include.h>
#include <logic/player.h>
#include <logic/land.h>

struct
{
    int angle;
    land_t land;
    player_t player;
} game;

void render_game(void)
{
    sprite_t land_sprite = draw_land(&game.land, game.angle);
    sprite_t player_sprite = draw_player(&game.player);
    draw_sprite(app_background, &land_sprite);
    draw_sprite(app_entities, &player_sprite);
    app_render();
}

void game_logic(void)
{
    game.player.x = 0;
    game.player.y = 0;

    init_resources();
    init_land(&game.land, 10, 10);

    SDL_Event event;
    const Uint8 *state;
    enum direction_type dir;
    Uint32 curr_time;
    Uint32 last_time;
    float delta_time;

    while (1)
    {
        SDL_PollEvent(&event);

        dir = DTYPE_SAME;
        state = SDL_GetKeyboardState(NULL);

        curr_time = SDL_GetTicks();
        delta_time = (curr_time - last_time) / 1000.0f;
        last_time = curr_time;

        if (state[SDL_SCANCODE_ESCAPE])
            break;
        if (state[SDL_SCANCODE_0])
            game.angle = (game.angle + 45) % 360;
        else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
            dir = DTYPE_LEFT_UP;
        else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
            dir = DTYPE_RIGHT_UP;
        else if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT])
            dir = DTYPE_LEFT_DOWN;
        else if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT])
            dir = DTYPE_RIGHT_DOWN;
        else if (state[SDL_SCANCODE_UP])
            dir = DTYPE_UP;
        else if (state[SDL_SCANCODE_DOWN])
            dir = DTYPE_DOWN;
        else if (state[SDL_SCANCODE_LEFT])
            dir = DTYPE_LEFT;
        else if (state[SDL_SCANCODE_RIGHT])
            dir = DTYPE_RIGHT;

        move_player(&game.player, dir, delta_time);
        render_game();
    }
}