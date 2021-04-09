// reboot.c

#include <login.h>
#include <obj.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string wiz_status;
	object npc;
        int intTime;

	if( me != this_player(1) ) return 0;
	
	wiz_status = SECURITY_D->get_status(me);
	if( wiz_status != "(admin)" && wiz_status != "(arch)" )
		return notify_fail("只有 (arch) 以上的巫师才能重新启动" + MUD_NAME + "\n");
        if (!arg)
            intTime = 5;
        else
        if (sscanf(arg,"%d",intTime) < 1)
            return notify_fail("命令格式：reboot 或 reboot 分钟。\n");

	seteuid(getuid());

    npc = new("/d/wizard/npc/god.c");
    npc->set("shutdown_time",intTime);
    npc->move("/d/city/idleroom");
    npc->shut_down();

	log_file("wiz/reboot",sprintf("%s于%s输入了reboot这个指令。\n",geteuid(me),ctime(time())));
	write("Ok。\n");

	return 1;
}

int help (object me)
{
        write(@HELP
指令格式: reboot
 
重新起动游戏, 系统会开始倒数计时, 五分钟後重新起动。
 
HELP
);
        return 1;
}
 
