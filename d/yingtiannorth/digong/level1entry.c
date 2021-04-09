inherit __DIR__"karma_room.c";
#include "tiny_maze.h";
#include <ansi.h>

void create()
{
	set("short", HIB"麝香境入口"NOR);
	set("long", @LONG
这里是地宫第一层麝香境的入口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 1);
	set("entry", 1);
	set("maze_index",3);
	set("exits", ([
		//"up" : (:get_path:),
		//"" : __DIR__"xiaoxib",
		//"north" : __DIR__"shanlus1",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
void clear_users()
{
	string *id_list;
	object pl;
	if (!query("id_list")||!arrayp(query("id_list"))) return;
	id_list=query("id_list");
	for (int i=0;i<sizeof(id_list);i++)
	{
		if (!pl=find_player(id_list[i])) continue;
		if (!environment(pl)->is_KARMA_ROOM()) continue;
		pl->move("/d/yingtiannorth/qlsi");
		tell_object(pl,"地宫发生剧烈晃动，安全起见，你被转移到了"+environment(pl)->query("short")+"。\n");
	}
	delete("id_list");
	return;
}
void init()
{
	tell_object(this_player(),HBWHT+HIB+"在这一关中，玩家需要通过的是一个简易迷宫！\n"+NOR);
	::init();
}