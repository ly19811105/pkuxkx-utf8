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
                
       set_name(HIG"圣诞树"NOR,({"gift tree","tree"}));
        set_weight(9999999);
           set("no_get",1);
        set_max_encumbrance(0);
        if (clonep())
                set_default_object(__FILE__);
        else {
             set("unit","棵");
           set("long",RED"这是一棵五彩缤纷的圣诞树,上面悬挂着许多礼物.\n 不想摘(pick)个看看吗？\n"NOR);
                                                  
        }
        
}

int do_pick(string arg)
{
        object p;
     object me= this_player();

     if (me->query("chris/got"))
     {
        tell_object(me,"你已经得到一个礼物啦！给别人留个机会嘛! \n");
        return 1;
     }
      p = new("/clone/gift/sdgift03-yom.c");
     p->move(me);
     me->set("chris/got",1);
     return 1;
}

