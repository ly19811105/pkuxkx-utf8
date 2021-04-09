// home.c

#include "/doc/help.h"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string msg;

         if( file_size("/d/wizard/wizard_room_" + geteuid(me) + ".c") <= 0 )
		return notify_fail("你没有自己的工作室。\n");

if( !me->query("env/invisibility") )
	if( stringp(msg = me->query("env/msg_home")) )
		message_vision(msg + "\n", me);
	me->move("/d/wizard/wizard_room_" + geteuid(me) + ".c");
	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : home

利用此一指令可直接回到自己的工作室。
如果你有 'msg_home' 这个设定, 则在场的人都会看到那个讯息.
HELP
    );
    return 1;
}

