#include <ansi.h>
#include <net/daemons.h>    // why this file must under net?
#include <mudlib.h>

inherit F_CLEAN_UP;

int help(object me);
int replace;
void create() {seteuid(getuid());}
string lose_continue_dir(object me,string msg,string pattern,string change)
{
	if (!replace)
	{
		if (strsrch(msg,pattern)!=-1)
		{
			me->set_temp("Tell_Obstruct",time());
			msg=replace_string(msg,pattern,change,1);
			replace=1;
		}
	}
	return msg;
}
string obstruct(object me,string msg)
{
	string change_msg,return_msg="",*msgs,*dirs=({"s","south","n","north","w","west","east","e","se","southeast","sw","southwest","ne","northeast","nw","northwest"});
	string *legal_dirs1=({"s","e","se","sw","n","w","nw","ne"}),*legal_dirs2=({"south","north","east","west","northeast","northwest","southeast","southwest"});
	replace=0;
	if (strsrch(msg,";")!=-1)
	msgs=explode(msg,";");
	else
	return msg;
	switch (random(2))
	{
		case 0:
		change_msg=msgs[random(sizeof(msgs))];
		for (int i=0;i<sizeof(msgs);i++)
		{
			if (!replace&&member_array(change_msg,dirs)!=-1&&msgs[i]==change_msg)
			{
				replace=1;
				if (random(2))
				return_msg+="";
				else if (member_array(msgs[i],legal_dirs1)!=-1)
				return_msg+=legal_dirs1[random(sizeof(legal_dirs1))]+";";
				else
				return_msg+=legal_dirs2[random(sizeof(legal_dirs2))]+";";
				me->set_temp("Tell_Obstruct",time());
			}
			else if (i<sizeof(msgs)-1)
			return_msg+=msgs[i]+";";
			else
			return_msg+=msgs[i];
		}
		return return_msg;
		case 1:
		msg=lose_continue_dir(me,msg,"s;s;s","s;s");
		msg=lose_continue_dir(me,msg,"n;n;n","n;n");
		msg=lose_continue_dir(me,msg,"w;w;w","w;w");
		msg=lose_continue_dir(me,msg,"e;e;e","e;e");
		msg=lose_continue_dir(me,msg,"se;se;se","se;se");
		msg=lose_continue_dir(me,msg,"sw;sw;sw","sw;sw");
		msg=lose_continue_dir(me,msg,"ne;ne;ne","ne;ne");
		msg=lose_continue_dir(me,msg,"nw;nw;nw","nw;nw");
		return msg;
	}
}
int main(object me, string arg)
{
        string target, msg, mud, state;
        object obj;
        int abnormal;

        if ( !arg || sscanf(arg, "%s %s", target, msg) != 2 )
                return help(me);

/*        if ( sscanf(target, "%s@%s", target, mud) == 2 )
        {
            if ( !mud || !mud = INTERMUD_D->GetMudName(mud) )
                return notify_fail("没有这个Mud: " + mud);
                INTERMUD_D->eventSendTell( mud, target, me->query("name"), msg )
;
         write(HIG "你告诉" HIC+ target + "@" + mud + HIG"：" + msg + "\n" NOR);

                return 1;
        }*/

        obj = find_player(target);
        if (!obj || !me->visible(obj))
                return notify_fail("没有这个人....。\n");

 	if (!wizardp(me) && obj->query_temp("pigging_seat"))
		return notify_fail("正在拱猪的人听不到悄悄话……。\n");
      	if( ( obj->query("env/refuse_tell") == 2
          || (obj->query("env/refuse_tell") == 1
              && undefinedp(obj->query("friends/"+me->query("id")))))
          &&!wizardp(me) )
           return notify_fail("对方不想听你的话，有事请用chat\n");

        abnormal = 1;
          if ( obj->query_temp( "netdead" ) && obj->query("noDeadNetnoIdle") != "Pkuxkx")
                state = HIG "断线中" NOR;
        else if ( in_input( obj ) )
                state = HIC "输入文字中" NOR;
        else if ( in_edit( obj ) )
                state = HIY "编辑档案中" NOR;
        else if ( (interactive( obj ) && query_idle( obj ) > 120 )
                  || (wizardp(obj) && obj->query("env/is_idle")) )
                state = HIM "发呆中" NOR;
        else
                abnormal = 0;
         write(HIG "你告诉" HIC+ obj->name(1) + HIG"：" + msg + "\n" NOR);
		if (time()-obj->query_temp("Tell_Obstruct")>300&&!random(5))
			msg=obstruct(obj,msg);
         tell_object(obj, HIC + me->name(1)+HIG"("+me->query("id")+")"+ "告诉你：" + msg + "\n" NOR);
		 //HIG"("+me->query("id")+")" 
		 //enable message logger to get bug information from users
		if (objectp(CHANNEL_D->query("logger"))  && !me->query("no_logger"))
		{
          if ((userp(me) && userp(CHANNEL_D->query("logger"))) && (msg[0..3] != me->query_temp("logger/last_tell_msg")) && (msg[0..3] != me->query_temp("logger/last_tell_msg2"))&& (me->query("id")!=obj->query("id"))  )
                   //if (strsrch(msg," 在:") != -1)
					tell_object(CHANNEL_D->query("logger"),sprintf(  "%s的%s告诉%s的%s："+HIG+"%s\n" NOR,
                environment(me)->query("short"),me->name(1)+"("+me->query("id")+")", environment(obj)->query("short"),obj->name(1)+"("+obj->query("id")+")",msg));
			me->set_temp("logger/last_tell_msg2",me->query_temp("logger/last_tell_msg"));
			me->set_temp("logger/last_tell_msg",msg[0..3]);
		}

        if ( abnormal )
        {
                write( "不过" + obj->name(1) + state + "，可能回答不了你。\n" );
                if(stringp(obj->query("auto_reply")) )
                //对方有设定自动回答哦
                {
                	write(GRN+obj->name(1)+"的留言如下："+obj->query("auto_reply")+"\n"+NOR);
                	tell_object(obj,"你使用自动留言功能，回复了"+me->name(1)+"的对话。\n");
                }
        }
	else
	{
		if(obj->query("env/auto_reply"))
		{
			write(GRN+obj->name(1)+"的留言如下："+obj->query("auto_reply")+"\n"+NOR);
                	tell_object(obj,"你使用自动留言功能，回复了"+me->name(1)+"的对话。\n");
		}
	}
        obj->set_temp("reply", me->query("id"));
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：tell <某人> <讯息>

  你可以用这个指令和其他地方的使用者说话。同样，当有人同你通话时，
你的屏幕上会显示出对方向你说话的内容。
  如果你现在不想听别人对你的谈话，你可以使用
     set refuse_tell 2
选择关闭接收所有人的tell。
  使用
     set refuse_tell 1
选择tell只对好友开放。
详细情况请看help settings。

其他相关指令：reply,auto_reply,setfrd
HELP
        );
        return 1;
}
