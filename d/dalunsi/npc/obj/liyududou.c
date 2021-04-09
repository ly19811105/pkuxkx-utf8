#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(RED"鲤鱼肚兜"NOR, ({ "liyu dudou", "dudou" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是一件红色的肚兜，上面用金线绣着一条栩栩如生的大鲤鱼。\n");
                set("unit", "件");
                set("value", 600);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/personality", 3);
                set("female_only", 1);
        }
        setup();
}

