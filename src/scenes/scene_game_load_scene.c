/*
** EPITECH PROJECT, 2017
** rpg
** File description:
** Load a scene (from the parsing)
*/

/* File created the 24/04/2018 at 13:41:45 by julian.frabel@epitech.eu */

#include "rpg.h"

void load_parsing_to_game_scene(parser_to_game_t *ptg, sf_engine_t *engine)
{
	scene_info_t *scene = ptg->game_info->scene[ptg->active_scene];

	if (scene == NULL)
		return;
	for (int i = 0; scene->tile != NULL && scene->tile[i] != NULL; i++) {
		create_prefab_tile(engine, scene->tile[i], scene->tileset);
	}
}