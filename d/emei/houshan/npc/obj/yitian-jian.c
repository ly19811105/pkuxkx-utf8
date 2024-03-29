// Made by cobra
// 02.06.24
#include <weapon.h>
#include <ansi.h>

inherit F_UNIQUE;
inherit SWORD;
int return_normal(object ppl,object ob);
void create()
{
        set_name(HIW"倚天剑"NOR, ({ "yitian jian","jian" }));
	set_weight(10000);
        set("value",0);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
                set("long", HIW+"这就是灭绝师太那把断金切玉、锋锐绝伦的倚天宝剑！\n"+NOR);
                set("value", 0);
		set("no_drop",this_object()->query("name")+HIR"是武林至宝，多少人为它丢掉了性命，你竟然舍得把他扔掉？\n"NOR);
		set("no_give",this_object()->query("name")+HIR"是武林至宝，多少人为它丢掉了性命，你竟然舍得把他送给别人？\n"NOR);
		set("no_steal",1);
                set("unique",1);
                set("no_store",1);
		set("material", "steel");
		set("weapon_prop/strength", 3);
		set("weapon_prop/dexerity", 4);
		set("weapon_prop/intelligence",3);
                set("wield_msg", HIW"$N反手抽出背上负着的"+query("name")+HIW"，霎时间寒芒吞吐，电闪星飞。\n$N手持宝剑斜指苍天，纵声狂笑！\n"NOR);
		set("unwield_msg", "寒光一闪，$N已把"+query("name")+"插回鞘中。\n");
                set("preorder",0);
                set("robinterval",7200);  
	}
        init_sword(300);
	setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon;
//        me->add_temp("apply/attack",30);
//        me->add_temp("apply/dodge", 40);
	if (random(20)==1)
	{
        // me->add_temp("apply/damage",20);
	if(!objectp(weapon=victim->query_temp("weapon")))
                message_vision(HIW"\n寒光一闪，$N"HIW"眼前一花，已被"+this_object()->query("name",1)+HIW+"削中。"NOR,victim);
	else if(weapon->query("unique"))
		message_vision(HIW"\n$N的"+this_object()->query("name")+HIW+
		"与$n手中的"+weapon->query("name")+HIW+
		"相击，竟都安然无恙。"NOR,me,victim);
	else
	{
		message_vision(HIW"\n只听“嚓”的一声，$N手中的$n已被"+
			this_object()->query("name")+HIW+"斩成两截！"NOR,victim,weapon);
		weapon->unequip();
		weapon->move(environment(victim));
		weapon->set("name", "断掉的" + weapon->query("name"));
		weapon->set("value", 0);
		weapon->set("weapon_prop", 0);
                remove_call_out("remove_broken_weapon");
               call_out("remove_broken_weapon", random(30)+60,weapon);
		me->reset_action();
	}
                //        call_out("return_normal",5,me,this_object());
	}
	return NOR;
}

int return_normal(object ppl,object ob)
{
//        ppl->add_temp("apply/attack",-30);
//        ppl->add_temp("apply/dodge", -40);
	ppl->add_temp("apply/damage",-20);
	return 1;
}

/*
string query_autoload()
{
	return query("name");
}

void autoload()
{}
*/
void remove_broken_weapon(object ob)
{
  if(ob && environment(ob)) {
    tell_object(environment(ob),
      "一阵微风吹过，"+ob->name()+"化为片片尘土，消失不见了。\n");
    destruct(ob);
  }
}

