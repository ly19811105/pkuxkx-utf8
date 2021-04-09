// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "兰山脚下");
	set("long", @LONG
这里是兰山的脚下，东面山势越来越陡峭了。
LONG );
	set("exits", ([
		"westdown" : __DIR__"lanshan_w2",
	]));
	set("outdoors", "lanzhou");
	setup();
}

int valid_leave(object me,string dir)
{
	if (dir!="westdown")
	{
		if (!userp(me)) return notify_fail("");
		if (me->query_dex()<45) return notify_fail("兰山西侧比较陡峭，你可以尝试从玉佛寺后山上山。\n");
	}
	return ::valid_leave(me,dir);
}
