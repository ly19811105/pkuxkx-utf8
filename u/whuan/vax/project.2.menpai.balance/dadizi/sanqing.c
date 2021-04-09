// sanqing.c 三清殿
// by Xiang

inherit ROOM;

void create()
{
	set("short", "三清殿");
	set("long", 
"这里是凌霄宫的三清殿，是武当派会客的地点。供着元始\n"
"天尊、太上道君和天上老君的神像，香案上香烟缭绕。靠墙放\n"
"着几张太师椅，地上放着几个蒲团。东西两侧是走廊，南边是\n"
"练武的广场，北边是后院。\n"
	);
	set("valid_startroom", 1);
	set("exits", ([
		"south" : __DIR__"guangchang",
		"north" : __DIR__"houtang",
		"east" : __DIR__"youdian",
		"west" : __DIR__"zuodian",
	]));
	set("objects", ([
		CLASS_D("wudang") + "/guxu" : 1,
		CLASS_D("wudang") + "/song" : 1,
		"/clone/npc/dadizi/wudang.c"    : 1,]));
	setup();
    "/clone/board/wd_b"->foo();
}

int valid_leave(object me,string dir)
{	
    mapping fam=(mapping)me->query("family");
	if (dir=="north" && (!fam || fam["family_name"]!="武当派")
	&& objectp(present("song yuanqiao",environment(me)))
	&& living(present("song yuanqiao",environment(me))))
	    return notify_fail("宋远桥拦住你说道：后面是本派重地，你不是武当弟子，此去多有不便，请留步。\n");
	return ::valid_leave(me, dir);
}
