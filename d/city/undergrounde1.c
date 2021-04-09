// Room: /city/undergrounde1.c by becool
inherit ROOM;

void create()
{
	set("short", "地下城东大街");
	set("long", @LONG
没想到扬州地下还有这么一个所在，宽阔的青石板街道向东边延伸。南边不时
地传来金属撞击声，像是一间铁铺，奇怪，怎么会有人把铁铺开在地下？
LONG);

	set("exits", ([
		"westup":"d/city/underground",
		"south":"d/city/playersmith1",
	  "north":"d/city/playersmith2",
		
	]));

	//set("objects",([
	//       __DIR__"npc/liumang.c":2,
	//]));
	setup();
	replace_program(ROOM);
}