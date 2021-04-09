// Created by iszt@pkuxkx, 2007-03-03

#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(MAG"雪梅"NOR, ({"xue mei", "mei", "plum"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", "这是一朵生长在雪峰峰顶的雪梅，服食之对人体大有助益。\n");
                set("value", 100);
        }
        setup();
}

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object me = this_player();

        if (!id(arg))
                return notify_fail("你要吃什么？\n");
        if(!present(this_object(), this_player()))
                return notify_fail("你身上没有这样东西。\n");
        if(environment(me)->query("outdoors") == "凌霄城")
                return notify_fail("这里冰天雪地的，还是下山再吃东西罢。\n");
        if ( me->query_skill_mapped("force") != "xueshan-neigong" )
        {
                me->add("max_neili", -10);
                message_vision(HIR "$N服下一朵"NOR+name()+HIG"，突然觉得周身冰凉，如坠冰窟，反而大损真元！\n" NOR, me);
                me->unconcious();
                destruct(this_object());
                return 1;
        }

        me->add("max_neili", 5+random(6));
        message_vision(HIG "$N服下一朵"NOR+name()+HIG"，只觉得内力又增长了一分！\n" NOR, me);

        destruct(this_object());
        return 1;
}
