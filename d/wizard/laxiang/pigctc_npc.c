#include <ansi.h>
inherit NPC;
void create()
{
	set_name("菜单Ｃ",({"pigctc npc"}));
	set("long",0);
	set("title","[32m朝廷四品官员 [2;37;0m[34m前锋营骑都尉[2;37;0m");
	set("age",153);
	set("str",26);
	set("con",25);
	set("int",40);
	set("spi",10);
	set("per",38);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;36m水　[1;37m云　[1;32m间　[1;31m[1;5m守护神　[2;37;0m[1;36m东方之神[2;37;0m—[1;36m青龙[2;37;0m[2;37;0m");
	set("combat_exp",115201041);
	set("max_qi",11696);
	set("max_jing",8633);
	set("gender","男性");
	set("max_neili",12450);
	set("max_jingli",11655);
	set("jiali",0);
	set("race","人类");
	set("class","officer");
	set("repute",1360179);
	set("score",1400);
	set("family/family_name","朝廷");
	set_skill("kuihua-zhua",835);
	set_skill("medical-skill",834);
	set_skill("xiake-shengong",186);
	set_skill("bixue-xinfa",389);
	set_skill("kuangfeng-dao",835);
	set_skill("fanwen",121);
	set_skill("kuangfeng-jian",835);
	set_skill("staff",734);
	set_skill("blade",836);
	set_skill("juemen-gun",835);
	set_skill("xiake-strike",190);
	set_skill("xiake-quanjiao",191);
	set_skill("strategy",201);
	set_skill("dodge",836);
	set_skill("literate",834);
	set_skill("strike",51);
	set_skill("sword",836);
	set_skill("leadership",201);
	set_skill("iron-cloth",834);
	set_skill("juehu-zhang",1);
	set_skill("parry",876);
	set_skill("qishang-quan",401);
	set_skill("training",11);
	set_skill("unarmed",65);
	set_skill("hujia-daofa",835);
	set_skill("yijin-jing",775);
	set_skill("xiake-jianfa",155);
	set_skill("xiake-daofa",155);
	set_skill("huzhua-shou",1);
	set_skill("hand",51);
	set_skill("force",834);
	set_skill("claw",545);
	set_skill("buddhism",151);
	map_skill("staff","juemen-gun");
	map_skill("blade","kuangfeng-dao");
	map_skill("dodge","juemen-gun");
	map_skill("strike","juehu-zhang");
	map_skill("sword","kuangfeng-jian");
	map_skill("parry","kuangfeng-dao");
	map_skill("unarmed","xiake-quanjiao");
	map_skill("hand","huzhua-shou");
	map_skill("force","yijin-jing");
	map_skill("claw","kuihua-zhua");
	setup();
}
