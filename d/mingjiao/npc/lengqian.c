inherit NPC;

#include <ansi.h>

void create()
{
        set_name("冷谦", ({ "leng qian", "leng", "qian", }));
        set("long",
        "他是一位冷冷的老者，身穿一件白布长袍。\n"
        "他说话极为简捷，便是杀了他的头也不肯多说半句废话。\n"
        );

        set("title", GRN "明教" NOR "五散人");
        set("nickname", "冷面先生");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "fighter");

        set("age", 54);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 5000);

        set_skill("force", 85);
        set_skill("hunyuan-yiqi", 85);
        set_skill("dodge", 85);
        set_skill("shaolin-shenfa", 85);
        set_skill("cuff", 95);
        set_skill("jingang-quan", 95);
        set_skill("parry", 85);
        set_skill("buddhism", 85);
        set_skill("literate", 85);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("parry", "jingang-quan");

        prepare_skill("cuff", "jingang-quan");
        create_family("明教", 21, "五散人");

        setup();

        carry_object("/d/mingjiao/npc/obj/baipao")->wear();
}

