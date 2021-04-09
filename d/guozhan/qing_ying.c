//Zine 国战

#include <ansi.h>
inherit __DIR__"room_config.c";

void create()
{
	set("short", HIG "清军大营" NOR);
	set("long", "这里清军的大营，几队牛录忙忙碌碌的，正在准备着接下来对明军的决战。\n");
	set("exits", ([
		"out" : __DIR__"qing_yingwai",
		"up": __DIR__"qing_wanglou",
        "north" : __DIR__"exit",
	]) );
	/*set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );*/
    set("no_reset",1);
    set("no_clean_up", 1);
    set("side","清");
    set("daying",1);
    set("land_type","pingyuan");
	setup();
}

int valid_leave(object me,string dir)
{
    if (dir=="north"&&!me->query_temp("guozhan/want_to_exit"))
    {
        me->set_temp("guozhan/want_to_exit",1);
        return notify_fail(BLINK+"退出战场这一次就不能继续参战了，如果你已决定，请再次向北。\n"+NOR);
    }
    return ::valid_leave(me,dir);
}