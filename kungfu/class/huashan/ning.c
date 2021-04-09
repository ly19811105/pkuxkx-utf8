// ning.c 宁中则
#include <ansi.h>
#include <title.h>

inherit NPC;
#include "bonus.h"
#include "random_user_quest.h"
inherit "/inherit/char/silver.c";
int ask_job();
int ask_fail();
int ask_finish();
string ask_for_leave();
inherit F_MASTER;
int ask_wushuang();
#include "/new_quest/qzhengpai.h"
#include "/new_quest/quest.h"

void create()
{
        set_name("宁中则",({"ning zhongze","ning"}));
	set("nickname", MAG "紫衫女侠" NOR);
	set("title", YEL "华山派" NOR + GRN "第十八代" NOR + YEL "掌门夫人" NOR);
        set("long",
                "华山派掌门岳不群的夫人。 \n"
               "她今年将近四十, 人称紫衫女侠.\n");
        set("gender", "女性");
        set("age", 36);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 20);
        set("int", 28);
        set("con", 26);
        set("dex", 30);
        set("max_qi", 1000);
        set("max_jing", 800);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 30);
        set("combat_exp", 900000);
        set("score", 40000);
        set_skill("force", 140);
        set_skill("huashan-neigong", 140);
	set_skill("cuff", 150);
	set_skill("poyu-quan", 150);
	set_skill("strike", 150);
	set_skill("hunyuan-zhang", 150);
        set_skill("dodge", 160);
        set_skill("huashan-shenfa", 160);
        set_skill("yunushijiu-jian", 200);
//      set_skill("tianpo-quan", 130);
        set_skill("parry", 140);
        set_skill("sword", 140);
        set_skill("huashan-jianfa", 140);
//      set_skill("taoism", 140);
        set_skill("literate", 150);

        map_skill("force", "huashan-neigong");
	map_skill("cuff", "poyu-quan");
	map_skill("strike", "hunyuan-zhang");
	map_skill("dodge", "huashan-shenfa");
//      map_skill("unarmed", "taiji-quan");
        map_skill("parry", "huashan-jianfa");
        map_skill("sword", "yunushijiu-jian");

	prepare_skill("cuff","poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");
        set("inquiry", ([
        "quest":   (: ask_quest() :),
        "cancelquest":   (: ask_cancel() :),
        "取消任务":   (: ask_cancel() :),
		"生活费" : (: ask_silver :),
		"无双无对，宁氏一剑" : (: ask_wushuang :),
                "job" : (: ask_job :),
                "任务" : (: ask_job :),
                "fail" : (: ask_fail :),
                "失败" : (: ask_fail :),
                "finish" : (: ask_finish :),
                "完成" : (: ask_finish :),
        "脱离门派" : (: ask_for_leave :),
      ]));


	set("silver_name", "生活费"); //例银的名称，默认为“例银”
        set("silver_factor", 1); //例银的数量因子，默认为1
        set("silver_family_skill", "huashan-jianfa"); //门派武功，提升此武功时可以领取例银，默认为parry
        set("msg_silver_firsttime", "好吧，以后每月你都来找我领生活费罢。"); //第一次打听例银的时候说的话
        set("msg_silver_record", "$N在一张帖子上写了点什么做记录。\n"); //作记录时的描述\n
        set("msg_silver_check", "$N翻了翻以前的帖子。\n"); //检查记录时的描述\n
        set("msg_silver_mudage", "上个月给你的钱还没花完罢？"); //时间未到不能领取时说的话
        set("msg_silver_paid", "给你拿着，别乱花钱，记得要多打抱不平。"); //领取成功时说的话
        set("msg_silver_score", "$N带着赞许对$n点头道：「你对师门的忠心师娘都看在眼里。」\n"); //由于提升师门忠诚而领取例银时的描述\n
        set("msg_silver_skill", "$N带着赞许对$n点头道：「你练剑的艰辛师娘都看在眼里。」\n"); //由于提升师门武功而领取例银时的描述\n
        set("msg_silver_exp", "$N带着赞许对$n点头道：「你勤于练武，师娘都看在眼里。」\n"); //由于提升经验而领取例银时的描述\n
        set("msg_silver_none", "你去思过崖上想想，自己都做了些什么？"); //领取例银条件均不满足时说的话

        create_family("华山派",18,"弟子");
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/huashan/obj/zishan")->wear();
}

string ask_for_leave()
{
	object me;

	me = this_player();

	if( (string)me->query("family/family_name") != "华山派")
		return "你非我华山派弟子，脱离门派的事情我作不得主。";

	me->set_temp("pending/leave_huashan", 1);
  return "如果" + RANK_D->query_respect(me) + "真想离我华山派而去，就请下决心(leave)吧！";
}
int remain(object me)
{
	if (me->query("combat_exp")>400000000)
	return 4;
	else if (me->query("combat_exp")>325000000)
	return 3;
	else if (me->query("combat_exp")>250000000)
	return 2;
	else if (me->query("combat_exp")>175000000)
	return 1;
	else
	return 0;
}

string Chinese_Desc(int type, int typeNo, int flag, int lv)
{
    string *C_lv = ({"戊","丁","丙","乙","甲","超","超上"}), *C_type = ({"连击","压制","重击"}), *C_subType1 = ({"连击数","提升档次"}),
       *C_subType2 = ({"命中概率","压制时长"}), *C_subType3 = ({"命中概率","击中效果"});
    if (type == 1) //返回类型
        return HIR + C_type[typeNo - 1] + NOR + "类绝技";
    else if (type == 2) //返回层次
        return HIY + C_lv[lv - 1] + "等" + NOR;
    else
    {
        if (typeNo == 1)
            return CYN + C_subType1[flag] + NOR;
        if (typeNo == 2)
            return CYN + C_subType2[flag] + NOR;
        if (typeNo == 3)
            return CYN + C_subType3[flag] + NOR;
    }
}

int increase_wushuang(object me, int inc_TYPE)
{
    int *layers;
    if (!me->query("huashan_newskills/wushuang") || !arrayp(me->query("huashan_newskills/wushuang"))
        || sizeof(me->query("huashan_newskills/wushuang")) != 5)
    {
        tell_object(me, "你根本还不会无双无对，不能提升。\n");
        return 1;
    }
    if (inc_TYPE != 1 && inc_TYPE != 2)
        return 0;
    layers = me->query("huashan_newskills/wushuang");
    if (layers[inc_TYPE] > 6 || (layers[inc_TYPE] > 4 && !me->query("huashan_newskills/wushuang_highStart")))
    {
        tell_object(me, "你的『无双无对』在" + Chinese_Desc(-1, layers[0], inc_TYPE - 1, -1) + "方面已经达到了巅峰。\n");
        return 1;
    }

    layers[inc_TYPE] += 1;
    me->set("huashan_newskills/wushuang", layers);
    me->add("huashan_newskills/wushuang_inc", 1);
    message_vision(HIC"$N" + HIC + "的剑法绝招无双无对获得了提升。\n" + NOR, me);
    tell_object(me, "你的『无双无对』在" + Chinese_Desc(-1, layers[0], inc_TYPE - 1, -1) + "方面提升为" + Chinese_Desc(2, -1, -1, layers[inc_TYPE]) + "。\n");
    return 1;
}



int choose_inc(string arg,object me,string file,string path1,string path2)
{
	if (!me)
	return 0;
	if (arg=="cancel"||arg=="Cancel")
	{
		tell_object(me,"你选择了放弃提升。\n");
		return 1;
	}
	if (!arg||(arg!=COLOR_D->uncolor(path1)&&arg!=COLOR_D->uncolor(path2)))
	{
		tell_object(me,"你要选择提升哪一个？"+path1+"或者"+path2+"或者放弃(cancel)？\n");
		input_to((:choose_inc:),me,file,path1,path2);
		return 1;
	}
	if (arg==COLOR_D->uncolor(path1))
	return increase_wushuang(me,1);
	if (arg==COLOR_D->uncolor(path2))
	return increase_wushuang(me,2);
}

int ask_wushuang()
{
	int times;
	object me=this_player();
	string file="/kungfu/skill/huashan-jianfa/wushuang.c";
	int pfm_type,pfm_rate,pfm_base;
	if (me->query("family/family_name")!="华山派")
	{
		message_vision("$N转过身去，不理睬你。\n",this_object());
		return 1;
	}
	if (!me->query("huashan_newskills/wushuang"))
	{
		command("say 说来见笑了，这一招是我早年所创。");
		return 1;
	}
	pfm_type=me->query("huashan_newskills/wushuang")[0];
	pfm_rate=me->query("huashan_newskills/wushuang")[1];
	pfm_base=me->query("huashan_newskills/wushuang")[2];
    tell_object(me, "你的『无双无对』是" + Chinese_Desc(1, pfm_type, -1, -1) + "类绝技，" + Chinese_Desc(-1, pfm_type, 0, -1) + "：" + Chinese_Desc(2, -1, -1, pfm_rate) + "，" + Chinese_Desc(-1, pfm_type, 1, -1) + "：" + Chinese_Desc(2, -1, -1, pfm_base) + "。\n");
	if (me->query("huashan_newskills/wushuang_inc")>=4)
	{
		command("say 人力或与穷尽，这招已经被你发挥到了极致。");
		return 1;
	}
	times=remain(me);
	if (times<0||times<=me->query("huashan_newskills/wushuang_inc"))
	{
		command("say 人力或与穷尽，以你的修为暂时无法提升这一招了。");
		return 1;
	}
//	tell_object(me,"你的『无双无对』是"+file->Chinese_Desc(1,me->query("huashan_newskills/wushuang")[0],-1,-1)+"类绝技，"+file->Chinese_Desc(-1,me->query("huashan_newskills/wushuang")[0],0,-1)+"："+file->Chinese_Desc(2,-1,-1,me->query("huashan_newskills/wushuang")[1])+"，"+file->Chinese_Desc(-1,me->query("huashan_newskills/wushuang")[0],1,-1)+"："+file->Chinese_Desc(2,-1,-1,me->query("huashan_newskills/wushuang")[2])+"。\n");
//	tell_object(me,"你要提升"+file->Chinese_Desc(-1,me->query("huashan_newskills/wushuang")[0],0,-1)+"还是"+file->Chinese_Desc(-1,me->query("huashan_newskills/wushuang")[0],1,-1)+"？\n");
//	input_to((:choose_inc:),me,file,file->Chinese_Desc(-1,me->query("huashan_newskills/wushuang")[0],0,-1),file->Chinese_Desc(-1,me->query("huashan_newskills/wushuang")[0],1,-1));
	tell_object(me,"你要提升"+Chinese_Desc(-1,pfm_type,0,-1)+"还是"+Chinese_Desc(-1,pfm_type,1,-1)+"？\n");
	input_to((:choose_inc:),me,file,Chinese_Desc(-1,pfm_type,0,-1),Chinese_Desc(-1,pfm_type,1,-1));
	return 1;
}
int do_leave()
{
	object me = this_player();
	
	if (me->query_temp("pending/leave_huashan") != 1)
		return 0;
	message_vision("$N对$n说道：「从此你就不再是我华山派门下了，请好自为之！」\n",this_object(), me );
	tell_object(me,HIR "你决定叛出华山派门下！\n" NOR);
	me->delete_temp("pending/leave_huashan");
  me->expell_family("华山派");
	if (me->query("combat_exp") >= 1000)
		me->add("betrayer",1);
	return 1;
}

void attempt_apprentice(object ob)
{
 if ((string)ob->query("family/family_name")!="华山派")
{
                command("say 你非我派弟子，我不能收你。");
                return ;
}

        if((string)ob->query("gender")=="女性")
          {
               if ((int)ob->query("max_neili") <200) {
                       command("say 我华山派原有剑宗、气宗之争。最终气宗为首。");
                       command("say " + RANK_D->query_respect(ob) +"是否还应该多练练内力？");
                       return;
               }
               if ((int)ob->query("score") < 500)
                {
                 command("sigh "+ob->query("id"));
                 command("say 你对本门的贡献太低了，我怎么能信任你呢?");
                 return;
                }
               if ((int)ob->query("shen") < 1000) {
                       command("say 学武之人，德义为先，功夫的高低倒还在其次，未练武，要先学做人。");
                       command("say 在德行方面，" + RANK_D->query_respect(ob) +"是否还做得不够？");
                       return;
               }
          command("say 好吧，" + RANK_D->query_respect(ob) +"，我就收下你了！");
          command("recruit "+ob->query("id"));

           }
        else {
          command("say 我不收男弟子，" + RANK_D->query_respect(ob) +"还是去找别人吧。n");
            };
}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        {
	        if (this_player()->query("shen")<10000)
           	ob->set("title",GRN "华山派" NOR + YEL +"女剑客" NOR);
        	else 
   	        ob->set("title",GRN "华山派" NOR + YEL +"女剑侠" NOR);
//title系统记录玩家title by seagate@pkuxkx
	        ob->set_title(TITLE_RANK, ob->query("title"));
        }
}

void re_rank(object student)
{
	      if (this_player()->query("shen")<10000)
         	student->set("title",GRN "华山派" NOR + YEL +"女剑客" NOR);
        else 
   	      student->set("title",GRN "华山派" NOR + YEL +"女剑侠" NOR);
//title系统记录玩家title by seagate@pkuxkx
	      student->set_title(TITLE_RANK, student->query("title"));
}

int ask_job()
{
    object me=this_player();
    object ob=this_object();
    object ling;
    
    
    if (me->query("family/family_name")!="华山派")
    {
        command("say 阁下不是我派弟子，这是何意？");
        return 1;
    }
    if (me->query("combat_exp")<=30000)
    {
        command("say 你的功夫太差，找灵珊去吧。");
        return 1;
    }
    if (me->query("combat_exp")>60000)
    {
        command("say 你的功夫不错了，在我这学不到什么了，去找掌门吧。");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        command("say 等你忙完再来找我吧。");
        return 1;
    }
    if (!me->query("hsnewbiejob/intro"))
    {
        me->set("hsnewbiejob/intro",1);
        tell_object(me,HIR"华山入门任务帮助请在游戏中使用命令help task-huashan获得。\n"NOR);
    }
    if (me->query("hsnewbiejob/start"))
    {
        command("say 你上次任务还没有完成呢！");
        return 1;
    }
    if(time() - (me->query("hsnewbiejob/lasttime")+(int)me->query("hsnewbiejob/user")*120) < 60)
    {
        command("say 你刚刚做过任务，先去休息一会吧。");
        return 1;
    }
    
    if (me->query("hsnewbiejob/user"))
    {
        lookingforplayer(me);
        return 1;
    }
    if (random(100)>90)
    {
        lookingforplayer(me);
        return 1;
    }
    else
    {
        me->set("hsnewbiejob/start",1);
        me->set("hsnewbiejob/lasttime",time());
        me->set_temp("hsnewbiejob/xunlian",1);
        ling=new("/d/huashan/npc/newdizi");
        ling->set("owner",me->query("id"));
        ling->set("title",me->query("name")+"教导的华山弟子");
        ling->set_name(ling->query("name"),({me->query("id")+"'s student","student","dizi"}));
        ling->move(environment(me));
        ling->gen(me);
		me->set_temp("hsnewbiejob/xunlian_target",ling);
        message_vision("$N对$n说道：最近华山来了些新弟子，你带去练功房指点(zhidian)一下吧。\n",ob,me);
        return 1;
    }
}

int ask_fail()
{
    object me=this_player();
    object ob=this_object();
    
    if (me->query("family/family_name")!="华山派")
    {
        command("say 阁下不是我派弟子，这是何意？");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        command("say 等你忙完再来找我吧。");
        return 1;
    }
    if (!me->query("hsnewbiejob/start"))
    {
        command("say 你没接过任务啊！");
        return 1;
    }
    
    
    command("say 我还是看错了人啊！下去吧");
    punish(me);
    return 1;
}

int ask_finish()
{
    object me=this_player();
    if (me->query("family/family_name")!="华山派")
    {
        command("say 阁下不是我派弟子，这是何意？");
        return 1;
    }
    if (me->is_busy()||me->is_fighting())
    {
        command("say 等你忙完再来找我吧。");
        return 1;
    }
    if (!me->query("hsnewbiejob/start"))
    {
        command("say 你没接过任务啊！");
        return 1;
    }
    if (me->query_temp("hsnewbiejob/xunlian/degree")<=50)
    {
        command("say 你简直是误人子弟，人给你教到哪去了？");
        return 1;
    }
    
    bonus(me);
    return 1;
}