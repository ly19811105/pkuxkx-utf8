
#include <weapon.h>
inherit SWORD;
#include <ansi.h>
#include <yugan.h>

void create()
{
        set_name("钓竿", ({ "diao gan","yu gan","gan" }) );
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("assist_fishing",120);//帮助钓鱼，越高越好，0-150
                set("long", "这是一柄钓鱼竿，上面的鱼钩却是直的。\n");
                set("value", 0);
                set("material", "steel");
                
        }
        init_sword(1);
        setup();
}

