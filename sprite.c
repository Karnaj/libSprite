#include <stdio.h>
#include <SDL2/SDL.h>
#include "sprite.h"
#include "utils_sdl.h"


SDL_Surface *load_surface(const char path[])
{
    SDL_Surface *s = SDL_LoadBMP(path);
    if(NULL == s)
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
    return s;
}

s_sprite *load_sprite(char path[], SDL_Renderer *renderer, SDL_Color *key)
{
    s_sprite *sprite = malloc(sizeof(s_sprite));
    if(NULL == sprite)
    {
        perror("Error creating a new sprite : ");
        return NULL;
    }
    SDL_Surface *tmp = load_surface(path);
    if(NULL == tmp)
    {
        free(sprite);
        return NULL;
    }
    sprite->w = tmp->w;
    sprite->h = tmp->h;
    if(key)
        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, key->r, key->g, key->b));
    sprite->texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == sprite->texture)
    {
        fprintf(stderr, "Error creating sprite : %s.", SDL_GetError());
        return NULL;
    }
    return sprite;
}

s_sprite *free_sprite(s_sprite *sprite)
{
    if(sprite)
    {
        SDL_DestroyTexture(sprite->texture);
        free(sprite);
    }
    return NULL;
}

void display_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y)
{
    SDL_Rect dst = {x, y, sprite->w, sprite->h};
    SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
}

void display_scaled_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, double scale)
{
    SDL_Rect dst = {x, y, sprite->w * scale, sprite->h * scale};
    SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
}

void display_dscaled_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, double wscale, double hscale)
{
    SDL_Rect dst = {x * wscale, y * hscale, sprite->w * wscale, sprite->h * hscale};
    SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
}

void set_background_sprite(SDL_Renderer *renderer, s_sprite *sprite)
{
    SDL_RenderCopy(renderer, sprite->texture, NULL, NULL);
}

void display_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src)
{
    SDL_Rect dst = {x, y, src->w, src->h};
    SDL_RenderCopy(renderer, sprite->texture, src, &dst);
}

void display_scaled_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src, double scale)
{
    SDL_Rect dst = {x, y, src->w * scale, src->h * scale};
    SDL_RenderCopy(renderer, sprite->texture, src, &dst);
}

void display_dscaled_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src, double wscale, double hscale)
{
    SDL_Rect dst = {x * wscale, y * hscale, src->w * wscale, src->h * hscale};
    SDL_RenderCopy(renderer, sprite->texture, src, &dst);
}
