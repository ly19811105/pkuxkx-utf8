#include <ansi.h>
inherit NPC;
void create()
{
	set_name("大海的尽头",({"ylei npc"}));
	set("long",0);
	set("title","[32m明教[2;37;0m[33m圣使[2;37;0m");
	set("age",123);
	set("str",35);
	set("con",27);
	set("int",30);
	set("spi",5);
	set("per",40);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;31m自由自在[1;33m的[1;36m飞翔[2;37;0m[2;37;0m");
	set("combat_exp",100881602);
	set("max_qi",16848);
	set("max_jing",16604);
	set("gender","男性");
	set("max_neili",13160);
	set("max_jingli",10634);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",1063795);
	set("score",4360);
	set("family/family_name","明教");
	set_skill("blade",965);
	set_skill("feihua-shou",944);
	set_skill("claw",971);
	set_skill("sword",955);
	set_skill("jiuyang-shengong",855);
	set_skill("dodge",970);
	set_skill("identification",50);
	set_skill("strike",837);
	set_skill("qiankun-danuoyi",465);
	set_skill("hujia-daofa",1006);
	set_skill("force",837);
	set_skill("training",19);
	set_skill("literate",839);
	set_skill("myingzhua-gong",970);
	set_skill("medical-skill",839);
	set_skill("hanbing-zhang",881);
	set_skill("datengnuo-bufa",962);
	set_skill("parry",1003);
	set_skill("qishang-quan",400);
	set_skill("throwing",642);
	set_skill("shenghuo-shengong",978);
	map_skill("blade","hujia-daofa");
	map_skill("claw","myingzhua-gong");
	map_skill("sword","shenghuo-shengong");
	map_skill("dodge","datengnuo-bufa");
	map_skill("strike","hanbing-zhang");
	map_skill("force","jiuyang-shengong");
	map_skill("parry","qiankun-danuoyi");
	map_skill("throwing","feihua-shou");
	setup();
}
