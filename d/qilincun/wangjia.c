// This is a room made by zhx.
// Rewrote by iszt@pkuxkx, 2007-02-11

inherit ROOM;

void create()
{
        set("short", "王员外家");
        set("long", @LONG
这里是王员外家，地势宽大，三面房舍，都是几净窗明，陈设整齐，比起村
中的破房要好得多。西北角土坡上，还有一座凉亭，可以望远。后院隐隐传来练
武声。
LONG);
	set("objects", ([
		__DIR__"npc/wangyuanwai.c" : 1,
		__DIR__"npc/wangqi.c" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"xiaolu1",
		"north" : __DIR__"lianwuchang",
	]));

	setup();
	replace_program(ROOM);
}