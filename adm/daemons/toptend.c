// modify by chui
// modify by seagate@pkuxkx 2011/04/18
// modified by zine@pkuxkx 2013/2/10 美化一下显示
// 1.从文件存储结构修改为mapping存储结构
// 2.增加排行榜头衔的授予
// 3.对财富的计量单位采用新计量单位金块，1金块=100黄金
// 4.增加排行榜-combat（宗师）排行榜
// 5.标准化get_score算法，paihang命令和top命令算法统一
// by 2011/04/20
// 1.增加了排行榜持有时间概念，对于排名在2-10内变动持有时间不变，
//   当从2-10变动到第一名或者从第一名变动到2-10或者新加入排名的
//   玩家排行榜持有时间会变化。
// 2.对配置表进行了标准化，topten_desc作为统一的排行榜配置参数表
// by 2011/04/25
// 1.增加排行榜score，修正了age的算法。
// 2.rm_prev_logs函数支持对某一种排行榜进行清理。
// 3.头衔获得顺序先天下第一头衔，后江湖第十头衔。
// by 2011/04/28
// 修正了函数topten_del中当找到删除目标时候忘记更新排名的bug，并且
// 对历史问题进行弥补。

#include <ansi.h>
#include <mudlib.h>
#include <title.h>
inherit F_SAVE;

//排行榜配置表，其中name为排行榜名称，color为排行榜显示的颜色配置，caltype支持function，attribute，expression三种形式，
//分别对应函数、属性、表达式三种取值方式，calexpr为表达式，当类型为函数时存放函数名，类型为属性时，放属性名，类型为
//表达式的时候，存放表达式（其中属性用$$**$$括起来。），titlecolor1为十大排名的头衔颜色，titlecolor2为第一名的头衔颜色，
//showdata为显示的数值，如果不存在该属性则默认%d格式显示。

//  "level":(["name":"等级高手", "color": ({YEL, MAG, GRN}), "caltype": "attribute", "calexpr": "level",
//           "titlecolor1":({RED, BLU, HIC}), "titlecolor2":({HIR, HIB, HIC}), "showdata": "%d级"]),
nosave mapping topten_desc=
([
  "rich":(["name":"富豪", "color": ({HIY, MAG, HIG}), "caltype": "function", "calexpr": "total_golds", 
  	       "titlecolor1":({BLU, GRN, HIY}), "titlecolor2":({HIB, HIG, HIY}), "showdata": "%d根金条"]),
  "pker":(["name":"杀手", "color": ({RED, BLU, MAG}), "caltype": "attribute", "calexpr": "PKS",
           "titlecolor1":({MAG, YEL, HIR}), "titlecolor2":({HIM, HIY, HIR}), "showdata": "杀%d人"]),
  "exp":(["name":"高手", "color": ({GRN, YEL, CYN}), "caltype": "function", "calexpr": "get_combatexp",
           "titlecolor1":({RED, BLU, HIC}), "titlecolor2":({HIR, HIB, HIC}), "showdata": "%d点积分"]),
  "age":(["name":"老手", "color": ({CYN, YEL, WHT}), "caltype": "attribute", "calexpr": "age",
           "titlecolor1":({YEL, CYN, HIW}), "titlecolor2":({HIY, HIC, HIW}), "showdata": "%d岁"]),
  "beauty":(["name":HIR+"美女"BLU, "color": ({BLU, MAG, CYN}), "caltype": "expression", "calexpr": "$$per$$-$$age$$/5+8",
           "titlecolor1":({GRN, HIY, HIM}), "titlecolor2":({HIG, HIY, HIM}), "showdata": "%d点容貌值"]),
  "handsome":(["name":HIC"帅哥"MAG, "color": ({MAG, HIC, CYN}), "caltype": "expression", "calexpr": "$$per$$-$$age$$/10+4",
           "titlecolor1":({YEL, HIW, HIC}), "titlecolor2":({HIY, HIW, HIC}), "showdata": "%d点容貌值"]),
  "repute":(["name":"名宿", "color": ({HIW, HIC, HIY}), "caltype": "attribute", "calexpr": "repute",
           "titlecolor1":({CYN, WHT, HIB}), "titlecolor2":({HIC, HIW, HIB})]),
  "combat":(["name":"宗师", "color": ({HIG, HIY, HIC}), "caltype": "function", "calexpr": "get_score",
           "titlecolor1":({MAG, BLU, HIG}), "titlecolor2":({HIM, HIB, HIG}), "showdata": "%d点评价值"]),
  "badrp":(["name":"衰神", "color": ({YEL, MAG, GRN}), "caltype": "attribute", "calexpr": "badrp",
           "titlecolor1":({WHT, RED, YEL}), "titlecolor2":({HIW, HIR, YEL})]),
  "petkiller":(["name":"宠物杀手", "color": ({YEL, MAG, GRN}), "caltype": "attribute", "calexpr": "PetKills",
           "titlecolor1":({MAG, YEL, HIR}), "titlecolor2":({HIM, HIY, HIR}), "showdata": "杀%d宠物"]),
  "neili":(["name":"内力高手", "color": ({YEL, MAG, GRN}), "caltype": "attribute", "calexpr": "max_neili",
           "titlecolor1":({RED, BLU, HIC}), "titlecolor2":({HIR, HIB, HIC})]),
  "qixue":(["name":"气血高手", "color": ({YEL, MAG, GRN}), "caltype": "attribute", "calexpr": "eff_qi",
           "titlecolor1":({RED, BLU, HIC}), "titlecolor2":({HIR, HIB, HIC})]),
  "jingshen":(["name":"精神高手", "color": ({YEL, MAG, GRN}), "caltype": "attribute", "calexpr": "eff_jing",
           "titlecolor1":({RED, BLU, HIC}), "titlecolor2":({HIR, HIB, HIC})]),
  "jingli":(["name":"精力高手", "color": ({YEL, MAG, GRN}), "caltype": "attribute", "calexpr": "max_jingli",
           "titlecolor1":({RED, BLU, HIC}), "titlecolor2":({HIR, HIB, HIC})]),
  "score":(["name":"义士", "color": ({HIY, GRN, CYN}), "caltype": "attribute", "calexpr": "score",
           "titlecolor1":({MAG, CYN, HIY}), "titlecolor2":({HIM, HIC, HIY})]),
  "jobscore":(["name":"任务高手", "color": ({HIY, GRN, CYN}), "caltype": "function", "calexpr": "job_score",
           "titlecolor1":({MAG, CYN, HIY}), "titlecolor2":({HIM, HIC, HIY})]),
  "fullme":(["name":"沉迷者", "color": ({HIW, GRN, CYN}), "caltype": "function", "calexpr": "fullme_time",
           "titlecolor1":({WHT, CYN, HIY}), "titlecolor2":({HIW, HIC, HIY}), "showdata": "%d分钟"])
]); //如果再新加排行榜内容，"name"的键值最好不要超过4个字，目前按4个字以内做了美化对齐，Zine

//存放每个排行榜的具体数据，具体数据为mapping阵列，内涵paiming，name，id，data, time五个键字。
//其中time为玩家持有该排名的起始时间。
mapping topten_data;

nosave int paiming;
nosave mapping top_buffer;
void topten_checkplayer(object);
int topten_del(string,string);
int topten_add(object,string);
string topten_query(string);
varargs int rm_prev_logs(string);
int how_many_money(object);
int job_score(string);
protected int total_golds(object);
protected string get_name(string);
protected int check_topten(string, string);
protected int get_toptime(string, string);
protected int get_timebypm(string, int);
protected int get_all_data(object,string);
protected int max_sklevel(object, string *);
protected string expr_replace(string, object);
protected int n_exp_cal(int *,string *);

string query_save_file()
{
    return "/data/toptend";
}

void create()
{
    seteuid(getuid());
    restore();
}

mapping *query_topten(string type)
{
	return topten_data[type];
}

varargs int rm_prev_logs(string type)
{
        if ( !type )
          topten_data=([]);
        else
        	map_delete(topten_data, type);
        return save();
}

void topten_checkplayer(object player)
{
        int pm, lp, timebypm;
        string *top_type;
        mapping t_topdesc;

        paiming=0;
        player->set_title(({TITLE_TOP1, TITLE_TOP2, TITLE_TOP3, TITLE_TOP4, TITLE_TOP5, 
         	                  TITLE_TOP6, TITLE_TOP7, TITLE_TOP8, TITLE_TOP9, TITLE_TOP10}));
        top_type=keys(topten_desc);
        for(lp=0;lp<sizeof(top_type);lp++)
        {
          if (top_type[lp]=="fullme") continue;
          t_topdesc=topten_desc[top_type[lp]];
          timebypm = get_timebypm(top_type[lp],10);
          if(topten_add(player, top_type[lp]) && !sizeof(top_buffer) && timebypm>0 && time()-timebypm > 3600) 
              CHANNEL_D->do_channel(this_object(), "rumor", player->query("name")+"进入了十大"+NOR+t_topdesc["titlecolor2"][2]+get_name(t_topdesc["name"])+NOR+HIM+"爬行榜！"+NOR);
          pm=check_topten(player->query("id"), top_type[lp]);
          if ( pm==1 )
          	player->set_title(({TITLE_TOP1, TITLE_TOP2, TITLE_TOP3, TITLE_TOP4, TITLE_TOP5, 
         	                      TITLE_TOP6, TITLE_TOP7, TITLE_TOP8, TITLE_TOP9, TITLE_TOP10}), 
         	                    t_topdesc["titlecolor2"][0]+"天下"+t_topdesc["titlecolor2"][1]+"第一"+t_topdesc["titlecolor2"][2]+get_name(t_topdesc["name"])+NOR,
         	                    0, get_toptime(player->query("id"), top_type[lp]));
          if ( pm>1 )
          	player->set_title(({TITLE_TOP1, TITLE_TOP2, TITLE_TOP3, TITLE_TOP4, TITLE_TOP5, 
         	                      TITLE_TOP6, TITLE_TOP7, TITLE_TOP8, TITLE_TOP9, TITLE_TOP10}), 
         	                    t_topdesc["titlecolor1"][0]+"江湖"+t_topdesc["titlecolor1"][1]+"十大"+t_topdesc["titlecolor1"][2]+get_name(t_topdesc["name"])+NOR,
         	                    0, get_toptime(player->query("id"), top_type[lp]));
        }
        return;
}

void topten_checkonetype(object player, string type)
{
        int pm, timebypm;
        mapping t_topdesc;
        string *ty, *tv;
        int i;

        paiming=0;
        // player->set_title(({TITLE_TOP1, TITLE_TOP2, TITLE_TOP3, TITLE_TOP4, TITLE_TOP5, 
        // 	                  TITLE_TOP6, TITLE_TOP7, TITLE_TOP8, TITLE_TOP9, TITLE_TOP10}));

        // 先清空玩家原有type项的title
        ty = keys(player->list_title());
        tv = values(player->list_title());
        for (i=0;i<sizeof(ty);i++)
        {
            if (strsrch(tv[i],topten_desc[type]["name"])!=-1)
            {
                player->set_title(ty[i]);
            }
        }

        t_topdesc=topten_desc[type];
        timebypm = get_timebypm(type,10);
        // if(topten_add(player, type) && !sizeof(top_buffer) && timebypm>0 && time()-timebypm > 3600) 
        //  CHANNEL_D->do_channel(this_object(), "rumor", player->query("name")+"进入了十大"+NOR+t_topdesc["titlecolor2"][2]+get_name(t_topdesc["name"])+NOR+HIM+"爬行榜！"+NOR);
        topten_add(player, type);
        pm=check_topten(player->query("id"), type);
        if (type=="fullme") return;
        if ( pm==1 )
        player->set_title(({TITLE_TOP1, TITLE_TOP2, TITLE_TOP3, TITLE_TOP4, TITLE_TOP5, 
                              TITLE_TOP6, TITLE_TOP7, TITLE_TOP8, TITLE_TOP9, TITLE_TOP10}), 
                            t_topdesc["titlecolor2"][0]+"天下"+t_topdesc["titlecolor2"][1]+"第一"+t_topdesc["titlecolor2"][2]+get_name(t_topdesc["name"])+NOR,
                            0, get_toptime(player->query("id"), type));
        if ( pm>1 )
        player->set_title(({TITLE_TOP1, TITLE_TOP2, TITLE_TOP3, TITLE_TOP4, TITLE_TOP5, 
                              TITLE_TOP6, TITLE_TOP7, TITLE_TOP8, TITLE_TOP9, TITLE_TOP10}), 
                            t_topdesc["titlecolor1"][0]+"江湖"+t_topdesc["titlecolor1"][1]+"十大"+t_topdesc["titlecolor1"][2]+get_name(t_topdesc["name"])+NOR,
                            0, get_toptime(player->query("id"), type));
        
        return;
}

string topten_query(string type)
{
        string str,title,name,id,score,ctime,*showcolor;
        int i,data,itime;
        mapping mod_topshow=          	
         (["top":"    ΩΩΩΩΩΩΩΩΩΩΩ=  北大侠客行十大%%%爬行榜  =ΩΩΩΩΩΩΩΩΩΩΩ\n"NOR,
           "bottom":"    ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ\n"NOR,
           "middle":"    ＄                                                                          ＄\n"NOR,
           "left":"    ＄ ",
           "right":"＄\n"NOR]);
        
        if ( !topten_desc[type] )        
          return "对不起，暂时没有这种排行榜！\n";

        if ( !sizeof(topten_data) || !sizeof(topten_data[type]) )
        	return "对不起，该排行榜目前还没有一个高手出现。\n";

        showcolor=topten_desc[type]["color"];
        str="\n"+showcolor[0]+replace_string(mod_topshow["top"],"%%%", sprintf("%|8s",topten_desc[type]["name"]))+NOR+showcolor[0]+mod_topshow["middle"];
		str=replace_string(str,topten_desc[type]["name"],U+showcolor[0]+topten_desc[type]["name"]+NOR+showcolor[0]);
        paiming=0;
        for(i=0;i<sizeof(topten_data[type])&&paiming<=topten_data[type][sizeof(topten_data[type])-1]["paiming"];i++)
        {
        	if ( i && topten_data[type][i]["paiming"]==topten_data[type][i-1]["paiming"] )
        		title ="并列第"+chinese_number(topten_data[type][i]["paiming"])+":";
        	else
            {
        		title ="排行第"+chinese_number(topten_data[type][i]["paiming"])+"：";
                paiming++;
            }
        	name=topten_data[type][i]["name"];
        	id=topten_data[type][i]["id"];
        	data=topten_data[type][i]["data"];
        	if ( !topten_data[type][i]["time"] )
        		topten_data[type][i]["time"]=time();
        	itime=time()-topten_data[type][i]["time"];
        	if ( itime<60 )
        		ctime=sprintf("%d秒", itime);
        	else if ( itime<60*60)
        		ctime=sprintf("%d分", itime/60);
        	else if ( itime<60*60*24)
        		ctime=sprintf("%d小时", itime/(60*60));
        	else if ( itime<60*60*24*30)
        		ctime=sprintf("%d天", itime/(60*60*24));
        	else if ( itime<60*60*24*30*25)
        		ctime=sprintf("%d月", itime/(60*60*24*30));
        	else
        		ctime=sprintf("%d年", itime/(60*60*24*365));

          score=sprintf("%d", data);
	        if (type == "repute")
	        {
	              if  (data>1000000)
		                    score = sprintf("%dM 武林声望",data/1000000);
		            else if (data>1000)
		                    score = sprintf("%dK 武林声望",data/1000);
		            else
		                    score = sprintf("%d点武林声望",data);
		      }
		      else if ( topten_desc[type]["showdata"] )
		      	score=sprintf(topten_desc[type]["showdata"], data);
		      
          str += showcolor[0] + mod_topshow["left"] + NOR +
                    sprintf("%16s %-24s%-18s(%-12s)", title, name+"("+id+")", score, ctime)+NOR+
                    showcolor[0]+mod_topshow["right"];
		  str=replace_string(str,title,NOR+showcolor[1]+title);
		  str=replace_string(str,name,NOR+showcolor[2]+name);
		  // str=replace_string(str,ctime,ctime+NOR);
        }
        str+=showcolor[0]+mod_topshow["middle"];
        str+=showcolor[0]+mod_topshow["bottom"];
        return str;
}

int topten_del(string pid,string type)
{
        mapping *top_list;
        int i,j,pm, mark;
        string *dels;
        
        top_buffer=([]);        
        dels=({});
        if(!topten_data[type])
        	return notify_fail(topten_desc[type]+"还没有创建！\n");
        
        for(i=0;i<sizeof(topten_data[type]);i++)
        {
                if(topten_data[type][i]["id"]==pid)//player的id检核，相同则进入删除程序
                {
						if(time()-topten_data[type][i]["uptime"]<3600&&topten_data[type][i]["data"]) return 0;
                        top_list=({});
                        top_buffer+=topten_data[type][i];
						pm=topten_data[type][0]["paiming"];
                        mark=0;
                        for(j=0;j<sizeof(topten_data[type]);j++)
                        {
                        	if ( j==i )
                        	{
                        		pm=topten_data[type][j]["paiming"];
                        		continue;
                        	}
                        	else
                        	{
                        		if ( j>i && 
                        			   topten_data[type][j]["paiming"]>pm )
                        			topten_data[type][j]["paiming"]--;
                        		else if ( j>i && j==i+1 && i>0 &&
                        			   topten_data[type][j]["data"]<topten_data[type][i-1]["data"] &&
                        			   topten_data[type][j]["paiming"]==topten_data[type][i-1]["paiming"] )
                        		{
                        			topten_data[type][j]["paiming"]++;
                        			mark=1;
                        		}
                        	  else if ( j<i && j>0 && 
                        		   topten_data[type][j]["data"]<topten_data[type][j-1]["data"] &&
                        		   topten_data[type][j]["paiming"]==topten_data[type][j-1]["paiming"] )
                        	  {
                        	  	topten_data[type][j]["paiming"]++;
                        	  	mark=1;
                        	  }
                        		else if ( mark )
                        			topten_data[type][j]["paiming"]++;
                        		top_list+=({topten_data[type][j]});
                        		pm=topten_data[type][j]["paiming"];
                        	}
                        }
                        topten_data[type]=({})+top_list;
                        save();
                }
                else if ( time()-topten_data[type][i]["uptime"]>=90*24*3600 )
                	dels+=({topten_data[type][i]["id"]});
        }

//3个月没有登录的玩家从exp排行榜中删除
       	for(i=0;i<sizeof(dels);i++)
       		topten_del(dels[i], type);
       		
        return 1;
}

int topten_add(object player,string type)
{
        int i,j,data;
        mapping *top_list;
        
        if(wizardp(player))//禁止巫师参加排行榜
                return 0;
  
        if ((int)player->query("env/invis"))
                return 0;
        
        if (player->query("no_top")>=1)
                return 0;
       
        if ( !topten_desc[type] )
          return notify_fail("对不起，暂时没有这种排行榜！\n");
          
        if(!objectp(player)||!userp(player))
                return 0;

        if (type == "beauty" && player->query("gender")!="女性")
                return 0;

        if (type == "handsome" && player->query("gender") =="女性")
                return 0;

        //主要程序！
        if(get_all_data(player,type)==-1)
                return notify_fail("数据查询错误，可能是查询类型错误！\n");

        //当排行榜第一次使用时
        if ( !sizeof(topten_data) && get_all_data(player,type) )
        {
        	topten_data=([]);
        	topten_data[type]=({(["paiming":1, 
        		                    "name": get_name(player->query("name")), 
        		                    "id": player->query("id"),
        		                    "data": get_all_data(player,type),
        		                    "time": time(),
        		                    "uptime": time()])});
          return save();
        }
        //当该类型排行榜第一次使用时
        else if ( !sizeof(topten_data[type]) && get_all_data(player,type) )
        {
        	topten_data[type]=({(["paiming":1, 
        		                    "name": get_name(player->query("name")), 
        		                    "id": player->query("id"),
        		                    "data": get_all_data(player,type),
        		                    "time": time(),
        		                    "uptime": time()])});
          return save();
        }
        
        if (!sizeof(topten_data) || !sizeof(topten_data[type]))
        {
            return 0;
        }

        //应该先排除该player的id!
        if(!topten_del(player->query("id"),type)) return 0;

        //关键词为零，不记入排行。
        if(get_all_data(player,type)==0)return 0;
        else data=get_all_data(player,type);

        for(i=0; i<sizeof(topten_data[type]); i++)
        {
                if ( data>topten_data[type][i]["data"] )
                {
                        top_list=({});
                        for(j=0;j<sizeof(topten_data[type]);j++)
                        {
                        	if (j==i)
                        	{
//在排名相同或者2-10排名之内流动的时候排名持有时间不变，否则排名持有时间重新计算。
                        		if ( top_buffer && 
                        		     top_buffer["id"]==player->query("id") &&
                        		     ( ( topten_data[type][j]["paiming"]>1 &&
                        		         top_buffer["paiming"]>1 ) ||
                        		       ( topten_data[type][j]["paiming"] == top_buffer["paiming"] ) ) )
                        		  top_list+=({(["paiming":topten_data[type][j]["paiming"],
                        		                "name":get_name(player->query("name")),
                        		                "id":player->query("id"),
                        		                "data":data,
                        		                "time":top_buffer["time"],
        		                                "uptime": time()])});
                        	  else
                        		  top_list+=({(["paiming":topten_data[type][j]["paiming"],
                        		                "name":get_name(player->query("name")),
                        		                "id":player->query("id"),
                        		                "data":data,
                        		                "time":time(),
        		                                "uptime": time()])});
                        	  topten_data[type][j]["paiming"]++;
                        	  if(topten_data[type][j]["paiming"]>10)
                        	  {
                        	  	topten_data[type]=({})+top_list;
                        	  	return save();
                        	  }
                        	  else
                        	  	top_list+=({topten_data[type][j]});
                        	}
                        	else if (j<i)
                        	  top_list+=({topten_data[type][j]});
                        	else
                        	{
                        		topten_data[type][j]["paiming"]++;
                        		if(topten_data[type][j]["paiming"]>10)
                        	  {
                        	  	topten_data[type]=({})+top_list;
                        	  	return save();
                        	  }
                        	  else
                        	  	top_list+=({topten_data[type][j]});
                        	}
                        }
                        topten_data[type]=({})+top_list;
                        return save();
                }
                else if ( data==topten_data[type][i]["data"] )
                {
                	if ( i<sizeof(topten_data[type])-1 &&
                		   data==topten_data[type][i+1]["data"] )
                	      continue;
                	else
                	{
                	    top_list=({});
                        for(j=0;j<sizeof(topten_data[type]);j++)
                        {
                        	if( j==i )
                        	{
                        		top_list+=({topten_data[type][j]});
//在排名相同或者2-10排名之内流动的时候排名持有时间不变，否则排名持有时间重新计算。
                        		if ( top_buffer && 
                        		     top_buffer["id"]==player->query("id") &&
                        		     ( ( topten_data[type][j]["paiming"]>1 &&
                        		         top_buffer["paiming"]>1 ) ||
                        		       ( topten_data[type][j]["paiming"] == top_buffer["paiming"] ) ) )
                              top_list+=({(["paiming":topten_data[type][j]["paiming"],
                        		                "name":get_name(player->query("name")),
                        		                "id":player->query("id"),
                        		                "data":data,
                        		                "time":top_buffer["time"],
        		                                "uptime": time()])});
                        		else
                        		  top_list+=({(["paiming":topten_data[type][j]["paiming"],
                        		                "name":get_name(player->query("name")),
                        		                "id":player->query("id"),
                        		                "data":data,
                        		                "time":time(),
        		                                "uptime": time()])});
                        	}
                        	else if ( j<i )
                        		top_list+=({topten_data[type][j]});
                        	else
                        	{
                        		topten_data[type][j]["paiming"]++;
                        		if(topten_data[type][j]["paiming"]>10)
                        	  {
                        	  	topten_data[type]=({})+top_list;
                        	  	return save();
                        	  }
                        	  else
                        	  	top_list+=({topten_data[type][j]});
                        	}
                        }
                        topten_data[type]=({})+top_list;
                        return save();
                    }
                }
        }
//该玩家数值比排行榜中都低并且排行榜没满在后尾追加。
        if ( sizeof(topten_data[type])<10 )
        {
//在排名相同或者2-10排名之内流动的时候排名持有时间不变，否则排名持有时间重新计算。
                if ( top_buffer && 
                     top_buffer["id"]==player->query("id") &&
                     top_buffer["paiming"]>1 )
                  topten_data[type]+=({(["paiming":sizeof(topten_data[type])+1,
                          		           "name":get_name(player->query("name")),
                          		           "id":player->query("id"),
                          		           "data":data,
                          		           "time":top_buffer["time"],
        		                             "uptime": time()])});
                else
                  topten_data[type]+=({(["paiming":sizeof(topten_data[type])+1,
                          		           "name":get_name(player->query("name")),
                          		           "id":player->query("id"),
                          		           "data":data,
                          		           "time":time(),
        		                             "uptime": time()])});
                return save();
        }
        return 0;
}

//个人综合评价值 
int get_score(object player)
{
	int skill_score, att_score, char_score;
	
	skill_score=player->query_skill("force")+player->query_skill("dodge");
	skill_score+=max_sklevel(player, ({"unarmed", "finger", "cuff", "strike", "hand", "claw"}));
	skill_score+=max_sklevel(player, ({"sword", "blade", "whip", "spear", "axe", 
		                                 "halberd", "throwing", "staff", "dagger", "hammer", 
		                                 "club" }) );
  if ( player->query_skill("qiankun-danuoyi", 1) )
  	skill_score+=player->query_skill("qiankun-danuoyi", 1);
  else if ( player->query_skill("jingang-buhai", 1) ||
  	        player->query_skill("douzhuan-xingyi", 1) )
  {
  	skill_score+=player->query_skill("jingang-buhai", 1)/4;
  	skill_score+=player->query_skill("douzhuan-xingyi", 1)/4;
  }
  
  att_score=player->query("max_neili")/50+player->query("max_qixue")/200+player->query("max_jingshen")/1000;
  att_score+=to_int(pow(to_float(player->query("combat_exp"))*10,0.3333))*10;
  
  char_score=player->query_str()/2 + player->query_dex()/6;
  char_score-=player->query_temp("apply/strength")/3;
  char_score-=player->query_temp("apply/dexerity")/9;
  
  return char_score*(att_score+skill_score)/10;
}
//jobscore Zine 添加
int job_score(object ob)
{
	return to_int("/cmds/usr/jobscore.c"->cal_score(ob)); 
}
//对外提供非金块的货币数量用
int how_many_money(object ob)
{
        int total;
        int total2;
        object gold,silver,coin,cash;
        total = 0;
        total2 = 0;                  
        gold   = present("gold",ob);
        silver = present("silver",ob);
        coin   = present("coin",ob);
        cash   = present("thousand-cash",ob);
        if( gold ) total += gold->value();
        if( silver ) total += silver->value();
        if( coin ) total += coin->value();
        if(cash) total += cash->value();
        total2 = (int)ob->query("balance");
        if (!total2 || total2 < 0)
                ob->set("balance", 0);
        total=total+total2;
        return total;
}

//算术表达式计算，仅支持+-*/四种运算法则
int expr_calculate(string expr)
{
	int *expr_loc,lp,result,*vals;
	string *expr_val, buf;
	
	expr_loc=({});
	expr_val=({});
	if ( !expr )
		return 0;
	buf=replace_string(expr," ","");
	for(lp=0;lp<strwidth(buf);lp++)
	{
		if (buf[lp]=='+' ||
			  buf[lp]=='-' ||
			  buf[lp]=='*' ||
			  buf[lp]=='/')
		{
			expr_loc+=({lp});
			expr_val+=({buf[lp..lp]});
		}
	}
//只有一个值的时候直接处理
	if ( !sizeof(expr_loc) )
	{
		if ( sscanf(buf, "%d", result)!=1 )
			return 0;
		else
			return result;
	}

	vals=allocate(sizeof(expr_loc)+1);
	for(lp=0;lp<sizeof(expr_loc);lp++)
	{
		if ( lp<sizeof(expr_loc)-1 && sscanf(buf, "%d"+expr_val[lp]+"%s", vals[lp], buf) != 2)
			return 0;
		else if (lp==sizeof(expr_loc)-1 && sscanf(buf, "%d"+expr_val[lp]+"%d", vals[lp], vals[lp+1])!=2 )
			return 0;
  }
  
  result=n_exp_cal(vals,expr_val);
  return result;
}

protected int n_exp_cal(int *val,string *expr)
{
	int lp, result, nt, t1,t2,t3,t4;
	nt=-1;
	for(lp=0;lp<sizeof(expr);lp++)
	{
		if ( expr[lp]=="+" ||
			   expr[lp]=="-" )
		  continue;
		else if ( expr[lp]=="*" )
		{
			result=val[lp]*val[lp+1];
			nt=lp;
			break;
		}
		else if ( expr[lp]=="/" )
		{
			result=val[lp]/val[lp+1];
			nt=lp;
			break;
		}
	}
	if ( nt>=0 )
	{
		if ( !nt )
		{
			if ( sizeof(val)>2 )
			  result=n_exp_cal( ({result})+val[2..], expr[1..] );
			return result;
		}
		else if ( nt==sizeof(expr)-1 )
		{
			result=n_exp_cal( val[0..nt-1]+({result}), expr[0..nt-1] );
			return result;
		}
		else
		{
			result=n_exp_cal( val[0..nt-1]+({result})+val[nt+2..], expr[0..nt-1]+expr[nt+1..] );
			return result;
		}
	}
	result=val[0];
	for(lp=0;lp<sizeof(expr);lp++)
	{
		if ( expr[lp]=="+" )
			result=result+val[lp+1];
		else if ( expr[lp]=="-" )
			result=result-val[lp+1];
	}
	return result;
}

protected int max_sklevel(object player, string *skill)
{
	int lp,level;
	
	level=0;
	for(lp=0;lp<sizeof(skill);lp++)
	{
		if ( player->query_skill(skill[lp])>level )
			level=player->query_skill(skill[lp]);
	}
	return level;
}

protected int check_topten(string pid, string type)
{
	int i;
	
	if ( !topten_data || !topten_data[type] )
		return -1;

	for(i=0;i<sizeof(topten_data[type]);i++)
	{
		if(topten_data[type][i]["id"]==pid)
			return topten_data[type][i]["paiming"];
	}
	return -1;
}

protected int get_toptime(string pid, string type)
{
	int i;
	
	if ( !topten_data || !topten_data[type] )
		return -1;

	for(i=0;i<sizeof(topten_data[type]);i++)
	{
		if(topten_data[type][i]["id"]==pid)
		{
			if ( !topten_data[type][i]["time"] )
				topten_data[type][i]["time"]=time();
			return topten_data[type][i]["time"];
		}
	}
	return -1;
}

//获取最后一个排名的玩家进入排行榜的时间点
protected int get_timebypm(string type, int pm)
{
	int i;
	
	if ( !topten_data || !topten_data[type] )
		return -1;

	for(i=0;i<sizeof(topten_data[type])&&pm==sizeof(topten_data[type]);i++)
	{
        if ( topten_data[type][i]["paiming"]== pm ) 
            return topten_data[type][i]["time"];
	}
	return -1;
}

protected int get_all_data(object player,string type)
{
        int total;
        
        switch(topten_desc[type]["caltype"])
        {
                case "function":
                        total=call_other(this_object(), topten_desc[type]["calexpr"], player);
                        break;
                case "attribute":
                        total=player->query(topten_desc[type]["calexpr"]);
                        break;
                case "expression":
                        total=expr_calculate(expr_replace(topten_desc[type]["calexpr"], player));
                        break;
                default:
                        total=-1;//用-1标志类型出错！
        }
        return total;
}

protected string get_name(string str)
{
    string str1, str2;

    while(sscanf(str,"%s%*sm%s",str1,str2)==3)
 	     str=str1+str2;
    return str;
}

//内部计算以金块计价的货币数量用
protected int total_golds(object ob)
{
        int total;
        int total2;
        object gold,silver,coin,cash;
        total = 0;
        total2 = 0;                  
        gold   = present("gold",ob);
        silver = present("silver",ob);
        coin   = present("coin",ob);
        cash   = present("thousand-cash",ob);
        if( gold ) total += gold->value();
        if( silver ) total += silver->value();
        if( coin ) total += coin->value();
        if(cash) total += cash->value();
        total2 = (int)ob->query("balance");
        if (!total2 || total2 < 0)
                ob->set("balance", 0);
//以百两黄金开始起算财富排名
        total=(total+total2)/1000000;
//支持待开发的高级财富接口，以百两黄金为存储单位
        total=total+ob->query("advance_balance");
        return total;
}

//将表达式中的$$***$$形式的属性用具体玩家的属性值来替换
protected string expr_replace(string expr, object player)
{
  int len=strwidth(expr),lp,loc, loc2;
  string buf;
  
  if ( !len ) return "";
  loc=strsrch(expr, "$$");
  if ( loc>=0 )
  {
  	loc2=strsrch(expr[loc+2..],"$$");
    if ( loc2<0 )
  	  error("表达式"+expr+"中属性字段必须以$$开始，以$$结束。\n");
  	buf=replace_string(expr, expr[loc..loc+loc2+3], sprintf("%d",player->query(expr[loc+2..loc+loc2+1])));
  	buf=expr_replace(buf, player);
  }
  else
  	return expr;
  return buf;
}

protected int get_combatexp(object ob)
{
	int exp, preexp, level;
	mapping hexp;
	string *dlist;
	float point;
	int mvalue, now, mexp,lp,year,month;
	mixed *tm=localtime(time());
	
	exp=ob->query("combat_exp");
	level=ob->query("level");
	now=tm[5]*12 + tm[4] +1;
	if ( (hexp=ob->query("exp_hist") ) &&
		   mapp(hexp) )
	{
		dlist=sort_array(keys(hexp),1);
		preexp=0;
		point=0;
		for(lp=0;lp<sizeof(dlist);lp++)
		{
			if ( sscanf(dlist[lp],"%d-%d", year, month )==2 )
			{
				mvalue=year*12+month;
				mexp=hexp[dlist[lp]];
				point+=((mexp-preexp)*pow(0.9,now-mvalue))/100000;
				preexp=mexp;
			}
		}
		point+=((exp-mexp)*1.0)/100000;
	}
	else
	{
		point=(exp*1.0)/100000;
	}
	point+=level*10;
	if ( level>100 )
		point+=(level-100)*50;	
	return to_int(ceil(point));
}

protected int fullme_time(object player)
{
    int hours,duration;
    if (player->query("antirobot/first_activity_time")<=0 || player->query("antirobot/last_activity_time")<=0 ) return 0;
    duration = player->query("antirobot/last_activity_time")-player->query("antirobot/first_activity_time");
    if (duration<0) return 0;
    hours = duration/60;
    return hours;
}
