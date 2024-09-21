#include "psp-include.h"

typedef struct {
    SDL_Texture *effects;
    SDL_Texture *entities;
    SDL_Texture *background;
    SDL_Renderer *renderer;
} multi_renderer_t;

int init_multi_renderer(multi_renderer_t *multi_renderer, SDL_Window *window, int width, int height) {
    multi_renderer->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!multi_renderer->renderer) {
        return -1;
    }

    multi_renderer->background = SDL_CreateTexture(
        multi_renderer->renderer, 
        SDL_PIXELFORMAT_RGB888, 
        SDL_TEXTUREACCESS_STREAMING, 
        width, 
        height
    );

    multi_renderer->entities = SDL_CreateTexture(
        multi_renderer->renderer, 
        SDL_PIXELFORMAT_RGB888, 
        SDL_TEXTUREACCESS_STREAMING, 
        width, 
        height
    );

    multi_renderer->effects = SDL_CreateTexture(
        multi_renderer->renderer, 
        SDL_PIXELFORMAT_RGB888, 
        SDL_TEXTUREACCESS_STREAMING, 
        width, 
        height
    );

    if (!multi_renderer->background || !multi_renderer->entities || !multi_renderer->effects) {
        return -1;
    }

    return 0;
}

void free_multi_renderer(multi_renderer_t *multi_renderer) {
    SDL_DestroyTexture(multi_renderer->background);
    SDL_DestroyTexture(multi_renderer->entities);
    SDL_DestroyTexture(multi_renderer->effects);
    SDL_DestroyRenderer(multi_renderer->renderer);
}

void update_multi_renderer(const multi_renderer_t *multi_renderer) {
    SDL_RenderClear(multi_renderer->renderer);
    SDL_RenderCopy(multi_renderer->renderer, multi_renderer->background, NULL, NULL);
    SDL_RenderCopy(multi_renderer->renderer, multi_renderer->entities, NULL, NULL);
    SDL_RenderCopy(multi_renderer->renderer, multi_renderer->effects, NULL, NULL);
}

void show_multi_renderer(multi_renderer_t *multi_renderer) {
    SDL_RenderPresent(multi_renderer->renderer);
}