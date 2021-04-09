// Modified by iszt@pkuxkx, 2007-04-14

inherit "/cmds/guider/guidercmd";

int get_cost(object me) {return 1;}

int exec_cmd(object me, string arg)
{
	object ob;
	seteuid(getuid(me));
	if(!arg)
    {
        tell_object(me,"命令格式：hpapp 学员ID\n");
		return 0;
    }		
    else
    {
        ob = present(arg, environment(me));
        if (!ob) ob = find_player(arg);
        if (!ob || !me->visible(ob))
		{
            tell_object(me,"你要察看谁的状态？\n");
			return 0;
		}
    }
    if (check_apprentice(me,ob)!=1)
    {
        tell_object(me,"你只能查看当前学员的状态 \n");
		return 0;
    }

	return "/cmds/usr/hp.c"->show_hp(me,ob);
}

int help(object me)
{
	write(@HELP
指令格式 : hpapp 学员ID

这个指令可以显示你的学员精, 气, 神等数值。

HELP
    );
    return 1;
}
