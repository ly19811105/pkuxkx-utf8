// item: /d/xingxiu/npc/obj/fire.c

// Yom 24/12/03
#include <ansi.h>
inherit ITEM;
void setup()
{}

void init()
{
    add_action("do_pick","pick");
}

void create()
{ 
                
       set_name(HIG"大榕树"NOR,({"rong shu","tree"}))
;
        set_weight(9999999);
        set("no_get",1);
        set_max_encumbrance(0);
        if (clonep())
                set_default_object(__FILE__);
        else {
             set("unit","棵");
           set("long",RED"这是一棵大榕树，已有千年的树龄。据说树上挂着许多神仙的礼物。\n不想摘(pick)个看看吗？\n"NOR);
                                                  
        }
        
}

int do_pick(string arg)
{
        object p;
     object me= this_player();
/*

     if (arg == "da baitu")
     {
         p = new("/clone/gift/dabaitu.c");
         message_vision("$N从礼品树上摘下一" + p->query("unit") + p->query("name")+"。\n" + NOR,me);
	     p->move(me);
	     return 1;
	 }
*/
/*
       if (arg == "zong zi") {
        p = new("/clone/gift/zong0755.c");
         message_vision("$N从礼品树上摘下一" + p->query("unit") + p->query("name")+"。\n" + NOR,me);
	     p->move(me);
	     return 1;
	}     	
*/
     if (me->query("chris/got"))
     {
        tell_object(me,"你已经得到一个礼物啦！给别人留个机会嘛! \n");
        return 1;
     }
    p = new("/clone/gift/giftguo.c");
     p->move(me);
    message_vision(HIM"$N从大榕树上摘下一颗$n"HIM"。\n"NOR, me, p);
     me->set("chris/got",1);
     return 1;
}

