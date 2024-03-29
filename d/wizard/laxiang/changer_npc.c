#include <ansi.h>
inherit NPC;
void create()
{
	set_name("玄总大师",({"changer npc"}));
	set("long",0);
	set("title","[1;31m天下第一镖[2;37;0m");
	set("age",120);
	set("str",31);
	set("con",36);
	set("int",28);
	set("spi",5);
	set("per",39);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname",0);
	set("combat_exp",100562131);
	set("max_qi",11443);
	set("max_jing",16152);
	set("gender","男性");
	set("max_neili",12760);
	set("max_jingli",9169);
	set("jiali",0);
	set("race","人类");
	set("class","bonze");
	set("repute",3410987);
	set("score",0);
	set("family/family_name","少林派");
	set_skill("buddhism",858);
	set_skill("yizhi-chan",992);
	set_skill("yunlong-shenfa",809);
	set_skill("zui-gun",710);
	set_skill("dodge",807);
	set_skill("yunlong-bian",981);
	set_skill("whip",980);
	set_skill("parry",834);
	set_skill("sword",951);
	set_skill("hunyuan-yiqi",337);
	set_skill("staff",709);
	set_skill("hand",713);
	set_skill("yunlong-shengong",812);
	set_skill("literate",550);
	set_skill("hujia-daofa",903);
	set_skill("yunlong-shou",713);
	set_skill("claw",981);
	set_skill("blade",762);
	set_skill("yunlong-zhua",981);
	set_skill("riyue-bian",726);
	set_skill("yunlong-jian",952);
	set_skill("force",805);
	set_skill("finger",992);
	map_skill("dodge","yunlong-shenfa");
	map_skill("whip","yunlong-bian");
	map_skill("parry","hujia-daofa");
	map_skill("sword","yunlong-jian");
	map_skill("staff","zui-gun");
	map_skill("hand","yunlong-shou");
	map_skill("claw","yunlong-zhua");
	map_skill("blade","hujia-daofa");
	map_skill("force","yunlong-shengong");
	map_skill("finger","yizhi-chan");
	setup();
}
