#ifndef SPRITE_H
#define SPRITE_H
 
#include <SDL2/SDL.h>


typedef struct s_sprite s_sprite;


struct s_sprite
{
    SDL_Texture *texture;
    unsigned int w, h;
};


SDL_Surface *load_surface(const char path[])
s_sprite *load_sprite(char path[], SDL_Renderer *renderer, SDL_Color *key);
s_sprite *free_sprite(s_sprite *sprite);
void display_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y);
void display_scaled_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, double scale);
void display_dscaled_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, double wscale, double hscale);
void set_background_sprite(SDL_Renderer *renderer, s_sprite *sprite);
void display_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src);
void display_scaled_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src, double scale);
void display_dscaled_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src, double wscale, double hscale);

#endif
