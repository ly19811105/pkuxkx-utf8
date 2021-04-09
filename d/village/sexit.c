// Room: /d/village/sexit.c

inherit ROOM;

void create()
{
	set("short", "南村口");
	set("long", @LONG
这里是华山脚下，虽然远离县城，却没有什麽山贼草寇在附近出没。
西面是一个小村庄，看来村子里人家不多，村民们过着日出而作，日落而
息的宁静生活。穿过这个小村子，就是上华山的山路了。
LONG
	);

	set("exits", ([ /* sizeof() == 1 */
	"north" : __DIR__"sroad1",
	"southeast" : "/d/zhongyuan/nanyang",
	"southwest" : "/d/wudang/vroad4"
]));
	
        set("objects", ([ __DIR__"npc/dog": 1,
		 ]) );
        set("no_clean_up", 0);
        set("outdoors", "xx" );

        setup();
        replace_program(ROOM);
}

