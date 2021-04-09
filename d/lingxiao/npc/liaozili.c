// File         : chengzixue.c
// Created By   : whuan@pkuxkx, 2008-04-16

#include "setdizi.h"

void create()
{
        setcreate(240);

        set_name("廖自砺", ({ "liao zili", "liao", "zili", }));
        set("long", "廖自砺\n");

        set("age", 50);
        set("gender", "男性");
        set("str", 25);
        set("dex", 18);
        set("con", 21);
        set("int", 23);
        set("per", 24);

        add("inquiry", ([
                "name" : "我廖自砺的名字又岂是你等小辈问得的！",
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "liuchu" :),
                (: perform_action, "fengjian" :),
        }));
        create_family("雪山派", 5, "弟子");

        setup();
        carry_object(__DIR__"obj/sword.c")->wield();
        carry_object(__DIR__"obj/changpao.c")->wear();

}

void attempt_apprentice(object ob)
{
        return notify_fail("我暂不收徒，你找掌门人去吧。");
}
