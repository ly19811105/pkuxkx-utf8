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
         shout(HIR"\n过年啦！过年啦！！每人都得一" + gift->query("unit") + gift->query("name") + "的大红包！！！\n");
        for(int i=sizeof(usr)-1;i>=0;i--)
       {  
       	  gift = new(arg);
          gift->move(usr[i]);
       }
}

