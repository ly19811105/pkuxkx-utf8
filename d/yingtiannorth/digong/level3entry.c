inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", CYN"琥珀境入口"NOR);
	set("long", @LONG
这里是地宫第三层琥珀境的入口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 3);
	set("entry", 1);
	set("exits", ([
		"enter" : __DIR__"level3a1",
		"up" : __DIR__"level2exit",
		//"north" : __DIR__"shanlus1",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
void init()
{
	object npc;
	string * places=({"a1","a2","a3","a4","b1","b2","b3","b4","c1","c2","c3","c4","d1","d2","d3","d4"});
	tell_object(this_player(),HBWHT+CYN+"这一关中，玩家需要通过合作围住一个蟊贼，只有第一次发现该蟊贼后，localmap才会显示蟊贼位置。\n"+NOR);
	if (!query("thief_gened"))
	{
		npc=new(__DIR__"npc/thief");
		npc->move(load_object(__DIR__"level3"+places[random(sizeof(places))]));
		set("thief_gened",1);
	}
	::init();
}