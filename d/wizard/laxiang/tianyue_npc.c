#include <ansi.h>
inherit NPC;
void create()
{
	set_name("渡天",({"tianyue npc"}));
	set("long",0);
	set("title","[1;31m福威镖局[1;33m镖师[2;37;0m");
	set("age",143);
	set("str",32);
	set("con",30);
	set("int",33);
	set("spi",5);
	set("per",32);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname",0);
	set("combat_exp",100253605);
	set("max_qi",11614);
	set("max_jing",20948);
	set("gender","男性");
	set("max_neili",13631);
	set("max_jingli",7110);
	set("jiali",0);
	set("race","人类");
	set("class","bonze");
	set("repute",1730610);
	set("score",2016);
	set("family/family_name","少林派");
	set_skill("qishang-quan",401);
	set_skill("sword",946);
	set_skill("hunyuan-yiqi",501);
	set_skill("dodge",1000);
	set_skill("damo-jian",202);
	set_skill("wuying-jian",1001);
	set_skill("zui-gun",1001);
	set_skill("hujia-daofa",1001);
	set_skill("riyue-bian",1001);
	set_skill("blade",932);
	set_skill("xiuluo-dao",204);
	set_skill("club",354);
	set_skill("iron-cloth",930);
	set_skill("xiake-quanjiao",206);
	set_skill("hand",1000);
	set_skill("whip",828);
	set_skill("yijin-jing",837);
	set_skill("shaolin-shenfa",1000);
	set_skill("cuff",653);
	set_skill("buddhism",910);
	set_skill("qianye-shou",1001);
	set_skill("staff",519);
	set_skill("finger",602);
	set_skill("unarmed",120);
	set_skill("strike",353);
	set_skill("luohan-quan",934);
	set_skill("force",930);
	set_skill("medical-skill",930);
	set_skill("jingang-buhuai",502);
	set_skill("literate",930);
	set_skill("nianhua-zhi",600);
	set_skill("parry",1001);
	set_skill("xiake-shengong",191);
	map_skill("sword","wuying-jian");
	map_skill("dodge","shaolin-shenfa");
	map_skill("blade","hujia-daofa");
	map_skill("club","zui-gun");
	map_skill("iron-cloth","jingang-buhuai");
	map_skill("hand","qianye-shou");
	map_skill("whip","riyue-bian");
	map_skill("cuff","luohan-quan");
	map_skill("staff","zui-gun");
	map_skill("finger","nianhua-zhi");
	map_skill("unarmed","xiake-quanjiao");
	map_skill("force","yijin-jing");
	map_skill("parry","hujia-daofa");
	set("shen_type",1);set("score",500000);setup();
}
