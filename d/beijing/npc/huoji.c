//Cracked by Roath
// huoji  伙计
// Ssy

inherit NPC;
#include "/d/beijing/killme.h"


void create()
{
        set_name("伙计", ({ "huoji", "keeper" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 25);
        set("long", "他是个勤劳的伙计，肚子里也有些墨水。\n");
        set("combat_exp", 5000);
        set("attitude", "friendly");

        set("shen_type",1);set("score",200);setup();
}
