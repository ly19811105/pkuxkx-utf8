// shechuangzi.c 蛇床子
// by Zine
inherit __DIR__"drug.c";
#include <ansi.h>
void create()
{
	set_name(YEL"蛇床子"NOR, ({ "shechuang zi", "zi","drug" }));
	set_weight(200);
	
		set("unit", "枚");
		set("long", "这是一枚蛇床的果实，可以入药。\n");
		set("value", 500);
		set("material", "grass");
		set("drugcode",12);
	
	setup();
    call_out("DownPrice",1);
}

int pricedown()
{
    this_object()->set("value", 0);
}