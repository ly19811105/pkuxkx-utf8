#include <ansi.h> //by mudy
//Created by mudy
inherit NPC;
inherit F_DEALER;
void create()
{
set_name("陈爽", ({"chen shuang", "chen", }));
/*TITLE*/ set("title",HIR"暗器门第三代弟子"NOR);
         set("nickname",HIY"铜钱镖"NOR);
        set("long",""
+"这就是江湖人称铜钱镖的暗器高手陈爽，他惯用的暗器是铜钱镖。\n"
+"现在他已经归于暗器门门下，成为暗器门下一员干将。\n"
);
/*GENDER*/    set("gender", "男性");
	    set("generation",1);
/*AGE*/        set("age", 40);
        set("attitude", "friendly");
        set("shen_type", 0);
/*STR*/ set("str",40);
/*INT*/ set("int",40);
/*CON*/ set("con",40);
/*DEX*/ set("dex",40);
/*MAX_QI*/ set("max_qi",2000);
/*MAX_JING*/ set("max_jing",2000);
/*MAX_NEILI*/ set("max_neili",2000);
/*NEILI*/ set("neili",6000);
/*JIALI*/ set("jiali",300);
/*EXP*/ set("combat_exp",500000);
/*CANEXPAND*/  set("canexpand",1);
        set("chat_chance", 15);
        set("chat_msg", ({
/*MSG_CHAT*/"这位，要买一点什么暗器么？\n",
/*MSG_CHAT*/"呵呵，......\n",
/*MSG_CHAT*/"陈爽朝你微笑示意。\n",
        }) );
set("inquiry", ([
        ]) );
/*SKILL*/  set_skill("parry",80);
/*SKILL*/  set_skill("dodge",120);
/*SKILL*/  set_skill("throwing",120);
/*SKILL*/  set_skill("miaoshouhuichun",80);
/*MAP*/   map_skill("throwing","miaoshouhuichun");
          map_skill("parry","miaoshouhuichun");
/*PREPARE*/   prepare_skill("throwing","miaoshouhuichun");
		set("vendor_goods",({
		__DIR__"obj/tongqianbiao.c",
		"/clone/weapon/wuyingzhen.c",
		__DIR__"obj/yingzhen.c",
		__DIR__"obj/xiuzhongjian.c",
		__DIR__"obj/huaguzhen.c",
		__DIR__"obj/suohoubiao.c",
		}));
        set("shen_type",-1);
set("score",3000);
setup();
        carry_object("/clone/armor/cloth")->wear();
		carry_object(__DIR__"obj/tongqianbiao.c")->wield();
        
}

void init()
{
    add_action("do_list","list");
    add_action("do_buy","buy");
}

int fight_ob(object me)
{
//        remove_call_out("anqi");
//        call_out("anqi",1,this_object(),me);
	::fight_ob(me);
	return 0;
}
int anqi(object npc,object me)
{
	if(!npc->is_fighting(me)||!living(npc)||!living(me)) return 1;
	if(npc->is_busy())
	{
		remove_call_out("anqi");
		call_out("anqi",1,npc,me);
		return 1;
	}
	message_vision(HIY"$N暗使内力，一枚铜钱突然就出现在$N手中，$N一摔碗，铜钱就随着指力射了出去!\n"NOR,npc);
	if(random(npc->query("combat_exp")*3)>random(me->query("combat_exp")))
	{//击中
		me->add("eff_qi",-10);
		me->add("qi",-20);
		message_vision(HIG"$n虽已看到，但是为时已晚，避无可避，被$N的暗器射中!\n"NOR,npc,me);
		if(me->query("qi")<1) me->die();
	}
	else
	{
		message_vision(MAG"$n一个燕子翻身，勉强躲过$N的暗器!\n"NOR,npc,me);
	}
	remove_call_out("anqi");
	call_out("anqi",4,npc,me);
	return 1;
}
