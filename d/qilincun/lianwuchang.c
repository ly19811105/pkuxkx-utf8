// This is a room made by zhx.
// Rewrote by iszt@pkuxkx, 2007-02-11

inherit ROOM;

void create()
{
	set("short", "练武场");
	set("long", @LONG
这里是王员外为了方便周桐授徒和王贵岳飞等练武，特意修的一个练武场。
场地虽小，练武用的家伙却是样样齐全，单箭靶就有好几个，还有各种兵器陈列
在那里。每到晚上，岳飞等就在此练武，常有金铁交鸣之声传出。
LONG);
	set("objects", ([
		__DIR__"npc/wanggui.c" : 1,
		__DIR__"npc/tanghuai.c" : 1,
		__DIR__"npc/zhangxian.c" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"wangjia",
	]));
	setup();
	replace_program(ROOM);
}