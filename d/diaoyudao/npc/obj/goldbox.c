
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
        set("long", "这是一口很大的木头箱子，看样子里面装着不少好东西，但外面有一把大铁锁。\n");
        set("value", 10000000);
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

/*
    ob= new("/d/diaoyudao/npc/obj/ruanjia.c");
   ob->move(this_object());
    ob = new("/d/diaoyudao/npc/obj/wdagger.c");
   ob->move(this_object());
*/
    add_action("do_unlock","unlock");
	add_action("do_put", "put");
    add_action("do_get","get");
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

    if ( objectp(wolf = present("wolf", environment())) )
    {
        message_vision("$N对着$n大喝一声：“干什么？想偷我的宝贝？八格牙路！”\n", wolf, me);
        wolf->kill_ob(me);
        me->kill_ob(wolf);
        return 1;
    }
    if (ob->query_temp("marks/开"))
        return notify_fail("箱子不是已经打开了吗？\n");
    if ( !objectp(key = present("key", me)) )
        return notify_fail("有没有搞错，你好象没有钥匙耶！\n");
    if (me->query("str") <30)
    {
        key->set_name("断掉的钥匙", ({ "broken key" }) );
        key->set("value", 0);
          return notify_fail("只听钥匙啪的一声就断了.\n");
    }
    write("只听~~嘎吱~~一声，大箱子的盖打开了，无数珍宝发出的光芒晃得你连眼睛都睁不开了。\n");
    me->set_busy(3);
    ob->set_temp("marks/开", 1);
    ob->set("long", "这是一个打开的大箱子，里面放着很多珠宝。\n");
    obj = new("/d/diaoyudao/npc/obj/wdagger.c");
    obj->move(ob);
    obj = new("/d/diaoyudao/npc/obj/ruanjia.c");
    obj->move(ob);
//  obj =new("/d/diaoyudao/npc/obj/zhenzhu.c");
//  obj->move(ob);
    return 1;
}
