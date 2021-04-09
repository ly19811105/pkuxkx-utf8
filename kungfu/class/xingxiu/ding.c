// ding.c 丁春秋
// modified by iszt@pkuxkx, 2007-02-08

#include <ansi.h>
#include "/kungfu/class/xingxiu/qingan.h"
#include <title.h>
inherit NPC;
inherit F_MASTER;
#include <no1master.h>

inherit "/inherit/char/silver.c";

string ask_me();
string ask_for_shenmuding();
int ask_li();
string ask_jieyao();
void consider();
string ask_for_leave();

void create()
{
	set_name("丁春秋", ({ "ding chunqiu", "ding" }));
	set("title",MAG "星宿派" NOR + YEL "开山" NOR + MAG "祖师" NOR);
	set("nickname", RED "星宿老怪" NOR);
	set("long",
		"他就是星宿派开山祖师、令正派人士深恶痛绝的星宿老怪丁春秋。\n"
		"可是他看起来形貌清奇，仙风道骨。\n");
	set("gender", "男性");
	set("age", 60);
	set("attitude", "friendly");
	set("shen_type", -1);
        set("sanxiao_count", 15);
	set("str", 25);
	set("int", 30);
	set("con", 28);
	set("dex", 28);
    set("step", 2);
	set("max_qi", 4000);
	set("max_jing", 3000);
	set("max_jingli", 2000);
	set("jingli", 2000);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 100);
	set("combat_exp", 1500000);
	set("score", 400000);
	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "strike.sandu" :),
		(: perform_action, "strike.huoqiu" :),
		(: perform_action, "strike.huoqiang" :),
		(: perform_action, "strike.huoqiu" :),
		(: consider :)
	}) );
	set("inquiry", ([
		"冰魄杖" : (: ask_me :),
		"虚竹" : "你问他干吗，他不是老仙的对手。",
		"阿紫" : "阿紫不是在外边吗？",
		"李秋水" : (: ask_li :),
		"奖赏" : (: ask_silver :),
    "炼毒" : "这个嘛……你得去找飘然子。",
    "三笑逍遥散" :(:ask_jieyao():),
    "脱离门派" : (: ask_for_leave :),
	"神木鼎" : (:ask_for_shenmuding :),
	"神木王鼎" : (:ask_for_shenmuding :),
	"神木宝鼎" : (:ask_for_shenmuding :),
	]) );
	set_skill("force", 150);
	set_skill("huagong-dafa", 180);
	set_skill("dodge", 150);
	set_skill("zhaixinggong", 150);
	set_skill("strike", 150);
	set_skill("xingxiu-duzhang", 180);
	set_skill("hand", 150);
	set_skill("zhaixing-shou", 150);
	set_skill("parry", 150);
	set_skill("staff", 150);
	set_skill("tianshan-zhang", 150);
//	set_skill("literate", 80);
        set_skill("poison", 350);
	map_skill("force", "huagong-dafa");
	map_skill("dodge", "zhaixinggong");
	map_skill("strike", "xingxiu-duzhang");
	map_skill("hand", "zhaixing-shou");
	map_skill("parry", "xingxiu-duzhang");
	map_skill("staff", "tianshan-zhang");
	prepare_skill("strike", "xingxiu-duzhang");
	create_family("星宿派", 1, "开山祖师");
	set("class", "taoist");
	set("silver_name", "奖赏"); //例银的名称，默认为“例银”
	set("silver_factor", 1.4); //例银的数量因子，默认为1
	set("silver_family_skill", "huagong-dafa"); //门派武功，提升此武功时可以领取例银，默认为parry
	set("msg_silver_firsttime", "嗯，以后每个月老仙心情好的时候给你点奖赏也未尝不可。"); //第一次打听例银的时候说的话
	set("msg_silver_record", "$N一努嘴，旁边的弟子忙记录了下来。\n"); //作记录时的描述\n
	set("msg_silver_check", "$N一拍手，便有弟子附上去说了几句什么。\n"); //检查记录时的描述\n
	set("msg_silver_mudage", "上个月的奖赏还没吃完罢？"); //时间未到不能领取时说的话
	set("msg_silver_paid", "嘿嘿，不错，给你点甜头尝尝。"); //领取成功时说的话
	set("msg_silver_score", "$N盯着$n看了半天，一言不发。\n"); //由于提升师门忠诚而领取例银时的描述\n
	set("msg_silver_skill", "$N突然在$n身上拍了几下，冷笑几声。\n"); //由于提升师门武功而领取例银时的描述\n
	set("msg_silver_exp", "$N飞快的和$n拆了几招，坐了回去。\n"); //由于提升经验而领取例银时的描述\n
	set("msg_silver_none", "小贼，来骗老仙钱的是不是？"); //领取例银条件均不满足时说的话

	setup();
	setup_no1master();

	set("chat_chance", 5);
	set("chat_msg", ({
		"丁春秋骂骂咧咧的说道：「虚竹这小子不是个东西，竟敢偷袭老仙。」\n",
		"丁春秋叹了口气：「唉，要是我的冰魄杖在就好了，虚竹那小子不是我的对手。」\n",
		"「哪儿去了呢？」丁春秋喃喃自语，「难道又给她偷去了？」\n"
		"丁春秋焦躁的转来转去：「我是放的好好的啊！唉。」\n",
		"丁春秋叹道：「想当年在逍遥派的时候，李师叔对我还是不错的! 」\n"
	}) );
//      carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xingxiu/obj/sanxiaosan");
        carry_object("/d/xingxiu/obj/sanxiaosan");
        carry_object("/d/xingxiu/obj/sanxiaosan");
        carry_object("/d/xingxiu/obj/sanxiaosan");
        carry_object("/d/xingxiu/obj/sanxiaosan");
}
void init()
{
	object ob = this_player();
	object me = this_object();
	mapping fam;

	add_action("do_flatter", "flatter");
  add_action("do_qingan", ({ "qingan" }));
	add_action("do_leave",  "leave");
	::init();

	if ( (int)ob->query("shen") >0 && ((fam = ob->query("family")) && fam["master_id"] == "ding chunqiu"))
	{
		command("say 你多次杀我同道中人，我岂能仍是你的师傅。\n");
		command("expell "+ ob->query("id"));
	}

	if (interactive(ob = this_player())&&(!is_fighting()))
                if((int)ob->query("shen")>=1000000)
		{
			remove_call_out("do_killing");
			call_out("do_killing", 2,ob);
			command("say 我最讨厌你们这些伪君子，去死吧! ");
		}
}

string ask_for_shenmuding()
{
	object me = this_player();
	if (me->query("shen")>0)
	{
		call_out("do_killing", 1, me);
		return "我最讨厌你们这些伪君子，竟敢觊觎我的宝鼎，受死吧！";
	}
	if (me->query_skill("force", 1)<300)
	{
		command("laugh "+me->query("id"));
		return "就凭你这点修为也配来问我的宝鼎，莫非是来消遣老仙的？";
	}
	me->set_temp("ask_ding_shenmuding", 1);
	return "唉，我的宝鼎失踪了，也不知道被哪个混账弟子偷了。如果你见到了，记得速速将它送还给我。";
}

string ask_for_leave()
{
	object me;

	me = this_player();

	if( (string)me->query("family/family_name") != "星宿派")
		return "你非我星宿派弟子，脱离门派的事情我作不得主。";

	me->set_temp("pending/leave_xingxiu", 1);
  return "如果" + RANK_D->query_respect(me) + "真想离我星宿派而去，就请下决心(leave)吧！";
}

int do_leave()
{
	object me = this_player();
	
	if (me->query_temp("pending/leave_xingxiu") != 1)
		return 0;
	message_vision("$N对$n说道：「从此你就不再是我星宿派门下了，请好自为之！」\n",this_object(), me );
	tell_object(me,HIR "你决定叛出星宿派门下！\n" NOR);
	me->delete_temp("pending/leave_xingxiu");
  me->expell_family("星宿派");
	if (me->query("combat_exp") >= 1000)
		me->add("betrayer",1);
	return 1;
}	

void do_killing(object ob)
{
	if (!ob || environment(ob) != environment())
		return;
	this_object()->kill_ob(ob);
}


void attempt_apprentice(object me)
{
	if ((int)me->query("shen") > -10000)
	{
		command("say 老仙越看你越象白道派来卧底的。");
		return;
		}
	if ((string)me->query("family/family_name") != "星宿派")
	{
		command("say 你不是我派弟子，此话从何说起！");
		return;
	}
	if ((int)me->query("score") < 800)
	{
		message_vision("丁春秋露出一副不信任的样子。\n", me);
		command("say 你对本门尽心了吗？");
		return;
	}
  
	if( me->query_temp("pending/flatter") )
	{
		command("say 你如此不把老仙放在眼里，老仙怎会收你？");
		return;
	} else
	{
		command("say 我星宿老仙比起古往今来的圣人怎么样啊？");
		message_vision("星宿老怪微闭双眼，手捻长须，一付等人拍马(flatter)的样子。\n", me);
		me->set_temp("pending/flatter", 1);
		return;
	}
}

int do_flatter(string arg)
{
	object me = this_player();

	string name = me->query("name"),color,new_name;
	

	if( !this_player()->query_temp("pending/flatter") )
		return 0;
	if( !arg )
		return notify_fail("你说老仙什么？\n");
	me->set_temp("pending/flatter", 0);
	message_vision("$N大声说道：「" + arg + "！」\n", this_player());
	if( strsrch(arg, "星宿老仙") >=0 && (strsrch(arg, "德配天地") >=0
		|| strsrch(arg, "威震寰宇") >=0 || strsrch(arg, "古今无比") >=0 ))
	{
		command("smile");
		command("say 这还差不多。以后你就跟着我现在的几个弟子排行吧！\n");
		me->set("xingxiu/old_name", name);
		color=COLOR_D->get_color(name);
		name=COLOR_D->uncolor(name);
		new_name = name[0..3] + "子";
		new_name = color+new_name+NOR;
		me->set("name", new_name);
		command("recruit " + me->query("id"));
		if((string)me->query("gender")!="女性")
			me->set("title",HIR "星宿派" NOR + GRN +"邪士" NOR);
		else
			me->set("title",HIR "星宿派" NOR + GRN +"妖女" NOR);
//title系统记录玩家title by seagate@pkuxkx
	  me->set_title(TITLE_RANK, me->query("title"));
	}
	else
		command("say 你如此不把老仙放在眼里，老仙怎会收你？");

	return 1;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		add("apprentice_available", -1);
}

void consider()
{
	int i=random(4);
	object *enemy,target;
	enemy = query_enemy() - ({ 0 });
	target = enemy[random(sizeof(enemy))];
	if (i==3)
		command("exert maxsuck " + target->query("id"));
	if (i==2)
		command("exert neilisuck " + target->query("id"));
	if (i==1)
		command("exert jingsuck " + target->query("id"));
	if (i==0)
		command("exert qisuck " + target->query("id"));
}

string ask_me()
{
	object me = this_player();
	mapping fam;
	if (!(fam = me->query("family"))
		|| fam["family_name"] != "星宿派")
		return "哼，" + RANK_D->query_respect(me) + "也来窥探我镇派之宝吗？";
	if ((int)me->query_temp("marks/丁") )
		return "你这恶徒，老仙不是刚告诉你了吗？";
        if (me->query_skill("tianshan-zhang",1) < 40)
		return "冰魄杖是我派镇派之宝，威力极大，" +RANK_D->query_respect(me) +
			"天山杖法太弱，还是专心练功罢。";
	me->set_temp("marks/丁", 1);
	command("say 冰魄杖是我派镇派之宝，可不知给谁拿走了我也不知道。");
	command("heng");
	return "我猜又是你那师姐阿紫偷的，你问问她吧。";
}

int ask_li()
{
	object me = this_player();
	mapping fam;
	int i=random(3); 
	if (!(fam = me->query("family")) || fam["family_name"] != "星宿派")
	{
		command("say "+RANK_D->query_respect(me) + "问李师叔干什么？");
	}
	else
	{
		if (i == 2)
		{
			command("say 听说李师叔来了天山，但我也不知道她老人家住在何处。");
			me->set_temp("marks/李",1);
			return 1;
		}
		if (i == 1) 
		{
			command("sigh"); 
			command("say 她是我的师叔，小无相神功天下无敌，可惜我没有学到！");
			return 1;
		}
		if (i == 0)
		{
			command("say 李师叔比较喜欢漂亮的年轻人，当初我还是蛮得李师叔的欢心的。");
			command("smile");
			return 1;
		}
	}
}

void die()
{
	object obj, me, cor;
	me = this_object();
	if( objectp(obj = me->get_damage_origin_object()) && ((obj->query_temp("lingjiu/kill_ding")))) 
	{
		 obj->set_temp("lingjiu/killer",1);
	}
	::die();

	return;
}
string ask_jieyao()
{        mapping fam;
        object ob;
         object me=this_player();
            if (!(fam = this_player()->query("family"))
            || fam["family_name"] != "星宿派")
             return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
        if((int)me->query("score")<1000)
                return "你对本门的贡献有限，神药不能给你。";
        if ( query("sanxiao_count")<1)
                      return "我的神药已经给完了。";
        add("sanxiao_count", -1);
        ob = new("/d/xingxiu/obj/sanxiaosan");
        ob->move(this_player());
        return RANK_D->query_respect(this_player())+"对本派贡献非小，这包三笑逍遥散就给你了。";
}
