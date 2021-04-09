// Room: /city/dongdajie3.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "东大街");
	set("long", @LONG
你走在东大街上，踩着坚实的青石板地面。东边是东城门，可以听到守城官
兵的吆喝声。南边是一家宠物店，专卖各种小动物，你似乎还可以闻到店里飘出
来的气味。
LONG);
	set("outdoors", "city");

	set("exits", ([
		"east" : __DIR__"dongmen",
		"south" : __DIR__"petstore",
		"west" : __DIR__"dongdajie2",
		"north":__DIR__"huohang.c",
	]));

	setup();
	replace_program(ROOM);
}