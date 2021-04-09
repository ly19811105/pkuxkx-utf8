// poison_dust.c
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
       set_name("点燃的毒虫粉", ({ "duchong fen", "duchong", "fen" }) );
       set("long", "一包以蜈蚣、蜘蛛等为原料制成的毒粉。已经点燃，可以涂(tu)在兵器上了。\n" );
       set("unit", "些");
       set("base_unit", "包");
       set("base_weight", 30);
       set("drug_color", ""BLU"蓝光闪闪"NOR"");
       set("poison", "xx_poison");
       set_amount(1);
}

#include "yaoa.h";

