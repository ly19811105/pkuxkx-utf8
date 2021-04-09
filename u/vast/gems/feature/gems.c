// /featur/gems.c
// by Vast@pkuxkx
// all comments added by Vast

inherit F_SAVE;
#include <ansi.h>
#include <dbase.h>
#include <name.h>

#include "gems.h"

string query_save_file()
{
        return PRIVATE_DIR + query("owner_id")[0..0] + "/" + query("owner_id") + "/" + query("owner_id") + query("savetime");
}

void set_owner(object me, int time)
{
	object ob = this_object();
	ob->set("owner_id", me->query("id"));
	ob->set("savetime", time);
}

int is_gems() {return 1;}// /clone/gem/gem.c里面是is_gem()

int valid_gem(string gem, int level)
{
	if (gem != "ruby"
	 && gem != "topaz"
	 && gem != "sapphire"
	 && gem != "emerald"
	 && gem != "amethyst"
	 && gem != "diamond"
	 && gem != "skull")
		return 0;
	if (level < 1 || level > 8)
		return 0;

	return 1;
}

string query_gem_name(string gemid, int level)
{
	return sprintf("%s%s%s"NOR, gems_color[gemid], gems_level[level - 1], gems[gemid]);
}

string query_gem_id(string gemid, int level)
{
	return sprintf("%s %s", gems_level_id[level - 1], gemid);
}

string query_all_effect(string gemid, object gem)
{
	string msg = gems_color[gemid] + "这是一颗" + gem->name() + gems_color[gemid]+ "，上面似乎附着某种神奇的魔力：
可以镶嵌到物品上（指令格式：insert <宝石> into <物品>）
可以用三颗同样的宝石合并为更高等级的宝石（指令格式：combine <宝石>）\n"NOR;
	msg += sprintf("\t兵器 - %s\n", weapon_effect[gemid]);
	msg += sprintf("\t防具 - %s\n", armor_effect[gemid]);
	msg += sprintf("\t戒指 - %s\n", ring_effect[gemid]);
	return msg;
}

string set_weapon_desc(object ob)
{
	int i, level, hole, min_dam, max_dam, dam, att, str, sockets = ob->query("sockets/max");
	string socket, desc = "";

	//暂时最多三孔
        if (sockets > 3)
	{
        	set("sockets/max", 3);
        	sockets = 3;
	}

	if (sockets < 1) return "错误: 请通知巫师解决。\n";
	//init
	if (!query("weapon/damage"))//生成的时候确定
	{
		if (!(min_dam = ob->query("weapon/min_dam"))) min_dam = 1;
		if (!(max_dam = ob->query("weapon/max_dam"))) max_dam = min_dam + 10;
		dam = min_dam + random(max_dam - min_dam + 1);
		ob->set("weapon/damage", dam);
	}
	dam = ob->query("weapon/damage");
	att = ob->query("weapon/attack");
	str = ob->query("weapon/strength");

	if (sockets)
	desc = "上面总共有" + chinese_number(sockets) + "个凹槽";
	if (hole = ob->query("sockets/filled"))
	{
		desc += "，其中" + chinese_number(hole) + "个已经镶嵌了宝石。\n";
		for(i = 1; i <= hole; i++)
		{
			socket = query(sprintf("sockets/socket%d", i));
			level = query(sprintf("sockets/socket%d_level", i));
			if (valid_gem(socket, level))
			desc += "第" + chinese_number(i) + "个凹槽里面镶嵌着"
			+ sprintf("[%s] - %s", query_gem_name(socket, level), weapon_effect[socket])
			+ "。\n";
			if(socket == "amethyst")
			dam += amethyst_damage[level-1];//累加amethyst的加成damage
		}
	}
	else
	desc += "。\n";

	ob->set("weapon_prop/damage", dam);
	if (att) ob->set("weapon_prop/attack", att);
	if (str) ob->set("weapon_prop/strength", str);

	ob->set_weight(ob->query("base_weight") + ob->query("item/weight"));

	if (ob->query("item/value"))
	ob->set("value", ob->query("item/value") + dam * 1000);

	return desc;
}

string set_armor_desc(object ob)
{
	int i, level, hole, min_def, max_def, def, dodge, magic, avf, avw, heal, sockets = query("sockets/max");
	string socket, desc = "";

        //盔甲最多三孔
                if (sockets > 3)
        {
                set("sockets/max", 3);
                sockets = 3;
        }

	if (sockets < 1) return "错误: 请通知巫师解决。\n";

	if (!query("armor/defence"))//生成的时候确定
	{
		if (!(min_def = ob->query("armor/min_def"))) min_def = 1;
		if (!(max_def = ob->query("armor/max_def"))) max_def = min_def + 50;
		def = min_def + random(max_def - min_def + 1);
		ob->set("armor/defence", def);
	}
	def = ob->query("armor/defence");

	dodge = ob->query("armor/dodge");
	magic = ob->query("armor/magic");
	avf = ob->query("armor/armor_vs_force");
	avw = ob->query("armor/armor_vs_weapon");
	heal = ob->query("armor/healup");

	if (sockets)
	desc = "上面总共有" + chinese_number(sockets) + "个凹槽";
	if (hole = ob->query("sockets/filled"))
	{
		desc += "，其中" + chinese_number(hole) + "个已经镶嵌了宝石。\n";
		for(i = 1; i <= hole; i++)
		{
			socket = query(sprintf("sockets/socket%d", i));
			level = query(sprintf("sockets/socket%d_level", i));
			if (valid_gem(socket, level))
			desc += "第" + chinese_number(i) + "个凹槽里面镶嵌着"
			+ sprintf("[%s] - %s", query_gem_name(socket, level), ring_effect[socket])
			+ "。\n";
			if(socket == "amethyst")
			def += amethyst_defence[level-1];//累加amethyst的加成damage
		}
	}
	else
	desc += "。\n";

	ob->set("armor_prop/armor", def);

	if (dodge) ob->set("armor_prop/dodge", dodge);
	if (magic) ob->set("armor_prop/magic", magic);
	if (avf) ob->set("armor_prop/armor_vs_force", avf);
	if (avw) ob->set("armor_prop/armor_vs_weapon", avw);
	if (heal) ob->set("armor_prop/healup", heal);

	ob->set_weight(ob->query("base_weight") + ob->query("item/weight"));

	if (ob->query("item/value"))
	ob->set("value", ob->query("item/value") + def * 1000);

	return desc;
}

string set_ring_desc(object ob)
{
	int i, level, hole, armor, att, str, unarmed, strike, cuff, finger, hand, claw, dodge, parry, magic, sockets = query("sockets/max");
	string socket, desc = "也许这枚指环能卖不少钱吧";

	//指环最多一个孔,也有可能没孔
        if (sockets > 1)
        {
                set("sockets/max", 1);
                sockets = 1;
        }

	if (sockets < 0) return "错误: 请通知巫师解决。\n";

	if (!query("ring/armor"))
	{
		armor = 1 + random(10);
		ob->set("ring/armor", armor);
	}
	armor = ob->query("ring/armor");
	att = ob->query("ring/attack");
	str = ob->query("ring/strength");
	unarmed = ob->query("ring/unarmed");
	strike = ob->query("ring/strike");
	cuff = ob->query("ring/cuff");
	finger = ob->query("ring/finger");
	hand = ob->query("ring/hand");
	claw = ob->query("ring/claw");
	dodge = ob->query("ring/dodge");
	parry = ob->query("ring/parry");
	magic = ob->query("ring/magic");

	if (sockets)
	desc = "上面总共有" + chinese_number(sockets) + "个凹槽";
	if (hole = ob->query("sockets/filled"))
	{
		desc += "，其中" + chinese_number(hole) + "个已经镶嵌了宝石。\n";
		for(i = 1; i <= hole; i++)
		{
			socket = query(sprintf("sockets/socket%d", i));
			level = query(sprintf("sockets/socket%d_level", i));
			if (valid_gem(socket, level))
			desc += "第" + chinese_number(i) + "个凹槽里面镶嵌着"
			+ sprintf("[%s] - %s", query_gem_name(socket, level), ring_effect[socket])
			+ "。\n";
	}
	}
	else
	desc += "。\n";

	ob->set("armor_prop/armor", armor);
	if (att) ob->set("armor_prop/attack", att);
	if (str) ob->set("armor_prop/strength", str);
	if (unarmed) ob->set("armor_prop/unarmed", unarmed);
	if (strike) ob->set("armor_prop/strike", strike);
	if (cuff) ob->set("armor_prop/cuff", cuff);
	if (finger) ob->set("armor_prop/finger", finger);
	if (hand) ob->set("armor_prop/hand", hand);
	if (claw) ob->set("armor_prop/claw", claw);
	if (dodge) ob->set("armor_prop/dodge", dodge);
	if (parry) ob->set("armor_prop/parry", parry);
	if (magic) ob->set("armor_prop/magic", magic);

	ob->set_weight(ob->query("base_weight") + ob->query("item/weight"));

	if (ob->query("item/value"))
	ob->set("value", ob->query("item/value") + armor * 1000);

	return desc;
}

object new_gem(string gem, int lev)
{
	object ob;

	ob = new("/clone/gem/gem.c");
	if (!ob) return ob;

	if (!gem || gem == "")
		gem = ob->query("material");
	if (!lev || lev == 0)
		lev = ob->query("level");
	if (!valid_gem(gem, lev)) return ob;

	ob->set_name(query_gem_name(gem, lev), ({query_gem_id(gem, lev)}));
	ob->set("long", query_all_effect(gem, this_object()));
	ob->set("value", 2000 * lev * lev * lev);
	ob->set("material", gem);
	ob->set("level", lev);
	return ob;
}
