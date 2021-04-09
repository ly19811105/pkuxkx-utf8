#include <ansi.h>
#include <room.h>
#include "nodie.h"
inherit ROOM;
void create()
{
	set("short", HIY"小侧厅"NOR);
	set("long","这里是绿柳山庄的小侧厅。靠墙的位置上摆放着一个栩栩如生的机关人，供庄内
的贵客习武和测试技能之用。\n"NOR);
	set("exits", ([
		"east" : __DIR__"dating",
	]));
    set("objects",([
        __DIR__"npc/jiguanren0.c":1,
    ]));
	set("item_desc", ([
		"pillar" : "你沿着立柱往上看去，似乎屋顶下有个洞，你不禁想到，或许可以爬(climb)上去瞧瞧……\n",
	]));
	setup();
}

void init()
{	
	add_action("do_climb","climb");       
}

int do_climb(string arg)
{
	object me = this_player();
	if (!arg || arg != "pillar")
		return notify_fail("你要爬什么？\n");
	if (me->is_fighting() || me->is_busy())
		return notify_fail("你现在没空爬柱子。\n");
	message_vision(HIC"$N往手里吐了口唾沫，双手抱住柱子开始往上爬……\n"NOR, me);
	me->start_busy(5);
	call_out("climb_up", 2, me);
	return 1;
}

void climb_up(object me)
{
	if (!objectp(me)) return;
	if (me->query("combat_exp")<10000000 && !random(4))
	{
		message_vision(YEL"$N一不留神手一滑，惊叫了一声，从柱子上摔了下来，啪唧一下摔了个大马趴。\n"NOR, me);
		me->start_busy(8);
		return;
	}
	message_vision(HIY"$N沿着柱子爬上了屋顶，顺着横梁爬到了洞口，往里望了一眼，似乎有点亮光，就钻了进去。\n"NOR, me);
	me->start_busy(0);
	me->move(__DIR__"hengliang");
}

