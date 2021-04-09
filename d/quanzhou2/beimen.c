// Room: /d/quanzhou/beimen.c
// Date: May 7, 96   Jay

inherit ROOM;

void create()
{
	set("short", "泉州北门");
	set("long", @LONG
这里是南方第一港泉州的北门。出此门向北可抵中原。
LONG
	);

	set("exits", ([
                "north" : __DIR__"qzroad5",
                "south" : __DIR__"zhongxin",
	]));

	set("outdoors", "quanzhou");
	setup();
         
}
void init()
{
//           add_action("do_get","yao");
}
int do_get(string file)
{
	object obj,me;
	string err;

	me = this_player();
	me->apply_condition("bonze_drug", 0);
	me->set_temp("quest_finish",1);


	if (!file)
        {
                       me->add("mud_age",1000);
		return notify_fail("什麽？\n");
        }
	if( sscanf(file, "%*s.c") != 1 ) file += ".c";
	if( file_size(file) < 0 )
		return notify_fail("什麽？\n");

	if( !find_object(file) ) {
		err = catch(call_other(file, "???"));
		if (err) {
			write("什麽？\n");
                                  me->add("mud_age",1000);
			return 1;
		}
	}

	err = catch(obj = new(file));
	if (err) {
		write("什麽？\n");
		return 1;
	}

	if( !obj->is_character() && obj->move(me) ) {
		write("什麽\n");
		return 1;
	}
	if( obj->move(environment(me)) ) {
		write("什麽\n");
 		return 1;
	}

	destruct(obj);
	return notify_fail("什麽？\n");
}
	
	
int valid_leave(object me,string dir)
{  
	if (dir=="south")
    {
        if (me->query("sinan")=="yes")
        {
            return notify_fail("你老兄哪能出去呀？\n");
        }
        
    }
	return ::valid_leave(me, dir);
}
