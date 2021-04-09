#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL"巨岩"NOR, ({ "ju yan", "yan shi", "rock" }) );
        set_weight(3000);
        set("unit", "块");
        set("long", "这是一块巨大的岩石。\n");
        
        set("value", 1000);
        set("material", "stone");
        set("no_get",1);
        set("no_drop",1);
               
        setup();
}

void init()
{
    add_action("do_mosuo", "mosuo");
}

int do_mosuo()
{
    object me=this_player();
    if (me->is_busy() || me->is_fighting())
    {
        tell_object(me,"你正忙着呢！\n");
        return 1;
    }
    message_vision("$N用指尖在岩缝之间摸索。\n",me);
    if (!me->query("exp_dep"))
    {
        message_vision("$N却什么也未曾发现。\n",me);
        return 1;
    }
    else
    {
        tell_object(me,"岩缝中摆着一张小纸条，纸条上写着："+"/cmds/usr/hp.c"->get_separator(me->query("exp_dep"),COLOR_D->uncolor(me->query("name"))+"的修行经验")+NOR);
        return 1;
    }
}