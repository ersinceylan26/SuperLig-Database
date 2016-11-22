# SuperLig-Database-in-C
In this project, I implemented a database system which allow users to manage team, player and statistical records in the SuperLig. Users can run queries to extract high level information from the database.

Command >> select 	
Pattern >> select field1, field2,.. from table_name
Return  >> Returns field1, field2,… of all records from table_name 
Use of  >> select team_name from teams

Command >> where 	
Pattern >> SELECT_STATEMENT where field_a=y 
Return  >> Returns field1, field2,… of records whose field is y from table_name
Use of  >> select colors, stadium from teams where team_name=fenerbahce 

Command >> sort 	
Pattern >> SELECT_STATEMENT sort by field1 asc
Return  >> Sorts the returned data from select statement by specified field. Sort may be in ascending (asc) or descending (desc) order. 	Use of  >> select team_name, founding_date from teams sort by founding_date asc 

Command >> insert
Pattern >> insert field1, field2,… to table_name
Return  >> Inserts given element to the database
Use of  >> insert ankaraspor,ankara,19_mayis,2005,mor-sari to teams

Command >> update
Pattern >> update field1, field2,… in table_name where field=y
Return  >> Update a record whose field is y in table_name
Use of  >> update team_name=osmanlispor, founding_date=2014 in teams where team_name=ankaraspor

Command >> delete
Pattern >> delete * from table_name where field=y
Return  >> Deletes a record from table_name whose field is y
Use of  >> delete * from teams where team_name=ankaraspor

q | Quits.


