//护镖公共文件, 包含总镖头、接镖伙计、镖车、劫匪所需的所有公共行为函数
// by seagate@pkuxkx 2012/01/03
// 镖局设置，根据发布任务的难度不同，分为5-7的新手镖局，8到12的普通镖局，13到15的长途镖局
// 新手镖局劫匪最多不超过2人，普通镖局劫匪最多不超过3人，长途镖局劫匪在3到4人之间
// 未来等新手镖局稳定以后，提高普通镖局进入门槛，限制普通镖局至少为2个劫匪。
// 查询镖局级别函数query_escort_level(level)，输入行镖难度

//dart_info是一个mapping array，里面包含area、short、id、name、value
//分别对应护镖目的地，护镖目的地名称，收镖人ID，收镖人名称，护镖路线权重
///quest/escort/cart_target为保镖人接镖伙计
///quest/escort/obj/cart为镖车
///quest/escort/cart_robber为镖车劫匪
//附加任务
///quest/escort/obj/dart_mixin为密信

#include <ansi.h>
#include <title.h>
#include <localtime.h>

//镖局信息mapping是由镖局所在城市id作为关键字，存放镖局名称、总镖头和总镖头id、镖局提供的业务难度、行镖所需时间等信息
mapping escort_info =
(["changan":(["escort":"长安飞马镖局", "boss" : "马行空", "bossid" : "ma xingkong", "diff" : 10, "time" : 1200]),
"suzhou" : (["escort":"苏州昌隆镖局", "boss" : "左二把", "bossid" : "zuo erba", "diff" : 10, "time" : 1200]),
"nanchang" : (["escort":"南昌飞虎镖局", "boss" : "楚大业", "bossid" : "chu daye", "diff" : 13, "time" : 1500]),
"luoyang" : (["escort":"洛阳龙门镖局", "boss" : "都大锦", "bossid" : "du dajin", "diff" : 13, "time" : 1500]),
"fuzhou" : (["escort":"福州福威镖局", "boss" : "林震南", "bossid" : "lin zhennan", "diff" : 6, "time" : 720]),
"wudang" : (["escort":"武当荆西镖局", "boss" : "张志", "bossid" : "zhang zhi", "diff" : 6, "time" : 720]),
"beijing" : (["escort":"北京武胜镖局", "boss" : "王武通", "bossid" : "wang wutong", "diff" : 11, "time" : 1320]),
"jiangzhou" : (["escort":"江州天福镖局", "boss" : "王小月", "bossid" : "wang xiaoyue", "diff" : 11, "time" : 1320]),
"jiankangfu" : (["escort":"建康府金陵镖局", "boss" : "陆世清", "bossid" : "lu shiqing", "diff" : 10, "time" : 1200])
]);

string quest_fail(object ppl);
mapping get_escort_info(string escort_id);
int query_escort_level(int level);
protected void start_add_quest(object ob);
protected int get_escort_lvlexp(object me, int eslvl);
protected int check_area(mapping escinfo, string area);

//get_dart函数是玩家从总镖头哪里接镖的函数
//level是运镖级别，ob是护镖人，dart_info是运镖参数
//level和运镖难度直接相关，也和奖励直接相关，从10开始计算，每增加一点增加10%奖励，同样劫匪难度也会增加10%

// get_dart接口修改，从直接送运镖级别修改为传送镖局id
string get_dart(string escort_id, object ob, mapping *dart_info)
{
	int index, exp, level, eslvl, lowexp;
	object cart, target, owner;
	mapping esinfo;

	if (arrayp(dart_info) &&
		sizeof(dart_info) > 0 &&
		mapp(dart_info[0]))
		index = random(sizeof(dart_info));
	else
		error("运镖参数有误，请联系在线巫师。\n");

	if (!objectp(ob))
		return "未知的押镖人！\n";

	if (ob->is_busy())
		return "你正忙着呢！";

	if (!escort_id || !stringp(escort_id))
		error("镖局ID传入有误，请联系在线巫师。\n");

	esinfo = get_escort_info(escort_id);
	level = esinfo["diff"];
	eslvl = query_escort_level(level);
	exp = get_escort_lvlexp(ob, eslvl);
	if (eslvl)
		lowexp = get_escort_lvlexp(ob, eslvl - 1);
	else
		lowexp = 0;

	if (wizardp(ob))
		message_vision(sprintf("任务难度：%d, 镖局级别：%d, 最低间隔时间：%d\n", level, eslvl, 180 + (eslvl - 1) * 60), ob);

	if (level < 5 || level>15)
		error("难度系数10为普通护镖，至少要保持难度系数5，不能超过15。\n");

	if (ob->query("in_dart"))
	{
		if (!ob->query_temp("over_dart") && (int)ob->query_condition("dart_limit") <= 0)
		{
			if (ob->query_combatgrade() < 20)
			{
				ob->delete("in_dart");
				ob->delete("yunbiao/last_reward");
				return "你没有领过什么任务吧？";
			}
			return quest_fail(ob);
		}
		else
		{
			//限制机器人狂问刷屏
			ob->start_busy(10);
			return "你不是才要了任务吗？";
		}
	}

	if ((int)ob->query_condition("dart_limit") > 0)
		return "你好象没完成任务吧。";

	if (ob->is_busy() || ob->query_temp("pending/exercising"))
		return "你现在正忙着呢。";

	if (level < 10 &&
		ob->query_combatgrade() < 10 + level)
		return "护镖是件危险工作，我看" + RANK_D->query_respect(ob) + "似乎没有这能力！";

	if (level >= 10 &&
		ob->query_combatgrade() < 20 + (level - 10) * 5)
		return "护镖是件危险工作，我看" + RANK_D->query_respect(ob) + "似乎没有这能力！";

	if ((int)ob->query("repute") < -400000)
		return RANK_D->query_respect(ob) + "在江湖上混得灰头土脸，我怎么放心将镖交给你呢？";

	if ((int)ob->query_skill("force", 1) < 50)
		return "护镖是件危险工作，我看" + RANK_D->query_respect(ob) + "的基本内功不足！";

	if (!eslvl && (exp >= 2000000 || ob->query("exp/hubiao") >= 3000000))
		return "你已经在新手镖局获得足够经验了，快到大城市去闯荡一番吧。\n";
	else if (eslvl == 1 && lowexp < 2000000 && ob->query("exp/hubiao") < 3000000)
		return "你需要在新手镖局获得足够经验后，才能够护送如此贵重的镖银。\n";
	else if (eslvl == 2 && lowexp < 2000000 && ob->query("exp/hubiao") < 10000000)
		return "你需要在普通镖局获得足够经验后，才能够护送如此贵重的镖银。\n";

	if (!eslvl && ob->query("baixiaosheng/tiaozhan"))
		return "百晓生挑战任务不允许接新手镖局的任务。\n";

	if (!eslvl && ob->query_temp("shilian/start"))
		return "南海神尼考验任务不允许接新手镖局的任务。\n";

	if (!eslvl && ob->query("safari"))
		return "铜雀台揭榜任务不允许接新手镖局的任务。\n";

	if (ob->query("baixiaosheng/tiaozhan") &&
		ob->query("baixiaosheng/hb_time"))
		return "你已经完成百晓生挑战任务中的护镖部分，不能再重复接任务。\n";

	ob->set("last_yunbiao_ask_eslvl", eslvl);
	if (!ob->query("baixiaosheng/tiaozhan"))
		return "非百晓生任务请用listesc/getesc命令来领取押镖任务。\n";

	//根据镖局级别修改最低任务间隔时间，新手镖局120秒，普通镖局180秒，长途镖局240秒
	if (time() - ob->query("last_yunbiao_time") < 180 + (eslvl - 1) * 60 &&
		time() > ob->query("last_yunbiao_time"))
	{
		ob->start_busy(10);
		return "你上次运镖太辛苦了，下去休息休息吧。";
	}

	if (ob->query("antirobot/deactivity") > 2)
		message("vision", HIR"$N狠狠的对$n说到：“怎么总是你！我看你是机器人吧。”\n"NOR, this_object(), ob);

	ob->set_temp("yunbiao/high_value", level);

	ob->set("in_dart", 1);
	ob->set_temp("dart_area", dart_info[index]["area"]);
	target = new("/quest/escort/cart_target");
	target->start_leave(esinfo["time"]);
	target->move(dart_info[index]["area"]);

	if (objectp(owner = present(dart_info[index]["id"], environment(target))))
	{
		message_vision("$N对伙计$n说道：最近要有一批镖运到，你出去接应一下，早些回来！\n", owner, target);
		message_vision("$N说道：遵命！\n", target);
	}

	target->set("dart_id", ob->query("id"));
	target->set("dart_name", ob->query("name"));
	target->set("gender", ob->query("gender"));
	target->set("from_id", this_object()->query("id"));
	target->random_move();
	target->random_move();
	target->random_move();
	target->random_move();
	ob->set_temp("dart_id", dart_info[index]["id"]);
	ob->set_temp("dart_name", dart_info[index]["name"]);
	//	ob->set("in_dart",dart_info[index]["value"]);
	//	ob->set_temp("yunbiao/bonus",dart_info[index]["value"]);
	//	ob->set_temp("dart_value",dart_info[index]["value"]);
	//给予护镖任务最低奖励值2，剩下的奖励依靠区域奖励和劫匪奖励综合来获得 
	// by seagate@pkuxkx 2012/01/04
	ob->set_temp("dart_value", 2);
	ob->set_temp("yunbiao/bonus", 2);
	ob->set("in_dart", 2);

	ob->set_temp("yunbiao/killed_num", 0);
	ob->set_temp("dart_target", target);
	ob->apply_condition("dart_limit", 60);
	ob->set_temp("huoji_name", target->name());
	ob->set_temp("yunbiao/from_id", this_object()->query("id"));
	ob->set_temp("yunbiao/escort_id", escort_id);
	ob->set_temp("huoji_where", environment(target)->query("short"));
	//推车就要简化pfm信息，外人不给看了
	ob->set_temp("pfm_skip",1);

	cart = new("/quest/escort/obj/cart");
	cart->set("master", ob->query("name"));
	cart->set("masterid", ob->query("id"));
	cart->set("from_id", this_object()->query("id"));
	cart->set("long", replace_string(cart->query("long"), "镖旗", "镖旗，上书一个「" + ob->query("name")[0..0] + "」字"));
	cart->move(environment());
	command("nod");
	message_vision(CYN "几个伙计将镖推了出来。\n" NOR, ob);
	ob->set_temp("yunbiao/can_go", 1);
	ob->set_temp("yunbiao/cart_ob", cart);
	ob->set("last_yunbiao_time", time());
	ob->delete_temp("hubiao/mixin");
	CHANNEL_D->do_channel(this_object(), "sys_misc",
		sprintf("%s接到一个护镖任务，地点在%s，等级为%d。", ob->name(), dart_info[index]["short"], ob->query_temp("yunbiao/lianxu")));
	return ob->query("name") + "把这批红货送到" + dart_info[index]["short"] + dart_info[index]["name"] +
		"那里，他已经派了个伙计名叫" + target->name() + "到" + environment(target)->query("short") + "附近接你，把镖车送到他那里就行了。\n";
}

//get_dart函数是玩家从总镖头哪里接镖的函数
//level是运镖级别，ob是护镖人，dart_info是运镖参数
//level和运镖难度直接相关，也和奖励直接相关，从10开始计算，每增加一点增加10%奖励，同样劫匪难度也会增加10%

// get_dart接口修改，从直接送运镖级别修改为传送镖局id
// get_dart接口的任务栏版本
int get_dart_fb(string escort_id, object ob, mapping *dart_info, int escort_serial)
{
	int index, exp, level, eslvl, lowexp;
	object cart, target, owner, eb;
	mapping esinfo, *f_dart;
	string earea;

	if (arrayp(dart_info) &&
		sizeof(dart_info) > 0 &&
		mapp(dart_info[0]))
		index = random(sizeof(dart_info));
	else
		error("运镖参数有误，请联系在线巫师。\n");

	if (!objectp(ob))
	{
		tell_object(ob, "未知的押镖人！\n");
		return 1;
	}

	if (ob->is_busy())
	{
		tell_object(ob, "你正忙着呢！\n");
		return 1;
	}

	if (!escort_id || !stringp(escort_id))
		error("镖局ID传入有误，请联系在线巫师。\n");

	esinfo = get_escort_info(escort_id);
	level = esinfo["diff"];
	eslvl = query_escort_level(level);
	exp = get_escort_lvlexp(ob, eslvl);
	if (eslvl)
		lowexp = get_escort_lvlexp(ob, eslvl - 1);
	else
		lowexp = 0;

	if (wizardp(ob))
		message_vision(sprintf("任务难度：%d, 镖局级别：%d, 最低间隔时间：%d\n", level, eslvl, 180 + (eslvl - 1) * 60), ob);

	if (level < 5 || level>15)
		error("难度系数10为普通护镖，至少要保持难度系数5，不能超过15。\n");

	if (ob->query("in_dart"))
	{
		if (!ob->query_temp("over_dart") && (int)ob->query_condition("dart_limit") <= 0)
		{
			if (ob->query_combatgrade() < 20)
			{
				ob->delete("in_dart");
				ob->delete("yunbiao/last_reward");
				tell_object(ob, "你没有领过什么任务吧？\n");
				return 1;
			}
			tell_object(ob, quest_fail(ob) + "\n");
			return 1;
		}
		else
		{
			//限制机器人狂问刷屏
			ob->start_busy(10);
			tell_object(ob, "你不是才要了任务吗？\n");
			return 1;
		}
	}

	if ((int)ob->query_condition("dart_limit") > 0)
	{
		tell_object(ob, "你好象没完成任务吧。\n");
		return 1;
	}

	if (ob->is_busy() || ob->query_temp("pending/exercising"))
	{
		tell_object(ob, "你现在正忙着呢。\n");
		return 1;
	}

	if (level < 10 &&
		ob->query_combatgrade() < 10 + level)
	{
		tell_object(ob, "护镖是件危险工作，我看" + RANK_D->query_respect(ob) + "似乎没有这能力！\n");
		return 1;
	}

	if (level >= 10 &&
		ob->query_combatgrade() < 20 + (level - 10) * 5)
	{
		tell_object(ob, "护镖是件危险工作，我看" + RANK_D->query_respect(ob) + "似乎没有这能力！\n");
		return 1;
	}

	if ((int)ob->query("repute") < -400000)
	{
		tell_object(ob, RANK_D->query_respect(ob) + "在江湖上混得灰头土脸，我怎么放心将镖交给你呢？\n");
		return 1;
	}

	if ((int)ob->query_skill("force", 1) < 50)
	{
		tell_object(ob, "护镖是件危险工作，我看" + RANK_D->query_respect(ob) + "的基本内功不足！\n");
		return 1;
	}

	if (!eslvl && (exp >= 2000000 || ob->query("exp/hubiao") >= 3000000))
	{
		tell_object(ob, "你已经在新手镖局获得足够经验了，快到大城市去闯荡一番吧。\n");
		return 1;
	}
	else if (eslvl == 1 && lowexp < 2000000 && ob->query("exp/hubiao") < 3000000)
	{
		tell_object(ob, "你需要在新手镖局获得足够经验后，才能够护送如此贵重的镖银。\n");
		return 1;
	}
	else if (eslvl == 2 && lowexp < 2000000 && ob->query("exp/hubiao") < 10000000)
	{
		tell_object(ob, "你需要在普通镖局获得足够经验后，才能够护送如此贵重的镖银。\n");
		return 1;
	}

	ob->set("last_yunbiao_ask_eslvl", eslvl);
	if (ob->query("baixiaosheng/tiaozhan"))
	{
		tell_object(ob, "百晓生挑战任务不允许使用任务栏模式接任务。\n");
		return 1;
	}

	//根据镖局级别修改最低任务间隔时间，新手镖局120秒，普通镖局180秒，长途镖局240秒
	if (time() - ob->query("last_yunbiao_time") < 180 + (eslvl - 1) * 60 &&
		time() > ob->query("last_yunbiao_time"))
	{
		ob->start_busy(10);
		tell_object(ob, "你上次运镖太辛苦了，下去休息休息吧。\n");
		return 1;
	}

	if (ob->query("antirobot/deactivity") > 2)
		message("vision", HIR"$N狠狠的对$n说到：“怎么总是你！我看你是机器人吧。”\n"NOR, this_object(), ob);
	//任务栏模式从任务栏信息中提取任务信息	
	if (!(eb = find_object("/quest/escort/escort_board")))
		eb = load_object("/quest/escort/escort_board");
	earea = eb->get_escort(escort_id, escort_serial, ob);
	if (earea)
		f_dart = filter_array(dart_info, (:check_area : ), earea);
	else
		return 1;
	ob->set("yunbiao/serial", escort_serial);

	ob->set_temp("yunbiao/high_value", level);
	ob->set_temp("pfm_skip",1);

	ob->set("in_dart", 1);
	ob->set_temp("dart_area", f_dart[0]["area"]);
	target = new("/quest/escort/cart_target");
	target->start_leave(esinfo["time"]);
	target->move(f_dart[0]["area"]);

	if (objectp(owner = present(f_dart[0]["id"], environment(target))))
	{
		message_vision("$N对伙计$n说道：最近要有一批镖运到，你出去接应一下，早些回来！\n", owner, target);
		message_vision("$N说道：遵命！\n", target);
	}

	target->set("dart_id", ob->query("id"));
	target->set("dart_name", ob->query("name"));
	target->set("gender", ob->query("gender"));
	target->set("from_id", this_object()->query("id"));
	target->random_move();
	target->random_move();
	target->random_move();
	target->random_move();
	ob->set_temp("dart_id", f_dart[0]["id"]);
	ob->set_temp("dart_name", f_dart[0]["name"]);
	//	ob->set("in_dart",dart_info[index]["value"]);
	//	ob->set_temp("yunbiao/bonus",dart_info[index]["value"]);
	//	ob->set_temp("dart_value",dart_info[index]["value"]);
	//给予护镖任务最低奖励值2，剩下的奖励依靠区域奖励和劫匪奖励综合来获得 
	// by seagate@pkuxkx 2012/01/04
	ob->set_temp("dart_value", 2);
	ob->set_temp("yunbiao/bonus", 2);
	ob->set("in_dart", 2);

	ob->set_temp("yunbiao/killed_num", 0);
	ob->set_temp("dart_target", target);
	ob->apply_condition("dart_limit", 60);
	ob->set_temp("huoji_name", target->name());
	ob->set_temp("yunbiao/from_id", this_object()->query("id"));
	ob->set_temp("yunbiao/escort_id", escort_id);
	ob->set_temp("huoji_where", environment(target)->query("short"));

	cart = new("/quest/escort/obj/cart");
	cart->set_temp("seeme", ob->query("id"));
	cart->set("master", ob->query("name"));
	cart->set("masterid", ob->query("id"));
	cart->set("from_id", this_object()->query("id"));
	cart->set("long", replace_string(cart->query("long"), "镖旗", "镖旗，上书一个「" + ob->query("name")[0..0] + "」字"));
	cart->move(environment());
	command("nod");
	message_vision(CYN "几个伙计将镖推了出来。\n" NOR, ob);
	ob->set_temp("yunbiao/can_go", 1);
	ob->set_temp("yunbiao/cart_ob", cart);
	ob->set("last_yunbiao_time", time());
	ob->delete_temp("hubiao/mixin");
	CHANNEL_D->do_channel(this_object(), "sys_misc",
		sprintf("%s接到一个护镖任务，地点在%s，等级为%d。", ob->name(), f_dart[0]["short"], ob->query_temp("yunbiao/lianxu")));
	tell_object(ob, ob->query("name") + "把这批红货送到" + f_dart[0]["short"] + f_dart[0]["name"] +
		"那里，他已经派了个伙计名叫" + target->name() + "到" + environment(target)->query("short") + "附近接你，把镖车送到他那里就行了。\n");
	return 1;
}

//give_reward函数是玩家完成护镖以后，总镖头给玩家的奖励
//地点奖励由query_temp("yunbiao/dart_rooms")提供
int admire(object ob)
{
	string *admires = ({ "admire", "praise", "praise2", "no1", "applaud", "bow" });
	CHANNEL_D->do_channel(this_object(), "bd", admires[random(sizeof(admires))] + " " + ob->query("id"), 1);
}
string give_reward(object ob)
{
	int grward; //金钱奖励
	int bonus, cost_time;
	int creward, preward, rreward, mreward;
	int deactivity_rate, dart_rooms, dart_level;
	int eslvl;
	object eb;

	if (!objectp(ob) &&
		!userp(ob))
		return "未知的押镖人！\n";

	if (!ob->query("in_dart"))
		return "我没让你走镖啊？";

	if (!ob->query_temp("over_dart"))
		return "镖车没有送到地头，莫非是你吞了！？";

	if (ob->query_temp("finis_cart") &&
		(!ob->query_temp("yunbiao/from_id") ||
		ob->query_temp("yunbiao/from_id") != this_object()->query("id")))
		return "听说你刚送完镖，但是是我家的镖吗！？";
	if (!ob->query("biography/jobs/hubiao"))
	{
		ob->set("biography/jobs/hubiao", time());//个人传记记录第一次完成任务时间ZINE
	}
	/*去掉finish_du之类特殊判定 by seagate@pkuxkx
	  if (!ob->query_temp("finish_du"))
	  {
	  return "听说你刚送完镖，但是是我家的镖吗！？";
	  }
	  ob->delete_temp("finish_du");
	  */

	//加入reward_d管理后，antirobot由reward负责
	deactivity_rate = 100;
	//任务栏模式从任务栏信息中提取任务信息	
	if (!(eb = find_object("/quest/escort/escort_board")))
		eb = load_object("/quest/escort/escort_board");
	eb->update_stat(ob->query_temp("yunbiao/escort_id"), ob->query("yunbiao/serial"), 2, ob);

	if (ob->query("baixiaosheng/tiaozhan"))
	{
		ob->add("baixiaosheng/hb_time", 1);
	}

	if (ob->query("hbisrobot"))
	{
		ob->add("hbisrobot", 1);
	}

	if (ob->query_temp("yunbiao/lianxu") == 5)
	{
		ob->delete_temp("yb_addi");
	}
	//删除pfm信息简化标记
	if (ob->query_temp("pfm_skip"))
	{
		ob->delete_temp("pfm_skip");
	}
	//进入触发护镖附加任务子函数  
	start_add_quest(ob);
	//进入计算奖励环节

	//计算任务难度，默认为10
	if (ob->query_temp("yunbiao/high_value"))
		dart_level = ob->query_temp("yunbiao/high_value");
	else
		dart_level = 10;

	//计算护镖经过的房间数，默认为2+(dart_level-10)	
	if (arrayp(ob->query_temp("yunbiao/dart_rooms")))
		dart_rooms = sizeof(ob->query_temp("yunbiao/dart_rooms"));
	else
		dart_rooms = 2 + (dart_level - 10);

	if (dart_rooms < (dart_level - 8))
		dart_rooms = dart_level - 8;

	if (dart_rooms <= 0)
		dart_rooms = 1;

	if (ob->query_combatgrade() >= 60)
	{
		creward = (random(15) + 5)*(dart_rooms + ob->query_temp("yunbiao/bonus"))*deactivity_rate / 100;
		preward = (random(4) + 3)*(dart_rooms + ob->query_temp("yunbiao/bonus"))*deactivity_rate / 100;
		rreward = (1 + random(2))*(dart_rooms + ob->query_temp("yunbiao/bonus"))*deactivity_rate / 100;
	}
	else
	{
		creward = (random(15) + 10)*(dart_rooms + ob->query_temp("yunbiao/bonus"))*deactivity_rate / 100;
		preward = (random(4) + 6)*(dart_rooms + ob->query_temp("yunbiao/bonus"))*deactivity_rate / 100;
		rreward = (2 + random(3))*(dart_rooms + ob->query_temp("yunbiao/bonus"))*deactivity_rate / 100;
	}

	ob->add_temp("yunbiao/lianxu", 1);
	creward = ceil(creward*ob->query_temp("yunbiao/lianxu")*(dart_level*2.5) / 10);
	preward = ceil(preward*ob->query_temp("yunbiao/lianxu")*(dart_level*2.5) / 10);
	rreward = ceil(rreward*ob->query_temp("yunbiao/lianxu")*(dart_level*2.5) / 10);
	grward = (int)ob->query_temp("yunbiao/lianxu");
	//特殊周效果    
	creward = creward*SPEWEEK_D->query_hubiao_bonus() / 100;
	preward = preward*SPEWEEK_D->query_hubiao_bonus() / 100;
	rreward = rreward*SPEWEEK_D->query_hubiao_bonus() / 100;
	if (ob->query_combatgrade() < 30)  //加入500k-1.1M的额外20%奖励，配合cut护卫，引导玩家尝试各种任务 by Zine Nov 11 2010
	{
		creward = creward * 6 / 5;
		preward = preward * 6 / 5;
		rreward = rreward * 6 / 5;
	}

	if (time() < 1292198399) //护镖对地图要求略高于其他任务，狂欢期再1.5倍奖励
	{
		creward = creward * 3 / 2;
		preward = preward * 3 / 2;
		rreward = rreward * 3 / 2;
	}

	if (ob->query("hbisrobot") > 2) //打击机器人的任务奖励到正常1/4 By Zine Nov 24 2010
	{
		creward = creward / (int)ob->query("hbisrobot");
		preward = preward / (int)ob->query("hbisrobot");
		rreward = rreward / (int)ob->query("hbisrobot");
	}

	if (ob->query_temp("extrajob/" + this_object()->query("id")))
	{
		ob->delete_temp("extrajob/" + this_object()->query("id"));
		creward = creward * 2;
		preward = preward * 2;
		rreward = rreward * 2;
	}

	creward = REWARD_D->add_exp(ob, creward);
	preward = REWARD_D->add_pot(ob, preward);

	if (ob->query_combatgrade() >= 60)
	{
		if (ob->query_temp("yunbiao/lianxu") > 9)
		{
			admire(ob);
			ob->set_temp("yunbiao/lianxu", 5);
			message("vision", HIC"由于你的辛勤劳动，你额外获得" + chinese_number(preward) + "潜能的奖励！\n"NOR, ob);
			ob->add("potential", preward);
			preward = preward * 2;
		}
	}
	else
	{
		if (ob->query_temp("yunbiao/lianxu") > 7)
		{
			admire(ob);
			ob->set_temp("yunbiao/lianxu", 3);
			message("vision", HIC"由于你的辛勤劳动，你额外获得" + chinese_number(preward) + "潜能的奖励！\n"NOR, ob);
			ob->add("potential", preward);
			preward = preward * 2;
		}
	}

	ob->add("exp/hubiao", creward);
	ob->add("pot/hubiao", preward);
	ob->add("yunbiao/exp/" + this_object()->query("id"), creward);

	rreward = REWARD_D->add_rep(ob, rreward);
	eslvl = F_ESCORT->query_escort_level(dart_level);
	if (!eslvl)
		mreward = random(grward) * 10000 + 10000;
	else if (eslvl == 1)
		mreward = random(grward) * 20000 + 20000;
	else
		mreward = random(grward) * 30000 + 20000;
	mreward = REWARD_D->add_money(ob, mreward);

	message("vision", HIW"你一共被奖励了：\n" + chinese_number(creward) + "点经验；\n" +
		chinese_number(preward) + "点潜能；\n" + chinese_number(rreward) + "点江湖声望。\n"NOR, ob);
	message_vision(CYN"$N吩咐了旁边的镖头几句，转头对$n道：「辛苦了，有几两银子略表心意，已经吩咐人存入你的钱庄账户。」\n"NOR, this_object(), ob);

	ob->add("jobs/completed/hubiao", 1);
	this_object()->add("statistic/finish", 1);
	CHANNEL_D->do_channel(this_object(), "sys_misc", sprintf("%s护镖获得经验%d，潜能%d，声望%d。", ob->name(), creward, preward, rreward));

	//加入任务统计系统 by icer
	cost_time = time() - ob->query("last_yunbiao_time");
	if (cost_time < 1000)
	{
		COMBAT_D->add("task_stat/hubiao/complete_times", 1);
		COMBAT_D->add("task_stat/hubiao/cost_time", cost_time);
		COMBAT_D->add("task_stat/hubiao/exp", creward);
		COMBAT_D->add("task_stat/hubiao/pot", preward);
		COMBAT_D->add("task_stat/hubiao/repute", rreward);
		COMBAT_D->add("task_stat/hubiao/expratio", to_float(creward) / ob->query("combat_exp"));
	}

	ob->set("yunbiao/last_reward", creward / 2);
	ob->add_temp("yunbiao/lianxunum", 1);
	command("pat " + ob->query("id"));
	ob->delete("in_dart");
	ob->delete("yunbiao/fail_num");
	ob->delete_temp("over_dart");
	ob->delete_temp("dart_name");
	ob->delete_temp("dart_id");
	ob->delete_temp("dart_area");
	ob->delete_temp("dart_value");
	ob->delete_temp("yunbiao/bonus");
	ob->delete_temp("yunbiao/high_value");
	ob->delete_temp("yunbiao/dart_rooms");
	ob->delete_temp("yunbiao/from_id");
	ob->delete_temp("yunbiao/escort_id");
	ob->delete_temp("finis_cart");
	ob->save();
	if (ob->query("hbisrobot"))
	{
		ob->set_temp("yunbiao/lianxu", 1 + random(2));
		ob->delete_temp("yb_addi");
	}
	return RANK_D->query_respect(ob) + "果然是栋梁之才！";
}

//quest_fail函数是玩家取消护镖任务的函数
string quest_fail(object ppl)
{
	int exp;
	object eb;

	if (!objectp(ppl) &&
		!userp(ppl))
		return "未知的押镖人！\n";

	if (!ppl->query("in_dart"))
		return "你没有领过什么任务吧？";
	else
	{
		if (ppl->query("balance") < 100000)
			return "你弄丢了我的镖，得赔偿我的损失，只是你的存款不够，你想想办法再来吧！";

		//任务栏模式从任务栏信息中提取任务信息	
		if (!(eb = find_object("/quest/escort/escort_board")))
			eb = load_object("/quest/escort/escort_board");
		eb->update_stat(ppl->query_temp("yunbiao/escort_id"), ppl->query("yunbiao/serial"), 3, ppl);

		ppl->apply_condition("dart_limit", -1);
		//赔偿5gold    
		if (ppl->query_temp("yunbiao/fail_num"))
		{
			ppl->add("yunbiao/fail_num", ppl->query_temp("yunbiao/fail_num"));
			ppl->delete_temp("yunbiao/fail_num");
		}
		ppl->add("yunbiao/fail_num", 1);
		if (ppl->query("yunbiao/fail_num") > 9)
		{
			command("slap " + ppl->query("id"));
			command("say 你已经连续丢了我这么多趟镖，得赔偿我10倍的损失。");
			ppl->add("balance", -500000);
			ppl->add("repute", -10000);
		}
		else
		{
			command("heng");
			command("say 你弄丢了我的镖，得赔偿我的损失，哼！");
			ppl->add("balance", -50000);
			ppl->add("repute", -1000);
		}

		if (objectp(ppl->query_temp("yunbiao/cart_ob")))
			destruct(ppl->query_temp("yunbiao/cart_ob"));

		log_file("static/escort_fail", sprintf("%s(%s) 在%s帮" + this_object()->query("name") + "进行第%s轮护镖任务失败！\n",
			ppl->query("name"), ppl->query("id"), ctime(time()), chinese_number(ppl->query_temp("yunbiao/lianxunum"))));
		ppl->set_temp("yunbiao/lianxu", 0);
		ppl->set_temp("yunbiao/lianxunum", 0);
		ppl->delete("in_dart");
		ppl->delete("yunbiao/last_reward");
		ppl->delete_temp("yunbiao/dart_rooms");
		ppl->delete_temp("yunbiao/from_id");
		ppl->delete_temp("yunbiao/escort_id");
		ppl->delete_temp("finis_cart");
		ppl->delete_temp("yb_addi");
		ppl->delete_temp("hubiao/mixin");
		if (ppl->query_temp("pfm_skip"))
		{
			ppl->delete_temp("pfm_skip");
		}

		ppl->save();
	}

	return "这点小事你都办不好，还能指望你作些什么呢？";
}

//检查附加任务完成结果，检查成功，完成附加任务，则返回1，否则返回0继续检查其他物品
int check_add_quest(object me, object caiwu)
{
	int i, exp, pot;
	string gem;
	object baoshi;

	if (caiwu->query("id") == "cai wu" &&
		caiwu->query("owner") == me->query("id") &&
		caiwu->query("from_id") == this_object()->query("id") &&
		me->query_temp("hubiao/mixin"))
	{
		if (random(me->query_combatgrade()) > random(70))
		{
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

			baoshi = new("/obj/gem/gem");
			baoshi->set_level(5001, 9999, gem);    //忽略地
			baoshi->move(me);
			CHANNEL_D->do_channel(this_object(), "rw", me->name(1) + "在帮助" + this_object()->query("name") + "追回财物后，获得" + baoshi->name() + "一枚!");
			CHANNEL_D->do_channel(this_object(), "sys_misc", me->name(1) + "在帮助" + this_object()->query("name") + "追回财物后，获得" + baoshi->name() + "一枚!");
			log_file("static/skf", sprintf("%s(%s) 在%s帮" + this_object()->query("name") + "追回财物任务中获得" + baoshi->name() + "一枚！\n",
				me->query("name"), me->query("id"), ctime(time())));
			me->set_temp("yunbiao/lianxu", 6);
			me->set_temp("yb_addi", 1);
			me->delete_temp("hubiao/mixin");
			me->delete("secondxin");
			me->add_busy(1);
			call_out("destobj", 1, caiwu);
			tell_object(me, this_object()->query("name") + "道：哇，你太厉害了，这么快就把这些财物追回，我有重谢！\n");
			return 1;
		}
		else
		{
			exp = (random(800) + me->query("yunbiao/last_reward")) * 10;
			if (exp > 25000)
				exp = 25000;
			pot = exp / 2;

			exp = REWARD_D->add_exp(me, exp);
			pot = REWARD_D->add_pot(me, pot);
			me->add("exp/hubiao", exp);
			me->add("pot/hubiao", pot);

			tell_object(me, me->query("name") + HIC"帮" + this_object()->query("name") + "追回财物，额外获得" + chinese_number(exp) +
				"点经验和" + chinese_number(pot) + "点潜能的奖励！\n"NOR);
			//      message("vision",HIC"$n帮$N追回财物，额外获得"+chinese_number(exp)+"点经验的奖励！\n"NOR,this_object(),me);
			//      message("vision",HIC"$n帮$N追回财物，额外获得"+chinese_number(pot)+"点潜能的奖励！\n"NOR,this_object(),me);
			me->set_temp("yunbiao/lianxu", 6);
			me->set_temp("yb_addi", 1);
			me->delete_temp("hubiao/mixin");
			me->delete("secondxin");
			me->add_busy(1);
			call_out("destobj", 1, caiwu);
			tell_object(me, this_object()->query("name") + "道：哇，你太厉害了，这么快就把这些财物追回，我有重谢！\n");
			return 1;
		}
	}
	else
		return 0;
}

//重新获得密信
int restart_add_quest(object me, object caiwu)
{
	object ob = this_object(), mx;

	if (!caiwu->query_temp("xinread"))
	{
		call_out("destobj", 1, caiwu);
		ob->add_busy(1);
		command("say 看都没看就还给我？好吧，不帮忙就算了。");
		return 1;
	}

	if (me->query("secondxin"))
	{
		call_out("destobj", 1, caiwu);
		ob->add_busy(1);
		command("say 你上次就偷懒，这次还来这套？");
		return 1;
	}

	call_out("destobj", 1, caiwu);
	ob->add_busy(1);
	me->add_busy(1);
	command("say 这么点小麻烦你都克服不了？好吧好吧，我再给你一次机会。");
	tell_object(me, ob->query("name") + "又给了你一封信。\n");
	mx = new("/quest/escort/obj/dart_mixin");
	mx->set("owner", me->query("id"));
	mx->set("from_id", ob->query("id"));
	mx->set("from_name", ob->query("name"));
	mx->set("long", "这是一张" + this_object()->query("name") + "给你的密信，需要用特殊的药水才能显形(xian)。\n");
	mx->move(me);
	me->set("secondxin", 1);
	me->set_temp("hubiao/mixin", 1);
	return 1;
}

//护镖头衔配置函数
int escort_rank(string escort)
{
	object me = this_player(), ob = this_object();
	int exp;
	string title;

	exp = (int)me->query("yunbiao/exp/" + ob->query("id"));

	if (exp <= 2000000)
	{
		command("say 你对本镖局贡献太小，不能给你什么称号。\n");
		return 1;
	}

	if (exp <= 3000000)
		title = HIR + escort + HIY"见习镖师"NOR;
	else if (exp <= 5000000)
		title = HIR + escort + HIY"镖师"NOR;
	else if (exp < 10000000)
		title = HIR + escort + HIY"少镖头"NOR;
	else
		title = HIR + escort + HIY"总镖头"NOR;

	me->set("title", title);
	//title系统记录玩家title by seagate@pkuxkx
	me->set_title(({ TITLE_MJOB1, TITLE_MJOB2, TITLE_MJOB3 }), title, ({ escort }));

	tell_object(me, ob->query("name") + "对你说：你可以做" + me->query("title") + "。\n");
	me->save();
	return 1;
}

//查询镖局的级别，镖局分为0-新手镖局，1-普通镖局，2-长途镖局三种级别
int query_escort_level(int level)
{
	if (level <= 7)
		return 0;
	else if (level <= 12)
		return 1;
	else
		return 2;
}

//获得镖局对应的镖局设置信息
mapping get_escort_info(string escort_id)
{
	if (mapp(escort_info[escort_id]))
		return escort_info[escort_id];
	else
		error("错误的镖局id，请核对输入的镖局编号是否正确。\n");
}

//触发护镖的附加任务
protected void start_add_quest(object ob)
{
	object mx;

	if (wizardp(ob))
		message_vision(sprintf("护镖附加任务测试:hbisrobot:%d, lianxunum:%d, lianxu:%d\n",
		ob->query("hbisrobot"), ob->query_temp("yunbiao/lianxunum"), ob->query_temp("yunbiao/lianxu")), ob);

	if ((!ob->query("hbisrobot") && ob->query_temp("yunbiao/lianxunum") > 5 && ob->query_temp("yunbiao/lianxu") == 5 && random(2))
		|| (!ob->query("hbisrobot") && ob->query("env/hubiao_additional") && ob->query_temp("yunbiao/lianxu") == 5)
		|| ob->query("hbisrobot") >= 6)
	{
		message("vision", HIC"$N沉吟着，护了这么多趟镖，你是值得信赖的，也许你可以再帮我一个忙？\n"NOR, this_object(), ob);
		mx = new("/quest/escort/obj/dart_mixin");
		if (mx)
		{
			mx->set("owner", ob->query("id"));
			mx->set("from_id", this_object()->query("id"));
			mx->set("from_name", this_object()->query("name"));
			mx->set("long", "这是一张" + this_object()->query("name") + "给你的密信，需要用特殊的药水才能显形(xian)。\n");
			tell_object(ob, this_object()->query("name") + "递给你一封密信。\n");
			mx->move(ob);
			ob->set_temp("hubiao/mixin", 1);
			tell_object(ob, "\n" + this_object()->query("name") + "告诉你：这封信用特殊药水写就，你把它显形后，按照指示去做就可以了。\n");
			ob->delete_temp("yb_addi");
			//先把运镖连续奖励随机到0-4轮，40%过关，如果完成后续任务，判断为人工，再恢复到4，即每轮检查一次。 By Zine Nov 11 2010
			if (!ANTIROBOT_D->stopped())
			{
				ob->add("hbisrobot", 1);
			}
		}
	}
}

//查询玩家完成各级别镖局经验
protected int get_escort_lvlexp(object me, int eslvl)
{
	string eskey;
	int exp;

	exp = 0;
	foreach(eskey in keys(escort_info))
	{
		if (eslvl != query_escort_level(escort_info[eskey]["diff"]))
			continue;
		else
		{
			exp = exp + me->query("yunbiao/exp/" + escort_info[eskey]["bossid"]);
		}
	}

	return exp;
}

protected int check_area(mapping escinfo, string area)
{
	if (escinfo["area"] == area)
		return 1;
	else
		return 0;
}

void destobj(object ob)
{
	if (objectp(ob))
		destruct(ob);
}