

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        if (duration < 1) {
           tell_object(me, HIY "你巡逻时间已过，如果四处查看完毕，可以回去覆命了！\n" NOR);
            return 0;
        }
        if (!duration) return 0;
        me->apply_condition("beijing_xuncheng", duration - 1);
        return 1;
}

string query_type(object me)
{
	return "job";
}
