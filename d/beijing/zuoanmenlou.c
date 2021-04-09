// Room: /d/beijing/east/zuoanmenlou.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIG"左安门城楼"NOR);
	set("long",
HIY"这是左安门城门上的望楼，一队队壮健的守城军丁盔甲鲜
明，手持大刀长矛，强弓利箭，警惕的注视着城下过望行人；
城门两边是长长的北京外城墙。\n"NOR
	);
	set("exits", ([ /* sizeof() == 3 */
  	"west" : __DIR__"chengqiang8",
  	"down" : __DIR__"zuoanmen",
 	 "east" : __DIR__"chengqiang7",
]));
	set("objects", ([
		__DIR__"npc/wujiang": 1,
		]));

	setup();

}
void init()
{
     object me = this_player();
     if(me->query_temp("chaoting/xuncheng"))
     {
       me->set_temp("xc/zuoanmenlou",1);
      }

}
int valid_leave(object me, string dir)
{
	if(dir == "down" && me->query("id") == "wu jiang")
	return 0;

    	return ::valid_leave(me, dir);
}