// special

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string  msg;
        mapping ss;
        string  skill;
        object ob;
        string pro;

        if (wizardp(me) && stringp(arg) &&
            objectp(ob = find_player(arg)))
                // 查看其他玩家的特殊技能
                arg = 0;
        else
                ob = me;

        pro = (ob == me) ? "你" : ob->name(1);

    if(me->query("age")<18&&!wizardp(me))
		return notify_fail("你还未成年，不能使用特殊技能。\n");
        

        if (! mapp(ss = ob->query("special_skill")) ||
            ! sizeof(ss))
                return notify_fail(pro + "现在什么特技都不会。\n");

        if (arg && (ob == me))
        {
                // 有参数，运用特技。
                if (me->is_busy() && arg != "chainless")
                        return notify_fail("你现在忙着呢，不能使用特技。\n");

                if (sscanf(arg, "%s %s", skill, arg) != 2)
                        skill = arg;

                if (! me->query("special_skill/" + skill))
                        return notify_fail("你不会这种特技啊！\n");

                if (file_size(SPECIAL_D(skill) + ".c") < 0)
                        return notify_fail("好像没有这种特技...\n");
                return SPECIAL_D(skill)->perform(me, skill, arg);
        }

        msg = pro + "现在会以下这些特技：\n";
        foreach (skill in keys(ss))
        {
                if (file_size(SPECIAL_D(skill) + ".c") < 0)
                {
                        write("不存在技能：" + skill + "\n");
                        continue;
                }
				if (!me->query("special_level/"+ skill))
				{
					me->set(("special_level/"+ skill),1);
				}
                msg += SPECIAL_D(skill)->name() + "(" YEL + skill + NOR "):等级"+chinese_number(me->query("special_level/"+skill))+"\n";
        }
        write(msg);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : special <skill> | <玩家ID>

使用这条命令可以查看你的特技，如果要运用你的特技，则可以加上
参数指名使用什么特技。比如：special health，增加自己的气血。

巫师可以查看其他玩家所会的特殊技能。
相关帮助：help kungfu-special

HELP );
    return 1;
}

