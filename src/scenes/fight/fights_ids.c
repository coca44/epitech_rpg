/*
** EPITECH PROJECT, 2017
** My_rp
** File description:
** Fights
*/

#include "my_sfml.h"
#include "rpg.h"

fight_player_t *get_player_fight(sf_engine_t *engine)
{
	gameobject_t *player_go = engine->get_gameobject(engine, "player");
	sf_inventory_t *inv = get_component(player_go, INVENTORY);
	fight_player_t *player = NULL;
	sf_linked_list_t *attacks = NULL;

	if (player_go != NULL) {
		add_attack(&attacks, "Ultima Attack", 10 * inv->s_atk, 6);
		add_attack(&attacks, "Heavy Attack", 4 * inv->s_atk, 3);
		add_attack(&attacks, "Sword Attack", 1 * inv->s_atk, 1);
	}
	player = create_fight_player("assets/faces/player.png", attacks);
	if (player_go != NULL)
		(player->life) *= inv->hp;
	return (player);
}

fight_t *create_fight_enemys(fight_info_t info, sf_engine_t *engine, \
gameobject_t *enemy_go)
{
	fight_t *fight = NULL;
	fight_player_t *player_fight = get_player_fight(engine);
	fight_enemy_t *enemy = NULL;
	sf_linked_list_t *eattacks = NULL;
	monster_info_t monster;
	attack_info_t att;

	fight = create_fight(BACKGROUND_FIGHT_PATH, player_fight);
	fight->end_datas = enemy_go;
	fight->end_callback = &end_callback_fight;
	for (int i = 0; i < info.nb_monsters; i++) {
		monster = MONSTERS_IDS[info.monsters[i]];
		for (int j = 0; j < monster.nb_attacks; j++) {
			att = ATTACKS_IDS[monster.attacks[j]];
			add_attack(&eattacks, att.name, att.damage, att.cost);
		}
		enemy = create_enemy(monster.life, monster.sprite, \
monster.name, eattacks);
		fight->ennemies = sf_push(enemy, my_strdup("enemy"), \
fight->ennemies);
		eattacks = NULL;
	}
	return (fight);
}

int run_fight(int id, sf_engine_t *engine, gameobject_t *enemy)
{
	fight_t *fight = NULL;
	parser_to_game_t *ptg = engine->data;

	if (id > NB_FIGHTS_ID)
		return (84);
	fight = create_fight_enemys((FIGHTS_ID[id - 1]), engine, enemy);
	ptg->fight = fight;
	return (engine->change_scene(engine, "fight", ptg));
}