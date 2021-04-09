#include <ansi.h>
inherit "/clone/stdpet/pet.c";
void create()
{
	set("race", "飞禽");
	set_name(COLOR+"PET_NAME"+NOR,({"PET_ID"}));
	set("unit", "只");
	set("age", 1);
	set("combat_exp", 1);
	set("birthday", time());
	set("long", "这是一只雄赳赳的小鹰。\n");
	set("limbs", ({ "头部", "身体", "脚", "左翅", "右翅", "尾巴" }) );
	set("verbs", ({ "claw", "poke", "sao" }) );
	set("attitude","peaceful");
	set_leader(find_player("PET_OWNER"));
	set("msg_lost", "$N好象找不到它的主人了，一副好可怜的样子。\n");
	set("msg_meet", "$N在空中盘旋几圈，落在" + query_leader()->query("name") + "的肩上。\n");
	set("msg_come", "$N飞了过来。\n");
	set("msg_leave", "$N向$E离开。\n");
	setup();
}