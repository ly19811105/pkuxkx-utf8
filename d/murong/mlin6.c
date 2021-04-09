//mlin6.c
//by hehe
//2003.3.5

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "茶花林");
    set("long", @LONG
你在花林中信步而行，所留神的只是茶花，忘了记忆路径，眼见小路东
一条、西一条，不知那一条才是来路，一眼望将出去，都是红白缤纷的
茶花，不见房屋。只见此处花草甚为凌乱，似有人挣扎而过。也许搜索
一下会有所发现。
LONG
    );

    set("exits", ([
		"north" : __FILE__,
		"east" : __DIR__"mlin5",
		"south" : __FILE__,
		"west" : __FILE__,
    ]));
    
    set("outdoors", "murong");
	set("number",1);
    setup();
}

void init()
{
	add_action("do_search","search");
}
int do_search()
{
	object me = this_player();
	object ob,obj; 
	int jing;    
	if( me->is_busy() )
	return notify_fail("你上一个动作还没有完成呢。\n");                       
	jing=me->query("jing");
	if(jing<30)                    
	return notify_fail("你无法集中精力找东西！\n");
	message_vision("$N开始在茶花丛中搜索，希望能发现点什么。\n",me);
	me->start_busy(2); 
	me->set("jing", jing-10); 
	call_out("end",3,me);
	return 1;
}  
                 
void end(object me)
{
	object tang;
	if (!me) return;
	if (query("number") == 0)
	{
		message_vision("$N累了个半死，结果什么都没有找到。\n",me);
		return;
	}
	switch(random(5))
	{
		case 0:
		case 1:  message_vision("$N发现了一只臭鞋套，闻了闻觉得不好，扔在了一边\n",me);
			break;
		case 2:
		case 4:  message_vision("$N累了个半死，结果什么都没有找到。\n",me);
			break;  
		case 3:  tang=new(__DIR__"npc/tang.c");
			message_vision("$N拨了拨浓密的茶花枝，忽忽然一个浑身是血的人滚了过来，吓了你一跳。\n",me);
			tang->move(environment(me));
			set("number",0);
			break;         
		default: message_vision("$N累了个半死，结果什么都没有找到。\n",me);
			break;
	}
}        
