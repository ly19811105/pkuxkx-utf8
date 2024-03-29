#include <ansi.h>
inherit NPC;
void create()
{
	set_name("飞贼",({"xumz npc"}));
	set("long",0);
	set("title","[31m武当派[2;37;0m[32m女真人[2;37;0m");
	set("age",240);
	set("str",25);
	set("con",27);
	set("int",35);
	set("spi",7);
	set("per",43);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname",0);
	set("combat_exp",100206729);
	set("max_qi",22994);
	set("max_jing",7441);
	set("gender","女性");
	set("max_neili",11630);
	set("max_jingli",7283);
	set("jiali",0);
	set("race","人类");
	set("class","taoist");
	set("repute",2771497);
	set("score",549);
	set("family/family_name","武当派");
	set_skill("training",10);
	set_skill("taiji-zhao",911);
	set_skill("beiming-shengong",153);
	set_skill("taiji-dao",244);
	set_skill("parry",991);
	set_skill("throwing",790);
	set_skill("bahuang-gong",536);
	set_skill("claw",789);
	set_skill("changhen-jian",187);
	set_skill("tianyu-qijian",990);
	set_skill("zhemei-shou",990);
	set_skill("blade",626);
	set_skill("cuff",544);
	set_skill("sword",991);
	set_skill("identification",51);
	set_skill("xiaowuxiang-gong",603);
	set_skill("liuyang-zhang",990);
	set_skill("taiji-jian",991);
	set_skill("hujia-daofa",1002);
	set_skill("hand",992);
	set_skill("taiji-quan",990);
	set_skill("strike",376);
	set_skill("tiyunzong",986);
	set_skill("yueying-wubu",931);
	set_skill("literate",741);
	set_skill("force",832);
	set_skill("taiji-shengong",689);
	set_skill("medical-skill",477);
	set_skill("taoism",832);
	set_skill("dodge",987);
	map_skill("parry","hujia-daofa");
	map_skill("throwing","liuyang-zhang");
	map_skill("claw","taiji-zhao");
	map_skill("blade","hujia-daofa");
	map_skill("cuff","taiji-quan");
	map_skill("sword","taiji-jian");
	map_skill("hand","zhemei-shou");
	map_skill("force","taiji-shengong");
	map_skill("dodge","tiyunzong");
	setup();
}
