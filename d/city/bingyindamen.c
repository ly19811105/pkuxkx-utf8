// Room: /city/bingyindamen.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "兵营大门");
	set("long", @LONG
你正站在兵营的门口，面对着一排简陋的营房，可以看到穿着制服的官兵正
在操练，不时地传来呐喊声。老百姓是不允许在此观看的，你最好赶快走开。
LONG);

	set("exits", ([
		"south" : __DIR__"bingyin",
		"north" : __DIR__"xidajie1",
	]));

	set("objects", ([
		__DIR__"npc/bing" : 4,
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	object *ob;
	int i;
	if( dir != "south" || me->query("class") == "officer" || wizardp(me) || present("xin jian",me))
		return ::valid_leave(me, dir);
	ob = all_inventory( environment( me ));
	for(i=0; i<sizeof(ob); i++) 
	{
		if( !living(ob[i]) || ob[i]->query("id") != "guan bing" ) continue;
		return notify_fail("官兵们拦住了你的去路。\n");
	}
	return ::valid_leave(me, dir);
}