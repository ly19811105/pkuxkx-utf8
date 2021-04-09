//hubian2.c
//by hehe
//2003.3.5

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "码头");
    set("long", @LONG
这是湖边一个小小的码头,湖上停着艘小船(boat)，只见
岸上疏疏落落四五座房舍，建造在一个不知是小岛还是半
岛之上。房舍小巧玲珑，颇为精雅。这里还可以遥遥望见
燕子坞和听香水榭，湖面之下栽了水桩(zhuang)通向两地。
LONG
    );

    set("exits", ([
        "west" : __DIR__"qroad1",
    ]));

	set("item_desc", ([
		"boat" :
"    这是一艘小船，看来要从这里出去就要靠他了。\n",
		"zhuang" :
"一根根木桩深埋于湖底，湖面上只隐隐约约露出,不知道踩上去什么感觉?
木桩在湖中延伸，似乎可以通到听香水榭(tingxiang)和燕子坞(yanziwu)\n",
                     ]));

    set("outdoors", "murong");
    setup();

}
void init()
{
    add_action("do_find", "find");
    add_action("do_enter", "enter");
	add_action("do_cai", "cai");
	add_action("do_cai", "step");
}

int do_find(string arg)
{
	object me;
	object *inv;
	int i;
	me = this_player();

	if (arg=="boat" && me->query("family/family_name")=="姑苏慕容")
	{

		inv=all_inventory(me);
		for(i=0; i<sizeof(inv); i++) {
			if (userp(inv[i]))
				return notify_fail("你负重太大了，小舟恐怕载不动你。\n");
		}
		tell_object(me, "你熟门熟路地找到一条小舟，解开绳子，划了起来。\n");
		tell_object(me, "不一会儿，小船划到了岸边。\n");
		me->move("/d/murong/hubian1.c");
		return 1;
	}
	return 0;
}


int do_enter(string arg)
{
    object me;
	object *inv;
	int i;
    me = this_player () ;

	if(arg!="boat")
	{
		message_vision("看清楚！你要往哪里钻?\n",me);
		return 1;
	}
		inv=all_inventory(me);
		for(i=0; i<sizeof(inv); i++) {
			if (userp(inv[i]))
				return notify_fail("你负重太大了，小舟恐怕载不动你。\n");
		}
    message_vision("\n$N跃上小舟，船就划了起来。\n\n" ,me );
    me->move("/d/murong/dahu2") ;
    tell_object(me, "\n小舟在湖中藕菱之间的水路上穿来穿去，你的眼都花了...\n\n" ) ;
    call_out("wait2", random(10) , me ) ;
    return 1 ;
}
void waittime(object me)
{
	if (!me) return;
	tell_object(me, "\n小舟终于划到近岸，你从船上走了出来。\n\n" ) ;
	me->move ("/d/murong/hubian1") ;
}
void wait1(object me)
{
	if (!me) return;
	tell_object(me, "\n............................\n" ) ;
	tell_object(me, "\n.......................\n" ) ;
	tell_object(me, "\n...................\n" ) ;
	tell_object(me, "\n..............\n" ) ;
	tell_object(me, "\n.....\n" ) ;
	me->move ("/d/murong/dahu") ;
        call_out("waittime", random(10) , me);
}
void wait2(object me)
{
	if (!me) return;
	tell_object(me, "\n............................\n" ) ;
	tell_object(me, "\n.......................\n" ) ;
	tell_object(me, "\n...................\n" ) ;
	tell_object(me, "\n..............\n" ) ;
	tell_object(me, "\n.....\n" ) ;
	me->move ("/d/murong/dahu1") ;
        call_out("wait1", random(10) , me);
}

int do_cai(string arg)
{
	object me;
    	me = this_player () ;
	if( !arg )
		return notify_fail("你要踩什么？\n");
	if ( arg == "zhuang" )
	{
		if ( (int)me->query("neili") < 80)
			return notify_fail ("你伸脚轻轻试了试木桩，心中有点发慌，忙缩了回来。\n");
	    if ( (int)me->query("combat_exp") <10000)
	    {
			me->receive_damage("qi", 50, "掉进湖里淹死了");
            me->receive_wound("qi",  50, "掉进湖里淹死了");
            message_vision("$N只觉得脚下一个踉跄，... 啊...！\n", me);
            tell_object(me, "你掉进大湖，几经努力才爬上木桩，身上又疼又酸。\n");
            message("vision", "只见" + me->query("name") + "从湖里湿漉漉爬上来，脸色苍白已极！\n", environment(me), me);
			return 1;
		}
	if (me->is_busy()) return notify_fail("你的动作还没有完成，不能移动。\n");
        if (me->query("jing") < 0)
        {
                me->set("jing",0);
                return notify_fail("你的精不足！不能再走了！\n");
        }
        if (me->query("neili") < 0)
        {
                me->set("neili",0);
                return notify_fail("你的内力不足！不能再走了！\n");
        }
		me->receive_damage("jing", random(50), "淹死了");
		me->add("neili", (-1)*random(50));
        message_vision("$N脚踩八卦方位，走得飞快。\n", me);
        me->start_busy(1);
        if ( me->query("combat_exp") >= me->query_skill("dodge", 1) * me->query_skill("dodge", 1) * me->query_skill("dodge", 1) / 10 )
        me->improve_skill("dodge", me->query("int") + me->query("kar"));
		return 1;
	}
	else
	{
		if ( (int)me->query_skill("dodge", 1) >= 120)
		{
			if ( arg == "yanziwu" )
			{
				me ->move("/d/murong/ybank");
				tell_object(me, "\n你健步如飞，不一会就走到燕子坞...\n\n" ) ;
				return 1 ;
			}
			else if ( arg == "tingxiang" )
			{
				me ->move("/d/murong/tbank");
				tell_object(me, "\n你健步如飞，不一会就走到听香水榭...\n\n" ) ;
				return 1;
			 }
			 else
			 {
				return notify_fail ("不要乱跑！\n");
			 }
		 }
		else if ( (int)me->query_skill("dodge", 1) < 120)
		{
				return notify_fail ("不要乱跑！\n");
		}
	}
}
