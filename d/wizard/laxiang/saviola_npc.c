#include <ansi.h>
inherit NPC;
void create()
{
	set_name("萨维奥拉",({"saviola npc"}));
	set("long",0);
	set("title","[35m丐帮[2;37;0m[33m九袋[2;37;0m[35m长老[2;37;0m");
	set("age",168);
	set("str",18);
	set("con",30);
	set("int",38);
	set("spi",6);
	set("per",57);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","火葬厂副厂长兼纪检科主任[2;37;0m[2;37;0m");
	set("combat_exp",131560764);
	set("max_qi",10157);
	set("max_jing",12013);
	set("gender","男性");
	set("max_neili",15200);
	set("max_jingli",15285);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",420053);
	set("score",2492);
	set("family/family_name","丐帮");
	set_skill("dodge",1054);
	set_skill("force",1019);
	set_skill("feihua-shou",1017);
	set_skill("unarmed",1010);
	set_skill("shenghuo-lingfa",1011);
	set_skill("strike",1010);
	set_skill("medical-skill",1009);
	set_skill("xianglong-zhang",1010);
	set_skill("literate",990);
	set_skill("throwing",1010);
	set_skill("checking",300);
	set_skill("xiake-quanjiao",1012);
	set_skill("dagou-bang",1010);
	set_skill("jiuyang-shengong",546);
	set_skill("xiake-daofa",971);
	set_skill("lieyan-dao",1014);
	set_skill("staff",350);
	set_skill("xiake-strike",1010);
	set_skill("iron-cloth",1009);
	set_skill("huntian-qigong",380);
	set_skill("qiankun-danuoyi",520);
	set_skill("jinshe-zhui",1010);
	set_skill("parry",1010);
	set_skill("xiake-shengong",1009);
	set_skill("xiake-jianfa",965);
	set_skill("datengnuo-bufa",1053);
	set_skill("sword",1010);
	set_skill("blade",1010);
	map_skill("dodge","datengnuo-bufa");
	map_skill("force","xiake-shengong");
	map_skill("unarmed","xiake-quanjiao");
	map_skill("strike","xianglong-zhang");
	map_skill("throwing","feihua-shou");
	map_skill("staff","dagou-bang");
	map_skill("parry","qiankun-danuoyi");
	map_skill("sword","xiake-jianfa");
	map_skill("blade","xiake-daofa");
	set("shen_type",1);set("score",500000);setup();
}
