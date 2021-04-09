// Room: /d/quanzhou/xijie.c
// Date: May 7, 96   Jay

inherit ROOM;

void create()
{
	set("short", "西街");
	set("long", @LONG
这里是泉州的西大街，北面有一所破败的宅子。西面有一家杂货铺，
专卖女人家用的东西，男人不可以进去。南面则是巨鲸帮的总舵。
LONG
	);

	set("exits", ([
                "east" : __DIR__"zhongxin",
		"south" : __DIR__"jujing-bang",
		"northwest": __DIR__"zengjing",
                "north" : __DIR__"machehang",
                "west" : __DIR__"zahuopu",
	]));

	set("outdoors", "quanzhou");
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "west" && ((string)me->query("gender") =="男性") && !wizardp(me))
                return notify_fail("你个大老爷们儿去那干嘛！！\n");
        return 1;
}


