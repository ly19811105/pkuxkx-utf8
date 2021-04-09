#include <ansi.h>
inherit NPC;
void create()
{
	set_name("本聪[2;37;0m",({"zsmjd npc"}));
	set("long",0);
	set("title","[1;36m殿中侍御史[2;37;0m");
	set("age",64);
	set("str",38);
	set("con",43);
	set("int",26);
	set("spi",13);
	set("per",18);
	set("job_title","[1;33m武学大宗师[2;37;0m");
	set("nickname",0);
	set("combat_exp",200001018);
	set("max_qi",22578);
	set("max_jing",9573);
	set("gender","男性");
	set("max_neili",41884);
	set("max_jingli",14255);
	set("jiali",0);
	set("race","人类");
	set("class","monk");
	set("repute",13151979);
	set("score",26747);
	set("family/family_name","天龙寺");
	set_skill("arrow",17);
	set_skill("beiming-shengong",1073);
	set_skill("pipa-shou",1202);
	set_skill("zui-quan",611);
	set_skill("lingbo-weibu",1210);
	set_skill("sword",1218);
	set_skill("literate",503);
	set_skill("disguise",109);
	set_skill("blade",1090);
	set_skill("force",1071);
	set_skill("hand",1190);
	set_skill("strike",1212);
	set_skill("jiuyin-shengong",180);
	set_skill("identification",51);
	set_skill("xuantie-jian",628);
	set_skill("finger",1209);
	set_skill("liumai-shenjian",1215);
	set_skill("yiyang-zhi",1208);
	set_skill("bizhen-qingzhang",1210);
	set_skill("dodge",1210);
	set_skill("parry",1211);
	set_skill("feihua-zhuyue",1208);
	set_skill("hujia-daofa",1216);
	set_skill("unarmed",11);
	map_skill("sword","liumai-shenjian");
	map_skill("blade","hujia-daofa");
	map_skill("force","beiming-shengong");
	map_skill("hand","pipa-shou");
	map_skill("strike","bizhen-qingzhang");
	map_skill("finger","liumai-shenjian");
	map_skill("dodge","lingbo-weibu");
	map_skill("parry","liumai-shenjian");
	setup();
}
