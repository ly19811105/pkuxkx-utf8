// 蝎子
// created by zine 2 Sep 2010

inherit "/d/xingxiu/npc/wudu.c";
#include <ansi.h>

void create()
{
	set_name("蝎子", ({ "xie zi", "scorpion" }) );
	set("race", "野兽");
	set("age", random(2));
	set("long", "一只毒蝎子，正张牙舞爪的看着你。\n");
	set("max_qi", 100);
	set("qi", 100);
	set("str", 10);
	set("con", 1);
	set("dex", 1);
	set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );
	set("combat_exp", 1000);
	
	setup();
}
