// 无常造化丹的原料
#include <ansi.h>
inherit ITEM;
int try_give(string arg);

void create()
{
	string* color = ({ HIR, RED, HIY, YEL, HIB, BLU, HIG, HIC, CYN, MAG, HIM, HIW, WHT });
	string* uname = ({"人参", "茯苓", "灵芝", "鹿茸", "首乌", "灵脂", "熊胆", "三七", "麝香", });
	string* uid = ({"renshen", "fuling", "lingzhi", "lurong", "shouwu", "lingzhi", "xiongdan", "sanqi", "shexiang", });
	string* umade = ({"醋制", "盐制", "酒制", "蜜制", "姜制", });
	string* mid = ({"cuzhi", "yanzhi", "jiuzhi", "mizhi", "jiangzhi", });
	int i, j, k;
	i = random(sizeof(umade));
	j = random(sizeof(uname));
	k = random(sizeof(color));
	set_name( color[k] + umade[i] + uname[j] + NOR, ({ mid[i]+" "+uid[j], uid[j], "yao cai", "material" }) );

	set_weight(5);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "剂");
		set("long", "这是一剂极其珍贵的药材，但是药效时间有限。如不尽快使用，很快就会失效。\n");
		set("value", 10000);
		set("material", "grass");
		set("no_give",1);
		set("no_drop",1);
		set("no_get",1);
		set("no_store",1);
		set("no_pawn",1);
		set("wuchang_material", 1);
	}
	setup();
}

void init()
{
	object me, ob;
	ob = this_object();
	me = this_player();
	
	add_action("try_give", "give");
	
    if (userp(me) && environment() == me && !ob->query("call_lost_efficacy"))
	{
		ob->set("call_lost_efficacy", 1);
		call_out("lost_efficacy", 3600);
	}
	return;
}

void lost_efficacy()
{
	object ob = this_object();
	if (!ob || !objectp(ob)) return;
	write(ob->query("name") + "渐渐失去了药效，化为一堆飞灰飘散了……\n");
	destruct(ob);
}

int try_give(string arg)
{
	object ob, me, who;
	string item, target;
	int money;
	me = this_player();
	if (!arg) return 0;
	if (sscanf(arg, "%s to %s", item, target)!=2 && sscanf(arg, "%s %s", target, item)!=2) return 0;
	if (!objectp(ob = present(item, me)) || ob != this_object() || ob->query("owner") != me->query("id")) return 0;
	if (!objectp(who = present(target, environment(me))) || !living(who)) return 0;
	if (!who->query("wuchangzaohua_maker")) return 0;
	if (who->is_fighting())
	{
		tell_object(me, who->name()+"现在恐怕腾不出手来接收你的物品。\n");
		return 1;
	}	
	if (who->is_busy())
	{
		tell_object(me, who->name()+"正忙着呢，晚点再给他吧。\n");
		return 1;
	}
	ob->move(who);
	printf("你从怀里小心翼翼地拿出一%s%s递给%s。\n", ob->query("unit"), ob->name(), who->name());
	me->set_temp("wuchang_zaohua/material", 1);
	message_vision(HIC"$N接过$n递来的药材，放在鼻下轻嗅了一下，点了点头。\n"NOR, who, me);
	money = me->query("combat_exp")/100000 + 1000;
	me->set_temp("wuchang_zaohua/need_money", money*10000);
	message_vision(CYN"$N说道：「神药制作不易，就收你"+ chinese_number(money) +"两黄金。给钱吧！」\n"NOR, who);
	log_file("static/wuchang_zaohua", sprintf("%s:%s(%s)给山中老人一份无常造化丹原料，制作费需要%d黄金。\n",ctime(time()),me->query("name"),me->query("id"),money)); 
	destruct(ob);
	return 1;
}
