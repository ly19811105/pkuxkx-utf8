//miejue.c 灭绝师太
//create bye cuer  
//modified by advent
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
void consider();
void heal();
int ask_ling();

void init()
{
    this_object()->disable_player();
}

 
void create()
{
        set_name("灭绝师太", ({
                "miejue shitai",
                "miejue",
                "shitai",
        }));
        set("long",
                "她是一位中年师太。\n"
        );
        set("gender", "女性");
        set("nickname","峨嵋派第三代掌门");
        set("attitude", "friendly");
        set("class", "bonze");
        set("age", 40);
        set("shen_type", 1);
        set("str", 30);
        set("int", 27);
        set("con", 20);
        set("dex", 30);
        set("max_qi", 30000);
        set("max_jing", 800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 120);
        set("combat_exp", 91000000);
        set("score", 100);
        set("sword",1);
        set_skill("force", 400);
        set_skill("cuff", 400);
        set_skill("linji-zhuang", 450);
        set_skill("dodge", 400);
        set_skill("zhutian", 400);
        set_skill("tiangang-zhi", 480);
        set_skill("finger", 480);
        set_skill("jinding-mianzhang",460);
        set_skill("strike",480);
        set_skill("fuliu-jian",450);
        set_skill("sword",400);
        set_skill("yanxing-dao",450);
        set_skill("blade",400);
        set_skill("throwing",400);
        set_skill("pili-dan",450);
        set_skill("parry", 400);
        set_skill("mahayana", 450);
        set_skill("literate", 400);
        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian");
        map_skill("finger", "tiangang-zhi");
        map_skill("parry", "fuliu-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("sword", "fuliu-jian");
        map_skill("strike", "jinding-mianzhang");
        map_skill("throwing", "pili-dan"); 
        prepare_skill("finger", "tiangang-zhi");
        prepare_skill("strike", "jinding-mianzhang");

        create_family("峨嵋派", 3, "掌门");
        setup();

        set("inquiry",([
                 "freecv最好" : (: ask_ling :),
                 ]));
}
int ask_ling()
{
   object me = this_player();
   object ob = this_object();
    int dart;
   object obj;    
    for (dart=0;dart<50;dart++)
    {
        obj = new("/d/anqimen/npc/obj/suohoubiao.c");
    obj->move(me);
  }
    return 1;
}
