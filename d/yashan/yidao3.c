//模板
inherit ROOM;

void create()
{
	set("short", "驿道");
	set("long", @LONG
这里是一条驿道，这一条驿道通向一直通向沿海
的军事重镇－－牙山，不过从这里到牙山还有些距离．
LONG
	);
	set("outdoors", "yanshan");
	set("objects", ([
		  
		]));
	set("exits", ([ 
		  "southwest" : __DIR__"yidao2.c",
		  "northeast" : __DIR__"yidao4.c",
		]));
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}

