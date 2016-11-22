# SuperLig-Database-in-C
In this project, I implemented a database system which allow users to manage team, player and statistical records in the SuperLig. Users can run queries to extract high level information from the database.



select 	select field1, field2,.. from table_name |	Returns field1, field2,… of all records from table_name |	select team_name from teams

where 	SELECT_STATEMENT where field_a=y |  Returns field1, field2,… of records whose field is y from table_name select colors, stadium from teams where team_name=fenerbahce 

sort 	SELECT_STATEMENT sort by field1 asc | Sorts the returned data from select statement by specified field. Sort may be in ascending (asc) or descending (desc) order. 	select team_name, founding_date from teams sort by founding_date asc 

insert | insert field1, field2,… to table_name | Inserts given element to the database | insert ankaraspor,ankara,19_mayis,2005,mor-sari to teams

update | update field1, field2,… in table_name where field=y | Update a record whose field is y in table_name | update team_name=osmanlispor, founding_date=2014 in teams where team_name=ankaraspor

delete | delete * from table_name where field=y | Deletes a record from table_name whose field is y | delete * from teams where team_name=ankaraspor

q | Quits.


