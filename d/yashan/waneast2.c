//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "牙山湾东路");
	set("long", @LONG
走到这里，你已经依稀可以看到济远和广乙两艘
军舰的英姿，据说本来要给他们配弹药的银子被慈禧
太后用来修什么院子给挪用了，到时候真和日本人干
起来还不知道弹药够不够用呢？
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
       "north" : __DIR__"wnbingying1.c",
		  "west" : __DIR__"waneast1.c",
		  "east" : __DIR__"waneast3.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

