// FanYao.c
// pal 1997.05.09

#include "ansi.h"
inherit "/inherit/char/silver.c";

inherit NPC;


string ask_me();

void create()
{
        set_name("范遥", ({"fan yao","fan","yao",}));
        set("long",
        "他是一位带发修行的头陀，身穿白布长袍。\n"
        "他的脸上七七八八的全是伤疤，简直看不出本来面目了。\n"
        );

  set("title",GRN "明教" NOR + YEL +"光明右使" NOR);
        set("gender", "男性");
        set("attitude", "peaceful");
        set("class", "bonze");

        set("age", 38);
        set("shen_type", 1);
        set("per", 12);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 3500);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 1000000);
        set("score", 800000);

        set_skill("force", 180);
        set_skill("guangming-shenghuogong", 180);
        set_skill("dodge", 180);
        set_skill("datengnuo-bufa", 180);
        set_skill("finger", 180);
        set_skill("strike", 180);
        set_skill("hand", 180);
        set_skill("claw", 180);
        set_skill("parry", 180);
        set_skill("blade", 180);
        set_skill("lieyan-dao", 180);
        set_skill("nianhua-zhi", 180);
        set_skill("sanhua-zhang", 180);
        set_skill("fengyun-shou", 180);
        set_skill("longzhua-gong", 180);
        set_skill("buddhism", 100);
        set_skill("literate", 110);

        map_skill("force", "guangming-shenghuogong");
        map_skill("dodge", "datengnuo-bufa");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("blade", "lieyan-dao");
        map_skill("parry", "nianhua-zhi");


        set("inquiry", ([
                "例银" : (: ask_silver :),
        ]));

        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "jiuyang-shengong"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "好，教中兄弟每月都有一份例银，以后你就找我来领罢。"); //第一次打听例银的时候说的话


        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: prepare_skill("finger", "nianhua-zhi") :),
                (: prepare_skill("strike", "sanhua-zhang") :),
        }) );
        create_family("明教",20, "光明右使");

        setup();

        carry_object("d/mingjiao/npc/obj/baipao.c")->wear();
}



void attempt_apprentice(object ob)
{
        command("say 我不收徒的，你找各位法王去。");
        return 0;
}



