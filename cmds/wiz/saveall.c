// save.c
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object link_ob,*all_users;
	int agediff,expdiff,timediff;
	string str;

	seteuid(getuid());
	all_users=users();
	for(int i=0;i<sizeof(all_users);i++)
		{
		if( !objectp(link_ob = all_users[i]->query_temp("link_ob")) )
		{
			if(all_users[i]->query("name")) tell_object(me,all_users[i]->query("name")+"不是经由正常连线进入，不能储存。\n");
			continue;
		}

      
		if( (int)link_ob->save() && (int)all_users[i]->save() ) {
			 all_users[i]->set("last_save_time",time());
			 tell_object(me,all_users[i]->query("name")+"储存完毕。\n");
                         "cmds/usr/backup.c"->main(all_users[i]);
                         tell_object(me,all_users[i]->query("name")+"的档案已被备份。\n");
			continue;
		} else {
			tell_object(me,all_users[i]->query("name")+"储存失败。\n");
			continue;
		}
	}
        message("vision",HIY"所有玩家存档一次!\n"NOR,this_player());
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式：saveall

把所有玩家辛苦奋斗的结果存起来。
HELP
	);
	return 1;
}
