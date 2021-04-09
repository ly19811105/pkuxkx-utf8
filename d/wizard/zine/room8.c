// Room: /d/wizard/zine/room8.c

inherit ROOM;

void create()
{
	set("short", "空房间");
	set("long", @LONG
这是一间什麽也没有的空房间。
LONG
	);
	set("main_dir", "/d/wizard/");
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"room11.c",
]));
	set("realmap", "                                               
                                    
                           [1;32m空房间[2;37;0m----猜猜猜    
                                    
                                               
");

	setup();
	replace_program(ROOM);
}
