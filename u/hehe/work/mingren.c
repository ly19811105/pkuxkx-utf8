#include <room.h>
#include <ansi.h>
inherit ROOM;
int do_none();

void create()
{
	set("short", HIR"名人堂"NOR);
	set("long", @LONG
这里就是北大侠客行的名人堂。在这里供奉的有大侠，也有魔头，
也有不是大侠不是魔头的玩家。无论是哪一位，都曾冠绝一时，都有
一个长长而惊心动魄的故事，每一个故事都曾很深远地影响了一代甚
至两三代玩家。
    虽然他们都曾经轰轰烈烈掀起满江湖的风雨，如今，他们再也不
会在江湖出现了。他们都已经退出江湖，但他们的侠影魔踪很长时间
以后仍是一个传说。
LONG );

	set("no_fight", "1");
	set("no_steal", "1");
	set("no_beg", "1");
	set("no_sleep_room", "1");
	set("no_clean_up", 0);

	set("exits", ([
		"down" : __DIR__"wumiao",
	]));
      set("objects", ([
      __DIR__"player/quqing" : 1,

      ]));

	setup();
}
void init()
{
add_action("do_none","perform");
}
int do_none()
{
object ob = this_player();
message_vision("这里不准打架\n",ob);
return 1;
}

