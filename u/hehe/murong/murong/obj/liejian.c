//liejian.c
//by hehe
//2003.3.22

inherit ITEM;
#include <ansi.h>

void create()
{
	set_name("翎箭", ({"ling jian","jian"}));
    set_weight(100);
    if( clonep() )
		set_default_object(__FILE__);
    else 
	{
		set("unit", "枝");
		set("value", 20);
        set("long","这是个做工粗糙的翎箭。\n");
        set("material", "steel");
    }
}
void init()
{
	add_action("do_gua","gua");
	add_action("do_aim","aim");
	add_action("do_shoot","shoot");
}

int do_gua(string arg)
{
	object me;
	me=this_player();
	if(!(present("liegong",me)))
	{
		tell_object(me,"你没有猎弓啊，搞什么鬼啊！\n");
		return 1;
	}
	if(!arg)
	{
		tell_object(me,"你要挂什么？\n");
		return 1;
	}
	if((string)arg!="jian")
	{
		tell_object(me,"你要挂什么?\n");
		return 1;
	}
	if(!(present("liegong",me)))
	{
		tell_object(me,"你没有弓箭也想打猎，搞笑啊！\n");
		return 1;
	}
	if(me->query_temp("murong/jian"))
	{
		tell_object(me,"你的猎弓上已经有了一枝翎箭了，不能再挂了！\n");
		return 1;
	}
	tell_object(me,"你小心的把翎箭挂到猎弓上。");
	me->set_temp("murong/jian",1);
	return 1;
}
int do_aim(string arg)
{
	object obj,me;
	me=this_player();
	
	if(!(present("liegong",me)))
	{
		tell_object(me,"你没有弓箭也想打猎，搞笑啊！\n");
		return 1;
	}
	if(!(me->query_temp("murong/jian")))
		return notify_fail("你还没把翎箭放到猎弓上哪！\n");
	if (me->is_busy())
		return notify_fail("你正忙着呢！\n");
	if( !arg )
		return notify_fail("乱瞄什么，你以为好玩啊？\n");
	if(!objectp(obj = present(arg, environment(me))))
		return notify_fail("这里没有这种猎物。\n");
	if(obj->query_temp("murong/shoot")!=1)
		return notify_fail("好像你瞄准的那家伙不是个猎物啊！\n");
	if( obj==me )
		return notify_fail("瞄谁不好，瞄自己？\n");
	message_vision(HIY "\n$N拉开弓箭，远远地瞄准$n，屏住呼吸，一动不动...\n\n" NOR, 
			me, obj);
	this_object()->set_temp("target", arg);
	me->set_temp("murong/aim",1);
	return 1;
}

int do_shoot()
{
	object me, ob,obj;
	string arg;
	me = this_player();
	ob = this_object();
	arg=ob->query_temp("target");
	obj=present(arg,environment(me));
	if(!arg) 
		return notify_fail("你还没有瞄准你的射击目标！\n");
	if(obj->query_temp("murong/shoot")!=1)
		return notify_fail("感觉你瞄准的这家伙不是个猎物啊！\n");
	if( !objectp(obj))
		return notify_fail("你要射杀的对象已经离开了。\n");
	message_vision(HIR "\n$N对准$n松开了手中的弓箭，翎箭激射而出....\n\n" NOR,
			me, obj);
	switch(random(2))
	{
	case 0 : 
		{
			message_vision(HIR "\n只听“吱”的一声惨叫，$n倒在血泊之中，$N真残忍啊！\n\n" NOR,me, obj);
			message_vision(HIG"$N捡起一块兔肉！\n"NOR,me,obj);
			destruct(obj);
			call_out("reward",0,me);
			break;
		}
	case 1 :
		{
			message_vision(HIY"$N的运气太差了，弓箭与$n擦边而过!$n警觉到了危险，跑掉了！\n"NOR,me,obj);
			me->set_temp("murong/jian",0);
			me->delete_temp("murong/jian");
			destruct(ob);
			destruct(obj);
			break;
		}
	default :
			message_vision(HIB"$N发射的弓箭卡住了，没射出去！！！！\n"NOR,me,obj);
	}
	return 1;
}

int reward(object me)
{
	object ob,obj;
	ob=this_object();
	obj=new("/d/murong/npc/turou.c");
	obj->move(me);
	me->set_temp("murong/jian",0);
	me->delete_temp("murong/jian");
	if((me->query("combat_exp"))<10000)
	{
		int a=20+random(20);
		int b=a/10;
		me->add("combat_exp",a);
		me->add("potential",b);
		me->add("jing",-b);
		me->improve_skill("blade",a);
		printf("你的经验增加了%d点\n",a);
		printf("你的潜能增加了%d点\n",b);
	}
	else if((me->query("combat_exp"))<100000)
	{
		int a=50+random(50);
		int b=a/10;
		me->add("combat_exp",a);
		me->add("potential",b);
		me->add("jing",-10);
		me->improve_skill("blade",a);
		printf("你的经验增加了%d点\n",a);
		printf("你的潜能增加了%d点\n",b);
	}
	else if((me->query("combat_exp"))<500000)
	{
		int a=100+random(100);
		int b=a/10;
		me->add("combat_exp",a);
		me->add("potential",b);
		me->add("jing",-10);
		me->improve_skill("blade",a);
		printf("你的经验增加了%d点\n",a);
		printf("你的潜能增加了%d点\n",b);
	}
	else if((me->query("combat_exp"))<1000000)
	{
		int a=200+random(150);
		int b=a/10;
		me->add("combat_exp",a);
		me->add("potential",b);
		me->add("jing",-10);
		me->improve_skill("blade",a);
		printf("你的经验增加了%d点\n",a);
		printf("你的潜能增加了%d点\n",b);
	}
	else
	{
		tell_object(me,"你该出去闯荡了！,不用沉湎于打猎了\n");
	}

	destruct(ob);
	return 1;
}



