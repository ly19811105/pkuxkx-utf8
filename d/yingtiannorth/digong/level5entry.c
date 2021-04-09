inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", MAG"水晶境入口"NOR);
	set("long", @LONG
这里是地宫第五层水晶境的入口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 5);
	set("entry", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"up" : __DIR__"level4exit",
		//"north" : __DIR__"shanlus1",
		"west" : __DIR__"level5path1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
void init()
{
	object migong=load_object(__DIR__"level6maze");
	if (!migong->query("generating")&&!migong->query("fully_generated"))
	migong->start();
	tell_object(this_player(),HBWHT+MAG+"这一关中，玩家需要找到神木后爬上去(climb up)，得到老和尚传法后，在西面被挡住路的地方说出来。\n"+NOR);
	::init();
}