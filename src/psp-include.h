#ifndef PSP_INCLUDE_H
#define PSP_INCLUDE_H

#ifdef PSP_BUILD
// Fixes missing '__ctype_ptr__'
extern const char _ctype_[];
const char* __ctype_ptr__ = _ctype_;

#include <pspkernel.h>
#include <pspdebug.h>

PSP_MODULE_INFO("SDL2", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include "stb_image.h"


// Thanks to BlastlessAnthony on github!
SDL_Surface *load_image(const char *filename) {
  int width = 0;
  int height = 0;
  int bytes_per_pixel =
      0; // Since we work with bytes instead of bits here in C.

  // Now the good stuff:
  Uint8 *data = stbi_load(filename, &width, &height, &bytes_per_pixel, 0);

  // What is a "pitch"? Its the "Dot Pitch" of an computer image.
  // Taken from https://en.wikipedia.org/wiki/Dot_pitch
  // Dot pitch (sometimes called line pitch, stripe pitch, or phosphor pitch) is
  // a specification for a computer display, computer printer, image scanner, or
  // other pixel-based devices that describe the distance, for example, between
  // dots (sub-pixels) on a display screen.
  Sint32 dot_pitch = width * bytes_per_pixel;
  dot_pitch = (dot_pitch + 3) & ~3;

  int red_mask;
  int green_mask;
  int blue_mask;
  int alpha_mask;

  // This only works with little endian computer processors,
  // if you want support for big endian (if you even still use it), implement it
  // yourself.
  red_mask = 0x000000FF;
  green_mask = 0x0000FF00;
  blue_mask = 0x00FF0000;
  alpha_mask = (bytes_per_pixel == 4) ? 0xFF000000 : 0;

  // Now finally we can get that damn surface.
  SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(
      data, width, height, bytes_per_pixel * 8, dot_pitch, red_mask, green_mask,
      blue_mask, alpha_mask);
  if (!surface) {
    SDL_free(data);
    return NULL;
  }

  return surface;
}
#endif