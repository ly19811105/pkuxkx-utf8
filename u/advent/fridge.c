//fridge.c 冰箱
//by zoom
//2003.5.12

#include <ansi.h>

inherit ITEM;

int open(string);
int pick(string);
int close(string);

void setup()
{}

void create()
{             
	set_name(HIG"新飞冰箱"NOR,({"xinfei fridge","fridge"}));
	set_weight(999999);
	set("no_get",1);
        set("value",1);
	set_max_encumbrance(999999);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("unit","台");
		set("long",HIG"一台冰箱，放在墙的角落里，时不时的发出一阵嗡嗡声。\n"NOR);
		set("tao_num",10);
		set("milk_num",10);
	}
        
}
void init()
{
	add_action("do_open","kai");
	add_action("do_close","guan");
	add_action("do_pick","pick");
}

int do_open(string arg)
{
	object me = this_player();
	object ob = this_object();
	if(!arg||arg=="")
	{
		write("你要干什么，不要乱动人家东西。\n");
		return 1;
	}
	else if(arg=="冰箱"||arg=="fridge"||arg=="xinfei fridge")
	{
		if(ob->query("opened"))
		{
			write("冰箱门开着呢，别费劲了。\n");
			return 1;
		}
		else
		{
			message_vision("$N小心的把冰箱门打开。\n",me);
			ob->set("opened",1);
			if(random(3)==0)
			{
				message_vision("$N一个不小心，头磕到冰箱门上，立时起了一个大包。\n",me);
				me->start_busy(10);
			}
			else
				me->start_busy(5);
			return 1;
		}
		return 1;
	}
	else
	{
		write("你要干什么，不要乱动人家东西。\n");
		return 1;
	}
return 1;
}

int do_close(string arg)
{
	object me = this_player();
	object ob = this_object();
	if(!arg||arg=="")
	{
		write("你要干什么，不要乱动人家东西。\n");
		return 1;
	}
	else if(arg=="冰箱"||arg=="fridge"||arg=="xinfei fridge")
	{
		if(!ob->query("opened"))
		{
			write("冰箱门关着呢，别费劲了。\n");
			return 1;
		}
		else
		{
			message_vision("$N小心的把冰箱门关上。\n",me);
			ob->set("opened",0);
			return 1;
		}
		return 1;
	}
	else
	{
		write("你要干什么，不要乱动人家东西。\n");
		return 1;
	}
return 1;
}

int do_pick(string arg)
{
	object me = this_player();
	object fridge = this_object();
	object food;
	if(!arg||arg==""||!fridge->query("opened"))
	{
		write("你要干什么，不要乱动人家东西。\n");
		return 1;
	}
	else if(me->is_busy())
	{
		write("你还忙着呢，等会在拿吧。\n");
	}
	else if(arg=="猕猴桃"||arg=="tao"||arg=="mihou tao")
	{
		if(fridge->query("tao_num")>=0)
		{
			food = new("/d/quanzhou/obj/tao.c");
			food->move(me);
			message_vision("$N鬼鬼祟祟的从冰箱拿出一个猕猴桃，放在怀里，又小心的把冰箱门关上。\n",me);
			fridge->add("tao_num",-1);
			fridge->set("opened",0);
			return 1;
		}
		else
		{
			write("冰箱里的猕猴桃都被拿光了。\n");
			return 1;
		}
	}
	else if(arg=="牛奶"||arg=="milk"||arg=="chun niunai")
	{
		if(fridge->query("milk_num")>=0)
		{
			food = new("/d/quanzhou/obj/milk.c");
			food->move(me);
			message_vision("$N鬼鬼祟祟的从冰箱拿出一瓶牛奶，放在怀里，又小心的把冰箱门关上。\n",me);
			fridge->add("milk_num",-1);
			fridge->set("opened",0);
			return 1;
		}
		else
		{
			write("冰箱里的牛奶都被拿光了。\n");
			return 1;
		}		
	}	
	else
	{
		write("冰箱里还有别的嘛，你看花眼了吧，想吃就放点进去好了。\n");
		return 1;
	}

return 1;
}
		
