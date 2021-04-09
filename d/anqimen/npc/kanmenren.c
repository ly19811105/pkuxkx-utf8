#include <ansi.h> //by mudy
//Created by mudy
inherit NPC;
void create()
{
set_name("罗天傲", ({"luo tianao", "luo", "tianao", }));
/*TITLE*/ set("title",HIR"暗器门第三代弟子"NOR);
         set("nickname",HIY"左手镖"NOR);
        set("long",""
/*DESCRIBE*/+"这就是江湖人称左手镖的暗器高手罗天傲，他左手暗器使得是神出鬼没。\n"
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
/*MAX_QI*/ set("max_qi",2000);
/*MAX_JING*/ set("max_jing",2000);
/*MAX_NEILI*/ set("max_neili",6000);
/*NEILI*/ set("neili",6000);
/*JIALI*/ set("jiali",300);
/*EXP*/ set("combat_exp",500000);
/*CANEXPAND*/  set("canexpand",1);
        set("chat_chance", 5);
        set("chat_msg", ({
/*MSG_CHAT*/"暗器门是天下最厉害的门派！\n",
/*MSG_CHAT*/"嘿嘿......\n",
/*MSG_CHAT*/"罗天傲仔细端详了你半天，轻轻的哼了一声。\n",
        }) );
set("inquiry", ([
        ]) );
/*SKILL*/  set_skill("parry",80);
/*SKILL*/  set_skill("dodge",80);
/*SKILL*/  set_skill("throwing",80);
/*SKILL*/  set_skill("miaoshouhuichun",80);
/*MAP*/   map_skill("throwing","miaoshouhuichun");
/*PREPARE*/   prepare_skill("throwing","miaoshouhuichun");

        set("shen_type",-1);
set("score",3000);
setup();
        carry_object("/clone/armor/cloth")->wear();
		carry_object("/clone/weapon/wuyingzhen.c")->wield();
        
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
	message_vision(HIM"$N突然纵身一跃,随之左手一扬，一支银针就从$N的左手手腕处飞了出来，直奔$n周身大穴!\n"NOR,npc,me);
	if(random(npc->query("combat_exp")*3)>random(me->query("combat_exp")))
	{//击中
		me->add("eff_qi",-10);
		me->add("qi",-20);
		message_vision(HIW"$n虽已看到，但是为时已晚，避无可避，被$N的暗器射中!\n"NOR,npc,me);
		if(me->query("qi")<1) me->die();
	}
	else
	{
		message_vision(HIB"$n一个燕子翻身，勉强躲过$N的暗器!\n"NOR,npc,me);
	}
	remove_call_out("anqi");
	call_out("anqi",4,npc,me);
	return 1;
}
