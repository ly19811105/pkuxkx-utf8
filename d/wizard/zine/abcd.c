// Room: /d/wizard/zine/abcd.c

inherit ROOM;

void create()
{
	set("short", "空房间");
	set("long", @LONG
这是一间什麽也没有的空房间。
LONG
	);
	set("main_dir", "/d/wizard/");
	set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"room8.c",
  "west" : __DIR__"room3.c",
]));
	set("no_clean_up", 0);
	set("realmap", "                                               
                                    
                 猜猜猜----[1;32m空房间[2;37;0m              
                                    
                                               
");

	setup();
	replace_program(ROOM);
}
