#include <ansi.h>
inherit NPC;
void create()
{
	set_name("慕容雨林",({"gaod npc"}));
	set("long",0);
	set("title","[1;31m天下第一镖[2;37;0m");
	set("age",147);
	set("str",38);
	set("con",30);
	set("int",27);
	set("spi",6);
	set("per",37);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;36m老了[1;31m推不了多久[1;33m就痿了[2;37;0m[2;37;0m");
	set("combat_exp",119774904);
	set("max_qi",12257);
	set("max_jing",9139);
	set("gender","男性");
	set("max_neili",15068);
	set("max_jingli",15044);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",11611020);
	set("score",2297);
	set("family/family_name","姑苏慕容");
	set_skill("finger",1053);
	set_skill("canhe-zhi",1053);
	set_skill("douzhuan-xingyi",1001);
	set_skill("xingyi-zhang",1051);
	set_skill("blade",1051);
	set_skill("shenyuan-gong",1004);
	set_skill("murong-jianfa",1055);
	set_skill("murong-daofa",1056);
	set_skill("sword",1056);
	set_skill("dodge",1060);
	set_skill("identification",3);
	set_skill("strike",1051);
	set_skill("hujia-daofa",4);
	set_skill("yanling-shenfa",1060);
	set_skill("force",1005);
	set_skill("literate",348);
	set_skill("parry",1056);
	map_skill("finger","canhe-zhi");
	map_skill("blade","murong-daofa");
	map_skill("sword","murong-jianfa");
	map_skill("dodge","yanling-shenfa");
	map_skill("strike","xingyi-zhang");
	map_skill("force","shenyuan-gong");
	map_skill("parry","murong-daofa");
	setup();
}
