//模板
inherit ROOM;

void create()
{
	set("short", "驿道");
	set("long", @LONG
从嘉兴南湖望东，是一条驿道，这一条驿道通向一直通向沿海
的军事重镇－－牙山，不过从这里到牙山还有些距离．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		"/d/lingxiao/npc/dizi_yashan" : random(2),
		]));
	set("exits", ([ 
		  "southwest" : "/d/quanzhou/nanhu1",
		  "east":__DIR__"yidao2.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

