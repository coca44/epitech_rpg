/*
** EPITECH PROJECT, 2017
** rpg
** File description:
** Main file for all pause stuff
*/

/* File created the 26/04/2018 at 13:20:28 by julian.frabel@epitech.eu */

#include "my_sfml.h"
#include "pause.h"

int goto_pause(sf_engine_t *engine, const char *scene)
{
	engine->pause.is_paused = true;
	engine->pause.scene_before_pause = engine->current_scene;
	engine->current_scene = engine->get_scene(engine, scene);
	if (engine->current_scene != NULL)
		engine->current_scene->load(engine, NULL);
	return (0);
}

void button_res(sf_button_t *button)
{
	quit_pause(button->engine);
}

int quit_pause(sf_engine_t *engine)
{
	if (engine->current_scene != NULL)
		engine->current_scene->unload(engine, NULL);
	engine->current_scene = engine->pause.scene_before_pause;
	engine->pause.scene_before_pause = NULL;
	engine->pause.is_paused = false;
	return (0);
}