#include <ansi.h>

inherit ROOM;



void create()

{

	set("short", HIY"天地会暗道"NOR);

	set("long",
HIC"地道里一片漆黑，呼呼的风声从四面八方传来。你什么也看不
见，只能在地道里瞎摸乱撞。西面似乎隐隐约约有人说话，但只一
会儿又没声了。你使劲地摇了摇头，很怀疑这到底是不是幻觉。好
象你已经迷路了。\n"NOR
	);



	set("exits", ([

		"south" : __FILE__,

		"north" : __DIR__"andao4",

		"east" : __FILE__,

		"west" : __DIR__"andao6",

	]));



	setup();

	replace_program(ROOM);

}



