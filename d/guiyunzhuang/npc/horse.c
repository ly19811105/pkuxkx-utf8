// item: horse.c
// pingpang
#include <armor.h>
inherit HORSE;
void setup()
{}

void init()
{
        add_action("do_ride", "ride");
}

void create()
{
        set_name("黑鬃马", ({"horse", "黑鬃马", "ma","heizong ma"}));
        set_weight(35000);
        set_max_encumbrance(50000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "匹");
                set("long", "一匹良种的黑鬃马，可以骑(ride)，也可以驮东西。\n");
                set("value", 3000);
		set("armor_prop/dodge",8);
        }
}

int do_ride(string arg)
{
	object me = this_player();
        if (!id(arg))
                return notify_fail("你要骑什么？\n");
        if (this_player()->query_temp("marks/骑") ) {
                       write("你已经骑在马上了。\n");
                        return 1;
        }
        else {
               message("vision",this_player()->name() + "翻身上马。\n",
                        environment(me), ({me}) );
               write("你很小心地爬上马背,往四下里瞅了瞅。\n");
                this_player()->set_temp("marks/骑", 1);
		return 1;
        }
}
