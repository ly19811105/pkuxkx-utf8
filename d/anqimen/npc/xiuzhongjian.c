#include <ansi.h> //by mudy
//Created by mudy
inherit NPC;
void create()
{
set_name("胡飞", ({"hu fei", "hu", }));
/*TITLE*/ set("title",HIR"暗器门第二代弟子"NOR);
         set("nickname",HIY"袖中剑"NOR);
        set("long",""
/*DESCRIBE*/+"这就是江湖人称袖中剑的暗器高手胡飞，他打斗中惯使袖中剑，让人防不胜防。\n"
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
/*EXP*/ set("combat_exp",2000000);
/*CANEXPAND*/  set("canexpand",1);
        set("chat_chance", 25);
        set("chat_msg", ({
/*MSG_CHAT*/"现如今不掌握两门暗器怎么在江湖上混？\n",
/*MSG_CHAT*/"哼......\n",
/*MSG_CHAT*/"胡飞理了理衣袖。\n",
        }) );
set("inquiry", ([
        ]) );
/*SKILL*/  set_skill("parry",200);
/*SKILL*/  set_skill("dodge",200);
/*SKILL*/  set_skill("throwing",200);
/*SKILL*/  set_skill("miaoshouhuichun",200);
/*MAP*/   map_skill("throwing","miaoshouhuichun");
          map_skill("parry","miaoshouhuichun");
/*PREPARE*/   prepare_skill("throwing","miaoshouhuichun");


        set("shen_type",-1);
set("score",5000);
setup();
        carry_object("/clone/armor/cloth")->wear();
		carry_object(__DIR__"obj/xiuzhongjian.c")->wield();
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
	message_vision(HIW"$N在打斗间突然,手法一变，双袖一扬，一支短剑就从$N的袖中飞了出来，直奔$n!\n"NOR,npc,me);
	if(random(npc->query("combat_exp")*4)>random(me->query("combat_exp")))
	{//击中
		me->add("eff_qi",-20);
		me->add("qi",-30);
		message_vision(HIB"$n虽已看到，但是为时已晚，避无可避，被$N的袖中剑射中!\n"NOR,npc,me);
		if(me->query("qi")<1) me->die();
	}
	else
	{
		message_vision(HIB"$n一个燕子翻身，勉强躲过$N的袖中剑!\n"NOR,npc,me);
	}
	remove_call_out("anqi");
	call_out("anqi",2,npc,me);
	return 1;
}
