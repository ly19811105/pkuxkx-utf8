// purge.c

#include <ansi.h>
#define SYNTAX	"指令格式：purge [<未上线天数>] | <使用者姓名> because <原因>\n"
#define MAIL_FILE "/adm/tmp/mailuser"

inherit F_CLEAN_UP;

protected int do_purge_players(int day);

int main(object me, string arg)
{
	string name, reason;
	string status;
	object ob;
	int day;
	string add_cmd;

	status = wizhood(me);
	if( me!=this_player(1)
	|| wiz_level(me) < wiz_level(status) )
		return notify_fail("你没有权力使用这个指令。\n");

	if( !arg ) return notify_fail(SYNTAX);

	if( sscanf(arg, "%d", day) && day >= 0) return do_purge_players(day);

	if( sscanf(arg, "%s because %s", name, reason)!=2 )
		return notify_fail(SYNTAX);

	seteuid(getuid());
        if( file_size(DATA_DIR + "login/" + name[0..0] + "/" + name + ".o")<0 )
		return notify_fail("没有这位使用者。\n");
         CNAME_D->remove_cname(name);
         write("移除使用者中文名....\n");

         cp(DATA_DIR + "login/" + name[0..0] + "/" + name + ".o","/data_bak/login/"+name+".bak");
         rm(DATA_DIR + "login/" + name[0..0] + "/" + name + ".o");
          cp(DATA_DIR + "user/" + name[0..0] + "/" + name + ".o","/data_bak/user/"+name+".bak");
          rm(DATA_DIR + "user/" + name[0..0] + "/" + name + ".o");
	write( "使用者 " + capitalize(name) + " 删除掉了。\n");
	log_file("static/PURGE", sprintf("[%s] %s purged %s because %s.\n",
		ctime(time())[0..15], geteuid(this_player(1)), name, reason));
        if(ob=find_player(name)) destruct(ob);
	return 1;
}

protected int do_purge_players(int day)
{
	int i, j, ppl_cnt, count;
	string *dir, *ppls, name,add_cmd;
	mixed info;
        if (day<60)
	return notify_fail("时间不能小于60天.\n");

	seteuid(getuid());
	message("system", "\n*** 整理玩家储存档中，请稍候.... ***\n", users());
	write("处理中：");
	count = 0;
	ppl_cnt = 0;
	dir = get_dir(DATA_DIR + "login/");
	for(i=0; i<sizeof(dir); i++) {
		reset_eval_cost();
		write(dir[i]);
		ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
		ppl_cnt += sizeof(ppls);
		for(j=0; j<sizeof(ppls); j++) {
			if( sscanf(ppls[j], "%s.o", name)==1 )
				if( (string)SECURITY_D->get_status(name)!="(player)" )
					continue;
			info = stat(DATA_DIR + "login/" + dir[i] + "/" + ppls[j]);
			if( (time()-(int)info[1])/86400 >= day ) {
				NAME_D->remove_id_name(ppls[j]);
			add_cmd = "adduser -kill " + name;
			write_file(MAIL_FILE, add_cmd + "\n"); 
			write_file(MAIL_FILE, name + "\n");
			write_file(MAIL_FILE, "delete\n");
			write("邮箱已删除。\n");

                                rm(DATA_DIR + "login/" + dir[i] + "/" + ppls[j]);
				rm(DATA_DIR + "user/" + dir[i] + "/" + ppls[j]);
				count ++;
			}
		}
	}
	write("\n\n原来总共有 " + ppl_cnt + " 位使用者。\n");
	write( count + " 个超过 " + day + " 天未上线的使用者被清除掉了。\n");
	write("现在总共有 " + (ppl_cnt - count) + " 位使用者。\n");
	log_file("static/PURGE", sprintf("[%s] %s cleaned up %d characters who didn't login for more than %d days\n"
		"\t\tResulting statistics: %d characters remaining.\n",
		ctime(time())[0..15], geteuid(this_player(1)), count, day, ppl_cnt - count));


	return 1;
}

int help(object me)
{
write(@HELP
指令格式：purge [<未上线天数>] | <使用者姓名> because <原因>

清除一个使用者或清除超过一定天数不曾上线地使用者。
HELP
	);
    return 1;
}
