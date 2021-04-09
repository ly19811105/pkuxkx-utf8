// gift.c    

#include "ansi.h"

inherit NPC;

#define TEST_MODE 

#ifdef TEST_MODE
#define TEST 2
#else
#define TEST 1
#endif

#define TEST_TIME (20 * TEST)			//测试开始到结束的时间
#define WAIT_TIME 60					//等待玩家回应时间

#define MAX_QUESTION	30				//补充随机问题到MAX_QUESTION
#define SELECT_COUNT	3				//每次选择3个人
#define SKIP_COUNT		2				//最多可以跳过的次数

nosave int question_count;
nosave int selected_count;




void start_test();
void show_question(int index, int show_answer);
void add_random_question();
void set_user_selected(object user);
int ask_question();
object select_user();

void create()
{
	set_name("礼券天使", ({ "gift angel", "angel" }));
	set("gender", "男性");
	set("age", 99);
	set("long", "向非机器人发放礼券的天使。其实他就是赫赫有名的青狼主法官，不过现在已经不以抓机器人为乐了。\n");

	set("combat_exp", 800000000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	set("title", HIC"青狼主法官"NOR);


	set_skill("parry", 8000);
	set_skill("dodge", 8000);
	set("max_qi", 20000);
	set("qi", 20000);
	set_temp("apply/attack", 10000);
	set_temp("apply/defense", 10000);

	set("no_ask", 1);		//不允许 ask all
	set("inquiry",([
		"question"	: (: ask_question :),
		"robot"		: "你是机器人吗？小心别被我逮着",
		"机器人"	: "你是机器人吗？小心别被我逮着",
		"礼券"		: "测试期间，查看礼券找小贩(list)",
		"rule"		: "答题时间为2分钟，回答正确可以继续答题，回答错误或要题目后超时没有回答则直接被淘汰，请谨慎选择！"
	]));
	setup();
	carry_object("/clone/misc/cloth")->wear();
	
}

void init()
{
	object me = this_player();

	add_action("do_answer","answer");
	add_action("do_skip", "skip");

	if (query_temp("gift/target") == me)
	{
		command("nod " + me->query("id"));
		command("say 你终于来啦。现在就开始测试吗？");
	}
}

void start()
{
	selected_count = 0;
	question_count = 0;
	start_test();
}

void start_test()
{
	object target = select_user();
	if (target)
	{
		set_user_selected(target);

		set_temp("gift/target", target);

		add_random_question();
		command("hi* " + target->query("id"));
		command("tell " + target->query("id") + "测试开始，请速来。");
		//@@	command("say 111 在下有几道测试题想向" + RANK_D->query_respect(target) + "请教，");
		set_temp("start_time", time());
		remove_call_out("end_wait");
		call_out("end_wait", WAIT_TIME, target);
	}
}

void wait_next()
{
	if (++selected_count < SELECT_COUNT)
	{
		call_out("start_test", 5, 0);
	}	
}

void end_wait(object target)
{
	if (target)
	{
		command("sigh* " + target->query("id"));
		command("say 111 看来我是看走眼了。");
		target->delete_temp("gift");
	}
	delete_temp("gift");
	wait_next();
}
void end_test()
{
	object me = query_temp("gift/target");
	if (me && environment(me) == environment())
	{
		command("say 时间到！");
		command("say 111 " + me->query("name") + "连续答对了" + me->query_temp("gift/count") + "道题。奖励xxxx\n");
		//@@ 功夫， 点券...  give_reward(me);
	}
	if (me)
		me->delete_temp("gift");
	wait_next();
}



// void move_to_random_place()
// {
// 	string *dir, main_dir = "/d/city/";
// 	object room;
// 	int i, tmp, test = 0;
// 
// #ifdef TEST_MODE	
// 	return;
// #endif
// 
// 	dir = get_dir(main_dir);
// 	while (i = random(sizeof(dir)))
// 	{
// 		if(file_size(main_dir + dir[i]) <= 0)
// 			continue;
// 		tmp = sizeof(dir[i])-1;
// 		if (dir[i][tmp-1..tmp] != ".c") 
// 			continue;
// 		room = load_object(main_dir + dir[i]);
// 		if (room || ++test > 30)
// 			break;		
// 	}
// 	write("find room " + dir[i] + "in " + test + " cycle.\n");
// 	move(room);
// }


int ask_question()
{
	object me = this_player();
	int index, remain_time, answer_remain_time;
	if (query_temp("gift/target") != me || !me->query_temp("gift/selected"))
		return 0;


	if (!me->query_temp("gift/end_time"))
	{
		me->set_temp("gift/end_time", time() + TEST_TIME);
		remove_call_out("end_wait");
		remove_call_out("end_test");
		call_out("end_test", TEST_TIME, 0);
	}

	index = me->query_temp("gift/index");

	if (!index)
	{
		index = random(question_count) + 1;
		me->set_temp("gift/index", index);
		me->set_temp("gift/answer", query_temp("gift/" + index + "/answer"));
		me->set_temp("gift/question_time", time());
	}	
	
	tell_object(me, "好，我们来做个简单的测试。请按格式回答下面的问题(answer)：\n");
	show_question(index, 0);
	tell_object(me, "你的答题时间还剩下" + (me->query_temp("gift/end_time") - time()) + "秒。\n");
	return 1;
}

int do_answer(string arg)
{
	object me = this_player();
	int t, point;
	if (!arg || query_temp("gift/target") != me || !me->query_temp("gift/selected") || !me->query_temp("gift/index"))
		return notify_fail("什么?\n");


	t = time() - me->query_temp("gift/question_time");


	message_vision((t < 10 ? "$N不加思索，脱口而出" : "$N考虑良久，犹豫答道") + "：“是"HIW + arg + NOR"吗？”\n", me);

	if (arg == me->query_temp("gift/answer"))
	{
		command(t < 10 ? "clever " : "nod " + me->query("id"));
		me->add_temp("gift/count", 1);
		me->delete_temp("gift/index");
		command("say 111* congr " + me->query("id"));
		command("say 恭喜你答对了！还有" + (me->query_temp("gift/end_time") - time()) + "秒，你想继续测试吗？(ask question)\n"
			"注意：领题不答或超时仍然保留成绩，"  + HIR"但答错将没有成绩，请仔细考虑。"NOR );
	}
	else
	{		
		me->delete_temp("gift");
		command((random(2) ? "faint " : "hidfy ") + me->query("id"));
		command("say 111* disapp " + me->query("id"));
		command("say " + RANK_D->query_respect(me) + "连这么简单的题都答错？回去好好努力，下次再来！");
		command("byebye " + me->query("id"));
//@@	将玩家踢出房间		
	}

	return 1;
}

int do_skip()
{
	object me = this_player();
	if (!me->query_temp("gift/index"))
		return notify_fail("你都没有领题，跳什么跳？\n");
	if (me->query_temp("gift/skip") >= SKIP_COUNT)
		return notify_fail("你已经跳过了"HIW + SKIP_COUNT + NOR"次，不能再跳过了！\n");
	me->add_temp("gift/skip", 1);
	me->delete_temp("gift/index");
	command("smirk " + me->query("id"));
	command("say 你选择了跳过，请重新领题。");
	command("addoil " + me->query("id"));
	return 1;
}

string random_string(string s)	//随机打乱一个中文字符串
{
	int len = sizeof(s) / 2;                //前提是都是中文字符，否则乱码...
	int i, j;
	mixed k1, k2;
	for(i = 0; i < len; i++)
	{
		j = random(len - i) + i;
		k1 = s[2*i];
		k2 = s[2*i+1];
		s[2*i] = s[2*j];
		s[2*i + 1] = s[2*j + 1];
		s[2*j] = k1;
		s[2*j + 1] = k2;
	}       
	return s;
}
void add_question(string question, string answer, string sample)
{
	question_count ++;
	set_temp("gift/" + question_count + "/question", question);
	set_temp("gift/" + question_count + "/answer", answer);
	set_temp("gift/" + question_count + "/sample", sample);
}




void add_idiom_question_from_dict(int count)
{	
	int total_question_count = 17762, i;
	int question_count = count;
	int start_line = random(total_question_count - question_count);
	string question = read_file("/u/boost/idiom.dict", start_line, question_count);
	string * questions = explode(question, "\n");
	for (i = 0; i < sizeof(questions); i++)
		add_question("请将打乱顺序的成语恢复："HIB + random_string(questions[i]) + NOR"", questions[i], random_string(questions[i]));
}


void add_random_math_question()		//四则运算
{
	int max = 1000, i;
	string str;
#define NUM_COUNT 4
	int *n = allocate(NUM_COUNT);
	for (i = 0; i < NUM_COUNT; i++)
		n[i] = random(max) + 1;
	str = "" + n[0];
	for (i = 0; i < NUM_COUNT - 1; i++ )
	{
		switch(random(3))
		{
		case 0:					// '+'
			str = random(2) ? "(" + str + "+" + n[i+1] + ")" : "(" + n[i+1] + "+" + str + ")";
			n[i+1] += n[i];
			break;
		case 1:					// '-'
			str = "(" + str + "-" + n[i+1] + ")";
			n[i+1] = n[i] - n[i+1];
			break;
		case 2:					// '*'
			str = random(2) ? "(" + str + "*" + n[i+1] + ")" : "(" + n[i+1] + "*" + str + ")";
			n[i+1] *= n[i];
			break;
		}
	}
	str += "=?";

	add_question("请计算下面算式的结果："HIW + str + NOR"", "" + n[i] , "" + random(max));
}



void add_random_question()
{
	int i;
	if (question_count < MAX_QUESTION)
	{
		add_idiom_question_from_dict(MAX_QUESTION - question_count);
		// 		for (i = question_count; i < MAX_QUESTION; i++)		//太容易做机器人了，以后再说
		// 			add_random_math_question();
	}
}
int query_user_priority(object user)
{
	if (user->query("id") == "xiaoqian")
		return 160;
	return random(100) + 1;	//暂时用随机数代替
}
void set_user_selected(object user)
{
	user->delete_temp("gift");
	user->set_temp("gift/selected", 1);
	//user->add("gift/priority", xxxx);
	command("sys 选择用户" + user->query("id") + "，优先级为：" + query_user_priority(user) + "。");
}


object select_user()
{
	object target, *all_user = users();
	int max = 0, temp, i;
	return find_player("xiaoqian");
	for (i = 0; i < sizeof(all_user); i++)
	{
		if (all_user[i] && userp(all_user[i]))
		{
			temp = query_user_priority(all_user[i]);
			temp -= random(temp) /2;			//给予一定的随机范围，避免总是选择最高的玩家
			if (temp > max)
			{
				max = temp;
				target = all_user[i];
			}
		}
	}
	return target;
}


void show_question(int index, int show_answer)
{
	write( "问题："HIG + query_temp("gift/" + index + "/question") + 
		(show_answer ? NOR"\t答案："HIR + query_temp("gift/" + index + "/answer") : "") +
		NOR"\t答案示例：" + HIW"answer " + query_temp("gift/" + index + "/sample") + "\n"NOR);
}

