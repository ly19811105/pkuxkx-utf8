// vote command..
// Modified by Marz, 04/18/96
// Modified by iszt@pkuxkx, 2007-03-11

#include <net/dns.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int valid_voters(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object victim;
        string act_name, victim_name;
        string file;
        object file_ob;
        int vote_result;

        if (((int)me->query("age")<16) && !wizardp(me))
        {
                return notify_fail("民主不是儿戏！小孩子一边玩去！\n");
        }

        if ((int)me->query("vote/deprived"))
        {
                return notify_fail("你想起当初玩弄民主、被剥夺投票权的事，追悔莫急。\n");
        }
        
        if ((int)me->query("deactivity") > 3)
        {
            return notify_fail("请先fullme后再投票。北侠投票系统只统计活跃玩家。\n");
        }

        if (!arg || sscanf(arg, "%s %s", act_name, victim_name) != 2)
        {
                write("这神圣的一票，要想清楚了才能投。\n");
                return notify_fail("指令格式：vote <动议> <某人>。请help vote查看详细格式。\n");
        }

        victim = LOGIN_D->find_body(victim_name);
        if ((!victim && act_name != "ban")|| (objectp(victim) && !wizardp(me) && wizardp(victim)))
                return notify_fail("你要投谁的票？\n");

        if( !stringp(file = (string)"/cmds/std/vote/"+act_name)
                || file_size(file + ".c") <= 0 )
                        return notify_fail("你要投票干什么？\n");

        if ( !(file_ob = find_object(file)) )
                file_ob = load_object(file);

        if(act_name == "ban")
        {
            vote_result = file_ob->vote(me, victim_name);
        }
        else
        {
            vote_result = file_ob->vote(me, victim);
        }
        if (vote_result <= 0)
                if ((int)me->query("vote/abuse")> 50)
                {
                        write( HIG "你因为胡乱投票，投票权被剥夺了！\n" NOR);
                        me->set("vote/deprived", 1);
                        me->apply_condition("vote_suspension", 120);
                        me->delete("vote/abuse");
                }
                else
                        return 0;

        return 1;
}

int valid_voters(object me)
{
        object *list;
        int d = 0;
        int j;

        list = users();
        j = sizeof(list);
        while( j-- )
        {
                // Skip those users in login limbo.
                if( !environment(list[j]) ) continue;
                if( !me->visible(list[j]) ) continue;
                if (((int)list[j]->query("age")<16) && !wizardp(list[j])) continue;
                if ((int)list[j]->query("vote/deprived")) continue;
                if ((int)list[j]->query("antirobot/deactivity") > 3) continue;//不fullme玩家不计入，这样就不会出现挂机太多，没人投票的情况。
                d++;
        }
        return d;
}

int help(object me)
{
write(@HELP
指令格式 : vote <动议> <某人> 

此命令提议采取某种行动，由大家投票决定。除reboot动议外，如果五分钟内没
有人附议，投票会自动取消。当前可以有如下<动议>：

chblk: 关闭某人交谈频道，需三票以上的简单多数同意。
unchblk: 打开某人交谈频道，需三票以上的三分之一票数同意。
reboot: 重启，同一ip只能投一次票（包括穿梭）。其中<某人>表示自己的id。
ban: 关闭某人的IP地址
xiuxian：关闭某人的休闲玩家模式，需实名玩家投5票同意。
HELP
    );
    return 1;
}

/**
future motion (not implemented yet):
eject: 驱逐某人，需三票以上的简单多数同意。
robot: 怀疑某人是机器人，如果有五人附议，则由系统审训被怀疑者。
jail: 将某人送进监狱，需三票以上的简单多数同意。
**/

