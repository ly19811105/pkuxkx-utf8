//xpasswd.c


#include <login.h>;
inherit F_CLEAN_UP;

void create()
{
	seteuid(getuid());
}

int main(object me, string arg)
{
	object ob,link_ob;
	string id,password;
	if(!arg||sscanf(arg,"%s %s",id,password)!=2)
		return notify_fail("用法:xpasswd ID 新密码\n此操作容易损害玩家利益，你必须先调查清楚！\n");
	ob=find_player(id);
	if(!ob)
	{
        ob = new(LOGIN_OB);
        ob->set("id",id);
        if( !ob->restore() )
        	return notify_fail("没有这个玩家。\n");
        else
		{                                    
            ob->set("name",password);
          tell_object(me, "玩家 " + ob->query("name") + "("+ob->query("id")+") "
              + "的密码已经更改为："+password+"。\n");
    log_file( "static/CHANGE_PASSWD", sprintf("%s(%s) 修改了 %s(%s) 的密码, %s。\n",me->query("name"), me->query("id"), ob->query("name"), ob->query("id"),ctime(time())));
           ob->save();
           destruct(ob);
           return 1;
		}
	}
	link_ob=ob->query_temp("link_ob");
	if(link_ob)
	{
                 link_ob->set("name",password);
		link_ob->save();
        tell_object(me, "玩家 " + ob->query("name") + "("+ob->query("id")+") "
			+ "的密码已经更改为："+password+"。\n");
    log_file( "static/CHANGE_PASSWD", sprintf("%s(%s) 修改了 %s(%s) 的密码, %s。\n",me->query("name"), me->query("id"), ob->query("name"), ob->query("id"),ctime(time())));
		return 1;
	}
	else
		return notify_fail("错误。无法进行修改。\n");
	return 1;
}


int help(object me)
{
        write(@HELP
指令格式 : xpasswd ID 新密码

这个指令可以修改玩家的密码，请谨慎使用。

HELP
    );
    return 1;
}
