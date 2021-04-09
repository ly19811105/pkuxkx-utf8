// command.c
// From ES2
// Modified by Xiang@XKX (12/15/95)
// Modified by Leon 97-11-26
// add command limit
// Modified by iszt@pkuxkx, 2007-04-12, command_hook must return 1

#include <command.h>
#include <dbase.h>
#include <origin.h>
// Let command path be static, thus we can make sure no one can get command
// path directly from restore_object().
nosave string *path;
int last_count;
int last_time;
// Leave this to allow other objects can search your commands such as
// help, which...
string find_command(string verb)
{
	return (string)COMMAND_D->find_command(verb, path);
}

string remove_leading_space(string arg)
{
	int i;
	for (i = 0; i < strwidth(arg); i++)
	if (arg[i..i] != " ")
		return arg[i..strwidth(arg)];
	return "";
}

// This is the add_action hook handling movement, commands, emotes and
// channels. Optimization is needed.
nomask int command_hook(string arg)
{
	string verb, file, env_file;
	object env, ob;

#ifdef PROFILE_COMMANDS
	int mem, utime, stime;
	mapping info;

	mem = memory_info();
	info = rusage();
	utime = info["utime"];
	stime = info["stime"];
#endif

	ob = this_object();
	env = environment();
	// player should do time limit check
	if( !living(ob) && ob->is_character() && !ob->is_corpse() )
	{	disable_commands();
	call_out( "enable_player", 100 );
	}
	if (time()<ob->query_temp("controled/till"))
	{
		tell_object(ob,"你现在正在被压制之中。\n");
		return 1;
	}
	if ( userp( ob ) && !wizardp( ob ) )
	{
	if ( time() - last_time == 0 )
	{
		last_count++;
		if ( last_count > 80 )
		{
				if ( last_count > 100 )
		{
			tell_object( ob, "你输入指令太多，系统负担不了!!!\n" );
			disable_commands();
			call_out( "enable_player", 10 );
			return 1;
		}
		tell_object( ob, "你输入的指令超过限制, 系统拒不接受.\n" );
		return 1;
		}
	}
	else
	{
		last_time = time();
		last_count = 0;
	}
	}
	verb = query_verb();
    ob->set_temp("last_command",verb + " " + arg);

	if ((verb = remove_leading_space(verb)) == "")
	return 0;

	if( !arg 
	  &&	(environment() 
	  && ( stringp(environment()->query("exits/" + verb)) ||
	       objectp(environment()->query("exits/" + verb)) ) )
	  &&	stringp(file = find_command("go"))
	  &&	call_other(file, "main", this_object(), verb))
	;


	else if( stringp(file = find_command(verb)) 
		&& call_other(file, "main", this_object(), arg))
	{
		if(strsrch(file,"app") != -1 || strsrch(file,"imm") != -1  || strsrch(file,"wiz") != -1  || strsrch(file,"arch") != -1  || strsrch(file,"adm") != -1)
		{
			log_file("wiz_command",sprintf("%s exec %s at %s from %s\n",getuid(),verb,ctime(time()),query_ip_number(this_object())));
		}
	}
		

	else if( EMOTE_D->do_emote( this_object(), verb, arg ) )
		;

	else if( CHANNEL_D->do_channel( this_object(), verb, arg ) )
		;

	else
	{
		string fail_msg;
		if(stringp(fail_msg = query_notify_fail()))
		{
			tell_object(this_object(), fail_msg);
			return 1;
		}
		else if (environment() == env)
		{
			return 0;
		}
	//	else	return 0; //yhzzyahoo fix @2015.12.30
	}

#ifdef PROFILE_COMMANDS
	info = rusage();
	PROFILE_D->log_command(verb, memory_info() - mem, info["stime"] - stime, info["utime"] - utime);
#endif

	return 1;
}

protected nomask void set_path(string *p)
{
	//	if( origin() != ORIGIN_LOCAL
	//	&&	geteuid(previous_object()) != ROOT_UID )
	//		return;
	path = p;
}

string *query_path() { return path; }
mixed *query_commands() { return commands(); }

int force_me(string cmd)
{
	if( geteuid(previous_object()) != ROOT_UID )
	return 0;

	return command( this_object()->process_input(cmd) );
}

nomask void enable_player()
{
	if( stringp(query("id")) ) set_living_name(query("id"));
	else set_living_name(query("name"));


	enable_commands();
	add_action("command_hook", "", 1);
	enable_commands();
	delete("disable_type");

	//setup_commands();


	if( !userp(this_object()) )
	set_path(NPC_PATH);
	else if ( this_object()->query("registered") == 0)
	set_path(UNR_PATH);
	else
	switch( wizhood(this_object()) ) {
	case "(admin)":
	set_path(ADM_PATH);
	enable_wizard();
	break;
	case "(arch)":
	set_path(ARC_PATH);
	enable_wizard();
	break;
	case "(wizard)":
	set_path(WIZ_PATH);
	enable_wizard();
	break;
	case "(apprentice)":
	set_path(APR_PATH);
	enable_wizard();
	break;
	case "(immortal)":
	set_path(IMM_PATH);
	break;
	case "(guider)":
	set_path(GUD_PATH);
	break;
	default:
	set_path(PLR_PATH);
	}
}

nomask void disable_player(string type)
{
	if( geteuid(previous_object())!=ROOT_UID
	  &&	previous_object()!=this_object()) return;

	set("disable_type", type);
	disable_commands();
}
