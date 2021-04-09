// Room: /d/beijing/zijin/huangjidian.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"皇极殿"NOR);
	set("long",
HIC"殿顶鎏金铜瓦是用黄金鎏成，脊上八条金龙，四上；四下，似腾云驾
雾。殿内四壁的彩色壁画，内容丰富，色彩绚丽。\n"NOR
	);
	set("exits", ([ /* sizeof() == 2 */
  	"north" : __DIR__"ningshougong.c",
  	"south" : __DIR__"ningshoumen",
]));

	setup();
	replace_program(ROOM);
}
