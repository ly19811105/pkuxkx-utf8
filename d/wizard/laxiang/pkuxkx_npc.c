#include <ansi.h>
inherit NPC;
void create()
{
	set_name("南万侠",({"pkuxkx npc"}));
	set("long",0);
	set("title","[1;31m福威镖局[1;33m总镖头[2;37;0m");
	set("age",88);
	set("str",25);
	set("con",30);
	set("int",27);
	set("spi",6);
	set("per",38);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname",0);
	set("combat_exp",100039519);
	set("max_qi",11090);
	set("max_jing",6894);
	set("gender","男性");
	set("max_neili",12923);
	set("max_jingli",6791);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",4780948);
	set("score",2156);
	set("family/family_name","雪山派");
	set_skill("yanyi-shenfa",1000);
	set_skill("sword",1000);
	set_skill("lingxiao-quan",894);
	set_skill("dodge",1000);
	set_skill("medical-skill",460);
	set_skill("force",819);
	set_skill("cuff",894);
	set_skill("blade",1000);
	set_skill("xueshan-jianfa",1000);
	set_skill("jinwu-daofa",1000);
	set_skill("parry",903);
	set_skill("iron-cloth",702);
	set_skill("hujia-daofa",1000);
	set_skill("literate",704);
	set_skill("xueshan-neigong",827);
	map_skill("sword","xueshan-jianfa");
	map_skill("dodge","yanyi-shenfa");
	map_skill("force","xueshan-neigong");
	map_skill("cuff","lingxiao-quan");
	map_skill("blade","jinwu-daofa");
	map_skill("parry","hujia-daofa");
	setup();
}
