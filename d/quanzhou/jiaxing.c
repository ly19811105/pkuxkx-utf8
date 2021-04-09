// Room: /d/quanzhou/jiaxing.c
// Date: May 21, 96   Jay

inherit ROOM;

void create()
{
	set("short", "嘉兴城");
	set("long", @LONG
这里是江南名城嘉兴。城东是风景如画的南湖。城北早先有座醉仙楼，
当年全真七子之一的丘处机和江南七怪就在那里盟约寻找忠良之后。不知
道什么原因店主把它迁到扬州了。
LONG
	);

	set("exits", ([
                "north" : "/d/suzhou/road5",
//+
 //       "northup":"/u/aiai/create_menpai/苹果派/fronthall.c",
//+



                "west" : __DIR__"qzroad2",
                "east" : __DIR__"nanhu",
		"south" : __DIR__"jxnanmen",
	]));


        set("objects", ([
                __DIR__"npc/zhangasheng": 1]));
	set("outdoors", "quanzhou");
	setup();
	replace_program(ROOM);
}

