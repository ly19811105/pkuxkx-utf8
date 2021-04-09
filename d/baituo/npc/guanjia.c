#include <ansi.h>

inherit NPC;
inherit F_MAILQUEST;
#include "/new_quest/qxiepai.h"
#include "/new_quest/quest.h"
void create()
{
        set_name("管家", ({ "guan jia","guan","jia" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "一个老谋深算的老管家。\n");
        set("shen_type", -1);
        set("combat_exp", 20000);
        set("str", 24);
        set("dex", 22);
        set("con", 23);
        set("int", 20);
        set("attitude", "friendly");
        set("max_qi", 200);
        set("max_jing", 200);
        set("neili", 200);
        set("max_neili", 200);
        set("score", 2500);
        set_skill("force", 22);
        set_skill("dodge", 23);
        set_skill("unarmed", 22);
        set_skill("parry", 24);
        set_temp("apply/attack", 15);
        set_temp("apply/defense", 14);
          create_family("白驼山", 4, "弟子");
        set("inquiry" ,([
        "储藏室" : "管家警惕地盯着你，说：你想偷东西吗？\n",
        "cancelquest":   (: ask_cancel() :),
        "取消任务":   (: ask_cancel() :),
        "quest":   (: ask_quest() :),        	        	
        ]));
        setup();
        carry_object("/d/baituo/obj/baipao")->wear();
        carry_object("/d/baituo/obj/key");
}

