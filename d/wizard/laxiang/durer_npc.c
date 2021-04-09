#include <ansi.h>
inherit NPC;
void create()
{
	set_name("琴瑟若无",({"durer npc"}));
	set("long",0);
	set("title","[1;31m福威镖局[1;33m镖师[2;37;0m");
	set("age",147);
	set("str",25);
	set("con",29);
	set("int",36);
	set("spi",6);
	set("per",37);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;31m沥泉[37m杀手[2;37;0m[2;37;0m");
	set("combat_exp",100018210);
	set("max_qi",38190);
	set("max_jing",7901);
	set("gender","男性");
	set("max_neili",13910);
	set("max_jingli",10903);
	set("jiali",0);
	set("race","人类");
	set("class","taoist");
	set("repute",3895502);
	set("score",2100);
	set("family/family_name","武当派");
	set_skill("literate",820);
	set_skill("throwing",2);
	set_skill("medical-skill",734);
	set_skill("cuff",996);
	set_skill("zui-quan",60);
	set_skill("taiji-jian",996);
	set_skill("taiji-dao",991);
	set_skill("taiji-quan",996);
	set_skill("tiyunzong",995);
	set_skill("taoism",1277);
	set_skill("jinshe-jian",299);
	set_skill("hujia-daofa",1002);
	set_skill("parry",995);
	set_skill("jinshe-zhui",299);
	set_skill("force",868);
	set_skill("taiji-zhao",723);
	set_skill("blade",992);
	set_skill("claw",453);
	set_skill("sword",996);
	set_skill("taiji-shengong",914);
	set_skill("training",14);
	set_skill("dodge",995);
	map_skill("throwing","jinshe-zhui");
	map_skill("cuff","taiji-quan");
	map_skill("parry","taiji-quan");
	map_skill("force","taiji-shengong");
	map_skill("blade","taiji-dao");
	map_skill("claw","taiji-zhao");
	map_skill("sword","taiji-jian");
	map_skill("dodge","tiyunzong");
	setup();
}