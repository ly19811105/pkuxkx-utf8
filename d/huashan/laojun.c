// laojun.c

inherit ROOM;

void create()
{
        set("short", "老君沟");
	set("long", @LONG
爬过两个要命的悬崖，可在这里稍作歇息。老君沟是一条半里多长的
山沟，相传为太上老君所开，故名老君沟。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "westdown" : __DIR__"baichi",
	"northup" : __DIR__"bieyuan",
  "southup" : __DIR__"husun",
]));
        set("no_clean_up", 0);
        set("outdoors", "xx" );
        set("room","room12");
        setup();
        replace_program(ROOM);
}
 
