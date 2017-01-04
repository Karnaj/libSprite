/**
 * \file sprite.c
 * \brief Fonctions utilitaires pour gérer des sprites avec la SDL.
 * \author Karnaj
 *
 * Bibliothèque très simple de gestion de sprites. Elle comporte des fonctions de création, d’affichage, etc.
 *
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include "sprite.h"

/**
 * \fn void destroy_sprite(s_sprite *sprite)
 * \brief Détruit un sprite.
 *
 * \param sprite Le sprite à détruire
 * 
 * Le sprite à détruire peut-être NULL, dans ce cas, la fonction ne faire rien.
 */
void destroy_sprite(s_sprite *sprite)
{
    if(sprite)
    {
        if(sprite->texture)
            SDL_DestroyTexture(sprite->texture);
        free(sprite);
    }
}

/**
 * \fn s_sprite *create_sprite_from_surface(SDL_Renderer *renderer, SDL_Surface *surface)
 * \brief Crée un sprite à partir d’une surface.
 *
 * \param renderer Le Renderer auquel le sprite doit être associée.
 * \param surface La surface à partir de laquelle le sprite doit être créé.
 * 
 * \return Le sprite créé, `NULL` en cas d’erreur.
 *
 * ## Remarques
 * La surface n’est pas modifiée ni libérée par la fonction.
 *
 */
s_sprite *create_sprite_from_surface(SDL_Renderer *renderer, SDL_Surface *surface)
{
    s_sprite *sprite = malloc(sizeof(s_sprite));
    if(NULL == sprite)
    {
        perror("Error creating sprite : ");
        return NULL;
    }
    sprite->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(NULL == sprite->texture)
    {
        fprintf(stderr, "Error creating sprite : %s.", SDL_GetError());
        return NULL;
    }
    sprite->w = surface->w;
    sprite->h = surface->h;
    return sprite;
}

/**
 * \fn s_sprite *create_sprite_from_bmp(SDL_Renderer *renderer, char path[])
 * \brief Crée une sprite à partir d’un fichier bmp.
 *
 * \param renderer Le Renderer auquel le sprite doit être associée.
 * \param path Le chemin de l’image à charger.
 * 
 * \return Le sprite créé, `NULL` en cas d’erreur.
 *
 *
 */
s_sprite *create_sprite_from_bmp(SDL_Renderer *renderer, char path[])
{
    SDL_Surface *tmp = load_surface(path);
    if(NULL == tmp)
        return NULL;
    return create_sprite_from_surface(renderer, tmp);
}

/**
 * \fn s_sprite *create_sprite_from_surface_with_color_key(SDL_Renderer *renderer, SDL_Surface *surface)
 * \brief Crée un sprite à partir d’une surface.
 *
 * \param renderer Le Renderer auquel le sprite doit être associée.
 * \param surface La surface à partir de laquelle le sprite doit être créé.
 * 
 * \return Le sprite créé, `NULL` en cas d’erreur.
 *
 * ## Remarques
 * La surface n’est pas modifiée ni libérée par la fonction.
 *
 */
s_sprite *create_sprite_from_surface_with_color_key(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Color color)
{
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(tmp->format, color.r, color.g, color.b));
    return create_sprite_from_surface(renderer, tmp);
}

/**
 * \fn s_sprite *create_sprite_from_bmp_with_color_key(SDL_Renderer *renderer, char path[], SDL_Color color)
 * \brief Crée une sprite à partir d’un fichier bmp.
 *
 * \param renderer Le Renderer auquel le sprite doit être associée.
 * \param path Le chemin de l’image à charger.
 * \param color La couleur qui doit être transparente.
 *
 * \return Le sprite créé, `NULL` en cas d’erreur.
 *
 */
s_sprite *create_sprite_from_bmp_with_color_key(SDL_Renderer *renderer, char path[], SDL_Color color)
{
    SDL_Surface *tmp = load_surface(path);
    if(NULL == tmp)
        return NULL;
    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, color.r, color.g, color.b));
    return create_sprite_from_surface(renderer, tmp);
}

/**
 * \fn int display_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y)
 * \brief Affiche un sprite.
 *
 * \param renderer Le renderer auquel est associé le sprite.
 * \param sprite Le sprite à afficher
 * \param x L’abscisse à laquelle afficher le sprite.
 * \param y L’ordonnée à laquelle afficher le sprite.
 *
 * \return 0 en cas de succès, une valeur négative en cas d’erreur.
 
 */
int display_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y)
{
    SDL_Rect dst = {x, y, sprite->w, sprite->h};
    return SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
}

/**
 * \fn int display_scaled_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, int xscale, int yscale)
 * \brief Affiche un sprite en le redimensionnant.
 *
 * \param renderer Le renderer auquel est associé le sprite.
 * \param sprite Le sprite à afficher
 * \param x L’abscisse à laquelle afficher le sprite.
 * \param y L’ordonnée à laquelle afficher le sprite.
 * \param xscale Le coefficient de redimensionnement en longueur.
 * \param yscale Le coefficient de redimensionnement en hauteur.
 * 
 * \return 0 en cas de succès, une valeur négative en cas d’erreur.
 *
 * ## Remarques
 * Si `xscale` et `yscale` valent `1`, appeler `display_scaled_sprite` revient à appeler `display_sprite`. 
 *
 */
int display_scaled_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, int xscale, int yscale)
{
    SDL_Rect dst = {x, y, sprite->w * xscale, sprite->h * yscale};
    return SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
}

/**
 * \fn int display_sprite_in_background(SDL_Renderer *renderer, s_sprite *sprite)
 * \brief Affiche un sprite en fond de fenêtre.
 *
 * \param renderer Le renderer auquel est associé le sprite.
 * \param sprite Le sprite à afficher
 *
 * \return 0 en cas de succès, une valeur négative en cas d’erreur.
 * 
 */
int display_sprite_in_background(SDL_Renderer *renderer, s_sprite *sprite)
{
    return SDL_RenderCopy(renderer, sprite->texture, NULL, NULL);
}

/**
 * \fn int display_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src)
 * \brief Affiche une partie d’un sprite.
 *
 * \param renderer Le renderer auquel est associé le sprite.
 * \param sprite Le sprite à afficher
 * \param x L’abscisse à laquelle afficher le sprite.
 * \param y L’ordonnée à laquelle afficher le sprite.
 * \param src Un pointeur sur `SDL_Rect` représentant la partie du sprite à afficher.
 *
 * \return 0 en cas de succès, une valeur négative en cas d’erreur.
 *
 * ## Remarques
 * Si `src` vaut `NULL`, toute la surface sera affichée (revient à utiliser `display_sprite`).
 *
 */
int display_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src)
{
    SDL_Rect dst = {x, y, src->w, src->h};
    return SDL_RenderCopy(renderer, sprite->texture, src, &dst);
}

/**
 * \fn int display_scaled_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src, int xscale, int yscale)
 * \brief Affiche une partie d’un sprite en le redimensionnant.
 *
 * \param renderer Le renderer auquel est associé le sprite.
 * \param sprite Le sprite à afficher
 * \param x L’abscisse à laquelle afficher le sprite.
 * \param y L’ordonnée à laquelle afficher le sprite.
 * \param src Un pointeur sur `SDL_Rect` représentant la partie du sprite à afficher.
 * \param xscale Le coefficient de redimensionnement en longueur.
 * \param yscale Le coefficient de redimensionnement en hauteur.
 *
 * \return 0 en cas de succès, une valeur négative en cas d’erreur.
 *
 * ## Remarques
 * - La partie du sprite qui sera affiché est celle correspondant à `src` sur le sprite original (non redimensionné).
 * - Si `src` vaut `NULL`, toute la surface sera affichée (revient à utiliser `display_scaled_sprite`).
 * - Si `xscale` et `yscale` valent `1`, revient à utiliser `display_cliped_sprite`.
 *
 */
int display_scaled_cliped_sprite(SDL_Renderer *renderer, s_sprite *sprite, int x, int y, SDL_Rect *src, int xscale, int yscale)
{
    SDL_Rect dst = {x, y, src->w * xscale, src->h * yscale};
    return SDL_RenderCopy(renderer, sprite->texture, src, &dst);
}

/**
 * \fn int display_cliped_sprite_in_background(SDL_Renderer *renderer, s_sprite *sprite, SDL_Rect *src)
 * \brief Affiche une partie d’un sprite en fond de fenêtre.
 *
 * \param renderer Le renderer auquel est associé le sprite.
 * \param sprite Le sprite à afficher
 * \param src Un pointeur sur `SDL_Rect` représentant la partie du sprite à afficher.
 *
 * \return 0 en cas de succès, une valeur négative en cas d’erreur.
 *
 * ## Remarques
 * - La partie du sprite qui sera affiché est celle correspondant à `src` sur le sprite original.
 * - Si `src` vaut `NULL`, toute la surface sera affichée (revient à utiliser `display_sprite_in_background`).
 *
 */
int display_cliped_sprite_in_background(SDL_Renderer *renderer, s_sprite *sprite, SDL_Rect *src)
{
    return SDL_RenderCopy(renderer, sprite->texture, src, NULL);
}
