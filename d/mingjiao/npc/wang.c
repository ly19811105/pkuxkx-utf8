// wang.c by binlang
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("王八衰", ({"wang bashuai","wang","bashuai"}) );
        set("gender", "男性" );
        set("title",  HIY"神箭八雄"NOR);
        set("age", 38);
		set("start_room","/d/mingjiao/xiceting");
        set("long",
"这是绿柳山庄的神箭八雄中的最小的。
此人轻功特好，善使长枪。\n");
        set_temp("apply/attack", 35);
        set_temp("apply/defense", 35);
        set_temp("apply/damage",20);
        set("combat_exp", 55000);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set_skill("unarmed",55);
        set_skill("dodge",65);
        set_skill("parry",50);
        set_skill("force",55);
        set_skill("spear",55);
        set("attitude","heroism");
        set("shen_type",1);set("score",500);setup();
        carry_object("/clone/weapon/changjian.c")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
     }

