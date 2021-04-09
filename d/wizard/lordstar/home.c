#include <ansi.h>
inherit ROOM;
int do_zhangsan(string user);

void create()
{
	set("short", HIY"云之遥的家"NOR);
	set("long", HIG"这里是云之遥的家，到处乱七八糟的，各种工具丢得到处都是，大概只有\n它的主人才知道各种东西放在哪里。\n"NOR
	);
	set("exits", ([
		"out" : "/d/city/guangchang",
	]));
    set("no_die",1);
	set("no_sleep_room",1);
	setup();
}

void init()
{
	add_action("do_zhangsan","zhangsan");
}

int do_zhangsan(string user)
{
	object ob, zs;
	object me = this_player();
	if (me->query("id")!="lordstar" && me->query("id")!="caijue")
		return notify_fail("你又不是房间的主人，还是不要乱动房间里的东西。\n");
	if (!objectp(ob=find_player(user)))
		return notify_fail("没有这个玩家在线。\n");
	if (ob->query("xkdling"))
		return notify_fail("人家已经去过侠客岛了，你就别操那个闲心了。\n");
	zs = new("/d/xiakedao/npc/zhangsan.c");
	zs->move(this_object());
	zs->set("count", 0);
	ob->set_temp("marks/bihua",1);
	message_vision(HIC"$N按动了一个按钮，叮的一声响，一位大汉推开门走了进来。\n"NOR, me);
	message_vision(HIW"$N"HIW"躬身行礼道：主人请吩咐！\n"NOR, zs);
	message_vision(HIW"$N向$n"HIW"耳语了两句，$n躬身领命出门去了。\n",me, zs);
	zs->FaLingToUser(ob->query("id"));
	return 1;
}