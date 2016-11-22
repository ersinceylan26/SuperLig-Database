/*######################################################*/
/* HWTP_121044064_Ersin_CEYLAN.zip                 	    */
/* main.c											    */	
/*_______________   						 		    */
/*                    								    */
/* Written by Ersin CEYLAN	05/01/2015				    */
/*                                                      */
/*######################################################*/

#include "project.h"

int part_select(char *command){

	char teams[]="teams";
	char players[]="players";
	char team_sta[]="team_statistics";
	char player_sta[]="player_statistics";

	char * where_sort;
	char * sort_fields;

	int field_num;
	int file_elem;

	int s_kind;
	int *select_kind=&s_kind;
	int where_size;
	int *where_size_p=&where_size;
	int w_sort;
	int *w_sort_p=&w_sort;

	char ** where_fields;
	char ** select_fields;

	teams_t * sorted_teams;
	players_t * sorted_players;
	teams_sta_t * sorted_team_sta;
	players_sta_t * sorted_player_sta;

	field_num=field_number(command);
	where_sort=search_where_sort(command,&s_kind);

	if(s_kind==0)
	{
		select_fields=break_select(command,field_num);

		if(strcmp(select_fields[field_num],teams)==0)
		{
			select_teams(select_fields,field_num);
		}
		else if(strcmp(select_fields[field_num],players)==0)
		{
			select_players(select_fields,field_num);
		}
		else if(strcmp(select_fields[field_num],team_sta)==0)
		{
			select_team_sta(select_fields,field_num);
		}
		else if(strcmp(select_fields[field_num],player_sta)==0)
		{
			select_player_sta(select_fields,field_num);
		}
	
		free(select_fields[0]);
		free(select_fields);
			
	}
	else if(s_kind==1)
	{
		select_fields=break_select(command,field_num);
		where_fields=break_where(where_sort,&where_size);

		if(strcmp(select_fields[field_num],teams)==0)
		{
			where_teams(select_fields,where_fields,field_num);
		}
		else if(strcmp(select_fields[field_num],players)==0)
		{
			where_players(select_fields,where_fields,field_num);
		}
		else if(strcmp(select_fields[field_num],team_sta)==0)
		{
			where_teams_sta(select_fields,where_fields,field_num);	
		}
		else if(strcmp(select_fields[field_num],player_sta)==0)
		{
			where_players_sta(select_fields,where_fields,field_num);
		}	
		free(select_fields[0]);
		free(select_fields);
	
		free(where_fields[0]);
		free(where_fields);
	
	}
	else if(s_kind==2)
	{
		select_fields=break_select(command,field_num);
		sort_fields=break_sort(where_sort,&w_sort);

		if(strcmp(select_fields[field_num],teams)==0)
		{
			sort_teams(sort_fields,w_sort,select_fields,field_num);
		}
		else if(strcmp(select_fields[field_num],players)==0)
		{
  	   		sort_players(sort_fields,w_sort,select_fields,field_num);	
		}
		else if(strcmp(select_fields[field_num],team_sta)==0)
		{
			sort_teams_sta(sort_fields,w_sort,select_fields,field_num);
		}
		else if(strcmp(select_fields[field_num],player_sta)==0)
		{
			sort_players_sta(sort_fields,w_sort,select_fields,field_num);
		}
			
		free(select_fields[0]);
		free(select_fields);
		free(sort_fields);
			
	}

}
int field_number(char str[MAX_SIZE]){

	int i=0;
	int field_num=1;
	
	while(str[i]!='\0')
	{
		if(str[i]==',')
		{
			field_num=field_num+1;
		}
		i=i+1;
	}

	return field_num;
}

int pass_space_select(char* pointer){

	while(pointer[1]!=' ')
	{
		pointer=&pointer[1];
	}

}

int part_insert(char *p){

	char to[3]="to";
	char teams[20]="teams";
	char players[20]="players";
	char team_statistics[20]="team_statistics";
	char player_statistics[20]="player_statistics";
	int i=0;
	int j=0;

	int k=10;
	int field_num;
 	char *data;
	char **pp;
	char *table_pp;

	field_num=field_number(p);

	#if defined(DEBUG)
	printf("F_Num:%d",field_num);
	#endif

 	data=(char *)malloc(field_num*20*sizeof(char));
	pp=(char**)malloc(field_num*sizeof(char*));

	for(i=0;i<field_num;i++)
	{
		pp[i]=data+i*20;
	}

	pass_space_select(p);

	p = strtok (NULL, ", ");

	while(strcmp(p,to)!=0)
	{
		strcpy(pp[j],p);
		pass_space_select(p);

		p = strtok (NULL, ", ");
		j++;

	}

	pass_space_select(p);

	p = strtok (NULL, ",\n ");


	#if defined(DEBUG)
		for(i=0;i<field_num;i++)
		{
			printf("/%s/",pp[i]);
		}
	#endif

	if(strcmp(teams,p)==0)
	{	
		#if defined(DEBUG)
			printf("table >> teams");
		#endif
		insert_teams(pp);
	}
	else if(strcmp(players,p)==0)
	{
		#if defined(DEBUG)
			printf("table >> players");
		#endif
		insert_players(pp);
	}
	else if(strcmp(team_statistics,p)==0)
	{
		#if defined(DEBUG)
			printf("table >> team_sta");
		#endif
		insert_teams_sta(pp);
	}
	else if(strcmp(player_statistics,p)==0)
	{
		#if defined(DEBUG)
			printf("table >> player_sta");
		#endif		
		insert_players_sta(pp);
	}
	else 
	{
		printf(">> Komut Hatali <<");

		free(pp[0]);
		free(pp);

		return -1;
	}

	free(pp[0]);
	free(pp);

}


int insert_teams(char ** team_data){

	char table_team[]="teams";
	teams_t team;
	teams_t * teams;
	
	FILE * file;

	int i;
	int size;

	size=num_file_elem(table_team);
	#if defined(DEBUG)
		printf("\nSIZE=%d",size);
	#endif

	if(size==-1)
	{
		strcpy(team.team_name,team_data[0]);
		strcpy(team.city,team_data[1]);
		strcpy(team.stadium,team_data[2]);
		team.founding_date=atoi(team_data[3]);
		strcpy(team.colors,team_data[4]);

		#if defined(DEBUG)
			printf("/%s/",team.team_name);
			printf("/%s/",team.city);
			printf("/%s/",team.stadium);
			printf("/%d/",team.founding_date);
			printf("/%s/\n",team.colors);
		#endif
	
		file=fopen("teams.bin","ab+");
		write_team(file,team);

		fclose(file);

		printf(">> Takım Eklendi\n");

		#if defined(DEBUG)
			printf("\n>> Dosyanin suanki hali >>\n");
			read_table(1);
		#endif
	}
	else
	{
		teams=read_teams(size);

		for(i=0;i<size;i++)
		{
			if(strcmp(teams[i].team_name,team_data[0])==0)
			{
				printf(">> Ayni takim bulunmaktadir !! \n");
				return -1;
			}
		}

		strcpy(team.team_name,team_data[0]);
		strcpy(team.city,team_data[1]);
		strcpy(team.stadium,team_data[2]);
		team.founding_date=atoi(team_data[3]);
		strcpy(team.colors,team_data[4]);

		#if defined(DEBUG)
			printf("/%s/",team.team_name);
			printf("/%s/",team.city);
			printf("/%s/",team.stadium);
			printf("/%d/",team.founding_date);
			printf("/%s/\n",team.colors);
		#endif
	
		file=fopen("teams.bin","ab+");
		write_team(file,team);

		fclose(file);

		free(teams);

		printf(">> Takım Eklendi\n");

		#if defined(DEBUG)
			printf("\n>> Dosyanin suanki hali >>\n");
			read_table(1);
		#endif
	}
}

int insert_players(char ** player_data){

	char table_players[]="players";

	players_t player;
	players_t * players;

	int i;
	int size;

	FILE * file;

	size=num_file_elem(table_players);
	
	#if defined(DEBUG)
		printf("\nSIZE=%d",size);
	#endif

	if(size==-1)
	{
		strcpy(player.player_name,player_data[0]);
		strcpy(player.team_name,player_data[1]);
		player.birth_date=atoi(player_data[2]);
		strcpy(player.origin,player_data[3]);
		strcpy(player.position,player_data[4]);
		player.salary=atoi(player_data[5]);

		#if defined(DEBUG)
			printf("-%s-",player.player_name);
			printf("-%s-",player.team_name);
			printf("-%d-",player.birth_date);
			printf("-%s-",player.origin);
			printf("-%s-",player.position);
			printf("-%d-\n",player.salary);
		#endif

		file=fopen("players.bin","ab+");
		write_player(file,player);

		fclose(file);

		printf(">> Oyuncu Eklendi\n");

		#if defined(DEBUG)
			printf("\n\n>> Dosyanin suanki hali >>\n");
			read_table(2);
		#endif

	}
	else
	{
		players=read_players(size);

		for(i=0;i<size;i++)
		{
			if(strcmp(players[i].player_name,player_data[0])==0)
			{
				printf(">> Ayni oyuncu bulunmaktadır !! \n\n");
				return -1;
			}
		}

		strcpy(player.player_name,player_data[0]);
		strcpy(player.team_name,player_data[1]);
		player.birth_date=atoi(player_data[2]);
		strcpy(player.origin,player_data[3]);
		strcpy(player.position,player_data[4]);
		player.salary=atoi(player_data[5]);

		#if defined(DEBUG)
			printf("-%s-",player.player_name);
			printf("-%s-",player.team_name);
			printf("-%d-",player.birth_date);
			printf("-%s-",player.origin);
			printf("-%s-",player.position);
			printf("-%d-\n",player.salary);
		#endif

		file=fopen("players.bin","ab+");
		write_player(file,player);

		fclose(file);
		free(players);

		printf(">> Oyuncu Eklendi\n");

		#if defined(DEBUG)
			printf("\n\n>> Dosyanin suanki hali >>\n");
			read_table(2);
		#endif
	}

}

int insert_teams_sta(char ** team_sta_data){

	char table_team_sta[]="team_statistics";
	teams_sta_t team_sta;
	teams_sta_t * team_sta_s;

	int i;
	int size;
	FILE * file;

	size=num_file_elem(table_team_sta);
	
	#if defined(DEBUG)
		printf("SIZE=%d",size);
	#endif	
	
	if(size==-1)
	{
		team_sta.year=atoi(team_sta_data[0]);
		strcpy(team_sta.team_name,team_sta_data[1]);
		team_sta.points=atoi(team_sta_data[2]);
		team_sta.wins=atoi(team_sta_data[3]);
		team_sta.loses=atoi(team_sta_data[4]);
		team_sta.draws=atoi(team_sta_data[5]);
		team_sta.goals_for=atoi(team_sta_data[6]);
		team_sta.goals_against=atoi(team_sta_data[7]);
		team_sta.goals_difference=atoi(team_sta_data[8]);

		#if defined(DEBUG)
			printf("\n-%d-",team_sta.year);
			printf("-%s-",team_sta.team_name);
			printf("-%d-",team_sta.points);
			printf("-%d-",team_sta.wins);
			printf("-%d-",team_sta.loses);
			printf("-%d-",team_sta.draws);
			printf("-%d-",team_sta.goals_for);
			printf("-%d-",team_sta.goals_against);
			printf("-%d-\n",team_sta.goals_difference);
		#endif
	
		file=fopen("team_statistics.bin","ab+");
		write_teams_sta(file,team_sta);

		fclose(file);

		printf(">> Takim Bilgileri Eklendi\n");

		#if defined(DEBUG)
			printf("\n\n>> Dosyanin suanki hali >>\n");
			read_table(3);
		#endif

	}
	else
	{

		team_sta_s=read_teams_sta(size);

		for(i=0;i<size;i++)
		{
			if(team_sta_s[i].year==atoi(team_sta_data[0]) &&
				strcmp(team_sta_s[i].team_name,team_sta_data[1])==0)
			{
			   printf(">> Ayni takim ve yila ait bilgiler bulunmaktadir !!\n");
				return -1;
			}
		}

		team_sta.year=atoi(team_sta_data[0]);
		strcpy(team_sta.team_name,team_sta_data[1]);
		team_sta.points=atoi(team_sta_data[2]);
		team_sta.wins=atoi(team_sta_data[3]);
		team_sta.loses=atoi(team_sta_data[4]);
		team_sta.draws=atoi(team_sta_data[5]);
		team_sta.goals_for=atoi(team_sta_data[6]);
		team_sta.goals_against=atoi(team_sta_data[7]);
		team_sta.goals_difference=atoi(team_sta_data[8]);

		#if defined(DEBUG)
			printf("\n-%d-",team_sta.year);
			printf("-%s-",team_sta.team_name);
			printf("-%d-",team_sta.points);
			printf("-%d-",team_sta.wins);
			printf("-%d-",team_sta.loses);
			printf("-%d-",team_sta.draws);
			printf("-%d-",team_sta.goals_for);
			printf("-%d-",team_sta.goals_against);
			printf("-%d-\n",team_sta.goals_difference);
		#endif
	
		file=fopen("team_statistics.bin","ab+");
		write_teams_sta(file,team_sta);

		fclose(file);
		free(team_sta_s);

		printf(">> Takim Bilgileri Eklendi\n");

		#if defined(DEBUG)
			printf("\n\n>> Dosyanin suanki hali >>\n");
			read_table(3);
		#endif

	}


}


int insert_players_sta(char ** player_sta_data){

	char table_player_sta[]="player_statistics";
	players_sta_t player_sta;
	players_sta_t * players_sta_s;

	int i;
	int size;
	FILE * file;

	size=num_file_elem(table_player_sta);

	#if defined(DEBUG)
		printf(" SIZE:%d",size);
	#endif

	if(size==-1)
	{
		player_sta.year=atoi(player_sta_data[0]);
		strcpy(player_sta.player_name,player_sta_data[1]);
		player_sta.goals=atoi(player_sta_data[2]);
		player_sta.assists=atoi(player_sta_data[3]);
		player_sta.red_cards=atoi(player_sta_data[4]);
		player_sta.yellow_cards=atoi(player_sta_data[5]);

		#if defined(DEBUG)
			printf("-%d-",player_sta.year);
			printf("-%s-",player_sta.player_name);
			printf("-%d-",player_sta.goals);
			printf("-%d-",player_sta.assists);
			printf("-%d-",player_sta.red_cards);
			printf("-%d-",player_sta.yellow_cards);
		#endif

		file=fopen("player_statistics.bin","ab+");
		write_players_sta(file,player_sta);

		fclose(file);
		free(players_sta_s);

		printf("\n>> Oyuncu Bilgileri Eklendi\n");

		#if defined(DEBUG)
			printf("\n\n>> Dosyanin suanki hali >>\n");
			read_table(4);
		#endif
	}
	else
	{
		players_sta_s=read_players_sta(size);
		
		for(i=0;i<size;i++)
		{
			if(players_sta_s[i].year==atoi(player_sta_data[0]) &&
			   strcmp(players_sta_s[i].player_name,player_sta_data[1])==0)
			{
				printf(">> Ayni oyuncu ve yila ait bilgiler");
				printf(" bulunmaktadir !!\n");
				return -1;
			}
		}

		player_sta.year=atoi(player_sta_data[0]);
		strcpy(player_sta.player_name,player_sta_data[1]);
		player_sta.goals=atoi(player_sta_data[2]);
		player_sta.assists=atoi(player_sta_data[3]);
		player_sta.red_cards=atoi(player_sta_data[4]);
		player_sta.yellow_cards=atoi(player_sta_data[5]);

		#if defined(DEBUG)
			printf("-%d-",player_sta.year);
			printf("-%s-",player_sta.player_name);
			printf("-%d-",player_sta.goals);
			printf("-%d-",player_sta.assists);
			printf("-%d-",player_sta.red_cards);
			printf("-%d-",player_sta.yellow_cards);
		#endif

		file=fopen("player_statistics.bin","ab+");
		write_players_sta(file,player_sta);

		fclose(file);
		free(players_sta_s);

		printf("\n>> Oyuncu Bilgileri Eklendi\n");

		#if defined(DEBUG)
			printf("\n\n>> Dosyanin suanki hali >>\n");
			read_table(4);
		#endif



	}


}

int write_team(FILE * file,teams_t write_table)
{
	int status=2;

	status=fwrite(&write_table,1*sizeof(teams_t),1,file);
}

int write_player(FILE * file,players_t write_table)
{
	int status=2;

	status=fwrite(&write_table,1*sizeof(players_t),1,file);
}

int write_teams_sta(FILE * file,teams_sta_t write_table)
{
	int status=2;

	status=fwrite(&write_table,1*sizeof(teams_sta_t),1,file);
}

int write_players_sta(FILE * file,players_sta_t write_table)
{
	int status=2;

	status=fwrite(&write_table,1*sizeof(players_sta_t),1,file);
}

void read_table(int a)
{

	int status=2;

	teams_t read_teams;
	players_t read_players;
	teams_sta_t read_team_sta;
	players_sta_t read_player_sta;

	FILE * file;

	if(a==1)
	{
		file=fopen("teams.bin","r");
		status=fread(&read_teams,sizeof(teams_t),1,file);
	
		while(status!=0)
		{
			printf("\n|%s",read_teams.team_name);
			printf("|%s",read_teams.city);
			printf("|%s",read_teams.stadium);
			printf("|%d",read_teams.founding_date);
			printf("|%s",read_teams.colors);

			status=fread(&read_teams,sizeof(teams_t),1,file);
		}

	}
	else if (a==2)
	{
		file=fopen("players.bin","r");
		status=fread(&read_players,sizeof(players_t),1,file);

		while(status!=0)
		{
			printf("\n|%s",read_players.player_name);
			printf("|%s",read_players.team_name);
			printf("|%d",read_players.birth_date);
			printf("|%s",read_players.origin);
			printf("|%s",read_players.position);
			printf("|%d",read_players.salary);

			status=fread(&read_players,sizeof(players_t),1,file);
		}

	}
	else if (a==3)
	{
		file=fopen("team_statistics.bin","r");
		status=fread(&read_team_sta,sizeof(teams_sta_t),1,file);
	
		while(status!=0)
		{
			printf("\n|%d",read_team_sta.year);
			printf("|%s",read_team_sta.team_name);
			printf("|%d",read_team_sta.points);
			printf("|%d",read_team_sta.wins);
			printf("|%d",read_team_sta.loses);
			printf("|%d",read_team_sta.draws);
			printf("|%d",read_team_sta.goals_for);
			printf("|%d",read_team_sta.goals_against);
			printf("|%d",read_team_sta.goals_difference);

			status=fread(&read_team_sta,sizeof(teams_sta_t),1,file);
		}
	
	}
	else if(a==4)
	{
		file=fopen("player_statistics.bin","r");
		status=fread(&read_player_sta,sizeof(players_sta_t),1,file);

		while(status!=0)
		{
			printf("\n|%d",read_player_sta.year);
			printf("|%s",read_player_sta.player_name);
			printf("|%d",read_player_sta.goals);
			printf("|%d",read_player_sta.assists);
			printf("|%d",read_player_sta.red_cards);
			printf("|%d",read_player_sta.yellow_cards);

			status=fread(&read_player_sta,sizeof(players_sta_t),1,file);
		}
	}
	printf("\n\n");

	fclose(file);
}

players_sta_t * read_players_sta(int size){

    players_sta_t * struct_arr_p;
    FILE * file;

    int status;
	int i=0;

    struct_arr_p=(players_sta_t *)calloc(size,sizeof(players_sta_t));
	
    file=fopen("player_statistics.bin","r");

    status=fread(&struct_arr_p[i],1*sizeof(players_sta_t),1,file);
 	
	#if defined (DEBUG)
		printf("\n\nDosyadan okunanlar >>\n");
	#endif

    while(status!=0)
	{

		#if defined (DEBUG)
		    printf("\n>>>%d",struct_arr_p[i].goals);
			printf("|%d|",struct_arr_p[i].year);
			printf("%s|",struct_arr_p[i].player_name);
			printf("%d|",struct_arr_p[i].goals);
			printf("%d|",struct_arr_p[i].assists);
			printf("%d|",struct_arr_p[i].red_cards);
			printf("%d|",struct_arr_p[i].yellow_cards);
		#endif

        i++;
		status=fread(&struct_arr_p[i],1*sizeof(players_sta_t),1,file);
    }
	printf("\n\n");

	fclose(file);
	return struct_arr_p;
}

teams_t * read_teams(int size){

    teams_t * struct_arr_p;
    FILE * file;

    int status;
	int i=0;

    struct_arr_p=(teams_t *)calloc(size,sizeof(teams_t));

    file=fopen("teams.bin","r");
	
    status=fread(&struct_arr_p[i],1*sizeof(teams_t),1,file); 

	#if defined (DEBUG)
		printf("\n\nDosyadan okunanlar >> \n");
	#endif

    while(status!=0)
	{
		#if defined (DEBUG)
			printf("\n>>>%s",struct_arr_p[i].team_name);
			printf("|%s|",struct_arr_p[i].city);
			printf("%s|",struct_arr_p[i].stadium);
			printf("%d|",struct_arr_p[i].founding_date);
			printf("%s|",struct_arr_p[i].colors);
		#endif

        i=i+1;
		status=fread(&struct_arr_p[i],1*sizeof(teams_t),1,file);
    }
	printf("\n\n");

	fclose(file);
	return struct_arr_p;
}

players_t * read_players(int size){

    players_t * struct_arr_p;
    FILE * file;

    int status;
	int i=0;

    struct_arr_p=(players_t *)calloc(size,sizeof(players_t));

    file=fopen("players.bin","r");
	
    status=fread(&struct_arr_p[i],1*sizeof(players_t),1,file); 

	#if defined (DEBUG)
		printf("\n\nDosyadan okunanlar >> \n");
	#endif

    while(status!=0)
	{
		#if defined (DEBUG)
			printf("\n>>>%s",struct_arr_p[i].player_name);
			printf("|%s|",struct_arr_p[i].team_name);
			printf("%d|",struct_arr_p[i].birth_date);
			printf("%s|",struct_arr_p[i].origin);
			printf("%s|",struct_arr_p[i].position);
			printf("%d|",struct_arr_p[i].salary);
		#endif

        i++;
		status=fread(&struct_arr_p[i],1*sizeof(players_t),1,file);
    }
	printf("\n\n");

	fclose(file);
	return struct_arr_p;
}

teams_sta_t * read_teams_sta(int size){

	teams_sta_t * struct_arr_p;
    FILE * file;

    int status;
    int i=0;

    struct_arr_p=(teams_sta_t *)calloc(size,sizeof(teams_sta_t));

    file=fopen("team_statistics.bin","r");
	
    status=fread(&struct_arr_p[i],1*sizeof(teams_sta_t),1,file); 

	#if defined (DEBUG)
		printf("\n\nDosyadan okunanlar >> \n");
	#endif

    while(status!=0)
	{  
		#if defined (DEBUG)
		  	printf("\n>>>%d",struct_arr_p[i].year);
			printf("|%s|",struct_arr_p[i].team_name);
			printf("%d|",struct_arr_p[i].points);
			printf("%d|",struct_arr_p[i].wins);
			printf("%d|",struct_arr_p[i].loses);
			printf("%d|",struct_arr_p[i].draws);
			printf("%d|",struct_arr_p[i].goals_for);
			printf("%d|",struct_arr_p[i].goals_against);
			printf("%d|",struct_arr_p[i].goals_difference);
		#endif		
	
        i++;
		status=fread(&struct_arr_p[i],1*sizeof(teams_sta_t),1,file);
    }
	printf("\n\n");	

	fclose(file);
	return struct_arr_p;
}

char* search_where_sort(char *str, int *which){

	char where[]="where";
	char sort[]="sort";
	char * p;

	p=strstr(str,where);

	if(p!=NULL)
	{
		*which=1;
		return p;
	}

	p=strstr(str,sort);

	if(p!=NULL)
	{
		*which=2;
		return p;
	}
	else
	{
		*which=0;
		return p;
	}
}

char ** break_select(char * select,int field_num){

	int i;

	char to[]="to";
	char teams[]="teams";
	char players[]="players";
	char team_statistics[]="team_statistics";
	char player_statistics[]="player_statistics";

 	char *data;
	char **pp;

	field_num++; /*Tablo ismi icin bir yer daha lazim*/

	#if defined (DEBUG)
		printf("F_SIZE:%d",field_num);
	#endif	

 	data=(char *)malloc(field_num*20*sizeof(char));
	pp=(char**)malloc(field_num*sizeof(char*));

	for(i=0;i<field_num;i++)
	{
		pp[i]=data+i*20;
	}

	pass_space_select(select);
	
	for(i=0;i<field_num-1;i++)
	{
		select = strtok(NULL,", ");
		strcpy(pp[i],select);
		pass_space_select(select);
	}
	
	pass_space_select(select);
	select = strtok(NULL,", ");
	pass_space_select(select);
	select = strtok(NULL,", ");
	
	strcpy(pp[field_num-1],select);

	#if defined (DEBUG)
		printf("\nAlinan Fieldlar >> ");
		for(i=0;i<field_num;i++)
		{
			printf("-%s",pp[i]);
		}
	#endif

	return pp;

}

char ** break_where(char * where,int *row_num){
	
	int i=0;
	int j=0;

	char * data_where;
	char ** data_where_pp;	

	int ope_num=0;
	*row_num=0;

	while(where[i]!='\0')
	{
		if(where[i]=='=' || where[i]=='<' || where[i]=='>' || 
			where[i]=='&' || where[i]=='|')
		{
			ope_num++;
		}

		i=i+1;
	}

	*row_num=ope_num+1;

	data_where=(char *)malloc(*row_num*20*sizeof(char));
	data_where_pp=(char**)malloc(*row_num*sizeof(char*));

	for(i=0;i<*row_num;i++)
	{
		data_where_pp[i]=data_where+i*20;
	}

	where = strtok(where," ");
	pass_space_select(where);

	for(i=0;i<*row_num;i++)
	{
		where = strtok(NULL,"=,<>|& ");
		strcpy(data_where_pp[i],where);
		pass_space_select(where);
	}

	#if defined (DEBUG)
		printf("Where Kosullari >>");
		for(i=0;i<*row_num;i++)
		{
			printf("-%s-",data_where_pp[i]);
		}
	#endif

	return data_where_pp;
}

int num_file_elem(char * table){

	char teams[]="teams";
	char players[]="players";
	char team_statistics[]="team_statistics";
	char player_statistics[]="player_statistics";

	int status=2;
	int size=0;

	FILE * inp;

	teams_t data1;
	players_t data2;
	teams_sta_t data3;
	players_sta_t data4;

	if(strcmp(table,teams)==0)
	{
		inp=fopen("teams.bin","rb");
		if(inp==NULL)
		{
			return -1;
		}
		while(status!=0){
			status=fread(&data1,1*sizeof(teams_t),1,inp);
			size++;
		}
	}
	else if(strcmp(table,players)==0)
	{
		inp=fopen("players.bin","rb");
		if(inp==NULL)
		{
			return -1;
		}
		while(status!=0){
			status=fread(&data2,1*sizeof(players_t),1,inp);
			size++;
		}		
	}
	else if(strcmp(table,team_statistics)==0)
	{
		inp=fopen("team_statistics.bin","rb");
		if(inp==NULL)
		{
			return -1;
		}
		while(status!=0){
			status=fread(&data3,1*sizeof(teams_sta_t),1,inp);
			size++;
		}
	}
	else if(strcmp(table,player_statistics)==0)
	{
		inp=fopen("player_statistics.bin","rb");
		if(inp==NULL)
		{
			return -1;
		}
		while(status!=0){
			status=fread(&data4,1*sizeof(players_sta_t),1,inp);
			size++;
		}
	}

	fclose(inp);
	return size-1;
}

void where_teams(char**field_arr,char**where,int f_size)
{

	char team_name[]="team_name";
	char city[]="city";
	char stadium[]="stadium";
	char founding_date[]="founding_date";
	char colors[]="colors";
	char teams[]="teams";

	teams_t * all_team;

	int i;
	int file_elem;

	file_elem=num_file_elem(teams);
	all_team=read_teams(file_elem);
	
	if(strcmp(where[0],city)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_team[i].city)==0)
			{
				show_teams(field_arr,all_team[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],stadium)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_team[i].stadium)==0)
			{
				show_teams(field_arr,all_team[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],colors)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_team[i].colors)==0)
			{
				show_teams(field_arr,all_team[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],team_name)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_team[i].team_name)==0)
			{
				show_teams(field_arr,all_team[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],founding_date)==0)
	{	
		for(i=0;i<file_elem;i++)

		{
			if(atoi(where[1])==all_team[i].founding_date)
			{
				show_teams(field_arr,all_team[i],f_size);
			}
		}
	}

	free(all_team);
}

void where_players(char**field_arr,char**where,int f_size)
{

	char team_name[]="team_name";
	char player_name[]="player_name";
	char birth_date[]="birth_date";
	char origin[]="origin";
	char position[]="position";
	char salary[]="salary";
	char players[]="players";

	players_t * all_player;

	int i;
	int file_elem;

	file_elem=num_file_elem(players);
	all_player=read_players(file_elem);
	
	if(strcmp(where[0],origin)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_player[i].origin)==0)
			{
				show_players(field_arr,all_player[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],position)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_player[i].position)==0)
			{
				show_players(field_arr,all_player[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],player_name)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_player[i].player_name)==0)
			{
				show_players(field_arr,all_player[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],team_name)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_player[i].team_name)==0)
			{
				show_players(field_arr,all_player[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],birth_date)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_player[i].birth_date)
			{
				show_players(field_arr,all_player[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],salary)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_player[i].salary)
			{
				show_players(field_arr,all_player[i],f_size);
			}
		}
	}

	free(all_player);
}

void where_players_sta(char**field_arr,char**where,int f_size)
{

	char year[]="year";
	char player_name[]="player_name";
	char goals[]="goals";
	char assists[]="assists";
	char red_cards[]="red_cards";
	char yellow_cards[]="yellow_cards";
	char player_sta[]="player_statistics";

	players_sta_t * all_player_sta;

	int i;
	int file_elem;

	file_elem=num_file_elem(player_sta);
	all_player_sta=read_players_sta(file_elem);
	
	if(strcmp(where[0],year)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_player_sta[i].year)
			{
				show_player_sta(field_arr,all_player_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],goals)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_player_sta[i].goals)
			{
				show_player_sta(field_arr,all_player_sta[i],f_size);
			}
		}
	}	
	else if(strcmp(where[0],assists)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_player_sta[i].assists)
			{
				show_player_sta(field_arr,all_player_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],red_cards)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_player_sta[i].red_cards)
			{
				show_player_sta(field_arr,all_player_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],yellow_cards)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_player_sta[i].yellow_cards)
			{
				show_player_sta(field_arr,all_player_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],player_name)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_player_sta[i].player_name)==0)
			{
				show_player_sta(field_arr,all_player_sta[i],f_size);
			}
		}
	}

	free(all_player_sta);

}

void where_teams_sta(char**field_arr,char**where,int f_size)
{

	char year[]="year";
	char team_name[]="team_name";
	char points[]="points";
	char wins[]="wins";
	char loses[]="loses";
	char draws[]="draws";
	char goals_for[]="goals_for";
	char goals_against[]="goals_against";
	char goals_difference[]="goals_difference";
	char team_sta[]="team_statistics";

	teams_sta_t * all_team_sta;

	int i;
	int file_elem;

	file_elem=num_file_elem(team_sta);
	all_team_sta=read_teams_sta(file_elem);
	
	if(strcmp(where[0],year)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_team_sta[i].year)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],points)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_team_sta[i].points)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],wins)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_team_sta[i].wins)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],loses)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_team_sta[i].loses)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],draws)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_team_sta[i].draws)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],goals_for)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_team_sta[i].goals_for)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],goals_against)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_team_sta[i].goals_against)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],goals_difference)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(atoi(where[1])==all_team_sta[i].goals_difference)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}
	else if(strcmp(where[0],team_name)==0)
	{	
		for(i=0;i<file_elem;i++)
		{
			if(strcmp(where[1],all_team_sta[i].team_name)==0)
			{
				show_team_sta(field_arr,all_team_sta[i],f_size);
			}
		}
	}

	free(all_team_sta);

}

void show_teams(char **field,teams_t team,int field_size){

	char team_name[]="team_name";
	char city[]="city";
	char stadium[]="stadium";
	char founding_date[]="founding_date";
	char colors[]="colors";
	char res[]="XOX--XOX";

	int i;
	
	if(strcmp(team.team_name,res)!=0)
	{
		for(i=0;i<field_size;i++)
		{
			if(strcmp(team_name,field[i])==0)
			{
				printf("|%s|",team.team_name);
			}
			else if(strcmp(city,field[i])==0)
			{
				printf("|%s|",team.city);
			}
			else if(strcmp(stadium,field[i])==0)
			{
				printf("|%s|",team.stadium);
			}
			else if(strcmp(founding_date,field[i])==0)
			{
				printf("|%d|",team.founding_date);
			}
			else if(strcmp(colors,field[i])==0)
			{	
				printf("|%s|",team.colors);
			}
		}
		printf("\n");
	}
}

void show_players(char **field,players_t player,int field_size){

	char team_name[]="team_name";
	char player_name[]="player_name";
	char birth_date[]="birth_date";
	char origin[]="origin";
	char position[]="position";
	char salary[]="salary";
	char res[]="XOX--XOX";

	int i;

	if(strcmp(player.player_name,res)!=0)
	{
		for(i=0;i<field_size;i++)
		{
			if(strcmp(player_name,field[i])==0)
			{
				printf("|%s|",player.player_name);
			}
			else if(strcmp(team_name,field[i])==0)
			{
				printf("|%s|",player.team_name);
			}
			else if(strcmp(birth_date,field[i])==0)
			{
				printf("|%d|",player.birth_date);
			}
			else if(strcmp(origin,field[i])==0)
			{
				printf("|%s|",player.origin);
			}
			else if(strcmp(position,field[i])==0)
			{	
				printf("|%s|",player.position);
			}
			else if(strcmp(salary,field[i])==0)
			{	
				printf("|%d|",player.salary);
			}
		}
		printf("\n");
	}
}

void show_team_sta(char **field,teams_sta_t team_sta,int field_size){

	char year[]="year";
	char team_name[]="team_name";
	char points[]="points";
	char wins[]="wins";
	char loses[]="loses";
	char draws[]="draws";
	char goals_for[]="goals_for";
	char goals_against[]="goals_against";
	char goals_difference[]="goals_difference";
	int res1=-9999;
	char res2[]="XOX--XOX";

	int i;

	if(strcmp(team_sta.team_name,res2)!=0 && team_sta.year!=res1)
	{
		for(i=0;i<field_size;i++)
		{
			if(strcmp(year,field[i])==0)
			{
				printf("|%d|",team_sta.year);
			}
			else if(strcmp(team_name,field[i])==0)
			{
				printf("|%s|",team_sta.team_name);
			}
			else if(strcmp(points,field[i])==0)
			{
				printf("|%d|",team_sta.points);
			}
			else if(strcmp(wins,field[i])==0)
			{
				printf("|%d|",team_sta.wins);
			}
			else if(strcmp(loses,field[i])==0)
			{	
				printf("|%d|",team_sta.loses);
			}
			else if(strcmp(draws,field[i])==0)
			{	
				printf("|%d|",team_sta.draws);
			}
			else if(strcmp(goals_for,field[i])==0)
			{	
				printf("|%d|",team_sta.goals_for);
			}
			else if(strcmp(goals_against,field[i])==0)
			{	
				printf("|%d|",team_sta.goals_against);
			}
			else if(strcmp(goals_difference,field[i])==0)
			{	
				printf("|%d|",team_sta.goals_difference);
			}
		}
		printf("\n");
	}	
}

void show_player_sta(char **field,players_sta_t player_sta,int field_size){

	char year[]="year";
	char player_name[]="player_name";
	char goals[]="goals";
	char assists[]="assists";
	char red_cards[]="red_cards";
	char yellow_cards[]="yellow_cards";
	int res1=-9999;
	char res2[]="XOX--XOX";

	int i;

	if(strcmp(player_sta.player_name,res2)!=0 && player_sta.year!=res1)
	{
		for(i=0;i<field_size;i++)
		{
			if(strcmp(year,field[i])==0)
			{
				printf("|%d|",player_sta.year);
			}
			else if(strcmp(player_name,field[i])==0)
			{
				printf("|%s|",player_sta.player_name);
			}
			else if(strcmp(goals,field[i])==0)
			{
				printf("|%d|",player_sta.goals);
			}
			else if(strcmp(assists,field[i])==0)
			{
				printf("|%d|",player_sta.assists);
			}
			else if(strcmp(red_cards,field[i])==0)
			{	
				printf("|%d|",player_sta.red_cards);
			}
			else if(strcmp(yellow_cards,field[i])==0)
			{	
				printf("|%d|",player_sta.yellow_cards);
			}
		}
		printf("\n");
	}	
}

players_sta_t * sort_players_sta(char * sort_by,int w_sort, char **fields,int 									field_size)
{
	char player_sta[]="player_statistics";
	char year[]="year";
	char player_name[]="player_name";
	char goals[]="goals";
	char assists[]="assists";
	char red_cards[]="red_cards";
	char yellow_cards[]="yellow_cards";

	int i;
	int empty;
	int file_elem;
	
	players_sta_t current;
	players_sta_t * players_sta;

	file_elem=num_file_elem(player_sta);
	players_sta=read_players_sta(file_elem);

	#if defined (DEBUG)
	printf("Siralama Sekli:%s||Siralanma Turu:%d||ELEM_SIZE:%d\n",sort_by,w_sort,file_elem);
	#endif

	if(strcmp(sort_by,year)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.year<players_sta[empty-1].year)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,year)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.year>players_sta[empty-1].year)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,goals)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.goals<players_sta[empty-1].goals)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,goals)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.goals>players_sta[empty-1].goals)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,assists)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.assists<players_sta[empty-1].assists)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,assists)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.assists>players_sta[empty-1].assists)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,red_cards)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.red_cards<players_sta[empty-1].red_cards)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,red_cards)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.red_cards>players_sta[empty-1].red_cards)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,yellow_cards)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.yellow_cards<players_sta[empty-1].yellow_cards)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,yellow_cards)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.yellow_cards>players_sta[empty-1].yellow_cards)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,player_name)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				 strcmp(current.player_name,players_sta[empty-1].player_name)<0)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}	
	else if(strcmp(sort_by,player_name)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players_sta[i];
			empty=i;

			while(empty!=0 && 
				 strcmp(current.player_name,players_sta[empty-1].player_name)>0)
			{
				players_sta[empty]=players_sta[empty-1];
				--empty;
			}
			players_sta[empty]=current;	
		}
	}

	printf("\n");
	
	for(i=0;i<file_elem;i++)
	{
		show_player_sta(fields,players_sta[i],field_size);
	}

	free(players_sta);

	printf("\n");

}
teams_t * sort_teams(char * sort_by,int w_sort, char **fields,int field_size){

	char team_name[]="team_name";
	char city[]="city";
	char stadium[]="stadium";
	char founding_date[]="founding_date";
	char colors[]="colors";
	char team[]="teams";

	int i;
	int empty;
	int file_elem;
	
	teams_t current;
	teams_t * teams;

	file_elem=num_file_elem(team);
	teams=read_teams(file_elem);

	#if defined (DEBUG)
	printf("Siralama Sekli:%s||Siralanma Turu:%d||ELEM_SIZE:%d\n",sort_by,w_sort,file_elem);
	#endif
	
	if(strcmp(sort_by,team_name)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.team_name,teams[empty-1].team_name)<0)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,team_name)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.team_name,teams[empty-1].team_name)>0)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,city)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.city,teams[empty-1].city)<0)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,city)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.city,teams[empty-1].city)>0)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,stadium)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.stadium,teams[empty-1].stadium)<0)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,stadium)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.stadium,teams[empty-1].stadium)>0)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,founding_date)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
			 current.founding_date<teams[empty-1].founding_date)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,founding_date)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
			 current.founding_date>teams[empty-1].founding_date)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,colors)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.colors,teams[empty-1].colors)<0)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}
	else if(strcmp(sort_by,colors)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.colors,teams[empty-1].colors)>0)
			{
				teams[empty]=teams[empty-1];
				--empty;
			}
			teams[empty]=current;	
		}
	}

	printf("\n");
	
	for(i=0;i<file_elem;i++)
	{
		show_teams(fields,teams[i],field_size);
	}

	printf("\n");

	free(teams);

}

players_t *sort_players(char *sort_by,int w_sort, char **fields,int field_size){

	char player[]="players";
	char team_name[]="team_name";
	char player_name[]="player_name";
	char birth_date[]="birth_date";
	char origin[]="origin";
	char position[]="position";
	char salary[]="salary";

	int i;
	int empty;
	int file_elem;
	
	players_t current;
	players_t * players;

	file_elem=num_file_elem(player);
	players=read_players(file_elem);

	#if defined (DEBUG)
	printf("Siralama Sekli:%s||Siralanma Turu:%d||ELEM_SIZE:%d\n",sort_by,w_sort,file_elem);
	#endif

	if(strcmp(sort_by,player_name)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.player_name,players[empty-1].player_name)<0)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,player_name)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.player_name,players[empty-1].player_name)>0)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,team_name)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.team_name,players[empty-1].team_name)<0)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,team_name)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.team_name,players[empty-1].team_name)>0)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,birth_date)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  current.birth_date<players[empty-1].birth_date)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,birth_date)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  current.birth_date>players[empty-1].birth_date)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,salary)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  current.salary<players[empty-1].salary)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}	
	else if(strcmp(sort_by,salary)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  current.salary>players[empty-1].salary)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,origin)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.origin,players[empty-1].origin)<0)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,origin)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.origin,players[empty-1].origin)>0)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,position)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.position,players[empty-1].position)>0)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	else if(strcmp(sort_by,position)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=players[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.position,players[empty-1].position)<0)
			{
				players[empty]=players[empty-1];
				--empty;
			}
			players[empty]=current;	
		}
	}
	
	printf("\n");

	for(i=0;i<file_elem;i++)
	{
		show_players(fields,players[i],field_size);
	}
	printf("\n");

	free(players);
}

teams_sta_t *sort_teams_sta(char *sort_by,int w_sort, char **fields,int field_size){

	char team_sta[]="team_statistics";
	char year[]="year";
	char team_name[]="team_name";
	char points[]="points";
	char wins[]="wins";
	char loses[]="loses";
	char draws[]="draws";
	char goals_for[]="goals_for";
	char goals_against[]="goals_against";
	char goals_difference[]="goals_difference";

	int i;
	int empty;
	int file_elem;
	
	teams_sta_t current;
	teams_sta_t * teams_sta;

	file_elem=num_file_elem(team_sta);
	teams_sta=read_teams_sta(file_elem);

	#if defined (DEBUG)
	printf("Siralama Sekli:%s||Siralanma Turu:%d||ELEM_SIZE:%d\n",sort_by,w_sort,file_elem);
	#endif

	if(strcmp(sort_by,year)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.year<teams_sta[empty-1].year)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,year)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.year>teams_sta[empty-1].year)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,points)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.points<teams_sta[empty-1].points)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,points)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.points>teams_sta[empty-1].points)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,wins)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.wins<teams_sta[empty-1].wins)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,wins)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.wins>teams_sta[empty-1].wins)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,loses)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.loses<teams_sta[empty-1].loses)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,loses)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.loses>teams_sta[empty-1].loses)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,draws)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.draws<teams_sta[empty-1].draws)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,draws)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.draws>teams_sta[empty-1].draws)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,goals_for)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.goals_for<teams_sta[empty-1].goals_for)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,goals_for)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.goals_for>teams_sta[empty-1].goals_for)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,goals_against)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.goals_against<teams_sta[empty-1].goals_against)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,goals_against)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.goals_against>teams_sta[empty-1].goals_against)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,goals_difference)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.goals_difference<teams_sta[empty-1].goals_difference)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,goals_difference)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  current.goals_difference>teams_sta[empty-1].goals_difference)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,team_name)==0 && w_sort==1)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.team_name,teams_sta[empty-1].team_name)<0)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}
	else if(strcmp(sort_by,team_name)==0 && w_sort==2)
	{
		for(i=1;i<file_elem;i++)
		{
			current=teams_sta[i];
			empty=i;

			while(empty!=0 && 
				  strcmp(current.team_name,teams_sta[empty-1].team_name)>0)
			{
				teams_sta[empty]=teams_sta[empty-1];
				--empty;
			}
			teams_sta[empty]=current;	
		}
	}

	printf("\n");
	for(i=0;i<file_elem;i++)
	{
		show_team_sta(fields,teams_sta[i],field_size);
	}
	printf("\n");

	free(teams_sta);

}

char *break_sort(char * where_sort, int *w_sort){

	char by[]="by";
	char asc[]="asc";
	char desc[]="desc";

 	char *sort_by;

	while(strcmp(where_sort,by)!=0)
	{
		pass_space_select(where_sort);
		where_sort = strtok (NULL, ", ");
	}

	pass_space_select(where_sort);
	where_sort = strtok (NULL, " ");
	
	sort_by=(char *)malloc((strlen(where_sort)+1)*sizeof(char));
	strcpy(sort_by,where_sort);
	#if defined (DEBUG)
		printf("\nSiralama Sekli:%s",sort_by);
	#endif
	pass_space_select(where_sort);
	where_sort = strtok (NULL, " ");

	if(strcmp(where_sort,asc)==0)
	{
		#if defined (DEBUG)
			printf(" >> Artan siralama");
		#endif
		*w_sort=1;
	}
	else if (strcmp(where_sort,desc)==0)
	{
		#if defined (DEBUG)
			printf(">> Azalan siralama\n");
		#endif
		*w_sort=2;
	}
	else
	{
		printf("Kod hatali");
		*w_sort=-1;
	}

	return sort_by;

}

part_delete(char * command){

	char *p;
	char from[]="from";
	char teams[]="teams";
	char players[]="players";
	char team_sta[]="team_statistics";
	char player_sta[]="player_statistics";
	char * where_sort;

	int i=0;
	teams_t * elem_teams;
	players_t * elem_players;
	teams_sta_t * elem_team_sta;
	players_sta_t * elem_player_sta;

	int s_kind;
	int *select_kind=&s_kind;

	int where_size;
	int *where_size_p=&where_size;

	char ** where_fields;

	int elem_size;

	where_sort=search_where_sort(command,&s_kind);
	where_fields=break_where(where_sort,&where_size);

	p = strtok (command, " ");

	while(strcmp(p,from)!=0)
	{
		pass_space_select(p);
		p = strtok (NULL, " ");
	}

	pass_space_select(p);
	p = strtok (NULL, " ");
	
	#if defined (DEBUG)
		printf("Table name: %s",p);
	#endif

	if(strcmp(p,teams)==0)
	{
		elem_size=num_file_elem(teams);
		elem_teams=read_teams(elem_size);
	#if defined (DEBUG)
		printf("ELEM SIZE:%d",elem_size);
	#endif
		delete_teams(where_fields,elem_teams,elem_size);
		free(elem_teams);
		free(where_fields[0]);
		free(where_fields);
	}
	else if(strcmp(p,players)==0)
	{
		elem_size=num_file_elem(players);
		elem_players=read_players(elem_size);
	#if defined (DEBUG)
		printf("ELEM SIZE:%d",elem_size);
	#endif
		delete_players(where_fields,elem_players,elem_size);
		free(elem_players);
		free(where_fields[0]);
		free(where_fields);	
	}	
	else if(strcmp(p,team_sta)==0)
	{
		elem_size=num_file_elem(team_sta);
		elem_team_sta=read_teams_sta(elem_size);
	#if defined (DEBUG)
		printf("ELEM SIZE:%d",elem_size);
	#endif
		del_teams_sta(where_fields,elem_team_sta,elem_size);
		free(elem_team_sta);
		free(where_fields[0]);
		free(where_fields);	
	}	
	else if(strcmp(p,player_sta)==0)
	{
		elem_size=num_file_elem(player_sta);
		elem_player_sta=read_players_sta(elem_size);
	#if defined (DEBUG)
		printf("ELEM SIZE:%d",elem_size);
	#endif
		del_players_sta(where_fields,elem_player_sta,elem_size);
		free(elem_player_sta);
		free(where_fields[0]);
		free(where_fields);	
	}
}

void delete_teams(char ** where_fields,teams_t *elem_teams,int elem_size){

	char team_name[]="team_name";
	char city[]="city";
	char stadium[]="stadium";
	char founding_date[]="founding_date";
	char colors[]="colors";
	char team[]="teams";
	char del[]="XOX--XOX";
	int del2=-9999;
	char all[]="all";

	int i;
	int status=0;

	FILE * file;

	#if defined (DEBUG)
		printf(" Where Kosullari>>%s/%s\n",where_fields[0],where_fields[1]);
	#endif

	if(strcmp(where_fields[0],all)==0 && strcmp(where_fields[1],all)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			strcpy(elem_teams[i].team_name,del);
			strcpy(elem_teams[i].city,del);
			strcpy(elem_teams[i].stadium,del);
			strcpy(elem_teams[i].colors,del);
			elem_teams[i].founding_date=del2;
			status++;
		}
	}
	else if(strcmp(where_fields[0],team_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_teams[i].team_name,where_fields[1])==0)
			{
				strcpy(elem_teams[i].team_name,del);
				strcpy(elem_teams[i].city,del);
				strcpy(elem_teams[i].stadium,del);
				strcpy(elem_teams[i].colors,del);
				elem_teams[i].founding_date=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],city)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_teams[i].city,where_fields[1])==0)
			{
				strcpy(elem_teams[i].team_name,del);
				strcpy(elem_teams[i].city,del);
				strcpy(elem_teams[i].stadium,del);
				strcpy(elem_teams[i].colors,del);
				elem_teams[i].founding_date=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],stadium)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_teams[i].stadium,where_fields[1])==0)
			{
				strcpy(elem_teams[i].team_name,del);
				strcpy(elem_teams[i].city,del);
				strcpy(elem_teams[i].stadium,del);
				strcpy(elem_teams[i].colors,del);
				elem_teams[i].founding_date=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],founding_date)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams[i].founding_date==atoi(where_fields[1]))
			{
				strcpy(elem_teams[i].team_name,del);
				strcpy(elem_teams[i].city,del);
				strcpy(elem_teams[i].stadium,del);
				strcpy(elem_teams[i].colors,del);
				elem_teams[i].founding_date=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],colors)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_teams[i].colors,where_fields[1])==0)
			{
				strcpy(elem_teams[i].team_name,del);
				strcpy(elem_teams[i].city,del);
				strcpy(elem_teams[i].stadium,del);
				strcpy(elem_teams[i].colors,del);
				elem_teams[i].founding_date=del2;
				status++;
			}
		}
	}

	if(status>0)
	{
		file=fopen("teams.bin","wb");
	
		for(i=0;i<elem_size;i++)
		{
			write_team(file,elem_teams[i]);
		}

		fclose(file);

		printf(">> %d Oge Silindi !!\n",status);
	}
	else
		printf(">> Silinecek Oge Bulunamadi !! \n");



	#if defined (DEBUG)
		printf("\n** Dosyanin Su Anki Hali **");
		read_table(1);
	#endif

}

void delete_players(char **where_fields,players_t *elem_players,int elem_size){

	char player_name[]="player_name";
	char team_name[]="team_name";
	char birth_date[]="birth_date";
	char origin[]="origin";
	char position[]="position";
	char salary[]="salary";
	char del[]="XOX--XOX";
	int del2=-9999;
	char all[]="all";

	int i;
	int status=0;

	FILE * file;

	#if defined (DEBUG)
		printf(" Where Kosullari>>%s/%s\n",where_fields[0],where_fields[1]);
	#endif

	if(strcmp(where_fields[0],all)==0 && strcmp(where_fields[1],all)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			strcpy(elem_players[i].player_name,del);
			strcpy(elem_players[i].team_name,del);
			strcpy(elem_players[i].origin,del);
			strcpy(elem_players[i].position,del);
			elem_players[i].birth_date=del2;
			elem_players[i].salary=del2;
			status++;
		}
	}	
	else if(strcmp(where_fields[0],player_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_players[i].player_name,where_fields[1])==0)
			{
				strcpy(elem_players[i].player_name,del);
				strcpy(elem_players[i].team_name,del);
				strcpy(elem_players[i].origin,del);
				strcpy(elem_players[i].position,del);
				elem_players[i].birth_date=del2;
				elem_players[i].salary=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],team_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_players[i].team_name,where_fields[1])==0)
			{
				strcpy(elem_players[i].player_name,del);
				strcpy(elem_players[i].team_name,del);
				strcpy(elem_players[i].origin,del);
				strcpy(elem_players[i].position,del);
				elem_players[i].birth_date=del2;
				elem_players[i].salary=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],origin)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_players[i].origin,where_fields[1])==0)
			{
				strcpy(elem_players[i].player_name,del);
				strcpy(elem_players[i].team_name,del);
				strcpy(elem_players[i].origin,del);
				strcpy(elem_players[i].position,del);
				elem_players[i].birth_date=del2;
				elem_players[i].salary=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],birth_date)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_players[i].birth_date==atoi(where_fields[1]))
			{
				strcpy(elem_players[i].player_name,del);
				strcpy(elem_players[i].team_name,del);
				strcpy(elem_players[i].origin,del);
				strcpy(elem_players[i].position,del);
				elem_players[i].birth_date=del2;
				elem_players[i].salary=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],position)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_players[i].position,where_fields[1])==0)
			{
				strcpy(elem_players[i].player_name,del);
				strcpy(elem_players[i].team_name,del);
				strcpy(elem_players[i].origin,del);
				strcpy(elem_players[i].position,del);
				elem_players[i].birth_date=del2;
				elem_players[i].salary=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],salary)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_players[i].salary==atoi(where_fields[1]))
			{
				strcpy(elem_players[i].player_name,del);
				strcpy(elem_players[i].team_name,del);
				strcpy(elem_players[i].origin,del);
				strcpy(elem_players[i].position,del);
				elem_players[i].birth_date=del2;
				elem_players[i].salary=del2;
				status++;
			}
		}
	}

	if(status>0)
	{
	
		file=fopen("players.bin","wb");
	
		for(i=0;i<elem_size;i++)
		{
			write_player(file,elem_players[i]);
		}

		fclose(file);
		printf(">> %d Oge Silindi !!\n",status);
	}
	else
		printf(">> Silinecek Oge Bulunamadi !! \n");

	#if defined (DEBUG)
		printf("\n** Dosyanin Su Anki Hali **");
		read_table(2);
	#endif
}

void del_teams_sta(char **where_fields,teams_sta_t *elem_teams_sta,int elem_size){

	char team_sta[]="team_statistics";
	char year[]="year";
	char team_name[]="team_name";
	char points[]="points";
	char wins[]="wins";
	char loses[]="loses";
	char draws[]="draws";
	char goals_for[]="goals_for";
	char goals_against[]="goals_against";
	char goals_difference[]="goals_difference";
	char all[]="all";

	char del1[]="XOX--XOX";
	int del2=-9999;

	int i;
	int status=0;

	FILE * file;

	#if defined (DEBUG)
		printf(" Where Kosullari>>%s/%s\n",where_fields[0],where_fields[1]);
	#endif

	if(strcmp(where_fields[0],all)==0 && strcmp(where_fields[1],all)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			strcpy(elem_teams_sta[i].team_name,del1);
			elem_teams_sta[i].year=del2;
			elem_teams_sta[i].points=del2;
			elem_teams_sta[i].wins=del2;
			elem_teams_sta[i].loses=del2;
			elem_teams_sta[i].draws=del2;
			elem_teams_sta[i].goals_for=del2;
			elem_teams_sta[i].goals_against=del2;
			elem_teams_sta[i].goals_difference=del2;
			status++;
		}
	}
	else if(strcmp(where_fields[0],year)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams_sta[i].year==atoi(where_fields[1]))
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],points)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams_sta[i].points==atoi(where_fields[1]))
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],wins)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams_sta[i].wins==atoi(where_fields[1]))
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],loses)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams_sta[i].loses==atoi(where_fields[1]))
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],draws)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams_sta[i].draws==atoi(where_fields[1]))
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],goals_for)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams_sta[i].goals_for==atoi(where_fields[1]))
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],goals_against)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams_sta[i].goals_against==atoi(where_fields[1]))
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],goals_difference)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_teams_sta[i].goals_difference==atoi(where_fields[1]))
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],team_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_teams_sta[i].team_name,where_fields[1])==0)
			{
				strcpy(elem_teams_sta[i].team_name,del1);
				elem_teams_sta[i].year=del2;
				elem_teams_sta[i].points=del2;
				elem_teams_sta[i].wins=del2;
				elem_teams_sta[i].loses=del2;
				elem_teams_sta[i].draws=del2;
				elem_teams_sta[i].goals_for=del2;
				elem_teams_sta[i].goals_against=del2;
				elem_teams_sta[i].goals_difference=del2;
				status++;
			}
		}
	}


	if(status>0)
	{
		file=fopen("team_statistics.bin","wb");
	
		for(i=0;i<elem_size;i++)
		{
			write_teams_sta(file,elem_teams_sta[i]);
		}

		fclose(file);
		printf(">> %d Oge Silindi !!\n",status);
	}
	else
		printf(">> Silinecek Oge Bulunamadi !! \n");
	
	#if defined (DEBUG)
		printf("\n** Dosyanin Su Anki Hali **");
		read_table(3);
	#endif
}

void del_players_sta(char **where_fields,players_sta_t *elem_players_sta,int elem_size){

	char year[]="year";
	char player_name[]="player_name";
	char goals[]="goals";
	char assists[]="assists";
	char red_cards[]="red_cards";
	char yellow_cards[]="yellow_cards";
	char all[]="all";

	char del1[]="XOX--XOX";
	int del2=-9999;

	int i;
	int status=0;

	FILE * file;

	#if defined (DEBUG)
		printf(" Where Kosullari>>%s/%s",where_fields[0],where_fields[1]);
	#endif

	if(strcmp(where_fields[0],all)==0 && strcmp(where_fields[1],all)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			strcpy(elem_players_sta[i].player_name,del1);
			elem_players_sta[i].year=del2;
			elem_players_sta[i].goals=del2;
			elem_players_sta[i].assists=del2;
			elem_players_sta[i].red_cards=del2;
			elem_players_sta[i].yellow_cards=del2;
			status++;
		}
	}
	else if(strcmp(where_fields[0],year)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_players_sta[i].year==atoi(where_fields[1]))
			{
				strcpy(elem_players_sta[i].player_name,del1);
				elem_players_sta[i].year=del2;
				elem_players_sta[i].goals=del2;
				elem_players_sta[i].assists=del2;
				elem_players_sta[i].red_cards=del2;
				elem_players_sta[i].yellow_cards=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],goals)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_players_sta[i].goals==atoi(where_fields[1]))
			{
				strcpy(elem_players_sta[i].player_name,del1);
				elem_players_sta[i].year=del2;
				elem_players_sta[i].goals=del2;
				elem_players_sta[i].assists=del2;
				elem_players_sta[i].red_cards=del2;
				elem_players_sta[i].yellow_cards=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],assists)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_players_sta[i].assists==atoi(where_fields[1]))
			{
				strcpy(elem_players_sta[i].player_name,del1);
				elem_players_sta[i].year=del2;
				elem_players_sta[i].goals=del2;
				elem_players_sta[i].assists=del2;
				elem_players_sta[i].red_cards=del2;
				elem_players_sta[i].yellow_cards=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],red_cards)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_players_sta[i].red_cards==atoi(where_fields[1]))
			{
				strcpy(elem_players_sta[i].player_name,del1);
				elem_players_sta[i].year=del2;
				elem_players_sta[i].goals=del2;
				elem_players_sta[i].assists=del2;
				elem_players_sta[i].red_cards=del2;
				elem_players_sta[i].yellow_cards=del2;
				status++;
			}
		}
	}
	else if(strcmp(where_fields[0],yellow_cards)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(elem_players_sta[i].yellow_cards==atoi(where_fields[1]))
			{
				strcpy(elem_players_sta[i].player_name,del1);
				elem_players_sta[i].year=del2;
				elem_players_sta[i].goals=del2;
				elem_players_sta[i].assists=del2;
				elem_players_sta[i].red_cards=del2;
				elem_players_sta[i].yellow_cards=del2;
				status++;
			}
		}
	}	
	else if(strcmp(where_fields[0],player_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(elem_players_sta[i].player_name,where_fields[1])==0)
			{
				strcpy(elem_players_sta[i].player_name,del1);
				elem_players_sta[i].year=del2;
				elem_players_sta[i].goals=del2;
				elem_players_sta[i].assists=del2;
				elem_players_sta[i].red_cards=del2;
				elem_players_sta[i].yellow_cards=del2;
				status++;
			}
		}
	}

	if(status>0)
	{
		file=fopen("player_statistics.bin","wb");
	
		for(i=0;i<elem_size;i++)
		{
			write_players_sta(file,elem_players_sta[i]);
		}

		fclose(file);
		printf(">> %d Oge Silindi !!\n",status);
	}
	else
		printf(">> Silinecek Oge Bulunamadi !! \n");	



	#if defined (DEBUG)
		printf("\n** Dosyanin Su Anki Hali **");
		read_table(4);
	#endif

}

int select_teams(char ** fields, int field_size){

	char team[]="teams";
	int i;
	int empty;
	int file_elem;

	teams_t * teams;

	file_elem=num_file_elem(team);
	teams=read_teams(file_elem);

	for(i=0;i<file_elem;i++)
	{
		show_teams(fields,teams[i],field_size);
	}
	
	free(teams);

}

int select_players(char **fields ,int field_size){

	char player[]="players";
	int i;
	int empty;
	int file_elem;

	players_t * players;

	file_elem=num_file_elem(player);
	players=read_players(file_elem);

	for(i=0;i<file_elem;i++)
	{
		show_players(fields,players[i],field_size);
	}

	free(players);
}

int select_team_sta(char **fields ,int field_size){

	char teams_sta[]="team_statistics";
	int i;
	int empty;
	int file_elem;

	teams_sta_t * team_sta;

	file_elem=num_file_elem(teams_sta);
	team_sta=read_teams_sta(file_elem);

	for(i=0;i<file_elem;i++)
	{
		show_team_sta(fields,team_sta[i],field_size);
	}
	
	free(team_sta);
}

int select_player_sta(char **fields ,int field_size){

	char players_sta[]="player_statistics";
	int i;
	int empty;
	int file_elem;

	players_sta_t * player_sta;

	file_elem=num_file_elem(players_sta);
	player_sta=read_players_sta(file_elem);

	for(i=0;i<file_elem;i++)
	{
		show_player_sta(fields,player_sta[i],field_size);
	}
	
	free(player_sta);
}

int part_update(char * command){

	char *p;
	char from[]="from";
	char team[]="teams";
	char player[]="players";
	char team_sta[]="team_statistics";
	char player_sta[]="player_statistics";
	char in[]="in";
	char * where_sort;

	teams_t * teams;
	players_t * players;
	teams_sta_t * teams_sta;
	players_sta_t * players_sta;

	int s_kind;
	int *select_kind=&s_kind;

	int where_size;
	int *where_size_p=&where_size;

	char ** where_fields;
	char ** select_fields;

	int field_num;
	int i=0;

	char * table_name;
	int elem_size;

 	char *data;
	char **pp;

	
	field_num=field_number(command);
	#if defined (DEBUG)
		printf("F_SIZE:%d ",field_num);
	#endif
	where_sort=search_where_sort(command,&s_kind);
	where_fields=break_where(where_sort,&where_size);

	field_num=(field_num)*2; 

 	data=(char *)malloc(field_num*20*sizeof(char));
	pp=(char**)malloc(field_num*sizeof(char*));
	
	for(i=0;i<field_num;i++)
	{
		pp[i]=data+i*20;
	}
	
	i=0;
	p= strtok (command, " ");
	p= strtok (NULL, "=, ");

	while(strcmp(p,in)!=0)
	{
		strcpy(pp[i],p);
		pass_space_select(where_sort);
		i++;
		p = strtok (NULL, "=, ");
	}

	#if defined (DEBUG)
		printf("\nGuncellenecek Bilgiler >>\n");
		for(i=0;i<field_num;i++)
		{
			printf("%s-",pp[i]);
		}
	#endif

	p= strtok (NULL, " ");
	#if defined (DEBUG)
		printf("\nTable name >> %s",p);
	#endif

	if(strcmp(p,team)==0)
	{
		elem_size=num_file_elem(team);
		teams=read_teams(elem_size);
		update_teams(pp,where_fields,teams,field_num,where_size,elem_size);
		free(where_fields[0]);
		free(where_fields);
		free(teams);
	}
	else if(strcmp(p,player)==0)
	{
		elem_size=num_file_elem(player);
		players=read_players(elem_size);
		update_players(pp,where_fields,players,field_num,where_size,elem_size);
		free(where_fields[0]);
		free(where_fields);
		free(players);
	}
	else if(strcmp(p,team_sta)==0)
	{
		elem_size=num_file_elem(team_sta);
		teams_sta=read_teams_sta(elem_size);
	update_teams_sta(pp,where_fields,teams_sta,field_num,where_size,elem_size);
		free(where_fields[0]);
		free(where_fields);
		free(teams_sta);
	}
	else if(strcmp(p,player_sta)==0)
	{
		elem_size=num_file_elem(player_sta);
		players_sta=read_players_sta(elem_size);
 update_players_sta(pp,where_fields,players_sta,field_num,where_size,elem_size);
		free(where_fields[0]);
		free(where_fields);
		free(players_sta);
	}



}

void update_players(char ** s_fields,char ** w_fields,players_t * players,int s_size,int w_size,int elem_size){

	char player_name[]="player_name";
	char team_name[]="team_name";
	char birth_date[]="birth_date";
	char origin[]="origin";
	char position[]="position";
	char salary[]="salary";

	int i;
	int j;
	int status=0;

	FILE * file;

	if(strcmp(w_fields[0],player_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(players[i].player_name,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(players[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],birth_date)==0)
					{	
						players[i].birth_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(players[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],origin)==0)
					{
						strcpy(players[i].origin,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],position)==0)
					{
						strcpy(players[i].position,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],salary)==0)
					{	
						players[i].salary=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],team_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(players[i].team_name,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(players[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],birth_date)==0)
					{	
						players[i].birth_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(players[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],origin)==0)
					{
						strcpy(players[i].origin,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],position)==0)
					{
						strcpy(players[i].position,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],salary)==0)
					{	
						players[i].salary=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],origin)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(players[i].origin,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(players[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],birth_date)==0)
					{	
						players[i].birth_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(players[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],origin)==0)
					{
						strcpy(players[i].origin,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],position)==0)
					{
						strcpy(players[i].position,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],salary)==0)
					{	
						players[i].salary=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],position)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(players[i].position,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(players[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],birth_date)==0)
					{	
						players[i].birth_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(players[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],origin)==0)
					{
						strcpy(players[i].origin,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],position)==0)
					{
						strcpy(players[i].position,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],salary)==0)
					{	
						players[i].salary=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],salary)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(players[i].salary==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(players[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],birth_date)==0)
					{	
						players[i].birth_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(players[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],origin)==0)
					{
						strcpy(players[i].origin,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],position)==0)
					{
						strcpy(players[i].position,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],salary)==0)
					{	
						players[i].salary=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],birth_date)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(players[i].birth_date==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(players[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],birth_date)==0)
					{	
						players[i].birth_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(players[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],origin)==0)
					{
						strcpy(players[i].origin,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],position)==0)
					{
						strcpy(players[i].position,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],salary)==0)
					{	
						players[i].salary=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}

	#if defined (DEBUG)
		printf(">> Guncellenmis strcut arrayi >> \n\n");
		for(i=0;i<elem_size;i++)
		{
			printf("%s|",players[i].player_name);
			printf("%s|",players[i].team_name);
			printf("%d|",players[i].birth_date);
			printf("%s|",players[i].origin);
			printf("%s|",players[i].position);
			printf("%d|\n",players[i].salary);
		}
	#endif

	if(status>0)
	{
		file=fopen("players.bin","wb");
	
		for(i=0;i<elem_size;i++)
		{
			write_player(file,players[i]);
		}
			
		fclose(file);
		printf(">> %d Oge Guncelledi !!\n",status);
	}
	else
		printf(">> Guncellenecek Oge Bulunamadi !! \n");

	#if defined (DEBUG)
		printf("\n>> Dosyanin suanki hali >> \n");
		read_table(2);
	#endif

}


void update_teams(char ** s_fields,char ** w_fields,teams_t * teams,int s_size,int w_size,int elem_size){
	
	char team_name[]="team_name";
	char city[]="city";
	char stadium[]="stadium";
	char founding_date[]="founding_date";
	char colors[]="colors";

	int i;
	int j;
	int status=0;

	FILE * file;

	if(strcmp(w_fields[0],team_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(teams[i].team_name,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],founding_date)==0)
					{	
						teams[i].founding_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],city)==0)
					{
						strcpy(teams[i].city,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],stadium)==0)
					{
						strcpy(teams[i].stadium,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],colors)==0)
					{
						strcpy(teams[i].colors,s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],city)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(teams[i].city,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],founding_date)==0)
					{	
						teams[i].founding_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],city)==0)
					{
						strcpy(teams[i].city,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],stadium)==0)
					{
						strcpy(teams[i].stadium,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],colors)==0)
					{
						strcpy(teams[i].colors,s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],stadium)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(teams[i].stadium,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],founding_date)==0)
					{	
						teams[i].founding_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],city)==0)
					{
						strcpy(teams[i].city,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],stadium)==0)
					{
						strcpy(teams[i].stadium,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],colors)==0)
					{
						strcpy(teams[i].colors,s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],colors)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(strcmp(teams[i].colors,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],founding_date)==0)
					{	
						teams[i].founding_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],city)==0)
					{
						strcpy(teams[i].city,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],stadium)==0)
					{
						strcpy(teams[i].stadium,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],colors)==0)
					{
						strcpy(teams[i].colors,s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],founding_date)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(teams[i].founding_date==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],founding_date)==0)
					{	
						teams[i].founding_date=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],city)==0)
					{
						strcpy(teams[i].city,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],stadium)==0)
					{
						strcpy(teams[i].stadium,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],colors)==0)
					{
						strcpy(teams[i].colors,s_fields[j+1]);
					}			
				}
				status++;
			}
		}
	}

	#if defined (DEBUG)
		printf(">> Guncellenmis strcut arrayi >> \n\n");
		for(i=0;i<elem_size;i++)
		{
			printf("%s|",teams[i].team_name);
			printf("%s|",teams[i].city);
			printf("%d|",teams[i].founding_date);
			printf("%s|",teams[i].stadium);
			printf("%s|\n",teams[i].colors);
		}
	#endif	

	if(status>0)
	{
		file=fopen("teams.bin","wb");
	
		for(i=0;i<elem_size;i++)
		{
			write_team(file,teams[i]);
		}

		fclose(file);
		printf(">> %d Oge Guncelledi !!\n",status);
	}
	else
		printf(">> Guncellenecek Oge Bulunamadi !! \n");


	#if defined (DEBUG)
		printf("\n>> Dosyanin suanki hali >> \n");
		read_table(1);
	#endif

}

void update_teams_sta(char ** s_fields,char ** w_fields,teams_sta_t * teams_sta
,int s_size,int w_size,int elem_size)
{

	char year[]="year";
	char team_name[]="team_name";
	char points[]="points";
	char wins[]="wins";
	char loses[]="loses";
	char draws[]="draws";
	char goals_for[]="goals_for";
	char goals_against[]="goals_against";
	char goals_difference[]="goals_difference";

	int i;
	int j;
	int status=0;

	FILE * file;

	if(strcmp(w_fields[0],year)==0)
	{
		for(i=0;i<elem_size;i++)
		{
			if(teams_sta[i].year==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],points)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(teams_sta[i].points==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],wins)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(teams_sta[i].wins==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],loses)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(teams_sta[i].loses==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],draws)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(teams_sta[i].draws==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],goals_for)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(teams_sta[i].goals_for==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],goals_against)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(teams_sta[i].goals_against==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],goals_difference)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(teams_sta[i].goals_difference==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],team_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(strcmp(teams_sta[i].team_name,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],team_name)==0)
					{
						strcpy(teams_sta[i].team_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],points)==0)
					{	
						teams_sta[i].points=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],wins)==0)
					{
						teams_sta[i].wins=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],loses)==0)
					{
						teams_sta[i].loses=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],draws)==0)
					{
						teams_sta[i].draws=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_for)==0)
					{
						teams_sta[i].goals_for=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_against)==0)
					{
						teams_sta[i].goals_against=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals_difference)==0)
					{
						teams_sta[i].goals_difference=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{
						teams_sta[i].year=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}


	#if defined (DEBUG)
		printf(">> Guncellenmis strcut arrayi >> \n\n");
		for(i=0;i<elem_size;i++)
		{
			printf("%d|",teams_sta[i].year);	
			printf("%s|",teams_sta[i].team_name);
			printf("%d|",teams_sta[i].points);
			printf("%d|",teams_sta[i].wins);
			printf("%d|",teams_sta[i].loses);
			printf("%d|",teams_sta[i].draws);
			printf("%d|",teams_sta[i].goals_for);
			printf("%d|",teams_sta[i].goals_against);
			printf("%d|\n",teams_sta[i].goals_difference);
		}
	#endif

	if(status>0)
	{
		file=fopen("team_statistics.bin","wb");
	
		for(i=0;i<elem_size;i++)
		{
			write_teams_sta(file,teams_sta[i]);
		}

		fclose(file);
		printf(">> %d Oge Guncelledi !!\n",status);
	}
	else
		printf(">> Guncellenecek Oge Bulunamadi !! \n");

	#if defined (DEBUG)
		printf("\n>> Dosyanin suanki hali >> \n");
		read_table(3);
	#endif

}

void update_players_sta(char ** s_fields,char ** w_fields,players_sta_t * 
player_sta,int s_size,int w_size,int elem_size)
{

	char year[]="year";
	char player_name[]="player_name";
	char goals[]="goals";
	char assists[]="assists";
	char red_cards[]="red_cards";
	char yellow_cards[]="yellow_cards";

	int i;
	int j;
	int status=0;

	FILE * file;

	if(strcmp(w_fields[0],year)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(player_sta[i].year==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(player_sta[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{	
						player_sta[i].year=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals)==0)
					{
						player_sta[i].goals=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],assists)==0)
					{
						player_sta[i].assists=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],red_cards)==0)
					{
						player_sta[i].red_cards=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],yellow_cards)==0)
					{
						player_sta[i].yellow_cards=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],goals)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(player_sta[i].goals==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(player_sta[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{	
						player_sta[i].year=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals)==0)
					{
						player_sta[i].goals=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],assists)==0)
					{
						player_sta[i].assists=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],red_cards)==0)
					{
						player_sta[i].red_cards=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],yellow_cards)==0)
					{
						player_sta[i].yellow_cards=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],assists)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(player_sta[i].assists==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(player_sta[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{	
						player_sta[i].year=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals)==0)
					{
						player_sta[i].goals=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],assists)==0)
					{
						player_sta[i].assists=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],red_cards)==0)
					{
						player_sta[i].red_cards=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],yellow_cards)==0)
					{
						player_sta[i].yellow_cards=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],red_cards)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(player_sta[i].red_cards==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(player_sta[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{	
						player_sta[i].year=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals)==0)
					{
						player_sta[i].goals=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],assists)==0)
					{
						player_sta[i].assists=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],red_cards)==0)
					{
						player_sta[i].red_cards=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],yellow_cards)==0)
					{
						player_sta[i].yellow_cards=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],yellow_cards)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(player_sta[i].yellow_cards==atoi(w_fields[1]))
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(player_sta[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{	
						player_sta[i].year=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals)==0)
					{
						player_sta[i].goals=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],assists)==0)
					{
						player_sta[i].assists=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],red_cards)==0)
					{
						player_sta[i].red_cards=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],yellow_cards)==0)
					{
						player_sta[i].yellow_cards=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}
	else if(strcmp(w_fields[0],player_name)==0)
	{
		for(i=0;i<elem_size;i++)
		{	
			if(strcmp(player_sta[i].player_name,w_fields[1])==0)
			{
				for(j=0;j<s_size;j=j+2)
				{
					if(strcmp(s_fields[j],player_name)==0)
					{
						strcpy(player_sta[i].player_name,s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],year)==0)
					{	
						player_sta[i].year=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],goals)==0)
					{
						player_sta[i].goals=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],assists)==0)
					{
						player_sta[i].assists=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],red_cards)==0)
					{
						player_sta[i].red_cards=atoi(s_fields[j+1]);
					}
					else if(strcmp(s_fields[j],yellow_cards)==0)
					{
						player_sta[i].yellow_cards=atoi(s_fields[j+1]);
					}
				}
				status++;
			}
		}
	}

	#if defined (DEBUG)
		printf(">> Guncellenmis strcut arrayi >> \n\n");
		for(i=0;i<elem_size;i++)
		{
			printf("%d|",player_sta[i].year);	
			printf("%s|",player_sta[i].player_name);
			printf("%d|",player_sta[i].goals);
			printf("%d|",player_sta[i].assists);
			printf("%d|",player_sta[i].red_cards);
			printf("%d|\n",player_sta[i].yellow_cards);
		}
	#endif

	if(status>0)
	{
		file=fopen("player_statistics.bin","wb");
	
		for(i=0;i<elem_size;i++)
		{
			write_players_sta(file,player_sta[i]);
		}

		fclose(file);
		printf(">> %d Oge Guncelledi !!\n",status);
	}
	else
		printf(">> Guncellenecek Oge Bulunamadi !! \n");

	#if defined (DEBUG)
		printf("\n>> Dosyanin suanki hali >> \n");
	read_table(4);
	#endif

}


void smart1()
{
	char teams_sta[]="team_statistics";
	char teams[]="teams";

	teams_t * team;
	teams_sta_t * team_sta;
	teams_sta_t current;

	int i;
	int j;
	int empty;
	int team_size;
	int team_sta_size;

	team_sta_size=num_file_elem(teams_sta);
	team_sta=read_teams_sta(team_sta_size);

	team_size=num_file_elem(teams);
	team=read_teams(team_size);

	/*printf("%d",team_size);
	printf("%d",team_sta_size);*/

	for(i=1;i<team_sta_size;i++)
	{
		current=team_sta[i];
		empty=i;

		while(empty!=0 && current.points>team_sta[empty-1].points)
		{
			team_sta[empty]=team_sta[empty-1];
			--empty;
		}
		team_sta[empty]=current;	
	}
	
	/*printf("\n");
	for(i=0;i<team_sta_size;i++)
	{
		printf("%d",team_sta[i].points);
	}
	printf("\n");*/
	
	for(i=0;i<team_sta_size;i++)
	{
		if(team_sta[i].year==2010 && team_sta[i].points>20)
		{
			for(j=0;j<team_size;j++)
			{
				if(strcmp(team_sta[i].team_name,team[j].team_name)==0)
				{
					printf("%s|",team[j].team_name);
					printf("%s|",team[j].stadium);			
					printf("%d\n",team_sta[i].points);
				}

			}

		}

	}
}

void smart2()
{

	char players_sta[]="player_statistics";
	char players[]="players";
	char gk[]="GK";

	players_t * player;
	players_sta_t * player_sta;
	players_sta_t current;

	int i;
	int j;
	int empty;
	int player_size;
	int player_sta_size;

	player_sta_size=num_file_elem(players_sta);
	player_sta=read_players_sta(player_sta_size);

	player_size=num_file_elem(players);
	player=read_players(player_size);


	for(i=1;i<player_sta_size;i++)
	{
		current=player_sta[i];
		empty=i;

		while(empty!=0 && current.red_cards>player_sta[empty-1].red_cards)
		{
			player_sta[empty]=player_sta[empty-1];
			--empty;
		}
		player_sta[empty]=current;	
	}

	/*printf("\n");
	for(i=0;i<player_sta_size;i++)
	{
		printf("%d",player_sta[i].red_cards);
	}
	printf("\n");*/

	for(i=0;i<player_sta_size;i++)
	{
		if(player_sta[i].red_cards>0)
		{
			for(j=0;j<player_size;j++)
			{
				if(strcmp(player_sta[i].player_name,player[j].player_name)==0)
				{
					if(strcmp(player[i].position,gk)==0)
					{
						printf("%s|",player[j].player_name);
						printf("%s|",player[j].position);			
						printf("%d\n",player_sta[i].red_cards);
					}
				}
			}
		}
	}

}

void smart3()
{
	char players_sta[]="player_statistics";
	char players[]="players";
	char teams[]="teams";
	char city[]="istanbul";

	players_t * player;
	players_sta_t * player_sta;
	players_sta_t current;
	teams_t * team;

	int i;
	int j;
	int k;
	int empty;
	int team_size;
	int player_size;
	int player_sta_size;


	player_sta_size=num_file_elem(players_sta);
	player_sta=read_players_sta(player_sta_size);

	player_size=num_file_elem(players);
	player=read_players(player_size);

	team_size=num_file_elem(teams);
	team=read_teams(team_size);

	
	for(i=0;i<player_sta_size;i++)
	{
		if(player_sta[i].goals>10)
		{
			for(j=0;j<player_size;j++)
			{
				if(strcmp(player_sta[i].player_name,player[j].player_name)==0)
				{
					for(k=0;k<team_size;k++)
					{
						if(strcmp(team[k].city,city)==0)
						{
							printf("%s|",player[j].player_name);
							printf("%s|",team[k].city);			
							printf("%d\n",player_sta[j].goals);		
							k=team_size;
						}
					}
				}
			}
		}
	}
	
}

void part_smart(char *command)
{

	char stadium[]="stadium";
	char red_cards[]="red_cards";
	char goals[]="goals";

	char *p;
	
	p=strstr(command,stadium);

	if(p!=NULL)
	{
		smart1();
	}

	p=strstr(command,red_cards);

	if(p!=NULL)
	{
		smart2();
	}
	
	p=strstr(command,goals);

	if(p!=NULL)
	{
		smart3();
	}



}
