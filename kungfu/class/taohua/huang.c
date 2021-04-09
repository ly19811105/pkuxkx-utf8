// huang.c 黄药师
// Modified by iszt@pkuxkx, 2007-03-01

#include <ansi.h>
#include <title.h>
inherit NPC;
inherit F_MASTER;
#include <no1master.h>
string ask_me();
string ask_dan();
string ask_zhenjing();
string ask_zhou();
string ask_bhcs();
string ask_lyz();
string ask_taohua();
string ask_zhugenu();
string ask_for_leave();

void consider();
void heal();

void create()
{
	set_name("黄药师", ({ "huang yaoshi", "huang", "yaoshi" }));
	set("title",MAG"桃花岛"NOR + YEL"岛主"NOR);//开山祖师也太俗气了,zine
	set("nickname", RED "东邪" NOR);
	set("long",
		"他就是桃花岛的岛主，非正非邪而又脾气古怪的黄药师。\n"
		"并且他看起来风流飘逸，颇有一股逍遥自在的感觉。\n");
	set("gender", "男性");
	set("generation",1);
	set("age", 55);
	set("attitude", "friendly");
	set("shen_type", 0);
	set("str", 35);
	set("int", 50);
	set("con", 35);
	set("dex", 50);
	set("max_qi", 16000);
	set("max_jing", 15000);
	set("neili", 16000);
	set("max_neili", 16000);
	set("jiali", 250);
	set("combat_exp",15000000);
	set("fighting",0);
	set("score", 1000000);
	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: consider :)
	}) );
	set("inquiry", ([
		"天王保命丹" : (: ask_dan :),
		"阿衡" : "内子是你能问的吗？",
		"九阴真经" :(: ask_zhenjing :),
		"曲灵风"  : "他是我的大弟子。",
		"梅超风"  : "哼，她不是我的徒弟！",
		"陈玄风"  : "哼，他们竟敢偷走九阴真经，我黄药师没有这样的徒弟！",
		"黄蓉" : "我也不知她在哪。",
		"玉箫" : (: ask_me :),
		"周伯通" : (: ask_zhou :),
		"桃花迷阵" : (: ask_taohua :),
		"碧海潮生曲" : (: ask_bhcs :),
    "落英神剑掌" : (: ask_lyz :),
    "诸葛连弩" : (: ask_zhugenu :),       
    "脱离门派" : (: ask_for_leave :),     
	]) );
	set_skill("force", 350);
	set_skill("bihai-shengong", 400);
	set_skill("dodge", 350);
	set_skill("luoying-shenfa", 300);
	set_skill("hand", 350);
	set_skill("music::music-theory", 300);
	set_skill("music::shaw", 300);
	set_skill("music::shaw::meihua-sannong", 250);
	set_skill("music::shaw::yuqiao-wenwan", 250);
	set_skill("music::shaw::bihai-chaosheng", 300);
	set_skill("qimen-bagua", 400);
	set_skill("qimen-baguazhen",350);
	set_skill("fuxue-shou", 350);
	set_skill("finger", 350);
	set_skill("tanzhi-shengong",300);
	set_skill("parry", 350);
	set_skill("sword", 350);
	set_skill("yuxiao-jian", 400);
	set_skill("literate", 400);
	map_skill("force", "bihai-shengong");
	map_skill("dodge", "luoying-shenfa");
	map_skill("hand", "fuxue-shou");
	map_skill("parry", "yuxiao-jian");
	map_skill("sword", "yuxiao-jian");
	map_skill("finger", "tanzhi-shengong");
	prepare_skill("finger", "tanzhi-shengong");
	create_family("桃花岛", 1, "岛主");
	set("class", "taoist");
	set("book_court", 1);

	set("shen_type",1);set("score",10000);setup();

	set("chat_chance", 2);
	set("chat_msg", ({
		"黄药师自言自语道：「傻姑又在偷懒了，哎，我真是对不起灵风呀。」\n",
		"黄药师喃喃道：「阿衡……阿衡……」\n",
		"黄药师喃喃道：「阿衡……都是我不好，是我害了你，我不该贪图那本九阴真经。」\n",
		"黄药师自言自语道：「好久没有见到蓉儿了。哎，我这个俏女儿怎么会看上那个傻小子郭靖。」\n",
	}) );
    set_temp("apply/armor", 300);
    set_temp("apply/damage", 450);

	setup_no1master();
	carry_object("/d/taohuadao/obj/lvpao")->wear();
	carry_object("/d/taohuadao/npc/obj/yuxiao")->wield();
}
string ask_zhenjing()
{
	object me = this_player();
	me->set_temp("askedzhenjing",1);
	return "唉，都怪我不好，为什么让阿衡又默写一遍真经呢？\n"
		"最可恨的是梅超风和陈玄风这两个徒儿竟然偷走了九阴真经！";
}

int accept_object(object me, object ob)
{
	object room;
	object zhenjing;
	me = this_player();
	if( ob->id("jiuyin zhenjing") )
	{
		call_out("destroy",1,ob);
		if(!me->query_temp("askedzhenjing"))
		{
			message_vision (HIR"黄药师见到九阴真经在$N手上勃然大怒：我已经在阿衡灵前发誓谁看过真经就要死！\n"NOR,me);
			set("max_qi",50000);
			set("eff_qi",50000);
			set("qi",50000);
			kill_ob(me);
			return 1;
		}
		else
		{
			me->set_temp("givezhenjing",1);
			tell_object(me,HIW"黄药师大喜：你果然帮我找回九阴真经？要是你能帮我抓回梅超风这个孽徒，我当感激不尽！\n");
			return 1;
		}
	}//如果给的是九阴真经
	if( ob->id("mei chaofeng") )
	{
		ob->move(this_object());
		room=load_object("/d/guiyunzhuang/shandong");
		ob->move(room);
		if(!me->query_temp("askedzhenjing")||!me->query_temp("givezhenjing"))
		{
			message_vision(HIR"黄药师见到梅超风昏迷不醒勃然大怒：「$N竟敢欺负我徒儿！受死吧！」\n"NOR,me);
			set("max_qi",50000);
			set("eff_qi",50000);
			set("qi",50000);
			kill_ob(me);
			return 1;
		}
		else
		{
		/*
		essage_vision(HIW"黄药师大笑道：$N果然并非泛泛之辈,颇有侠义之风，\n我想如果阿衡知道九阴真经在$N这样的人手中在九泉之下也该瞑目了！\n黄药师将$N对九阴真经不明白的地方向$N讲解了一遍，$N觉得茅塞顿开！\n最后，黄药师又将九阴真经交到$N手中.\n"NOR,me);
		huang->set("fighting",0);
		zhenjing=load_object("/d/gumu/obj/zhenjing.c");
		zhenjing->move(me);
		*/
			if(me->query_temp("givenzhenjing"))
			{
				message_vision("怎么？闲得无聊，又给黄药师教训徒儿来了？呵呵。\n",me);
				return 1;
			}
			message_vision(HIB"黄药师见到$N将梅超风带来大喜过望。$N乘着黄药师高兴之际向其请教九阴真经方面的问题。\n"
				"黄药师开始把脸一沉，随后在地上随便拣了一根树枝，用树枝在地上画了一个七尺见方的圆圈。\n"
				"黄药师笑道：$N若能在一柱香时间内将黄某打败或逼出此圈，黄某就答应你！(fight)\n"NOR,me);
			me->set_temp("givemei",1);
			return 1;
		}
	}
	if( ob->id("gem") )
	{
	    if(me->query_temp("ask_zhugenu") != 1)
	    {
	        message_vision("无功不受禄，$N请拿回去。\n",me);
	    }
	    else
	    {
	        if(ob->query("material") != "sui")
	        {
	            message_vision("黄药师摇摇头：内子喜欢的是玉髓。\n",me);
	            return 0;
	        }
	        else if(ob->query("level") < 8)
	        {
	            message_vision("黄药师大怒：你竟敢拿这种垃圾货色来，亵渎内子亡灵！\n",me);
	            return 0;
	        }
	        else
	        {
	            command("smile");
	            message_vision("$N既然有心，我就将这诸葛连弩的秘密告诉你。\n",me);
	            me->set("qimen-bagua/jiemi",1);
	            me->delete_temp("ask_zhugenu");
	            call_out("destroy",1,ob);
	        }	        
	    }
	    return 0;
	}
	return 0;
}

int timeout(object huang,object me)
{
	if(huang->is_fighting())
	{
		message_vision(HIY"突然，黄药师一招「如影随形」鬼魅般的绕到了$N身后，只轻轻一推，$N一个不稳甩出圈外！\n"NOR,me);
		huang->remove_all_enemy();
		me->remove_all_enemy();
		message_vision(HIR"黄药师笑道：「承让！看来$N资质平庸，不适合学习九阴真经中的上乘武功。$N还是请回吧。」\n"NOR,me);
		me->set_temp("halted",1);
		huang->set("fighting",0);
		set("max_qi",6000);
		set("eff_qi",6000);
		set("qi",6000);
	}
	return 1;
}

void init()
{
	object ob;
	mapping fam;
	::init();
	ob = this_player();
	add_action("do_none", "fight");
	add_action("do_none",  "hit");
	add_action("do_none",  "kill");
	add_action("do_none",  "steal");
	add_action("do_learn", "learn");
	add_action("do_leave",  "leave");
}

string ask_for_leave()
{
	object me;

	me = this_player();

	if( (string)me->query("family/family_name") != "桃花岛")
		return "你非我桃花岛弟子，脱离门派的事情我作不得主。";

	me->set_temp("pending/leave_taohua", 1);
  return "如果" + RANK_D->query_respect(me) + "真想离我桃花岛而去，就请下决心(leave)吧！";
}

int do_leave()
{
	object me = this_player();
	
	if (me->query_temp("pending/leave_taohua") != 1)
		return 0;
	message_vision("$N对$n说道：「从此你就不再是我桃花岛门下了，请好自为之！」\n",this_object(), me );
	tell_object(me,HIR "你决定叛出桃花岛门下！\n" NOR);
	me->delete_temp("pending/leave_taohua");
  me->expell_family("桃花岛");
	if (me->query("combat_exp") >= 1000)
		me->add("betrayer",1);
	return 1;
}	

int do_learn()
{
	object ob = this_player();
	if((int)ob->query("shen") < -10000 && (string)ob->query("family/master_id") == "huang yaoshi")
	{
		command("say 你屡次在外杀戮良民，败坏我的名声。我黄药师不会教你这个徒弟。\n");
		return 1;
	}
	return 0;
}

int do_none()
{
	object me = this_player();
	if (!userp(me)) return 0;
	if(this_object()->query("fighting"))
	{
		tell_object(me,HIR"别人比武，你捣什么乱？\n"NOR);
		return 1;
	}
	else return 0;
}

int accept_fight(object huang)
{
	object me = this_player();
	huang = this_object();
	if(huang->query("fighting")) return 1;
	if(me->query_temp("givemei")&&!me->query_temp("givenzhenjing"))
	{
		say(me->name() + "对黄药师说：好吧，那在下就献丑了！\n");
		me->set_temp("halted",0);
		huang->set("fighting",1);
		remove_call_out("checking");
		call_out("checking", 1, huang, me);
		call_out("timeout", 30,huang,me);
		set("max_qi",50000);
		set("eff_qi",50000);
		set("qi",50000);
		return 1;
	}
	else
	{
		return 0;
	}
}

int checking(object huang, object me)
{
	object zhenjing;
	if (huang->is_fighting())
	{
		call_out("checking",2, huang, me);
		return 1;
	}
	if ( !present(me, environment()) )
	{
		huang->set("fighting",0);
		set("max_qi",6000);
		set("eff_qi",6000);
		set("qi",6000);
		huang->remove_all_enemy();
		return 1;
	}
	if(me->query_temp("halted"))
		return 1;
	if(huang->query("qi")<25000)
	{
		message_vision(HIW"黄药师大笑道：「$N果然并非泛泛之辈，颇有侠义之风，\n"
  			"我想如果阿衡知道九阴真经在$N这样的人手中在九泉之下也该瞑目了！」\n"
  			"黄药师将$N对九阴真经不明白的地方向$N讲解了一遍，$N觉得茅塞顿开！\n"
  			"最后，黄药师又将九阴真经交到$N手中。\n"NOR,me);
		set("max_qi",6000);
		set("eff_qi",6000);
		set("qi",6000);
		huang->set("fighting",0);
		me->set_temp("givenzhenjing",1);
		zhenjing=load_object("/d/gumu/obj/zhenjing.c");
		zhenjing->move(me);
		me->set("canread",1);
		return 1;
	}
	else
	{
		message_vision(HIW"黄药师笑道：「看来$N资质平庸，难以理解九阴真经中的个中含义，还是请回吧！」\n"NOR,me);
		huang->set("fighting",0);
		set("max_qi",6000);
		set("eff_qi",6000);
		set("qi",6000);
		return 1;
	}
	huang->set("fighting",0);
	set("max_qi",6000);
	set("eff_qi",6000);
	set("qi",6000);
	return 1;
}
void attempt_apprentice(object me)
{
	object ob;
	ob = this_player();
	if ((string)ob->query("family/family_name") != "桃花岛")
	{
		command("say 我派是修心养性之派。\n");
		command("say" + RANK_D->query_respect(ob) + "要想拜我，可以先拜我的弟子。");
		return;
	}
    if ((int)ob->query_skill("qimen-bagua", 1) < 110 )
	{
		command("say 桃花岛的功夫有很多和奇门术数有很深的联系。\n");
		command("say" + RANK_D->query_respect(ob) + "你是否应在奇门八卦上多下点功夫。");
		return;
	}
	if ((int)ob->query_skill("bihai-shengong", 1) < 200 )
	{
		command("say 桃花岛的功夫最讲究内力，内功太差无法领悟桃花岛高深的武功。\n");
		command("say" + RANK_D->query_respect(ob) + "你是否应在碧海神功上多下点功夫。");
		return;
	}
	if (ob->query_int() < 40)
	{
		command("say 我桃花岛的武功全靠自己深入领会。");
		command("say 要想达到返璞归真之境，悟性太差是不行的。");
		command("say " + RANK_D->query_respect(ob) + "的悟性还有潜力可挖，先请回吧。");
		return;
	}
	if ((int)me->query("shen") < -5000)
	{
		command("say 我虽然人称东邪，也不是嗜杀之辈。\n");
		return;
	}
	CHANNEL_D->do_channel(this_object(), "jh", "黄药师冷冷地看了一圈在场众人。", -1);
	CHANNEL_D->do_channel(this_object(), "jh", "桃花岛弟子"+ob->query("name")+"在江湖中历练，请各位朋友多多照应。");
	command("recruit " + ob->query("id"));
	if ((string)ob->query("gender")=="女性")
		ob->set("title",RED"桃花岛"NOR + HIW" 岛主亲传弟子"NOR);
	else
		ob->set("title",RED"桃花岛"NOR + YEL" 岛主亲传弟子"NOR);
//title系统记录玩家title by seagate@pkuxkx
	ob->set_title(TITLE_RANK, ob->query("title"));
}

void consider()
{
	object *enemy,target,obj;
	enemy = query_enemy() - ({ 0 });
	target = enemy[random(sizeof(enemy))];
	switch( random(3))
	{
	case 0:
		command("wield xiao");
		command("perform sword.xiaohua " + target->query("id"));
		command("unwield xiao");
		break;
	case 1:
		obj = new("/d/taohuadao/obj/shizi");
		obj->move(this_object());
		command("perform finger.tan " +target->query("id"));
		break;
	case 2:
		command("wield xiao");
		command("perform sword.chan " + target->query("id"));
		command("unwield xiao");
		break;
	}
}

string ask_me()
{
	mapping fam;
	object ob;
	if (!(fam = this_player()->query("family"))
		|| fam["family_name"] != "桃花岛")
		return RANK_D->query_respect(this_player()) +
			"你也来偷窥我的玉箫？黄药师哼了一声。";
	if((string)this_player()->query("family/master_id") != "huang yaoshi")
		return "你的身份太低，本岛主怎能将此物交与你保管。";
	if (this_player()->query_skill("bihai-shengong", 1) < 50)
		return "玉箫威力极大，可" + RANK_D->query_respect(this_player()) + "玉箫剑法太差，\n"
			"要去也没用。" + RANK_D->query_respect(this_player()) + "还是钻心练功吧。\n";
	if (query("book_court") < 1)
		return "你来晚了，本派的玉箫不在这里。";
	add("book_court", -1);
	ob = new("/d/taohuadao/npc/obj/yuxiao");
	ob->move(this_player());
	return "好吧，这把玉箫你就拿回去保管吧。";
}
string ask_dan()
{
	mapping fam;
	object ob;
	if(!(fam = this_player()->query("family"))
		|| fam["family_name"] != "桃花岛")
		return RANK_D->query_respect(this_player()) +
			"你非本门派弟子，从何提起这事？";
	if (query("book_court") < 1)
		return ("你来晚了，我现在身上没有天王保命丹。");
	add("book_court", -1);
	ob = new("/d/taohuadao/npc/obj/baoming-dan");
	ob->move(this_player());
	return "我这颗天王保命丹你就拿去吧。";
}
string ask_zhou()
{
	if (this_player()->query_temp("zyhb/zbt"))
	{
		this_player()->start_busy(1);
		return "我不是已经告诉你了吗！";
	}
	this_player()->set_temp("zyhb/zbt", 1);
	say("黄药师说道：「这家伙有九阴真经的上卷，就是死也不肯交出来。」\n");
	say("黄药师「哼」地冷笑一声。\n");
	return "我用“桃花迷阵”将他困在岛上，看他能撑到几时！";
}
string ask_taohua()
{
	if (this_player()->query_temp("zyhb/bhcs") || this_player()->query_temp("zyhb/bhcs0"))
	{
		this_player()->start_busy(1);
		return "我不是已经告诉你了吗！";
	}
	if (this_player()->query_temp("zyhb/zbt"))
	{
		this_player()->set_temp("zyhb/bhcs0", 1);
		return "要走出桃花迷阵必须由我的“碧海潮生曲”做导引，否则任你天大本领也走不出去！";
	}
	return "你问这个干什么？";
}
int zyhb_permit(object me)
{
	if (!me->is_ghost()&&environment(me)==environment(this_object()))
	me->set_temp("zyhb/bhcs", 1);
	return 1;
}
string ask_bhcs()
{
	object xiao;
	if (this_player()->query_temp("zyhb/bhcs"))
	{
		this_player()->start_busy(1);
		return "我已经给你演奏过一次了啊！";
	}
	if (this_player()->query_temp("zyhb/bhcs0") && !this_player()->query("zyhb"))
	{
		//此处可能会被玩家利用来NK，请巫师注意---vast
    if(query("startroom") == file_name(environment()))
    {
			say("黄药师说道：「那我就给你演奏一曲吧！」\n\n");
			xiao = new("/d/taohuadao/npc/obj/yuxiao");
			xiao->move(this_object());
			command("wield xiao");
			command("exert bhcs " + this_player()->query("id"));
			command("unwield xiao");
			destruct(xiao);//new一把玉箫，用完之后dest，不使用黄药师身上那把，以免出现bug---vast注
			call_out("zyhb_permit",4,this_player());
			this_player()->add_busy(4);
			return "你可要仔细记好了！";
	  }
	  else
	  	return "我现在有事在外面，等我回桃花岛再说吧。";
	}
	return "此曲精深奥妙，岂可轻易示人。";
}
 string ask_lyz()
 {
         mapping fam;
         if(!(fam = this_player()->query("family")) || fam["family_name"] != "桃花岛") 
                 return RANK_D->query_respect(this_player()) + "你非本门派弟子，想偷学桃花绝学？";
                 
         if( this_player()->query_skill("bihai-shengong", 1) < 120 || this_player()->query_skill("force") < 200 )
                 return "你的内功修为不够，无法学习落英神剑掌。";                 

         if(this_player()->query("betrayer"))
                 return "我不能相信你，谁知道你叛师不？";

         if(this_player()->query("thd/lyz"))
                 return "我不是已经告诉你了吗！";

         this_player()->set("thd/lyz", 1);
         
         return "落英神剑掌是本门绝学，死丫头练功常不专心，就拿来打蜡烛玩。";
 }
 
string ask_zhugenu()
{
    mapping fam;
    object p = this_player();
    
    if(!(fam = this_player()->query("family")) || fam["family_name"] != "桃花岛") 
        return RANK_D->query_respect(this_player()) + "你非本门派弟子，想偷学桃花绝学？";
    if( this_player()->query_skill("qimen-bagua", 1) < 100)
         return "你的奇门八卦学的太差，跟你讲了也没用。";
                         
    if(this_player()->query("betrayer"))
        return "我不能相信你，谁知道你会不会背叛我？";

    if(this_player()->query("qimen-bagua/jiemi"))
        return "我不是已经告诉你了吗！";    
    p->set_temp("ask_zhugenu",1);
    return "诸葛连弩乃是三国孔明所创，精妙无比，威力惊人。内子曾经苦研数年，终于解开了其中的奥妙。过几日正是内子忌日，你若是想学就去找一颗内子最爱的玉髓来吧。";
}

void heal()
{
	object ob=this_object();
	if(ob->query("eff_qi") < ob->query("max_qi"))
	{
		command("exert heal");
		command("enforce 150");
		return;
	}
	if(ob->query("qi") < ob->query("eff_qi"))
	{
		command("exert recover");
		return;
	}
	if(ob->query("jing") < ob->query("eff_jing"))
	{
		command("exert regererate");
		return;
	}
}
void destroy(object ob)
{
	destruct(ob);
	return;
}

#include "/kungfu/class/masterdie.h"