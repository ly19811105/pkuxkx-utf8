#include <ansi.h> //by mudy
//Created by ldjt
inherit NPC;
void create()
{
/*NAME*/set_name("酷老鼠"
, ({ 
"ku laoshu", "ku", 

		}));
/*TITLE*/ set("title","清洁工人");
//NICKNAME here
        set("long",""
/*DESCRIBE*/+"一个老人，喃喃自语得打扫着。\n"
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//OVERDESCRIBE
);
/*GENDER*/  set("gender","男性");
	    set("generation",1);
/*AGE*/ set("age",50);
        set("attitude", "friendly");
        set("shen_type", 0);
/*STR*/ set("str",50);
/*INT*/ set("int",50);
/*CON*/ set("con",50);
/*DEX*/ set("dex",50);
/*MAX_QI*/ set("max_qi",5000);
/*MAX_JING*/ set("max_jing",5000);
/*MAX_NEILI*/ set("max_neili",5000);
/*NEILI*/ set("neili",5000);
/*JIALI*/ set("jiali",200);
/*EXP*/ set("combat_exp",8000000);
/*CANEXPAND*/  set("canexpand",1);
        set("chat_chance", 5);
        set("chat_msg", ({
/*MSG_CHAT*/"这里要是没有我，哼横。。。。。\n",
/*MSG_CHAT*/"我是人民的勤务员啊！！\n",
/*MSG_CHAT*/"我从事的是伟大的事业\n",
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//MSG_CHAT
//OVERMSG_CHAT
        }) );
set("inquiry", ([
        ]) );
/*SKILL*/  set_skill("parry",450);
/*SKILL*/  set_skill("dodge",450);
/*SKILL*/  set_skill("force",450);
/*SKILL*/  set_skill("sword",450);
/*SKILL*/  set_skill("xiantian-gong",450);
/*SKILL*/  set_skill("tonggui-jian",450);
/*SKILL*/  set_skill("xiaoyaoyou",450);
/*SKILL*/  set_skill("literate",450);
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//SKILL
//OVERSKILL
/*MAP*/   map_skill("parry","tonggui-jian");
/*MAP*/   map_skill("dodge","xiaoyaoyou");
/*MAP*/   map_skill("force","xiantian-gong");
/*MAP*/   map_skill("sword","tonggui-jian");
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//MAP
//OVERMAP
/*PREPARE*/   prepare_wskill("sword","tonggui-jian");
//PREPARE
//PREPARE
//PREPARE
//PREPARE
//OVERPREPARE
        setup();
        carry_object("/clone/armor/cloth")->wear();
/*WEAPON*/  carry_object("/clone/weapon/changjian.c")->wield();
        
}