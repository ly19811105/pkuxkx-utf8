#include "setdizi.h"

void create()
{
        setcreate(50);
        add("long", "正在专心练剑。\n");
    add("inquiry", ([
       "here" : "这里便是闻名天下的凌霄城了。",
    ]));
    set("chat_chance", 14);
    set("chat_msg", ({
        (: command("sweat") :),
        (: command("halt") :),
        (: command("zeze") :),
    }));
        set("random_npc",1);
        setfamily(7);
        setup();
        setequip();
}

void init()
{
        setinit();
        ::init();
}

void attempt_apprentice(object ob)
{
    setapp(ob);
}
