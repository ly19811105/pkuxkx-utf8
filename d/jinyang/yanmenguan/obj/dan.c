#include <ansi.h>
inherit ITEM;
void setup()
{}
void init()
{
        add_action("do_eat", "eat");
}
void create()
{
        set_name(HIG"百草丹"NOR, ({"baicao dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("long", "这是一颗用数百种药物精制而成的丹药，有神奇药效。\n");
                set("value", 5);
				set("yanmen_item",1);
        }
        setup();
}

int do_eat(string arg)
{
        int fw;
        object me = this_player();
	    if (!id(arg))  return notify_fail("你要吃什么？\n");
	    {
                fw = (int)me->max_food_capacity();
                me->set("food", fw);
                fw = (int)me->max_water_capacity();
                me->set("water", fw);
	 	        me->set("neili",me->query("max_neili")/10*(10+random(11)));
                message_vision(HIG"$N吃下一颗百草丹，顿时只觉丹田充满了内力！\n"NOR,me);
		        me->start_busy(1);
        	    destruct(this_object());
	    }
	    return 1;
}

