#include <ansi.h>
inherit "/clone/stdpet/pet.c";
void create()
{
	set("race","野兽");
	set_name(COLOR+"PET_NAME"+NOR,({"PET_ID"}));
	set("unit","只");
	set("age",1);
	set("combat_exp",1);
	set("birthday",time());
	set("long","这是一条刚出生不久的小狗。\n");
	set("limbs",({"头部", "身体", "前脚", "後脚", "尾巴" }) );
	set("verbs", ({ "bite", "claw", "hoof" }) );
	set("attitude","peaceful");
	set_leader(find_player("PET_OWNER"));
	set("msg_lost","$N好象找不到它的主人了，一副好可怜的样子。\n");
	set("msg_meet","$N高兴地跳到了"+query_leader()->query("name")+"的怀里，「喵喵」地叫了几声。\n");
	set("msg_come", "$N跑了过来。\n");
	set("msg_leave", "$N向$E离开。\n");
	setup();
}