// Room: /lingzhou/yipingate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "一品堂大门");
	set("long", @LONG
这里是西夏一品堂的所在地，座落在西大街的北面，是一座高大的
石头建筑，看上去坚固之极。门口有两个武士站着，既不高大也不彪悍，
和皇宫门口的守卫差远啦，就是和衙门口的衙役比也颇有不如，但从他
们阴鹫的眼神里你不难看出他们是身怀绝技的高手，谁不知西夏一品堂
广招天下高手为皇上效命。
LONG );
	set("exits", ([
		"south"  : __DIR__"xidajie",
//                "north"  : __DIR__"yipindayuan",
	]));
	set("objects", ([
               __DIR__"npc/ye" : 1,
                __DIR__"npc/yue" : 1,
                __DIR__"npc/yun" : 1,
	]));
	setup();
}
//        create_door("north" , "铜皮大门", "south" , DOOR_CLOSED);

int valid_leave(object me, string dir)
{
        if (dir == "north" && 
            !(int)me->query("yipin/joined") && 
            objectp(present("wu shi", environment(me))))
           return notify_fail("一品堂武士拦住你的去路。\n");

        return ::valid_leave(me, dir);
}

