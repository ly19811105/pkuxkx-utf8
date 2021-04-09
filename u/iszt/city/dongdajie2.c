// Room: /city/dongdajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "东大街");
	set("long", @LONG
你走在东大街上，踩着坚实的青石板地面。东边传来一阵阵猫嘶狗咬还有小
鸟的鸣叫声，与西边朗朗的读书声混杂在一起。北边是一家老字号的药铺，南边
是打铁铺，叮叮当当的声音老远就能听到。
LONG);
        set("outdoors", "city");

	set("exits", ([
		"east" : __DIR__"dongdajie3",
		"south" : __DIR__"datiepu",
		"west" : __DIR__"dongdajie1",
		"north" : __DIR__"yaopu",
	]));

	setup();
	replace_program(ROOM);
}