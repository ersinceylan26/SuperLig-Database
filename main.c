/*######################################################*/
/* HWTP_121044064_Ersin_CEYLAN.zip                 	    */
/* main.c											    */	
/*_______________   						 		    */
/*                    								    */
/* Written by Ersin CEYLAN	05/01/2015				    */
/*                                                      */
/*######################################################*/

#include "project.h"

int main (int argc,char * argv[])
{

	char command[CMD_SIZE];
	char command_temp[CMD_SIZE];
	char select[]="select";
	char insert[]="insert";
	char update[]="update";
	char delete[]="delete";
	char smart[]="smart";
	char q[]="q";
	char fn[]="fn";
	char r[]="r";
	char del1[]="delete * from player_statistics where all=all";
	char del2[]="delete * from teams where all=all";
	char del3[]="delete * from players where all=all";
	char del4[]="delete * from team_statistics where all=all";
	
	char *p;
	FILE * inp;
	char* status;
	int i;

	if(argc==3 && strcmp(argv[1],fn)==0)
	{
		inp=fopen(argv[2],"r");

		status=fgets(command,CMD_SIZE,inp);

		while(status!=0)
		{
			strcpy(command_temp,command);

			p = strtok (command_temp," ");
	
			if(strcmp(p,select)==0)
			{
				#if defined(DEBUG)
				printf("komut select\n");
				#endif
				part_select(command);
			}
			else if(strcmp(p,insert)==0)
			{
				#if defined(DEBUG)
				printf("komut insert\n");
				#endif
				part_insert(command);
			}
			else if (strcmp(p,delete)==0)
			{
				#if defined(DEBUG)
				printf("komut delete\n");
				#endif
				part_delete(command);
			}
			else if(strcmp(p,update)==0)
			{
				#if defined(DEBUG)
				printf("komut update\n");
				#endif
				part_update(command);
			}
			else if(strcmp(p,smart)==0)
			{
				#if defined(DEBUG)
				printf("komut smart\n");
				#endif
				part_smart(command);
			}

			status=fgets(command,CMD_SIZE,inp);
		}
	}
	else if(argc==2 && strcmp(argv[1],r)==0)
	{
		part_delete(del1);
		part_delete(del2);
		part_delete(del3);
		part_delete(del4);
		
	}
	else if(argc==4 && strcmp(argv[1],fn)==0 && strcmp(argv[3],r)==0)
	{
		
	}

	printf(">> Komut");

	gets(command);

	strcpy(command_temp,command);

	p = strtok (command_temp," ");
	
	while(strcmp(p,q)!=0)
	{
		if(strcmp(p,select)==0)
		{
			#if defined(DEBUG)
			printf("komut select\n");
			#endif
			part_select(command);
		}
		else if(strcmp(p,insert)==0)
		{
			#if defined(DEBUG)
			printf("komut insert\n");
			#endif
			part_insert(command);
		}
		else if (strcmp(p,delete)==0)
		{
			#if defined(DEBUG)
			printf("komut delete\n");
			#endif
			part_delete(command);
		}
		else if(strcmp(p,update)==0)
		{
			#if defined(DEBUG)
			printf("komut update\n");
			#endif
			part_update(command);
		}
		else if(strcmp(p,smart)==0)
		{
			#if defined(DEBUG)
			printf("komut smart\n");
			#endif
			part_smart(command);
		}

		status=gets(command);

		if(status==NULL)
		{
			printf("Komut alimi bitti");
			exit(1);
		}

		strcpy(command_temp,command);
		p = strtok (command_temp," ");


	}



}

