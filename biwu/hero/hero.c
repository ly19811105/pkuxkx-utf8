
inherit "/biwu/hero/heromap.c";


void create()
{
	set("short", "英雄冢");
	set("long", @LONG
英雄路漫漫，白骨不世功。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		  "west" : __DIR__"westgate",
		  "east" : __DIR__"eastgate",
		]));
	set("no_clean_up", 0);
	set("flag","英雄旗");
	set("default_flag_hp",10);
	set("flag_hp",10);
    set("objects", ([
        "/biwu/jieshuo2" : 1,
        ]));	
    set("action_queue",({}));
	setup();
}


int valid_leave(object me, string dir)
{
    return notify_fail("不分胜负，不能离场。不怕愧对师门吗？\n");
}