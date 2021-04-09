// Room: /d/quanzhou/qzroad4.c
// Date: May 7, 96   Jay

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
你走在一条山路上。时值春日，路旁的山坡上开满了金黄色的油菜花。
北面是江南名城嘉兴。向南则进入福建武夷山区。
LONG
	);

	set("exits", ([
                "north" : "d/quanzhou/jxnanmen",
                "east" : "/d/yuewangmu/xiaodao7.c",
                "southwest" : "/d/hangzhou/shanlu1",
		"south" : __DIR__"qzroad5",
        "southeast" : "/d/fuzhou/shanlu3",
	]));

	set("outdoors", "quanzhou");
	setup();
	
}

int valid_leave(object me,string dir)
{  
	if (dir=="north" || dir=="east" || dir=="southwest")
    {
        if (me->query("sinan")=="yes")
        {
            return notify_fail("你老兄哪能出去呀？\n");
        }
        
    }
	return ::valid_leave(me, dir);
}
