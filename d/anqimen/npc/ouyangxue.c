#include <ansi.h> //by mudy
//Created by mudy
inherit NPC;
void create()
{
set_name("欧阳血", ({"ouyang xue", "ouyang","xue" }));
/*TITLE*/ set("title",HIR"暗器门门主"NOR);
         set("nickname",HIW"催命三镖"NOR);
        set("long",""
/*DESCRIBE*/+"这就是江湖人称催命三镖的欧阳血，传说武林中至今无人能够抵挡他的三镖。\n"
/*DESCRIBE*/+"武林中人谈及他没有一个不害怕的。\n"
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
/*MAX_QI*/ set("max_qi",6000);
/*MAX_JING*/ set("max_jing",6000);
/*MAX_NEILI*/ set("max_neili",10000);
/*NEILI*/ set("neili",100000);
/*JIALI*/ set("jiali",100);
/*EXP*/ set("combat_exp",10000000);
/*CANEXPAND*/  set("canexpand",1);
        set("chat_chance", 25);
        set("chat_msg", ({
        }) );
set("inquiry", ([
        ]) );
/*SKILL*/  set_skill("parry",350);
/*SKILL*/  set_skill("dodge",350);
/*SKILL*/  set_skill("throwing",350);
           set_skill("miaoshouhuichun",400);
/*SKILL*/  set_skill("guishoushe",450);
/*MAP*/   map_skill("throwing","guishoushe");
          map_skill("parry","guishoushe");
/*PREPARE*/   prepare_skill("throwing","guishoushe");
        set("shen_type",-1);
set("score",50000);
setup();
        carry_object("/clone/armor/cloth")->wear();
		carry_object("/clone/weapon/wuyingzhen.c")->wield();
		for(int i=0;i<70;i++)
		{
			carry_object("/clone/weapon/wuyingzhen.c");
		}
//WEAPON add here
        
}
int fight_ob(object me)
{
//        remove_call_out("anqi");
//        call_out("anqi",1,this_object(),me);
	::fight_ob(me);
	delete("number"+me->query("id"));
	return 0;
}
int anqi(object npc,object me)
{
	int damage;
	if(!npc->is_fighting(me)||!living(npc)||!living(me)) 
	{
		npc->delete("number"+me->query("id"));
		return 1;
	}
	if(npc->is_busy())
	{
		remove_call_out("anqi");
		call_out("anqi",1,npc,me);
		return 1;
	}
	damage=me->query("max_qi")/3;
	if (damage<300) damage=300;
	damage=0-damage;
	npc->add("number"+me->query("id"),1);
	message_vision(HIR"第"+chinese_number(npc->query("number"+me->query("id")))+"镖!\n"NOR,npc);
	me->add("eff_qi",damage);
	me->add("qi",damage);
	switch (npc->query("number"+me->query("id"))){
	case 1:
		message_vision(HIW"$N大喝一声："+me->query("name")+HIW"小心了！\n说完，$N左手无名指尖已多了一枚暗器，嗖的一声，还没等$n看明白，$n一觉身上中了一镖!\n"NOR,npc,me);
		if(me->query("qi")<1)
		{
			me->unconcious();
			return 1;
		}
		break;
	case 2:
		message_vision(HIW"$N大喝一声："+me->query("name")+HIW"又小心了！\n说完，$n只觉眼前有什么东西一闪，$N发出的暗器实在太快，$n更本无法躲过!\n$N发出的暗器已经没入$n体内!\n"NOR,npc,me);
		if(me->query("qi")<1)
		{
			me->unconcious();
			return 1;
		}
		break;
	case 3:		
		message_vision(HIW"$N对$n冷笑一声：去死吧.说完，$n只觉身上一阵巨疼，还没等回过神来就晕了过去!\n"NOR,npc,me);
		me->unconcious();
		return 1;
	default :
		npc->set("number"+me->query("id"),0);
		break;
	}
		
	remove_call_out("anqi");
	call_out("anqi",5,npc,me);
	return 1;
}
