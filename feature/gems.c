// /featur/gems.c
// by Vast@pkuxkx
// all comments added by Vast
// upgraded by becool

inherit F_SAVE;
#include <ansi.h>
#include <dbase.h>
#include <name.h>

#include "gems.h"

void generate_newweapon(object ob, int bonus, int channel);
void generate_newarmor(object ob, int bonus, int channel);
void generate_newring(object ob, int bonus, int channel);

string query_save_file()
{
  string str;

  if ( stringp(query("owner_id")) )
    str = PRIVATE_DIR + query("owner_id")[0..0] + "/" + query("owner_id") + "/" + query("owner_id") + query("savetime");
  else
    return 0;
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
int yinyangid;
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
yinyangid = random(2);
 if (gemid == "gu" || gemid == "yu" || gemid == "jiao" || gemid == "jia")
	return sprintf("%s%s%s%s"NOR, gems_color[gemid], gems_level[level - 1], gems_yinyang[yinyangid], gems[gemid]);
 else return sprintf("%s%s%s"NOR, gems_color[gemid], gems_level[level - 1], gems[gemid]);
}

string query_gem_name2(string gemid, int level, string yinyang)
{
  if (yinyang == "yin" ) 
  	yinyangid = 0;
  else if (yinyang == "zhong" ) 
  	yinyangid = 2;
  else 
  	yinyangid = 1;
  
  if (gemid == "gu" || gemid == "yu" || gemid == "jiao" || gemid == "jia")
	  return sprintf("%s%s%s%s"NOR, gems_color[gemid], gems_level[level - 1], gems_yinyang[yinyangid], gems[gemid]);
  else 
  	return sprintf("%s%s%s"NOR, gems_color[gemid], gems_level[level - 1], gems[gemid]);
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
		else if (gemid == "ri") return "yang";
		else if (gemid == "yue") return "yin";
		else
		{
			if (yinyangid==1) 
				return "yang";
			if (yinyangid==2)
				return "zhong";
			else 
				return "yin";
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
else if (gemid == "jia")
	{
		string msg = "这是一块"+gems_color[gemid]+gem->name()+NOR"，光华内敛，如有不可思议的神秘力量附于其上。\n";
		return msg;
	}
else if (gemid == "ri")
	{
		string msg = "这是一块"+gems_color[gemid]+gem->name()+NOR"，由太阳真火凝聚而成，乌金色，能破邪怯魔，千军辟易。\n";
		return msg;
	}
else
	{
		string msg = "这是一块"+gems_color[gemid]+gem->name()+NOR"，由太阴真火凝聚而成，月白色，能摄心定神，百邪不侵。\n";
		return msg;
	}
}

string set_weapon_desc(object ob)
{
	int i, level, capacity, capacity_max = ob->query("forge/max");
	string material, desc = "";
  if (capacity_max > 4)
	{
        	set("forge/max", 4);
        	capacity_max = 4;
	}

	if (capacity_max < 1) return "错误: 请通知巫师解决。\n";

	if (capacity_max>1)
	desc = "看起来成色相当不错";
	else desc = "成色一般";
	if (capacity = ob->query("forge/capacity"))
	{
		desc += "，从光泽来看，至少已经和" + chinese_number(capacity) + "种特殊材料熔化重铸过。\n";
		for(i = 1; i <= capacity; i++)
		{
			material = ob->query(sprintf("forge/material%d", i));
			level = ob->query(sprintf("forge/material%d_level", i));
			if (valid_gem(material, level))
			{
			if (capacity == 1)
			desc += "这种材料是"
			+ sprintf("[%s] - %s", query_gem_name(material, level), weapon_effect[material])
			+ "。\n";
			else
			desc += "第" + chinese_number(i) + "种材料是"
			+ sprintf("[%s] - %s", query_gem_name(material, level), weapon_effect[material])
			+ "。\n";
		  }
		}
	}
	else
	desc += "。\n";
return desc;
}

string set_armor_desc(object ob)
{
	int i, level, capacity, capacity_max = query("forge/max");
	string material, desc = "", yinyang;

        //盔甲最多4孔
                if (capacity_max > 4)
        {
                set("forge/max", 4);
                capacity_max = 4;
        }

	if (capacity_max < 1) return "错误: 请通知巫师解决。\n";


	if (capacity_max>2)
	desc = "看起来成色相当不错";
	else desc = "成色一般";
	if (capacity = ob->query("forge/capacity"))
	{
		desc += "，从光泽来看，至少已经和" + chinese_number(capacity) + "种特殊材料熔化重铸过。\n";
		for(i = 1; i <= capacity; i++)
		{
			material = ob->query(sprintf("forge/material%d", i));
			level = ob->query(sprintf("forge/material%d_level", i));
			yinyang = ob->query(sprintf("forge/material%d_yinyang", i));
			if (valid_gem(material, level))
			{
			  if (capacity == 1)
			  {
			  	if ( !yinyang ) 
			      desc += "这种材料是"
			           + sprintf("[%s] - %s", query_gem_name(material, level), armor_effect[material])
			           + "。\n";
			    else
			      desc += "这种材料是"
			           + sprintf("[%s] - %s", query_gem_name2(material, level,yinyang), armor_effect[material])
			           + "。\n";
			  }
			  else
			  {
			  	if ( !yinyang ) 
			      desc += "第" + chinese_number(i) + "种材料是"
			           + sprintf("[%s] - %s", query_gem_name(material, level), armor_effect[material])
			           + "。\n";
			    else
			      desc += "第" + chinese_number(i) + "种材料是"
			           + sprintf("[%s] - %s", query_gem_name2(material, level,yinyang), armor_effect[material])
			           + "。\n";
			  }
		  }
		}
	}
	else
	desc += "。\n";

	return desc;
}

string set_ring_desc(object ob)
{
	int i, level, capacity, capacity_max = query("forge/max");
	string material, desc = "也许这枚指环能卖不少钱吧", yinyang;

        //指环最多2个孔,也有可能没孔
        if (capacity_max > 2)
        {
                set("capacity_max/max", 2);
                capacity_max = 2;
        }

	if (capacity_max < 0) return "错误: 请通知巫师解决。\n";

	if (capacity_max>1)
	desc = "看起来成色相当不错";
	else desc = "成色一般";
	if (capacity = ob->query("forge/capacity"))
	{
		desc += "，从光泽来看，至少已经和" + chinese_number(capacity) + "种特殊材料熔化重铸过。\n";
		for(i = 1; i <= capacity; i++)
		{
			material = ob->query(sprintf("forge/material%d", i));
			level = ob->query(sprintf("forge/material%d_level", i));
			yinyang = ob->query(sprintf("forge/material%d_yinyang", i));
			if (valid_gem(material, level))
			{
			  if (capacity == 1)
			  {
			  	if ( !yinyang )
			      desc += "这种材料是"
			           + sprintf("[%s] - %s", query_gem_name(material, level), ring_effect[material])
			           + "。\n";
			    else
			      desc += "这种材料是"
			           + sprintf("[%s] - %s", query_gem_name2(material, level, yinyang), ring_effect[material])
			           + "。\n";
			  }
			  else
			  {
			  	if ( !yinyang )
			      desc += "第" + chinese_number(i) + "种材料是"
			           + sprintf("[%s] - %s", query_gem_name(material, level), ring_effect[material])
			           + "。\n";
			    else
			      desc += "第" + chinese_number(i) + "种材料是"
			           + sprintf("[%s] - %s", query_gem_name2(material, level, yinyang), ring_effect[material])
			           + "。\n";
			  }
		  }
		}
	}
	else
	desc += "。\n";

	return desc;
}

object new_gem(string gem, int lev, string yinyang)
{
	object ob;

        ob = new("/obj/gem/gem.c");
	if (!ob) return ob;
	if (!gem || gem == "")
		gem = ob->query("material");
	if (!lev || lev == 0)
		lev = ob->query("level");
	if (!valid_gem(gem, lev)) return ob;
  if (!yinyang || yinyang =="")
	ob->set_name(query_gem_name(gem, lev), ({query_gem_id(gem, lev),"gem"}));
	else ob->set_name(query_gem_name2(gem, lev, yinyang), ({query_gem_id(gem, lev),"gem"}));
	ob->set("long", query_all_effect(gem, ob)); 
  ob->set("yinyang", query_all_yinyang(gem, ob));
	ob->set("value", 2000 * lev * lev * lev);
	ob->set("material", gem);
	ob->set("level", lev);
    ob->set("base_weight", 100 * lev);
    ob->set_weight( 100 * lev );
  if (gem == "yan" || gem == "mu" || gem == "sui" || gem == "jin" || gem == "bing")
  ob->set("type", "wuxing");
  else if (gem == "gu" || gem == "yu" || gem == "jiao" || gem == "jia")
  ob->set("type", "siling");
  else
  ob->set("type", "riyue");
	return ob;
}

//分不同类的物品，对锻造过的物品进行属性更新。
void generate_newitem(object ob, int bonus, int channel)
{
	if(ob->query("weapon_prop"))
	generate_newweapon(ob, bonus, channel);
	else if(ob->query("armor_type") != "finger" && ob->query("armor_type") != "neck" )
	generate_newarmor(ob, bonus, channel);
	else
	generate_newring(ob, bonus, channel);
}

void generate_newweapon(object ob, int bonus, int channel)
{
	string prefix, material;
	int dam, str, att, jing, poison, rigidity, suck, lev, level, i, capacity = ob->query("forge/capacity");
	if (channel == 2)
		bonus = ob->query("forge/bonus");
	dam = ob->query("weapon/damage");
// 有些装备可能没有 "weapon/damage" 这个属性，则获取 "weapon_prop/damage" 属性。 by lordstar 20171116
	if (dam<=0)
		dam = ob->query("weapon_prop/damage");
	str = ob->query("weapon/strength");
	att = ob->query("weapon/attack");
	jing = ob->query("weapon/weapon_effect_jing");
	poison = ob->query("weapon/weapon_effect_poison");
	rigidity = ob->query("rigidity");
	suck = ob->query("weapon/weapon_effect_suck");
	if(stringp(ob->query("weapon/name")))
	prefix = ob->query("weapon/name");
	else if (!stringp(ob->query("forge/times")))
	 prefix = " " + ob->query("name");
  else prefix = ob->query("name");
  for (i=1; i<capacity+1; i++)
  {
	  material = ob->query(sprintf("forge/material%d",i));
	  lev = ob->query(sprintf("forge/material%d_level",i));
	  if (valid_gem(material, lev))
	  switch (material)
	  {
		case "yan":
		//1.前缀(未判断重名前缀的情况，可以加上)
		      prefix = HIR + yan_prefix[random(sizeof(yan_prefix))] + NOR + prefix;
		      str = str + yan_weapon_effect[lev - 1]*(bonus+100)/100;
		//改变wield,unwield描述，以最后一次镶嵌的宝石为标准
        	ob->set("wield_msg", HIR + yan_wield_msg[random(sizeof(yan_wield_msg))] + NOR);
        	ob->set("unwield_msg", HIR + yan_unwield_msg[random(sizeof(yan_unwield_msg))] + NOR);
    //特效
        	ob->set("weapon_prop/strength", str);
        	if (channel != 2)
        	  ob->add("gem_prop/strength", yan_weapon_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		break;
		case "sui":
		      prefix = HIY + sui_prefix[random(sizeof(sui_prefix))] + NOR + prefix;
		      att = att + sui_weapon_effect[lev - 1]*(bonus+100)/100;
        	ob->set("wield_msg", HIY + sui_wield_msg[random(sizeof(sui_wield_msg))] + NOR);
        	ob->set("unwield_msg", HIY + sui_unwield_msg[random(sizeof(sui_unwield_msg))] + NOR);
        	ob->set("weapon_prop/attack", att);
        	if (channel != 2)
        	  ob->add("gem_prop/attack", sui_weapon_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		break;
		case "yue":
		      prefix = HIM + yue_prefix[random(sizeof(yue_prefix))] + NOR + prefix;
		      jing = jing + yue_weapon_effect[lev - 1]*(bonus+100)/100;
        	ob->set("wield_msg", HIM + yue_wield_msg[random(sizeof(yue_wield_msg))] + NOR);
        	ob->set("unwield_msg", HIM + yue_unwield_msg[random(sizeof(yue_unwield_msg))] + NOR);
        	ob->set("weapon_prop/weapon_effect_jing", jing);
        	if (channel != 2)
        	  ob->add("gem_prop/weapon_effect_jing", yue_weapon_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		break;
		case "bing":
		      prefix = HIB + bing_prefix[random(sizeof(bing_prefix))] + NOR + prefix;
		      poison = poison + bing_weapon_effect[lev - 1]*(bonus+100)/100;
        	ob->set("wield_msg", HIB + bing_wield_msg[random(sizeof(bing_wield_msg))] + NOR);
        	ob->set("unwield_msg", HIB + bing_unwield_msg[random(sizeof(bing_unwield_msg))] + NOR);
        	ob->set("weapon_prop/weapon_effect_poison", poison);
        	if (channel != 2)
        	  ob->add("gem_prop/weapon_effect_poison", bing_weapon_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		break;
		case "jin":
		      prefix = HIW + jin_prefix[random(sizeof(jin_prefix))] + NOR + prefix;
		      dam = dam + jin_damage[lev - 1]*(bonus+100)/100;
       		ob->set("wield_msg", HIW + jin_wield_msg[random(sizeof(jin_wield_msg))] + NOR);
       		ob->set("unwield_msg", HIW + jin_unwield_msg[random(sizeof(jin_unwield_msg))] + NOR);
       		ob->set("weapon_prop/damage", dam);
       		if (channel != 2)
       		  ob->add("gem_prop/damage", jin_damage[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
       		break;
		case "mu":
		      prefix = HIG + mu_prefix[random(sizeof(mu_prefix))] + NOR + prefix;
		      rigidity = rigidity + mu_weapon_effect[lev - 1]*(bonus+100)/100;
       		ob->set("wield_msg", HIG + mu_wield_msg[random(sizeof(mu_wield_msg))] + NOR);
       		ob->set("unwield_msg", HIG + mu_unwield_msg[random(sizeof(mu_unwield_msg))] + NOR);
       		ob->set("rigidity", rigidity);
       		ob->set("max_rigidity", rigidity);
       		if (channel != 2)
       		  ob->add("gem_prop/rigidity", mu_weapon_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
   	break;
		case "ri":
		      prefix = HIC + ri_prefix[random(sizeof(ri_prefix))] + NOR + prefix;
		      suck = suck + ri_weapon_effect[lev - 1]*(bonus+100)/100;
        	ob->set("wield_msg", HIC + ri_wield_msg[random(sizeof(ri_wield_msg))] + NOR);
        	ob->set("unwield_msg", HIC + ri_unwield_msg[random(sizeof(ri_unwield_msg))] + NOR);
        	ob->set("weapon_prop/weapon_effect_suck", suck);
        	if (channel != 2)
        	  ob->add("gem_prop/weapon_effect_suck", ri_weapon_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		break;
		default:
		error("gems: undefined type " + material + ".\n");
	  }
	}
	if (ob->query("is_forging"))
	{
	ob->set("weapon/name", prefix);
	ob->set("name", prefix);
  ob->delete("is_forging");
  }
	ob->forge_capacity();
	ob->set_weight(ob->query("base_weight") + ob->query("item/weight"));
}

void generate_newring(object ob, int bonus, int channel)
{
	string prefix, material,type,yinyang;
	int str, att, prop_unarmed, prop_hand, prop_finger, prop_strike, prop_cuff, prop_claw;
	int dodge, armor, parry, magic, lev, level, i, capacity = ob->query("forge/capacity");
	int mqi, mjing, qir, jingr, qic, jingc, neilir, jinglir;
	if (channel == 2)
		bonus = ob->query("forge/bonus");
	str = ob->query("armor/strength");
	att = ob->query("armor/attack");
	prop_unarmed = ob->query("armor/unarmed");
	prop_hand = ob->query("armor/hand");
	prop_finger = ob->query("armor/finger");
	prop_strike = ob->query("armor/strike");
	prop_cuff = ob->query("armor/cuff");
	prop_claw = ob->query("armor/claw");
	dodge = ob->query("armor/dodge");
	armor = ob->query("armor/armor");
	parry = ob->query("armor/kf_def_wound");
	magic = ob->query("armor/magic");
	mqi = ob->query("armor/max_qi");
	mjing = ob->query("armor/max_jing");
	qir = ob->query("armor/qi_recover");
	jingr = ob->query("armor/jing_recover");
	qic = ob->query("armor/qi_cure");
	jingc = ob->query("armor/jing_cure");
	neilir = ob->query("armor/neili_recover");
	jinglir = ob->query("armor/jingli_recover");
	if (ob->query("armor/armor")>53)
		ob->set("armor/armor",30);
	if(stringp(ob->query("ring/name")))
	prefix = ob->query("ring/name");
	else if (!stringp(ob->query("forge/times")))
	 prefix = " " + ob->query("name");
	else prefix = ob->query("name");
  for (i=1; i<capacity+1; i++)
  {
	  material = ob->query(sprintf("forge/material%d",i));
	  lev = ob->query(sprintf("forge/material%d_level",i));
	  type = ob->query(sprintf("forge/material%d_type",i));
	  yinyang = ob->query(sprintf("forge/material%d_yinyang",i));
	  if ( type=="siling" && yinyang!="zhong" )   //暂时不支持非中性的四灵宝石镶嵌
	  	continue;
	  if (valid_gem(material, lev))
	  switch (material)
	  {
		  case "yan":
		//1.前缀(未判断重名前缀的情况，可以加上)
		      prefix = HIR + yan_prefix[random(sizeof(yan_prefix))] + NOR + prefix;
		      str = str + yan_ring_effect[lev - 1]*(bonus+100)/100;
		//2.特效
        	ob->set("armor_prop/strength", str);
        	if (channel != 2)
        	  ob->add("gem_prop/strength", yan_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "sui":
		      prefix = HIY + sui_prefix[random(sizeof(sui_prefix))] + NOR + prefix;
		      att = att +sui_ring_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/attack", att);
        	if (channel != 2)
		        ob->add("gem_prop/attack", sui_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "yue":
		      prefix = HIM + yue_prefix[random(sizeof(yue_prefix))] + NOR + prefix;
		      prop_unarmed = prop_unarmed + yue_ring_effect[lev - 1]*(bonus+100)/100;
		      prop_hand = prop_hand + yue_ring_effect[lev - 1]*(bonus+100)/100;
		      prop_finger = prop_finger + yue_ring_effect[lev - 1]*(bonus+100)/100;
		      prop_strike = prop_strike + yue_ring_effect[lev - 1]*(bonus+100)/100;
		      prop_cuff = prop_cuff + yue_ring_effect[lev - 1]*(bonus+100)/100;
		      prop_claw = prop_claw + yue_ring_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/unarmed", prop_unarmed);
        	ob->set("armor_prop/hand", prop_hand);
        	ob->set("armor_prop/finger", prop_finger);
        	ob->set("armor_prop/strike", prop_strike);
        	ob->set("armor_prop/cuff", prop_cuff);
        	ob->set("armor_prop/claw", prop_claw);
        	if (channel != 2)
        	{
		        ob->add("gem_prop/unarmed", yue_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		        ob->add("gem_prop/hand", yue_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		        ob->add("gem_prop/finger", yue_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		        ob->add("gem_prop/strike", yue_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		        ob->add("gem_prop/cuff", yue_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		        ob->add("gem_prop/claw", yue_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      }
		      break;
		  case "bing":
		      prefix = HIB + bing_prefix[random(sizeof(bing_prefix))] + NOR + prefix;
		      dodge = dodge + bing_ring_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/dodge", dodge);
        	if (channel != 2)
        	  ob->add("gem_prop/dodge", bing_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "jin":
		      prefix = HIW + jin_prefix[random(sizeof(jin_prefix))] + NOR + prefix;
		      armor = armor + jin_ring_effect[lev - 1]*(bonus+100)/100;
       		ob->set("armor_prop/armor", armor);
       		if (channel != 2)
            ob->add("gem_prop/armor", jin_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
          break;
		  case "mu":
		      prefix = HIG + mu_prefix[random(sizeof(mu_prefix))] + NOR + prefix;
		      parry = parry + mu_ring_effect[lev - 1]*(bonus+100)/100;
       		if ( parry>20 )
       			parry=20;
       		ob->set("armor_prop/kf_def_wound", parry);
       		if (channel != 2)
            ob->add("gem_prop/kf_def_wound", mu_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
          break;
		  case "ri":
		      prefix = HIC + ri_prefix[random(sizeof(ri_prefix))] + NOR + prefix;
		      magic = magic + ri_ring_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/magic", magic);
        	if (channel != 2)
		        ob->add("gem_prop/magic", ri_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "gu":
		      prefix = CYN + gu_prefix[random(sizeof(gu_prefix))] + NOR + prefix;
		      mqi = mqi + gu_ring_effect[lev - 1]*(bonus+100)/100;
		      mjing = mjing + gu_ring_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/max_qi", mqi);
        	ob->set("armor_prop/max_jing", mjing);
        	if (channel != 2)
        	{
		        ob->add("gem_prop/max_qi", gu_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		        ob->add("gem_prop/max_jing", gu_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      }
		      break;
		  case "yu":
		      prefix = WHT + yu_prefix[random(sizeof(yu_prefix))] + NOR + prefix;
		      qir = qir + yu_ring_effect[lev - 1]*(bonus+100)/100;
		      jingr = jingr + yu_ring_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/qi_recover", qir);
        	ob->set("armor_prop/jing_recover", jingr);
        	if (channel != 2)
        	{
        	  ob->add("gem_prop/qi_recover", yu_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	  ob->add("gem_prop/jing_recover", yu_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	}
		      break;
		  case "jiao":
		      prefix = RED + jiao_prefix[random(sizeof(jiao_prefix))] + NOR + prefix;
		      qic = qic + jiao_ring_effect[lev - 1]*(bonus+100)/100;
		      jingc = jingc + jiao_ring_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/qi_cure", qic);
        	ob->set("armor_prop/jing_cure", jingc);
        	if (channel != 2)
        	{
		        ob->add("gem_prop/qi_cure", jiao_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		        ob->add("gem_prop/jing_cure", jiao_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      }
		      break;
		  case "jia":
		      prefix = YEL + jia_prefix[random(sizeof(jia_prefix))] + NOR + prefix;
		      neilir = neilir + jia_ring_effect[lev - 1]*(bonus+100)/100;
		      jinglir = jinglir + jia_ring_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/neili_recover", neilir);
        	ob->set("armor_prop/jingli_recover", jinglir);
        	if (channel != 2)
        	{
		        ob->add("gem_prop/neili_recover", jia_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		        ob->add("gem_prop/jingli_recover", jia_ring_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      }
		      break;
		  default:
		      error("gems: undefined type " + material + ".\n");
	}
  }
	if (ob->query("is_forging"))
	{
	ob->set("ring/name", prefix);
	ob->set("name", prefix);
  ob->delete("is_forging");
  }
	ob->setup_armor();
	ob->set_weight(ob->query("base_weight") + ob->query("item/weight"));
}

void generate_newarmor(object ob, int bonus, int channel)
{
	string prefix, material,type,yinyang;
	int rebound, dodge, magic, poison, armor, vs_force, healup, lev, level, i, capacity = ob->query("forge/capacity");
	int mqi, mjing, qir, jingr, qic, jingc, neilir, jinglir;
	if (channel == 2)
		bonus = ob->query("forge/bonus");
	rebound = ob->query("armor/rebound");
	dodge = ob->query("armor/dodge");
	magic = ob->query("armor/magic");
	poison = ob->query("armor/poison");
	armor = ob->query("armor/armor");
	vs_force = ob->query("armor/week_injure");
	healup = ob->query("armor/healup");
	mqi = ob->query("armor/max_qi");
	mjing = ob->query("armor/max_jing");
	qir = ob->query("armor/qi_recover");
	jingr = ob->query("armor/jing_recover");
	qic = ob->query("armor/qi_cure");
	jingc = ob->query("armor/jing_cure");
	neilir = ob->query("armor/neili_recover");
	jinglir = ob->query("armor/jingli_recover");
	if (ob->query("type") == 1 && ob->query("armor/armor")>569)
		ob->set("armor/armor",500);
	if (ob->query("type") != 1 && ob->query("type") != 6 && ob->query("armor/armor")>129)
		ob->set("armor/armor",70);
	if(stringp(ob->query("armor/name")))
	prefix = ob->query("armor/name");
	else if (!stringp(ob->query("forge/times")))
	 prefix = " " + ob->query("name");
	else prefix = ob->query("name");
  for (i=1; i<capacity+1; i++)
  {
	  material = ob->query(sprintf("forge/material%d",i));
	  lev = ob->query(sprintf("forge/material%d_level",i));
	  type = ob->query(sprintf("forge/material%d_type",i));
	  yinyang = ob->query(sprintf("forge/material%d_yinyang",i));
	  if ( type=="siling" && yinyang!="zhong" )   //暂时不支持非中性的四灵宝石镶嵌
	  	continue;
	  if (valid_gem(material, lev))
	  switch (material)
	  {
		  case "yan":
		      prefix = HIR + yan_prefix[random(sizeof(yan_prefix))] + NOR + prefix;
          rebound = rebound + yan_armor_effect[lev - 1]*(bonus+100)/100;
        	if ( rebound > 80 )
        		rebound=80;
        	ob->set("armor_prop/armor_effect_rebound", rebound);
        	if (channel != 2)
        	  ob->add("gem_prop/armor_effect_rebound", yan_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "sui":
		      prefix = HIY + sui_prefix[random(sizeof(sui_prefix))] + NOR + prefix;
		      dodge = dodge + sui_armor_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/dodge", dodge);
        	if (channel != 2)
		        ob->add("gem_prop/dodge", sui_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "yue":
		      prefix = HIM + yue_prefix[random(sizeof(yue_prefix))] + NOR + prefix;
		      magic = magic + yue_armor_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/magic", magic);
        	if (channel != 2)
		        ob->add("gem_prop/magic", yue_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "bing":
		      prefix = HIB + bing_prefix[random(sizeof(bing_prefix))] + NOR + prefix;
		      poison = poison + bing_armor_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/armor_effect_poison", poison);
        	if (channel != 2)
		        ob->add("gem_prop/armor_effect_poison", bing_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "jin":
		      prefix = HIW + jin_prefix[random(sizeof(jin_prefix))] + NOR + prefix;
		      armor = armor + jin_defence[lev - 1]*(bonus+100)/100;
       		ob->set("armor_prop/armor", armor);
       		if (channel != 2)
       		  ob->add("gem_prop/armor", jin_defence[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
       		break;
		  case "mu":
		      prefix = HIG + mu_prefix[random(sizeof(mu_prefix))] + NOR + prefix;
		      vs_force = vs_force + mu_armor_effect[lev - 1]*(bonus+100)/100;
       		if ( vs_force>20 )
       			vs_force=20;
       		ob->set("armor_prop/week_injure", vs_force);
       		if (channel != 2)
       		  ob->add("gem_prop/week_injure", mu_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
       		break;
		  case "ri":
		      prefix = HIC + ri_prefix[random(sizeof(ri_prefix))] + NOR + prefix;
		      healup = healup + ri_armor_effect[lev - 1]*(bonus+100)/100;
        	if ( healup > 80 )
        		healup=80;
        	ob->set("armor_prop/armor_effect_healup", healup);
        	if (channel != 2)
		        ob->add("gem_prop/armor_effect_healup", ri_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
		      break;
		  case "gu":
		      prefix = CYN + gu_prefix[random(sizeof(gu_prefix))] + NOR + prefix;
		      mqi = mqi + gu_armor_effect[lev - 1]*(bonus+100)/100;
		      mjing = mjing + gu_armor_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/max_qi", mqi);
        	ob->set("armor_prop/max_jing", mjing);
        	if (channel != 2)
        	{
        	  ob->add("gem_prop/max_qi", gu_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	  ob->add("gem_prop/max_jing", gu_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	}
		      break;
		  case "yu":
		      prefix = WHT + yu_prefix[random(sizeof(yu_prefix))] + NOR + prefix;
		      qir = qir + yu_armor_effect[lev - 1]*(bonus+100)/100;
		      jingr = jingr + yu_armor_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/qi_recover", qir);
        	ob->set("armor_prop/jing_recover", jingr);
        	if (channel != 2)
        	{
        	  ob->add("gem_prop/qi_recover", yu_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	  ob->add("gem_prop/jing_recover", yu_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	}
		      break;
		  case "jiao":
		      prefix = RED + jiao_prefix[random(sizeof(jiao_prefix))] + NOR + prefix;
		      qic = qic + jiao_armor_effect[lev - 1]*(bonus+100)/100;
		      jingc = jingc + jiao_armor_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/qi_cure", qic);
        	ob->set("armor_prop/jing_cure", jingc);
        	if (channel != 2)
        	{
        	  ob->add("gem_prop/qi_cure", jiao_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	  ob->add("gem_prop/jing_cure", jiao_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	}
		      break;
		  case "jia":
		      prefix = YEL + jia_prefix[random(sizeof(jia_prefix))] + NOR + prefix;
		      neilir = neilir + jia_armor_effect[lev - 1]*(bonus+100)/100;
		      jinglir = jinglir + jia_armor_effect[lev - 1]*(bonus+100)/100;
        	ob->set("armor_prop/neili_recover", neilir);
        	ob->set("armor_prop/jingli_recover", jinglir);
        	if (channel != 2)
        	{
        	  ob->add("gem_prop/neili_recover", jia_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	  ob->add("gem_prop/jingli_recover", jia_armor_effect[lev - 1]*(bonus+100)/100);        //宝石提供的装备提升
        	}
		      break;
		  default:
		      error("gems: undefined type " + material + ".\n");
	  }
  }
	if (ob->query("is_forging"))
	{
	ob->set("armor/name", prefix);
	ob->set("name", prefix);
  ob->delete("is_forging");
  }
	ob->setup_armor();
	ob->set_weight(ob->query("base_weight") + ob->query("item/weight"));
}
