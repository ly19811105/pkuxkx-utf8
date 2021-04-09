//
//create bye cuer
//modified by Zine EM newbie job
#include <ansi.h>
inherit NPC;
inherit "/inherit/char/silver.c";
#include "/d/emei/bonus.h"
void init();
int adv();
int do_ling(string);
int ask_job();
int ask_fail();
int ask_finish();
int adv();
void create()
{
        set_name("静和师太", ({
                "jinghe shitai",
                "jinghe",
                "shitai",
        }));
        set("long",
                "她是一位中年师太。\n"
        );
        set("gender", "女性");
        set("attitude", "friendly");
        set("class", "bonze");
        set("age", 40);
        set("shen_type", 1);
        set("str", 21);
        set("int", 25);      
        set("con", 20);
        set("dex", 25);
        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 70);
        set("combat_exp", 150000);
        set("score", 100);
		set("bonus",1+random(2));
        set_skill("force", 100);
        set_skill("linji-zhuang", 100);
        set_skill("dodge", 100);
        set_skill("zhutian", 100);
        set_skill("fuliu-jian", 100);
        set_skill("sword", 100);
        set_skill("parry", 100);
        set_skill("mahayana", 100);
        set_skill("literate", 100);
        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian");
        map_skill("sword", "fuliu-jian");
        map_skill("parry", "fuliu-jian");
        prepare_skill("sword", "fuliu-jian");
        
        set("inquiry", ([
		"香火" : (: ask_silver :),
		"help" : (: ask_job :),
            "帮助" : (: ask_job :),
            "fail" : (: ask_fail :),
            "失败" : (: ask_fail :),
            "finish": (: ask_finish :),
            "完成": (: ask_finish :),
        ]));
        
	set("silver_name", "香火"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "fuliu-jian"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "本派香火鼎盛，以后每月你可来找我领取一份。"); //第一次打听例银的时候说的话
        set("msg_silver_score", "$N双手合十，道：「本门发扬光大，全靠弟子齐心。」\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N双手合十，道：「本门剑法独树一帜，当勤学苦练。」\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N双手合十，道：「本门发扬光大，武功不可轻视。」\n"); //由于提升经验而领取例银时的描述\n


        create_family("峨嵋派", 4, "弟子");
        setup();
        carry_object(__DIR__"obj/changjian")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
        call_out("adv",1);
}

int adv()
{
    int i;
    object *ob;
	if (!environment()||base_name(environment())!="/d/emei/dian4")
	{
		return 1;
	}
    ob = filter_array(children(USER_OB), (: userp :));
    ob = filter_array(ob, (: environment :));
    ob = filter_array(ob, (: TASK_D->place_belong(environment($1))==TASK_D->place_belong(environment(this_object())) :) );
    for (i=0;i<sizeof(ob);i++)
    {
        if (ob[i]->query("family/family_name")=="峨嵋派"&&ob[i]->query("combat_exp")<100000&&time()-ob[i]->query_temp("广告")>600)
        {
            ob[i]->set_temp("广告",time());
            command("tell "+ob[i]->query("id")+" 峨嵋新手任务已经开放，你可以到我这里接到新手任务。\n");
        }
    }
	remove_call_out("adv");
    call_out("adv",400+random(100));
    return 1;
}

void init()
{
   add_action("do_ling","ling");
}                               

int ask_fail()
{
	object me=this_player();
	object ob=this_object();
	if (me->is_busy()||me->is_fighting())
	{
		tell_object(me,"你正忙着呢。\n");
		return 1;
	}
	if (ob->is_busy()||ob->is_fighting())
	{
		tell_object(me,ob->name()+"正忙着呢。\n");
		return 1;
	}
	if (me->query("family/family_name")!="峨嵋派")
	{
		command("say 阁下不是峨嵋派弟子，请回吧。");
		return 1;
	}
	if (!me->query("emnewbiejob/start"))
	{
		command("say 我没有给你任务啊，你是不是记错了？");
		return 1;
	}
	if (me->query("emnewbiejob/newbiestart"))
	{
		command("say 没完成？没事没事，熟了就快了。");
		me->delete("emnewbiejob/start");
        me->delete("emnewbiejob/newbiestart");
		me->delete_temp("emnewbiejob");
		me->set("emnewbiejob/starttime",time());
		return 1;
	}
    if (me->query("emnewbiejob/skill/start"))
    {
        command("say 没完成？没事没事，熟了就快了。");
		me->delete("emnewbiejob/start");
        me->delete("emnewbiejob/skill/start");
		me->delete_temp("emnewbiejob");
		me->set("emnewbiejob/starttime",time());
		return 1;
    }
	else
	{
		command("say 谁交给你的任务，就找谁去放弃吧。");
		return 1;
	}

}

int ask_finish()
{
	object me=this_player();
	object ob=this_object();
    int sk_ljz,sk_ztb,sk_jdz,sk_yxd,sk_tgz,sk_flj;
	if (me->is_busy()||me->is_fighting())
	{
		tell_object(me,"你正忙着呢。\n");
		return 1;
	}
	if (ob->is_busy()||ob->is_fighting())
	{
		tell_object(me,ob->name()+"正忙着呢。\n");
		return 1;
	}
	if (me->query("family/family_name")!="峨嵋派")
	{
		command("say 阁下不是峨嵋派弟子，请回吧。");
		return 1;
	}
	if (!me->query("emnewbiejob/start"))
	{
		command("say 我没有给你任务啊，你是不是记错了？");
		return 1;
	}
    if (me->query_temp("emnewbiejob/jinghe/dazuo"))
    {
        if ((int)me->query("max_neili")-(int)me->query_temp("emnewbiejob/jinghe/max_nl")<(int)me->query_temp("emnewbiejob/jinghe/dazuo"))
        {
            command("say 你好像没打坐到我要求的内力吧？");
            return 1;
        }
        else if ((int)me->query("max_neili")-(int)me->query_temp("emnewbiejob/jinghe/max_nl")==(int)me->query_temp("emnewbiejob/jinghe/dazuo"))
        {
            command("say 一丝不差，厉害啊！");
            bonus(me);
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
        else
        {
            command("say 不错，但是你对内力的控制还不够精确，还需要努力。");
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
    }
    if (me->query_temp("emnewbiejob/jinghe/tuna"))
    {
        if ((int)me->query("max_jingli")-(int)me->query_temp("emnewbiejob/jinghe/max_jl")<(int)me->query_temp("emnewbiejob/jinghe/tuna"))
        {
            command("say 你好像没吐纳到我要求的精力吧？");
            return 1;
        }
        else if ((int)me->query("max_jingli")-(int)me->query_temp("emnewbiejob/jinghe/max_jl")==(int)me->query_temp("emnewbiejob/jinghe/tuna"))
        {
            command("say 一丝不差，厉害啊！");
            bonus(me);
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
        else
        {
            command("say 不错，但是你对精力的控制还不够精确，还需要努力。");
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
    }
            sk_ljz=(int)me->query_skill("linji-zhuang",1);
            sk_ztb=(int)me->query_skill("zhutian",1);
            sk_jdz=(int)me->query_skill("jinding-mianzhang",1);
            sk_yxd=(int)me->query_skill("yanxing-dao",1);
            sk_tgz=(int)me->query_skill("tiangang-zhi",1);
            sk_flj=(int)me->query_skill("fuliu-jian",1);
    if (me->query_temp("emnewbiejob/jinghe/ljz"))
    {
        if (sk_ljz-(int)me->query_temp("emnewbiejob/jinghe/sk_ljz")<(int)me->query_temp("emnewbiejob/jinghe/ljz"))
        {
            command("say 你好像没学到我要求的级别吧？");
            return 1;
        }
        else if (sk_ljz-(int)me->query_temp("emnewbiejob/jinghe/sk_ljz")==(int)me->query_temp("emnewbiejob/jinghe/ljz"))
        {
            command("say 一丝不差，厉害啊！");
            bonus(me);
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
        else
        {
            command("say 不错，但是你学习的能力还不够精确，还需要努力。");
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
    }
    if (me->query_temp("emnewbiejob/jinghe/ztb"))
    {
        if (sk_ztb-(int)me->query_temp("emnewbiejob/jinghe/sk_ztb")<(int)me->query_temp("emnewbiejob/jinghe/ztb"))
        {
            command("say 你好像没学到我要求的级别吧？");
            return 1;
        }
        else if (sk_ztb-(int)me->query_temp("emnewbiejob/jinghe/sk_ztb")==(int)me->query_temp("emnewbiejob/jinghe/ztb"))
        {
            command("say 一丝不差，厉害啊！");
            bonus(me);
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
        else
        {
            command("say 不错，但是你学习的能力还不够精确，还需要努力。");
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
    }
    if (me->query_temp("emnewbiejob/jinghe/jdz"))
    {
        if (sk_jdz-(int)me->query_temp("emnewbiejob/jinghe/sk_jdz")<(int)me->query_temp("emnewbiejob/jinghe/jdz"))
        {
            command("say 你好像没学到我要求的级别吧？");
            return 1;
        }
        else if (sk_jdz-(int)me->query_temp("emnewbiejob/jinghe/sk_jdz")==(int)me->query_temp("emnewbiejob/jinghe/jdz"))
        {
            command("say 一丝不差，厉害啊！");
            bonus(me);
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
        else
        {
            command("say 不错，但是你学习的能力还不够精确，还需要努力。");
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
    }
    if (me->query_temp("emnewbiejob/jinghe/tgz"))
    {
        if (sk_tgz-(int)me->query_temp("emnewbiejob/jinghe/sk_tgz")<(int)me->query_temp("emnewbiejob/jinghe/tgz"))
        {
            command("say 你好像没学到我要求的级别吧？");
            return 1;
        }
        else if (sk_tgz-(int)me->query_temp("emnewbiejob/jinghe/sk_tgz")==(int)me->query_temp("emnewbiejob/jinghe/tgz"))
        {
            command("say 一丝不差，厉害啊！");
            bonus(me);
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
        else
        {
            command("say 不错，但是你学习的能力还不够精确，还需要努力。");
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
    }
    if (me->query_temp("emnewbiejob/jinghe/yxd"))
    {
        if (sk_yxd-(int)me->query_temp("emnewbiejob/jinghe/sk_yxd")<(int)me->query_temp("emnewbiejob/jinghe/yxd"))
        {
            command("say 你好像没学到我要求的级别吧？");
            return 1;
        }
        else if (sk_yxd-(int)me->query_temp("emnewbiejob/jinghe/sk_yxd")==(int)me->query_temp("emnewbiejob/jinghe/yxd"))
        {
            command("say 一丝不差，厉害啊！");
            bonus(me);
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
        else
        {
            command("say 不错，但是你学习的能力还不够精确，还需要努力。");
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
    }
    if (me->query_temp("emnewbiejob/jinghe/flj"))
    {
        if (sk_flj-(int)me->query_temp("emnewbiejob/jinghe/sk_flj")<(int)me->query_temp("emnewbiejob/jinghe/flj"))
        {
            command("say 你好像没学到我要求的级别吧？");
            return 1;
        }
        else if (sk_flj-(int)me->query_temp("emnewbiejob/jinghe/sk_flj")==(int)me->query_temp("emnewbiejob/jinghe/flj"))
        {
            command("say 一丝不差，厉害啊！");
            bonus(me);
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
        else
        {
            command("say 不错，但是你学习的能力还不够精确，还需要努力。");
		    me->delete("emnewbiejob/start");
            me->delete("emnewbiejob/skill/start");
		    me->delete_temp("emnewbiejob");
            return 1;
        }
    }
	if (me->query_temp("emnewbiejob/newbie/finish"))
	{
		command("say 这么快就静下心来了？你真是有佛缘啊。");
		bonus(me);
		me->delete("emnewbiejob/start");
		me->delete_temp("emnewbiejob");
		return 1;
	}
	else
	{
		command("say 谁交给你的任务，就找谁去复命吧。");
		return 1;
	}
}

int ask_job()
{
	object me=this_player();
	object ob=this_object();
	string *place=({"千佛庵大殿","文殊殿","毗卢殿","万年庵","报国寺大殿","伏虎寺"});
	string *tasklist=({"静慈","西廊禅房静字辈师太","杂役尼姑"});
	int n=random(sizeof(place));
	int max_nl,max_jl,limit_nl,limit_jl,sk_ljz,sk_ztb,sk_jdz,sk_yxd,sk_tgz,sk_flj,limit_sk;
	if (me->is_busy()||me->is_fighting())
	{
		tell_object(me,"你正忙着呢。\n");
		return 1;
	}
	if (ob->is_busy()||ob->is_fighting())
	{
		tell_object(me,ob->name()+"正忙着呢。\n");
		return 1;
	}
	if (me->query("family/family_name")!="峨嵋派")
	{
		command("say 我派香火鼎盛，不需要外派弟子帮忙，阁下请回吧。");
		return 1;
	}
	if (me->query("emnewbiejob/start"))
	{
		command("say 你接了任务就快去完成吧。");
		return 1;
	}
	if (me->query("combat_exp")>=18000&& time()-me->query("emnewbiejob/starttime")<180)
	{
		command("say 你刚刚做完任务，迟点再来吧。");
		return 1;
	}
	if (me->query("combat_exp")<18000&& time()-me->query("emnewbiejob/starttime")<120)
	{
		command("say 你刚刚做完任务，迟点再来吧。");
		return 1;
	}
	if (me->query_temp("emnewbiejob/newbie/place"))
	{
		command("say 静下心来，一切都会变得很容易。");
		return 1;
	}
	if (me->query("combat_exp")<18000)
	{
		command("say 你刚进我派，其实我派一切以静修为主，你且去"+place[n]+"念段佛经(nianjing)，静下心来吧。");
		me->set("emnewbiejob/start",1);
		me->set("emnewbiejob/starttime",time());
        me->set("emnewbiejob/newbiestart",1);
		me->set_temp("emnewbiejob/newbie/place",place[n]);
		return 1;
	}
	else
	{
		if (me->query("combat_exp")>60000&&!random(10))
		{
			command("say 掌门在招人办事，你且去帮帮她吧。");
			me->set("emnewbiejob/start",1);
			me->set("emnewbiejob/starttime",time());
			me->set_temp("emnewbiejob/miejue/start",1);
            return 1;
		}
        if (random(3))
        {
        
            max_nl=(int)me->query("max_neili");
            max_jl=(int)me->query("max_jingli");
            limit_nl=(int)me->query_skill("force")*10;
            limit_jl=(int)me->query_skill("force",1)*15;
            sk_ljz=(int)me->query_skill("linji-zhuang",1);
            sk_ztb=(int)me->query_skill("zhutian",1);
            sk_jdz=(int)me->query_skill("jinding-mianzhang",1);
            sk_yxd=(int)me->query_skill("yanxing-dao",1);
            sk_tgz=(int)me->query_skill("tiangang-zhi",1);
            sk_flj=(int)me->query_skill("fuliu-jian",1);
            limit_sk=to_int(pow((int)me->query("combat_exp")/100,0.333)*10);
            if (limit_nl-max_nl>20 && random(100)>85)
            {
                n=random(5)+5;
                command("say 你的内力太低，去打坐"+chinese_number(n)+"点内力再回来吧。");
                me->set("emnewbiejob/start",1);
                me->set("emnewbiejob/skill/start",1);
                me->set("emnewbiejob/starttime",time());
                me->set_temp("emnewbiejob/jinghe/dazuo",n);
                me->set_temp("emnewbiejob/jinghe/max_nl",max_nl);
                return 1;
            }
            if (limit_jl-max_jl>20 && random(100)>85)
            {
                n=random(2)+2;
                command("say 你的精力太低，去吐纳"+chinese_number(n)+"点精力再回来吧。");
                me->set("emnewbiejob/start",1);
                me->set("emnewbiejob/skill/start",1);
                me->set("emnewbiejob/starttime",time());
                me->set_temp("emnewbiejob/jinghe/tuna",n);
                me->set_temp("emnewbiejob/jinghe/max_jl",max_jl);
                return 1;
            }
            if (limit_sk-sk_ljz>10 && random(100)>85)
            {
                n=random(3)+2;
                command("say 你的临济十二庄太低了，去学个"+chinese_number(n)+"级再回来吧。");
                me->set("emnewbiejob/start",1);
                me->set("emnewbiejob/skill/start",1);
                me->set("emnewbiejob/starttime",time());
                me->set_temp("emnewbiejob/jinghe/ljz",n);
                me->set_temp("emnewbiejob/jinghe/sk_ljz",sk_ljz);
                return 1;
            }
            if (limit_sk-sk_ztb>10 && random(100)>85)
            {
                n=random(3)+2;
                command("say 你的诸天化身法太低了，去练个"+chinese_number(n)+"级再回来吧。");
                me->set("emnewbiejob/start",1);
                me->set("emnewbiejob/skill/start",1);
                me->set("emnewbiejob/starttime",time());
                me->set_temp("emnewbiejob/jinghe/ztb",n);
                me->set_temp("emnewbiejob/jinghe/sk_ztb",sk_ztb);
                return 1;
            }
            if (limit_sk-sk_jdz>10 && random(100)>85)
            {
                n=random(3)+2;
                command("say 你的金顶绵掌太低了，去练个"+chinese_number(n)+"级再回来吧。");
                me->set("emnewbiejob/start",1);
                me->set("emnewbiejob/skill/start",1);
                me->set("emnewbiejob/starttime",time());
                me->set_temp("emnewbiejob/jinghe/jdz",n);
                me->set_temp("emnewbiejob/jinghe/sk_jdz",sk_jdz);
                return 1;
            }
            if (limit_sk-sk_yxd>10 && random(100)>85)
            {
                n=random(3)+2;
                command("say 你的雁行刀太低了，去练个"+chinese_number(n)+"级再回来吧。");
                me->set("emnewbiejob/start",1);
                me->set("emnewbiejob/skill/start",1);
                me->set("emnewbiejob/starttime",time());
                me->set_temp("emnewbiejob/jinghe/yxd",n);
                me->set_temp("emnewbiejob/jinghe/sk_yxd",sk_yxd);
                return 1;
            }
            if (limit_sk-sk_tgz>10 && random(100)>85)
            {
                n=random(3)+2;
                command("say 你的天罡指太低了，去练个"+chinese_number(n)+"级再回来吧。");
                me->set("emnewbiejob/start",1);
                me->set("emnewbiejob/skill/start",1);
                me->set("emnewbiejob/starttime",time());
                me->set_temp("emnewbiejob/jinghe/tgz",n);
                me->set_temp("emnewbiejob/jinghe/sk_tgz",sk_tgz);
                return 1;
            }
            if (limit_sk-sk_flj>10 && random(100)>85)
            {
                n=random(3)+2;
                command("say 你的回风拂柳剑太低了，去练个"+chinese_number(n)+"级再回来吧。");
                me->set("emnewbiejob/start",1);
                me->set("emnewbiejob/skill/start",1);
                me->set("emnewbiejob/starttime",time());
                me->set_temp("emnewbiejob/jinghe/flj",n);
                me->set_temp("emnewbiejob/jinghe/sk_flj",sk_flj);
                return 1;
            }
		}
		n=random(sizeof(tasklist));
		command("say "+tasklist[n]+"最近事情比较多，你且去帮帮她吧。");
		me->set("emnewbiejob/start",1);
		me->set("emnewbiejob/starttime",time());
		if (n==0)
		{
			me->set_temp("emnewbiejob/jingci/start",1);
		}
		if (n==1)
		{
			me->set_temp("emnewbiejob/jingwen/start",1);
		}
		if (n==2)
		{
			me->set_temp("emnewbiejob/qingjie/start",1);
		}
		return 1;
	}
}
int do_ling(string arg)
{
 object ob = this_object();
 object me = this_player();
 object obj;
 if(!arg || (arg != "zhujian" && arg != "mudao"))
    return notify_fail("你要领什么？\n"); 
 
 if( arg == "zhujian")
    { 
      if(objectp(present("zhujian", this_player())) ) 
         return notify_fail("你已有了，还领什么？\n");
      command("say 好吧，就给你一把竹剑。\n");
      message_vision("$N交给$n一把竹剑。\n", ob, me);
      obj=new(__DIR__"obj/zhujian");
    }  
 if( arg == "mudao")
    { 
      if(objectp(present("mudao", this_player())) ) 
         return notify_fail("你已有了，还领什么？\n");
      command("say 好吧，就给你一把木刀。\n");
      message_vision("$N交给$n一把木刀。\n", ob, me);
      obj=new(__DIR__"obj/mudao");
    }                          
  obj->move(me);
  return 1;
}
