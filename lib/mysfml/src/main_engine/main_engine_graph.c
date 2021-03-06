/*
** EPITECH PROJECT, 2017
** my_sfml
** File description:
** Graphical related functions
*/

#include "my_sfml_core.h"
#include "my_sfml_engine.h"
#include <SFML/Graphics.h>

int render_main_engine(sf_engine_t *engine)
{
	int return_value = 0;

	if (engine == NULL || engine->current_scene == NULL) {
		my_putdebug("Render main engine:\n    ");
		my_putdebug(MSG_MY_SFML_ERR_NULL);
		return (84);
	}
	sfRenderWindow_clear(engine->window, sfBlack);
	if (engine->pause.is_paused && engine->pause.scene_before_pause != NULL)
		engine->pause.scene_before_pause->graphical_engine->render(\
engine->pause.scene_before_pause->graphical_engine, engine->window);
	return_value = engine->current_scene->graphical_engine->render(\
engine->current_scene->graphical_engine, engine->window);
	if (DISPLAY_HITBOX)
		display_hitbox(engine);
	if (DISPLAY_CAMERA_DEBUG)
		display_camera_debug(engine->current_scene->camera);
	sfRenderWindow_display(engine->window);
	return (return_value);
}

int add_to_layer_main_engine(sf_engine_t *engine, int layer, void **data)
{
	if (engine == NULL || data == NULL) {
		my_putdebug("Render main engine:\n    ");
		my_putdebug(MSG_MY_SFML_ERR_NULL);
		return (84);
	}
	if (engine->current_scene == NULL)
		return (84);
	return (engine->current_scene->graphical_engine->add_to_layer(\
engine->current_scene->graphical_engine, layer, data));
}

int load_texture_main_engine(sf_engine_t *engine, char const *path)
{
	if (engine == NULL || path == NULL) {
		my_putdebug("Render main engine:\n    ");
		my_putdebug(MSG_MY_SFML_ERR_NULL);
		return (84);
	}
	if (engine->current_scene == NULL)
		return (84);
	return (engine->current_scene->graphical_engine->load_texture(\
engine->current_scene->graphical_engine, path));
}

sfTexture *get_texture_main_engine(sf_engine_t *engine, char const *id)
{
	if (engine == NULL || id == NULL) {
		my_putdebug("Render main engine:\n    ");
		my_putdebug(MSG_MY_SFML_ERR_NULL);
		return (NULL);
	}
	if (engine->current_scene == NULL)
		return (NULL);
	return (engine->current_scene->graphical_engine->get_texture(\
engine->current_scene->graphical_engine, id));
}

int main_engine_set_layer_type(sf_engine_t *engine, int priority, \
layer_render_type_t new_type)
{
	if (engine == NULL) {
		my_putdebug("Render main engine:\n    ");
		my_putdebug(MSG_MY_SFML_ERR_NULL);
		return (84);
	}
	if (engine->current_scene == NULL)
		return (84);
	return (engine->current_scene->graphical_engine->set_type(\
engine->current_scene->graphical_engine, priority, new_type));
}