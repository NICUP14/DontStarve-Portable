#ifndef PSP_INCLUDE_H
#define PSP_INCLUDE_H

// Fix for missing __ctype_ptr__
extern const char _ctype_[];
const char* __ctype_ptr__ = _ctype_;

#include <pspkernel.h>
#include <pspdebug.h>
#include <SDL2/SDL.h>

PSP_MODULE_INFO("SDL2", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#endif