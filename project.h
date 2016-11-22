/*######################################################*/
/* HWTP_121044064_Ersin_CEYLAN.zip                 	    */
/* main.c											    */	
/*_______________   						 		    */
/*                    								    */
/* Written by Ersin CEYLAN	05/01/2015				    */
/*                                                      */
/*######################################################*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define CMD_SIZE 300
#define DEBUG2 aa

typedef struct{

	char team_name[MAX_SIZE];
	char city[MAX_SIZE];
	char stadium[MAX_SIZE];
	int founding_date;
	char colors[MAX_SIZE];

}teams_t;

typedef struct{

	char player_name[MAX_SIZE];
	char team_name[MAX_SIZE];
	int birth_date;
	char origin[MAX_SIZE];
	char position[MAX_SIZE];
	int salary;

}players_t;

typedef struct{

	int year;
	char team_name[MAX_SIZE];
	int points;
	int wins;
	int loses;
	int draws;
	int goals_for;
	int goals_against;
	int goals_difference;

}teams_sta_t;

typedef struct{

	int year;
	char player_name[MAX_SIZE];
	int goals;
	int assists;
	int red_cards;
	int yellow_cards;

}players_sta_t;

int insert_teams(char ** team_data);
int insert_players(char ** player_data);
int insert_teams_sta(char **team_sta_data);
int insert_players_sta(char ** player_sta_data);

int write_team(FILE *,teams_t write_table);
int write_player(FILE * file,players_t write_table);
int write_teams_sta(FILE * file,teams_sta_t write_table);
int write_players_sta(FILE * file,players_sta_t write_table);

int select_teams(char **,int);
int select_players(char **,int);
int select_team_sta(char **,int);
int select_player_sta(char **,int);

void show_teams(char **field,teams_t team,int field_size);
void show_players(char **field,players_t player,int field_size);
void show_team_sta(char **field,teams_sta_t team_sta,int field_size);
void show_player_sta(char **field,players_sta_t player_sta,int field_size);

teams_t * sort_teams(char * sort_by,int w_sort, char **fields,int);
players_t * sort_players(char * sort_by,int w_sort, char **fields,int);
teams_sta_t *sort_teams_sta(char *,int , char **,int);
players_sta_t * sort_players_sta(char * ,int , char **,int);

players_sta_t * read_players_sta(int size);
teams_t * read_teams(int size);
players_t * read_players(int size);
teams_sta_t * read_teams_sta(int size);

void delete_teams(char **where_fields,teams_t *elem_teams,int elem_size);
void delete_players(char **where_fields,players_t *elem_players,int elem_size);
void del_teams_sta(char **,teams_sta_t *,int );
void del_players_sta(char **,players_sta_t *,int);

void read_table(int );
int field_number(char str[MAX_SIZE]);
int pass_space_select(char*);
int num_file_elem(char * table);

int part_delete(char *);
int part_insert(char *);
int part_select(char *);
int part_update(char *);

char* search_where_sort(char *str, int *which);

char ** break_select(char * select,int field_num);
char ** break_where(char * where,int *col_size);

void where_teams(char**field_arr,char**where_arr,int f_size);
void where_players(char**field_arr,char**where_arr,int f_size);
void where_teams_sta(char**field_arr,char**where_arr,int f_size);
void where_players_sta(char**field_arr,char**where_arr,int f_size);

char *break_sort(char * where_sort, int *w_sort);

void update_teams(char **,char **,teams_t *,int,int,int);
void update_players(char ** ,char ** ,players_t *,int ,int,int);
void update_teams_sta(char **,char ** ,teams_sta_t *,int,int,int );
void update_players_sta(char **,char ** ,players_sta_t *,int,int,int);

void smart1();
void smart2();
void smart3();

void part_smart(char *);
