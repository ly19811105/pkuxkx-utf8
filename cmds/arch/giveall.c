/*请不要连续使用本命令，特别是在人多的时候，会给系统带来很大负担*/

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string what)
{
	object ob, *ob_list, ob1;
	int i, count;
	string str;

	if(!what)
		return notify_fail("指令格式 giveall 物品路径\n");
	
	if( sscanf(what, "%*s.c") != 1)
		return notify_fail("路径不合法，无法找到物品。\n");
	
	if( file_size(what) < 0 )
		return notify_fail("没有这个档案(" + what + ")。\n");	

	seteuid(getuid());

	ob_list = users();

	for(i=0; i<sizeof(ob_list); i++)
	{
/*
                if(!random(10))
			continue; //避免礼物泛滥
*/
		count++;
		ob = ob_list[i];
		ob1 = new(what);
                ob1->set_amount(random(9)+1);    //给太多了
		ob1->move(ob); 
		tell_object(ob, HIG "天上突然掉下了什么东西到你的口袋里，你最好检查一下。\n" NOR);
	}
	str = sprintf("共有 %d 位玩家得到了%s。\n", count, what->query("name"));
	log_file("wiz/giveall", me->query("name")+"("+capitalize(geteuid(me))+")在"
		+ctime(time())+"输入giveall "+what+"，"+str+"\n");
	me->start_more(str);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式：giveall 物品路径

给在线的所有玩家一件物品。请慎用！
HELP);
	return 1;
}
