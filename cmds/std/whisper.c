// whisper.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string dest, msg;
	object ob;

	if( !arg || sscanf(arg, "%s %s", dest, msg)!=2 )
		return notify_fail("你要对谁耳语些什么？\n");

	ob = present(dest, environment(me));
	if( !ob || !ob->is_character() )
		return notify_fail("你要对谁耳语？\n");
	if(ob==me) return notify_fail("自己怎么和自己说悄悄话?\n");
        write( "你在" + ob->name() + "的耳边悄声说道："BRED+HIW + msg + NOR"\n" NOR);
	tell_room( environment(me), me->name() + "在" + ob->name()
		+ "耳边小声地说了些话。\n", ({ me, ob }) );
	if( !userp(ob) ) ob->relay_whisper(me, msg);
	else
                tell_object( ob, me->name() +"在你的耳边悄声说道："BRED+HIW + msg + "\n" NOR);
               if (objectp(CHANNEL_D->query("logger")))
               {
                        if (userp(CHANNEL_D->query("logger"))&& (msg[0..3] != me->query_temp("logger/last_whisper_msg")) && (msg[0..3] != me->query_temp("logger/last_whisper_msg2")))
                                if (ob != me)
                                        tell_object(CHANNEL_D->query("logger"),sprintf(  "%s的%s耳语%s的%s："+HIG+"%s\n" NOR,
                environment(me)->query("short"),me->name(1)+"("+me->query("id")+")", environment(ob)->query("short"),ob->name(1)+"("+ob->query("id")+")",msg));
				me->set_temp("logger/last_whisper_msg2",me->query_temp("logger/last_whisper_msg"));
				me->set_temp("logger/last_whisper_msg",msg[0..3]);
            }
	return 1;
}

int help(object me)
{
	write( @TEXT
指令格式：whisper <某人> <讯息>

这个指令可以用来和同一房间中的人耳语，包括 NPC 在内。
TEXT
	);
	return 1;
}
