//  zanghonghua

#include <ansi.h>

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIR"藏红花"NOR, ({"zang honghua","zanghonghua","hua"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", "这是一朵生长在西藏高原上极其罕见的藏红花。\n"
                           "据说藏红花五年一开花，其花有起死回生的效果，。\n");
                set("value", 1000);
        }

        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if (!id(arg))
                return notify_fail("你要吃什么？\n");

      if (me->is_busy() || me->is_fighting())
        return notify_fail("你正忙着呢。\n");

        if ((int)me->query("eff_qi") ==
            (int)me->query("max_qi"))
                return notify_fail("你现在精神饱满，气血充盈，不需要用药物。\n");


        if (random(10) > 5) {
         me->add("max_neili",1+random(2));
        }
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("max_qi"));
        message_vision(HIW"$N服下藏红花，只觉遍体生凉，神清气爽，不但伤势大为好转，\n"+
                          "身体似乎也比以前强健许多。\n"NOR, this_player());       
        me->start_busy(1);
        destruct(this_object());
        return 1;
}
