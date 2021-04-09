// room.c
// modified by freecv 2005.04.16
// fix the bug of room reset, add "if (environment(camelob))" to void non-envrionment exception
// the path should be /inherit/room/room.c

#pragma save_binary

#include <dbase.h>
#include <room.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

nosave mapping doors;

int query_max_encumbrance() { return 100000000000; }

object make_inventory(string file)
{
	object ob;

	ob = new(file);
	ob->move(this_object());
	ob->set("startroom", base_name(this_object()));
	//log_file("refresh",base_name(this_object())+" reload "+file+" at "
	//+ctime(time())+"\n");
	return ob;
}
void m_inv(string file)
{	
	object ob;

	ob = new(file);
	ob->move(this_object());
	ob->set("startroom", base_name(this_object()));
}
void reset()
{
	mapping ob_list, ob;
	object tem_ob,camelob;
	string *list;
	object *inv;
	int i,j;

	//
	// Check loaded objects to match the objects specified in "objects"
	// while query("objects") is 
	// ([ <object filename>: <amount>, ..... ])
	// and query_temp("objects") is
	// ([ <object filename>: ({ob1, ob2, ...}), .... ])
	//
	//log_file("refresh",base_name(this_object())+" reset at "+
	//ctime(time())+"\n");
	inv=all_inventory();
	if (sizeof(inv) > 100)
	{
		camelob = load_object("/clone/npc/camel1");
    if (environment(camelob))    //added by freecv
                message_vision("一阵悦耳的和弦铃声响起，只见毫毛掏出一部带摄像头的彩屏手机，招呼道『啥？那里破烂比较多？好！我马上打的去！』转身打了辆桑塔纳就没了踪影。\n",environment(camelob));

		camelob->move(this_object());
		camelob->init();
	}
        if (this_object()->query("no_reset")) return;
	set("no_clean_up", 0);

	if (this_object()->query("no_dig")) 
	this_object()->delete("no_dig");//added by vast,让寻宝任务中挖过的房间更新
        if( query_temp("changxi"))
        set_temp("changxi",0);//added by vast,让唱戏任务中去过的房间更新
	ob_list = query("objects");
	if( !mapp(ob_list) ) return;
	
	if( !mapp(ob = query_temp("objects")) )
		ob = allocate_mapping(sizeof(ob_list));
/*
	for(int k=0;k<sizeof(inv);k++)
	{
		if(!userp(inv[k])&&inv[k]->query("no_clean_up")&&inv[k]->is_character())
		{
			add("no_clean_up",1);
			return;
		}
	}
*/
	
	list = keys(ob_list);
	for(i=0; i<sizeof(list); i++) {
		// Allocate an array if we have multiple same object specified.
		if(	undefinedp(ob[list[i]])
		&&	intp(ob_list[list[i]])
		&&	ob_list[list[i]] > 1 )
			ob[list[i]] = allocate(ob_list[list[i]]);

		switch(ob_list[list[i]]) {
		case 1:
			
			if( ob[list[i]] ) {
				
			if( environment(ob[list[i]]) != this_object())
				if(!ob[list[i]]->return_home(this_object())) 
					ob[list[i]] = make_inventory(list[i]);
					//icer modified 
					//如果npc不return_home，则new出新的，
					//有利于丰富npc资源
								
		}	else
				ob[list[i]] = make_inventory(list[i]);
			break;
		default:
			for(j=0; j<ob_list[list[i]]; j++) {
				// If the object is gone, make another one.
				if( ! objectp(ob[list[i]][j]) ) {	
				ob[list[i]][j] = make_inventory(list[i]);
				continue;
				}
				// Try to call the wandering npc come back here.
				if( environment(ob[list[i]][j]) != this_object()) {
						if(!ob[list[i]][j]->return_home(this_object()))
							ob[list[i][j]] = make_inventory(list[i]);
							//icer modified
							//同上
				}
			}
		}
	}
	set_temp("objects", ob);
}

// Redirect item_desc of the door to this function in default.
string look_door(string dir)
{
	if( !mapp(doors) || undefinedp(doors[dir]) )
		return "你要看什么？\n";
	if( doors[dir]["status"] & DOOR_CLOSED )
		return "这个" + doors[dir]["name"] + "是关着的。\n";
	else
		return "这个" + doors[dir]["name"] + "是开着的。\n";
}

varargs int open_door(string dir, int from_other_side)
{
	mapping exits;
	object ob;

	if( !mapp(doors) || undefinedp(doors[dir]) )
		return notify_fail("这个方向没有门。\n");

	if( !(doors[dir]["status"] & DOOR_CLOSED) )
		return notify_fail( doors[dir]["name"] + "已经是开着的了。\n");

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: open_door: attempt to open a door with out an exit.\n");

	if( from_other_side )
		message("vision", "有人从另一边将" + doors[dir]["name"] + "打开了。\n", this_object());
	else if( objectp(ob = find_object(exits[dir])) ) {
		if( !ob->open_door(doors[dir]["other_side_dir"], 1) ) return 0;
	}

	doors[dir]["status"] &= (!DOOR_CLOSED);
	return 1;
}

varargs int close_door(string dir, int from_other_side)
{
	mapping exits;
	object ob;

	if( !mapp(doors) || undefinedp(doors[dir]) )
		return notify_fail("这个方向没有门。\n");

	if( (doors[dir]["status"] & DOOR_CLOSED) )
		return notify_fail( doors[dir]["name"] + "已经是关着的了。\n");

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: close_door: attempt to open a door with out an exit.\n");

	if( from_other_side )
		message("vision", "有人从另一边将" + doors[dir]["name"] + "关上了。\n", this_object());
	else if( objectp(ob = find_object(exits[dir])) ) {
		if( !ob->close_door(doors[dir]["other_side_dir"], 1) ) return 0;
	}

	doors[dir]["status"] |= DOOR_CLOSED;
	return 1;
}

int check_door(string dir, mapping door)
{
	// If we have no responding door, assume it is correct.
	if( !mapp(doors) || undefinedp(doors[dir]) ) return 1;

	door["status"] = doors[dir]["status"];
	return 1;
}

varargs void create_door(string dir, mixed data, string other_side_dir, int status)
{
	mapping d, exits, item_desc;
	object ob;

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: create_door: attempt to create a door without exit.\n");

	// Compact mode.
	if( stringp(data) ) {
		d = allocate_mapping(4);
		d["name"] = data;
		d["id"] = ({ dir, data, "door" });
		d["other_side_dir"] = other_side_dir;
		d["status"] = status;
	} else if( mapp(data) )
		d = data;
	else
		error("Create_door: Invalid door data, string or mapping expected.\n");

	set("item_desc/" + dir, (: look_door, dir :) );

	if( objectp(ob = find_object(exits[dir])) ) {
		if( !ob->check_door(other_side_dir, d) )
			return;
	}

	if( !mapp(doors) ) doors = ([ dir: d ]);
	else doors[dir] = d;
}

mapping query_doors() { return doors; }

mixed query_door(string dir, string prop)
{
	if( !mapp(doors) || undefinedp(doors[dir]) ) return 0;
	else return doors[dir][prop];
}

int valid_leave(object me, string dir)
{              
        object room = this_object();
        object guarder;
        object *inv;  
        int i;
 
	if( mapp(doors) && !undefinedp(doors[dir]) ) {
		if( doors[dir]["status"] & DOOR_CLOSED )
			return notify_fail("你必须先把" + doors[dir]["name"] + "打开！\n");
		// if ( door[dir]["status"] & DOOR_HAS_TRAP ) ....
	}  
        if (room->query("no_fight")==1)
        {
            return 1;
        }
        inv = all_inventory(room);  
        for(i=0;i<sizeof(inv);i++)
           { 
            if( !living(inv[i]) || !interactive(inv[i]) ) continue;
			else if(inv[i] != me && inv[i]->query_temp("guards/exit") == dir )
                   {
                        if ((int)inv[i]->query_skill("dodge") > random((int)me->query_skill("dodge")*2))
                return notify_fail(inv[i]->query("name")+"正在看守"+dir+"这个方向，你无法通过！\n");  
                   }
           }                
	me->delete_temp("guards/exit");
	me->delete_temp("guards/object");
	return 1;
}

void setup()
{
	seteuid(getuid());
	this_object()->reset();
}
