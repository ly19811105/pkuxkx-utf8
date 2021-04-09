// Room: /d/shaolin/cjlou1.c
// Date: YZC 96/01/19
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "藏经阁二楼");
	set("long", @LONG
千余年来少林寺执中原武林之牛耳，自达摩老祖以下，历代
人材辈出。其中有不少高僧遗著留存，汇集至今，终成名震天下
的少林七十二绝艺。少林精华，尽集于此。二楼四面开窗，确保
通风。中间排列着五排大书架。四周则陈列矮几，以供阅读。几
位老僧手执经卷，正在闭目凝思。
LONG
	);

	set("exits", ([
            "south" : __DIR__"cjlou2",
            "down" : __DIR__"cjlou",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/hui-zhen" : 1,
		"d/shaolin/obj/wuji1" : 1,
		"d/shaolin/obj/wuji2" : 1,
		"d/shaolin/obj/wuji3" : 1,
	]));
    create_door("south", "壁门", "north", DOOR_CLOSED);
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;

	if( present("shaolin wuji", me)
        && present("huizhen zunzhe", environment(me)) 
    	&& living( present("huizhen zunzhe", environment(me))))
    {
        if (dir == "down" )
        {
            return notify_fail("慧真说道: 武功秘籍只许在藏经阁内研习，不得携带外出 !\n");
        }
        if (dir == "south" && me->query_temp("cjlou_allow")!=1 )
        {
            return notify_fail("慧真说道: 你还没有得要少林方丈长老的允许 !\n");
        }   
    }
	return ::valid_leave(me, dir);
}
