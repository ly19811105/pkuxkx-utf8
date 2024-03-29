// object.c

varargs int getoid(object ob)
{
	int id;

	if (!ob) ob = previous_object();
	sscanf(file_name(ob), "%*s#%d", id);
	return id;
}

// Get the owner of a file.  Used by log_error() in master.c.
string file_owner(string file)
{
    string name, rest, dir;

    if (file[0] != '/') {
        file = "/" + file;
    }
    if (sscanf(file, "/u/%s/%s/%s", dir, name, rest) == 3) {
        return name;
    }
    return 0;
}

// domain_file should return the domain associated with a given file.
string domain_file(string file)
{
	string domain;

	if( sscanf(file, "/d/%s/%*s", domain) )
		return domain;

	return ROOT_UID;
}

// creator_file should return the name of the creator of a specific file.
string creator_file(string file)
{
	string *path;

	path = explode(file, "/") - ({ 0 });
	switch(path[0]) {
		case "adm":
			if( file==SIMUL_EFUN_OB ) return "MudOS";
			else return ROOT_UID;
		case "cmds":
			return ROOT_UID;
		case "u":
			if( sizeof(path)>=4 ) return path[2];
		case "d":
		case "open":
		case "ftp":
			if( sizeof(path)>=3 ) return path[1];
		default:
			if( this_player(1) )
				return getuid(this_player(1));
			else
				return "MudOS";
	}
}

// author_file should return the name of the author of a specific file.
string author_file(string file)
{
	string name;

	if( sscanf(file, "/u/%*s/%s/%*s", name) )
		return name;
	return ROOT_UID;
}

void destruct(object ob)
{
	    // add by Vast for AREA system
    if( objectp(ob) && environment(ob) && environment(ob)->is_area() ) {
    	environment(ob)->move_out(ob->query("area_info/x_axis"),
    		                      ob->query("area_info/y_axis"), ob);
    		                      efun::destruct(ob);
    		                      return;
    }
    
   	if (ob) {
		if( previous_object() ) ob->remove( geteuid(previous_object()) );
		else ob->remove(0);
		if(function_exists("pre_destruct",ob))
			ob->pre_destruct();
		efun::destruct(ob);
	}
	
}

//disable the replace_program function.
//the new fluffos does not allow call it if super class function is called from the child object
//it leads to lots of trouble. simply abandon it, since we dont care the memory

void replace_program(string replacer)
{
       //do nothing
}


/*void shutdown(int arg)
{
        if (geteuid(previous_object()) != ROOT_UID )
                return;
                
        efun::shutdown(arg);
}*/

