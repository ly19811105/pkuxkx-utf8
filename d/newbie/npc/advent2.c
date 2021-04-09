#include <ansi.h>

inherit NPC;
int do_changegift(string);
int ask_gift();
void create()
{
        set_name("行云", ({"wiz advent"}));
        set("title",HIW"巫师" NOR);
        set("gender", "男性");
        set("age", 27);
        set("long",
                "他就是行云(advent)，听说可以帮新人调整属性！\n你不妨上去打听一下“属性”或者“gift”的问题。\n");
        set("attitude", "heroism");
        set("str", 28);
        set("int", 18);
        set("con", 24);
        set("dex", 20);
        set("chat_chance", 20);
        set("max_qi", 600);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 50);

        set("combat_exp", 10000);

        set("inquiry", ([
                "属性" : (: ask_gift:),
                "gift" : (: ask_gift:),
        ]) );

        setup();
}

void init()
{
        object me = this_player();        
        add_action("do_changegift","changegift");

        ::init();

        if( interactive(me) )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}



int do_changegift(string arg)
{
     int str, ints, con, dex;
     object me;
     me = this_player();
     if (me->query("marks/changegift")==1)
     return notify_fail("每个人只有一次改变的机会！\n");
     
     if (me->query("mud_age")>3600 || me->query("combat_exp")>100)
     return notify_fail("你太大了，不适合调整筋骨！\n");
        
     if ( !arg || sscanf(arg, "%d %d %d %d", str, ints, con, dex) != 4)
     return notify_fail("指令格式：changegift <膂力> <悟性> <根骨> <身法>。\n");

     if(str+ints+con+dex !=80)
     return notify_fail("你的属性值不等于80，请重新输入！\n指令格式：changegift <膂力> <悟性> <根骨> <身法>。\n");    

     if(str>30 || ints>30 || con>30 || dex>30)
     return notify_fail("各项属性均不能超过30！\n");
     
     if(str<10 || ints<10 || con<10 || dex<10)
     return notify_fail("各项属性均不能低于10！\n");
     
     
     me->set("str",str);
     me->set("int",ints);
     me->set("con",con);
     me->set("dex",dex);
     me->set("marks/changegift",1);
     log_file("static/changegift",sprintf(" %s(%s)于%s调整先天属性，调整后膂力为%d，悟性为%d，根骨为%d，身法为%d。\n",me->query("name"),me->query("id"),ctime(time()),me->query("str"),me->query("int"),me->query("con"),me->query("dex")));   
     me->save();
     write("属性设置成功!\n");
     return 1;
}

int ask_gift()
{
     object me;
     me = this_player();
     if (me->query("mud_age")>3600 || me->query("combat_exp")>100) return 0;
     write("行云说道：看好了，以下是你的属性：\n\n");
     write("你的膂力是："+me->query("str")+"!\n");
     write("你的悟性是："+me->query("int")+"!\n");
     write("你的根骨是："+me->query("con")+"!\n");
     write("你的身法是："+me->query("dex")+"!\n");
     write("你的福缘是："+me->query("kar")+"!\n");
     write("你的容貌是："+me->query("per")+"!\n");
     write("你的灵性是："+30+"!\n");
     write("如果你想改变前四项属性，可以按照下面的格式来更改！\n");
     write("指令格式：changegift <膂力> <悟性> <根骨> <身法>。\n");
     return 1;    
}
void greeting(object me)
{
        command("tell "+me->query("id")+"你想知道你的属性吗？输入ask wiz advent about gift。\n" + NOR);
        command("tell "+me->query("id")+"你想改变输入可以用changegift命令。\n" + NOR);
}
