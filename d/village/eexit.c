// Room: /d/village/nwexit.c

inherit ROOM;

void create()
{
	set("short", "东村口");
	set("long", @LONG
这里是华山脚下，虽然远离县城，却没有什麽山贼草寇在附近出没。
往东就是上山的路了。西边是一个小村庄，村子里人家并不多，村民们过
着日出而作，日落而息的宁静生活。
LONG
	);

	set("exits", ([
//+
    //    "northup":"/u/aiai/create_menpai/小爱工作室/fronthall.c",
//+













 /* sizeof() == 2 */
	"west" : __DIR__"eroad1",
	"east" : "/d/huashan/path1",
]));
	
        set("objects", ([ __DIR__"npc/boy": 1 ]) );

        set("no_clean_up", 0);
        set("outdoors", "xx" );

        setup();
        replace_program(ROOM);
}

