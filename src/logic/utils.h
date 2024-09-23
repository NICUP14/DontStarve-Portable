#include <app.h>
#include <psp-include.h>
#include <unistd.h>

#ifndef UTILS_H
#define UTILS_H

struct
{
    SDL_Texture *turf;
    SDL_Texture *desert_turf;
    SDL_Texture *wilson_front_tex;
    SDL_Texture *wilson_back_tex;
    SDL_Texture *wilson_left_tex;
    SDL_Texture *wilson_right_tex;
} resources;

enum direction_type
{
    DTYPE_SAME,
    DTYPE_UP,
    DTYPE_DOWN,
    DTYPE_LEFT,
    DTYPE_RIGHT,
    DTYPE_LEFT_UP,
    DTYPE_LEFT_DOWN,
    DTYPE_RIGHT_UP,
    DTYPE_RIGHT_DOWN,
};

enum entity_type
{
    ETYPE_PLAYER,
    ETYPE_TREE,
};

typedef struct
{
    void *data;
    enum entity_type type;
} entity_t;

typedef struct
{
    int x;
    int y;
    int width;
    int height;
    SDL_Texture *texture;
} sprite_t;

#define load_resource(path, sur, dst)                               \
    do                                                              \
    {                                                               \
        sur = load_image(path);                                     \
        dst = SDL_CreateTextureFromSurface(app_renderer(app), sur); \
        if (!dst)                                                   \
        {                                                           \
            app_log("Cannot import texture '%s'", path);            \
            return -1;                                              \
        }                                                           \
        SDL_FreeSurface(sur);                                       \
    } while (0);

int init_resources(void)
{
    SDL_Surface *surface;
    load_resource("assets/forest_turf.png", surface, resources.turf);
    load_resource("assets/desert_turf.png", surface, resources.desert_turf);
    load_resource("assets/wilson_front.png", surface, resources.wilson_front_tex);
    load_resource("assets/wilson_back.png", surface, resources.wilson_back_tex);
    load_resource("assets/wilson_left.png", surface, resources.wilson_left_tex);
    load_resource("assets/wilson_right.png", surface, resources.wilson_right_tex);
    return 0;
}

void draw_sprite(SDL_Texture *target, sprite_t *sprite)
{
    SDL_Rect quad = {sprite->x, sprite->y, sprite->width, sprite->height};
    SDL_SetRenderTarget(app_renderer(app), target);
    SDL_RenderCopy(app_renderer(app), sprite->texture, NULL, &quad);
    SDL_SetRenderTarget(app_renderer(app), NULL);
}

#endif