#include <ansi.h>
inherit NPC;
void create()
{
	set_name("名击剑",({"univursal npc"}));
	set("long",0);
	set("title","[1;32m诚实可靠[1;35m小郎君[2;37;0m");
	set("age",114);
	set("str",24);
	set("con",27);
	set("int",27);
	set("spi",4);
	set("per",41);
	set("job_title",0);
	set("nickname","[1;33m论万安塔的倒掉[2;37;0m[2;37;0m");
	set("combat_exp",100016630);
	set("max_qi",17411);
	set("max_jing",16453);
	set("gender","男性");
	set("max_neili",11857);
	set("max_jingli",8702);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",3296293);
	set("score",1612);
	set("family/family_name","明教");
	set_skill("literate",624);
	set_skill("jiuyang-shengong",790);
	set_skill("qishang-quan",400);
	set_skill("sword",901);
	set_skill("throwing",901);
	set_skill("blade",926);
	set_skill("datengnuo-bufa",914);
	set_skill("shenghuo-shengong",911);
	set_skill("hujia-daofa",1002);
	set_skill("force",741);
	set_skill("hanbing-zhang",902);
	set_skill("medical-skill",620);
	set_skill("feihua-shou",902);
	set_skill("parry",980);
	set_skill("lieyan-dao",903);
	set_skill("training",10);
	set_skill("dodge",913);
	set_skill("strike",903);
	set_skill("qiankun-danuoyi",426);
	map_skill("sword","shenghuo-shengong");
	map_skill("throwing","feihua-shou");
	map_skill("blade","lieyan-dao");
	map_skill("force","jiuyang-shengong");
	map_skill("parry","qiankun-danuoyi");
	map_skill("dodge","datengnuo-bufa");
	map_skill("strike","hanbing-zhang");
	setup();
}
