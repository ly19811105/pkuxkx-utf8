// Room: /u/hacky/quanzhen/gongmen.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "[31m宫门[2;37;0m");
	set("long", @LONG
这是全真派重阳宫的宫门，这里整个由大块的青石铺成，极为平坦。但因年
代久远，都有些破损。丛丛小草从石板的缝隙中长了出来。门前站着两位道长，
北边遥遥可以望见一个高大的宫殿。
LONG
	);
    set("valid_startroom",1);
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"sanqingdian.c",
  "southdown" : __DIR__"shijie1",
"east" : __DIR__"machehang",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/zhike" : 1,
  __DIR__"npc/zhike2" : 1,
]));
     set("outdoors","quanzhen");
	setup();
   "/clone/board/qz_b"->foo();
}

void init()
{
    object me=this_player();
    if (me->query_skill("fx-step"))
    {
        me->set_skill("jinyan-gong",me->query_skill("fx-step",1));
        me->delete_skill("fx-step");
        me->set_skill_mapped("dodge","jinyan-gong");
        tell_object(me,HIM+BLINK+"你的飞仙步已经被自动转化成金雁功。\n"NOR);
    }
}