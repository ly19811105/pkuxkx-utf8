// securityd.c 
//leon modified 11/21/97 10:08:26
//把arch的写目录权限改小了，防止arch自己提升为天神的事件出现。

//增加某个巫师对/d下某个目录的写权的独立设置
//彻底整理了混乱的权限设置
//这个文件以后不要随意改动--jason 2001-9-17
// modify by shure arch写权等于admin 2001-10-21



#include <login.h>

// By Annihilator@Eastern.Stories (11/25/94)

// This is the "effective" access status compare to the "status" property
// in login object that this mapping determine wizards' access rights
// directly. It is important to make the "status" property matches this
// mapping for wizards higher than regular wizard such as sage, arch and
// admin. For thoese users whose name doesnot appear in this mapping, they
// are divided into three groups (wizard),(player) and (object) using
// wizardp() and interactive() efun.
// The parenthesis is nessessary to prevend players naming themself "admin"
// to hack the security system.
// 
// 01/14/95 Annihilator - wiz_status are defined outside this daemon in the
//                        WIZLIST file.
// Modified by Xiang for XKX


protected mapping wiz_status;

protected string *wiz_levels = ({
	"(player)",
	"(guider)",
	"(immortal)",
	"(apprentice)",
	"(wizard)",
	"(arch)",
	"(admin)"
});

// A valid write attempt must pass 2 checks: your uid or status must not be
// "excluded" and must be "trusted" on that directory in order to write in 
// that directory. The directories containing the file is searched backward
// from the current directory to root. And exclude is checked prior than
// trusted.

protected mapping trusted_write = ([
	"/": 		({ "(admin)" }),
        "d":            ({"(arch)","(wizard)"}),
        "kungfu": 	({ "(arch)" }),
	"log":		({ "(admin)" }),
	"doc":          ({ "(arch)","(wizard)" }),
        "open":     	({ "(apprentice)","(wizard)","(arch)" }),
    	"new_quest":    ({"(arch)","(wizard)"}),
        "quest":    ({"(arch)","(wizard)"}),
    	"hate":		({"(arch)"}),
    	"job":		({"(arch)"}),
    	"hslj":		({"(arch)"}),
    	"task":		({"(arch)"}),
        "web":         ({"(arch)"}),
        "clone":                ({"(admin)","(arch)"}),
        "obj":                ({"(admin)","(arch)"}),        	
        "data":         ({"(admin)"}),
        "inherit":         ({"(arch)"}),
        "adm":                ({"(admin)"}),
// 去掉temp和open的写权限。
//"temp":     ({ "(apprentice)","(wizard)","(arch)" }),
]);

protected mapping exclude_write = ([
	"adm":		({ "(arch)","(wizard)","(apprentice)","(immortal)","(guider)"}),
        "cmds":     ({ "(wizard)","(apprentice)","(immortal)","(guider)" }),
	"data":		({ "(arch)","(wizard)","(apprentice)","(immortal)","(guider)"}),
	"include":	({ "(arch)","(wizard)","(apprentice)","(immortal)","(guider)" }),
	"log":		({ "(arch)","(wizard)","(apprentice)","(immortal)","(guider)"}),
	"u":		({ "(wizard)","(apprentice)","(immortal)","(guider)"}),
	"feature":	({ "(arch)","(wizard)","(apprentice)","(immortal)","(guider)"}),
         "inherit":      ({ "(wizard)","(apprentice)","(immortal)","(guider)"}),
        "obj":        ({ "(wizard)","(apprentice)","(immortal)","(guider)"}),
        "clone":        ({ "(wizard)","(apprentice)","(immortal)","(guider)"}),        	
]);

protected mapping exclude_read = ([
        "open"             : ({"(arch)"}),
        "data"             : ({"(arch)"}),
]);


void create()
{
	string *wizlist, wiz_name, wiz_level;
	int i;

	seteuid(ROOT_UID);
	wizlist = explode(read_file(WIZLIST), "\n");
	wiz_status = allocate_mapping(sizeof(wizlist));
	for(i=0; i<sizeof(wizlist); i++) {
		if( wizlist[i][0]=='#' 
		|| sscanf(wizlist[i], "%s %s", wiz_name, wiz_level)!=2 ) continue;
		wiz_status[wiz_name] = wiz_level;
	}
}

string *query_wizlist() { return keys(wiz_status); }

// This function returns the status of an uid.
string get_status(mixed ob)
{
	string euid;
	
	if( objectp(ob) ) {
		euid = geteuid(ob);
		if( !euid ) euid = getuid(ob);
	}
	else if( stringp(ob) ) euid = ob;

	if( !undefinedp(wiz_status[euid]) ) return wiz_status[euid];
	else if( member_array(euid, wiz_levels)!=-1 ) return euid;
	else return "(player)";
}

int get_wiz_level(mixed ob)
{
	return member_array(get_status(ob), wiz_levels);
}

int set_status(mixed ob, string status)
{
	string uid, *wiz, wizlist;
	int i;

	if( geteuid(previous_object())!= ROOT_UID ) return 0;

	if( userp(ob) )			uid = getuid(ob);
	else if(stringp(ob))	uid = ob;
	else return 0;
	
	if( status == "(player)" )
		map_delete(wiz_status, uid);
	else
		wiz_status[uid] = status;
	wiz = keys(wiz_status);
	for(wizlist = "", i=0; i<sizeof(wiz); i++)
		wizlist += wiz[i] + " " + wiz_status[wiz[i]] + "\n";
	rm(WIZLIST);
	write_file(WIZLIST, wizlist);
	log_file( "static/promotion", capitalize(uid)
	 + " become a " + status + " on " + ctime(time()) + "\n" );
	return 1;
}

string *get_wizlist() { return keys(wiz_status); }

// valid_write - called by the master object to determine whether if an user
//               is allowed to write on a certain file.
// NOTE:
//     The argument user should be an object according to the source code
// of driver. However, it is a mixed type in the released docs. We assume
// it is an object in normal case here and issue an error if it was not
// an object. 												- Annihilator

varargs int valid_write(string file, mixed user, string func,int flag)
{
	string euid, status, *path, dir;
	string domain_write,*dw_list,str;
	int i;
	if(flag&&base_name(previous_object())!="/adm/daemons/ftpd") 
                return 0;
	if( !objectp(user) && !flag)
		error("TRUST_D->valid_write: Invalid argument type of user.\n");

	if( sscanf(file, LOG_DIR + "%*s") && func=="write_file" ) return 1;
        //开放open的写权限
        if (sscanf(file,"/open/test/%*s")) return 1;
		

	// Let user save their save file
	if( func=="save_object" ) {
		if( sscanf(base_name(user), "/newbiequest/shaolin/cjg/equip2/%*s")
                &&      (sscanf(file, "/data/%*s") || sscanf(file, PRIVATE_DIR + "%*s"))
              &&      file == (string)user->query_save_file() + ".o" )
			return 1;//藏经阁装备
		if( sscanf(base_name(user), "/clone/%*s")
                &&      (sscanf(file, "/data/%*s") || sscanf(file, PRIVATE_DIR + "%*s"))
              &&      file == (string)user->query_save_file() + ".o" )
			return 1;
		if( sscanf(base_name(user), "/obj/gem/%*s")
                &&      (sscanf(file, "/data/%*s") || sscanf(file, PRIVATE_DIR + "%*s"))
              &&      file == (string)user->query_save_file() + ".o" )
			return 1;
		//pal 添加用来存自创山庄文件。
		if ( sscanf(file,"/data/home/%s",str) )
			return 1;
	    //较技场的文件
		if ( sscanf(file,"/data/jiaoji/%s",str) )
			return 1;
	    //特殊礼物
		if ( sscanf(file,"/data/gift/%s",str) )
			return 1;
		if ( sscanf(file,"/data/business/%s",str) )
		{
			return 1;
		}
		if ( sscanf(file,"/data/business/olympic_coin/%s",str) )
		{
			return 1;
		}
		//投票
		if ( sscanf(file,"/data/vote/%s",str) )
		{
			return 1;
		}		
		//门派比武
		if (file == "/data/biwud.o")
			return 1;
		if (file == "/data/familyd.o")
			return 1;
	}

	// Get the euid and status of the user.
	if(flag)
		euid=user;
	else
		euid = geteuid(user);
	if( !euid ) return 0;
	status = get_status(user);

	if( euid==ROOT_UID ) return 1;

//	if( sscanf(file, "/u/" + euid[0..0] + "/" + euid + "/%*s") )
	if( sscanf(file, "/u/" + euid + "/%*s") )
		return 1;

	path = explode(file, "/");
	
	// Check if we are excluded in one of the directories containing the file.
	for(i=sizeof(path)-1; i>=0; i--) {
		dir = implode(path[0..i], "/");
		if( undefinedp(exclude_write[dir]) ) continue;
		if( member_array(euid, exclude_write[dir])!=-1 ) 
		{
			log_file("FILES", sprintf("%s(%s) write attempt on %s failed.\n", geteuid(user), wizhood(user), file));
			return 0;
		}
		if( member_array(status, exclude_write[dir])!=-1 ) 
		{
			log_file("FILES", sprintf("%s(%s) write attempt on %s failed.\n", geteuid(user), wizhood(user), file));
			return 0;
		}
	}
	//将特别的设置放在exclude判断之后
	//jason 2001-9-15
	if(!userp(user)||!domain_write=read_file("/adm/etc/domain_write")) 
	{;}
	else
	{
		string id,ddir;
		dw_list=explode(domain_write,"\n");
		dw_list=filter_array(dw_list,(:$1[0..0]!='#':));
		for(int ii=0;ii<sizeof(dw_list);ii++)
		{
			if(sscanf(dw_list[ii],"%s %s",id,ddir)!=2) 
				continue;
			else if(id==euid&&get_status(user)=="(wizard)")
			{
				string *ddirs;
				ddirs=explode(ddir,"+");
				if(sizeof(path)>=3&&path[0]=="d"&&member_array(path[1],ddirs)!=-1)//只对/d目录生效
					return 1;
			}
			else
				continue;
		}
	}
	
	// And then check if we are trusted in one of the directories containing
	// the file.
	if( member_array(euid, trusted_write["/"])!=-1 ) return 1;
	if( member_array(status, trusted_write["/"])!=-1 ) return 1;
	for(i=sizeof(path)-1; i>=0; i--) {
		dir = implode(path[0..i], "/");
		if( undefinedp(trusted_write[dir]) ) continue;
		if( member_array(euid, trusted_write[dir])!=-1 ) return 1;
		if( member_array(status, trusted_write[dir])!=-1 ) return 1;
	}

	log_file("FILES", sprintf("%s(%s) write attempt on %s failed.\n", geteuid(user), wizhood(user), file));
	return 0;
}

// valid_read - called by the master object to determine whether if an user
//		  is allowed to read on a certain file.

int valid_read(string file, mixed user, string func)
	
{
	
	
	string euid, status, *path, dir;
	int i,j;

	if (this_player()) user = this_player();
	if( !objectp(user) )
		error("TRUST_D->valid_read: Invalid argument type of user.\n");

	if (	//func != "read_file" &&
		func != "file_size" &&
		func != "cat" &&
		func != "stat" &&
		func != "read_bytes" &&
		func != "tail" &&
		func != "help" && // add by shure
		func != "ed_start"
	) return 1;

	// Get the euid and status of the user.
	euid = geteuid(user);

	if( !euid ) return 1;
	if( euid==ROOT_UID ) return 1;

	status = get_status(user);
	//pal 添加用来读写自创山庄文件。
//	log_file("test/sec",file+"\n");
	if( sscanf(file, "/data/home/%*s") )
	{
//                write(file+"\n");
		return 1;
	}
	
	//icer 不显示版本控制相关目录
	if ( sscanf(file,"%*s.svn%*s") )
			return 0;

	path = explode(file, "/");

	// Check if we are trusted in one of the directories to access.
	for(i=sizeof(path)-1; i>=0; i--) {
		dir = implode(path[0..i], "/");
		// Checking if exclude directories define (user or status) or not.
		if( undefinedp(exclude_read[dir]) ) continue;
		// Checking if we are excluded in one of the directories containing the file.
		if( sizeof(exclude_read[dir]) > 0 )
		// Checking exclude directories.
		for(j=0;j<sizeof(exclude_read[dir]);j++) {
			// If wizard have no rights access this dirctory.
			if( euid == exclude_read[dir][j] ) return 0;
			// If status have no rights access this dirtory.
			if( wiz_level(status) > 1 )
				if( wiz_level(status) < wiz_level(exclude_read[dir][j])+1 )
					return 0;
		}
	}
	return 1;
}


int valid_seteuid( object ob, string uid )
{
	if( uid==0 ) return 1;
	if( uid==getuid(ob) ) return 1;
	if( getuid(ob)==ROOT_UID ) return 1;
	if( sscanf(file_name(ob), "/data/home/file/%*s") ) return 1;//pal 添加用来存自创山庄文件
	if( sscanf(file_name(ob), "/adm/%*s") ) return 1;
	if( wiz_status[uid] != "(admin)"
	&&	wiz_status[getuid(ob)] == "(admin)" )
		return 1;
    //只有这个命令有需要seteuid
    if( sscanf(file_name(ob), "/cmds/guider/expellapp%*s") ) return 1;
	return 0;
}


