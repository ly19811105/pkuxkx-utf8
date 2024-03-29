//modified by iszt@pkuxkx, 2007-02-11
//modified by zine@pkuxkx，2013-11-1 close current chaoting and transfer it into Song.
#include <ansi.h>
#include <title.h>
inherit NPC;
//inherit F_MASTER;

#include "/d/beijing/beijing_defs.h"
#include "/d/beijing/job_info.h"
#include "/d/beijing/autok.h"

#include <no1master.h>
string * province=({"两广","两江","四川","直隶"});
string * pin9=({"外委把总","兰翎长","协领"});
string * pin8=({"典仪","亲军校","前锋校","护军校","骁骑校","千总"});
string * pin7=({"七品典仪","盛京游牧副尉","城门史","马厂协领","把总","安抚使司佥事"});
string * pin6=({"卫千总","安抚使司副使","内务府六品兰翎长","六品典仪","门千总","营千总","宣抚使司佥事","安抚使司同知","副招讨使","百户","兰翎侍卫","整仪尉"});
string * pin5=({"关口守御","防御","守备","宣慰使司佥事","宣抚使司同知","千户","分管佐领","监守信礮官","步军校","步军副尉","三等侍卫","治仪正","守御所千总","河营协办守备","安抚使","招讨使","宣抚使司副使","副千户","四等侍卫","委署前锋参领","委署护军参领","委署鸟枪护军参领","委署前锋侍卫","下五旗包衣参领","五品典仪","印物章京","三等护卫"});
string * pin4=({"贝勒府司仪长","侍卫领班","指挥佥事","宣慰使司同知","二等侍卫","云麾使","副护军参领","副前锋参领","副骁骑参领","太仆寺马厂驼厂总管","宣抚使","宣慰使司副使","二等护卫","四品典仪","城门领","包衣副护军参领","包衣副骁骑参领","包衣佐领","防守尉","佐领","都司"});
string * pin3=({"城守尉","骁骑参领","王府长史","参将","指挥使","一等侍卫","火器营翼长","健锐营翼长","前锋参领","护军参领","游击","五旗参领","协领","宣慰使","指挥同知","包衣护军参领","包衣骁骑参领","王府一等护卫"});
string * pin2=({"副将","散秩大臣","副都统","总兵","右翼前锋营统领","左翼前锋营统领","八旗护军统领","銮仪使"});
string * pin1=({province[random(sizeof(province))]+"将军",province[random(sizeof(province))]+"都统",province[random(sizeof(province))]+"提督","提督九门步军巡捕五营统领","内大臣","领侍卫内大臣","掌銮仪卫事大臣"});
string * jue3=({"忠诚伯"});
string * jue2=({"延恩侯","同安侯"});
string * jue1=({"忠襄公","承恩公","孝愍公","海澄公","忠锐公","辅国公","镇国公","鹿鼎公"});
void set_shiwei_status(int);
string do_toujun();
void do_answer(string);
int do_decide();
string guard_door();
string ask_job();
string do_task();
string ask_leadership();
string ask_strategy();
string ask_badman();
void do_check(object ob);
string ask_feizei();
string ask_jianzhan();
string do_give();
string do_fail();
int ask_leave();
void greeting(object ob);
void create()
{
	set_name("多隆", ({"duo long", "duo", "long"}));
	set("title", "侍卫总管");
	set("long",
		"作为侍卫总管，多隆深受皇上器重。\n"
		"他十八般武艺样样精通，对行军打仗颇有心得。\n"
		"御林军的任务也都从他这里分派。\n"
	);

	set_max_encumbrance(100000000);
	set("no_get", 1);
        set("attitude","friendly");
	set("pin", 3);
	set("max_qi", 1800);
	set("eff_qi", 1800);
	set("qi", 1800);

	set("max_jing", 1800);
	set("eff_jing", 1800);
	set("jing", 1800);

	set("jingli", 3600);
	set("max_jingli", 3600);

	set("neili", 3600);
	set("max_neili", 3600);

	set("jiali", 180);

	set("combat_exp", 1000000);
	set_skill("force", 220);
	set_skill("dodge", 180);
	set_skill("cuff", 180);
	set_skill("strike",180);
	set_skill("hand",180);
	set_skill("parry", 180);
	set_skill("blade",180);
	set_skill("sword",180);
	set_skill("staff",180);
	set_skill("whip",180);
	set_skill("axe",180);
	set_skill("halberd",180);
	set_skill("spear",180);
	set_skill("claw",180);
//	set_skill("strategy", 200);
//	set_skill("leadership", 200);
/*	set_skill("literate", 100);
  set_skill("strategy", 100);
  set_skill("leadership", 100);
	set_skill("bixue-xinfa", 220);
	set_skill("longfeng-xiang", 180);
	set_skill("qingmang-jian", 180);
	set_skill("juemen-gun", 180);
	set_skill("fenglei-dao", 180);
	set_skill("taizu-quan", 180);
	set_skill("kuangfeng-dao", 180);
	set_skill("kuangfeng-jian", 180);
	set_skill("lujia-ji", 180);
	set_skill("bainiao-qiangfa", 180);
	set_skill("huzhua-shou", 180);
	set_skill("juehu-zhang", 180);
	set_skill("kuihua-zhua", 180);
	set_skill("duanyun-bian", 180);
	set_skill("leiting-axe", 180);

	map_skill("force", "bixue-xinfa");
	map_skill("sword", "kuangfeng-jian");
	map_skill("blade", "kuangfeng-dao");
	map_skill("dodge", "longfeng-xiang");
	map_skill("strike", "juehu-zhang");
	map_skill("parry", "huzhua-shou");
	map_skill("hand", "huzhua-shou");
	map_skill("whip", "duanyun-bian");
	map_skill("halberd", "lujia-ji");
	map_skill("axe", "leiting-axe");
	map_skill("claw", "kuihua-zhua");
	map_skill("staff", "juemen-gun");
	map_skill("spear", "bainiao-qiangfa");
	map_skill("cuff", "taizu-quan");

	prepare_wskill("sword", "kuangfeng-jian");
	prepare_wskill("blade", "kuangfeng-dao");

	prepare_skill("strike", "juehu-zhang");
	prepare_skill("hand", "huzhua-shou");

*/
	set("gender", "男性");
	set("age", 35);
        set("book_count", 10);
	set("class", "officer");
	//create_family("朝廷", 2, "官员");
	set("shen_type",1);set("score",5000);setup();
	carry_object("/d/beijing/npc/obj/shiweicloth")->wear();
	carry_object("/d/city/obj/gangjian")->wield();
	carry_object("/clone/weapon/gangdao")->wield();

	set("inquiry", ([
	/*"飞贼" : (: ask_feizei :),
	"巡逻" : (: ask_job :),
    "leave" : (: ask_leave :),
    "辞官" : (:ask_leave:),
	"完成" : (: do_task :),
	"抓坏人" : (: ask_badman :),
	"守门" : (: guard_door :),
	"投军" : (: do_toujun :),
	"入伍" : (: do_toujun :),
	"join" : (: do_toujun :),
	"为官之道" : (: ask_leadership :),
	"兵法战策" : (: ask_strategy :),
	"监斩" : (: ask_jianzhan:),
	"奖励": (:do_give:),
	"失败": (:do_fail:),
	"晋升" : "这个你到兵部去问明珠尚书吧。",
	"promotion" : "这个你到兵部去问明珠尚书吧。",
	"升官" : "这个你到兵部去问明珠尚书吧。",*/
	"here" : "这里是侍卫营。不得喧哗。",
//        "抓猪头" : (HIC"最近" + (random(2)?(random(2)?("冰冰"):("行云")):(HIG"流氓"HIY"猪"NOR)) + HIC"比较猪头，你去把他捉拿归案。"NOR),
	]));

	setup_no1master();
}

void init()
{
	object ob= this_player();

	::init();
	if( !query_heart_beat(this_object()) ) set_heart_beat(1);

	/*add_action("do_decide", "decide");
	ob = this_player();
	do_check(ob);*/
	if( interactive(ob) && !is_fighting())
	{
		//remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

/*int count_pot(object me)
{
    int force_lv=me->query_skill("bixue-xinfa",1),i,result=0,pot;
    for (i=1;i<=force_lv;i++)
    {
        pot=i*i/5;
        if (pot<1)
        {
            pot=1;
        }
        result+=pot;
    }
    if (result<50000)
    {
        result=50000;
    }
    //每人最少给50000点，防止没有碧血神功的再啰嗦了。
    return result;
}*/

/*int ask_leave()
{
    object me=this_player();
    if (me->query("family/family_name")!="朝廷")
    {
        command("hmm");
        return 1;
    }
    if (me->query("combat_exp")<30000000)
    {
        command("say 你的经验还很低，再考虑考虑清楚吧。");
        return 1;
    }
    if (me->query("family/enter_time")>=1329093149)
    {
        command("say 辞官？做梦吧你？");
        return 1;
    }
    if (me->query("family/master_name")!="多隆")
    {
        command("hmm");
        return 1;
    }
    if (me->query("left_ct"))
    {
        tell_object(me,"你不是之前离开过了吗？又发现了哪门子的bug?\n");
        return 1;
    }
    command("say 你真的决定了要离开朝廷吗？所有朝廷武功以及其他与朝廷相关的东西都将被扣除。如果决定请输入(decide)。");
    tell_object(me,HIR+"此时决定离开(decide)并拜入别的门派将不会增加判师次数，你可获得潜能补偿"+count_pot(me)+"点。\n"+NOR);
    me->set_temp("permit_to_leave_ct",1);
    return 1;
}*/

void greeting(object ob)
{
	int bonus,old_pot;
	string *skname;
	mapping skills;
	int i;

	if( !ob || environment(ob) != environment() ) return;
	auto_kill(ob);
}
/*
void do_check(object ob)
{
	if(ob->query("class") == "officer"
		&& ob->query_condition("bjkiller"))
	{
		message_vision(HIR"$N对$n怒喝道：「身为朝廷官员居然知法犯法，念你初犯姑且记你一过，记住，若有再犯军法伺候！！」\n"NOR, this_object(), ob);
		ob->add("chaoting/mistake", 1);
		ob->set("chaoting/salary", ob->query("chaoting/salary") + 7200);
		ob->clear_condition("bjkiller");
		tell_object(ob,"你被扣除了一个月的俸禄。\n你被兵部记过一次。\n");
	}
	if(ob->query("class") == "officer"
		&& ob->query("chaoting/job_fail") / (ob->query("chaoting/job_bonus") + 1) >= 10 )
	{
		message_vision(HIR"$N对$n怒喝道：「身为朝廷官员屡次玩忽职守，念你初犯姑且记你一过，记住，若有再犯军法伺候！！」\n"NOR, this_object(), ob);
		ob->add("chaoting/mistake", 1);
		ob->set("chaoting/salary", ob->query("chaoting/salary") + 7200);
		ob->add("chaoting/job_bonus", 1);
		tell_object(ob,"你被扣除了一个月的俸禄。\n你被兵部记过一次。\n");
	}
	if(ob->query("class") == "officer" && ob->query("chaoting/mistake") >= 10 )
	{
		message_vision(HIR"$N对$n怒喝道：「身为朝廷官员屡次知法犯法，来人啊，给我拉出去斩了！！」\n"NOR, this_object(), ob);
		message_vision(HIR"$N吓得面如土灰，全身不断哆嗦。\n"NOR, ob);
		ob->start_busy(100);
		remove_call_out("responsing");
		call_out("responsing", 3, ob);
	}
}
void processing(object ob)
{
    if (ob->is_ghost()) return;
	ob->revive();
	write(HIW "\n你恢复了神志，环顾四周，只见数十名刽子手将你团团围起来，\n"
		"一片雪亮的刀光逼得你眼都睁不开。正前方的高台上放着一把\n"
		"铡刀，笼罩着浓烈的肃杀的气氛。\n\n" NOR);
	message_vision(HIR "周围挤满了围观群众，$N心道：「这回真的完了。」\n"
			"旁边的监斩官员扔出一道令牌，.....\n"
			"刽子手大刀一挥..........\n\n" NOR, ob);
	ob->set("chaoting/mistake",0);
	ob->add("chaoting/decapitate", 1);
	ob->start_busy(0);
    ob->receive_damage("qi", 0, this_object());
	ob->die();
	CHANNEL_D->do_channel(this_object(), "rumor", ob->name()+"在菜市口被斩首示众！");
	return;
}
void responsing(object ob)
{
	if( !ob||ob->is_ghost() ) return;
	message_vision(HIR "兵营内冲进来几个官兵，将$N五花大绑！\n" NOR, ob);
	remove_call_out("beating");
	call_out("beating", 8, ob);
	return;
}
void beating(object ob)
{
	if( !ob||ob->is_ghost() ) return;
	message_vision(HIY "\n$N喝道：「将$n押到菜市口斩首示众！！」\n" NOR, this_object(), ob);
	message_vision(HIR "官兵们一涌而上，乱棒齐下将$N打得昏了过去......\n" NOR, ob);
	ob->move("/d/beijing/caishikou");
	ob->unconcious();
	remove_call_out("processing");
	call_out("processing", 15, ob);
}

int accept_object(object me, object obj)
{
	object ob = this_player();
	int reduce, bonus = 100;
	int sc, pot, exp, rep, shen;
	string beauty;
	//抓坏人
	this_object()->start_busy(3);
	if(stringp(beauty = ob->query("chaoting/badman")))
	{
		if(obj->query("money_id") && obj->value() >= 2500)
		{
			message_vision("$N叹道：罢了罢了，这么点小事都办不成！\n", this_object());
			ob->delete("chaoting/badman");
			ob->delete_temp("badman");
			ob->add("chaoting/job_fail", 1);
			tell_object(me, "到目前为止你总共任务失败" + ob->query("chaoting/job_fail") + "次。\n");
			return 1;
		}
		if(obj->query("money_id") && obj->value() < 2500)
		{
			message_vision("$N看了你一眼道：这也太少了吧！\n", this_object());
			return 0;
		}
		if(obj->name() != ob->query("chaoting/badman"))
		{
			message_vision("$N大怒道：滚！我要的不是这个人！\n", this_object());
			return 0;
		}
		if(userp(obj))
		{
			message_vision("$N大怒道：想用这套来蒙骗我，门都没有！\n", this_object());
			return 0;
		}
		if(!obj->is_character())
		{
			message_vision("$N大怒道：这是什么烂东西啊！\n", this_object());
			return 0;
		}

		if (ob->query_temp("badman/times") > 10)
		ob->set_temp("badman/times", 6);

		exp = info_beauty[beauty] * ob->query_temp("badman/times");
		pot = exp / 8;

		if(ob->query("class") == "officer")
		{
			ob->add("score", 1);
			ob->add("combat_exp", exp);
			ob->add("exp/chaoting", exp);
			ob->add("potential", pot);
			ob->add("pot/chaoting", pot);
			ob->add("shen", 100);
			tell_object(ob,"你对朝廷的贡献度提高了。\n");
			tell_object(ob,"你的经验增加了" + chinese_number(exp) + "点。\n");
			tell_object(ob,"你的潜能增加了" + chinese_number(pot) + "点。\n");
			tell_object(ob,"你的道德提高了。\n");
			ob->delete("chaoting/badman");
			ob->add("chaoting/catchman", 1);
			call_out("destroy_beauty", 1, obj);
			return 1;
		}
		else
		{
			ob->add("repute", 100);
			ob->add("combat_exp", exp);
			ob->add("exp/chaoting", exp);
			ob->add("potential", pot);
			ob->add("pot/chaoting", pot);
			ob->add("shen", 100);
			tell_object(ob,"你的经验增加了" + chinese_number(exp) + "点。\n");
			tell_object(ob,"你的潜能增加了" + chinese_number(pot) + "点。\n");
			tell_object(ob,"你的道德提高了。\n");
			tell_object(ob,"你的江湖声望增加了。\n");
			ob->delete("chaoting/badman");
			call_out("destroy_beauty", 1, obj);
			return 1;
		}
	}
	//取消抓飞贼任务
	if(ob->query("chaoting/catchfeizei"))
	{
		if(obj->query("money_id") && obj->value() >= 10000)
		{
			message_vision("$N叹道：罢了罢了，这么点小事都办不成！\n", this_object());
			ob->delete("chaoting/catchfeizei");
			ob->delete_temp("feizei");
			ob->delete_temp("guanf_huida1");
			ob->add("chaoting/job_fail", 1);
			ob->set("last_feizei_time",time());
			tell_object(me, "到目前为止你总共任务失败" + ob->query("chaoting/job_fail") + "次。\n");
			return 1;
		}
		if(obj->query("money_id") && obj->value() < 10000)
		{
			message_vision("$N看了你一眼道：这也太少了吧！\n", this_object());
			return 0;
		}
	}
	//抓飞贼
	if(obj->query("id") == "cai bao")
	{
		if(obj->query("owner") == ob)
		{
			if(ob->query("chaoting/catchfeizei") && ob->query("class") == "officer")
			{
				if(ob->query("score") < 1400)
				{
				ob->add("score", 1);
				tell_object(ob,"你对朝廷的贡献度提高了。\n");
				}
				ob->delete("chaoting/catchfeizei");
				ob->add("chaoting/feizei", 1);
				call_out("destroying", 1, obj, ob);
				return 1;
			}
			else if(! ob->query("chaoting/catchfeizei"))
			{
				call_out("destroying", 1, obj, ob);
				return 1;
			}
		}
		else
		{
			command( "?" );
			command( "say 这个东西是你找到的么？" );
			return 0;
		}
	}

	command( "hmm" );
	command( "say 你给我这东西做什麽？" );

	return 0;
}

void destroying(object obj, object me)
{
	int kar, exp, pot, sc;
	kar = me->query("kar") * (10 + random(40));
	exp = 2 * kar;
	pot = exp / 8;

	if (me->query("combat_exp") < 1000000)
	{
		exp = exp / 3;
		pot = exp /8;
	}

	me->add("combat_exp", exp);
	me->add("exp/chaoting", exp);
	me->add("potential", pot);
	me->add("pot/chaoting", pot);
	me->add("repute", 100);
	me->add("shen", 1000);

	tell_object(me,"你的经验增加了" + chinese_number(exp) + "点。\n");
	tell_object(me,"你的潜能增加了" + chinese_number(pot) + "点。\n");
	tell_object(me,"你的武林声望增加了。\n");
	tell_object(me,"你的道德提高了。\n");

	if(obj)
		destruct(obj);

	return;
}

string ask_badman()
{
	object me = this_player();
	string *beautys, beauty;

	if( is_fighting() || is_busy())
		return RANK_D->query_rude(me) + "瞎了眼没见我正忙着？！";

	if ( me->query("combat_exp") < 5000 )
	{
		command("shake "+me->query("id"));
		return "你才这两下子恐怕无法胜任这事。";
	}
	if ( me->query("combat_exp") > 800000 || (me->query("pin") < 6 && me->query("class") == "officer"))
	{
		command("shake "+me->query("id"));
		return "你经验太高，没必要作这个了。";
	}

	if (me->query("score") >= 800 && me->query("class") == "officer")
	{
		command("shake "+me->query("id"));
		return "你已经可以升迁了，没必要继续作这个任务。";
	}
	if( stringp(me->query("chaoting/badman")))
	{
		command("slap " + me->query("id"));
		return "先把上一个任务完成了再说，实在做不了就给钱取消吧。";
	}

	if( me->query("chaoting/catchfeizei"))
		return "你把抓飞贼的任务完成了再说吧。";

	if ( me->query("jianzhan/in_dart"))
		return "你先把监斩任务完成了再说吧。";

	if( time() < (int)me->query("chaoting/joytime"))
	{
		if (random(2))
		{
			command("lazy");
			return "最近风平浪静，没有什么案件。";
		}
		command("shake");
		return "我这里没事干了，你下去吧。";
	}

	beautys = keys(info_beauty);

	if(me->query("combat_exp") < 10000)
	{
		beauty = beautys[random(31)];//数量请查阅job_info.h(下同)
	}
	else if(me->query("combat_exp") < 100000)
	{
		beauty = beautys[random(68)];
	}
	else if(me->query("combat_exp") < 500000)
	{
		beauty = beautys[random(89)];
	}
	else
	{
		beauty = beautys[random(sizeof(beautys))];//所有
	}
	command("pat " + me->query("id"));
	me->set("chaoting/badman", beauty);
	me->add_temp("badman/times", 1);
	me->set("chaoting/joytime", time() + 60 + random(20));
	return "最近" + beauty + "为非作歹，你去把他捉拿归案。";
}
void destroy_beauty(object ob)
{
	 destruct(ob);
}

string do_toujun()
{
	object me = this_object();
	object player = this_player();
	object yaopai;
	mapping fam;
	int leave_age;

	if (player->query("class") == "officer")
		return "你开什么玩笑？当心我把你革职查办。";

	if (player->query("gender") == "无性")
	return RANK_D->query_respect(player) + "要进宫做事可以找海公公。";

	// we allow this player to join, check positions available

		if ((string)player->query("family/family_name") == "灵鹫宫"
			&& player->query("lingjiu/xiulian"))
		{
			player->set_temp("chaoting/bai",1);
			return RANK_D->query_respect(player) + "，你现在加入朝廷似乎会有很大损失，你能拿定主意吗？(answer)";

		}
		else
		{
            if (player->query("mingpin"))
            {
                tell_object(player,BLINK HIR"加入我大清就必须放弃在明国的一切成就了。你是否愿意？\n"NOR);
            }
			player->set_temp("chaoting/toujun", 1);
			return "你决定加入朝廷吗？(decide)";
		}

}

void do_answer(string arg)
{
	object me=this_player();
	int time;
	if (!me->query_temp("chaoting/bai")) return;
	if (!arg || (arg != "是" && arg != "能" && arg != "yes"))
		command("say 你说的什么乱七八糟的，看来你是没有诚心，算了！");
	else
	{
		command("say 好吧，"+RANK_D->query_respect(me)+"，我就同意你了！");
		me->set("mud_age",me->query("lingjiu/mud_age"));
		me->set("age",14 + me->query("mud_age")/3600/24);
		me->delete("lingjiu/skill_status");
		me->delete("lingjiu/qi");
		me->delete("lingjiu/eff_qi");
		me->delete("lingjiu/max_qi");
		me->delete("lingjiu/jing");
		me->delete("lingjiu/eff_jing");
		me->delete("lingjiu/max_jing");
		me->delete("lingjiu/jingli");
		me->delete("lingjiu/neili");
		me->delete("lingjiu/max_jingli");
		me->delete("lingjiu/max_neili");
		me->delete("lingjiu/combat_exp");
		me->delete("lingjiu/need_xiulian");
		me->delete("lingjiu/mud_age");
		me->delete("lingjiu/xiulian");
		me->delete("lingjiu/last_xiulian_time");
		me->delete_temp("chaoting/bai");
		//灵鹫的肯定是女性，以下就不判断性别了
		message_vision("$N决定背叛师门，加入朝廷！！\n", me);
		me->delete("family");
		me->set("family", ([
			"family_name"    : "朝廷",
			"enter_time"     : time(),
			]));
		time = me->query("mud_age");
		me->set("chaoting/salary", time);
		me->set("score", 0);
		if ( me->query("combat_exp") >= 1000 ) me->add("betrayer", 1);
		me->set("class", "officer");
		me->set("chaoting/officer", 1);
		me->set("pin", 9);
		me->set("title", NOR"朝廷九品官员 "NOR);
//title系统记录玩家title by seagate@pkuxkx
	  me->set_title(TITLE_RANK, "朝廷九品官员 ");
		message_vision("$N拍着$n的肩膀说道：恭喜你成为朝廷的一员。\n", this_object(), me);
		me->save();
	}
	return;
}

int delete_ct_title(object me)
{
    if (me->get_title(TITLE_RANK)&&strsrch(me->get_title(TITLE_RANK),"朝廷")!=-1)
    {
        me->set_title(TITLE_RANK,"");
    }
    if (me->get_title(TITLE_QUEST1)&&strsrch(me->get_title(TITLE_QUEST1),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST1,"");
    }
    if (me->get_title(TITLE_QUEST2)&&strsrch(me->get_title(TITLE_QUEST2),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST2,"");
    }
    if (me->get_title(TITLE_QUEST3)&&strsrch(me->get_title(TITLE_QUEST3),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST3,"");
    }
    if (me->get_title(TITLE_QUEST4)&&strsrch(me->get_title(TITLE_QUEST4),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST4,"");
    }
    if (me->get_title(TITLE_QUEST5)&&strsrch(me->get_title(TITLE_QUEST5),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST5,"");
    }
    if (me->get_title(TITLE_QUEST6)&&strsrch(me->get_title(TITLE_QUEST6),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST6,"");
    }
    if (me->get_title(TITLE_QUEST7)&&strsrch(me->get_title(TITLE_QUEST7),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST7,"");
    }
    if (me->get_title(TITLE_QUEST8)&&strsrch(me->get_title(TITLE_QUEST8),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST8,"");
    }
    if (me->get_title(TITLE_QUEST9)&&strsrch(me->get_title(TITLE_QUEST9),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST9,"");
    }
    if (me->get_title(TITLE_QUEST10)&&strsrch(me->get_title(TITLE_QUEST10),"大清")!=-1)
    {
        me->set_title(TITLE_QUEST10,"");
    }
    if (me->get_title(TITLE_MASTER)&&strsrch(me->get_title(TITLE_MASTER),"朝廷")!=-1)
    {
        me->set_title(TITLE_MASTER,"");
    }
    me->set("title","普通百姓");
    me->delete("multi_title");
    return 1;
}

int leave_ct(object me)
{
    mapping sk=me->query_skills();
    string *sname;
    string *skills=({"leadership","strategy","bainiao-qiangfa","bixue-xinfa","duanyun-bian","fenglei-dao","huzhua-shou","juehu-zhang","juemen-gun",
        "kuangfeng-dao","kuangfeng-jian","kuihua-zhua","leiting-axe","longfeng-xiang","lujia-ji","qingmang-jian","taizu-quan"});
    int i,pot;
    me->delete("chaoting");
    me->delete_temp("chaoting");
    me->delete("family");
    me->delete("score");
    me->delete("class");
    me->delete("bingbu");
    me->delete("members");
    if (!sk)//无任何技能不处理，不补偿
    {
        return 1;
    }
    pot=count_pot(me);
    sname=keys(sk);
    me->map_skill(sk);
    me->reset_action();
    for(i=0;i<sizeof(sname);i++)
    {
        if (member_array(sname[i],skills)!=-1)
        {
            me->delete_skill(sname[i]);
            tell_object(me,"删除技能"+sname[i]+"。\n");
        }
    }
    me->add("potential",pot);
    me->set("left_ct",1);
    tell_object(me,HIC+"你的潜能被补偿了"+chinese_number(pot)+"点。\n"+NOR);
    tell_object(me,HIG+"你现在和朝廷全无任何关系，可以拜入其他门派或者选择当一个普通百姓了。\n"+NOR);
    delete_ct_title(me);
    me->save();
    return 1;
}

int do_decide()
{
	object player = this_player();
    object me = this_player();
	int time;
	string name;
    string* color=({HIR,RED,HIY,YEL,HIB,BLU,HIG,GRN,HIC,CYN,MAG,HIM,HIW,WHT});
	string color1=color[random(sizeof(color))];
	name = player->query("name");
    if (me->query_temp("permit_to_leave_ct"))
    {
        if (me->query("left_ct"))
        {
            tell_object(me,"你不是之前离开过了吗？又发现了哪门子的bug?\n");
            return 1;
        }
        me->delete_temp("permit_to_leave_ct");
        leave_ct(me);
        return 1;
    }
	if (!player->query_temp("chaoting/toujun")) return 0;
	if(player->query("class") == "officer")
		return 0;
	if(player->query("chaoting/officer") || player->query("chaoting/eunuch")) 	
		return 0; //added by whuan at 2009-1-10 to fix the bug that officer can cut and join again
    if (player->query("mingpin"))
        {
            
            tell_object(player,"你放弃了自己在明国的所有成就，加入大清。\n");
            message("chat",HIW"【大明】我朝"+chinese_number(player->query("mingpin"))+"品官员"+player->query("name")+"投降清廷。\n"+NOR,users());
            if (me->get_title(TITLE_QUEST1) && strsrch(me->get_title(TITLE_QUEST1), "大明")>=0 )
            {
                me->set_title(TITLE_QUEST1,color1+"闲云野鹤"+NOR);
            }
            if (me->get_title(TITLE_QUEST2) && strsrch(me->get_title(TITLE_QUEST2), "大明")>=0 )
            {
                me->set_title(TITLE_QUEST2,color1+"闲云野鹤"+NOR);
            }
            if (me->get_title(TITLE_QUEST3) && strsrch(me->get_title(TITLE_QUEST3), "大明")>=0 )
            {
                me->set_title(TITLE_QUEST3,color1+"闲云野鹤"+NOR);
            }
            player->delete("mingpin");
            player->delete("ming");
        }
	if(mapp(player->query("family")))
	{
		message_vision("$N必须先脱离原先的门派：" + player->query("family/family_name")+", 才能转投别的门派。\n", player);
		return 1;
		message_vision("$N决定背叛师门，加入朝廷！！\n", player);
        
		player->delete("family");
		player->set("family", ([
			"family_name"    : "朝廷",
			"enter_time"     : time(),
			]));

		if ( player->query("combat_exp") >= 1000 ) player->add("betrayer", 1);

	}
	else
	{
		message_vision("$N决定加入朝廷！！\n", player);
		player->set("family", ([
			"family_name"    : "朝廷",
			"enter_time"     : time(),
			]));
	}
		time = player->query("mud_age");
		player->set("chaoting/salary", time);
		player->set("score", 0);
		player->set("class", "officer");
//		player->set("chaoting/officer", 1);
		if (player->query("gender") == "男性")
		{
			player->set("title",NOR"朝廷九品官员 "NOR);
			//title系统记录玩家title by seagate@pkuxkx
	    player->set_title(TITLE_RANK, "朝廷九品官员 ");
			player->set("chaoting/officer", 1);
		}
		else if (player->query("gender") == "女性")
		{
			player->set("title",NOR"朝廷九品官员 "NOR);
			//title系统记录玩家title by seagate@pkuxkx
	    player->set_title(TITLE_RANK, "朝廷九品官员 ");
			player->set("chaoting/officer", 1);
		}
		else 
		{
			player->set("title",YEL"朝廷九品官员 "HIM"尚膳监太监"NOR);
			player->set("name","小"+name[0..0]+"子");
			player->set("chaoting/eunuch", 1);
		}

	player->set("pin", 9);
	message_vision("$N拍着$n的肩膀说道：恭喜你成为朝廷的一员。\n", this_object(), player);
	player->save();
	return 1;
}
void attempt_apprentice(object ob)
{
	if(ob->query("class") != "officer")
	{
		command("say " + RANK_D->query_respect(ob) + "是否有意加入朝廷呢？");
		tell_object(ob,"你若想加入朝廷，请ask duo about 入伍。\n");
		return;
	}

	if(ob->query("chaoting/eunuch"))
	{
		command("say " + RANK_D->query_respect(ob) + "要学习武功可以拜海公公为师。");
		return;
	}

	command("say 好吧，那我就收下你了。");
	command("recruit " + ob->query("id"));
}*/

/*void recruit_apprentice(object ob)
{
	int pin;
	string *rank_name, title;
	string *all_color = ({HIR,HIB,HIG,HIY,HIC,HIW,HIM,GRN,YEL});

	if( ::recruit_apprentice(ob) )
	pin = ob->query("pin");
	switch (pin)
	{
	case 9:
	if (ob->query("gender") == "男性")
	title = YEL+pin9[random(sizeof(pin9))]+NOR;
	else if(ob->query("gender") == "女性")
	title = YEL+pin9[random(sizeof(pin9))]+NOR;
	else
	title = HIM"尚膳监太监"NOR;
	break;

	case 8:
	//rank_name = ({ YEL"清兵千总"NOR, YEL"清兵守备"NOR,});
	//title = rank_name[random(sizeof(rank_name))];
	title=YEL+pin8[random(sizeof(pin8))]+NOR;
    break;

	case 7:
	//title = HIC"侍卫营侍卫"NOR;
	title=HIY+pin7[random(sizeof(pin7))]+NOR;
    break;

	case 6:
	//rank_name = ({ RED"侍卫营佐领"NOR, RED"侍卫营参将"NOR,});
	//title = rank_name[random(sizeof(rank_name))];
	title=WHT+pin6[random(sizeof(pin6))]+NOR;
    break;

	case 5:
	//title = MAG"侍卫营副都统"NOR;
	title=HIW+pin5[random(sizeof(pin5))]+NOR;
    break;

	case 4:
	rank_name = ({
		BLU"侍卫营都统"NOR,
		BLU"侍卫营云骑尉"NOR,
		BLU"侍卫营骑都尉"NOR,
		BLU"前锋营都统"NOR,
		BLU"前锋营云骑尉"NOR,
		BLU"前锋营骑都尉"NOR,
		});
	title = rank_name[random(sizeof(rank_name))];
    title=CYN+pin4[random(sizeof(pin4))]+NOR;
	break;

	case 3:
	//title = CYN"御前侍卫总管"NOR;
	title=HIY+jue3[random(sizeof(jue3))]+" "+HIB+pin3[random(sizeof(pin3))]+NOR;
    break;

	case 2:
	rank_name = ({
		HIR"平西将军"NOR,
		HIR"镇南将军"NOR,
		HIR"征东将军"NOR,
		HIR"抚远将军"NOR,
		});
	if (ob->query("gender") == "男性")
		title = rank_name[random(sizeof(rank_name))];
	else
		title = HIR"巾帼英雄"NOR;
    title=HIY+jue2[random(sizeof(jue2))]+" "+RED+pin2[random(sizeof(pin2))]+NOR;
	break;

	case 1:
	/*rank_name = ({
		HIY"鹿鼎公"NOR,
		HIY"镇国公"NOR,
		HIY"辅国公"NOR,
		});
	if (ob->query("gender") == "男性")
		title = rank_name[random(sizeof(rank_name))];
	else
		title = HIY"女元帅"NOR;
        if (!ob->query("chaoting/wang")&&!ob->query("chaoting/jiawang"))
        {
            title=HIY+jue1[random(sizeof(jue1))]+" "+HIR+pin1[random(sizeof(pin1))]+NOR;
        }
    
	break;
	}
	title = HIG+ "朝廷" + chinese_number(pin) + "品官员 "NOR + title;
	ob->set("title", title);
	//title系统记录玩家title by seagate@pkuxkx
	ob->set_title(TITLE_RANK, title);
    ob->set("chaoting/newtitle",1);
//修改title请同时修改mingzhu.c里面的相应地方 - vast
}*/

/*string guard_door()
{
	int i, j, pin;
	string gate;
	object ob = this_player();

	if ( ob->query("class") != "officer" )
		return "你没有为朝廷效力，我怎么会给你任务呢？";
	if ( ob->query_temp("chaoting/current_job"))
		return "我不是告诉你了吗？去" + ob->query_temp("chaoting/current_job") + "守门吧。";

	pin = ob->query("pin");
	if (pin == 9)
		return RANK_D->query_respect(ob) + "武功太差，作这种工作未免有些危险。";
	if (pin < 5)
		return RANK_D->query_respect(ob) + "位高权重，已经不用干这种活了。";
	if (ob->query("score") >= 1000)
		return RANK_D->query_respect(ob) + "已经可以升迁了，不必干这种活了。";
	if (ob->query("score") >= 400 && pin > 7)
		return RANK_D->query_respect(ob) + "需要升迁之后再继续作守门任务。";
	if (ob->query("score") >= 600 && pin > 6)
		return RANK_D->query_respect(ob) + "需要升迁之后再继续作守门任务。";
	if (ob->query("score") >= 800 && pin > 5)
		return RANK_D->query_respect(ob) + "需要升迁之后再继续作守门任务。";
	if (HELPER->is_sunrise() != 0 && HELPER->is_sunset() != 0)
		return "守门只有早晚两班，你到时间再来吧。";

	i = random(sizeof(outer_gate_name));
	j = random(sizeof(inner_gate_name));
	if (pin <= 6)
		gate = random(2)?outer_gate_name[i]:inner_gate_name[j];
	else
		gate = outer_gate_name[i];

	if (HELPER->is_sunrise() == 0)
		ob->set_temp("chaoting/day_job", 1);
	else if (HELPER->is_sunset() == 0)
		ob->set_temp("chaoting/night_job", 1);

	ob->set_temp("chaoting/current_job", gate);

	tell_object(ob,"你的任务是去"+gate+"守门。\n");
	return "你快去" + gate + "守门 (guarding) 吧。";

}

string ask_job()
{
	object me;
	object ob;
	int i;
	string *place = ({ "外城", "内外城城墙", "天坛",});
	ob = this_player();
	me = this_object();
	if (ob->query("class") != "officer")
		return RANK_D->query_respect(ob) + "不是朝廷官员，此话从何说起？";
	if (ob->query_temp("chaoting/xuncheng"))
		return ("你不是已经领了巡城的任务吗？还不快去做。");
	if (ob->query("combat_exp") < 3000)
		return ("你武功太低，无法胜任。");
	if (ob->query("pin") < 8)
		return ("我看你的武功已有相当的功底了，就不用干这种事了。");
	if (ob->query("score") >= 400)
		return RANK_D->query_respect(ob) + "已经可以升迁了，不必干这种活了。";

	i = random(3);
	ob->set_temp("chaoting/xuncheng", i + 1);
	ob->apply_condition("beijing_xuncheng", random(5) + 5);
	return "好吧，你去" + place[i] + "巡逻一下吧，巡逻时应当小心防范，防止外敌。";
}

string do_task()
{
	object ob,me;
	int pot,exp,sil;
	ob = this_player();
	me = this_object();

	if(!ob->query_temp("chaoting/xuncheng"))
		return ("你没巡逻跑来领什么功？");
	if (interactive(ob)
		&& (int)ob->query_condition("beijing_xuncheng"))
	{
		command("slap " + ob->query("id"));
		return (RED"你这么快回来了，是不是有些地方只是马马虎虎看看？"NOR);
	}
	switch (ob->query_temp("chaoting/xuncheng"))
	{
	case 1://外城(经过13个城门即可)
		if(!(ob->query_temp("xc/yonganmen")
		&& ob->query_temp("xc/zuoanmen")
		&& ob->query_temp("xc/youanmen")
		&& ob->query_temp("xc/guangqumen")
		&& ob->query_temp("xc/dongbianmen")
		&& ob->query_temp("xc/chaoyangmen")
		&& ob->query_temp("xc/dongzhimen")
		&& ob->query_temp("xc/andingmen")
		&& ob->query_temp("xc/deshengmen")
		&& ob->query_temp("xc/xizhimen")
		&& ob->query_temp("xc/fuchengmen")
		&& ob->query_temp("xc/xibianmen")
		&& ob->query_temp("xc/guanganmen")
		))
			return("你是不是偷懒，漏了些地方没巡？ \n");
		break;
	case 2://内外城城墙(经过16个城楼即可)
		if(!(ob->query_temp("xc/yonganmenlou")
		&& ob->query_temp("xc/zuoanmenlou")
		&& ob->query_temp("xc/youanmenlou")
		&& ob->query_temp("xc/guangqumenlou")
		&& ob->query_temp("xc/dongbianmenlou")
		&& ob->query_temp("xc/chaoyangmenlou")
		&& ob->query_temp("xc/dongzhimenlou")
		&& ob->query_temp("xc/andingmenlou")
		&& ob->query_temp("xc/deshengmenlou")
		&& ob->query_temp("xc/xizhimenlou")
		&& ob->query_temp("xc/fuchengmenlou")
		&& ob->query_temp("xc/xibianmenlou")
		&& ob->query_temp("xc/guanganmenlou")
		&& ob->query_temp("xc/zhengyangmenlou")
		&& ob->query_temp("xc/chongwenmenlou")
		&& ob->query_temp("xc/xuanwumenlou")
		))
			return ("你是不是偷懒，漏了些地方没巡？ \n");
		break;
	case 3://天坛(需要走遍四个天门内所有17个地方)
		if(!(ob->query_temp("xc/baihuayuan")
		&& ob->query_temp("xc/beitianmen")
		&& ob->query_temp("xc/danbiqiao")
		&& ob->query_temp("xc/dongtianmen")
		&& ob->query_temp("xc/huangqiongyu")
		&& ob->query_temp("xc/huanqiu")
		&& ob->query_temp("xc/nantianmen")
		&& ob->query_temp("xc/penshuichi")
		&& ob->query_temp("xc/qiniandian")
		&& ob->query_temp("xc/shibanlu1")
		&& ob->query_temp("xc/shibanlu2")
		&& ob->query_temp("xc/shibanlu3")
		&& ob->query_temp("xc/shibanlu4")
		&& ob->query_temp("xc/shibanlu5")
		&& ob->query_temp("xc/xitianmen")
		&& ob->query_temp("xc/zaichufang1")
		&& ob->query_temp("xc/zaichufang2")
		))
			return ("你是不是偷懒，漏了些地方没巡？ \n");
		break;
	}
	command("pat " + ob->query("id"));

	sil = (int)(ob->query_skill("force",1)/2) + random(5);
	pot = 5 + random(20);
	exp = 30 + random(70);
	me->add_money("silver",sil);
	command("give "+ob->query("id")+" "+sil+" silver");
	ob->add("potential", pot);
	ob->add("pot/chaoting", pot);
	ob->add("combat_exp",exp);
	ob->add("exp/chaoting",exp);
	ob->add("score", 1);
	ob->add("chaoting/xuncheng", 1);
	tell_object(ob,HIW"你被奖励了：\n" +
		chinese_number(exp) + "点实战经验\n" +
		chinese_number(pot) + "点潜能\n"+
		chinese_number(sil)+"两白银\n"+
		"你对朝廷的贡献度增加了。\n" +
		"你已为朝廷做了"+ chinese_number(ob->query("chaoting/xuncheng")) + "次巡逻任务。\n"NOR);
	ob->delete_temp("chaoting/xuncheng");
	ob->delete_temp("xc");
	return "哈哈，真难为你了，" + RANK_D->query_respect(ob) + "做得好！";
}

string ask_leadership()
{
	object ob;
	if (this_player()->query("class") != "officer")
		return RANK_D->query_respect(this_player()) +
		"与朝廷素无来往，不知此话从何谈起？";
	if (query("book_count") < 1)
	{		
		if(!random(10)) 
			set("book_count",10);
		return "为官之道首先要研究刑法律例，不过「大清律例」已经被人拿走了。";
	}
	add("book_count", -1);

	ob = new(__DIR__"obj/book_lvli");

	ob->move(this_player());

	return "为官之道首先要研究刑法律例，这本「大清律例」你拿回去好好钻研。";
}
string ask_strategy()
{
	object ob;
	if (this_player()->query("class") != "officer")
		return RANK_D->query_respect(this_player()) +
		"与朝廷素无来往，不知此话从何谈起？";
	if (this_player()->query_skill("strategy", 1) >= 120)
		return "不敢当不敢当，大人早已不逊于我了。";
	if (query("book_count") < 1)
	{
		if(!random(10)) 
			set("book_count",10);
		return "行军打仗要钻研古代兵书，不过我的书已经被人拿走了。";
	}

	if(this_player()->query_skill("strategy", 1) < 30)
	{
		ob = new(__DIR__"obj/book_wendui");
		ob->move(this_player());
		add("book_count", -1);
		return "好吧，这本「李卫公问对」你拿回去好好钻研。";
	}
	else if(this_player()->query_skill("strategy", 1) < 60)
	{
		ob = new(__DIR__"obj/book_liutao");
		ob->move(this_player());
		add("book_count", -1);
		return "好吧，这本「六韬」你拿回去好好钻研。";
	}
	else if(this_player()->query_skill("strategy", 1) < 90)
	{
		if (this_player()->query("pin") > 7)
			return "你官阶尚低，升迁以后再来问我吧。";
		ob = new(__DIR__"obj/book_sanlue");
		ob->move(this_player());
		add("book_count", -1);
		return "好吧，这本「三略」你拿回去好好钻研。";
	}
	else if(this_player()->query_skill("strategy", 1) < 120)
	{
		if (this_player()->query("pin") > 6)
			return "你官阶尚低，升迁以后再来问我吧。";
		ob = new(__DIR__"obj/book_sunbin");
		ob->move(this_player());
		add("book_count", -1);
		return "好吧，这本「孙膑兵法」你拿回去好好钻研。";
	}
}

string ask_feizei()
{
	object me, ob, feizei,where;
	mapping target, position;
	int exp;
	string name;

	me = this_player();
	exp = me->query("combat_exp");

	if (me->query("class") != "officer")
		return RANK_D->query_respect(this_player()) + "与朝廷素无来往，不知此话从何谈起？";

	if(stringp(me->query("chaoting/badman")))
		return "你先把抓坏人的任务完成了再说吧。";

	if ( me->query("jianzhan/in_dart"))
		return "你先把监斩任务完成了再说吧。";

	if( me->query("chaoting/catchfeizei"))
	{
		command("slap " + me->query("id"));
		return "先把上一个任务完成了再说，实在做不了就给钱取消吧。";
	}

	if(time() - me->query("last_feizei_time") < 180)
	return "目前治安良好，没有发现飞贼。";

        feizei = new("/d/beijing/npc/feizei1");
	//只有要的人杀这个飞贼才有用
	feizei->set("catcher",me->query("id"));
        feizei->set("can_arrest",random(2));

	if (!feizei)
		return "BUG: 请通知巫师。";

	if (exp < 100000)
	{
		feizei->Set_Npcattrib(20, 10,
					500, 1000,
					1000, 1000,
					1000, 1000,
					1000, 1000,
					50000, 50000 );
		if (random(2) == 0)
		feizei->skills_setup_none(10, 90, "random_menpai");
		else
		feizei->skills_setup_weapon(10, 90, "random_menpai");
	}
	else if (exp < 500000)
	{
		feizei->Set_Npcattrib(20, 10,
					1000, 1000,
					1000, 1000,
					1000, 1000,
					1000, 1000,
					100000, 200000 );
		if (random(2) == 0)
		feizei->skills_setup_none(50, 100, "random_menpai");
		else
		feizei->skills_setup_weapon(50, 100, "random_menpai");
	}
	else if (exp < 1000000)
	{
		feizei->Set_Npcattrib(20, 10,
					1000, 2000,
					1000, 1000,
					1000, 1000,
					1000, 1000,
					200000, 500000 );
		if (random(2) == 0)
		feizei->skills_setup_none(80, 120, "random_menpai");
		else
		feizei->skills_setup_weapon(80, 120, "random_menpai");
	}
	else
	{
		feizei->Set_Npcattrib(20, 10,
					1500, 2500,
					1000, 1000,
					1000, 1000,
					1000, 1000,
					300000, 2000000 );
		if (random(2) == 0)
		feizei->skills_setup_none(100, 150, "random_menpai");
		else
		feizei->skills_setup_weapon(100, 150, "random_menpai");
	}
	//position = feizei->query_quest(); //用taskd统一分配任务，用各自的任务列表修改起来太麻烦了。
	while (!objectp(where) || 
               !where->isroom()||
               TASK_D->place_belong(where)=="不明区域"||
               base_name(where) == "/adm/daemons/taskd")
	{
		where = TASK_D->random_place();
	}
	if (feizei->move(where))
	{
		if (!living(feizei))
		{
			return "你迟些再来吧。\n";
			me->add_busy(5);
		}
		me->delete_temp("feizei");
		me->set("chaoting/catchfeizei", 1);
		me->set_temp("feizei/gkill1", 1);
		this_object()->set("last_feizei_time",time());
		return "飞贼" + feizei->short() + "在「" +TASK_D->place_belong(where)+"的"+where->query("short") + "」出现，请速去将他捉拿归案！";
	}
	else return "BUG: 请通知巫师。";
}

string ask_jianzhan()
{
	int i;
	object ob, cart, bing;
	ob=this_player();

	if (ob->query("class") != "officer")
		return RANK_D->query_respect(this_player()) + "与朝廷素无来往，不知此话从何谈起？";

	if(stringp(ob->query("chaoting/badman")))
		return "你先把抓坏人的任务完成了再说吧。";

	if( ob->query("chaoting/catchfeizei"))
	{
		command("slap " + ob->query("id"));
		return "先把抓飞贼任务完成了再说吧。";
	}

	if ( ob->query("jianzhan/in_dart"))
		return "你上一个任务还没结算呢？";

	if ( ob->query("pin") < 3)
		return "大人已经不用再作这种任务了。";

	if ( ob->query("score") >= 1400)
		return "你已经可以升迁了，没有必要再作这个任务。";

	if (ob->query("score") >= 800 && ob->query("pin") > 5)
		return RANK_D->query_respect(ob) + "需要升迁之后再继续作监斩任务。";

	if ( ob->is_busy() || ob->query_temp("pending/exercising"))
		return "你现在正忙着呢。";

	if ( (int)ob->query("combat_exp") < 100000 )
		return "护送囚车是件危险工作，我看"+RANK_D->query_respect(ob)+"似乎没有这能力！";


	if(time() - ob->query("last_jianzhan_time") < 120)
		return "你上次监斩太辛苦了，下去休息休息吧。";

	ob->set("jianzhan/in_dart",1);

	if (ob->query("pin") > 7)
		ob->set("jianzhan/dart_value", 4);
	else if (ob->query("pin") > 5)
		ob->set("jianzhan/dart_value", 6);
	else
		ob->set("jianzhan/dart_value", 8);

	cart=new(__DIR__"obj/cart");
	cart->set("master", ob->query("name"));
	cart->set("masterid", ob->query("id"));
	cart->set("owner", ob);
	cart->move("/d/beijing/shiwei_office");
	command("nod");
	message_vision(CYN "几个官兵推出一辆囚车。" NOR,ob);
	ob->set("jianzhan/can_go",1);
	ob->set("last_jianzhan_time",time());
	for (i = 1; i < 5; i++)
	{
                bing = new(__DIR__"jz_bing");
		bing->set_shiwei_status(30 + random(60));
		bing->move("/d/beijing/shiwei_office");
		bing->set_leader(ob);
	}
	return ob->query("name")+"把这辆囚车护送到" + HIC"菜市口"NOR + "吧。";

}

string do_give()
{
	int bonus;
	object ob;
//	int max_pot;

	ob=this_player();
//	max_pot=(int)this_player()->query("max_pot");

	if (ob->query("class") != "officer")
		return RANK_D->query_respect(this_player()) + "与朝廷素无来往，不知此话从何谈起？";

	if ( !ob->query("jianzhan/in_dart"))
		return "我没让你监斩啊？";

	if ( !ob->query("jianzhan/over_dart") )
		return "囚车没有送到目的地，莫非你假公济私？！";

	if (ob->query("combat_exp") < 1000000)
	{
		int creward,preward,rreward;

		creward = (random(70) + 30) * ob->query("jianzhan/dart_value");
		preward = creward / 2;

		ob->add("combat_exp",creward);
		ob->add("exp/chaoting",creward);
		ob->add("potential",preward);
		ob->add("pot/chaoting",preward);
		ob->add("score", 1);
		ob->add("chaoting/jianzhan", 1);
		ob->delete("jianzhan");
		tell_object(ob,"你对朝廷的贡献度增加了。\n");
		message("vision",HIW"你被奖励了"+chinese_number(creward)+"点经验，"+
			chinese_number(preward)+"点潜能！\n"NOR,ob);
	}
	else
	{
		int creward,preward,rreward;

		creward = ( random(80) + 40) * ob->query("jianzhan/dart_value");
		preward = creward / 2;
		ob->add("combat_exp",creward);
		ob->add("exp/chaoting",creward);
		ob->add("potential",preward);
		ob->add("pot/chaoting",preward);

		ob->add("score", 1);
		ob->add("chaoting/jianzhan", 1);
		ob->delete("jianzhan");
		tell_object(ob,"你对朝廷的贡献度增加了。\n");
		message("vision",HIW"你被奖励了"+chinese_number(creward)+"点经验，"+
			chinese_number(preward)+"点潜能！\n"NOR,ob);
	}
	ob->delete("jianzhan_failnum");
	command("pat "+ob->query("id"));
	return RANK_D->query_respect(ob)+"果然是栋梁之才！";
}


string do_fail()
{
	int creward,preward,rreward,times;
	object ppl=this_player();
	if (ppl->query("class") != "officer")
		return RANK_D->query_respect(this_player()) + "与朝廷素无来往，不知此话从何谈起？";

	if(!ppl->query("jianzhan/in_dart"))
		return "你没有领过什么任务吧？";
	else
	{
		command("heng "+ppl->query("id",1));
		ppl->add("jianzhan_failnum",1);
		if (ppl->query("combat_exp") < 1000000)
		{
			creward = (random(40) + 20) * ppl->query("jianzhan/dart_value");
			creward = creward * ppl->query("jianzhan_failnum")* ppl->query("jianzhan_failnum");
			preward = creward / 2;
			ppl->add("combat_exp", - creward);
			ppl->add("exp/chaoting", - creward);
			ppl->add("pot/chaoting", - preward);
			ppl->add("chaoting/job_fail", 1);

			message("vision",HIW"你被扣除了"+chinese_number(creward)+"点经验，"+
				chinese_number(preward)+"点潜能！\n"NOR,ppl);
		}
		else
		{
			creward = ( random(50) + 20) * ppl->query("jianzhan/dart_value");
			creward = creward * ppl->query("jianzhan_failnum")* ppl->query("jianzhan_failnum");
			preward = creward / 2;
			ppl->add("combat_exp", - creward);
			ppl->add("exp/chaoting", - creward);
			ppl->add("pot/chaoting", - preward);
			ppl->add("chaoting/job_fail", 1);

			message("vision",HIW"你被扣除了"+chinese_number(creward)+"点经验，"+
				chinese_number(preward)+"点潜能！\n"NOR,ppl);
		}
		ppl->delete("jianzhan");
	}
	if(ppl->query("combat_exp")<2000)
		ppl->set("combat_exp", 2000);
	return "这点小事你都办不好，还能指望你作些什么呢？";
}
*/