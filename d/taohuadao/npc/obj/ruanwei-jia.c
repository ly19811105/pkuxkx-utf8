//jia.c
#include <weapon.h>
#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
set_name("软猬甲",({"ruanwei jia","jia"}));
set_weight(2400);
if(clonep())
set_default_object(__FILE__);
else
{
set("long","此甲通体用刺猬皮织成，坚韧无比.\n");
set("material","cloth");
set("unit","件");
set("value",300000);
set("no_pawn",1);
set("no_sell",1);
set("sell_in_playershop",1);
set("wear_msg",HIY"刹那间，天云变色，$N被一片金光包了起来。\n"NOR);
set("remove_msg",HIY"$N将$n脱了下来，$N周身顿觉暗淡.\n"NOR);
set("armor_prop/armor",500);
setup();
}
}
