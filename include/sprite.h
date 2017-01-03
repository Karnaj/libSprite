#ifndef SPRITE_H
#define SPRITE_H
 
#include <SDL2/SDL.h>

/**
 * \struct s_sprite
 * \brief Structure représentant un sprite.
 *
 * Sprite est une structure contenant une texture,
 * la hauteur et la largeur du sprite.
 */
 
struct s_sprite
{
    SDL_Texture *texture; /*!< La texture du sprite. */
    int w; /*!< La largeur du sprite. */
	int h; /*!< La hauteur du sprite. */
};
typedef struct s_sprite s_sprite;

void destroy_sprite(s_sprite *sprite);
s_sprite *create_sprite_from_surface(SDL_Renderer *renderer, SDL_Surface *surface);
s_sprite *create_sprite_from_bmp(SDL_Renderer *renderer, char path[]);
s_sprite *create_sprite_from_bmp_with_color_key(SDL_Renderer *renderer, char path[], SDL_Color c);

int display_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y);
int display_scaled_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, int scale);
int display_sprite_in_background(SDL_Renderer *renderer, s_sprite *sprite);
int display_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src);
int display_scaled_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src, int scale);
int display_cliped_sprite_in_background(SDL_Renderer *renderer, s_sprite *sprite, SDL_Rect *src);

extern SDL_Surface *load_surface(const char path[]);
#endif
