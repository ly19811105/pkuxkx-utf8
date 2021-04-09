// Room: /d/beijing/zijin/xiaohuayuan.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"小广场"NOR);
	set("long",
HIC"这是保和殿后的一个小广场，向北走是乾清门，向南是保和殿，
向西是隆宗门，向东是景运门。南边保和殿台阶下是一块巨大的石
雕(sculpture)。东北方向一排平房是军机处。\n"NOR
	);
	set("exits", ([ /* sizeof() == 9 */
 	"south" : __DIR__"baohedian",
  	"east" : __DIR__"jingyunmen",
//         "enter" : __DIR__"junjichu",
  	"north" : __DIR__"qianqingmen",
 	"west" : __DIR__"longzongmen",

]));
	set("item_desc", ([ /* sizeof() == 1 */
  "sculpture" : "这是宫中最大的一块石雕，石雕四周刻有缠枝莲花纹，下部为海\n"
		"水江牙，中间雕刻着流云衬托着九条蟠龙和升龙，云龙形象生动，\n"
		"雕刻精细，一丝不苟。\n",
]));
	set("outdoors", "beijing");
	set("objects", ([
		"/d/beijing/npc/shiwei1" : 6,
		"/d/beijing/npc/shiwei2" : 6,
		"/d/beijing/npc/zhaoqixian" : 1,
		]) );
	setup();
	replace_program(ROOM);
}
