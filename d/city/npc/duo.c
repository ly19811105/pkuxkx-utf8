// 多尔衮

#include <ansi.h>
#include <title.h>
inherit NPC;
int ask_finish();
int ask_job();
int ask_fail();
int ask_convert();
void create()
{
        set_name(HIR"爱新觉罗.多尔衮"NOR, ({ "duo ergun", "duo"}));
        set("gender", "男性");
        set("age", 30+random(7));
        set("str", 40);
        set("dex", 20);
        set("long", "他是大名鼎鼎的大清摄政王多尔衮。\n");
        set("combat_exp", 1000000);
        set("shen_type", 1);
        set("attitude", "peaceful");
		set("uni_target",1);
		set("skfxiang",1);
        set_skill("unarmed", 100);
        set_skill("force", 100);
        set_skill("sword", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);
		set("skfnokill",1);
		set("qi", 1000); 
		set("max_qi", 1000); 
        set("neili", 800); 
        set("max_neili", 800);
        set("jiali", 10);
		set("inquiry", ([
            "问计" : (: ask_job :),
            "任务" : (: ask_job :),
			"job" : (: ask_job :),
            "兑换" : (: ask_convert :),
			"convert" : (: ask_convert :),
            "复命" : (: ask_finish :),
            "finish" : (: ask_finish :),
            "失败" : (: ask_fail :),
            "fail" : (: ask_fail :),

            
       	]) );
        set("family/family_name","朝廷");
        setup();
		carry_object(__DIR__"items/cloth")->wear();
		carry_object(__DIR__"items/sword")->wield();
}

void init()
{
	add_action("do_kill", ({ "kill", "hit"}));
}

int jobreset()
{
    this_object()->delete("jobgiven");
    return 1;
}

int ask_convert()
{
    object me=this_player();
    int getnum,zs;
    if (!me->query("chaoting/wang")&&!me->query("chaoting/jiawang"))
    {
        tell_object(me,"多尔衮道：你是哪边冒出来的无名小卒？\n");
        return 1;
    }
    if (me->is_busy() || me->is_fighting())
	{
		tell_object(me,"你正忙着哪！\n");
        return 1;
    }
    if (!me->query("zhusantimes"))
    {
        tell_object(me,"你好像没啥可以兑换的东西。\n");
        return 1;
    }
    
        getnum=(int)me->query("zhusantimes")*9/4+random(3);
        zs=(int)me->query("zhusantimes");
        me->set("zhusantimes",0);
        me->add("chaoting/skf",getnum);
        tell_object(me,HIC"你把之前刺探史可法大营的"+chinese_number(zs)+"点功绩转换成"+chinese_number(getnum)+"点大清功勋度。\n"NOR);
        return 1;
}


int ask_fail()
{
    object me=this_player();
    object mudiao;
    if (!me->query("chaoting/wang")&&!me->query("chaoting/jiawang"))
    {
        tell_object(me,"多尔衮道：你是哪边冒出来的无名小卒？\n");
        return 1;
    }
    if (!me->query_temp("skf/ct"))
    {
        tell_object(me,"多尔衮道：我叫你干什么了吗？\n");
        return 1;
    }
    if (me->query_temp("skf/killnumber")>=100)
    {
        tell_object(me,"多尔衮道：你在开玩笑吗？你不是杀够一百个难民了？\n");
        return 1;
    }
    else
    {
        tell_object(me,"多尔衮道：娘的，"+me->query("name")+"你也太菜了吧？退下！\n");
        tell_object(me,HIC"你的功勋度下降了一点！\n"NOR);
        if (present("mu diao",me))
        {
            mudiao=present("mu diao",me);
            destruct(mudiao);
        }
        me->add("chaoting/skf",-1);
        me->delete("skf/jobasked");
        return 1;
    }
}



int ask_finish()
{
    object me=this_player();
    object mudiao;
    if (!me->query("chaoting/wang")&&!me->query("chaoting/jiawang"))
    {
        tell_object(me,"多尔衮道：你是哪边冒出来的无名小卒？\n");
        return 1;
    }
    if (!me->query_temp("skf/ct"))
    {
        tell_object(me,"多尔衮道：我叫你干什么了吗？\n");
        return 1;
    }
    if (me->query_temp("skf/killnumber")<100)
    {
        tell_object(me,"多尔衮道：你杀够一百个难民了吗？\n");
        return 1;
    }
    else
    {
        tell_object(me,"多尔衮道：嘿嘿，"+me->query("name")+"不愧为我多尔衮的臂助啊。\n");
        tell_object(me,"你的功劳我不会忘记，回京之后重重有赏！\n");
        tell_object(me,HIC"你的功勋度增加了五点！\n"NOR);
        command("mp "+me->query("name")+"在密林边缘屠杀明国难民一百余人，特赐嘉奖！");
        //CHANNEL_D->do_channel(this_object(), "chat", sprintf("%s在密林边缘屠杀明国难民一百余人，特赐嘉奖！\n",me->query("name")));
        if (present("mu diao",me))
        {
            mudiao=present("mu diao",me);
            destruct(mudiao);
        }
        me->add("chaoting/skf",5);
        me->delete_temp("skf");
        me->delete("skf");
        
        return 1;
    }
}

int ask_job()
{
    object ob=this_object();
    object me=this_player();
    object mudiao,qb;
    int i;
    if (!me->query("chaoting/wang")&&!me->query("chaoting/jiawang"))
    {
        tell_object(me,"多尔衮道：你是哪边冒出来的无名小卒？\n");
        return 1;
    }
    if (!me->query_temp("skf/skf-ct"))
    {
        tell_object(me,"多尔衮道：你先尝试去骗取史可法的信任，最后的办法莫过于去帮助他转移难民。\n");
        return 1;
    }
    if (me->is_busy() || me->is_fighting())
	{
		tell_object(me,"你正忙着哪！\n");
        return 1;
    }
    if (ob->query("jobgiven"))
    {
        tell_object(me,"多尔衮道：今天我有点累了，你迟点再来吧。\n");
        return 1;
    }
    else
    {
        tell_object(me,"多尔衮道：既然如此，你且领一批斥候，狠狠地狙杀逃难的明国人。\n");
        tell_object(me,"我且给你一个木雕，杀一个人，在上面刻一道痕迹，杀满一百个人就回来用木雕复命把。\n");
        tell_object(me,"斥候队在前面迎着你，你且出发吧。\n");
        tell_object(me,BLINK HIR"最后随便和你说一句，你知道其实我族绝门棍最强的威力其实发挥在战场上吗？\n"NOR);
        mudiao=new(__DIR__"obj/mudiao");
        mudiao->set("owner",me->query("id"));
        mudiao->move(me);
        message_vision("$N交给$n一件木雕。\n",ob,me);
        me->set_temp("skf/ct",1);
        me->set_temp("skf/qingstart",time());
        me->move("/d/city/duo-path1");
        for (i=0;i<2+random(4);i++)
        {
            qb=new(__DIR__"qingbing1-2");
            qb->copy(me);
            qb->set("lord",me->query("id"));
            qb->move("/d/city/duo-path1");
            qb->gen(me);
        }
        ob->set("jobgiven",1);
        command("mp "+me->query("name")+"带领一队女真精兵，准备在密林附近狙杀明国难民。");
        //message("chat",HIM"【谣言】某人："+me->query("name")+"带领一队女真细作，准备在密林附近狙杀难民。\n"+NOR,users());
        remove_call_out("jobreset");
        call_out("jobreset",600);
        return 1;
    }
	
}


int bonus(object me)
{
	string* title=({"礼亲王","睿亲王","豫亲王","郑亲王","肃亲王","庄亲王","克勤郡王","顺承郡王",});
	string* color=({HIR,RED,HIY,YEL,HIB,BLU,HIG,GRN,HIC,CYN,MAG,HIM,HIW,WHT});
	string title1=title[random(sizeof(title))];
	string color1=color[random(sizeof(color))];
	string color2=color[random(sizeof(color))];
    object baoshi;
    int i;
    string gem;
    if (me->query("chaoting/jiawang")||me->query("chaoting/wang")) //继续做任务的奖励
        {
            me->add("chaoting/catch_feizei",5);
            baoshi = new("/obj/gem/gem");
            i = random(20);
			if (i < 3) gem = "yan";
			else if (i < 6) gem = "mu";
			else if (i < 9) gem = "sui";
			else if (i < 12) gem = "jin";
			else if (i < 15) gem = "bing";
			else if (i < 16) gem = "gu";
			else if (i < 17) gem = "yu";
			else if (i < 18) gem = "jiao";
			else gem = "jia";
            baoshi->set_level(8000,9999,gem);    //3级及以上
			baoshi->move(me);
		    CHANNEL_D->do_channel(this_object(), "chat", me->name(1) +"在为大清立下汗马功劳后，奖励"+baoshi->name()+"一枚!");
			CHANNEL_D->do_channel(this_object(), "sys_misc", me->name(1) +"在为大清立下汗马功劳后，奖励"+baoshi->name()+"一枚!"); 
			log_file("static/skf",sprintf("%s(%s) 在%s朱三太子(清朝)任务中获得"+baoshi->name()+"一枚！\n",  
			me->query("name"),me->query("id"),ctime(time()))); 
            tell_object(me,"多尔衮道：你立下此等大功，我不会亏待你的。\n");
            return 1;
        }
	if( me->query("family/family_name")=="朝廷" && (int)me->query("pin") == 1 && me->query("combat_exp")>50000000 && !me->query("chushi"))
		{
			me->set("title",color1+"大清铁帽子王 "NOR+color2+title1+NOR);
			//title系统记录玩家title by seagate@pkuxkx
			me->set_title(({TITLE_QUEST1, TITLE_QUEST2, TITLE_QUEST3}), color1+"大清铁帽子王 "NOR+color2+title1+NOR, "大清");

			CHANNEL_D->do_channel(this_object(), "chat", me->name(1) +"多年卧底，终于助我大清攻克扬州，特封"+color2+title1+"。\n"NOR);
            me->set("chaoting/wang",1);
            return 1;
		}
    if (me->query("family/family_name")=="朝廷" && (int)me->query("pin") == 1 && me->query("combat_exp")>50000000)
        {
            me->set("title",color1+"大清铁帽子王 "NOR+color2+title1+NOR);
			//title系统记录玩家title by seagate@pkuxkx
			me->set_title(({TITLE_QUEST1, TITLE_QUEST2, TITLE_QUEST3}), color1+"大清铁帽子王 "NOR+color2+title1+NOR, "大清");
				
			CHANNEL_D->do_channel(this_object(), "chat", me->name(1) +"多年卧底，终于助我大清攻克扬州，特封"+color2+title1+"。\n"NOR);
            me->set("chaoting/jiawang",1);
            return 1;
        }
    else
    {
            baoshi = new("/obj/gem/gem");
            i = random(20);
			if (i < 3) gem = "yan";
			else if (i < 6) gem = "mu";
			else if (i < 9) gem = "sui";
			else if (i < 12) gem = "jin";
			else if (i < 15) gem = "bing";
			else if (i < 16) gem = "gu";
			else if (i < 17) gem = "yu";
			else if (i < 18) gem = "jiao";
			else gem = "jia";
            baoshi->set_level(5000,9999,gem);    //3级及以上
			baoshi->move(me);
		    CHANNEL_D->do_channel(this_object(), "chat", me->name(1) +"在为大清立下汗马功劳后，奖励"+baoshi->name()+"一枚!");
			CHANNEL_D->do_channel(this_object(), "sys_misc", me->name(1) +"在为大清立下汗马功劳后，奖励"+baoshi->name()+"一枚!"); 
			log_file("static/skf",sprintf("%s(%s) 在%s朱三太子(清朝)任务中获得"+baoshi->name()+"一枚！\n",  
			me->query("name"),me->query("id"),ctime(time()))); 
            tell_object(me,"多尔衮道：你立下此等大功，我不会亏待你的。\n");
            return 1;
    }
}

int accept_object(object me, object ob)
{
	if( ob->query("id") != "qing bao")
	return notify_fail(this_object()->query("name")+"转过身去，脸色阴沉。\n");
	if (ob->query("owner")!= me->query("id"))
	return notify_fail(this_object()->query("name")+"怒道：叫去刺探情报，你就随便找来份应付我？\n");
		else
		{
			if (me->query("skfxiang")<=25)
			{
				command("say 嗯，你卧底时日尚浅，打探不到太核心的情报也不奇怪。\n");
				return 1;
			}
			else
			{
				command("faintx "+me->query("id"));
				command("say 阁下真是我大清骄傲中的骄傲，栋梁中的栋梁啊。");
				me->add("zhusan",-1);
				me->delete_temp("zhusan");
				me->add("skfxiang",-25);
				bonus(me);
				return 1;
			}
		}
}

int do_kill(string arg)
{
	object me=this_player();
	object room=environment();
	if(arg=="duo"||arg =="duo ergun")
		{
			if (userp(me))
				{
					message_vision(HIW"多尔衮冷冷地看着你，你低下了头再不敢乱动！\n"NOR, me);
					return 1;
				}
		}
}