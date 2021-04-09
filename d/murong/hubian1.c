//hubian1.c
//by hehe
//2003.3.20

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "湖边");
    set("long", @LONG
你走到湖边,前面豁然一个大湖泊(hu),水面光滑如镜,湖上停着艘小船(boat)，
船头坐着一位绿衣少女，正在唱着渔歌。湖边则杏花夹径,绿柳倒垂。暖洋洋的
春风吹在身上,当真是熏熏欲醉。
LONG
    );

    set("exits", ([
        "north" : "/d/suzhou/road4",
    ]));
	set("objects",([
		__DIR__"npc/girl" : 1,
        ]));
    set("couldfish",1);
	set("item_desc", ([
		"hu" :
"    湖面宽阔无比，一眼无边。远远望去，湖中种满了红菱白藕，
微风吹过，绿叶轻摇，煞是动人。藕菱之间，是一条条曲曲的水路，
不知道通向何处。
",
                     ]));

    set("outdoors", "murong");
    setup();

}
void init()
{
    add_action("do_find", "find");
    add_action("do_enter", "enter");
}

int do_find(string arg)
{
	object me;
	object *inv;
	int i;
	me = this_player();

        if (arg=="boat" && (me->query("family/family_name")=="姑苏慕容" || wizardp(me)))
	{

		inv=all_inventory(me);
		for(i=0; i<sizeof(inv); i++) {
			if (userp(inv[i]))
				return notify_fail("你负重太大了，小舟恐怕载不动你。\n");
		}
		tell_object(me, "你熟门熟路地找到一条小舟，解开绳子，划了起来。\n");
		tell_object(me, "不一会儿，你来到参合庄。\n");
		me->move("/d/murong/hubian2.c");
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
		message_vision("$N看清楚往哪里钻?\n",me);
		return 1;
	}
	if ( !(this_player()->query_temp("marks/拜庄")) ) {
		message_vision("$N没事不要乱往别人船上钻!\n",me);
		return 1;
	}
		inv=all_inventory(me);
		for(i=0; i<sizeof(inv); i++) {
			if (userp(inv[i]))
				return notify_fail("你负重太大了，小舟恐怕载不动你。\n");
		}
    message_vision("\n$N跃上小舟，船就划了起来。\n\n" ,me );
    me->move("/d/murong/dahu1") ;
    call_out("wait1", random(10) , me );

    return 1 ;
}

void wait1(object me)
{
	if (!me) return;
	tell_object(me, "\n............................\n" ) ;
	tell_object(me, "\n.......................\n" ) ;
	tell_object(me, "\n...................\n" ) ;
	tell_object(me, "\n..............\n" ) ;
	tell_object(me, "\n.....\n" ) ;
	me->move ("/d/murong/dahu2") ;
        call_out("wait2", random(10) , me);
}
void wait2(object me)
{
	if (!me) return;
	tell_object(me, "\n............................\n" ) ;
	tell_object(me, "\n.......................\n" ) ;
	tell_object(me, "\n...................\n" ) ;
	tell_object(me, "\n..............\n" ) ;
	tell_object(me, "\n.....\n" ) ;
	me->move ("/d/murong/dahu3") ;
        call_out("wait3", random(10) , me);
}
void wait3(object me)
{
	if (!me) return;
	tell_object(me, "\n............................\n" ) ;
	tell_object(me, "\n.......................\n" ) ;
	tell_object(me, "\n...................\n" ) ;
	tell_object(me, "\n..............\n" ) ;
	tell_object(me, "\n.....\n" ) ;
	me->move ("/d/murong/dahu4") ;
        call_out("wait4", random(10) , me);
}
void wait4(object me)
{
	if (!me) return;
	tell_object(me, "\n............................\n" ) ;
	tell_object(me, "\n.......................\n" ) ;
	tell_object(me, "\n...................\n" ) ;
	tell_object(me, "\n..............\n" ) ;
	tell_object(me, "\n.....\n" ) ;
	me->move ("/d/murong/hubian2") ;
	message_vision("绿衣少女将小船系在树枝之上，$N跨上岸去。\n",me);
	me->delete_temp("marks/拜庄");
}
