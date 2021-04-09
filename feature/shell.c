// created by poet on 2001.10.23
// added by super
// for command shell,if any problem ,comment it--jason
// poet slightly modified it, to prevent flood.
// Super modified again for set vars.
// poet modified for stand-alone feature

#include <dbase.h>

nosave int count = 0;

mixed process_shell(string arg)
{
    string file, content;
    object me;
    mixed result;
    mixed *var;
    mapping vars;

    me = this_object();
    // poet added restriction for > (wizard)
    if ( wiz_level(me) < 5 ) 
	return arg;
    var = allocate(10);

    // use the file to make sure that:
    //          the temp file has the same EUID as the player.
    file = sprintf("%s/%d%d.c", user_cwd(geteuid(me)), time(), count);
    if ( count++ >= 10 ) count = 0;

    vars = query_temp("vars");
    if ( sizeof(vars) > 0 )
    {
	// treat vars as parameters, define the param list.
	content =
	"// Temp file, safe for delete\n"
	"#include <ansi.h>\n"
	"mixed temp(object me";
	foreach (string key in keys(vars))
	{
	    if (arrayp(vars[key])) {
		content += ", mixed *" + key;
	    } else if (objectp(vars[key]))
		content += ", object " + key;
	    else if (mapp(vars[key]))
		content += ", mapping " + key;
	    else if (stringp(vars[key]))
		content += ", string " + key;
	    else if (intp(vars[key]))
		content += ", int " + key;
	    else if (floatp(vars[key]))
		content += ", float " + key;
	    else
		content += ", mixed " + key;
	}
	content += sprintf(")\n"
	  "{ return %s; } \n", arg);
	// check if the user has the privilege to write the file
	if ( !write_file(file, content, 1) )
	    return arg;

	// fill in environment vars as parameter.
	var[0] = "temp";
	var[1] = me;
	for (int i = 2; i <= sizeof(vars) + 1; i++)
	    var[i] = values(vars)[i-2];

	// if fail, return the input string
	if ( catch(result = call_other(file, var) ) )
	{
	    cat(file);
	    result = arg;
	}
	// no environment vars.
    } else {

	content =
	"// Temp file, safe for delete\n"
	"#include <ansi.h>\n"
	"mixed temp(object me) { return %s; }\n";
	// check if the user has the privilege to write the file
	if ( !write_file(file,
	    sprintf(content, arg), 1))
	    return arg;

	// if fail, return the input string
	if ( catch(result = call_other(file, "temp", me) ) )
	{
	    cat(file);
	    result = arg;
	}
    }

    log_file("static/SHELL", sprintf("%s use shell %s on %s\n",
	me->name_id(), arg, ctime(time()) ) );
    // remove the temp file.
    destruct(find_object(file));
    rm(file);

    return result;
}

string process_shell_str(string arg)
{
    mixed result;

    result = process_shell(arg);

    if ( stringp(result) )
	return result;

    // convert to string
    return sprintf("%O", result);
}


int evaluate_shell(string arg)
{
    string file, content;
    object me;
    mixed result;
    mixed *var;
    mapping vars;

    me = this_object();
    // poet added restriction for > (wizard)
    if ( wiz_level(me) < 5 )
	return notify_fail("权限拒绝。\n");
    var = allocate(10);

    // use the file to make sure that:
    //          the temp file has the same EUID as the player.
    file = sprintf("%s/%d%d.c", user_cwd(geteuid(me)), time(), count);
    if ( count++ >= 10 ) count = 0;
    vars = query_temp("vars");
    if ( sizeof(vars) > 0 )
    {
	// treat vars as parameters, define the param list.
	content =
	"// Temp file, safe for delete\n"
	"#include <ansi.h>\n"
	"int temp(object me";
	foreach (string key in keys(vars))
	{
	    if (arrayp(vars[key])) {
		content += ", mixed *" + key;
	    } else if (objectp(vars[key]))
		content += ", object " + key;
	    else if (mapp(vars[key]))
		content += ", mapping " + key;
	    else if (stringp(vars[key]))
		content += ", string " + key;
	    else if (intp(vars[key]))
		content += ", int " + key;
	    else if (floatp(vars[key]))
		content += ", float " + key;
	    else
		content += ", mixed " + key;
	}
	content += sprintf(")\n"
	  "{ %s; return 1; } \n", arg);
	// check if the user has the privilege to write the file
	if ( !write_file(file, content, 1) )
	    return notify_fail("写文件出错！\n");

	// fill in environment vars as parameter.
	var[0] = "temp";
	var[1] = me;
	for (int i = 2; i <= sizeof(vars) + 1; i++)
	    var[i] = values(vars)[i-2];
	// if fail, return the input string
	if ( catch(result = call_other(file, var) ) )
	{
	    cat(file);
	    return notify_fail("程序编译失败！\n");
	}
	// no environment vars.
    } else {

	content =
	"// Temp file, safe for delete\n"
	"#include <ansi.h>\n"
	"int temp(object me) { %s; return 1; }\n";
	// check if the user has the privilege to write the file
	if ( !write_file(file,
	    sprintf(content, arg), 1))
	    return notify_fail("写文件出错！\n");

	// if fail, return the input string
	if ( catch(result = call_other(file, "temp", me) ) )
	{
	    cat(file);
	    return notify_fail("程序编译失败！\n");
	}
    }

    log_file("static/SHELL", sprintf("%s use shell %s on %s\n",
	me->name_id(), arg, ctime(time()) ) );
    // remove the temp file.
    destruct(find_object(file));
    rm(file);

    return 1;
}


