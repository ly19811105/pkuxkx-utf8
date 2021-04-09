//Cracked by Roath
// tyjisi.c 台夷祭司

#include <ansi.h>

inherit NPC;

string ask_heal();

void create()
{
	set_name("祭司", ({ "ji si", "si", "woman" }) );
	set("long", "一位满脸皱纹的老年妇女，是本村的大祭司，常年司守祭台。台夷时处母系氏族，祭司要职皆为妇女。\n");

	set("age", 65);
	set("gender", "女性");
	set("dalivictim",1);

	set("str", 20);
	set("cor", 20);

    set("combat_exp", 1000);
	set("max_qi", 200);
	set("qi", 200);
	set_skill("dodge", 10);
	set_skill("parry", 10);
	set_temp("apply/attack", 10);
	set_temp("apply/damage", 5);
	set_temp("apply/armor", 5);
	
	set("attitude", "peaceful");
	set("shen_type", 1);

        set("inquiry", ([
                "疗伤" : (: ask_heal :),
        ]));
	setup();
	carry_object("/d/dali/npc/obj/tytongqun.c")->wear();
}
string ask_heal()
{
        object me = this_player();
        if(!me->query("zigongwan"))
                return "本祭司只管祭祀，不管疗伤。";
        message_vision(HIR"祭司念了几句咒语，$N只觉下体一热，似乎起了什么变化！\n"NOR, me);
        me->set("gender","男性");
        me->delete("zigongwan");
        me->delete_skill("pixie-jian");
        return "好了，你去吧。下次别这么不小心了。";
}
