//  礼品分发器

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("礼品分发器", ({"gift box","box"}) );
        setup();
}
void init()
{
        add_action("do_giftall","giftall");
//      add_action("do_gift",gift);
}

int do_gift()
{
return 1;
}

int do_giftall(string arg)
{
    call_out("sagift",1,arg);
        return 1;
}
void sagift(string arg)
{
        object *usr;
        object gift;

        usr=users();
        gift = new(arg);
		if(!gift) gift=new("/d/gift/mudy/xmas/giftbag.c");
		arg="/d/gift/mudy/xmas/giftbag.c";
        for(int i=sizeof(usr)-1;i>=0;i--)
       {  
		  tell_object(usr[i],HIY+this_player()->query("name")+HIY"突然来到你面前笑道：过节了，给大家发礼物了！\n"NOR);
		  tell_object(usr[i],HIB+this_player()->query("name")+HIB"给你一个"+gift->query("name")+"\n"NOR);
       	  gift = new(arg);
          gift->move(usr[i]);
       }
}

