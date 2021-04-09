#include <ansi.h>
inherit NPC;

void create()
{
        set_name("十夫长", ({ "shifu zhang","zhang"}));
        set("gender", "男性");
        set("age", 36);
        set("attitude", "aggressive");
        set("shen", -8000);
        set("str", 28);
        set("int", 20);
        set("con", 25);
        set("dex", 27);

        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 50);
        set("combat_exp", 800000);
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
               (: perform_action, "strike.diezhang" :),
       }));
         set_skill("force", 50);
        set_skill("xuantian-wuji", 140);
         set_skill("dodge", 120 + random(30));


        set_skill("kunlun-shenfa", 140);
        set_skill("strike", 120 + random(30));
        set_skill("kunlun-zhang", 120 + random(30));
        set_skill("parry", 140);
        set_skill("literate", 80);
        map_skill("force", "xuantian-wuji");
         map_skill("dodge", "kunlun-shnfa");
          map_skill("strike", "kunlun-zhang");
          map_skill("parry", "kunlun-zhang");
        set_temp("apply/attack", 20);
        set_temp("apply/defense",50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 50);
        prepare_skill("strike", "kunlun-zhang");

        setup();

        carry_object("/d/shaolin/obj/puti-zi.c");
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", random(200));
}
