// 蛤蟆
// created by zine 2 Sep 2010

inherit "/d/xingxiu/npc/wudu2.c";
#include <ansi.h>

void create()
{
	set_name(BLU"幽冥蛤蟆"NOR, ({ "youming hama", "hama", "toad" }) );
	set("race", "野兽");
	set("age", random(2));
	set("long", "一条蓝幽幽的大蛤蟆，腹部一涨一涨的。\n");
	set("max_qi", 1000);
	set("qi", 1000);
	set("str", 10);
	set("con", 1);
	set("dex", 1);
	set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );
	set("combat_exp", 10000);
    
	setup();
}
