// im.c

#include <ansi.h>
#define IM_D "/adm/daemons/im_d.c"

inherit F_CLEAN_UP;

int who_list(object me);
int register(object me,string pro);
int help(object me);

int main(object me, string arg)
{
    string who,msg;
    //QQ群消息转发id专用命令
    if (!me->query("qqmessage"))
    	return 0;
    if(!arg) return help(me);
    if(arg == "login") {
        if(me->query_temp("im_fd") && IM_D->query_users()[me->query_temp("im_fd")]["obj"] == me)
            return notify_fail("\n[IM Message]:你正在登入中，請用 im quit 離線。\n");
        write("\n[IM Message]:開始登入即時通訊精靈。\n");
        IM_D->login_irc(me);
        return 1;
    } //return process_login(me,crypt(me->query("id"),me->query("id"))[0..10]);
    if(!undefinedp(me->query_temp("im_fd"))) {
	    if(arg == "who") return who_list(me);
        
	    if(arg == "quit") {
	        IM_D->send_command(me->query_temp("im_fd"),"QUIT\r\n");
	        me->delete_temp("im_fd");
            write("\n[IM Message]:即時通訊精靈離線了。\n");
	        return 1;
	    }
        
	    if(sscanf(arg,"tell %s %s",who,msg) == 2)
	        return IM_D->process_send_msg(me,who,msg);
        
        if(arg == "register msn") return register(me,"MSN");
        if(arg == "register yahoo") return register(me,"YAHOO");
        
        if(sscanf(arg,"add %s %s",who,msg) == 2)
        {
            if(who != "msn" && who != "yahoo")
                return notify_fail("\n[IM Message]:目前只能加入 msn 或是 yahoo 的好友名單。\n");
            IM_D->send_command(me->query_temp("im_fd"),
                               "PRIVMSG #bitlbee :add "+who+" "+msg);
            write("\n[IM Message]:你把 "+msg +" 加入你的 "+who +" 好友名單。\n");
            return 1;
        }
        if(sscanf(arg,"remove %s",who) == 1)
        {
            int fd = me->query_temp("im_fd");
            if(!undefinedp(IM_D->query_users()[fd]["list"])
                && !undefinedp(IM_D->query_users()[fd]["list"][who]))
            {
                IM_D->send_command(fd,
                                   "PRIVMSG #bitlbee :remove "+who);
                return notify_fail("\n[IM Message]:你把 "+who +" 從你的好友名單刪除。\n");
            }
            return notify_fail("\n[IM Message]:沒有這個人哦！\n");
            return 1;
        }

                
        if(arg == "yes") 
        {
            IM_D->send_command(me->query_temp("im_fd"),
                                      "PRIVMSG #bitlbee : yes");
            write("\n[IM Message]:你同意他把你加入他的好友名單。\n");
            return 1;
        }
        if(arg == "no")
        {
            IM_D->send_command(me->query_temp("im_fd"),
                               "PRIVMSG #bitlbee : no");
            write("\n[IM Message]:你不同意他加你進入他的好友名單。\n");
            return 1;
        }
        if(sscanf(arg,"nick %s",msg))
        {
            write("\n[IM Message]:你將名字改為："+msg+"。\n");
            IM_D->send_command(me->query_temp("im_fd"),
                               "PRIVMSG #bitlbee :nick msn \""+msg+"\"");
            return 1;
        }
        write("\n[IM Message]:沒有這項功能哦。\n");
    }
     else return notify_fail("你並沒有登入\n");
    return 1;
}
int who_list(object me)
{
    mapping map = IM_D->query_users();
    printf("好友名單列表：\n");
    
    foreach(int fd,mapping m in map)
    {
        if(m["obj"] == me && me->query("id") == m["id"] )
        {
            foreach(string k,string* v in m["list"])
            {
                if(v[2] == m["id"] || v[2] == "root") continue;
                //({ id,ip,name,status,nick});
                printf("(%-4s)[%-10s] %-70s \n",v[3]=="G"?"離開":"線上",v[2],v[4]+"("+v[0]+"@"+v[1]+")");
            }
        }
    }
    return 1;
}
int register(object me,string pro)
{
    write("[IM Message] 請輸入你的 "+pro+" 帳號，或是按 . 取消:");
    input_to("register_step1",me, pro);
    return 1;
}
int register_step1(string arg,object me,string pro)
{
    if(arg[0] == '.') 
    {
        write("[IM Message] 取消設定。\n");
        return 1;
    }
    if(strwidth(arg) < 5) 
    {
        write("[IM Message] 請輸入你的 "+pro+" 帳號，或是按 . 取消:");
        input_to("register_step1",me,pro);
    }
    write("[IM Message] 請輸入你的 "+pro+" 密碼，或是按 . 取消:");
    input_to("register_step2",me,pro,arg);
}
int register_step2(string arg,object me,string pro,string account)
{
    if(arg[0] == '.') 
    {
        write("[IM Message] 取消設定。\n");
        return 1;
    }
    if(strwidth(arg) < 5) 
    {
        write("[IM Message] 請輸入你的 "+pro+" 密碼，或是按 . 取消:");
        input_to("register_step2",me,pro,account);
    }
    IM_D->del_account(me->query_temp("im_fd"),pro);
    IM_D->register_account(me->query_temp("im_fd"),pro,account,arg);
    write("[IM Message] "+pro+" 帳號新增或修改完畢。\n");
}
int help(object me)
{
    write(@HELP
指令格式 : im [各項參數]
            
    這個指令可以讓你登入網路上流行的即時通訊軟體。目前支援的         
即時通訊軟體有 MSN 、 YAHOO 這二項。

    不管你是第幾次使用，要使用 im 時，必需先打 im login 作
登入的動作。

    因為網路傳輸的關系，有些訊息可能會延遲一些時間才會收到。
     
     im login           - 登入 im 系統。
     im quit            - 登出 im 系統。
     im who             - 列出你的好友名單。
     im register msn    - 註冊 msn 帳號。
     im register yahoo  - 註冊 yahoo 帳號。
     im add <protocol> <account> - 新增好友。
     im remove <account>- 移除好友。
     im no              - 不同意他人把你加入好友名單。
     im yes             - 同意他人把你加入好友名單。
     im nick <nick>     - 修改 msn 的暱稱。
     im tell <id> <msg> - 傳訊給某人。
HELP
         );
    return 1;
}

