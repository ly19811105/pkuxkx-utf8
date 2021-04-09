#include <ansi.h> //by mudy
//Created by mudy
inherit NPC;
void create()
{
set_name("孙笑痴", ({"sun xiaochi", "sun", }));
/*TITLE*/ set("title",HIR"暗器门大弟子"NOR);
         set("nickname",HIW"夺命连环镖"NOR);
        set("long",""
/*DESCRIBE*/+"这就是江湖人称夺命连环镖的暗器高手孙笑痴，他出暗器的速度极快，让人无法抵挡。\n"
/*DESCRIBE*/+"现在他已经归于暗器门门下，成为暗器门下一员干将。\n"
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
/*MAX_QI*/ set("max_qi",3000);
/*MAX_JING*/ set("max_jing",3000);
/*MAX_NEILI*/ set("max_neili",8000);
/*NEILI*/ set("neili",8000);
/*JIALI*/ set("jiali",300);
/*EXP*/ set("combat_exp",5000000);
/*CANEXPAND*/  set("canexpand",1);
        set("chat_chance", 25);
        set("chat_msg", ({
/*MSG_CHAT*/"要是哪一天，我能够接住门主的三镖，门主一定会把掌门人的位置让给我。\n",
/*MSG_CHAT*/"嘿嘿......\n",
/*MSG_CHAT*/"孙笑痴左手小拇指微微动了一下。\n",
        }) );
set("inquiry", ([
        ]) );
/*SKILL*/  set_skill("parry",250);
/*SKILL*/  set_skill("dodge",250);
/*SKILL*/  set_skill("throwing",250);
/*SKILL*/  set_skill("miaoshouhuichun",250);
/*MAP*/   map_skill("throwing","miaoshouhuichun");
          map_skill("parry","miaoshouhuichun");
/*PREPARE*/   prepare_skill("throwing","miaoshouhuichun");
        set("shen_type",-1);
set("score",10000);
setup();
        carry_object("/clone/armor/cloth")->wear();
		carry_object("/clone/weapon/wuyingzhen.c")->wield();
//WEAPON add here
        
}
int fight_ob(object me)
{
//        remove_call_out("anqi");
	call_out("anqi",1,this_object(),me);
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
	message_vision(HIW"$N突然双手往前一送，顿时就又出了一镖！夺命镖平平向$n飞去！\n"NOR,npc,me);
	if(random(npc->query("combat_exp")*5)>random(me->query("combat_exp")))
	{//击中
		me->add("eff_qi",-50);
		me->add("qi",-100);
		message_vision(HIB"$n虽已看到，但是为时已晚，避无可避，被$N的夺命镖射中!\n"NOR,npc,me);
		if(me->query("qi")<1) me->die();
	}
	else
	{
		message_vision(HIB"$n一个燕子翻身，勉强躲过$N的夺命镖!\n"NOR,npc,me);
	}
	remove_call_out("anqi");
	call_out("anqi",1,npc,me);
	return 1;
}
