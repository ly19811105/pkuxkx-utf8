// 东天目山，一座随机生成的区域。玩家副本 Zine 2014/7/14
inherit "/d/southmountain/dongtianmu/baseroom.c";
#include <ansi.h>


void create()
{
	set("short", "山路");
	set("long", @LONG
这里是一段山路，北面进山到东天目山，南面有一座佛寺。
LONG
	);
        set("outdoors", "dongtianmu");
	set("exits", ([
		"south" : __DIR__"dajuesi",
		//"up" : __DIR__"fenghuang2",
		//"northeast" : __DIR__"wall1",
		//"west" : __DIR__"wall1",
	]));
	set("objects", ([
		//__DIR__"npc/wujiang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	set("init_time",time());
	setup();
}
