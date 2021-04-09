// gift.c    

#include "ansi.h"


inherit NPC;


#define TEST_MODE   0

#define TEST_TIME 600	        		//测试开始到结束的时间
#define WAIT_TIME 600					//等待玩家回应时间
#define NEXT_TURN_TIME  (random(86400) + 3600)  //下一轮等待时间

#define MAX_QUESTION	30				//补充随机问题到MAX_QUESTION
#define SKIP_COUNT		2				//最多可以跳过的次数

#define LOWEST_JOBSCORE        300             //jobscore门槛

#define JOBSCORE        "/cmds/usr/jobscore.c"


#define SELECTED    1
#define STARTED     2
#define TIMEOUTED   3

#define COEFF   100      //测试期间，只奖励10%

nosave int question_count = 0;

#include "gift.h"


int ask_question();
void greeting(object me);

void create()
{
	set_name("老学究", ({ "teacher"}));
	set("gender", "男性");
	set("age", 66);
	set("long", "他是一位老学究，对大部分常用成语了如指掌，要不要向他讨教一下呢？\n");


	set("no_ask", 1);		//不允许 ask all
	set("inquiry",([
		"question"	: (: ask_question :),
        "问题"	    : (: ask_question :),
        "礼券"		: (: ask_gift :),
	]));
	setup();
	carry_object("/clone/misc/cloth")->wear();	
    call_out("select_next_player", NEXT_TURN_TIME);
}

void init()
{
	object me = this_player();

	add_action("do_answer","answer");
	add_action("do_skip", "skip");
    add_action("do_test", "test");
    call_out("greeting", 0, me);
}

void greeting(object me)
{
    if (!me) return;
    if (me->query_temp("jobs/selected") == SELECTED)
	{
		command("nod " + me->query("id"));
		command("say 你终于来啦。现在就开始测试吧。\n你一共有十分钟的答题时间，题目很简单，就是把打乱顺序的成语复原，答对可以继续答题，答错则停止答题\n"
            "对于没有把握的题，你可以选择跳过(skip)，你一共有两次跳过的机会。\n好，倒计时开始！");
        me->set_temp("jobs/selected", STARTED);
        me->set_temp("jobs/end_time", time() + TEST_TIME);
        remove_call_out("wait_player");
        remove_call_out("wait_end");
        call_out("wait_end", TEST_TIME, me);
	}
    else if (me->query_temp("jobs/selected") == STARTED)
	{
		command("sonhere " + me->query("id"));
		command("say 跑什么跑，不做测试了吗？");
	}
    else if (me->query_temp("jobs/selected") == TIMEOUTED)
    {
        command("sigh " + me->query("id"));
		command("say 你怎么现在才来啊。");
        me->delete_temp("jobs/selected");
    }
    if (wizardp(me))
        tell_object(me, "输入test <bonus>可以启动面向所有在线玩家的测试，该测试可以用作奖励或节假日礼物，bonus/100为奖励系数。\n");

}
//给用户奖励，并清除临时参数
void give_rewards_and_remove_temp(object me)
{
    int point, count, bonus;
    count = me->query_temp("jobs/count");
    bonus = me->query_temp("jobs/bonus");
    point = 10 * count + count * count + bonus * bonus;
//    point = point * 2 / 3;
//    point += random(point);
    point += me->query_temp("jobs/jobscore_bonus");
    point = point * COEFF / 100;
    if (query_temp("bonus"))
        point = point * query_temp("bonus") / 100;

#ifndef TEST_MODE
    me->add("jobs/reward/count", count);
    me->add("jobs/reward/bonus", bonus);
    me->add("jobs/reward/point", point);
#else
    me->add_temp("jobsreward/count", count);
    me->add_temp("jobsreward/bonus", bonus);
    me->add_temp("jobsreward/point", point);
#endif

    command("say 111 " + me->query("name") + "(" + me->query("id") + ")连续答对了" + count + 
#ifndef TEST_MODE
        "道题，奖励点券"
#else
        "道题，奖励临时点券"
#endif
        + point + "点。");

    me->delete_temp("jobs");
    delete_temp("jobs/target");
}

//选择jobscore最高的用户

object select_user()
{
	object target = 0, *all_user = users();
	int max = 0, temp, i;
//	return find_player("xiaoqian");
	for (i = 0; i < sizeof(all_user); i++)
	{
		if (all_user[i] && userp(all_user[i]) && !wizardp(all_user[i]))
		{
#ifndef TEST_MODE
            temp = JOBSCORE->cal_score(all_user[i]);
            temp -= all_user[i]->query("jobs/used");
			temp -= random(temp) /2;			//给予一定的随机范围，避免总是选择最高的玩家
#else
            temp = random(10000);
#endif

			if (temp > max && temp > LOWEST_JOBSCORE)
			{
				max = temp;
				target = all_user[i];
			}
		}
	}
    if (target)
    {
#ifndef TEST_MODE
        target->add("jobs/used", max * 2 / 3);      //保留1/3的差值，鼓励玩家继续挣jobscore
        target->add_temp("jobs/jobscore_bonus", max * 2 / 3);  //消耗掉的jobscore当作奖励回馈给用户
#endif
    }
	return target;
}

//进入下一轮选择，每次启动时间为 NEXT_TURN_TIME  (random(86400) + 3600)
int select_next_player()
{
    object target = select_user();
    if (target)
    {
        target->set_temp("jobs/selected", SELECTED);
        command("say * admire " + target->query("id"));
        command("say 纵观全部玩家，阁下十分勤劳，可否前来做个答题测试？");
        set_temp("jobs/target", target);
        remove_call_out("wait_player");
        call_out("wait_player", WAIT_TIME, target);
        reset_questions();
    }
    remove_call_out("select_next_player");
    call_out("select_next_player", NEXT_TURN_TIME);
    return 1;
}

//等待被选择用户超时
void wait_player(object target)
{
    if (target)
    {
        command("say sigh* " + target->query("id"));
        target->delete_temp("jobs");
        target->set_temp("jobs/selected", TIMEOUTED);
    }
}

//等待用户测试结束
int wait_end(object me)
{
    if (!me || me->query_temp("jobs/selected") != STARTED)
        return 0;
    message_vision("$N答题时间到！\n", me); 
    give_rewards_and_remove_temp(me);
    return 1;
}

int ask_question()
{
    object me = this_player();
	int index, remain_time, answer_remain_time;
	if (me->query_temp("jobs/selected") != STARTED)
		return 0;

    if (me->query_temp("jobs/ask_time"))
    {
        index = me->query_temp("jobs/index");
    }
    else
    {
        index = me->add_temp("jobs/index", 1);
        me->set_temp("jobs/ask_time", time());
    }


    if (index <= question_count)
	{
        tell_object(me, "好，我们来做个简单的测试。请按格式回答下面的问题(answer)：\n");
        show_question(index, 0);
        tell_object(me, "你的答题时间还剩下" + (me->query_temp("jobs/end_time") - time()) + "秒。\n");
    }
    else
    {
        command("say " + me->query("id") + "在" + TEST_TIME + "秒内连续回答正确" + question_count + "道题");
        command("admire " + me->query("id"));
        command("say 我已经没有题了...");
        give_rewards_and_remove_temp(me);
    }
	
	return 1;
}

int do_answer(string arg)
{
	object me = this_player();
	int t, point, index;
	if (!arg || me->query_temp("jobs/selected") != STARTED || !me->query_temp("jobs/ask_time"))
		return notify_fail("什么?\n");

	t = time() - me->query_temp("jobs/ask_time");
    me->delete_temp("jobs/ask_time");


	message_vision((t < 10 ? "$N不加思索，脱口而出" : "$N考虑良久，犹豫答道") + "：“是"HIW + arg + NOR"吗？”\n", me);

    index = me->query_temp("jobs/index");
	if (arg == query_temp("jobs/" + index + "/answer"))
	{
		command(t < 10 ? "clever " : "nod " + me->query("id"));
		me->add_temp("jobs/count", 1);
        if (t < 10)
            me->add_temp("jobs/bonus", 1);
		command("say 111* congr " + me->query("id"));
		command("say 恭喜你答对了！还有" + (me->query_temp("jobs/end_time") - time()) + "秒，你想继续测试吗？(ask question)\n"
			"注意：领题不答或超时仍然保留成绩，"  + HIR"但答错将立即结束测试，请仔细考虑。"NOR );
	}
	else
	{		
		command((random(2) ? "faint " : "hidfy ") + me->query("id"));
		command("say 111* disapp " + me->query("id"));
		command("say " + RANK_D->query_respect(me) + "连这么简单的题都答错？回去好好努力，下次再来！");
		command("smug " + me->query("id"));
        give_rewards_and_remove_temp(me);
	}
	return 1;
}

int do_skip()
{
	object me = this_player();
	if (me->query_temp("jobs/selected") != STARTED)
		return notify_fail("什么?\n");
	if (!me->query_temp("jobs/ask_time"))
		return notify_fail("你都没有领题，跳什么跳？\n");
	if (me->query_temp("jobs/skip") >= SKIP_COUNT)
		return notify_fail("你已经跳过了"HIW + SKIP_COUNT + NOR"次，不能再跳过了！\n");
	me->add_temp("jobs/skip", 1);
	me->delete_temp("jobs/ask_time");
	command("smirk " + me->query("id"));
	command("say 你选择了跳过，请重新领题。");
	command("addoil " + me->query("id"));
	return 1;
}




int do_test(string arg)
{
    int bonus = 100, i;
    object me = this_player();
    object *all_user;

    if (!wizardp(me))
        return notify_fail("什么?\n");

    if (query_temp("jobs/target"))
        return notify_fail("目前已有玩家在测试，不可以开启答题系统！\n");

    if (!arg || sscanf(arg, "%d", bonus) == 1)
    {
        if (bonus > 300 || bonus <= 0)
            return notify_fail("奖励因该为[1%-300%]！\n");

        if (!query_temp("bonus") || query_temp("bonus") != bonus)
        {
            set_temp("bonus", bonus);
            tell_object(me, "你要以bonus：" + bonus + "启动答题吗？确认请再次输入" + query_verb() + " " + bonus + "\n");
        }
        else
        {
            command("say 答题系统启动，请在线玩家速来测试。");
	        all_user = users();
	        for (i = 0; i < sizeof(all_user); i++)
	            all_user[i]->set_temp("jobs/selected", SELECTED);
            reset_questions();
            remove_call_out("select_next_player");
            call_out("select_next_player", NEXT_TURN_TIME);
            remove_call_out("wait_test_end");
            call_out("wait_test_end", 30 * 60);     //三十分钟内有效
            
        }
        return 1;
    }

    return notify_fail("请输入test <bonus>来启动答题系统。\n");
}

int wait_test_end()
{
    object *all_user = users();
    int i;
    for (i = 0; i < sizeof(all_user); i++)
	    if (all_user[i]->query_temp("jobs/count"))
            give_rewards_and_remove_temp(all_user[i]);
        else
            all_user[i]->delete_temp("jobs");
}

