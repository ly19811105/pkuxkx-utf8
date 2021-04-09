// Zine 兰州城

#include <ansi.h>
inherit __DIR__"lanzhou.c";
void create()
{
	set("short", "北府大道");
	set("long", @LONG
这里是兰州城北城的大道，巡逻的兵丁正在仔细盘问每一个过往的行人，整
体一片肃杀的气氛，东面是兰州将军的府邸，西面是国师府，而正北方向是西夏
国主的行宫。
LONG );
	set("exits", ([
		"east" : __DIR__"jiangjun",
		"west" : __DIR__"guoshi",
		"north" : __DIR__"xinggong",
		"south" : __DIR__"north_avenue1",
	]));
	set("outdoors", "lanzhou");
	setup();
}

