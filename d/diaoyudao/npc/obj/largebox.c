// largebox.c 大箱子
// hongdou 98.10.10

#include <ansi.h>

inherit ITEM;

void create()
{
    	set_name("大箱子", ({ "large box", "xiang", "box" }) );
     	set_weight(10000);
	set_max_encumbrance(5000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
        set("unit", "口");
        set("long", "这是一口沉重的大箱子，看样子里面装着不少好东西，
外面有一把大铁锁，已经生了锈。\n");
        set("value", 1);
        set("material", "wood");
		set("no_get",1);
		set("no_drop",1);
	}
	setup();
}

int is_container()
{
    return query_temp("marks/开");
}

void init()
{
	object ob;
	object me = this_player();

    	add_action("do_unlock","unlock");
	add_action("do_put", "put");
    	add_action("do_get","get");
	add_action("do_move","move");
}

int do_put(string arg)
{
    	object me,obj,ob;
	string item, target; 
	int amount;

	me = this_player();
    	ob = this_object();
	if(!arg) return notify_fail("你要将什么东西放进哪里？\n");

	if( sscanf(arg, "%s in %s", item, target)!=2 
	||  sscanf(item, "%d %s", amount, item)!=2
	||  !objectp(obj = present(item, me)) )
		return notify_fail("你要给谁什么东西？\n");
    if (((target=="box")||(target=="xiang"))&&(!ob->query_temp("marks/开")))
    {
        write("箱子上着锁，你怎么放呀？\n");
        return 1;
    }
    return 0;
}

int do_get( string arg)
{
    object me, ob;
    string item, target;
    ob= this_object();
    if (!arg) return 0;
    if ( sscanf(arg, "%s from %s", item ,target)!= 2)
      return 0;
    if (((target== "box") || (target=="xiang")) && (!ob->query_temp("marks/开")))
      {
        write("箱子没开你怎么拿呀？\n");
 	   return 1;
      }
      return 0;
}

int do_unlock()
{
    object me, obj, ob, key;
    me= this_player();
    ob= this_object();

    if (ob->query_temp("marks/开"))
        return notify_fail("箱子不是已经打开了吗？\n");
    if ( !objectp(key = present("iron key", me)) )
        return notify_fail("有没有搞错，你好象没有这个箱子的钥匙耶！\n");
        if (me->query_str() <30) 
	return notify_fail("由于箱子上的铁锁锈得太厉害，你没有将它打开。\n");
    key->set_name("断掉的钥匙", ({ "broken key" }) );
    key->set("value", 0);
    message_vision("$N猛力地一拧钥匙，啪的一声铁锁打开了，随即铁钥匙断成了两截。\n",me);
    
    write("\n只听~~嘎吱~~一声，大箱子的盖打开了......\n");
    me->set_busy(3);
    ob->set_temp("marks/开", 1);
    ob->set("long", "这是一个打开的大箱子，里面的东西，箱子底有几样东西引起了你的注意。\n");
//    obj = new("/d/diaoyudao/npc/obj/wdagger.c");
//    obj->move(ob);
    obj = new("/d/diaoyudao/npc/obj/baojia.c");
    obj->move(ob);

    return 1;
}

int do_move(string arg)
{
    object me, ob,obj;
    ob= this_object(); 
    me= this_player();
    if(!id(arg)) return notify_fail("你要移动什么？\n");
    if (!(ob->query_temp("marks/开")))  return 0;
    if (ob->query_temp("经") || ( objectp(obj = present("42 jing1", me)) ))
         return notify_fail("你把箱子在洞里推来拉去，感到好玩吗？\n");
    if (me->query("str")>=35) 
    {
	if (me->query_temp("push")>=4)
	{
	    tell_object(me,"你移开了沉重的大箱子，发现底下有一个油纸包，里面有一本书。\n");
	    tell_object(me,HIY"\n你得到了一本经书。\n"NOR);
	    obj=new("/d/diaoyudao/npc/obj/jing42_1");
	    obj->move(me);
	    me->delete_temp("push");
	    ob->set_temp("经",1);
	    return 1;
	}
	me->add_temp("push",1);
	return notify_fail("你使劲推了推，箱子只微微晃动了一下。\n");
    }
    return notify_fail("你想尽办法要移动箱子，可是箱子偏偏不听你的话。\n");
}

