#include <ansi.h>
inherit NPC;
void create()
{
	set_name("蚊子",({"mosquito npc"}));
	set("long",0);
	set("title","[1;36m姑苏慕容叛徒幕后主使[2;37;0m");
	set("age",223);
	set("str",26);
	set("con",36);
	set("int",33);
	set("spi",6);
	set("per",50);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;36m人生[1;31m若[1;33m只[1;32m如[2;37;0m[37m初见[2;37;0m[2;37;0m");
	set("combat_exp",104769162);
	set("max_qi",24282);
	set("max_jing",13061);
	set("gender","男性");
	set("max_neili",15251);
	set("max_jingli",9542);
	set("jiali",0);
	set("race","人类");
	set("class","taoist");
	set("repute",2330078);
	set("score",0);
	set("family/family_name","武当派");
	set_skill("dodge",1017);
	set_skill("taiji-quan",832);
	set_skill("force",1017);
	set_skill("taiji-zhao",601);
	set_skill("feihua-shou",834);
	set_skill("unarmed",1017);
	set_skill("daoxue-xinfa",101);
	set_skill("medical-skill",1036);
	set_skill("strike",1017);
	set_skill("literate",1046);
	set_skill("taiji-shengong",362);
	set_skill("throwing",1017);
	set_skill("xiake-quanjiao",1017);
	set_skill("xiake-shenfa",964);
	set_skill("jiuyang-shengong",588);
	set_skill("xiake-daofa",911);
	set_skill("tonggui-jian",847);
	set_skill("xiake-strike",1017);
	set_skill("xiantian-gong",221);
	set_skill("iron-cloth",236);
	set_skill("cuff",1017);
	set_skill("claw",1017);
	set_skill("qiankun-danuoyi",359);
	set_skill("parry",1017);
	set_skill("xiake-jianfa",909);
	set_skill("xiake-shengong",1017);
	set_skill("quanzhen-jian",848);
	set_skill("sword",1017);
	set_skill("taoism",940);
	set_skill("blade",1017);
	map_skill("dodge","xiake-shenfa");
	map_skill("force","xiake-shengong");
	map_skill("unarmed","xiake-quanjiao");
	map_skill("strike","xiake-strike");
	map_skill("throwing","feihua-shou");
	map_skill("cuff","taiji-quan");
	map_skill("claw","taiji-zhao");
	map_skill("parry","qiankun-danuoyi");
	map_skill("sword","xiake-jianfa");
	map_skill("blade","xiake-daofa");
	set("shen_type",1);set("score",500000);setup();
}
