// gouqi 枸杞
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name(HIR"枸杞"NOR, ({ "gouqi", "gou qi" }));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "包");
		set("long", "这是一包枸杞，是河套地区的特产。根皮可以削(xiao)去入药。\n");
		set("value", 200);
		set("material", "grass");
		set("drugcode",15);
		
	}
	setup();
    call_out("pricedown",1);
}

int pricedown()
{
    this_object()->set("value", 0);
}
void init()
{
	add_action("do_xiao", "xiao");
}

int do_xiao(string arg)
{
    object me=this_player();
    object ob=this_object();
    object dgp;
    if (!arg)
    {
        return notify_fail("你要削什么？\n");
    }
    if (arg!="gouqi"&&arg!="gou qi")
    {
        return notify_fail("你要削什么？\n");
    }
    dgp=new(__DIR__"digupi");
    dgp->move(me);
    message_vision("$N削去枸杞的根皮，得到一片地骨皮。\n",me);
    destruct(ob);
    return 1;
}