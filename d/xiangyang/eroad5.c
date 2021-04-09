// Modified by iszt@pkuxkx, 2007-04-03
// Modified by iszt@pkuxkx, 2007-05-21

#include <ansi.h>

inherit ROOM;

void create ()
{
	set("short",BLK"黑松岭"NOR);
	set("outdoors","xiangyang");
	set("long",CYN @LONG
这里到处都是千年古松，枝繁叶茂，遮天蔽日。一阵阴风吹来，枝叶乱摇隆
隆作响，似乎每棵树后都有人在窥视着你。你后脊梁不禁一阵发凉，正要转身离
开这个是非之地，突然仓琅琅一阵铜锣响亮，几个彪形大汉从树后窜了出来，手
持利刃，拦住你的去路。
LONG NOR);
	set("objects", ([
		__DIR__"npc/tufei1" : 1,
		__DIR__"npc/tufei2" : 3,
	]));
	setup();
}

void init()
{
        delete("realmap");
	set("exits/eastup",__DIR__"chukou"+random(4));
	set("exits/westup",__DIR__"chukou0");
	set("exits/south",__DIR__"chukou"+random(4));
	set("exits/north",__DIR__"chukou"+random(4));
	add_action("do_look", "look");
}

int do_look(string arg)
{
	if(random(2) && query("exits/"+arg))
	{
		write("那边是一片树林，什么也看不到。\n");
		return 1;
	}
	if(query("exits/"+arg))
		write("你努力的望着，终于看到了些什么。\n");
	return 0;
}

int valid_leave(object me, string dir)
{
	object ob;
	object* inv;
	int i;

	if ((ob = present("tu fei", environment(me))) && living(ob) )
		return notify_fail("土匪嘿嘿冷笑几声：我们这黑松岭难道是你想来就来，想走就走的？\n");
	if(wizardp(me) || !load_object(query("exits/"+dir))->query("faint_player"))
		return ::valid_leave(me, dir);

	me->move(query("exits/"+dir));

	tell_object(me, RED"
    你走着走着，突然脚下一空，你掉进了土匪们设下的陷阱！瞬间周围一片昏
暗，一股怪异的气味扑鼻而来，你脑中一片空白，仿佛到了仙界。冥冥中你被人
抬到一个地方，有人在你的身上摸来摸去，最后后脑海被狠狠砸了一下。
"NOR);
	inv = all_inventory(me);

	for (i = 0; i < sizeof(inv); i++)
		if (userp(inv[i]))
			inv[i]->move(environment(me));
		else
			destruct(inv[i]);

	new("/clone/misc/cloth.c")->move(me);
	me->unconcious();
}
