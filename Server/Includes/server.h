/*
** server.h for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:16 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:16 2015 Dany Bouca Nova
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/select.h>
# include "common.h"

# define FAIL		-1
# define NONE		0
# define MATCH		1
# define STONE_DENSITY	60
# define FOOD_DENSITY	40
# define MSG1		"usage: ./zappy [-p port [-x size_x] [-y size_y] \
[-c max_clients] [-t speed] -n team_1 team_2 ...\n"
# define MAX(x, y)	((x) > (y) ? (x) : (y))
# define MULT(x, y)	(((((x) - 1) / (y)) * (y)) + (y))

typedef			enum
  {
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
  }			eObjet;

typedef			enum
  {
    N = 1,
    E,
    S,
    O
  }			e_direction;

typedef			enum
  {
    EGG,
    WAITING,
    CONNECTED,
    GRAPHIC
  }			e_state;

typedef struct		s_map
{
  int			obj[7];
  t_list		players;
  t_list		eggs;
}			t_map;

typedef struct		s_team
{
  int			nb_player;
  int			nb_lvl_max;
  char			*name;
}			t_team;

typedef struct		s_player
{
  int			fd;
  int			nb;
  int			lvl;
  e_state		state;
  int			x;
  int			y;
  e_direction		direction;
  float			food;
  int			obj[6];
  char			*team;
  char			*cmd_buff;
  float			time;
  t_list		cmd;
  t_list		send;
}			t_player;

typedef struct		s_egg
{
  int			nb;
  int			father;
  int			x;
  int			y;
  e_state		state;
  float			time;
  char			*team;
}			t_egg;

typedef struct		s_opt
{
  int			x;
  int			y;
  int			port;
  int			nb_players;
  int			number_of_client;
  int			delay;
  t_list		team;
}			t_opt;

typedef struct		s_graph
{
  int			fd;
  int			nb;
  char			*buff;
  t_list		cmd;
  t_list		send;
  int			mct_x;
  int			mct_y;
  t_elem		*pos;
}			t_graph;

typedef struct		s_serv
{
  int			sock;
  fd_set		readfd;
  fd_set		writefd;
  int			maxfd;
  t_map			**map;
  t_opt			opt;
  t_list		players;
  t_list		eggs;
  t_list		graphic;
}			t_serv;

typedef struct		s_cmdopt
{
  char			c;
  int			(*ptr)();
}			t_cmdopt;

typedef struct		s_cmd
{
  char			*cmd;
  int			(*ptr)();
}			t_cmd;

int			my_puterr(const char *);
int			my_perror(const char *);
int			is_number(const char *);
void			handle_sigint_server(int);
void			free_server();
void			handle_sigpipe_server(int);
int			fill_nb_players(char **);
int			handle_options(int, char **, int, int);
int			fill_delay(char **);
int			fill_port(char **);
int			fill_x(char **);
int			fill_y(char **);
int			init_server(int);
int			init_map();
void			start_server();
void			new_client();
void			*handle_client(t_elem*);
void			*handle_graphic(t_elem*);
void			handle_waiting_player(t_player *, char[]);
void			connect_client(t_player *, t_team *);
void			connect_graphic(t_player *);
void			erase_client(t_player*, int);
void			erase_graphic(t_graph*);
void			cycle_management(float);
void			*manage_player(t_elem*, float);
void			send_ko(t_player*);
int			check_incantation(t_player*);
int			manage_ressource(t_player*);
void			send_to_client(t_player*);
void			send_to_graph(t_graph*);
void			graphic_cycle();
void			destroy_egg(t_egg *);

int			mszg(t_graph*);
int			bctg(t_graph*, int, int);
int			mctg(t_graph*);
int			tnag(t_graph*);
int			pnwg(t_graph*, t_player*);
int			ppog(t_graph*, t_player*);
int			plvg(t_graph*, t_player*);
int			ping(t_graph*, t_player*);
int			pexg(t_graph*, t_player*);
int			pbcg(t_graph*, t_player*, char*);
int			picg(t_graph*, t_player*);
int			pieg(t_graph*, t_player*, int);
int			pfkg(t_graph*, t_player*);
int			pdrg(t_graph*, t_player*, eObjet);
int			pgtg(t_graph*, t_player*, eObjet);
int			pdig(t_graph*, t_player*);
int			enwg(t_graph*, t_egg*);
int			ehtg(t_graph*, t_egg*);
int			ebog(t_graph*, t_egg*);
int			edig(t_graph*, t_egg*);
int			sgtg(t_graph*);
int			segg(t_graph*, char*);
int			smgg(t_graph*, char*);
int			sucg(t_graph*);
int			sbpg(t_graph*);

int			mszgh(t_graph*, char*, char*);
int			bctgh(t_graph*, char*, char*);
int			mctgh(t_graph*, char*, char*);
int			tnagh(t_graph*, char*, char*);
int			ppogh(t_graph*, char*, char*);
int			plvgh(t_graph*, char*, char*);
int			pingh(t_graph*, char*, char*);
int			sgtgh(t_graph*, char*, char*);
int			sstgh(t_graph*, char*, char*);
int			pnwgh(t_graph*, char*, char*);
int			enwgh(t_graph*, char*, char*);

int			avance(t_player*, int, char*);
int			droite(t_player*, int, char*);
int			gauche(t_player*, int, char*);
int			inventaire(t_player*, int, char*);
int			prend(t_player*, int, char*);
int			pose(t_player*, int, char*);
int			expulse(t_player*, int, char*);
int			incantation(t_player*, int, char*);
int			start_incantation(t_player*);
int			end_incantation(t_player*, int, int);
void			inc_lvl_team(t_player*);
int			forkp(t_player*, int, char*);
int			connect_nbr(t_player*, int, char*);

int			food_linemate_deraumere(int x, int y, char **buff);
int			sibur_mendiane_phiras(int x, int y, char **buff);
int			thystame_players_eggs(int x, int y, char **buff);
int			add_coord(int x, int y, char **buff);
int			scan_n(t_player *player, int c, char **buff);
int			scan_s(t_player *player, int c, char **buff);
int			scan_o(t_player *player, int c, char **buff);
int			scan_e(t_player *player, int c, char **buff);
int			voir(t_player *player, int nb);
int			add_to_buff(char *s, char **buff);

int			calculate(int speaker, int listener, int max);
void			direction_tab(e_direction dir[]);
void			horizontal_tab(int left[], int right[]);
void			vertical_tab(int up[], int down[]);
void			no_tab(int tab[]);
void			ne_tab(int tab[]);
void			so_tab(int tab[]);
void			se_tab(int tab[]);
int			broadcasts(t_player *player, int nb, char *msg);
void			broadcast_graphic(t_player* player, char *msg);
int			direction_player(t_player *speaker, t_player *listener);

#endif /* !SERVER_H_ */
