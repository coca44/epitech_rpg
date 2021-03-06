/*
** EPITECH PROJECT, 2017
** my_rpg
** File description:
** every function in relation with npc and loot info
*/

#include "my.h"
#include "get_next_line.h"
#include "parsing.h"

loot_info_t **realloc_loot(loot_info_t **loot, int nb_arg)
{
	loot_info_t **new_loot = malloc(sizeof(loot_info_t*) * (nb_arg + 1));

	if (new_loot == NULL)
		return (NULL);
	for (int i = 0; i < nb_arg; i++) {
		if ((new_loot[i] = malloc(sizeof(loot_info_t))) == NULL)
			return (NULL);
		if (loot != NULL && loot[i] != NULL) {
			new_loot[i]->loot_id = loot[i]->loot_id;
			new_loot[i]->loot_pos = loot[i]->loot_pos;
			new_loot[i]->event = loot[i]->event;
		}
	}
	new_loot[nb_arg] = NULL;
	for (int i = 0; loot != NULL && loot[i] != NULL; i++)
		free(loot[i]);
	if (loot != NULL)
		free(loot);
	return (new_loot);
}

npc_info_t *get_npc(npc_info_t *npc, char *buffer)
{
	if (!(match(buffer, NPC_INFO))) {
		return (NULL);
	}
	npc->npc_id = get_id(buffer);
	if (npc->npc_id <= 0) {
		free(npc);
		return (NULL);
	}
	npc->npc_pos = get_pos(buffer);
	npc->event = get_event(buffer);
	if (npc->event == NULL)
		return (NULL);
	return (npc);
}

scene_info_t *parse_npc_info(scene_info_t *scene, int fd, \
game_info_t *game_info, char **buffer)
{
	int i = 0;

	*buffer = get_next_line(fd);
	while (*buffer != NULL && *buffer[0] != '\0') {
		scene->npc = realloc_npc(scene->npc, i + 1);
		if (scene->npc == NULL) {
			free_game_info(game_info);
			return (NULL);
		}
		scene->npc[i] = get_npc(scene->npc[i], *buffer);
		if (scene->npc[i++] == NULL) {
			scene->npc = NULL;
			return (scene);
		}
		free(*buffer);
		*buffer = get_next_line(fd);
	}
	free(*buffer);
	*buffer = NULL;
	return (scene);
}

loot_info_t *get_loot(loot_info_t *loot, char *buffer)
{
	if (!(match(buffer, LOOT_INFO))) {
		return (NULL);
	}
	loot->loot_id = get_id(buffer);
	loot->loot_pos = get_pos(buffer);
	loot->event = get_event(buffer);
	if (loot->event == NULL)
		return (NULL);
	return (loot);
}

scene_info_t *parse_loot_info(scene_info_t *scene, int fd, \
game_info_t *game_info, char **buffer)
{
	int i = 0;

	if (scene->npc != NULL)
		*buffer = get_next_line(fd);
	while (*buffer != NULL && *buffer[0] != '\0') {
		scene->loot = realloc_loot(scene->loot, i + 1);
		if (scene->loot == NULL) {
			free_game_info(game_info);
			return (NULL);
		}
		scene->loot[i] = get_loot(scene->loot[i], *buffer);
		if (scene->loot[i++] == NULL) {
			scene->loot = NULL;
			return (scene);
		}
		free(*buffer);
		*buffer = get_next_line(fd);
	}
	free(*buffer);
	*buffer = NULL;
	return (scene);
}
