// /featur/gems.c
// by Vast@pkuxkx
// all comments added by Vast

inherit F_SAVE;
#include <ansi.h>
#include <dbase.h>
#include <name.h>

#include "gems2.h"

string query_save_file()
{
string str;
str = PRIVATE_DIR + query("owner_id")[0..0] + "/" + query("owner_id") + "/" + query("owner_id") + query("savetime");
//write_file("/log/wiz/gems", str);
return str;
//        return PRIVATE_DIR + query("owner_id")[0..0] + "/" + query("owner_id") + "/" + query("owner_id") + query("savetime");
}

void set_owner(object me, int time)
{
	object ob = this_object();
	ob->set("owner_id", me->query("id"));
	ob->set("savetime", time);
}

int is_gems() {return 1;}// /clone/gem/gem.c里面是is_gem()
int yinyang = random(2);
int valid_gem(string gem, int level)
{
	if (gem != "yan"
	 && gem != "mu"
	 && gem != "sui"
	 && gem != "jin"
	 && gem != "bing"
	 && gem != "ri"
	 && gem != "yue"
	 && gem != "gu"
	 && gem != "yu"
	 && gem != "jiao"
	 && gem != "jia")
		return 0;
	if (level < 1 || level > 8)
		return 0;

	return 1;
}

string query_gem_name(string gemid, int level)
{
 if (gemid == "gu" || gemid == "yu" || gemid == "jiao" || gemid == "jia")
	return sprintf("%s%s%s%s"NOR, gems_color[gemid], gems_level[level - 1], gems_yinyang[yinyang], gems[gemid]);
 else return sprintf("%s%s%s"NOR, gems_color[gemid], gems_level[level - 1], gems[gemid]);
}

string query_gem_id(string gemid, int level)
{
	return sprintf("%s %s", gems_level_id[level - 1], gemid);
}

string query_all_yinyang(string gemid, object gem)
{
	  if (gemid == "yan" || gemid == "mu") return "yang";
		else if (gemid == "sui") return "zhong";
		else if (gemid == "bing" || gemid == "jin") return "yin";
		else
			{if (yinyang) return "yang";
			else return "yin";
			}
}

string query_all_effect(string gemid, object gem)
{
if (gemid == "yan")
	{
		string msg = "这是一颗"+gems_color[gemid]+gem->name()+NOR"，为地肺熔岩受南明离火所化，色赤红，温度极高。\n";
		return msg;
	}
else if (gemid == "mu")
	{
		string msg = "这是一个"+gems_color[gemid]+gem->name()+NOR"，相传东海有扶桑之树，上古神人所栖，每千年而有木灵生，色青，触之若无物。\n";
		return msg;
	}
else if (gemid == "sui")
	{
		string msg = "这是一粒"+gems_color[gemid]+gem->name()+NOR"，受中央戊己土气所钟而生，色黄，入手温润。\n";
		return msg;
	}
else if (gemid == "jin")
	{
		string msg = "这是一枚"+gems_color[gemid]+gem->name()+NOR"，由西方庚辛之气凝结而成，色银白，坚不可摧。\n";
		return msg;
	}
else if (gemid == "bing")
	{
		string msg = "这是一片"+gems_color[gemid]+gem->name()+NOR"，为极北万年冰山所孕，色玄青，寒气逼人。\n";
		return msg;
	}
else if (gemid == "gu")
	{
		string msg = "这是一条"+gems_color[gemid]+gem->name()+NOR"，光华流转，如有不可思议的神秘力量附于其上。\n";
		return msg;
	}
else if (gemid == "yu")
	{
		string msg = "这是一根"+gems_color[gemid]+gem->name()+NOR"，璀璨夺目，如有不可思议的神秘力量附于其上。\n";
		return msg;
	}
else if (gemid == "jiao")
	{
		string msg = "这是一只"+gems_color[gemid]+gem->name()+NOR"，光芒四射，如有不可思议的神秘力量附于其上。\n";
		return msg;
	}
else
	{
		string msg = "这是一块"+gems_color[gemid]+gem->name()+NOR"，光华内敛，如有不可思议的神秘力量附于其上。\n";
		return msg;
	}

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
			dam += jin_damage[level-1];//累加amethyst的加成damage
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
			+ sprintf("[%s] - %s", query_gem_name(socket, level), armor_effect[socket])
			+ "。\n";
			if(socket == "amethyst")
			def += jin_defence[level-1];//累加amethyst的加成damage
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

        //指环最多2个孔,也有可能没孔
        if (sockets > 2)
        {
                set("sockets/max", 2);
                sockets = 2;
        }

	if (sockets < 0) return "错误: 请通知巫师解决。\n";

	if (!query("ring/armor"))
	{
                armor = 10 + random(41);
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

        ob = new("/obj/gem/gem.c");
	if (!ob) return ob;

	if (!gem || gem == "")
		gem = ob->query("material");
	if (!lev || lev == 0)
		lev = ob->query("level");
	if (!valid_gem(gem, lev)) return ob;

	ob->set_name(query_gem_name(gem, lev), ({query_gem_id(gem, lev),"gem"}));
	ob->set("value", 2000 * lev * lev * lev);
	ob->set("material", gem);
	ob->set("level", lev);
        ob->set("long", query_all_effect(gem, ob));
	return ob;
}
