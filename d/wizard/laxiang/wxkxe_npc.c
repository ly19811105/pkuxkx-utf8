#include <ansi.h>
inherit NPC;
void create()
{
	set_name("慕容风",({"wxkxe npc"}));
	set("long",0);
	set("title","[1;37m以彼之道 还施彼身[2;37;0m");
	set("age",102);
	set("str",29);
	set("con",39);
	set("int",27);
	set("spi",8);
	set("per",36);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname","[1;32m※※威震河朔※※[1;37m之[1;33m风刀[2;37;0m[2;37;0m");
	set("combat_exp",105724564);
	set("max_qi",10520);
	set("max_jing",8790);
	set("gender","男性");
	set("max_neili",38394);
	set("max_jingli",9165);
	set("jiali",0);
	set("race","人类");
	set("class","taoism");
	set("repute",11140835);
	set("score",1503);
	set("family/family_name","姑苏慕容");
	set_skill("liumai-shenjian",1010);
	set_skill("douzhuan-xingyi",439);
	set_skill("blade",567);
	set_skill("xingyi-zhang",75);
	set_skill("beiming-shengong",1010);
	set_skill("shenyuan-gong",445);
	set_skill("lingbo-weibu",857);
	set_skill("xiantian-gong",177);
	set_skill("feihua-shou",120);
	set_skill("yiyangzhi",954);
	set_skill("murong-jianfa",1016);
	set_skill("feihua-zhuyue",339);
	set_skill("sword",1016);
	set_skill("murong-daofa",128);
	set_skill("jiuyang-shengong",449);
	set_skill("dodge",1011);
	set_skill("hujia-daofa",1016);
	set_skill("qiankun-danuoyi",469);
	set_skill("force",1011);
	set_skill("training",299);
	set_skill("yanling-shenfa",1011);
	set_skill("literate",822);
	set_skill("medical-skill",822);
	set_skill("parry",837);
	set_skill("finger",955);
	set_skill("quanzhen-jian",1000);
	set_skill("canhe-zhi",881);
	map_skill("blade","hujia-daofa");
	map_skill("sword","murong-jianfa");
	map_skill("dodge","yanling-shenfa");
	map_skill("force","shenyuan-gong");
	map_skill("parry","xingyi-zhang");
	map_skill("finger","canhe-zhi");
	setup();
}
