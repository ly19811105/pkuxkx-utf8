// Room: /d/huijiang/shulin1.c
// by hubo

inherit ROOM;

void create()
{
	set("short", "树林");
	set("long", @LONG
湖边的这树林并不茂密，只是稀疏的几棵，远处高山上覆盖着白雪，
如同天上白色的云彩。湖中碎冰相互撞击的叮叮声犹自传来。林中野花
的香味从脚下升上来，在林中铺了浅浅的一层。
LONG
	);
	set("no_clean_up", 0);
	set("outdoors", "huijiang");
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"buluo",
]));

	setup();

}

