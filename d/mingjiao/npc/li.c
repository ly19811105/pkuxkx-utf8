// li.c by binlang
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("李四摧", ({"li sicui","li","sicui"}) );
        set("gender", "男性" );
        set("title",  HIY"神箭八雄"NOR);
        set("age", 42);
        set("long",
"这是绿柳山庄的神箭八雄中的老四。
此人身强力壮，不用箭时就使一把长剑。\n");
        set_temp("apply/attack", 35);
        set_temp("apply/defense", 35);
        set_temp("apply/damage",20);
        set("combat_exp", 50000);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set_skill("unarmed",55);
        set_skill("dodge",55);
        set_skill("parry",55);
        set_skill("force",55);
        set_skill("blade",55);
        set("attitude","heroism");
        set("shen_type",1);set("score",500);setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();

}

