#include <ansi.h>
#include <net/socket.h>
#include <socket_err.h>
#define CH_D "/adm/daemons/channeld.c"
inherit F_DBASE;
protected mapping users=([]);
  
void create() 
{ 
	
	  return 0;
        seteuid(getuid()); 
        set("channel_id", "web精灵");
}
  
void read_callback(int fd,mixed val) {
	string str,from1,from2;
	if (mapp(users[fd]))
      if (users[fd]["user"] && userp(users[fd]["user"]))
		{
			if (users[fd]["type"]=="WIKI")
			{
				str = replace_string(COLOR_D->trans_color(val,0),"<!--",HIG+"\n=============================WIKI查询完毕（如果不想看到此类帮助信息，请set nowiki 1）\n"+NOR );
				str = replace_string(str,"无相关信息\n","无相关信息\n"+HIG+"=============================WIKI查询完毕（如果不想看到此类帮助信息，请set nowiki 1）\n"+NOR );
	        	if (users[fd]["wiki_result"]==0)
	        	{
	        		users[fd]["wiki_result"]=1;
	        		str = HIG"以下为北侠WIKI查询『" + HIY + users[fd]["user"]->query_temp("wiking") + HIG+ "』的结果：===============================================\n"NOR + str;
	        	}
				if (strsrch(str,"WIKI查询完毕") != -1)
				{
					users[fd]["user"]->delete_temp("wiking");
					if (random(10)==1)
						str = str + HIB + "更多信息请到北侠百科和北侠论坛查询。欢迎积极参与完善北侠百科，对修订北侠百科贡献较大的玩家巫师将给予奖励！\n" + NOR;
					if (random(7)==2)
						str = str + HIB + "一次查询多个关键词请在关键词之间加上“+”，比如“武当+道德”。\n" + NOR;
					if (random(10)==3)
						str = str + HIB + "由于wiki对中文支持不完善，查询可能并不精确，敬请谅解。\n" + NOR;
		           	tell_object (users[fd]["user"],str);
					users[fd]["user"]->delete_temp("wiking");
					map_delete(users,fd);
	        	} else tell_object (users[fd]["user"],str);
	        } else if (users[fd]["type"]=="IP")
	        {
	        	str = "IP地址" + users[fd]["arg"] + "来自" + val + "\n";
		        tell_object (users[fd]["user"],str);
				map_delete(users,fd);
	        } else if (users[fd]["type"]=="IPRecord")
	        {
	        	if (sscanf(val, "%s %s", from1, from2)!=2)
	        	{
	        		users[fd]["user"]->set_temp("ip_from/from1",val);
	        		users[fd]["user"]->set_temp("ip_from/from2","");
	        	}
	        	else {
	        		users[fd]["user"]->set_temp("ip_from/from1",from1);
	        		users[fd]["user"]->set_temp("ip_from/from2",from2);
	        	}
				map_delete(users,fd);
	        } else if (users[fd]["type"]=="PING")
	        {
		        tell_object (users[fd]["user"],val);
				map_delete(users,fd);	        	
	        }
		}
}

void write_callback(int fd) {
}

//http连接与其他连接不同，传输只有几秒，终止之后socket会自动close
//所以没有必要强制socket，除非链接已经持续了60秒，不自动关闭
void close_socket(int fd)
{
		if (users[fd])
		{
			if (users[fd]["user"] && userp(users[fd]["user"]))
			{
				if ( (users[fd]["user"]->query_temp("wiking")==users[fd]["arg"]) && ((time()-users[fd]["start_time"])>=60))
				{
#ifdef DEBUG              
					CH_D->do_channel(this_object(),"sys",sprintf("user:%O",users[fd]));
			        CH_D->do_channel(this_object(),"sys","close socket"+fd+"!");  
#endif
					tell_object (users[fd]["user"],HIG + "可能由于网络原因，本次查询已超时终止。\n" + NOR);
		        	socket_close(fd);
					users[fd]["user"]->delete_temp("wiking");
		        	map_delete(users,fd);
				}
			}
        }
}
void querystr(int fd,string strquery)
{
	int err;
	
	if (users[fd]["type"]=="WIKI")
		strquery = "GET /conv/wiki2mud.php?str="+strquery;
	if (users[fd]["type"] =="IP" || users[fd]["type"] =="IPRecord")
		strquery = "GET /conv/ip.php?ip="+strquery;
	if (users[fd]["type"]=="PING")
		strquery = "GET /conv/ping.php?ip="+strquery;
	
    err = socket_write(fd,"\r\n"+strquery+"\r\n");
#ifdef DEBUG              
	CH_D->do_channel(this_object(),"sys",sprintf("err%d",err));
	CH_D->do_channel(this_object(),"sys",sprintf("fd%d",fd));
	CH_D->do_channel(this_object(),"sys",strquery);
#endif	
}
string query_web(object user, string strquery, string type) 
{ 
        int fd,err;
        string strres,address;
        
				log_file("wiz/query_web",sprintf("%s query %s at %s\n",user->query("id"),strquery, ctime(time())));
        fd = socket_create(STREAM, "read_callback");
        if (fd < 0)
                return HIR+"socket创建失败， 请联系巫师。\n"+NOR;
		
		if (type == "WIKI" || type == "IP" || type == "IPRecord"|| type == "PING")
                    address = "114.112.188.112 80";
        
        err=socket_connect(fd,address,"read_callback","write_callback" );
	if (err<1)
        {
                close_socket(fd);
                return HIR+"socket连接失败，请联系巫师。\n"+NOR;        
        }
#ifdef DEBUG              
 	CH_D->do_channel(this_object(),"sys",sprintf("fd:%d",fd)); 
	CH_D->do_channel(this_object(),"sys",strquery);
#endif
	if (type == "WIKI")
	{
      users[fd] = allocate_mapping(5);
      users[fd]["user"] = user;
      users[fd]["arg"]=strquery;
      users[fd]["start_time"]=time();
      users[fd]["wiki_result"]=0;
      users[fd]["type"]="WIKI";
      call_out("close_socket",60,fd);
      strres = HIG+"查询北侠百科(wiki.pkuxkx.com)中，请稍候...\n"+NOR;
    }
    if (type == "IP")
	{
      users[fd] = allocate_mapping(4);
      users[fd]["user"] = user;
      users[fd]["arg"]=strquery;
      users[fd]["start_time"]=time();
      users[fd]["type"]="IP";
      strres = "";
    }    
    if (type == "IPRecord")
	{
      users[fd] = allocate_mapping(4);
      users[fd]["user"] = user;
      users[fd]["arg"]=strquery;
      users[fd]["start_time"]=time();
      users[fd]["type"]="IPRecord";
      strres = "";
    }    
    if (type == "PING")
	{
      users[fd] = allocate_mapping(4);
      users[fd]["user"] = user;
      users[fd]["arg"]=strquery;
      users[fd]["start_time"]=time();
      users[fd]["type"]="PING";
      strres = "正在检测北侠服务器到" + strquery + "的网络连接速度，请稍候几秒至半分钟，如果长时间不返回结果，则可能无法连接或域名不存在...\n";
    }    
	call_out("querystr",2,fd,strquery);
	return strres;
}
