/*
** EPITECH PROJECT, 2017
** rpg
** File description:
** Fight callback
*/

/* File created the 11/05/2018 at 10:37:34 by julian.frabel@epitech.eu */

#include "my_sfml.h"
#include "rpg.h"

int end_fight_win(sf_engine_t *engine, gameobject_t *enemy)
{
	engine->destroy_gameobject(engine, enemy);
	return (0);
}

int end_fight_lose(sf_engine_t *engine, UNUSED gameobject_t *enemy, \
parser_to_game_t *ptg)
{
	sf_speak_t *dead = create_speak_component(NULL);

	dead->set_info(dead, DEATH_MESSAGE, FACE_HERO);
	dead->set_font(dead, FONT_SPEAK);
	ptg->active_scene = 1;
	ptg->player_start_pos = (sf_vector_3d_t){23 * TILE_SIZE, \
11 * TILE_SIZE, 0};
	engine->change_scene(engine, "game", ptg);
	update_selected_scene(engine);
	dead->show(dead, engine);
	return (0);
}

int end_callback_fight(UNUSED fight_t *fight, void *datas,\
bool win, sf_engine_t *engine)
{
	parser_to_game_t *ptg = engine->data;

	if (datas == NULL || ptg == NULL)
		return (84);
	ptg->come_from_fight = true;
	engine->change_scene(engine, "game", ptg);
	update_selected_scene(engine);
	if (win) {
		end_fight_win(engine, datas);
	} else {
		end_fight_lose(engine, datas, ptg);
	}
	return (0);
}