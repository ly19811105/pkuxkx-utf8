inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>
 
void create()
{
        set_name(BLU "归魂秘籍" NOR, ({ "miji","guihun" }));
        set_weight(900);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
             set("long",
                "薄薄的一本书，看起来没什么特别的。\n",

        );      set("no_drop",RED "楚帮主给你的这本秘籍乃是当世之宝，你怎么可以随便丢弃!\n" NOR);
                set("no_give",YEL "楚帮主给你的这本秘籍乃是当世之宝，你怎么可以随便给别人!\n" NOR);
                set("no_get",1);
                set("value", 0);
                set("material", "silk");
                set("skill", ([
                        "name":       "guihun-jian",
		        "exp_required":1000000,
                        "jing_cost":  80,
                        "difficulty": 30,
                        "max_skill":  250
                ]) );
        }
}
