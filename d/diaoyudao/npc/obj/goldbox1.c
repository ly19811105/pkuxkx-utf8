
#include <ansi.h>

inherit ITEM;

void create()
{
     set_name("聚宝箱", ({ "jubao xiang", "xiang" ,"box" }));
   set_weight(10000);
	set_max_encumbrance(5000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "个");
    set("long","这是一个纯金的箱子,箱子里应该有不少好东西.但箱子上好象上了锁,不能打开.\n");
       set("value",10000000);
       set("material","gold");
		set("no_get",1);
		set("no_drop",1);
    carry_object(__DIR__"obj/zhenzhu");
    set_temp("marks/开",0);
	}
	setup();
}

int is_container() { return 1; }

void init()
{
	object ob;
	object me = this_player();

    ob= new("/d/diaoyudao/npc/obj/ruanjia.c");
   ob->move(this_object());
    ob = new("/d/diaoyudao/npc/obj/wdagger.c");
   ob->move(this_object());
    add_action("do_unlock","unlock");
	add_action("do_put", "put");
}

int do_put(string arg)
{
    object me,obj,ob;
	string item, target; 
	int amount;

	me = this_player();
   ob= this_object();
   if (!ob->query_temp("mark/开"))
    {
          write("箱子显然没有打开,你怎么放呀!\n");
         return 1;
    }
	if(!arg) return notify_fail("你要将什么东西放进哪里？\n");

	if( sscanf(arg, "%s in %s", item, target)!=2 
	||  sscanf(item, "%d %s", amount, item)!=2
	||  !objectp(obj = present(item, me)) )

	return notify_fail("你要给谁什么东西？\n");


   return 0;
}
int do_unlock()
{
      object me,obj,ob;
      me= this_player();
      ob= this_object();
      if ( ! present("key",me))
          return notify_fail("有没有搞错,你好象没有钥匙耶!\n");
      if ( me->query("str") < 30 )
          return notify_fail("只听钥匙啪的一声就断了.\n");
      write("只听~~嘎吱~~一声, 聚宝箱的盖打开了, 你的眼睛立刻被无数珍宝的光芒晃的睁不开了.\n");
      me->set_busy(3);
      ob->set_temp("mark/开",1);
}
