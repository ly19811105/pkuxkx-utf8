#include <ansi.h>

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_open", "open");
}

void create()
{
        set_name(HIW"圣诞礼物"NOR, ({"shengdan bag", "bag"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
				set("no_give",1);
				set("no_get",1);
				set("no_sell",1);
                set("unit", "份");
                set("long", "这是北侠为大家准备的圣诞礼物！还不快打开它？(open)\n");
                set("value", 100);
        }
        setup();
}

int do_open(string arg)
{
	object gift;
	object me=this_player();

        if (!id(arg))
                return notify_fail("你要打开什么？\n");
		if(me!=environment(this_object())) return 1;
		message_vision(HIW"$N"+HIW"迫不及待地打开自己的圣诞礼包...\n"NOR,me);
		gift=new("/d/gift/mudy/xmas/dacan.c");
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		gift=new("/d/gift/mudy/xmas/lingdan.c");
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		gift=new("/d/shaolin/obj/puti-zi.c");
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		gift=new("/d/gift/mudy/xmas/lxmw_book.c");
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		gift=new("/d/gift/mudy/xmas/tongbi_book.c");
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		gift=new("/d/gift/mudy/xmas/guishoushe_book.c");
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		gift=new("/d/gift/mudy/xmas/kaitian_book.c");
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		gift=new("/d/gift/mudy/xmas/cikebi_book.c");
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
       	destruct(this_object());
       	return 1;
}
