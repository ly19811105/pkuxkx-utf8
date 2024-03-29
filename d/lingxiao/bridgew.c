// File		: bridgew.c
// Created By	: iszt@pkuxkx, 2006-08-14

#include <ansi.h>;

inherit ROOM;

void create()
{
	set("short", YEL"桥头"NOR);
	set("long", @LONG
西、南两条深谷在此交会，向东北方延伸，这里的地势自然极为险要：东连
一线索，北与凌霄城隔谷相望。北边的深谷仿佛天然的护城河，城墙高逾三丈，
墙头墙垣雪白一片，尽是冰雪。城墙上凝结冰雪，坚如精铁，外人实难攻入。一
条吊桥(bridge)高高在上，有人喊(yell)一声就有轮值弟子放下来让人进城。
LONG);

	set("outdoors", "凌霄城");
	set("no_sleep_room", 1);
	set("item_desc", ([
		"bridge" : "从这里看过去，那边好象是几个雪山弟子掌握着放下吊桥的机关。为什么不喊(yell)一声呢？\n",
	]));
	set("exits", ([
		"southwest" : __DIR__"xuedi6",
		"east" : __DIR__"yixiansuo",
	]));
	set("objects", ([
		__DIR__"npc/dizi_xunluo" : 1,
	]));
	set("lingxiao_yell_bridge_room", 1);
	setup();
}

void init()
{
	add_action("do_yell", "yell");
}

int up_bridge()
{
	object room;

	if(!( room = find_object(__DIR__"chengmen")) )
		room = load_object(__DIR__"chengmen");
	if(objectp(room))
	{
		delete("exits/north");
		message("vision", "只听一阵吱呀乱响，吊桥又升了起来。\n",
			this_object());
		room->delete("exits/south");

		message("vision", "六名雪山弟子一齐转动机关，吊桥便又升了起来。\n", room);
	}
	else message("vision", "错误: 请报告巫师，gate not found(close).\n", room);
}

int do_yell(string arg)
{
	object me = this_player();
	object room;

	if(query("exits/north"))
		return notify_fail("吊桥已经放下来了，快进去吧。\n");

	if(!arg)
		arg = "啊";
	switch(arg)
	{
		case "bridge" : arg = "放下吊桥"; break;
		case "boat" : arg = "船家"; break;
		case "zt" : arg = "我是猪头"; break;
		case "dizi" : arg = "轮值弟子"; break;
		case "banana" : arg = HIY"香蕉"NOR; break;
	}

	if(me->query("neili") > 500)
		message_vision("$N轻吸一口气，长啸一声：「"+arg+"～～～」，声音远远传了出去。\n", me);
	else
		message_vision("$N朝对岸高声喊道：「"+arg+"！」\n", me);

	if (!arg || (arg != "放下吊桥" && arg != "轮值弟子"))
		return notify_fail("你的声音在深谷中来回震荡，可就是无人为你放下吊桥。\n");

	if(!( room = find_object(__DIR__"chengmen")) )
		room = load_object(__DIR__"chengmen");
	if (me->query("shen") < -1000 && !me->query("special_skill/sociability") && !me->query_temp("lingxiao_bribe_bridge"))
	{	// 有长袖善舞的可以进；有贿赂过巡逻弟子的可以进。by lordstar 20180607
		message_vision("只听吊桥对岸对$N高喊：邪魔外道之人，离我们凌霄城远点，否则别怪我们不客气！\n", me);
		return notify_fail("看来要进城还是另想办法吧。\n");
	}

	if(objectp(room))
	{
		set("exits/north", __DIR__"chengmen");
		message_vision("只听得轧轧声响，吊桥缓缓放下，正架在你的眼前。\n", me);
		room->set("exits/south", __FILE__);
		message("vision", "城外一阵「"+arg+"」的呼叫，六名雪山弟子一齐转动机关，吊桥便架在了深谷之上。\n", room); 
		if (me->query_temp("lingxiao_bribe_bridge"))
		{
			me->delete_temp("lingxiao_bribe_bridge");
			tell_object(me, HIG"一名雪山弟子看看无人注意，偷偷对你道：「快进去吧！下次需要进城再来找我们兄弟帮忙。」\n"NOR);
		}
		remove_call_out("up_bridge");
		call_out("up_bridge", 10);
	}

	return 1;
}

int valid_leave(object me, string dir)
{
	if ( dir != "north" )
		return ::valid_leave(me, dir);

	if (dir == "north") {
		if (me->id("xueshan dizi")) return 0;
	}

	if ( (me->query("family/family_name") == "雪山派"))
		if ( me->query("family/generation") > 6 )
			message_vision(HIW"六名雪山弟子齐声对$N道：欢迎师兄回城！\n"NOR, me);
	
	return 1;
}
