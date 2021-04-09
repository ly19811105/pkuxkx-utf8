#include <ansi.h>
#include <room.h>
#include "nodie.h"
inherit ROOM;
void npc_do_kill(object me);
int have_npc_can_kill(object me);

void create()
{
	set("short", "小厅");
	set("long","这里是绿柳山庄里的一个偏僻小厅，堆放着一些杂物，但是靠西的一堵墙(wall)
前却什么都没有摆放，显得十分惹眼。有两个劲装武士正围着一张小桌喝酒闲聊。\n"NOR);
	set("item_desc", ([
		"wall" : "一堵白墙，仔细看的话能够发现有机关的痕迹，你可以用力推推(push)看。\n",
	]));
    set("objects",([
        __DIR__"npc/guard.c":2,
    ]));
	setup();
}

void init()
{	
	object me = this_player();
	add_action("do_push","push"); 
	if (userp(me) || me->query("id")!= "jinzhuang wushi")
		call_out("npc_do_kill",1,me);
}

int do_push(string arg)
{
	object me = this_player();
	if (!arg || arg != "wall")
		return notify_fail("你要推什么？\n");
	if (me->is_fighting() || me->is_busy())
		return notify_fail("你还是先忙活完自己的事再说吧。\n");
	if (have_npc_can_kill(me))
		return notify_fail("守卫正盯着你呢，你还敢轻举妄动？\n");
	if ((int)me->query("lvliu/jiuzhou/start")>time())
		return notify_fail("你使出吃奶的力气也推不动暗门，还是过会儿再来试试吧。\n");
	
	message_vision(HIC"$N在墙上轻轻一推，一道暗门就被推开了。$N钻了进去，又把门掩上了。\n"NOR, me);
	me->move(__DIR__"jiuzhou_mishi1");
	message_vision(HIC"$N摸着墙跟，蹑手蹑脚地走了过来。\n"NOR, me);
	return 1;
}

void npc_do_kill(object me)
{
	object *allob = all_inventory(this_object());
	if (!objectp(me)) return;
	for (int i=0;i<sizeof(allob);i++)
	{
		if (!allob[i]->is_character())
		{
			destruct(allob[i]);
			continue;
		}
		if (allob[i]->query("id") != "jinzhuang wushi" 
			|| userp(allob[i])
			|| !living(allob[i])) 
			continue;
		message_vision(HIC"$N大喝一声：「什么人，胆敢来此放肆！」\n"NOR, allob[i]);
		allob[i]->kill_ob(me);
	}	
}

int have_npc_can_kill(object me)
{
	object *allob = all_inventory(this_object());
	if (!objectp(me)) return 1;
	for (int i=0;i<sizeof(allob);i++)
	{
		if (allob[i]->query("id") != "jinzhuang wushi" 
			|| userp(allob[i])
			|| !allob[i]->is_character()
			|| !living(allob[i])) 
			continue;
		return 1;
	}	
	return 0;
}
