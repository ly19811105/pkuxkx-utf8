// destroy.c
//
// Created by pretty (09/16/98)

int main(object me, string arg)
{
	object ob, *list;
	string *autoloads, filename;

	if( !arg )
		return notify_fail("你要销毁什么东西？\n");

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("你身上没有这样东西。\n");

	filename = base_name(ob) + ".c";

	if( !arrayp(autoloads = me->query("auto_load")) ||
		member_array( filename, autoloads ) == -1 )
		return notify_fail("这个东西不是你定做的。\n");

	seteuid(ROOT_UID);
	rm(filename);
	ob->move(environment(me));
	destruct(ob);
	autoloads -= ({ filename });
	me->set("auto_load", autoloads);
	seteuid(getuid());
	write("销毁完毕。\n");
	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : destroy <某物件>

你可以用这个指令来销毁你定做的物品，当
你对所定做的物品不满意或者需要新的物品
时可以使用这个指令。

HELP
    );
    return 1;
}

