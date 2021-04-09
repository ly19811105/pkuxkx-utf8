#include <ansi.h>

inherit NPC;
int do_changegift(string);
int ask_gift();
void create()
{
        set_name("行云", ({"wiz advent", "advent"}));
        set("title",HIG"天赋调整巫师"NOR);
        set("gender", "男性");
        set("age", 27);
        set("long",
                "他就是行云(advent)，听说可以帮新人调整属性！\n你不妨上去打听一下“属性”或者“gift”的问题。\n");
        set("attitude", "heroism");
        set("str", 28);
        set("per", 48);
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

        set("shen_type",1);set("score",200);setup();
}

void init()
{
	      object me = this_player();        

        ::init();

        if( interactive(me) )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
        add_action("do_changegift","changegift");        
}


int do_changegift(string arg)
{
     int str, ints, con, dex, kar, per;
     object me;
     me = this_player();
     if (me->query("marks/changegift"))
          return notify_fail("每个人只有一次改变的机会！\n");
     
     if (me->query("mud_age")>3600 || me->query("combat_exp")>1000)
     return notify_fail("你太大了，不适合调整筋骨！\n");
        
     if ( !arg || sscanf(arg, "%d %d %d %d %d %d", str, ints, con, dex, kar, per) != 6)
     return notify_fail("指令格式：changegift <膂力> <悟性> <根骨> <身法> <福缘> <容貌>。\n");

     if(str+ints+con+dex !=80)
     return notify_fail("你的前四项属性值不等于80，请重新输入！\n");

     if(str>30 || ints>30 || con>30 || dex>30 || kar>30 || per>30)
     return notify_fail("各项属性均不能超过30！\n");
     
     if(str<10 || ints<10 || con<10 || dex<10 || kar<10 || per<10)
     return notify_fail("各项属性均不能低于10！\n");
     
     
     me->set("str",str);
     me->set("int",ints);
     me->set("con",con);
     me->set("dex",dex);
     me->set("kar", kar);
     me->set("per", per);
     me->set("marks/changegift",1);
     log_file("static/changegift", sprintf("%s(%s)于%s调整先天属性，调整后膂力%d，悟性%d，根骨%d，身法%d，福缘%d，容貌%d。\n",me->query("name"),me->query("id"),ctime(time()),me->query("str"),me->query("int"),me->query("con"),me->query("dex"),me->query("kar"),me->query("per")));
     me->save();
     write(HIM"恭喜你，属性设置成功！\n"NOR);
     return 1;
}

int ask_gift()
{
     object me;
     me = this_player();
     if (me->query("mud_age")>3600 || me->query("combat_exp")>100){ 
        tell_object(me,"你这么大了，自己去算命吧。\n");
        return 1;
        }
     write("行云说道：看好了，以下是你的属性：\n\n");
     write("你的膂力是："+me->query("str")+"!\n");
     write("你的悟性是："+me->query("int")+"!\n");
     write("你的根骨是："+me->query("con")+"!\n");
     write("你的身法是："+me->query("dex")+"!\n");
     write("你的福缘是："+me->query("kar")+"!\n");
     write("你的容貌是："+me->query("per")+"!\n");
     write("你的灵性是："+30+"!\n");
     write("如果你想改变前六项属性，可以按照下面的格式来更改。注意：福缘和容貌不一定越高越好。\n");
     write("指令格式：changegift <膂力> <悟性> <根骨> <身法> <福缘> <容貌>。\n");
     return 1;    
}
void greeting(object me)
{
        command("tell "+me->query("id")+" 
        欢迎光临北大侠客行！
        我是调整天赋的巫师，你可以输入changegift命令来调整你的天赋。
        命令格式：changegift <膂力> <悟性> <根骨> <身法> <福缘> <容貌>
        \n");
}
