#include <ansi.h>
inherit NPC;
void create()
{
	set_name("小宝贝",({"baobei npc"}));
	set("long",0);
	set("title","[32m天龙寺[2;37;0m[33m特使[2;37;0m");
	set("age",161);
	set("str",28);
	set("con",31);
	set("int",34);
	set("spi",5);
	set("per",40);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;31m知书达理[1;33m温柔婉约[1;34m贤惠能干[1;35m才貌双全[1;32m天上少有[1;36m地下无双[2;37;0m[2;37;0m");
	set("combat_exp",100054134);
	set("max_qi",10857);
	set("max_jing",6713);
	set("gender","女性");
	set("max_neili",13081);
	set("max_jingli",7078);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",1589063);
	set("score",2009);
	set("family/family_name","天龙寺");
	set_skill("cuff",386);
	set_skill("whip",909);
	set_skill("force",819);
	set_skill("yunu-jianfa",834);
	set_skill("beauty",494);
	set_skill("jiuyin-shengong",450);
	set_skill("finger",598);
	set_skill("throwing",49);
	set_skill("blade",644);
	set_skill("medical-skill",300);
	set_skill("xuantie-jian",835);
	set_skill("qufengshu",83);
	set_skill("yunu-xinfa",865);
	set_skill("dodge",983);
	set_skill("liumai-shenjian",949);
	set_skill("changhen-bian",950);
	set_skill("jiuyin-baiguzhao",791);
	set_skill("meinu-quan",585);
	set_skill("hujia-daofa",812);
	set_skill("parry",950);
	set_skill("xianyun",837);
	set_skill("yiyang-zhi",950);
	set_skill("beiming-shengong",380);
	set_skill("literate",686);
	set_skill("quanzhen-jian",834);
	set_skill("qianmie-shou",294);
	set_skill("qishang-quan",115);
	set_skill("claw",792);
	set_skill("lingbo-weibu",836);
	set_skill("sword",879);
	set_skill("feihua-zhuyue",347);
	map_skill("cuff","qishang-quan");
	map_skill("whip","changhen-bian");
	map_skill("force","yunu-xinfa");
	map_skill("finger","yiyang-zhi");
	map_skill("throwing","qianmie-shou");
	map_skill("blade","hujia-daofa");
	map_skill("dodge","lingbo-weibu");
	map_skill("parry","hujia-daofa");
	map_skill("claw","jiuyin-baiguzhao");
	map_skill("sword","quanzhen-jian");
	set("shen_type",1);set("score",500000);setup();
}
