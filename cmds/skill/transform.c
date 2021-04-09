// transform.c
// 将某一种内力转换成另外一种内力

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string fforce, tforce;
	string fneili, tneili;
	int pct, tf_n, tf_e, con, fuse;

	seteuid(getuid());
	fuse = 0;

	if (!stringp(arg))
		return notify_fail("指令参数错误！正确的格式是：transform <内功ID> into <内功ID> <转换百分比>\n");

	if (sscanf(arg, "%s into %s %d", fforce, tforce, pct) != 3)
	{
		if (sscanf(arg, "%s into none", fforce) != 1)
			return notify_fail("指令参数错误！正确的格式是：transform <内功ID> into <内功ID> <转换百分比>\n");
		else
		{
			tforce = "none";
			pct = 100;
		}
	}

	printf("%s, %d\n", tforce, pct);

	if (me->is_busy()) return notify_fail("你现在正忙着呢。\n");

	if (me->is_fighting()) return notify_fail("战斗中不能练内功，会走火入魔。\n");

	if (file_size(SKILL_D(fforce) + ".c") <= 0)
		return notify_fail("内功" + fforce + "并不存在，请检查你输入是否有误。\n");

	if (file_size(SKILL_D(tforce) + ".c") <= 0 && tforce != "none")
		return notify_fail("内功" + tforce + "并不存在，请检查你输入是否有误。\n");

	//判断是否是内功，否则不能转换
	if (!SKILL_D(fforce)->valid_enable("force") &&
		!(fforce == "force" &&
		tforce == "none"))
		return notify_fail("你只能转换内功！\n");

	if (!stringp(fneili = SKILL_D(fforce)->translate(fforce)))
		fneili = fforce;

	if (tforce == "none" &&
		(!me->query_skill(fforce, 1) ||
		fforce == "force") &&
		me->query("backup_neili/" + fneili + "/max_neili") > 0)
	{
		me->delete("backup_neili/" + fneili);
		message_vision(HIR"$N逆转真气，放弃了自己的部分内力。\n"NOR, me);
		me->start_busy(5);
		return 1;
	}

	if (!me->query_skill(fforce, 1) ||
		(!me->query_skill(tforce, 1) && tforce != "none"))
		return notify_fail("你不会这种技能。\n");

	if (me->query_skill_mapped("force") != fforce)
		return notify_fail("只能将当前在用内力转换到其他新修炼内功上。\n");

	SKILL_D(fforce)->backup_neili(me, fforce);

	if (fneili != fforce &&
		me->query("backup_neili/" + fneili + "/force") != fforce)
		return notify_fail("当前使用内功对应的内力是其他内功修炼出来的，请切换到该门内功后再进行转换。\n");

	if (!me->query("transform_first"))
		fuse = 1;

	if ((pct < 10 || pct> 90) &&
		(!fuse || tforce == "none"))
		return notify_fail("只能将该门内功的10%到90%的内力转换到一门新内功上。\n");

	if (tforce == "none")
	{
		me->set("max_neili", me->query("max_neili")*(100 - pct) / 100);
		me->set("backup_neili/" + fneili + "/max_neili", me->query("max_neili"));
		message_vision(HIR"$N逆转真气，放弃了自己的部分内力。\n"NOR, me);
		me->start_busy(5);
		return 1;
	}

	if (!SKILL_D(tforce)->valid_enable("force"))
		return notify_fail("只有内功才能接收内力！\n");

	if (!stringp(tneili = SKILL_D(tforce)->translate(tforce)))
		tneili = tforce;

	if (me->query("backup_neili/" + tneili + "/max_neili") > 0)
		return notify_fail("接收内力的新学内功必须本身未修炼出任何内力。\n");

	if (fuse)
	{
		me->delete("backup_neili/" + tneili);
		me->set("backup_neili/" + tneili, me->query("backup_neili/" + fneili));
		if (tneili == tforce)
			me->delete("backup_neili/" + tneili + "/force");
		else
			me->set("backup_neili/" + tneili + "/force", tforce);
		me->delete("backup_neili/" + tneili + "/sucked_neili");
		me->map_skill("force", tforce);
		me->delete("backup_neili/" + fneili);
		me->set("transform_first", 1);
		message_vision(HIG"$N将自己的内力转换到新学的内功上。\n"NOR, me);
		me->start_busy(5);
		return 1;
	}

	if (me->query("sucked_neili") ||
		SKILL_D(fforce)->force_character("TYPE_SUCK_EFF") > 0)
		return notify_fail("你的内力中包含有杂质，恐怕无法将该内力转移到新修炼的内功上。\n");

	con = me->query("con") - 20;
	if (con < 0)
		con = 0;
	tf_n = me->query("max_neili")*pct / 100;
	tf_e = me->query("exercised_neili")*pct / 100;
	me->add("max_neili", -tf_n);
	me->add("exercised_neili", -tf_e);
	me->add("backup_neili/" + fneili + "/max_neili", -tf_n);
	me->add("backup_neili/" + fneili + "/exercised_neili", -tf_e);
	me->add("backup_neili/" + tneili + "/max_neili", tf_n*(60 + con) / 100);
	me->add("backup_neili/" + tneili + "/exercised_neili", tf_e*(60 + con) / 100);
	if (tneili != tforce)
		me->set("backup_neili/" + tneili + "/force", tforce);

	message_vision(HIY"$N将自己的部分内力转换到新学的内功上。\n"NOR, me);
	me->start_busy(5);
	return 1;
}

int help(object me)
{
	tell_object(me, @HELP
命令格式：transform <内功ID> into <内功ID> < 转换百分比 >
命令格式：transform <内功ID> into none
将一门内功的内力按照百分比转移到一门新内功上，如果以
前从来没用过该功能，则第一次使用该功能不会有任何损耗，否
则每次转换将按照先天根骨受到一定程度的损耗。
注意内力中包含从他人哪里吸取过来的内力或者内功拥有吸
取他人内力功能的是不能将内力转移到其他内力的。（当然第一
次操作不在此限制内。）
当转换目标内功ID为none的时候表示你要放弃当前内功的内力。
注意第一次使用transform命令的时候为特殊场景，这时候
转换百分比无效，可以输入任意数值，效果是将当前内功对应
内力相关属性直接修改为另外一门内功，仅此一次机会，使用过
后就是正常使用模式。
正常使用模式仅能将10%到90%的当前最大内力转换到一门新
内功上，并且转换过程中有一定程度损失，具体损失百分比和先
天根骨有关系。
HELP
		);
	return 1;
}