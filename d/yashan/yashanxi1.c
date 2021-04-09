//模板
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "西驿道");
	set("long", @LONG
再往前就是牙山湾了，朝廷接获日本第二次绝交书后，
让李鸿章速筹战备，不要诿卸迁延，以免误了大事．李鸿
章原本期望利用外援促使日本撤兵，但最后得知外援已无
希望，才开始调动部队增援牙山，并作会师平壤的准备．
现在牙山湾已是一片战事气象．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "west" : __DIR__"yashanxi2.c",
		  "east" : __DIR__"wanxi3.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

