// 完颜康 Zine Oct 6 2010


#include <ansi.h>
inherit NPC;
#include "/d/menggu/shediao_bonus.h"
int ask_kang1();
int ask_kang2();
int ask_kang3();


void create()
{
        set_name("完颜康", ({ "wanyan kang", "wanyan", "kang" }));
		set("title", HIW"小王爷"NOR);
        set("gender", "男性");
        set("age", 18);
        set("str", 25);
        set("dex", 100);
        set("long", "他面如冠玉，真是一个翩翩浊世佳公子。\n");
        set("combat_exp", 600000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("claw", 200);
        set_skill("force", 60);
        set_skill("sword", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
		set_skill("jiuyin-baiguzhao",200);
		set_skill("xiantian-gong",60);
        set_skill("jinyan-gong",60);
		map_skill("claw","jiuyin-baiguzhao");
		map_skill("force","xiantian-gong");
        map_skill("dodge","jinyan-gong");
		prepare_skill("claw","jiuyin-baiguzhao");
        set("neili", 400); 
        set("max_neili", 400);
        set("max_qi",50000);
        set("qi",50000);
        set("jiali", 10);
		set("inquiry", ([
            "name" : "本人就是小王爷完颜康。",
            "师傅" : "我的师傅是长春真人丘处机。",
            "母亲" : "我的母后现在总把自己关在小房间里。",
			"父亲" : "我的父王是大金国太子完颜洪烈。",
            "here" : "这里就是我们大金国的中都北京。",
    
			"不对" :(: ask_kang1 :),
            "娶亲" : (: ask_kang2 :),
			"比武招亲" : (: ask_kang3 :),
        ]) );
		set("chat_chance", 1);
        set("chat_msg", ({
                "完颜康微微笑了笑。\n",
        }) );
		setup();
        carry_object(__DIR__"items/jinpao")->wear();
}

void unconcious()
{
        die();
}

void die()
{
        message_vision("完颜康微微笑了笑，风度迷倒万千少女。\n",environment(this_object()));
        this_object()->fullme();
        return;
}


int bwzq()
{
	command("ask hongyi nvzi about 比武招亲");
    return 1;
}

int ask_kang1()
{
	object me=this_player();
	if (!me->query_temp("shediaoquest/askkang1"))
	{
		message_vision(HIW"完颜康似乎不明白你是什么意思。\n"NOR,me);
		return 1;
	}
	else
	{
		message_vision(HIW"完颜康一呆，随即笶道：“要怎样干才对阿？”\n"NOR,me);
        tell_object(me,"你心中暗想：你既然赢了，就应该"+HIR"娶亲"+NOR"。\n");
		me->set_temp("shediaoquest/askkang2",1);
		return 1;
	}
}

int ask_kang2()
{
	object me=this_player();
	if (!me->query_temp("shediaoquest/askkang2"))
	{
		message_vision(HIW"完颜康似乎不明白你是什么意思。\n"NOR,me);
		return 1;
	}
	else
	{
		message_vision(HIW"完颜康侧过了头，笶吟吟的道：“要是我不娶呢？”\n"NOR,me);
        tell_object(me,"你心中暗想：你不愿娶亲，干嘛要来"+HIG"比武招亲"+NOR"。\n");
		me->set_temp("shediaoquest/askkang3",1);
		return 1;
	}
}

int ask_kang3()
{
	object me=this_player();
	if (!me->query_temp("shediaoquest/askkang3"))
	{
		message_vision("完颜康似乎不明白你是什么意思。\n",me);
		return 1;
	}
	else
	{
		message_vision("完颜康脸色一沉，道：“你这小子来多管闲事，要想怎地？”\n",me);
		me->delete_temp("shediaoquest");
		command("consider "+me->query("id"));
		remove_call_out("attack1");
		call_out("attack1",4,me);
		return 1;
	}
}

int visit()
{
    command("hi");
    return 1;
}

int chit()
{
    command("say 我乃玉树临风小王爷完颜康是也。");
    return 1;
}

int attack1(object me)
{
	object ob=this_object();
	int i;
	int exp,exp2,lv;
	lv=10;
	if (!me)
	return 1;
	exp = me->query("combat_exp");
	exp2=exp*10;
	while (lv*lv*lv<exp2)
	{
		lv=lv+10;
	}
	lv=lv*3/2;
	ob->set("combat_exp", exp*2);
	ob->set_skill("claw", lv);
    ob->set_skill("force", lv);
    ob->set_skill("sword", lv);
    ob->set_skill("dodge", lv);
    ob->set_skill("parry", lv);
	ob->set_skill("jiuyin-baiguzhao",lv);
	ob->set_skill("xiantian-gong",lv);
    ob->set_skill("jinyan-gong",lv);
	ob->map_skill("claw","jiuyin-baiguzhao");
	ob->map_skill("force","xiantian-gong");
    ob->map_skill("dodge","jinyan-gong");
	ob->prepare_skill("claw","jiuyin-baiguzhao");
	COMBAT_D->do_attack(ob, me, query_temp("weapon"), 1);
	remove_call_out("attack2");
	call_out("attack2",2,me,ob);
	return 1;
}

int attack2(object me,object ob)
{
	if (me)
	{
	if (me->query("qi")<me->query("max_qi")/10 || me->query("qi")<0)
	{
		tell_object(me,HIW"完颜康笑道：“这点本事也敢学人家充英雄？”\n"NOR);
		tell_object(me,"你知道自己不是完颜康对手，灰溜溜地离开了。\n");
		me->delete_temp("shediaoquest");
		me->move("/d/beijing/changjie");
		return 1;
	}
	else
	{
		tell_object(me,HIW"完颜康笑道：“有点意思，再接我一招试试？”\n"NOR);
		COMBAT_D->do_attack(ob, me, query_temp("weapon"), 1);
		remove_call_out("attack3");
		call_out("attack3",2,me,ob);
		return 1;
	}
	}
}

int attack3(object me,object ob)
{
	if (me)
	{
	if (me->query("qi")<me->query("max_qi")/10 || me->query("qi")<0)
	{
		tell_object(me,HIW"完颜康笑道：“这点本事也敢学人家充英雄？”\n"NOR);
		tell_object(me,"你知道自己不是完颜康对手，灰溜溜地离开了。\n");
		me->delete_temp("shediaoquest");
		me->move("/d/beijing/changjie");
		return 1;
	}
	else
	{
		tell_object(me,HIW"完颜康笑道：“有点意思，再接我一招试试？”\n"NOR);
		COMBAT_D->do_attack(ob, me, query_temp("weapon"), 1);
		remove_call_out("attack4");
		call_out("over",1,me,ob);
		return 1;
	}
	}
}

int over(object me,object ob)
{
    object baoshi = new("/obj/gem/gem");
	string gem;
	int i,e_reward;
    // object kongdi=load_object("/u/huoyu/11/kongdi"); //测试
	if (!me)
	{
        destruct(this_object());
        return 1;
    }
	if (me->query("qi")<0)
	{
		tell_object(me,HIW"完颜康笑道：“这点本事也敢学人家充英雄？”\n"NOR);
		tell_object(me,"你知道自己不是完颜康对手，灰溜溜地离开了。\n");
		me->delete_temp("shediaoquest");
		me->move("/d/beijing/changjie");
        destruct(this_object());
		return 1;
	}
	else
	{
		tell_object(me,HIW"完颜康不可置信地看着你。\n"NOR);
		tell_object(me,"完颜康在众家丁护持下狼狈地离开了。\n");
        if (me->query("shediaoquest/bwzq"))
        {
            return 1;
        }
        me->set("shediaoquest/bwzq",1);
        e_reward=bonus(me,6000);
        me->add("combat_exp",e_reward);
        tell_object(me,HIC"完成射雕主线任务【比武招亲】，你被奖励了"+chinese_number(e_reward)+"点经验！\n"NOR);
	    if (me->query("combat_exp")<10000000)
	    {
		    i= random(20);
		    if (i < 3) gem = "yan";
		    else if (i < 6) gem = "mu";
		    else if (i < 9) gem = "sui";
		    else if (i < 12) gem = "jin";
		    else if (i < 15) gem = "bing";
		    else if (i < 16) gem = "gu";
		    else if (i < 17) gem = "yu";
		    else if (i < 18) gem = "jiao";
		    else gem = "jia";
		    baoshi->set_level(8335,9940,gem);    //3级及以上
		    baoshi->move(me);
            tell_object(me,"完颜康走得匆忙，从身上掉下一块宝石。\n");
            CHANNEL_D->do_channel(this_object(), "rumor", me->name(1) +"比武招亲中，捡到"+baoshi->name()+"一枚!");
            CHANNEL_D->do_channel(this_object(), "sys", me->name(1) +"比武招亲中，获得"+baoshi->name()+"一枚!"); 
            log_file("static/skf",sprintf("%s(%s) 在%s比武招亲中获得"+baoshi->name()+"一枚！\n",  
            me->query("name"),me->query("id"),ctime(time())));
            me->set("shediaoquest/bwzq",1);
            destruct(this_object());
            return 1;
	    }
	    else
	    {
		    i= random(20);
            if (i < 4) gem = "yan";
            else if (i < 8) gem = "mu";
            else if (i < 12) gem = "sui";
            else if (i < 16) gem = "jin";
            else gem = "bing";
            baoshi->set_level(9446,9994,gem);    //4级及以上,五行。
            baoshi->move(me);
            tell_object(me,"完颜康走得匆忙，从身上掉下一块宝石。\n");
            CHANNEL_D->do_channel(this_object(), "rumor", me->name(1) +"比武招亲中，捡到"+baoshi->name()+"一枚!");
            CHANNEL_D->do_channel(this_object(), "sys", me->name(1) +"比武招亲中，获得"+baoshi->name()+"一枚!"); 
            log_file("static/skf",sprintf("%s(%s) 在%s比武招亲中获得"+baoshi->name()+"一枚！\n",  
            me->query("name"),me->query("id"),ctime(time())));
            me->set("shediaoquest/bwzq",1);
            // call_other(kongdi,"reopen");
            destruct(this_object());
            return 1;
	    }
		
	}
}