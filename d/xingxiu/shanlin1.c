// 山林
// edit: by zine Oct 19 2010

inherit __DIR__"shanlinconfig";

void create()
{
	set("short", "山林");
	set("long", @LONG
这里是一座毒虫出没的山林，千年的古树却是制作兵器的上佳材料。
LONG
	);
    set("normaldesc", @LONG
这里是一座毒虫出没的山林，千年的古树却是制作兵器的上佳材料。
LONG
	);
	set("exits", ([ 
		"north" : __DIR__"shanlin3",
        "east": __DIR__"shanlin",
		
    ]));
	//set("objects", ([(__DIR__"npc/qinjun") : 1,
    //]));
	setup();
	::create();
}

