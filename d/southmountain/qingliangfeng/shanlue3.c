// 东天目山，一座随机生成的区域。玩家副本 Zine 2014/7/14
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "山脚下"+NOR);
	set("long", @LONG
这里是阳山脚下，东南面有一座畲族山寨。
LONG
	);
        set("outdoors", "xitianmu");

	set("exits", ([
		//"northeast" : "/d/southmountain/shezhai/shezhai2",
		"southeast" : __DIR__"shanlue1",
		"westup" : __DIR__"yangshan",
		//"eastdown" : __DIR__"fengshu",
	]));

	set("objects", ([
		//__DIR__"npc/wujiang" : 1,
		//__DIR__"npc/shebing" : 2,
        ]));
	setup();
}
