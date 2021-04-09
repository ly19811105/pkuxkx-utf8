//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", HIW "明军大营" NOR);
	set("long", "这里明军的大营，几队士兵忙忙碌碌的，正在准备着接下来对清军的决战。\n");
	set("exits", ([
		"out" : __DIR__"ming_yingwai",
		"up": __DIR__"ming_wanglou",
        "south" : __DIR__"exit",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","明");
    set("daying",1);
    set("land_type","pingyuan");
	setup();
}

int valid_leave(object me,string dir)
{
    if (dir=="south"&&!me->query_temp("guozhan/want_to_exit"))
    {
        me->set_temp("guozhan/want_to_exit",1);
        return notify_fail(BLINK+"退出战场这一次就不能继续参战了，如果你已决定，请再次向南。\n"+NOR);
    }
    return ::valid_leave(me,dir);
}