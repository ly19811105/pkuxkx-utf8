// /adm/daemons/gemd.c

//这个列表用于增加在其他场景出现的物品列表，请不断更新
//请留意物品的选择，不合适的物品请不要放置在这个列表中, 比如在一些解密过程中才能拿到的物品
//总之这一部分放置最最常见的东西
//物品列表请分类明确(按出现场景或者按不同的类别来区分, 不怕重复)，但是一定要容易整理
//护镖采用特殊掉落机制by yhzzyahoo @2015.7.23
#include <ansi.h>
inherit F_DBASE;

#include <localtime.h>

float mf_rate = 1.0;

object setup_item(int success);
void item_drop(object npc, object user, object item);

float get_mf_rate()
{
	mf_rate = 0.8;

	return mf_rate;

}

void create()
{
	seteuid(getuid());
	set("name", "掉宝精灵");
	set("id", "gemdropd");
}

string *misc_item_list = ({


	//"/d/beijing/npc/obj/yuchandan",
	//   "/d/beijing/npc/obj/goldleaf.c",
	// /d/shenlongdao/obj下出现的物品

	// 普通兵器
	//   "/d/shaolin/obj/fumo-dao.c",
	//   "/d/dalicheng/obj/yxbj.c", 
	//   "/d/xingxiu/obj/bingpozhang.c", 
	//  "/d/xiangyang/npc/obj/item/27.c", //烈火鞭
	//  "/d/taohuadao/npc/obj/yuxiao.c", //玉箫
	// 食物


	// 灵丹妙药
	//"/d/xiangyang/npc/obj/shanlw.c",

	//金钱
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/gold",
	"/clone/money/thousand-cash",
	//大家看看怎样分类比较好？
	//一些相对较好的物品可以放到/d/ludingshan/obj/special目录下，比如菩提子，熊胆丸等等
});

varargs int drop(object npc, object user)
{
	/******************************************************
	1.系统掉落不仅仅跟玩家自己有关，跟npc敌人也有关系
	2.决定掉落率的有玩家的福缘，掉宝率和级别
	3.决定npc级别的有npc的经验
	*******************************************************/
	int npc_exp, npc_level;
	int ppl_level, ppl_kar, ppl_mf;
	int success;
	int mf_bonus;
	int *npc_levs = ({ 15, 30, 60, 120, 240, 480, 1000, 2000, 3000, 4000,
		5000, 6000, 7500, 9000, 12000, 15000, 18000, 21000, 24000, 30000,
		36000, 42000, 48000, 54000, 60000, 72000, 84000, 96000, 108000, 120000,
		140000, 160000, 180000, 200000, 220000, 240000, 280000, 320000, 360000, 400000 });
	object item;
	string gem;

	npc_exp = npc->query("combat_exp");
	if (!user || !objectp(user)) user = npc;
	ppl_level = user->query("level");
	ppl_kar = user->query_kar();
	ppl_mf = user->query_temp("apply/magic"); //掉落率

	//计算npc等级
	//扩充npc_level的范围，从原先的20级扩充到41级，并且调整成功率的npc_level因子，从×4变成×2.5
	//在高经验范畴下增加了差不多25%，主流经验范畴下有不同比例的下降
	npc_level = 0;
	for (int lp = 1; lp <= sizeof(npc_levs); lp++)
	{
		if (npc_exp / 1000 <= npc_levs[lp - 1])
		{
			npc_level = lp;
			break;
		}
	}

	if (!npc_level)
		npc_level = sizeof(npc_levs) + 1;

	if (wizardp(user))
		printf("%d, %d\n", npc_exp, npc_level);

	//计算玩家成功率
	success = ppl_kar / 3 + ppl_level*ppl_level / 80 + ppl_mf / 2 + npc_level * 5 / 2;
	success = success + random(success);
	mf_bonus = SPEWEEK_D->query_mf_bonus();
	mf_bonus = (mf_bonus - 100) * 2 + 100;//特殊周效果加倍
	success = success*mf_bonus / 100;

	//增加门派威望对掉率的影响。第一5%,第二3%,第三2%
	if (member_array(user->query("family/family_name"), FAMILY_D->get_repute_top(1)) != -1)
	{
		success = success * 105 / 100;
	}
	else if (member_array(user->query("family/family_name"), FAMILY_D->get_repute_top(2)) != -1)
	{
		success = success * 103 / 100;
	}
	else if (member_array(user->query("family/family_name"), FAMILY_D->get_repute_top(3)) != -1)
	{
		success = success * 102 / 100;
	}

	//增加门派争胜奖励
	if (user->query("family/family_name") == FAMILY_D->get_task_winner_family())
	{
		success = success * 120 / 100;
	}
	if (REWARD_D->get_global_factor("gem_drop") == 2.0 || REWARD_D->get_special_user_factor(user) == 2.0)
	{
		//超级狂欢周，奖励加倍。
		success *= 2;
	}

	// 增加全自动机器判断
	if (user->query("antirobot/deactivity") > 3)
	{
		success = success / 10;
	}
	else if (user->query("antirobot/deactivity") > 4)
	{
		success = success / (3 * user->query("antirobot/deactivity"));
	}

	success = to_int(1.0 * success *(get_mf_rate())); //整体调整掉宝率



	user->set_temp("magic_find", success);
	//if (success > 300)
	//MONITOR_D->report_system_msg (user->name()+"("+user->query("id")+")的掉宝成功率为"+ success +"\n"); 
	//随便给了一个计算方法，by whuan
	if (random(success) < 20 && !npc->query("QUEST_DROP_GEM"))//有些是quests里引用了gemd的函数，而这个npc exp很低success低于20，被返回了，加个特例，Zine 
		return 1;
	//  item=setup_item(obj_min, obj_max);
	item = setup_item(success);
	//减少护镖任务劫匪的四灵石头掉率，将50%的四灵转换为mu或yan
	//推车绝少掉禽兽了，fix by yhzzyahoo 2015.7.16
/*	if (file_name(npc) == "/quest/escort/cart_robber" && item->is_gem() && item->query("type") == "siling")
	{
		if (random(2))
			gem = "mu";
		else
			gem = "yan";
		item->set_special(gem, item->query("level"));
	}
	if (npc->query("name") == "劫匪" && item->query("type") == "siling")
	{
		if (random(2))
			gem = "mu";
		else
			gem = "yan";
		item->set_special(gem, item->query("level"));
	}
*/
	item_drop(npc, user, item);
}

varargs int drop_hubiao(object npc, object user)
{
	/******************************************************
	1.系统掉落不仅仅跟玩家自己有关，跟npc敌人也有关系
	2.决定掉落率的有玩家的福缘，掉宝率和级别
	3.决定npc级别的有npc的经验
	*******************************************************/
	int npc_exp, npc_level;
	int ppl_level, ppl_kar, ppl_mf;
	int success;
	int mf_bonus;
	int *npc_levs = ({ 15, 30, 60, 120, 240, 480, 1000, 2000, 3000, 4000,
		5000, 6000, 7500, 9000, 12000, 15000, 18000, 21000, 24000, 30000,
		36000, 42000, 48000, 54000, 60000, 72000, 84000, 96000, 108000, 120000,
		140000, 160000, 180000, 200000, 220000, 240000, 280000, 320000, 360000, 400000 });
	object item;
	string gem;

	npc_exp = npc->query("combat_exp");
	if (!user || !objectp(user)) user = npc;
	ppl_level = user->query("level");
	ppl_kar = user->query_kar();
	ppl_mf = user->query_temp("apply/magic"); //掉落率

	//计算npc等级
	//扩充npc_level的范围，从原先的20级扩充到41级，并且调整成功率的npc_level因子，从×4变成×2.5
	//在高经验范畴下增加了差不多25%，主流经验范畴下有不同比例的下降
	npc_level = 0;
	for (int lp = 1; lp <= sizeof(npc_levs); lp++)
	{
		if (npc_exp / 1000 <= npc_levs[lp - 1])
		{
			npc_level = lp;
			break;
		}
	}

	if (!npc_level)
		npc_level = sizeof(npc_levs) + 1;

	if (wizardp(user))
		printf("%d, %d\n", npc_exp, npc_level);

	//计算玩家成功率
	success = ppl_kar / 3 + ppl_level*ppl_level / 80 + ppl_mf / 2 + npc_level * 5 / 2;
	success = success + random(success);
	mf_bonus = SPEWEEK_D->query_mf_bonus();
	mf_bonus = (mf_bonus - 100) * 2 + 100;//特殊周效果加倍
	success = success*mf_bonus / 100;

	//增加门派威望对掉率的影响。第一5%,第二3%,第三2%
	if (member_array(user->query("family/family_name"), FAMILY_D->get_repute_top(1)) != -1)
	{
		success = success * 105 / 100;
	}
	else if (member_array(user->query("family/family_name"), FAMILY_D->get_repute_top(2)) != -1)
	{
		success = success * 103 / 100;
	}
	else if (member_array(user->query("family/family_name"), FAMILY_D->get_repute_top(3)) != -1)
	{
		success = success * 102 / 100;
	}

	//增加门派争胜奖励
	if (user->query("family/family_name") == FAMILY_D->get_task_winner_family())
	{
		success = success * 120 / 100;
	}
	if (REWARD_D->get_global_factor("gem_drop") == 2.0 || REWARD_D->get_special_user_factor(user) == 2.0)
	{
		//超级狂欢周，奖励加倍。
		success *= 2;
	}

	// 增加全自动机器判断
	if (user->query("antirobot/deactivity") > 3)
	{
		success = success / 10;
	}
	else if (user->query("antirobot/deactivity") > 4)
	{
		success = success / (3 * user->query("antirobot/deactivity"));
	}

	success = to_int(1.0 * success *(get_mf_rate())); //整体调整掉宝率



	user->set_temp("magic_find", success);
	//if (success > 300)
	//MONITOR_D->report_system_msg (user->name()+"("+user->query("id")+")的掉宝成功率为"+ success +"\n"); 
	//随便给了一个计算方法，by whuan
	if (random(success) < 20 && !npc->query("QUEST_DROP_GEM"))//有些是quests里引用了gemd的函数，而这个npc exp很低success低于20，被返回了，加个特例，Zine 
		return 1;
	//  item=setup_item(obj_min, obj_max);
	item = setup_item(success);
	//减少护镖任务劫匪的四灵石头掉率，将50%的四灵转换为mu或yan
	//推车绝少掉禽兽了，fix by yhzzyahoo 2015.7.23
	if (item->query("type") == "siling") 
	{
	//	log_file("wiz/hubiao_gem",sprintf("%s于%s掉四灵宝石%s的log。\n",geteuid(npc),ctime(time()),item->query("gem")));
		if (random(2))
			gem = "mu";
		else
			gem = "yan";
		item->set_special(gem, item->query("level"));
	}

	item_drop(npc, user, item);
}

void item_drop(object npc, object user, object item)
{
	object env = environment(npc);
	string msg;
	if (!env) return;
	if (item->query("level") > 5)
	{
		if (random(item->query("level") + 5) >= 10 && item->query("forge/max") <= 1 && item->query("armor_type") != "neck" && item->query("armor_type") != "finger")
		{
			item->add("forge/max", 1);
			item->forge_capacity();
		}
		if (item->is_gem())
			CHANNEL_D->do_channel(this_object(), "jh", "听说" + user->query("name") + "得到一"
			+ item->query("unit") + item->name() + "啦。", -1);
	}
	if (!item->move(user)) item->move(env);
	if (stringp(npc->gem_drop_msg(user, item)))//如果是npc有这个gem_drop_msg时候，优先返回这个信息。比如在房间而不是npc引用drop()函数时候，比如用“从南门身上掉下来一两黄金”就很不合理了，zine
		tell_room(environment(npc), npc->gem_drop_msg(user, item));
	else
		message_vision(GRN + "从$N身上掉了出来一" + item->query("unit") + item->name() + "\n" + NOR, npc);
	
	if (item->is_gems() && !item->is_gem() && (item->query("forge/max") >= 3))
		msg = user->name() + "得到一" + item->query("unit") + item->name()
		+ "[等级：" + item->query("level") + "，可塑性：" + item->query("forge/max") + "]。";
	if (item->is_gems() && item->is_gem() && item->query("level") >= 6)
		msg = user->name() + "得到一" + item->query("unit") + item->name()
		+ "[等级：" + item->query("level") + "]。";
	if (item->is_gems() && strwidth(msg) > 0)
		MONITOR_D->report_system_msg(msg);
	item->query_temp("seeme", user->query("id"));
	return;
}

object setup_item(int success)
{
	/************************************************************************************************
	1.drop_odds参数可以省略
	缺省情况下drop几率:80% misc, 6% weapon, 6% armor, 1.5% special, 2.5% ring, 4% gems, 0% unique(根据实际情况调整)
	//普通情况下不会出现unique物品，一般boss级别npc可以设置此参数调整drop几率
	2.weapon,armor,ring的不同类别稀有度在各自的文件中定义了，如果不太好控制可以考虑采取和gems级别限制的相同方法
	3.npc设置参数限制gems的最高级别,和非缺省情况下的drop几率
	set("item_drop_odds", ({500, 150, 150, 100, 50, 45, 5, }));
	总和1000。分别代表7种不同类物品的drop几率
	obj_min - obj_max
	0    - 5000  1级
	5000 - 8334  2级
	8335 - 9444  3级
	9445 - 9814  4级
	9815 - 9939  5级
	9940 - 9979  6级
	9980 - 9994  7级
	9995 - 10000 8级
	具体请看/clone/gem/gem.c  set_level()函数
	4.每位npc具体能够drop多少Item, 在各自的文件中自己定义，需要drop多个item的情况，多次调用本函数即可
	4.misc包括普通场景中能够得到的各种物品，也包括部分特殊药品
	************************************************************************************************/

	//其实n可以直接设定为7, 这个看以后是否增加新的物品类别而定，这样写只是为了减少以后的劳动量尽量避免出错
	//如果增加新的类别，下面的if ....else if还是需要手动修改
	int i, n, sum, *layer;
	int odds;
	object item;
	string *file;
	int *drop_odds;
	int obj_min, obj_max;
	int judge = 0;

	if (success > 40 + random(3000))      { obj_min = 8500; obj_max = 9999; judge = 7; } //6-8
	else if (success > 35 + random(2000)) { obj_min = 7300; obj_max = 9700; judge = 6; } //5-7
	else if (success > 30 + random(1000)) { obj_min = 6100; obj_max = 9300; judge = 5; } //4-6
	else if (success > 25 + random(500))  { obj_min = 4500; obj_max = 8500; judge = 4; } //3-5
	else if (success > 20 + random(200))  { obj_min = 2500; obj_max = 8500; judge = 3; }	//2-5
	else if (success > 15 + random(100))  { obj_min = 0;   obj_max = 8500; judge = 2; }	//1-5									
	else                             { obj_min = 0;   obj_max = 6100; judge = 1; } //1-4

	if (judge <= 2)
		drop_odds = ({ 800, 60, 60, 15, 25, 40, 0 });
	else if (judge <= 4)
		drop_odds = ({ 400, 220, 220, 30, 50, 80, 0 });
	else if (judge <= 5)
		drop_odds = ({ 200, 280, 280, 45, 75, 120, 0 });
	else if (judge <= 6)
		drop_odds = ({ 100, 290, 290, 60, 100, 160, 0 });
	else
		drop_odds = ({ 0, 300, 300, 75, 125, 200, 0 });
	n = sizeof(drop_odds);
	layer = allocate(n);
	if (n != 7) error("错误：drop参数数量设置错误。请通知巫师！\n");
	for (i = 0; i < n; i++)	sum = sum + drop_odds[i];
	if (sum != 1000) error("错误：drop率总和错误。请通知巫师！\n");

	layer[0] = drop_odds[0];
	for (i = 1; i < n; i++)
		layer[i] = layer[i - 1] + drop_odds[i];

	odds = random(1000);
	if (odds < layer[0])
	{
		//这部分还需要细分为 1.misc/目录下的物品;2.misc_item_list列表中的物品;3.特殊的药品
		//		file = get_dir(LDC_OBJ("misc/"));
		//		item = new(file[random(sizeof(file))]);
		item = new(misc_item_list[random(sizeof(misc_item_list))]);
		if (objectp(item))
			return item;
		else error("错误：物品(misc)生成错误，请报告巫师。\n");
	}
	else if (odds < layer[1])
	{
		item = new("/obj/gem/weapon");
		if (objectp(item))
		{
			item->gen_weapon(item->query("type"), obj_min, obj_max);
			return item;
		}
		else error("错误：物品(weapon)生成错误，请报告巫师。\n");
	}
	else if (odds < layer[2])
	{
		if (random(1000)) item = new("/obj/gem/armor");
		else
		{
			i = random(10);
			if (i < 6) item = new("/obj/taozhuang/long/longya");
			else if (i < 9) item = new("/obj/taozhuang/long/longlin");
			else item = new("/obj/taozhuang/long/longxin");
		}
		if (objectp(item))
		{
			item->gen_armor(item->query("type"), obj_min, obj_max);
			return item;
		}
		else error("错误：物品(armor)生成错误，请报告巫师。\n");
	}
	else if (odds < layer[3])
	{
		file = get_dir(LDC_OBJ("special/"));
		item = new(LDC_OBJ("special/" + file[random(sizeof(file))]));
		if (objectp(item))
			return item;
		else error("错误：物品(special)生成错误，请报告巫师。\n");
	}
	else if (odds < layer[4])
	{
		item = new("/obj/gem/ring");
		if (objectp(item))
		{
			item->gen_armor(item->query("type"), obj_min, obj_max);
			return item;
		}
		else error("错误：物品(ring)生成错误，请报告巫师。\n");
	}
	else if (odds < layer[5])
	{
		item = new("/obj/gem/gem");
		if (objectp(item))
		{
			item->set_level(obj_min, obj_max, item->query("material"));
			return item;
		}
		else error("错误：物品(gem)生成错误，请报告巫师。\n");
	}
	else
	{
		file = get_dir(LDC_OBJ("unique/"));
		item = new(LDC_OBJ("unique/" + file[random(sizeof(file))]));
		if (objectp(item))
			return item;
		else error("错误：物品(uniqie)生成错误，请报告巫师。\n");
	}
}