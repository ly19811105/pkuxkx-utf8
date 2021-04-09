//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", "营外空地" );
	set("long", "这里明军的营外的空地，为防止敌人乘黑偷营，这里被清出一片空地。\n");
	set("exits", ([
		"enter" : __DIR__"ming_ying",
        "west" : __DIR__"ming_ying1",
        "east" : __DIR__"ming_ying2",
        "north": __DIR__"ming_xiaolu",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","明");
    set("land_type","pingyuan");
    set("hardness",1);
	setup();
}

int buff(object me)
{
    int buff=(int)me->query("level")*3;
    if (me->query_temp("guozhan/side")==this_object()->query("side"))
    {
        me->add_temp("apply/damage",buff);
    }
    else
    {
        me->add_temp("apply/damage",-buff);
    }
    return 1;
}

void init()
{
    object me=this_player();
    buff(me);
    ::init();
}

int valid_leave(object me,string dir)
{
    int buff=(int)me->query("level")*3;
    if (me->query_temp("guozhan/side")==this_object()->query("side"))
    {
        me->add_temp("apply/damage",-buff);
    }
    else
    {
        me->add_temp("apply/damage",buff);
    }
    return ::valid_leave(me,dir);
}