#include <ansi.h>
inherit NPC;
void create()
{
	set_name("小牛",({"pixyee npc"}));
	set("long","[1;36m你以为自己眼花了...
[2;37;0m");
	set("title","[32m明教[2;37;0m[33m圣使[2;37;0m");
	set("age",185);
	set("str",37);
	set("con",30);
	set("int",30);
	set("spi",11);
	set("per",37);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname",".[2;37;0m[2;37;0m");
	set("combat_exp",100031432);
	set("max_qi",14636);
	set("max_jing",13352);
	set("gender","男性");
	set("max_neili",12540);
	set("max_jingli",11456);
	set("jiali",1);
	set("race","人类");
	set("class",0);
	set("repute",1215131);
	set("score",1505);
	set("family/family_name","明教");
	set_skill("force",954);
	set_skill("qiankun-danuoyi",430);
	set_skill("blade",954);
	set_skill("kuangfeng-dao",954);
	set_skill("medical-skill",856);
	set_skill("throwing",844);
	set_skill("stealing",11);
	set_skill("myingzhua-gong",42);
	set_skill("kuihua-zhua",700);
	set_skill("feihua-shou",646);
	set_skill("parry",954);
	set_skill("sword",954);
	set_skill("jiuyang-shengong",672);
	set_skill("staff",954);
	set_skill("claw",954);
	set_skill("bixue-xinfa",444);
	set_skill("rumoring",10);
	set_skill("buddhism",150);
	set_skill("xiake-daofa",377);
	set_skill("literate",954);
	set_skill("leadership",201);
	set_skill("lieyan-dao",139);
	set_skill("xiake-shengong",450);
	set_skill("qishang-quan",400);
	set_skill("iron-cloth",954);
	set_skill("xiake-strike",464);
	set_skill("kuangfeng-jian",954);
	set_skill("yijin-jing",725);
	set_skill("strategy",200);
	set_skill("xiake-quanjiao",465);
	set_skill("hujia-daofa",954);
	set_skill("juemen-gun",954);
	set_skill("xiake-jianfa",379);
	set_skill("fanwen",122);
	set_skill("dodge",943);
	set_skill("unarmed",103);
	set_skill("datengnuo-bufa",943);
	set_skill("shenghuo-lingfa",119);
	set_skill("jinshe-zhui",843);
	map_skill("force","jiuyang-shengong");
	map_skill("blade","kuangfeng-dao");
	map_skill("throwing","feihua-shou");
	map_skill("parry","qiankun-danuoyi");
	map_skill("sword","kuangfeng-jian");
	map_skill("staff","juemen-gun");
	map_skill("claw","kuihua-zhua");
	map_skill("dodge","datengnuo-bufa");
	map_skill("unarmed","xiake-quanjiao");
	set("shen_type",1);set("score",500000);setup();
}