//Zine Oct 13 2010 铁匠
inherit NPC;
#include <ansi.h>

int ask_bonus();
string* obj = ({

       __DIR__"obj/modaoshi",
       __DIR__"obj/modaoshi",
       __DIR__"obj/modaoshi",
       __DIR__"obj/modaoshi",
       __DIR__"obj/modaoshi",
	   __DIR__"obj/modaoshi2",
       __DIR__"obj/modaoshi2",
       __DIR__"obj/modaoshi2",
	   __DIR__"obj/modaoshi3",
	   
	   
     
});

string* where =({
    "/d/luoyang/mishi1",
    "/d/luoyang/mishi2",
    "/d/luoyang/mishi3",
    "/d/luoyang/mishi4",
    "/d/luoyang/mishi5",
    "/d/luoyang/mishi6",
    "/d/luoyang/mishi7",
    "/d/luoyang/mishi8",
});
string where1=where[random(sizeof(where))];



void create()
{
        set_name("铁匠", ({ "tie jiang"}));
        set("gender", "男性");
        set("age", 35);
        set("long", "一个浑身黝黑的铁匠，看起来再普通不过了。\n");

        set("combat_exp", 7500);
        set("no_get", 1);
        set_skill("unarmed", 35);
        set_skill("force", 35);
        set_skill("dodge", 40);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 40);
        set("shen_type", -1);
        set("inquiry", ([
            "name" : "英雄不问出处，快帮我挡住他们，别问啦。",
            "here" : "这里是哪你都不知道，真是笨蛋。",
			"奖励" : (: ask_bonus :),
            "bonus" : (: ask_bonus :),
			
       	]) );
		
        set("chat_chance", 100);
	    set("chat_msg", ({
		(: random_move :),
	    }) );
        setup();
        call_out("bonus",120);
        call_out("moving",1);
}

void init()
{
    add_action("do_follow","follow");
}

int moving()
{
    if (this_object()->query("bonus"))
    {
        return 1;
    }
    else
    {
        this_object()->random_move();
        remove_call_out("moving");
        call_out("moving",4+random(4));
        return 1;
    }
}

int start_busy(int busy) 
{return 0;}

int add_busy(int busy) 
{return 0;}


int do_follow(string arg)
{
    object me=this_player();
    if (!arg)
    {
        tell_object(me,"你要跟随谁？\n");
        return 1;
    }
    else
    {
        if (arg=="tie jiang" && userp(me))
        {
            tell_object(me,"铁匠受惊了，跑得飞快，你根本追不上！\n");
            return 1;
        }
    }
}

int dest()
{
    tell_room(environment(),"铁匠突然想起什么，转身失去了踪迹。\n");
    destruct(this_object());
    return 1;
}

int bonus()
{
    this_object()->set("bonus",1);
    call_out("dest",100);
}

int ask_bonus()
{
    object bonus;
    object shi;
    object me=this_player();
    object ob=this_object();
    object loc=load_object(where1);
    int i;
    object* all=all_inventory(environment());
    
    if (!ob->query("bonus"))
    {
        command("b4 "+ me->query("id"));
        return 1;
    }
    else
    {
        bonus= new( obj[random(sizeof(obj))] );
        if (bonus)
        {
            bonus->move(loc);
        }
        tell_room(loc,"地上有块不起眼的石头动了动。\n");
        for (i=0;i<sizeof(all);i++)
        {
            if (!userp(all[i]))
            {
                continue;
            }
            if (!all[i]->query_temp("tiejiangjob/ticket"))
            {
                continue;
            }
            else
            {
                shi= new(__DIR__"obj/modaoshi0");
                if (shi)
                {
                    shi->move(all[i]);
                    all[i]->set("tiejiangjob_last_time",time());
                    tell_object(all[i],"铁匠给了你一块石头，不知道有什么作用。\n");
                }
            }
        }
        CHANNEL_D->do_channel(this_object(), "rumor", me->name(1) +"等众人在帮助铁匠度过危机后，发现"+bonus->name()+"一枚!");
		CHANNEL_D->do_channel(this_object(), "sys_misc", me->name(1) +"等众人在帮助铁匠度过危机后，发现"+bonus->name()+"一枚!"); 
		log_file("static/tiejiang",sprintf("%s(%s) 等众人在%s帮助铁匠度过危机后，发现"+bonus->name()+"一枚！\n",  
				me->query("name"),me->query("id"),ctime(time()))); 
        tell_room(environment(),"铁匠突然想起什么，转身失去了踪迹。\n");
        destruct(this_object());
        return 1;
    }
}

