#include <ansi.h>
inherit NPC;
void create()
{
	set_name("杨雪燕",({"yxy npc"}));
	set("long",0);
	set("title","[32m古墓派[2;37;0m[35m圣女[2;37;0m");
	set("age",229);
	set("str",34);
	set("con",36);
	set("int",38);
	set("spi",8);
	set("per",35);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;34m[1;5m剑魔[2;37;0m[2;37;0m");
	set("combat_exp",118409227);
	set("max_qi",13767);
	set("max_jing",7768);
	set("gender","女性");
	set("max_neili",14180);
	set("max_jingli",13620);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",8670901);
	set("score",3999);
	set("family/family_name","古墓派");
	set_skill("beauty",421);
	set_skill("quanzhen-jian",1004);
	set_skill("hujia-daofa",1003);
	set_skill("claw",1001);
	set_skill("spear",450);
	set_skill("xuantie-jian",1042);
	set_skill("forging",106);
	set_skill("flatter",301);
	set_skill("parry",1024);
	set_skill("blade",1002);
	set_skill("qianmie-shou",1003);
	set_skill("sword",1044);
	set_skill("yunu-xinfa",907);
	set_skill("jiuyin-baiguzhao",1000);
	set_skill("meinu-quan",1044);
	set_skill("strike",200);
	set_skill("xiaohun-zhang",115);
	set_skill("xianyun",1043);
	set_skill("changhen-bian",1018);
	set_skill("force",908);
	set_skill("identification",267);
	set_skill("throwing",1004);
	set_skill("literate",500);
	set_skill("yuejia-qiangfa",574);
	set_skill("dodge",1044);
	set_skill("cuff",1044);
	set_skill("whip",1018);
	set_skill("training",22);
	set_skill("yunu-jianfa",1016);
	set_skill("jiuyin-shengong",200);
	map_skill("claw","jiuyin-baiguzhao");
	map_skill("spear","yuejia-qiangfa");
	map_skill("parry","hujia-daofa");
	map_skill("blade","hujia-daofa");
	map_skill("sword","yunu-jianfa");
	map_skill("strike","xiaohun-zhang");
	map_skill("force","yunu-xinfa");
	map_skill("throwing","qianmie-shou");
	map_skill("dodge","xianyun");
	map_skill("cuff","meinu-quan");
	map_skill("whip","changhen-bian");
	setup();
}
