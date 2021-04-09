//建康府尹

#include <ansi.h>
inherit NPC;

int ask_paper();

void create()
{
    set_name("马光祖", ({"ma guangzu", "ma","guangzu"}));
    set("title", HIR"大宋 "+HIG+"观文殿学士、沿江制置使兼建康府知府"NOR);
    set("gender", "男性");
    set("age", 50);
    set("long", "他就是当今朝廷的建康府知府——马光祖，字华父，号裕斋。\n");
    set("attitude","heroism");
    set("generation",0);
    set("mingpin",4);
    set("max_qi",800);
    set("eff_qi",800);
    set("qi",800);
    set("max_jing",300);
    set("jing",300);
    set("shen_type",1);
    set("no_clean_up",1);
    set("combat_exp",20000);

   

    setup();
	carry_object("/d/song/npc/obj/cloth1.c")->wear();
}
