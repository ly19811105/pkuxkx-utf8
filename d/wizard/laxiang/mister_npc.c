#include <ansi.h>
inherit NPC;
void create()
{
	set_name("迷死她",({"mister npc"}));
	set("long",0);
	set("title","[31m桃花岛[2;37;0m[32m使者[2;37;0m");
	set("age",64);
	set("str",25);
	set("con",27);
	set("int",37);
	set("spi",6);
	set("per",34);
	set("job_title",0);
	set("nickname",0);
	set("combat_exp",100021443);
	set("max_qi",10638);
	set("max_jing",7020);
	set("gender","男性");
	set("max_neili",14775);
	set("max_jingli",7393);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",1587128);
	set("score",432);
	set("family/family_name","桃花岛");
	set_skill("sword",816);
	set_skill("literate",893);
	set_skill("unarmed",22);
	set_skill("jiuyin-shengong",33);
	set_skill("claw",10);
	set_skill("qimen-bagua",436);
	set_skill("strike",11);
	set_skill("finger",786);
	set_skill("beiming-shengong",342);
	set_skill("parry",771);
	set_skill("cuixin-zhang",9);
	set_skill("dodge",813);
	set_skill("tanzhi-shengong",6);
	set_skill("force",815);
	set_skill("duanshi-shenfa",813);
	set_skill("yuxiao-jian",801);
	set_skill("music",428);
	set_skill("liumai-shenjian",817);
	set_skill("jiuyin-baiguzhao",9);
	set_skill("yiyangzhi",224);
	set_skill("bihai-shengong",793);
	map_skill("sword","liumai-shenjian");
	map_skill("claw","jiuyin-baiguzhao");
	map_skill("strike","cuixin-zhang");
	map_skill("finger","liumai-shenjian");
	map_skill("parry","yuxiao-jian");
	map_skill("dodge","duanshi-shenfa");
	map_skill("force","bihai-shengong");
	setup();
}
