#include <ansi.h>
inherit NPC;
void create()
{
	set_name("洛春岚",({"luochunlan npc"}));
	set("long",0);
	set("title","[32m明教[2;37;0m[33m圣使[2;37;0m");
	set("age",165);
	set("str",35);
	set("con",30);
	set("int",29);
	set("spi",7);
	set("per",366);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;33m红尘笑,[1;35m问天道,[1;37m江湖路上谁逍遥.[2;37;0m[2;37;0m");
	set("combat_exp",122591988);
	set("max_qi",16400);
	set("max_jing",13994);
	set("gender","女性");
	set("max_neili",16040);
	set("max_jingli",15126);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",3540989);
	set("score",1503);
	set("family/family_name","明教");
	set_skill("jiuyin-shengong",400);
	set_skill("qiankun-danuoyi",497);
	set_skill("literate",1030);
	set_skill("dodge",1061);
	set_skill("medical-skill",465);
	set_skill("jiuyin-baiguzhao",1044);
	set_skill("jiuyang-shengong",527);
	set_skill("meinu-quan",1062);
	set_skill("blade",1046);
	set_skill("throwing",1060);
	set_skill("sword",1062);
	set_skill("qianmie-shou",1060);
	set_skill("cuff",1063);
	set_skill("datengnuo-bufa",1061);
	set_skill("shenghuo-shengong",1057);
	set_skill("feihua-shou",1025);
	set_skill("parry",1063);
	set_skill("force",1026);
	set_skill("beauty",470);
	set_skill("hujia-daofa",1072);
	set_skill("claw",1045);
	set_skill("changhen-bian",1061);
	set_skill("xuantie-jian",954);
	set_skill("quanzhen-jian",1063);
	set_skill("yunu-xinfa",1026);
	set_skill("whip",1061);
	set_skill("yunu-jianfa",1062);
	map_skill("dodge","datengnuo-bufa");
	map_skill("blade","hujia-daofa");
	map_skill("throwing","qianmie-shou");
	map_skill("sword","yunu-jianfa");
	map_skill("cuff","meinu-quan");
	map_skill("parry","qiankun-danuoyi");
	map_skill("force","yunu-xinfa");
	map_skill("claw","jiuyin-baiguzhao");
	map_skill("whip","changhen-bian");
	setup();
}
