//岳家枪法--连环枪  grin
// Modified by iszt@pkuxkx, 2007-04-07

#include <ansi.h>
inherit F_SSERVER;
void attack_enemy(object me,object target);
int actionnuma,actionnumb;

int perform(object me, object target)
{
	object weapon;
	float coefficiency;
	int ini_damage;
	int damage;
	int delays = time();

	if(!target) target=offensive_target(me);
	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail(HIR"连环枪要对战斗中的对手使用！\n"NOR);

	if(!me->is_fighting())
		return notify_fail(HIR"连环枪只能在战斗中使用！\n"NOR);
	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "spear")
		return notify_fail("连环枪当然要用枪啦，没枪你搞什么搞！\n");
	if(me->query_skill("yuejia-qiangfa",1)<100)
		return notify_fail(HIR"你的岳家枪法级别还不够，不能连环出击！\n"NOR);
	if(me->query("shen")<-1000)
		return notify_fail(HIR"鸡鸣狗盗之徒还配使岳家连环枪？\n"NOR);
	if(me->query("neili")<400)
		return notify_fail(HIR"你就这么点内力还想连环出几招？省省吧！\n"NOR);
	if( (delays - me->query_temp("lianhuan_end")) < 10 )
		return notify_fail("连环枪不能一用再用，敌人现在已经提高警惕了！\n");

	message_vision(HIW"\n$N"+HIW"趁$n"+HIW"不备使出夺魄连环枪，让$n"+HIW"防不胜防！\n",me,target);

	me->set_temp("yuejia_lianhuan", 0);
	ini_damage=me->query_temp("apply/damage");
	attack_enemy(me,target);
	me->set_temp("apply/damage",ini_damage);
	me->start_busy(1);
	if (!target->is_busy())
	{
		target->start_busy(1);
	}
	me->set_temp("lianhuan_end",time());
	return 1;
}

void attack_enemy(object me,object target)
{
	int coefficient;
	int damage;
	object weapon;
	string msg;
	if (!target)
		return;
	if(me->query("neili")<50)
	{
		message_vision(HIR"$N由于内力不支，连环攻击无法继续下去了。\n"NOR,me,target);
		if (!target->is_busy())
		{
			target->start_busy(1);
		}
		return ;
	}
	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "spear")
	{
		tell_object(me, HIR"连环枪当然要用枪啦，没枪你搞什么搞！\n"NOR);
		if (!target->is_busy())
		{
			target->start_busy(1);
		}
		if (!me->is_busy())
		{
			me->start_busy(1);
		}
		return ;
	}
	if (me->query_skill_mapped("spear") != "yuejia-qiangfa")
	{
		tell_object(me, HIR"夺魄连环必须使用岳家枪法方能施展！\n"NOR);
		if (!target->is_busy())
		{
			target->start_busy(1);
		}
		if (!me->is_busy())
		{
			me->start_busy(1);
		}
		return ;
	}
	if (!target->is_busy())
	{
		target->start_busy(6);
	}
	
		coefficient=me->query_skill("yuejia-qiangfa")*11/1000;
	if (objectp(weapon = me->query_temp("weapon"))&& (string)weapon->query("id")== "duopo qiang")
	{
		coefficient=coefficient*2;
		write(MAG"由于你手握"+HIR"夺魄枪"+MAG"，你发现你的命中率高了许多！\n"NOR);
	}
	if(coefficient>11) coefficient=11;
	if(coefficient<2) coefficient=2;
//C-直到S		
	if( F_KUNGFU->hit_rate( me->query("combat_exp"), (int)target->query("combat_exp"), 11-coefficient, me, target) )
	{
		me->add_temp("yuejia_lianhuan",1);
		if(me->query_temp("yuejia_lianhuan")>9)
		{
			message_vision(HIY"岳家夺魄连环枪连环九式打完收功！\n"NOR,me,target);
			if (!target->is_busy())
			{
				target->start_busy(1);
			}
			me->set_temp("yuejia_lianhuan_num",0);
			return;
		}
		message_vision(HIR"夺魄连环枪连环夺魄第"+
			chinese_number(me->query_temp("yuejia_lianhuan"))+"式！\n"NOR,me,target);
		damage=1;
		me->start_busy(0);
		if ( me->query_temp("yuejia_lianhuan") > 2 )
		{
			actionnuma = me->query_temp("yuejia_lianhuan")-2;
			actionnumb = me->query_temp("yuejia_lianhuan")-1;
		}
		else
		{
			actionnuma = 1;
			actionnumb = 2;
		}
		me->set_temp("yuejia_lianhuan_num",1);
		me->set("actions", (: call_other,"/kungfu/skill/yuejia-qiangfa.c", "query_action" :));
		damage=COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		if (damage < 1) target->receive_damage("qi", 30+random(20), me);
		me->set_temp("yuejia_lianhuan_num",2);
		me->set("actions", (: call_other,"/kungfu/skill/yuejia-qiangfa.c", "query_action" :));
		damage=COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
		me->set_temp("yuejia_lianhuan_num",0);
		me->start_busy(3);
		me->add("neili",-50);
		if(target->query("qi")<5)
		{
			message_vision(HIW"$N"+HIW"看到$n"+HIW"已命在旦夕，心一软，停下了攻击。\n"NOR,me,target);
			target->command("halt");
			CHANNEL_D->do_channel(target, "bd", "admire "+me->query("id"), 1);
			CHANNEL_D->do_channel(target, "bd", "fear1x", 1);
			if (!target->is_busy())
			{
				target->start_busy(1);
			}
			return ;
		}
		else
		{
			call_out("attack_enemy",1,me,target);
		}
	}
	else
	{
		message_vision(HIY"$n"+HIY"抓住$N"+HIY"的一个破绽，从$N"+HIY"的枪风下逃了过去！$n"+HIY"吓出了一身冷汗。\n"NOR,me,target);
		if (!target->is_busy())
		{
			target->start_busy(1);
		}
		me->set_temp("yuejia_lianhuan_num",0);
		return;
	}
}