#include <ansi.h>
inherit NPC;
void create()
{
	set_name("神侠",({"arnold npc"}));
	set("long",".
[2;37;0m");
	set("title","[32m天龙寺[2;37;0m[33m特使[2;37;0m");
	set("age",140);
	set("str",26);
	set("con",32);
	set("int",29);
	set("spi",7);
	set("per",51);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;37m退隐江湖[2;37;0m[2;37;0m");
	set("combat_exp",102581375);
	set("max_qi",11339);
	set("max_jing",7877);
	set("gender","男性");
	set("max_neili",13987);
	set("max_jingli",11010);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",2985319);
	set("score",2016);
	set("family/family_name","天龙寺");
	set_skill("liumai-shenjian",1005);
	set_skill("blade",1007);
	set_skill("beiming-shengong",380);
	set_skill("stealing",147);
	set_skill("huntian-qigong",839);
	set_skill("lingbo-weibu",1000);
	set_skill("jiuyin-shengong",101);
	set_skill("xianglong-zhang",1002);
	set_skill("yijin-jing",500);
	set_skill("yiyangzhi",325);
	set_skill("feihua-zhuyue",400);
	set_skill("claw",840);
	set_skill("dagou-bang",1002);
	set_skill("fanwen",200);
	set_skill("identification",51);
	set_skill("strike",1000);
	set_skill("checking",297);
	set_skill("medical-skill",501);
	set_skill("qishang-quan",397);
	set_skill("staff",1002);
	set_skill("cuff",400);
	set_skill("xiaoyaoyou",1000);
	set_skill("jiuyin-baiguzhao",840);
	set_skill("iron-cloth",694);
	set_skill("sword",1000);
	set_skill("dodge",1000);
	set_skill("hujia-daofa",1010);
	set_skill("force",1000);
	set_skill("training",300);
	set_skill("literate",922);
	set_skill("parry",1003);
	set_skill("finger",1005);
	map_skill("blade","hujia-daofa");
	map_skill("claw","jiuyin-baiguzhao");
	map_skill("strike","xianglong-zhang");
	map_skill("staff","dagou-bang");
	map_skill("cuff","qishang-quan");
	map_skill("sword","liumai-shenjian");
	map_skill("dodge","lingbo-weibu");
	map_skill("force","huntian-qigong");
	map_skill("parry","xianglong-zhang");
	map_skill("finger","yiyangzhi");
	setup();
}
