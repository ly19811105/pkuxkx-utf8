//Cracked by Kafei
inherit ROOM;

void create()
{
        set("short", "般若台");
        set("long", @LONG
这是一座孤伶伶的高台，台上除了几个蒲团外空空如野。据闻许多高僧爱在
此冥思，以求进一步的修行。方案上的那半部梵经，却是来自西域嫡淦嬷铩?LONG
        );
       set("exits", ([
		"west" : __DIR__"tianls8.c",
        "east" : __DIR__"tianls7",
        "southeast" : __DIR__"tianls6",
        "northup" : __DIR__"tianls10",		]));

set("no_clean_up", 0);
        set("cost", 3);

setup();
}

