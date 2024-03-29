#include <ansi.h>
inherit NPC;
void create()
{
	set_name("一过",({"yiguo npc"}));
	set("long",0);
	set("title","[32m朝廷一品官员 [2;37;0m[1;33m辅国公[2;37;0m");
	set("age",99);
	set("str",38);
	set("con",27);
	set("int",28);
	set("spi",6);
	set("per",35);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname",0);
	set("combat_exp",100289453);
	set("max_qi",10023);
	set("max_jing",5733);
	set("gender","男性");
	set("max_neili",13478);
	set("max_jingli",6940);
	set("jiali",0);
	set("race","人类");
	set("class","officer");
	set("repute",829313);
	set("score",1410);
	set("family/family_name","朝廷");
	set_skill("literate",775);
	set_skill("strategy",359);
	set_skill("buddhism",150);
	set_skill("qishang-quan",400);
	set_skill("sword",716);
	set_skill("fanwen",100);
	set_skill("blade",901);
	set_skill("kuihua-zhua",950);
	set_skill("hujia-daofa",994);
	set_skill("kuangfeng-jian",820);
	set_skill("taoism",1);
	set_skill("force",870);
	set_skill("claw",949);
	set_skill("medical-skill",710);
	set_skill("parry",989);
	set_skill("bixue-xinfa",874);
	set_skill("unarmed",51);
	set_skill("kuangfeng-dao",871);
	set_skill("staff",965);
	set_skill("leadership",358);
	set_skill("juemen-gun",981);
	set_skill("dodge",951);
	set_skill("yijin-jing",309);
	set_skill("xiake-quanjiao",200);
	map_skill("sword","kuangfeng-jian");
	map_skill("blade","hujia-daofa");
	map_skill("force","bixue-xinfa");
	map_skill("claw","kuihua-zhua");
	map_skill("parry","hujia-daofa");
	map_skill("unarmed","xiake-quanjiao");
	map_skill("staff","juemen-gun");
	map_skill("dodge","juemen-gun");
	setup();
}
