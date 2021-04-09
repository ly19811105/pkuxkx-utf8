// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
int xunluo()
{
	object npc;
	for (int i=0;i<4;i++)
	{
		npc=new(__DIR__"npc/bing1");
		npc->set("xunluo",query("xunluo_path")%2);
		if (i==0)
		{
			npc->set("leader",1);
			npc->set_name("巡城士兵首领", ({ "shibing shouling", "shouling", }));
			npc->set("long","他是这一队士兵的首领。\n");
		}
		npc->move(this_object());
	}
	remove_call_out("xunluo");
	call_out("xunluo",60);
	add("xunluo_path",1);
	if (query("xunluo_path")>=10)
	set("xunluo_path",0);
	return 1;
}
void create()
{
	set("short", "北府大道");
	set("long", @LONG
这里是兰州城北城的大道，巡逻的兵丁渐渐多起来了，东面是部落首领居住
的祖儒府，西面是兰州城民政长官的刺史府。
LONG );
	set("exits", ([
		"east" : __DIR__"zuru",
		"west" : __DIR__"cishi",
		"north" : __DIR__"north_avenue2",
		"south" : __DIR__"guangchang",
	]));
	set("outdoors", "lanzhou");
	setup();
	xunluo();
}

