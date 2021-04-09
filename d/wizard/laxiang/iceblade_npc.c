#include <ansi.h>
inherit NPC;
void create()
{
	set_name("天涯",({"iceblade npc"}));
	set("long",0);
	set("title","[32m古墓派[2;37;0m[35m圣使[2;37;0m");
	set("age",223);
	set("str",24);
	set("con",33);
	set("int",36);
	set("spi",10);
	set("per",41);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","保卫襄阳爱好者协会常务理事[2;37;0m[2;37;0m");
	set("combat_exp",101330709);
	set("max_qi",8330);
	set("max_jing",4979);
	set("gender","男性");
	set("max_neili",15420);
	set("max_jingli",14349);
	set("jiali",100);
	set("race","人类");
	set("class",0);
	set("repute",810400);
	set("score",1533);
	set("family/family_name","古墓派");
	set_skill("dodge",1005);
	set_skill("xuantie-jian",1005);
	set_skill("meinu-quan",185);
	set_skill("xianyun",1005);
	set_skill("strike",944);
	set_skill("literate",1005);
	set_skill("yuejia-qiangfa",237);
	set_skill("xiake-strike",1006);
	set_skill("buddhism",155);
	set_skill("iron-cloth",1005);
	set_skill("bizhen-qingzhang",118);
	set_skill("whip",935);
	set_skill("claw",1005);
	set_skill("xiaohun-zhang",944);
	set_skill("parry",1005);
	set_skill("xiake-jianfa",849);
	set_skill("quanzhen-jian",936);
	set_skill("blade",968);
	set_skill("yijin-jing",655);
	set_skill("force",1005);
	set_skill("spear",934);
	set_skill("unarmed",1005);
	set_skill("qishang-quan",404);
	set_skill("medical-skill",1005);
	set_skill("throwing",936);
	set_skill("xiake-quanjiao",1006);
	set_skill("jiuyin-baiguzhao",1005);
	set_skill("xiake-daofa",847);
	set_skill("jiuyin-shengong",661);
	set_skill("changhen-bian",933);
	set_skill("yunu-jianfa",1006);
	set_skill("xiake-shengong",1005);
	set_skill("qianmie-shou",931);
	set_skill("sword",1006);
	set_skill("yunu-xinfa",110);
	map_skill("dodge","xianyun");
	map_skill("strike","xiaohun-zhang");
	map_skill("whip","changhen-bian");
	map_skill("claw","jiuyin-baiguzhao");
	map_skill("parry","xuantie-jian");
	map_skill("blade","xiake-daofa");
	map_skill("force","jiuyin-shengong");
	map_skill("spear","yuejia-qiangfa");
	map_skill("unarmed","xiake-quanjiao");
	map_skill("throwing","qianmie-shou");
	map_skill("sword","xiake-jianfa");
	set("shen_type",1);set("score",500000);setup();
}
