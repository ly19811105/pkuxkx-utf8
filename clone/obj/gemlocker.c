
#include <ansi.h>
inherit F_SAVE;
inherit ITEM;
#include <title.h>
#include "tobedone.h"
#define TITLE_SAVE "/data/business/honor_title"

nosave string *gems_level = ({
	"地",
	"山",
	"水",
	"风",
	"雷",
	"火",
	"泽",
	"天"
});

string query_save_file()
{
	return TITLE_SAVE;
}
int down_price();
void create()
{
	string* color = ({ HIR, RED, HIY, YEL, HIB, BLU, HIG, GRN, HIC, CYN, MAG, HIM, HIW, WHT });
	set_name(color[random(sizeof(color))] + "锦囊" + NOR, ({ "jin nang", "nang", "baoshi dai", "dai", "gem bag" }));
	set_weight(1);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "这是一个精致的锦囊，可以装很多宝石。你可以检查(jiancha)自己的宝石\n");
		set("material", "cloth");
		set("unit", "个");
		set("value", 1);
		set("no_get", "这个袋子拿不起来。\n");
		set("no_drop", "这个袋子不能扔。\n");
		set("no_give", "这个袋子不能给别人。\n");
		set("no_steal", "这个袋子不能偷。\n");
		set("gem_locker", 1);
	}
	setup();
	call_out("down_price", 1);
}

int down_price()
{
	to_do_list();
	set("value", 0);
}

void init()
{
	add_action("do_pick", "pickgem");
	add_action("do_pack", "pack");
	add_action("do_jiancha1", "jiancha");
	//add_action("do_jiancha1","jiancha1");
	add_action("do_querytitle", "querytitle");
	add_action("do_zhuicha", "zhuicha");
	add_action("do_olympic", "olympic");
}
int do_olympic()
{
	object me = this_player();
	if (time() > 1344962118)
	{
		return 0;
	}
	if (!me->query("olympic/target_exp"))
	{
		return 0;
	}
	tell_object(me, "目标" + me->query("olympic/target_exp") + "。\n");
	return 1;
}
int do_querytitle()
{
	object me = this_player(), ob = this_object();
	string title, *titles = ({}), output = "";
	int i, flag = 0, flag2 = 0;
	if (!title = COLOR_D->uncolor(me->get_title(TITLE_HONOR)))
	{
		return 0;
	}
	if (title == "")
	{
		return 0;
	}
	ob->restore();
	if (ob->query(title))
	{
		titles = ob->query(title);
	}
	if (titles && arrayp(titles))
	{
		for (i = 0; i < sizeof(titles); i++)
		{
			if (titles[i] == me->query("id"))
			{
				continue;
			}
			flag2 += 1;
			if (flag < 3 && titles[i])
			{
				flag += 1;
				output += titles[i] + " ";
			}
		}
	}
	if (flag2 > 0)
	{
		if (flag == 1)
		{
			output = replace_string(output, " ", "");
			tell_object(me, "江湖中除你之外，被称为" + title + "的还有" + output + "。\n");
		}
		else
		{
			tell_object(me, "江湖中除你之外，被称为" + title + "的共有" + output + "等" + chinese_number(flag2) + "人。\n");
		}
	}
	else
	{
		tell_object(me, "目前江湖中，只有你被人称作" + title + "。\n");
	}
	return 1;
}

int do_jiancha(string arg)
{
	object  me;
	mapping gembox, num, obj;
	string  msg, name, *slot;
	int     i, amount, allamount = 0;
	me = this_player();
	if (!arg)
		return notify_fail("请用jiancha jin nang命令来查看宝石。\n");
	if (arg != "nang" && arg != "jin nang" && arg != "baoshi dai"&& arg != "dai" && arg != "gem bag")
		return notify_fail("请用jiancha jin nang命令来查看宝石。\n");


	if (!mapp(gembox = me->query("gembox_slot")))
	{
		tell_object(me, "你的宝石袋里空空荡荡，用" + HIY"pack <宝石id> "NOR + "将宝石放入其中！\n");
		return 1;
	}
	if (!mapp(num = me->query("gembox_number")))
	{
		tell_object(me, "你的宝石袋里空空荡荡，用" + HIY"pack <宝石id> "NOR + "将宝石放入其中！\n");
		return 1;
	}
	if (sizeof(gembox) != sizeof(num))
	{
		tell_object(me, HIR "\n你的宝石袋遭劫了，请和巫师联系。\n" NOR);
		return 1;
	}

	if (!sizeof(gembox))
	{
		tell_object(me, "你的宝石袋里空空荡荡，用" + HIY"pack <物品id> "NOR + "将宝石放入其中！\n");
		return 1;
	}
	slot = keys(gembox);

	msg = CYN"\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n" NOR;

	for (i = 0; i < sizeof(slot); i++) {

		amount = num[slot[i]];
		obj = gembox[slot[i]];
		msg = sprintf("%s" HIG "%3d、" NOR "%15s  %s                    " HIW "%d\n"NOR,
			msg,
			i + 1,
			" ",
			slot[i], amount);
		allamount + amount;
	}
	msg += CYN"\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n"NOR;
	msg += "你的宝石袋里共有" + allamount + "个宝石。";
	msg += "\n用" + HIY"pack <物品id>"NOR + "将宝石放入其中，用" + HIC"pickgem <序号>"NOR + "取出其中的某一宝石。\n"NOR;

	me->start_more(msg);
	return 1;


}

int do_jiancha1(string arg)
{
	object  me;
	mapping gembox, num, obj;
	string  msg;

	/* added by labaz 定义gem相关类型 */
	string *gemtype = ({ "★炎晶", "★木灵", "◎玉髓", "☆精金", "☆玄冰", "★日魂", "☆月魄", "★神龙骨", "★凤凰羽", "★麒麟角", "★玄武甲", "◎神龙骨", "◎凤凰羽", "◎麒麟角", "◎玄武甲", "☆神龙骨", "☆凤凰羽", "☆麒麟角", "☆玄武甲" });
	mapping gemdata = ([]), gemdisp = ([]);
	string *name, *gemdisp_idx, temp, *gem_name, gemlevel, levelname, *gemdata_key;
	int i, j, amount, *number, column, tabsize;

	int m = 0;
	int n = 0;
	int column_no = 5;
	mapping mapa;

	me = this_player();

	if (!arg)
		return notify_fail("请用jiancha jin nang命令来查看宝石。\n");
	if (arg != "nang" && arg != "jin nang" && arg != "baoshi dai"&& arg != "dai" && arg != "gem bag")
		return notify_fail("请用jiancha jin nang命令来查看宝石。\n");

	if (!mapp(gembox = me->query("gembox_number")))
	{
		tell_object(me, "你的宝石袋里空空荡荡，用" + HIY"pack <宝石id> "NOR + "将宝石放入其中！\n");
		return 1;
	}
	if (!mapp(num = me->query("gembox_number")))
	{
		tell_object(me, "你的宝石袋里空空荡荡，用" + HIY"pack <宝石id> "NOR + "将宝石放入其中！\n");
		return 1;
	}
	if (sizeof(gembox) != sizeof(num))
	{
		tell_object(me, HIR "\n你的宝石袋遭劫了，请和巫师联系。\n" NOR);
		return 1;
	}

	if (!sizeof(gembox))
	{
		tell_object(me, "你的宝石袋里空空荡荡，用" + HIY"pack <物品id> "NOR + "将宝石放入其中！\n");
		return 1;
	}
	// slot = keys(gembox);
	name = keys(gembox);
	number = values(gembox);
	for (i = 0; i < sizeof(name); i++)   /* added by labaz sizeof(name)--玩家拥有宝石的名称总数 */
	{
		// gemdata[name[i]]["index"]=i+1;
		// gemdata[name[i]]["number"]=number[i]);
		for (j = 0; j < sizeof(gemtype); j++)    /* added by labaz sizeof(gemtype)--游戏中定义宝石的大类总数 */
		{
			if (strsrch(name[i], gemtype[j], 1) > 0)
			{
				/* added by labaz 初始化类型声明 */
				if (undefinedp(gemdata[gemtype[j]])) gemdata[gemtype[j]] = ([]);
				if (undefinedp(gemdata[gemtype[j]][name[i]])) gemdata[gemtype[j]][name[i]] = ([]);
				if (undefinedp(gemdata[gemtype[j]]["gemlevel"])) gemdata[gemtype[j]]["gemlevel"] = ({});
				/* added by labaz 宝石数量和名称存储 */
				gemdata[gemtype[j]][name[i]]["index"] = i + 1;
				gemdata[gemtype[j]][name[i]]["number"] = number[i];
				/* added by labaz 宝石大类从地到天的等级汇总 */
				levelname = replace_color(name[i]);
				gemlevel = levelname[0..0];
				gemdata[gemtype[j]]["gemlevel"] += ({ gemlevel });
				break;
			}
		}
	}

	gemdata_key = keys(gemdata);
	for (i = 0; i < sizeof(gemdata); i++)   /* added by labaz sizeof(gemdata)--玩家拥有宝石的大类总数 */
	{
		gemdata[gemdata_key[i]]["gemlevel"] = gems_level - (gems_level - gemdata[gemdata_key[i]]["gemlevel"]);
		// for(j=0;j<sizeof(gemdata[gemdata_key[i]]);j++)
		// {
		// if(strsrch(gemdata[gemdata_key[i]][name[j],gemdata[gemdata_key[i]]["gemlevel"][i],1)>0)
		// {

		// break;
		// }
		// }
		gemdisp[gemdata_key[i]] = sizeof(gemdata[gemdata_key[i]]) - 1;
		// printf("%s=%d",gemdata_key[i],gemdisp[gemdata_key[i]]);
	}

	gemdisp_idx = keys(gemdisp); /* 获取具体大类名称 */
	for (i = 1; i < sizeof(gemdata); i++)
	{
		for (j = 0; j < sizeof(gemdata) - i; j++)
		{
			if (gemdisp[gemdisp_idx[j]] < gemdisp[gemdisp_idx[j + 1]])
			{
				temp = gemdisp_idx[j];
				gemdisp_idx[j] = gemdisp_idx[j + 1];
				gemdisp_idx[j + 1] = temp;
			}
		}
	}

	column = sizeof(gemdata);

	msg = CYN"\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n" NOR;
	while (column > 0)
	{
		for (j = 0; j < gemdisp[gemdisp_idx[sizeof(gemdisp) - column]]; j++)
		{
			// printf("column=%d gem=%s\n",column,gemdisp_idx[sizeof(gemdisp)-column]);
			for (i = 0; i < column_no; i++)
			{
				mapa = ([]);
				if (i + column_no*n >= sizeof(gemdisp)) continue;
				mapa = gemdata[gemdisp_idx[i + column_no*n]];
				if (sizeof(mapa) - 2 < j)
				{
					//msg+=sprintf("%22s"," ");
					break;
				}
				else
				{
					gem_name = keys(mapa);
					gem_name -= ({ "gemlevel" });
					//printf("%d",sizeof(gem_name));
					for (m = 0; m < sizeof(gem_name); m++)
					{
						// printf("%s %s\n",gem_name[m],mapa["gemlevel"][j]);
						if (strsrch(gem_name[m], mapa["gemlevel"][j], 1) >= 0)
						{
							tabsize = 65;
							if (strwidth(replace_color(gem_name[m])) == 8) tabsize = 67;
							msg += sprintf("%-" + tabsize + "s", HIG"(" + sprintf("%2d", mapa[gem_name[m]]["index"]) + ")"NOR + gem_name[m] + "*"HIW + mapa[gem_name[m]]["number"] + NOR);
							// printf("%d ",strwidth(replace_color(gem_name[m])));
							break;
						}
					}
				}
			}
			msg += "\n";
		}
		n = n + 1;
		column = sizeof(gemdata) - column_no*n;
		if (column>0) msg += "\n";
	}

	msg += CYN"\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n"NOR;
	msg += "\n用" + HIY"pack <物品id>"NOR + "将宝石放入其中，用" + HIC"pickgem <序号>"NOR + "取出其中的某一宝石。\n"NOR;
	msg += "以你目前的级别，锦囊内共可存放"HIW + (me->query("level") * 4) + NOR"颗宝石，目前锦囊内有"HIW + me->query("baoshi_number") + NOR"颗宝石。\n";

	printf("%s", msg);

	return 1;


}

int do_pick(string arg)
{
	object  me, ob, *inv;
	int   i, index, amount;
	string files, slot, gem_type, yinyang;
	mapping diablo_ob, dbase, num;
	string *list, *prop, *gem, *gem2, *gem3;
	int gem_level;
	me = this_player();

	if (!arg) return notify_fail("你要取回哪样物品？\n");
	i = atoi(arg);
	if (!i) return notify_fail("你要取回哪样物品？\n");
	if (!mapp(diablo_ob = me->query("gembox_number")))
		return notify_fail("你的宝石袋里空空荡荡！\n");

	if (sizeof(all_inventory(me)) > 200)
		return notify_fail("笨阿，身上东西满了，小心无欢打劫你的宝石！\n");
	if (!mapp(num = me->query("gembox_number")))
		return notify_fail("你的宝石袋里空空荡荡！\n");

	if (sizeof(diablo_ob) != sizeof(num))
		return notify_fail(HIR "\n你的宝石袋遭劫了，请和巫师联系。\n" NOR);

	list = keys(diablo_ob);

	if (i < 1)
		return notify_fail("你的宝石袋里没有这件宝石！\n");
	if (sizeof(num) < i)
		return notify_fail("你的宝石袋里没有这件宝石！\n");
	slot = list[i - 1];
	//	files=diablo_ob[list[i-1]];

	gem = explode(slot, "☆");
	gem2 = explode(slot, "★");
	gem3 = explode(slot, "◎");
	if (sizeof(gem) != 2 && sizeof(gem2) != 2 && sizeof(gem3) != 2)
		return notify_fail("好像出错了，通知虫子吧。\n");
	if (sizeof(gem) == 2)
	{
		yinyang = "yin";
		switch (replace_color(gem[1]))
		{
		case "精金":gem_type = "jin"; break;
		case "玄冰":gem_type = "bing"; break;
		case "日魂":gem_type = "ri"; break;
		case "月魄":gem_type = "yue"; break;
		case "神龙骨":gem_type = "gu"; break;
		case "凤凰羽":gem_type = "yu"; break;
		case "麒麟角":gem_type = "jiao"; break;
		case "玄武甲":gem_type = "jia"; break;
		default:       gem_type = "bing"; break;
		}
		switch (replace_color(gem[0]))
		{
		case "地":gem_level = 1; break;
		case "山":gem_level = 2; break;
		case "水":gem_level = 3; break;
		case "风":gem_level = 4; break;
		case "雷":gem_level = 5; break;
		case "火":gem_level = 6; break;
		case "泽":gem_level = 7; break;
		case "天":gem_level = 8; break;
		default:      gem_level = 1; break;
		}
	}

	else if (sizeof(gem2) == 2)
	{
		yinyang = "yang";
		switch (replace_color(gem2[1]))
		{
		case "炎晶":gem_type = "yan"; break;
		case "木灵":gem_type = "mu"; break;
		case "日魂":gem_type = "ri"; break;
		case "月魄":gem_type = "yue"; break;
		case "神龙骨":gem_type = "gu"; break;
		case "凤凰羽":gem_type = "yu"; break;
		case "麒麟角":gem_type = "jiao"; break;
		case "玄武甲":gem_type = "jia"; break;
		default:       gem_type = "bing"; break;
		}
		switch (replace_color(gem2[0]))
		{
		case "地":gem_level = 1; break;
		case "山":gem_level = 2; break;
		case "水":gem_level = 3; break;
		case "风":gem_level = 4; break;
		case "雷":gem_level = 5; break;
		case "火":gem_level = 6; break;
		case "泽":gem_level = 7; break;
		case "天":gem_level = 8; break;
		default:    gem_level = 1; break;
		}
	}

	else
	{
		yinyang = "zhong";
		switch (replace_color(gem3[1]))
		{
		case "玉髓":gem_type = "sui"; break;
		case "神龙骨":gem_type = "gu"; break;
		case "凤凰羽":gem_type = "yu"; break;
		case "麒麟角":gem_type = "jiao"; break;
		case "玄武甲":gem_type = "jia"; break;
		default:       gem_type = "bing"; break;
		}
		switch (replace_color(gem3[0]))
		{
		case "地":gem_level = 1; break;
		case "山":gem_level = 2; break;
		case "水":gem_level = 3; break;
		case "风":gem_level = 4; break;
		case "雷":gem_level = 5; break;
		case "火":gem_level = 6; break;
		case "泽":gem_level = 7; break;
		case "天":gem_level = 8; break;
		default:    gem_level = 1; break;
		}
	}

	ob = F_GEMS->new_gem(gem_type, gem_level, yinyang);

	if (!ob)
		return notify_fail("取得宝石失败，请联系巫师。\n");
	if (!ob->move(me))
	{
		destruct(ob);
		write("你拿不动这么多宝石了。\n");
		return 1;
	}

	message_vision("$N从宝石袋里面取出一颗" + ob->name() + "。\n", me);
	me->add("gembox_number/" + slot, -1);
	me->add("baoshi_number", -1);
	if (me->query("baoshi_number") <= 0)
		me->delete("baoshi_number");
	if (!me->query("gembox_number/" + slot))
	{
		me->delete("gembox_number/" + slot);
		me->delete("gembox_slot/" + slot);
	}
	return 1;
}

int do_pack(string arg)
{
	object  me, ob;
	int amount;
	string files, slot;
	mapping num, ob_dbase;
	string *list;
	me = this_player();
	if (!arg) return notify_fail("你要把什么东西放进宝石袋？\n");
	if (!objectp(ob = present(arg, me)))
	{
		tell_object(me, "你要把什么东西放进宝石袋？\n");
		return 1;
	}
	if (!ob->is_gem())
	{
		tell_object(me, "这样东西不能放进宝石袋。\n");
		return 1;
	}
	if (ob->query("newgem") != 1)
	{
		tell_object(me, "这是哪个年代的化石啊？\n");
		return 1;
	}
	if (me->query("level") < 10)
	{
		tell_object(me, "往锦囊里存放宝石，至少需要10级。\n");
		return 1;
	}
	if (me->query("baoshi_number") >= me->query("level") * 4)
	{
		tell_object(me, "以你目前的级别，你放不了更多宝石。\n");
		return 1;
	}

	files = base_name(ob) + ".c";
	slot = ob->query("name");
	me->set("gembox_slot/" + slot, files);
	me->add("gembox_number/" + slot, 1);
	me->add("baoshi_number", 1);
	message_vision("$N将手中" + ob->query("name") + "放进了宝石袋。\n", me);
	ob->move("/obj/void");
	destruct(ob);
	return 1;
}

#define OLD_BLK ESC+"[0;30m"          /* Black    */
#define OLD_RED ESC+"[0;31m"          /* Red      */
#define OLD_GRN ESC+"[0;32m"          /* Green    */
#define OLD_YEL ESC+"[0;33m"          /* Yellow   */
#define OLD_BLU ESC+"[0;34m"          /* Blue     */
#define OLD_MAG ESC+"[0;35m"          /* Magenta  */
#define OLD_CYN ESC+"[0;36m"          /* Cyan     */
#define OLD_WHT ESC+"[0;37m"          /* White    */

int zhuicha(object me, string arg)
{
	object env, target;
	if (!me)
	{
		return 1;
	}
	if (!living(me))
	{
		return 1;
	}
	if (!environment(me))
	{
		return 1;
	}
	tell_object(me, HIW + "派出追查" + arg + "的人陆续回报：\n" + NOR);
	target = find_player(arg);
	if (!target)
	{
		target = find_living(arg);
		if (!target)
		{
			tell_object(me, arg + "极有可能已经不在人世了。\n");
			return 1;
		}
	}
	if (wizardp(target))
	{
		tell_object(me, "这个人行踪不定，没人能找到他。\n");
		return 1;
	}
	env = environment(target);
	if (!env)
	{
		tell_object(me, "这个人恐怕没人能找到。\n");
		return 1;
	}
	else
	{
		me->add("ming/zhuicha/times", 1);
		tell_object(me, target->name() + "现在躲在" + HBWHT + HIR + env->query("short") + NOR + "，那里的描述是：\n    " + env->query("long"));
		return 1;
	}
}
int do_zhuicha(string arg)
{
	object me = this_player();
	int period;
	if (!arg)
	{
		tell_object(me, "你要追查什么？\n");
		return 1;
	}
	if (me->query("non_daming_bonus_zhuicha") <= 0)
	{
		return 0;
	}
	if (arg == me->query("id"))
	{
		tell_object(me, "你要追查自己？\n");
		return 1;
	}
	me->add("non_daming_bonus_zhuicha", -1);
	message_vision(HIW"$N借助大明官方力量派出大量人手开始在各地追查" + arg + "的消息。\n"NOR, me);
	period = 5 + random(5);
	call_out("zhuicha", period, me, arg);
	return 1;
}

string replace_color(string arg)
{
	string str;
	str = arg;
	str = replace_string(str, BLK, "");
	str = replace_string(str, RED, "");
	str = replace_string(str, GRN, "");
	str = replace_string(str, YEL, "");
	str = replace_string(str, BLU, "");
	str = replace_string(str, MAG, "");
	str = replace_string(str, CYN, "");
	str = replace_string(str, WHT, "");

	str = replace_string(str, HIR, "");
	str = replace_string(str, HIG, "");
	str = replace_string(str, HIY, "");
	str = replace_string(str, HIB, "");
	str = replace_string(str, HIM, "");
	str = replace_string(str, HIC, "");
	str = replace_string(str, HIW, "");
	str = replace_string(str, NOR, "");
	str = replace_string(str, BNK, "");
	str = replace_string(str, REV, "");
	str = replace_string(str, U, "");

	str = replace_string(str, OLD_WHT, "");
	str = replace_string(str, OLD_RED, "");
	str = replace_string(str, OLD_GRN, "");
	str = replace_string(str, OLD_YEL, "");
	str = replace_string(str, OLD_BLU, "");
	str = replace_string(str, OLD_MAG, "");
	str = replace_string(str, OLD_CYN, "");

	return str;
}

int dest_gemlocker()
{
	object *ob = children("/clone/obj/gemlocker"), *ob2 = children("/d/city/obj/gemlocker");
	for (int i = 0; i < sizeof(ob); i++)
	{
		if (ob[i] == this_object()) continue;
		destruct(ob[i]);
	}
	for (int i = 0; i < sizeof(ob2); i++)
	{
		if (ob2[i] == this_object()) continue;
		destruct(ob2[i]);
	}
	return 1;
}

int restore_gemlocker()
{
	object *ob, *obs, gy;
	int i, j, flag;
	ob = filter_array(children(USER_OB), (: userp : ));
	ob = filter_array(ob, (: environment : ));
	for (i = 0; i < sizeof(ob); i++)
	{
		flag = 0;
		obs = all_inventory(ob[i]);
		for (j = 0; j < sizeof(obs); j++)
		{
			if (obs[j]->query("gem_locker"))
			{
				flag = 1;
			}
		}
		if (flag == 0)
		{
			gy = new("/clone/obj/gemlocker");
			gy->move(ob[i]);
		}
	}
	return 1;
}