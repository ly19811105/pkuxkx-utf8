// File		: bingwest5.c
// Created By	: iszt@pkuxkx, 2006-09-04

inherit ROOM;

void create()
{
	set("short", "石板路");
	set("long", @LONG
这里是一片青石铺就的平整的广场，雕饰极尽简单，却整齐有序。再往西北
是一条石板路，通向内城。
LONG);
	
	set("outdoors", "凌霄城");
	set("exits", ([
		"east" : __DIR__"bingjie5",
		"northwest" : __DIR__"stonew1",
	]));
	set("objects", ([
		__DIR__"npc/dizi" : 1,
	]));

	setup();
	replace_program(ROOM);
}