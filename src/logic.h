#include "app.h"
#include "psp-include.h"
#include <unistd.h>

enum entity_type {
    ETYPE_PLAYER,
    ETYPE_TREE,
};

typedef struct {
    void *data;
    enum entity_type type;
} entity_t;


typedef struct {
    int x;
    int y;
    int width;
    int height;
    SDL_Texture *texture;
} sprite_t;

typedef struct {
    SDL_Texture *walking_texture;
} player_t;

int init_player(player_t *player) {
    SDL_Surface *walking_surf = load_image("assets/Wilson.png");
    player->walking_texture = SDL_CreateTextureFromSurface(app.tex_renderer, walking_surf);
    if (!player->walking_texture) {
        app_log("Cannot import surface 'Wilson'\n");
        return -1;
    }

    SDL_FreeSurface(walking_surf);
    return 0;
}

sprite_t draw_player(player_t *player) {
    return (sprite_t) {
        .height = 50,
        .width = 50,
        .x = 50,
        .y = 50,
        .texture =player->walking_texture
    };
}

#define ENTITY_COUNT 128

struct {
    entity_t player;
    entity_t entities[ENTITY_COUNT];
} game;

// void game_render(void) {
//     sprite_t sprite = draw_player(game.player.data);
//     SDL_Rect quad = {sprite.x, sprite.y, sprite.width, sprite.height};
//     SDL_SetRenderTarget(app.tex_renderer, app.multi_renderer.background);
//     SDL_RenderCopy(app.tex_renderer, sprite.texture, &quad, NULL);
//     SDL_SetRenderTarget(app.tex_renderer, NULL);
// 
//     SDL_DestroyTexture(sprite.texture);
//     app_render();
// }

void game_logic(void) {
    // Create the scene
    // SDL_Rect fill_rect = {0, 0, app.width, app.height};
    // SDL_SetRenderTarget(app.tex_renderer, app.multi_renderer.background);
    // SDL_SetRenderDrawColor(app.tex_renderer, 112, 91, 42, 255);
    // SDL_RenderFillRect(app.tex_renderer, &fill_rect);
    // SDL_SetRenderTarget(app.tex_renderer, NULL);
    // SDL_RenderClear(app.tex_renderer);

    // player_t *player = malloc(sizeof(player_t));
    // init_player(player);
    // game.player.data = player;

    // Player
    int done = 0;
    while (!done) {
        // game_render();
        app_render();
        sleep(5);
    }
}