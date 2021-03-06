/*
** EPITECH PROJECT, 2017
** rpg
** File description:
** Functions run at the end of a speak
*/

/* File created the 10/05/2018 at 13:50:28 by julian.frabel@epitech.eu */

#include "rpg.h"

int give_sword(sf_engine_t *engine, UNUSED gameobject_t *parent)
{
	gameobject_t *player = engine->get_gameobject(engine, "player");
	sf_inventory_t *inv = get_component(player, INVENTORY);
	sf_speak_t *guard = create_speak_component(NULL);

	if (guard == NULL)
		return (0);
	if (inv && inv->retrieve_item(inv, &(ITEM_LIST[ITEM_SWORD])) == -1) {
		inv->add_item(inv, &(ITEM_LIST[ITEM_SWORD]));
		guard->set_info(guard, "It's dangerous to go alone! \
Take this.", FACE_SOLDIER);
		guard->set_font(guard, FONT_SPEAK);
		guard->show(guard, engine);
	} else {
		guard->set_info(guard, "Time is counted", FACE_SOLDIER);
		guard->set_font(guard, FONT_SPEAK);
		guard->show(guard, engine);
	}
	return (0);
}

int give_potions(sf_engine_t *engine, UNUSED gameobject_t *parent)
{
	static bool potion_given = false;
	gameobject_t *player = engine->get_gameobject(engine, "player");
	sf_inventory_t *inv = get_component(player, INVENTORY);
	sf_speak_t *speak = create_speak_component(NULL);

	speak->set_font(speak, FONT_SPEAK);
	if (inv != NULL && potion_given == false) {
		inv->add_item(inv, &(ITEM_LIST[ITEM_POTION_STR]));
		inv->add_item(inv, &(ITEM_LIST[ITEM_POTION_DEX]));
		inv->add_item(inv, &(ITEM_LIST[ITEM_POTION_EXP]));
		potion_given = true;
		speak->set_info(speak, POTION_DIALOG, FACE_HERO);
		speak->show(speak, engine);
	} else {
		speak->set_info(speak, "There is nothing in it", FACE_HERO);
		speak->show(speak, engine);
	}
	return (0);
}

int king_end_game(sf_engine_t *engine, UNUSED gameobject_t *parent)
{
	return (engine->change_scene(engine, "end", engine->data));
}

int evil_king_fight(sf_engine_t *engine, gameobject_t *parent)
{
	run_fight(2, engine, parent);
	return (0);
}