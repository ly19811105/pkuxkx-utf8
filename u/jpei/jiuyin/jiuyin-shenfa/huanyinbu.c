#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        int i;

        if( (int)me->query_skill("jiuyin-zhengong",1) < 120 )
                return notify_fail("你的九阴真功还不够火候，使不出幻阴步。\n");  

        if( (int)me->query_skill("jiuyin-shenfa",1) < 120 )
                return notify_fail("你的九阴身法还不够火候，使不出幻阴步。\n");  

        if( (int)me->query("jingli", 1) < 200 )
                return notify_fail("你现在精力不够。\n");

        if( (int)me->query("neili", 1) < 200 )
                return notify_fail("你现在内力不够。\n");

        if (me->query_temp("jiuyin/fast"))
                return notify_fail("你正在使用幻阴步。\n");

        msg = HIW"$N施展出幻阴步，身法变得飘忽异常！\n\n"NOR; 

       me->add("neili", -100);
       me->add("jingli", -100);
       message_vision(msg, me);
       i = me->query_skill("jiuyin-shenfa", 1)/5;
       me->add_temp("apply/dexerity", i);
// 启动 auto perform
       me->set_temp("jiuyin/fast", 1);        
       call_out("remove_effect", (int)me->query_skill("jiuyin-zhengong")/2, me, i);
        return 1;
}

void remove_effect(object me, int i)
{
         if (!me) return;
         me->delete_temp("jiuyin/fast");
         me->add_temp("apply/dexerity", - i);
         message_vision(HIW"$N停止了幻阴步，身法恢复了正常。\n"NOR, me);
}

