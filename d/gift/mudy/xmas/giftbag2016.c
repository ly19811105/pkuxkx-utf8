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
        set_name(HIW"新年礼物"NOR, ({"newyear bag", "bag"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
				set("no_give",1);
				set("no_get",1);
				set("no_sell",1);
                set("unit", "份");
                set("long", "这是北侠为大家准备的新年礼物！还不快打开它？(open)\n");
                set("value", 100);
        }
        setup();
}

int do_open(string arg)
{
	object gift;
	object me=this_player();
	object ob=this_object();
	int i;

        if (!id(arg))
                return notify_fail("你要打开什么？\n");
		if(me!=environment(this_object())) 
			{
			 write("这不是你的新年包裹，当心被人剁手啊1！\n");
			 return 1;
			}
		if (ob->query("owner")!=me->query("id"))
		{
			 write("这不是你的新年包裹，当心被人剁手啊！\n");
			 return 1;
		}
		message_vision(HIW"$N"+HIW"迫不及待地打开自己的新年礼包...\n"NOR,me);
/*		gift=new("/d/gift/icer/newskillbook.c");
		gift->set("owner",me->query("id"));
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		gift=new("/d/gift/icer/newskillbook.c");
		gift->set("owner",me->query("id"));
		gift->move(me);
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
*/
		for (i=0;i<20 ;i++ )
		{
			gift=new("/clone/gift/jiaozi2016.c");
			gift->set("owner",me->query("id"));
			gift->move(me);
			tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);
		}
		/*gift=new("/d/shaolin/obj/puti-zi.c");
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
		tell_object(me,HIY"你得到了"+gift->query("name")+"\n"NOR);*/
       	destruct(this_object());
       	return 1;
}
