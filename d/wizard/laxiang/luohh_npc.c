#include <ansi.h>
inherit NPC;
void create()
{
	set_name("渡门",({"luohh npc"}));
	set("long","luohh
[2;37;0m");
	set("title","[1;31m天下第一镖[2;37;0m");
	set("age",158);
	set("str",38);
	set("con",32);
	set("int",33);
	set("spi",10);
	set("per",38);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;32m推车[1;31m修禅[2;37;0m[2;37;0m");
	set("combat_exp",109486406);
	set("max_qi",12540);
	set("max_jing",29273);
	set("gender","男性");
	set("max_neili",15249);
	set("max_jingli",14202);
	set("jiali",0);
	set("race","人类");
	set("class","bonze");
	set("repute",14114690);
	set("score",500);
	set("family/family_name","少林派");
	set_skill("jingang-buhuai",498);
	set_skill("zui-gun",1031);
	set_skill("hunyuan-yiqi",502);
	set_skill("staff",1031);
	set_skill("shaolin-shenfa",1031);
	set_skill("unarmed",510);
	set_skill("cuff",961);
	set_skill("yizhi-chan",1031);
	set_skill("blade",579);
	set_skill("fumo-jian",579);
	set_skill("cibei-dao",579);
	set_skill("yijin-jing",986);
	set_skill("buddhism",1314);
	set_skill("iron-cloth",890);
	set_skill("nianhua-zhi",299);
	set_skill("sword",579);
	set_skill("dodge",1031);
	set_skill("fanwen",324);
	set_skill("hujia-daofa",200);
	set_skill("daweituo-chu",1031);
	set_skill("force",1021);
	set_skill("whip",579);
	set_skill("luohan-quan",961);
	set_skill("literate",907);
	set_skill("medical-skill",907);
	set_skill("jinshe-jian",49);
	set_skill("parry",1031);
	set_skill("qishang-quan",390);
	set_skill("finger",1031);
	map_skill("staff","daweituo-chu");
	map_skill("cuff","luohan-quan");
	map_skill("blade","cibei-dao");
	map_skill("iron-cloth","jingang-buhuai");
	map_skill("sword","fumo-jian");
	map_skill("dodge","shaolin-shenfa");
	map_skill("force","yijin-jing");
	map_skill("parry","daweituo-chu");
	map_skill("finger","yizhi-chan");
	setup();
}
