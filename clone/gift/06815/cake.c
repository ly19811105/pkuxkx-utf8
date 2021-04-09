#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY"双黄"HIW+"白莲蓉"+HIG"月饼"NOR, ({"moon cake", "cake"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR"这是一盒天神制作的"+this_object()->name()+"，听说有益寿延年的神奇功效！\n"NOR);
                set("unit", "块");
                set("value", 0);
                set("no_store", 1);
                set("no_sell",1);
                set("no_pawn",1);
        }
        setup();
}
void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object me = this_player();
        object ob = this_object();
        object ak;
        int reward;
        reward=1+random(2);
        if(arg != "moon cake" && arg != "cake")
                return 0;
        if(me->query("gift/2006zhongqiu"))
                return notify_fail("做人不要太贪，月饼吃多了也会肚子痛的！\n");
        if(me->query("mud_age")<36000)
                return notify_fail("起码要在这个mud中呆足10个小时才可以食用中秋月饼!\n");
        if(me->query("combat_exp")<20000)
                return notify_fail("经验20000以上才可以食用中秋月饼!\n");
        switch(random(50)){
        case 0:
           me->add("int",reward);
           me->add("xiantian/int/2006zhongqiu", reward);
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，提高先天悟性！\n"NOR,users());
           break;
        case 1:
           me->add("str",reward);
           me->add("xiantian/str/2006zhongqiu", reward);
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，提高先天膂力！\n"NOR,users());
           break;
        case 2:
           me->add("con",reward);
           me->add("xiantian/con/2006zhongqiu", reward);
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，提高先天根骨！\n"NOR,users());
           break;
        case 3:
           me->add("dex",reward);
           me->add("xiantian/dex/2006zhongqiu", reward);
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，提高先天身法！\n"NOR,users());
           break;
        case 4:
           me->add("spi",reward);
           me->add("xiantian/spi/2006zhongqiu", reward);
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，提高先天灵性！\n"NOR,users());
           break;
        case 5:
           me->add("per",reward);
           me->add("per",reward);
           me->add("xiantian/per/2006zhongqiu", reward);
           me->add("xiantian/per/2006zhongqiu", reward);
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，提高容貌！\n"NOR,users());
           break;
        case 6:
           me->add("kar",reward);
           me->add("xiantian/kar/2006zhongqiu", reward);
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，提高福缘！\n"NOR,users());
           break;        
        case 7:
           if (me->query("betrayer")>0) 
           {
           me->add("betrayer",-1);
           write("减少叛师记录一次！\n");
           }
           else
           {
           write("减少叛师记录一次！\n");
           write("可惜你没有叛过师，并没有生效！\n");           
           }
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，减少一次叛师记录！\n"NOR,users());
           break;
        case 8:
           me->add("banlance",random(1000)*10000);
           write("你的存款增加了！\n");
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，获得了金钱奖励！\n"NOR,users());
           break;
        case 9:
           ak=new("/clone/gift/06815/ak.c");
           ak->move(me);
           write("你得到了一支ak！\n");
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"得到了一支冲锋枪，大家小心了！\n"NOR,users());           
           break;
        default:
           me->add("combat_exp",random(50000));
           me->add("potential",random(50000));
           message("channel:" + "chat",HIR + "【谣言】听说" + me->query("name") +"运气极好，提高经验和潜能！\n"NOR,users());
                
        }
        me->add("gift/2006zhongqiu", 1);
     log_file("static/zhongqiugift",sprintf("%s(%s)于%s领取06中秋礼物一次！\n",me->query("name"),me->query("id"),ctime(time())));
        me->save();
        destruct(ob);
        return 1;          
}
