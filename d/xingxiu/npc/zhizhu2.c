// 蜘蛛
// created by zine 2 Sep 2010

inherit "/d/xingxiu/npc/wudu2.c";
#include <ansi.h>

void create()
{
	set_name(WHT"雪蜘蛛"NOR, ({ "xue zhizhu","zhizhu", "spider" }) );
	set("race", "野兽");
	set("age", random(2));
	set("long", "一只雪白色的大蜘蛛，其毒无比。\n");
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
