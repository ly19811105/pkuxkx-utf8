#include <ansi.h>
inherit NPC;
void create()
{
	set_name("超级笨蛋",({"cjbd npc"}));
	set("long",0);
	set("title","[1;33m嫣然到此一游[2;37;0m");
	set("age",108);
	set("str",36);
	set("con",23);
	set("int",22);
	set("spi",4);
	set("per",19);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","高山仰止[2;37;0m[2;37;0m");
	set("combat_exp",100012917);
	set("max_qi",19654);
	set("max_jing",18235);
	set("gender","男性");
	set("max_neili",14212);
	set("max_jingli",7890);
	set("jiali",0);
	set("race","人类");
	set("class",0);
	set("repute",5387795);
	set("score",1504);
	set("family/family_name","明教");
	set_skill("literate",977);
	set_skill("datengnuo-bufa",732);
	set_skill("jinshe-jian",918);
	set_skill("unarmed",977);
	set_skill("qiankun-danuoyi",446);
	set_skill("medical-skill",977);
	set_skill("sword",977);
	set_skill("parry",977);
	set_skill("huashan-neigong",175);
	set_skill("shenghuo-lingfa",408);
	set_skill("force",977);
	set_skill("blade",973);
	set_skill("training",13);
	set_skill("huashan-jianfa",799);
	set_skill("hujia-daofa",1007);
	set_skill("dodge",921);
	set_skill("jiuyang-shengong",876);
	map_skill("sword","jinshe-jian");
	map_skill("parry","qiankun-danuoyi");
	map_skill("force","jiuyang-shengong");
	map_skill("blade","hujia-daofa");
	map_skill("dodge","datengnuo-bufa");
	set("shen_type",1);set("score",500000);setup();
}