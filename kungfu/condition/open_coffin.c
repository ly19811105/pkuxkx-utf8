#include <login.h>
int update_condition(object me, int duration)
{
       if (duration < 1) return 0;
        me->apply_condition("open_coffin", duration - 1);
        return 1;
}
