#include "setdizi.h"

void create()
{
        setcreate(50);
        add("long", "大约是看守角门的。\n");
	add("inquiry", ([
		"here" : "这里便是闻名天下的凌霄城了。在下奉命在此看守角门。",
	]));
	set("chat_chance", 14);
	set("chat_msg", ({
		this_object()->query("name")+"正在练习雪山剑法。\n",
		this_object()->query("name")+"正在练习雪山剑法。\n",
		(: command("think") :),
		this_object()->query("name")+"警惕的四处张望，防止奸邪之徒作恶。\n",
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