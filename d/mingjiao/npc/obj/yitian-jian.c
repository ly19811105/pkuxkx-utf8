// yitian-jian 倚天剑

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name("倚天剑",({ "yitian jian", "yitian", "sword", "jian" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("value", 10000);
                set("material", "steel");
                set("no_drop", "1");
                set("long", "这是一柄四尺来长的古剑，剑鞘上金丝镶着两个字“倚天”。\n"
                        "整个剑身隐隐发出一层青气，剑未出鞘，已可见其不凡。\n");
                set("wield_msg", HIY "$N“唰”的一声抽出$n挽了个剑花，只觉淡淡清香，\n"
                        "剑色淡黄，这把倚天剑竟是檀香木所制。$N一时不知所措。\n"NOR);
                set("unwield_msg", HIY "$N将木剑还入剑鞘。\n" NOR);
        }
        init_sword(50);
        setup();
}
