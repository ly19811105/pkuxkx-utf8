#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
	set_name(HIG"缎绿绸衫"NOR, ({"chou shan", "cloth", "shan"}) );
    set_weight(2500);
    if( clonep() )
       set_default_object(__FILE__);
    else {
        set("unit", "件");
		set("long", "一件缎绿色的绸衫。\n");
        set("material", "cloth");
        set("armor_prop/armor", 1);
		set("value",100);
    }
    setup();
}
