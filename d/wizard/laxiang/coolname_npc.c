#include <ansi.h>
inherit NPC;
void create()
{
	set_name("浪子",({"coolname npc"}));
	set("long",0);
	set("title","[32m天龙寺[2;37;0m[33m使者[2;37;0m");
	set("age",121);
	set("str",25);
	set("con",31);
	set("int",40);
	set("spi",6);
	set("per",38);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname",0);
	set("combat_exp",100000070);
	set("max_qi",8925);
	set("max_jing",4939);
	set("gender","男性");
	set("max_neili",12921);
	set("max_jingli",5519);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",2362331);
	set("score",1035);
	set("family/family_name","天龙寺");
	set_skill("beiming-shengong",381);
	set_skill("xianglong-zhang",951);
	set_skill("strike",951);
	set_skill("lingbo-weibu",950);
	set_skill("liumai-shenjian",934);
	set_skill("medical-skill",854);
	set_skill("huntian-qigong",827);
	set_skill("force",856);
	set_skill("checking",309);
	set_skill("iron-cloth",811);
	set_skill("parry",974);
	set_skill("yiyang-zhi",975);
	set_skill("dodge",950);
	set_skill("shexing-shou",431);
	set_skill("sword",933);
	set_skill("hand",384);
	set_skill("begging",257);
	set_skill("spear",405);
	set_skill("rumoring",8);
	set_skill("xiaoyaoyou",764);
	set_skill("staff",964);
	set_skill("yuejia-qiangfa",422);
	set_skill("dagou-bang",964);
	set_skill("blade",850);
	set_skill("hujia-daofa",857);
	set_skill("literate",854);
	set_skill("stealing",158);
	set_skill("finger",249);
	map_skill("strike","xianglong-zhang");
	map_skill("force","huntian-qigong");
	map_skill("parry","hujia-daofa");
	map_skill("dodge","lingbo-weibu");
	map_skill("sword","liumai-shenjian");
	map_skill("hand","shexing-shou");
	map_skill("spear","yuejia-qiangfa");
	map_skill("staff","dagou-bang");
	map_skill("blade","hujia-daofa");
	map_skill("finger","yiyang-zhi");
	set("shen_type",1);set("score",500000);setup();
}
