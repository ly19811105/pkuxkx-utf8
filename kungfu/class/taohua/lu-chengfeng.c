#include <ansi.h>
#include <title.h>

inherit NPC;
inherit F_QUESTMASTER;
inherit "/inherit/char/silver.c";
int ask_job();
int ask_shediao();
void create()
{
	set_name("陆乘风",({"lu chengfeng","lu","chengfeng"}));
	set("nickname",HIC"仗义行侠"NOR);
	set("title",GRN"归云庄"NOR+YEL"庄主"NOR);
	set("long","他是一位威风凛凛，面容冷峻的人.\n");
	set("gender","男性");
	set("age",54);
	set("attitute", "peaceful");
	set("shen-type", 1);
	set("str", 25);
	set("int", 28);
	set("con", 30);
	set("dex", 29);
	set("max_qi", 3000);
	set("qi", 3000);
	set("max_jing", 1500);
	set("jing", 1500);
	set("max_neili", 2000);
	set("neili", 2000);
	set("jiali", 150);
	set("combat_exp", 400000);
	set_skill("force", 100);
	set_skill("bihai-shengong", 120);
	set_skill("dodge", 100);
	set_skill("luoying-shenfa", 120);
	set_skill("parry",100);
	set_skill("sword",100);
	set_skill("yuxiao-jian",120);
	set_skill("hand",100);
	set_skill("fuxue-shou",120);
	set_skill("finger",100);
	set_skill("literate",100);
	map_skill("force","bihai-shengong");
	map_skill("dodge","luoying-shenfa");
	map_skill("parry","yuxiao-jianfa");
	map_skill("sword","yuxiao-jian");
	map_skill("hand","fuxue-shou");
	prepare_skill("hand","fuxue-shou");
	create_family("桃花岛",2,"弟子");

        set("inquiry", ([
                "例银" : (: ask_silver :),
                "任务" : (: ask_job :),
                "job" : (: ask_job :),
				"请教" : (: ask_shediao :),
        ]));

        set("sivler_name", "例银"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "literate"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "我陆某既已重回师门，无以图报，唯有以积蓄为门下弟子谋点福利。以后每月都来找我领例银罢。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N命人将一应事项等记了下来。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N命人从书房取来记录，翻了翻。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "一月时间尚未到罢？"); //时间未到不能领取时说的话
        set("msg_silver_paid", "不错，拿着罢。"); //领取成功时说的话

	set("shen_type",1);set("score",20000);setup();
	carry_object("/d/guiyunzhuang/npc/obj/lvshan")->wear();
	carry_object("/d/guiyunzhuang/npc/obj/cleansword")->wield();
	set("chat_chance",5);
	set("chat_msg", ({
		"陆乘风自言自语道：「我自从建立归云庄以来，从没享受过人间福分，如今人过半百，真是岁月似水啊！」\n",
		"陆乘风自言自语道：「师傅当年教我武功，如今报答恩师的唯一方法只有把桃花岛武功发扬光大。」\n"
	}));
}

int aftersaylu(object ob,object me,object huang)
{
	if (!me||!living(me))
	{
		return 1;
	}
	if (!ob||!living(ob))
	{
		return 1;
	}
	if (!huang||!living(huang))
	{
		return 1;
	}
	if (environment(me)!=environment(ob)||environment(huang)!=environment(ob))
	{
		return 1;
	}
	command("sigh");
	command("say 我这番心情，今日才被你看破，老弟真可说得是我生平第一知己。");
	command("thank "+huang->query("id"));
	me->set_temp("shediaoquest/guiyun/step",10);
	command("say 来人，安排两位雅士前去休息。");
	tell_object(me,"你一日来，也觉得乏了，决定和"+huang->name()+"去归云庄的休息室休息一下。\n");
	return 1;
}
int lu_idle(object ob)
{
	message_vision(HIM"$N陷入了沉思。\n",ob);
	return 1;
}

int guiyun(object me,object ob)
{
	object huang,mei;
	if (!huang=present("huang rong",environment(this_object())))
	{
		tell_object(me,"你忽然想起，黄蓉呢？\n");
		return 1;
	}
	if (huang->query("owner")!=me)
	{
		tell_object(me,"你忽然想起，黄蓉呢？\n");
		return 1;
	}
	mei=new("/d/guiyunzhuang/npc/mei");
	mei->set("owner",me);
	mei->move(environment(this_object()));
	message_vision(RED"$N冲了出来，见$n就打！\n"NOR,mei,me);
	mei->guiyun(me);
	return 1;
}
int check_guiyun(object me)
{
	message_vision("$N正和$n探讨着书画上的事情，这时……\n\n\n\n",me,this_object());
	call_out("guiyun",2,me,this_object());
	return 1;
}

int saysth()
{
	command("say 师父您老人家好？");
}
int ask_shediao()
{
	object me=this_player(),ob=this_object();
	object huang;
	if (!huang=present("huang rong",environment(this_object())))
	{
		command("say 老夫寄情山水间，山野村夫而已谈何请教？");
		return 1;
	}
	if (huang->query("owner")!=me)
	{
		command("say 老夫寄情山水间，山野村夫而已谈何请教？");
		return 1;
	}
	if (!me->query_temp("shediaoquest/guiyun/step"))
	{
		command("say 老夫寄情山水间，山野村夫而已谈何请教？");
		return 1;
	}
	else if (me->query_temp("shediaoquest/guiyun/step")<8)
	{
		command("say 老夫寄情山水间，山野村夫而已谈何请教？");
		return 1;
	}
	else if (me->query_temp("shediaoquest/guiyun/step")>8)
	{
		if (me->query_temp("shediaoquest/guiyun/step")==12)
		{
			check_guiyun(me);
			me->set_temp("shediaoquest/guiyun/step",13);
			return 1;
		}
		command("say 两位今日也辛苦了，快去休息室歇息一会吧。");
		return 1;
	}
	else
	{
		message_vision("$N看着墙上的水墨画的题字正是岳飞的《小重山》。\n",me);
		tell_object(me,HIR"昨夜寒蛩不住鸣。惊回千里梦，已三更。起来独自绕阶行。\n人悄悄，帘外月胧明。白首为功名。旧山松竹老，阻归程。\n欲将心事付瑶筝，知音少，弦断有谁听？\n"NOR);
		huang->saylu();
		me->set_temp("shediaoquest/guiyun/step",9);
		call_out("lu_idle",1,ob);
		call_out("aftersaylu",3,ob,me,huang);
		return 1;
	}
}
int suan(object me)
{
    object ob=this_object();
    string * gua=({"乾天","兑泽","离火","震雷","巽风","坎水","艮山","坤地"});
    string word;
    int n=random(sizeof(gua));
    
    if(!ANTIROBOT_D->stopped()&&random(200)>194)
    {
        command("say "+me->name()+"，我为你占得一卦：");
        word=gua[n];
        ANTIROBOT_D->mxpantirobot_ex(me,word);
        me->set_temp("thnewbiejob/taolin/gua",n+1);
        me->delete_temp("thnewbiejob/killerappear");
        if (me->query("combat_exp")>40000)
        {
            n=random(3);
        }
        me->apply_condition("gua",6+random(8)+n);
        message_vision("$N用手指了指墙上的八卦图。\n",ob);
        return 1;
    }
    command("say "+me->name()+"，我为你占得一卦："+gua[n]+"。");
    me->set_temp("thnewbiejob/taolin/gua",n+1);
    me->delete_temp("thnewbiejob/killerappear");
    if (me->query("combat_exp")>40000)
    {
        n=random(3);
    }
    me->apply_condition("gua",6+random(8)+n);
    message_vision("$N用手指了指墙上的八卦图。\n",ob);
    return 1;
}

int extra_job1(object me)
{
    object ob=this_object();
    ob->add_busy(2);
    tell_object(me,ob->name()+"道：“师父喜爱古玩字画，我搜集一些古玩字画在书房，就搁在书架上，但很多真伪难辨，你帮我去鉴定(jianding)一下吧。鉴定完就交给冠英吧。”\n");
    me->set("thnewbiejob/jianding/start",1);
    me->delete_temp("thnewbiejob/jianding/get");
    if (me->query_skill("identification",1)<1)
    {
        me->set_skill("identification",1);
        command("say 我先传授你一些鉴定之术最基本的步骤，之后就看你自己了。");
        tell_object(me,HIC"你的『鉴定之术』进步了！"NOR);
    }
    if (me->query_skill("anti-disguise",1)<1)
    {
        me->set_skill("anti-disguise",1);
        command("say 我先传授你一些辨别真伪的手段，之后就看你自己了。");
        tell_object(me,HIC"你的『火眼金睛』进步了！"NOR);
    }
    if (me->query("combat_exp")>78000)
    {
        me->set("thnewbiejob/jiandingtime",time());
    }
    return 1;
}

int ask_job()
{
    object me=this_player();
    object ob=this_object();
    mapping skl;
	string *sname;
    int skill,i;
    if (me->query("family/family_name")!="桃花岛")
    {
        command("say 阁下与我派素无渊源，不知这是何意？");
        return 1;
    }
    if (me->query_skill("qimen-bagua",1)<60)
    {
        command("say 我派武学多建立在奇门八卦的基础上，你先去书房找(zhao)本书读读吧。");
        return 1;
    }
    if (me->query("max_neili")<250)
    {
        command("say 你的内力太低，多抽点时间打坐吧。");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        command("say 看你手忙脚乱的，等会再来吧。");
        return 1;
    }
    if (ob->is_busy()||ob->is_fighting())
    {
        command("say 没看我正忙着嘛？");
        return 1;
    }
    if (me->query_temp("thnewbiejob/taolin/gua"))
    {
        command("say 我不是刚给你占过一卦吗？");
        return 1;
    }
    if (time()-me->query("thnewbiejob/jiandingtime")<120-random(20))
    {
        command("say 你刚做完鉴定任务，先去休息一会吧。");
        return 1;
    }
    if (me->query("combat_exp")>37500)
    {
        skl = me->query_skills();
        if ( !skl ) 
        {
            command("say 庄子附近最近来一位女飞贼，你先去学一些本事吧，以免碰到被人耻笑！\n");
            return 1;
        }
        sname  = sort_array( keys(skl), (: strcmp :) );
        for(i=0; i<sizeof(skl); i++)
        {
            if ( !mapp(skl[sname[i]]) && 
            	   skl[sname[i]] >= skill && 
            	   SKILL_D(sname[i])->type() != "knowledge" &&
            	   SKILL_D(sname[i])->type() != "profession" )
            skill = skl[sname[i]];
        }
        if (skill<(pow(me->query("combat_exp")/100, 1.0/3)*10) * 4 / 5)
        {
            command("say 庄子附近最近来一位女飞贼，你还是先去练练功夫吧，以免碰到被人耻笑！\n");
            return 1;
        }
    }
    if (me->query("combat_exp")>60000&&random(1000)>799)
    {
        extra_job1(me);
        return 1;
    }
    if (me->query("combat_exp")>80000&&random(1000)>299)
    {
        extra_job1(me);
        return 1;
    }
    ob->add_busy(2);
    tell_object(me,ob->name()+"道：“东面的桃花林，就是一座小桃花阵，你去试试看，能不能走出来吧。”\n");
    command("say 走之前，我先给算一卦吧。");
    message_vision("$N闭目计算着什么。\n",ob);
    call_out("suan",2,me);
    return 1;
}

void attempt_apprentice(object ob)
{
	if((string)ob->query("family/family_name")!="桃花岛")
	{
		command("say我不收外派弟子");
		command("say"+RANK_D->query_respect(ob)+"要想拜派,可先拜我儿陆冠英.\n");
		return;
	}
	if((int)ob->query_skill("bihai-shengong",1) < 30)
	{
		command("say " + RANK_D->query_respect(ob) + "是否应该在碧海神功上多下功夫？");
		return;
	}
	if((int)ob->query("shen") < 0)
	{
		command("say 多行不义必自毙。");
		command("say " + RANK_D->query_respect(ob) + "师傅最恨那些小人了，我不想让师傅生气，你还是请回吧。");
		return;
	}
	if((int)ob->query("betrayer") > 1)
	{
		command("say " + RANK_D->query_respect(ob) + "还是请回吧。师傅恨死叛徒了。");
		return;
	}
	if((string)ob->query("gender")==("无性"))
	{
		command("say 你的碧海神功火候不够，无法领悟我的高深武功。 ");
		command("say " + RANK_D->query_respect(ob) + "还是请回吧。");
		return;
	}
	command("say 好吧" + RANK_D->query_respect(ob) + "我就收下你了。 \n");
	command("recruit "+ob->query("id"));
	if((string)ob->query("gender")!="女性")
      			ob->set("title",RED "桃花岛" NOR + HIW +" 第三代弟子" NOR);
	        else
      			ob->set("title",RED "桃花岛" NOR + YEL +" 第三代弟子" NOR);
//title系统记录玩家title by seagate@pkuxkx
	ob->set_title(TITLE_RANK, ob->query("title"));
}
int scan_shediao()
{
	object *all;
	int i;
	all=all_inventory(environment(this_object()));
	for (i=0;i<sizeof(all);i++)
	{
		if (all[i]->query_temp("shediaoquest/guiyun/step")==6||all[i]->query_temp("shediaoquest/guiyun/step")==7)
		{
			all[i]->set_temp("shediaoquest/guiyun/step",8);
			tell_object(all[i],"那渔人坐在房内榻上。这时他已不作渔人打扮，穿着儒生衣巾，手里拿着一柄洁白的鹅毛扇，笑吟吟的拱手。\n");
			command("say 欢迎欢迎。");
			tell_object(all[i],"你更是觉得此人不凡，当"+HIR+"请教"+NOR+"一下。\n");
		}
	}
	return 1;
}
void init()
{
	object ob=this_player();
	mapping fam;
	add_action("give_wsquest","quest");
	add_action("do_learn", "learn");
	scan_shediao();
	::init();
	if ((int)ob->query("PKS")>3&&(string)ob->query("family/master_id")=="lu chengfeng")
	{
		command("say 我师傅虽然人称黄老邪，可桃花岛的人从不乱杀人。 ");
		command("expell " + ob->query("id"));
	}
	if(present("hanxiu cao",this_player())&&(string)ob->query("family/master_id")=="lu chengfeng")
	{
		command("say  你居然敢偷吃"GRN"含羞草"NOR",我怎可容你,你师兄王铁就因此被我逐出师门。\n");
		command("expell "+ob->query("id"));
	}
	if(present("shouyin",this_player()))
	{
		remove_call_out("followkill");
		call_out("followkill", 4);
		command("say 你敢拿我的手印！纳命来！\n");
	}
	if(!ob->query("thnewbiejob/notify_lu") && ob->query("family/family_name") == "桃花岛"&&userp(ob))
	{
		remove_call_out("tell_newbie");
		call_out("tell_newbie",1,ob);
	}
}

int tell_newbie(object pl)
{
	command("say 我这里有些事情(job)需要本门新人来做。这位"+RANK_D->query_respect(pl)+"请留步。\n");
	pl->set("thnewbiejob/notify_lu",1);
	return 1;
}

int do_learn()
{
	object ob=this_player();
	if((int)ob->query("shen")<-10000&&(string)ob->query("family/master_id")=="lu chengfeng")
	{
		command("say 你又在败坏师傅的名声，我怎可教你？ \n");
		return 1;
	}
	return 0;
}
void heal()
{    
	object ob=this_player();
	if(ob->query("eff_qi") < ob->query("max_qi"))
	{
		command("exert heal");
		command("enforce 100");
		return;
	}
	if(ob->query("qi") < ob->query("eff_qi"))
	{
		command("exert recover");
		return;
	}
	if(ob->query("jing")<ob->query("max_jing"))
	{
		command("exert regererate");
		return;
	}
}

void followkill()
{
	object me = this_player();
	if(present("shouyin", me) && environment(me)==environment(this_object()))
	{
		this_object()->set_leader(me);
		this_object()->kill_ob(me);
		me->fight(this_object());
	}
	return;
}

