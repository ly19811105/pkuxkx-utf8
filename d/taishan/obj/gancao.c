// shenggancao 生甘草
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name(GRN"甘草"NOR, ({ "gancao", "gan cao","cao" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片甘草，生长在荒漠边缘，剥(bo)去外皮，内芯可以入药。\n");
		set("value", 3500);
		set("material", "grass");
		set("drugcode",14);
		
	}
	setup();
	call_out("DownPrice",1);
}

void init()
{
	add_action("do_bo", "bo");
}

int do_bo(string arg)
{
    object me=this_player();
    object ob=this_object();
    object sgc;
    if (!arg)
    {
        return notify_fail("你要剥什么？\n");
    }
    if (arg!="gancao"&&arg!="gan cao"&&arg!="cao")
    {
        return notify_fail("你要剥什么？\n");
    }
    sgc=new(__DIR__"shenggancao");
    sgc->move(me);
    message_vision("$N剥去甘草的外皮，得到一片生甘草。\n",me);
    destruct(ob);
    return 1;
}