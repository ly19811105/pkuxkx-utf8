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

int do_giftall()
{
    call_out("sagift",1);
        return 1;
}
void wizard()
{
shout( HIC"\n猪头猪脑的巫师们躲在云里，偷看着大地上发生的一切。过节啦!\n"NOR);
        shout(HIY"\n大家不自禁放下手中的武器，跪在地上向天空膜拜。\n"NOR);
        call_out("sagift",5);
}

void sagift()
{
        shout(BNK+HIC"\n中秋刚过，又来国庆，有老婆的玩老婆，哦，错了，跟老婆玩，没老婆的玩泥巴。小意思，小意思，不成敬意。\n"NOR);



    call_out("guo",1);
}
void guo()
{
        object *usr;
        object giftguo;
        usr=users();
        for(int i=0;i<sizeof(usr);i++)
{
        {
         giftguo = new("/u/gudu/obj/guoqi.c");
          giftguo->move(usr[i]);
                }
        }
}

