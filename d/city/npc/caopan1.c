// caopan.c  by hubo

inherit NPC;
#include <ansi.h>

void create()
{
	set_name("操盘手", ({ "shou","caopan shou"}) );
	set("gender", "男性" );
	set("age", 30);
	set("long",
		"他是著名的赌球操盘手，场次赔率都是他定的，据说\n"
    "和欧洲赌博公司有很大瓜葛\n");
	set("combat_exp", 50000);
	set("attitude", "friendly");
	set("rank_info/respect", "老板");
	set("shen_type",1);set("score",200);setup();
}

void init()
{
                add_action("do_paicai","paicai"); 
}
int do_paicai(string arg)
{
          object me;
          me = this_player();
         
         if  ( me->query("duqiu/what1") != 22 )
             
             {
             	  me->delete("duqiu/what1");
                me->delete("duqiu/amount1");
                me->delete("duqiu/code1");
                me->delete("duqiu/money1");
                write ("你没下过注，敢来赌博公司骗钱，不想活了？\n");
                return 1;
             }      
         
         if  ( !me->query("duqiu/amount1" ))
         	   
         	   {
         	   	  me->delete("duqiu/what1");
                me->delete("duqiu/amount1");
                me->delete("duqiu/code1");
                me->delete("duqiu/money1");
                write("你没买这场比赛，敢来赌博公司骗钱，不想活了？\n");
                return 1;
             }
             
         if  (me->query("duqiu/code1") != "3")
         	   
         	   {
         	   	  me->delete("duqiu/what1");
                me->delete("duqiu/amount1");
                me->delete("duqiu/code1");
                me->delete("duqiu/money1");
                write("非常抱歉，你押错了，全输光了，下次再翻本吧！\n");
                return 1;
             }
         
            write("恭喜您，押中了，为了您的安全，您的彩金已经直接汇入您的账号中，共"+me->query("duqiu/amount1")*23+"两黄金。\n");
            shout(HIG + me->query("name") + "在赌球中赚了"+me->query("duqiu/amount1")*23+"两黄金！\n"NOR);
            me->add("balance",me->query("duqiu/amount1")*230000);
            
            log_file("static/duqiu",sprintf("%s(%s) 在%s赌球中赚得%d两黄金，当前存款为(%d)！\n",
            me->query("name"),me->query("id"),ctime(time()),me->query("duqiu/amount1")*23,me->query("balance")));

            me->delete("duqiu/what1");
            me->delete("duqiu/amount1");
            me->delete("duqiu/code1");
            me->delete("duqiu/money1");

          return 1;               
}


