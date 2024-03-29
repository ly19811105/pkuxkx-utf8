#include <ansi.h>
inherit NPC;
void create()
{
	set_name("舒肤佳",({"safeguard npc"}));
	set("long",0);
	set("title","[31m武当派[2;37;0m[32m真人[2;37;0m");
	set("age",115);
	set("str",25);
	set("con",33);
	set("int",38);
	set("spi",7);
	set("per",36);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;37m[4m万安塔唯一指定香皂品牌[2;37;0m[2;37;0m");
	set("combat_exp",105479087);
	set("max_qi",28098);
	set("max_jing",24017);
	set("gender","男性");
	set("max_neili",15090);
	set("max_jingli",13823);
	set("jiali",0);
	set("race","人类");
	set("class","taoist");
	set("repute",6338703);
	set("score",366);
	set("family/family_name","武当派");
	set_skill("myingzhua-gong",964);
	set_skill("xiake-quanjiao",349);
	set_skill("qiankun-danuoyi",471);
	set_skill("dodge",987);
	set_skill("hanbing-zhang",977);
	set_skill("cuff",378);
	set_skill("feihua-shou",997);
	set_skill("sword",1000);
	set_skill("parry",1006);
	set_skill("lieyan-dao",872);
	set_skill("jiuyang-shengong",965);
	set_skill("taiji-quan",914);
	set_skill("hujia-daofa",1019);
	set_skill("literate",907);
	set_skill("shenghuo-shengong",1006);
	set_skill("qishang-quan",400);
	set_skill("throwing",997);
	set_skill("claw",965);
	set_skill("datengnuo-bufa",987);
	set_skill("xiake-shengong",328);
	set_skill("strike",977);
	set_skill("blade",950);
	set_skill("medical-skill",759);
	set_skill("taoism",472);
	set_skill("taiji-zhao",403);
	set_skill("tiyunzong",1);
	set_skill("taiji-shengong",481);
	set_skill("unarmed",535);
	set_skill("taiji-jian",913);
	set_skill("taiji-dao",1);
	set_skill("force",962);
	map_skill("dodge","datengnuo-bufa");
	map_skill("cuff","taiji-quan");
	map_skill("sword","taiji-jian");
	map_skill("parry","qiankun-danuoyi");
	map_skill("throwing","feihua-shou");
	map_skill("claw","taiji-zhao");
	map_skill("strike","hanbing-zhang");
	map_skill("blade","hujia-daofa");
	map_skill("unarmed","xiake-quanjiao");
	map_skill("force","jiuyang-shengong");
	setup();
}
