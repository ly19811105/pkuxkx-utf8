// Rewrote by iszt@pkuxkx, 2007-02-11

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
这里便是沥泉山上崎岖不平的山路。这里地处中原，山势虽不高，但由于连
年战乱，荒山野岭之间罕有人迹，这条山路走起来却也颇为费力。不知为什么，
这里并没有山中常有的水声或是鸟鸣，静得吓人。
LONG);
	set("outdoors", "沥泉山");

	set("exits", ([
		"southdown" : __DIR__"shanlu6",
		"northwest" : __DIR__"shanlu8",
	]));

	setup();
	replace_program(ROOM);
}
