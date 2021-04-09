// 多铎

#include <ansi.h>

inherit __DIR__"qingbing_base.c";

void create()
{
	set_name(HIR"爱新觉罗.多铎"NOR, ({ "duo ergun", "duo"}));
	set("title",HIW"定国大将军 "HIY"豫王"NOR);
	set("gender","男性");
	set("age", 20+random(5));

	set("long","他就是凶名四播的定国大将军多铎。\n");
	set("attitude", "peaceful");
	set("combat_exp", 5000000);
	set("str", 20+random(5));
	set("int", 20+random(5));
	set("con", 20+random(5));
	set("dex", 20+random(5));
	set("max_qi", 20000);
	set("max_jing", 20000);
	set("max_neili", 5000);
	set("max_neili", 20000);
	set("neili", 5000);
	set("neili", 20000);
	set_temp("apply/armor", 100);
	set("jingli", 20000);
	set("max_jingli", 20000);
	set_skill("strike", 500);
	set_skill("cuff", 500);
	set_skill("hand", 500);
	set_skill("dodge", 500);
	set_skill("sword", 500);
	set_skill("force", 500);
	set_skill("parry", 500);
	set_skill("blade", 500);
	set_skill("hammer", 500);
	set_skill("axe", 500);
	set_skill("staff", 500);
	set_skill("literate", 500);
	set_skill("whip", 500);
	set("no_get", 1);
	set("random_npc",1);
	set("qingbing",3);
	setup();
	
	carry_object(__DIR__"items/cloth3")->wear();
	carry_object(__DIR__"items/sword")->wield();
	call_out("kill2", 1);
	call_out("dest", 180);
}

void die()
{
	object pl=find_player(this_object()->query("target"));
    object book;
	pl->add("skf/credit",10);
	tell_object(environment(),HIG"定国大将军多铎在众人拥簇下施施然的离开了。\n"NOR,);
    if (random(1000)>899)
    {
        book=new("/d/beijing/npc/obj/book42_2");
        book->move(pl);
        tell_object(pl,HIY"多铎走得有些匆忙，怀里掉落下一本黄色封皮的书。\n"NOR);
    }
	if(this_object())
	destruct(this_object());
}

