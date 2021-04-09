#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIM"神机营大门"NOR);
	set("long",
HIC"这里是京城三大禁卫军之一的神机营所在，其作战原则
是“神机铳居前，马队居后”，配合步兵、骑兵作战，战争中
发挥了重要作用。此处大门紧闭，不知道能不能翻(jump)过去。\n"NOR
	);

	set("exits", ([
		"east" : __DIR__"houyuan",
		"west": __DIR__"shenji-guangchang",
	]));

	setup();
}

void init()
{
	add_action("do_fan", "jump");
}

int do_fan(string arg)
{
	object me, here, killer, *ob;
	int i, flag;
	
	me = this_player();
	here = this_object();
	
	if(!arg || (arg != "gate" && arg != "门"))
	{
		tell_object(me, "你要翻什么？\n");
		return 1;
	}
	
	if(me->query_skill("dodge") < 300)
	{
		tell_object(me, "你轻功不到家，看来这道门对你来说很有难度！\n");
		return 1;
	}	
	
	ob = all_inventory(me);
	for(i = 0; i < sizeof(ob); i++)
	{
		if(userp(ob[i]))
		{
			tell_object(me, "你背着别人哪里还有气力翻门啊！\n");
			return 1;
		}	
	}
	
	flag = here->query("playing");
	
	if(flag)
		{
			tell_object(me, "神机营内守卫森严，还是稍等一会儿再进去吧！\n");
			return 1;
		}

	message_vision("$N运起轻功翻身越过了神机营大门!\n", me);	
	killer = new(__DIR__"npc/killer.c");
	killer->move(__DIR__"room33.c");
//	killer = new(__DIR__"npc/killer.c");
//	killer->move(__DIR__"room03.c");
	
	me->move(__DIR__"room00.c");
	tell_object(me, "你突然感到周围有点不对劲，好像走错了地方!\n");

	here->set("playing", 1);
			
	return 1;
}

int valid_leave(object me, string dir)
{
	object *ob;
	int i, flag;
	  
  if(dir == "west" && me->query("class") != "eunuch" && !wizardp(me)) 
  return notify_fail("你并非东厂中人，直接进出，恐怕过于危险。\n");
  
	ob = all_inventory(me);
	for(i = 0; i < sizeof(ob); i++)
	{
		if(userp(ob[i]))
			{
				flag = 1;
				break;
			}
	}
	if(dir == "west" && flag && !wizardp(me))
		return notify_fail("先把你身上的人放下来再说吧！\n");
		   
   return ::valid_leave(me, dir);
}  
