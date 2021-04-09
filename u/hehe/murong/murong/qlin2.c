//qlin2.c
//by hehe
//2003.3.14

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
小树林安静昏暗，经常有小动物出没，看来这里可以打些野味。
LONG
    );

    set("exits", ([
		"west" : __DIR__"qlin3",
		"south" : __DIR__"qlin1",
		"southwest" : __DIR__"qlin5",
    ]));
    
    set("outdoors", "murong");
    setup();

}
void init()
{
	add_action("do_search", "search");
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
	message_vision("$N开始在树林中搜索，希望能发现什么猎物。\n",me);
	me->start_busy(2); 
	me->set("jing", jing-10); 
	call_out("end",3,me);
	return 1;
}  
                 
void end(object me)
{
	object ob;

	switch(random(3))
	{
		case 0:
		case 1:  
			{
				message_vision("$N发现了一只臭鞋套，闻了闻觉得不好，扔在了一边\n",me);
				break;
			}
		case 2:  
			{
				ob=new(__DIR__"npc/yetu.c");
				message_vision("$N小心的在树林里搜寻，你看到前面树林中好像有个........\n",me);
				message_vision("$N慢慢地靠近，原来是一只兔子，还好还没有惊动它！\n",me);
				ob->move(environment(me));
				break;
			}
		default: 
			{
				message_vision("$N累了个半死，结果什么都没有找到。\n",me);
				break;
			}
	}
	return;
}        