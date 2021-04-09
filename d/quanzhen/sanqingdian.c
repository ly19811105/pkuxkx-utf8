// Room: /u/hacky/quanzhen/sanqingdian.c
// Made by: hacky

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "[31m三清殿[2;37;0m");
	set("long", @LONG
这里是重阳宫的三清殿，是全真教会客的地点。供着元始天尊、太上道君和
太上老君的神像，香案上香烟缭绕。正厅上高挂着：                                            
                                                                                         
			[33m三     清     殿[2;37;0m                               
                                                                                         
靠墙放着几张太师椅，地上放着几个蒲团。东边是升遐房，西边是烧香坊，北边
是崇玄台。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"gongmen.c",
  "north" : __DIR__"xuanzt",
  "west" : __DIR__"shaoxf",
  "east" : __DIR__"shengxf",
]));
	set("objects", ([ /* sizeof() == 1 */
  CLASS_D("quanzhen")+"/cheng":1,
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
