#include <ansi.h>
inherit NPC;
void create()
{
	set_name("慕容白云",({"hbao npc"}));
	set("long",0);
	set("title","[1;37m以彼之道 还施彼身[2;37;0m");
	set("age",267);
	set("str",26);
	set("con",33);
	set("int",26);
	set("spi",9);
	set("per",37);
	set("job_title",0);
	set("nickname","[1;34m别在我的坟前哭[1;36m脏我了轮回的路[2;37;0m[2;37;0m");
	set("combat_exp",100010468);
	set("max_qi",8799);
	set("max_jing",5222);
	set("gender","女性");
	set("max_neili",12231);
	set("max_jingli",7858);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",3285139);
	set("score",18944);
	set("family/family_name","姑苏慕容");
	set_skill("force",706);
	set_skill("training",5);
	set_skill("strike",905);
	set_skill("blade",842);
	set_skill("douzhuan-xingyi",797);
	set_skill("bizhen-qingzhang",194);
	set_skill("xiake-shengong",695);
	set_skill("canhe-zhi",995);
	set_skill("xiake-strike",724);
	set_skill("shenyuan-gong",811);
	set_skill("unarmed",546);
	set_skill("xiake-jianfa",589);
	set_skill("sword",913);
	set_skill("yanling-shenfa",908);
	set_skill("parry",996);
	set_skill("literate",355);
	set_skill("hujia-daofa",885);
	set_skill("murong-daofa",780);
	set_skill("finger",911);
	set_skill("dodge",910);
	set_skill("xiake-quanjiao",726);
	set_skill("xingyi-zhang",921);
	set_skill("xiake-daofa",590);
	set_skill("murong-jianfa",996);
	map_skill("force","shenyuan-gong");
	map_skill("strike","xingyi-zhang");
	map_skill("blade","hujia-daofa");
	map_skill("unarmed","xiake-quanjiao");
	map_skill("sword","murong-jianfa");
	map_skill("parry","xingyi-zhang");
	map_skill("finger","canhe-zhi");
	map_skill("dodge","yanling-shenfa");
	setup();
}
