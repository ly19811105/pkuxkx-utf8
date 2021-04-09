inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", CYN"琥珀境出口"NOR);
	set("long", @LONG
这里是地宫第三层琥珀境的出口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 3);
	set("exit", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"down" : __DIR__"level4entry",
		"enter" : __DIR__"level3d4",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
int valid_leave(object me,string dir)
{
	if (dir=="down"&&!query("allow_pass"))
	return notify_fail("你记起清凉寺方丈的话，还是要把这一层的毛贼抓住才好。\n");
	return ::valid_leave(me,dir);
}