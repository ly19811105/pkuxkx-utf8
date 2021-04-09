// Room: /city/qianzhuang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
    set("short","扬州钱庄");
	set("long", @LONG
	这是一家老字号的钱庄，已有几百年的历史，在全国各地都有分店。它发
行的银票信誉非常好，通行全国。
LONG
	);

	set("exits", ([
		"out" : __DIR__"shichang",
	]));

	set("objects", ([
                 "/adm/npc/qian" : 1
	]));
	setup();
	replace_program(ROOM);
}

