// Modified by iszt@pkuxkx, 2007-04-20

#include <ansi.h>

inherit ROOM;

void create ()
{
	set("short", "襄阳西门");
	set("outdoors","xiangyang");
	set("long",YEL @LONG
这里是襄阳的西门，几个月前刚刚打退了蒙古人的进攻。襄阳的守军正在积
极备战，往城里运送物资。城门口有一队守军，对进出的行人盘查很严。
LONG NOR);

        set("gate", 1);//保卫襄阳攻城门的判据．
        set("gatetype", 3);//保卫襄阳攻城门的判据．
	set("exits", ([
		"east" : __DIR__"xywest3",
                "west" : __DIR__"westr1",
	]));

	set("objects", ([
		__DIR__"npc/shoujun" : 4,
	        __DIR__"npc/shjiang" : 1,
        ]));

	setup();
}

void init()
{
	if(!query("occupied") && (load_object("/adm/daemons/xytaskd.c"))->query("begin")
		&& this_player()->query("id")=="menggu bing")
		CHANNEL_D->do_channel( this_object(), "bd", query("short")+HIR"受到蒙古兵的攻击！", -1);
	return;
}

int valid_leave(object me, string dir)
{        
	if( present("shou jun", environment(me))
		&& (dir == "north")
		&& (!me->query_temp("shoujiang_asked"))
		|| present("shou jun", environment(me))
		&& (dir == "north")
		&& (!present("yao pai",this_player())) )
		return notify_fail("守军拦住了你的去路，大声喝道：「干什么的？」\n");
	return ::valid_leave(me, dir);
}
