/*
** EPITECH PROJECT, 2017
** My rpg
** File description:
** The scene for the fighting system
*/

#include "rpg.h"

static int load_fight_scene(sf_engine_t *engine, parser_to_game_t *ptg)
{
	fight_t *fight = ptg->fight;
	sf_linked_list_t *current = fight->ennemies;
	int pos = 0;
	sf_vector_3d_t log_pos = {WINDOW_SIZE_X - 450, WINDOW_SIZE_Y - 450, 0};

	create_prefab_log(engine, log_pos, fight);
	create_prefab_fbackground(engine, fight);
	create_prefab_fplayer(engine, fight);
	engine->add_audio(engine, MUSIC_FIGHT, true);
	engine->play(engine, MUSIC_FIGHT);
	select_attack(engine, fight, true);
	while (current) {
		((fight_enemy_t *)(current->data))->go =\
create_prefab_fenemy(engine, current->data, pos, fight);
		pos++;
		current = current->next;
	}
	return (0);
}

static int loop_fight_scene(sf_engine_t *engine, UNUSED parser_to_game_t *data)
{
	sfEvent evt;

	if (engine == NULL)
		return (84);
	while (sfRenderWindow_pollEvent(engine->window, &evt)) {
		if (evt.type == sfEvtClosed)
			sfRenderWindow_close(engine->window);
	}
	return (0);
}

static int unload_fight_scene(sf_engine_t *engine, parser_to_game_t *data)
{
	if (engine == NULL)
		return (84);
	engine->stop(engine, MUSIC_FIGHT);
	reset_scene(engine->current_scene);
	data->fight = NULL;
	return (0);
}

sf_scene_t *create_fight_scene(sf_engine_t *engine, UNUSED fight_t *fight)
{
	sf_scene_t *new_scene = create_scene("fight");

	if (new_scene == NULL || engine == NULL)
		return (NULL);
	new_scene->load = &load_fight_scene;
	new_scene->loop = &loop_fight_scene;
	new_scene->unload = &unload_fight_scene;
	engine->add_scene(engine, new_scene);
	return (new_scene);
}