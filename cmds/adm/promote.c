// promote.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string old_status, new_status, str;
	int my_level, ob_level, level;

	if( me!=this_player(1) ) return 0;

	if( !arg || sscanf(arg, "%s %s", arg, new_status)!=2 )
		return notify_fail("指令格式：promote <使用者> <等级>\n");

	if( wiz_level(new_status) < 0 || wiz_level(new_status) > 6)return notify_fail("没有这种等级。\n");

	if( !objectp(ob = present(arg, environment(me))) 
	||	!userp(ob) )
		return notify_fail("你只能改变使用者的权限。\n");


	old_status = wizhood(ob);

	seteuid(getuid());
	if( !(SECURITY_D->set_status(ob, new_status)) )
		return notify_fail("修改失败。\n");

	str = me->query("name") + "(" + me->query("id") + ")将" + ob->query("name")
            + "(" + ob->query("id") + ")的权限从 " + old_status + " 改为 " + new_status + " 。\n";
	write_file("/log/static/promote", str);		 	
	message_vision("$N将$n的权限从 " + old_status + " 改为 " + new_status + " 。\n", me, ob);
	seteuid(getuid());
	ob->enable_player();

	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : promote <某人> (权限等级)

用来提升权限等级, (player) (immortal) (apprentice) (wizard)
(arch) (admin)
一个 admin 能提升权限至任何等级, 而 arch 只能提升至 arch。
HELP
    );
    return 1;
}
