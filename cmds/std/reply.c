// reply.c

#include <ansi.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string target, mud;
	object obj;

	if( !arg || arg=="" )
		return notify_fail("你要回答什么？\n");

	if( !stringp(target = me->query_temp("reply")) )
		return notify_fail("刚才没有人和你说过话。\n");

	if( sscanf(target, "%s@%s", target, mud)==2 ) {
		GTELL->send_gtell(lower_case(mud), lower_case(target), me, arg);
		write("网路讯息已送出，可能要稍候才能得到回应。\n");
		return 1;
	}

	obj = find_player(target);
	if( !obj )
		return notify_fail("刚才和你说话的人现在无法听见你，或者已经离开游戏了。\n");
        write(HIG "你回答"HIC + obj->name() + HIG"：" + arg + "\n" NOR);
        tell_object(obj, sprintf(HIC"%s"+HIG"回答你：%s\n"NOR,
		me->name(), arg ));

	 //enable message logger to get bug information from users
	if (objectp(CHANNEL_D->query("logger"))  && !me->query("no_logger"))
		if (userp(CHANNEL_D->query("logger")))
			if (obj != me)
				tell_object(CHANNEL_D->query("logger"),sprintf( "%s的%s回答%s的%s："+HIG+"%s\n" NOR,
			environment(me)->query("short"),me->name(1)+"("+me->query("id")+")", environment(obj)->query("short"),obj->name(1)+"("+obj->query("id")+")",arg));

	obj->set_temp("reply", me->query("id"));
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式：reply <讯息>

你可以用这个指令和刚才用 tell 和你说话的使用者说话。

see also : tell
HELP
	);
	return 1;
}
