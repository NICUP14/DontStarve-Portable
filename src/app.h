// Application header - A unified interface for managing SDL2 windows

#include <stdio.h>
#include "psp-include.h"
#include "multi-render.h"

#ifndef APP_H
#define APP_H

typedef struct
{
    int width;
    int height;
    const char *title;
    SDL_Joystick *joystick;
    SDL_Window *window;
    SDL_Renderer *tex_renderer;
    multi_renderer_t multi_renderer;
} app_t;

app_t app;

#define app_log(...)               \
    do                             \
    {                              \
        SDL_Log("%s_", app.title); \
        SDL_Log(__VA_ARGS__);      \
    } while (0);

#define app_renderer(app) app.multi_renderer.renderer
#define app_background app.multi_renderer.background
#define app_entities app.multi_renderer.entities

int app_init(const char *title, int width, int height, int flags)
{
    app.title = title;
    app.width = width;
    app.height = height;

    // SET THIS TO ACTIVATE joystick
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0)
    {
        app_log("SDL_Init: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // create an SDL window (pspgl enabled)
    app.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!app.window)
    {
        app_log("SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // create the multi-renderer (OpenGL ES2)
    if (init_multi_renderer(&app.multi_renderer, app.window, width, height) < 0)
    {
        app_log("Failed initializing multi_renderer\n");
        SDL_Quit();
        return -1;
    }

    if (SDL_NumJoysticks() < 1)
        app_log("No joysticks connected: %s\n", SDL_GetError());

    app.joystick = SDL_JoystickOpen(0);
    if (app.joystick == NULL)
    {
        app_log("SDL_JoystickOpen: %s\n", SDL_GetError());
        // SDL_Quit();
        // return -1;
    }

    return 0;
}

void app_render()
{
    update_multi_renderer(&app.multi_renderer);
    show_multi_renderer(&app.multi_renderer);
}

void app_free(void)
{
    SDL_CloseAudio();
    SDL_JoystickClose(app.joystick);
    SDL_DestroyWindow(app.window);
    free_multi_renderer(&app.multi_renderer);
}

void app_exit(void)
{
    app_free();
    SDL_Quit();

#ifdef PSP_BUILD
    sceKernelExitGame();
#endif
}

void app_run(void (*app_loop)(void))
{
    (*app_loop)();
    app_exit();
}

#endif