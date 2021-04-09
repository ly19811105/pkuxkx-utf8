
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", CYN"瞿塘巫峡纤道"NOR);
        set("long", "这段纤道位于长江三峡岸边，山高万仞，水落千丈，无山径可通，为蜀道难\n中之最。于岸壁开凿，既供逆水行舟作拉纤用，又可供轿马通行。站在这里你可\n以看到(watch)最近处的长江岸边。\n");
        set("exits", ([
               
               "southeast" : __DIR__"shudao2",
               "northwest" : __DIR__"shudao4",
                
        ]));
        set("outdoors", "chengdu");
		set("jiang","/d/changjiang/dkn4");
        setup();
   
}

int valid_leave(object me,string dir)
{  
	object pl=this_player();
        if (time() - pl->query_temp("shudao/last_go_time") <= 3+random(3))
        {
            return notify_fail("你小心翼翼往前挪动，遇到艰险难行处，只好放慢脚步。\n");
        }
        else
        {
            pl->set_temp("shudao/last_go_time",time());
        }
    
	return ::valid_leave(me, dir);
}
int look_jiang(object me,string msg)
{
	object ob=load_object(this_object()->query("jiang"));
	if (!me)
	me=this_player();
	if (me)
	{
		if (!msg)
		{
			msg=HIC+"向北眺望，正是长江最险峻湍急之处。\n"+NOR;
		}
		else
		{
			msg+=HIC+"向北眺望，正是长江最险峻湍急之处。\n"+NOR;
		}
		tell_object(me,HIC+msg);
		return "/cmds/std/look.c"->mudlook_room(me,ob,0);
	}
	return 1;
}
void init()
{
	object me=this_player();
	string msg;
	add_action("look_jiang","watch");
	if (random(100)>94)
	{
		msg=HIC+"走到这里，你被壮阔的景色所吸引，"+NOR;
		call_out("look_jiang",1,me,msg);
	}
}
