// profession职业系统 by Vast@pkuxkx 2009-06

#include <ansi.h>
#include <dbase.h>

mapping profs;
nosave string *all_profs = ({"alchemy", "blacksmithing", "cooking", "medicine", "pharmacy"});

mapping query_profs() 
{ 
	return profs; 
}

int set_prof(string prof, string arg)
{
	string *list;
	
				if(member_array(prof, all_profs) == -1)
					error("F_PROFESSION: No such profession (" + prof + ")\n");
		
        if( !find_object(PROFESSION_D(prof + "/" + arg)) 
			&& file_size(PROFESSION_D(prof + "/" + arg)+".c") < 0 
			)
        	error("F_PROFESSION: No such profession (" + prof + "/" + arg + ")\n");

        if( !mapp(profs) || member_array(prof, keys(profs)) == -1 ) 
        	profs = ([ prof : ({ arg }) ]);
        	else if(arrayp(profs[prof]))
        	{
        		list = profs[prof];
        		if(member_array(arg, list) != -1)
        			error("已学会此技能。\n");
        		list += ({ arg });
        		profs[prof] = list;
        	}
   return 1;
}

int delete_prof(string prof, string arg)
{
	string *list;
        if( mapp(profs) && member_array(prof, keys(profs)) != -1) 
        {
        	if(arrayp(profs[prof]))
        		{
        			list = profs[prof];
        			if(member_array(arg, list) == -1)
        				error("未学会此技能。\n");
        			list -= ({ arg });
        			if(sizeof(list))
        				profs[prof] = list;
        			else
        				map_delete(profs, prof);
        			return 1;
        		}
        }
        return 0;
}

string *query_prof(string prof)
{
	if(!stringp(prof) || member_array(prof, all_profs) == -1)
		error( prof + "并非一个职业技能。\n");

//		error("F_PROFESSION: No such profession (" + prof + ")\n");

	if(!mapp(profs)|| member_array(prof, keys(profs)) == -1)
		error("未学会任何(" + to_chinese(prof) + ")\n");	
		
	if( arrayp(profs[prof]) ) return profs[prof];
}