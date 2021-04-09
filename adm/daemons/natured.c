// natured.c

#include <ansi.h>

#define TIME_TICK (time())

inherit F_DBASE;

nosave int current_day_phase,current_month;
mapping *day_phase;

string *month_desc = ({
	"「隆冬」: ",
	"「寒冬」: ",
	"「初春」: ",
	"「早春」: ",
	"「阳春」: ",
	"「初夏」: ",
	"「盛夏」: ",
	"「仲夏」: ",
	"「初秋」: ",
	"「高秋」: ",
	"「深秋」: ",
	"「初冬」: ",
});

string *weather_msg = ({
	"天空中万里无云",
	"几朵淡淡的云彩妆点著清朗的天空",
	"白云在天空中飘来飘去",
	"厚厚的云层堆积在天边",
	"天空中乌云密布",
});

mapping *read_table(string file);

void init_day_phase();
void jiang_shichou();
void check_zeroid();
void check_im_d();
string gametime();
void do_event1();
void do_event2();
void do_event3();
void do_event4();
void do_event5();
void do_event6();

void create()
{
	string get_month, get_day;
	mixed *local;
	seteuid( ROOT_UID );
	local = localtime(TIME_TICK);
        get_day = CHINESE_D->chinese_number(local[3]);
	get_month = CHINESE_D->chinese_number(local[4]+1);
        switch(get_month)
        {
                //spring weather
                case "三":
                case "四":
                case "五":
                     switch(random(3))
                     {
                        case 0:
                           day_phase = read_table("/adm/etc/nature/spring_rain");
                           break;
                        case 1:
                           day_phase = read_table("/adm/etc/nature/spring_sun");
                           break;
                        case 2:
                           day_phase = read_table("/adm/etc/nature/spring_wind");
                           break;
                     }
                     break;
                //summer weather
                case "六":
                case "七":
                case "八":
                     switch(random(3))
                     {
                        case 0:
                           day_phase = read_table("/adm/etc/nature/summer_rain");
                           break;
                        case 1:
                           day_phase = read_table("/adm/etc/nature/summer_sun");
                           break;
                        case 2:
                           day_phase = read_table("/adm/etc/nature/summer_wind");
                           break;
                     }
                     break;
                //autumn weather
                case "九":
                case "十":
                case "十一":
                     switch(random(3))
                     {
                        case 0:
                           day_phase = read_table("/adm/etc/nature/autumn_rain");
                           break;
                        case 1:
                           day_phase = read_table("/adm/etc/nature/autumn_sun");
                           break;
                        case 2:
                           day_phase = read_table("/adm/etc/nature/autumn_wind");
                           break;
                     }
                     break;
                //winter weather
              case "十二":
		case "二":
		     switch(random(3))
		     {
			case 0:
			   day_phase = read_table("/adm/etc/nature/winter_rain");
			   break;
			case 1:		
			   day_phase = read_table("/adm/etc/nature/winter_sun");
			   break;
			case 2:
			   day_phase = read_table("/adm/etc/nature/winter_wind");
			   break;
		     }
		case "一":
		        if(get_day=="一")
		      { day_phase = read_table("/adm/etc/nature/spring");break;}
		      else switch(random(3))
		     {
			case 0:
			   day_phase = read_table("/adm/etc/nature/winter_rain");
			   break;
			case 1:		
			   day_phase = read_table("/adm/etc/nature/winter_sun");
			   break;
			case 2:
			   day_phase = read_table("/adm/etc/nature/winter_wind");
			   break;
		     }

                     break;
                default:
                     day_phase = read_table("/adm/etc/nature/day_phase");
        }
          set("channel_id", "时空精灵");
	init_day_phase();
        // call_out("check_all",60);
}

void check_all()
{
	call_out("check_all_data",1);
        // call_out("check_all",60);
	return;
}
//检查玩家数据，防止bug
void check_all_data()
{
        object *usr;
        int i,j,money,exp,skill;
        mapping skills,skills_old;
	mixed *skl;
	
        usr = users();
	//icer added to record users money&exp&skill per minute to check if there were bugs on earning money or exp
        for (i=0; i < sizeof(usr); i++)
        {

                money = TOPTEN_D->how_many_money(usr[i]);
				exp = usr[i]->query("combat_exp");
                if (usr[i]->query_temp("last_money_checked") == 0)
                    	usr[i]->set_temp("last_money_checked",money);
                else  	{
                       	if ( (money - (int)usr[i]->query_temp("last_money_checked")) > 100000 )
                        	log_file("money.log", usr[i]->query("name") + "(" + usr[i]->query("id") + ")" + "于" + ctime(time()) + "在" + environment(usr[i])->query("short") + "(" + base_name(environment(usr[i])) + ")" + "金钱增加了" + (money - (int)usr[i]->query_temp("last_money_checked"))/10000 + "两黄金，现金加存款共计" + money/10000 + "两黄金。\n");

                       	if ( (money - (int)usr[i]->query_temp("last_money_checked")) < -200000 )
							log_file("money.log", usr[i]->query("name") + "(" + usr[i]->query("id") + ")" + "于" + ctime(time()) + "在" + environment(usr[i])->query("short") + "(" + base_name(environment(usr[i])) + ")" + "金钱减少了" + (money - (int)usr[i]->query_temp("last_money_checked"))/10000 + "两黄金，现金加存款共计" + money/10000 + "两黄金。\n");
                       	}
                usr[i]->set_temp("last_money_checked",money);
                if (usr[i]->query_temp("last_exp_checked") == 0)
                    	usr[i]->set_temp("last_exp_checked",exp);
                else  	{
                       	if ( (exp - (int)usr[i]->query_temp("last_exp_checked")) > 5000 )
                        log_file("exp.log", usr[i]->query("name") + "(" + usr[i]->query("id") + ")" + "于" + ctime(time()) + "在" + environment(usr[i])->query("short") + "(" + base_name(environment(usr[i])) + ")" + "经验增加了" + (exp - (int)usr[i]->query_temp("last_exp_checked")) + "点，现在经验" + exp + "点。\n");
                       }
               	usr[i]->set_temp("last_exp_checked",exp);
			
/*
               	skills = usr[i]->query_skills();
               	if (sizeof(skills) > 0)
		{
			if (usr[i]->query_temp("last_skill_checked") != 0)
			{
				skills_old = usr[i]->query_temp("last_skill_checked");
				skl = keys(skills);
				for (j=0;j<sizeof(skills);j++)
				{	
					skill = (int)(skills[skl[j]]) - (int)(skills_old[skl[j]]);
  							if ((skill>3) || usr[i]->query("id") == "olap")
						log_file("skill.log",usr[i]->name_id() + "于" + ctime(time()) + "在" + environment(usr[i])->query("short") + "(" + base_name(environment(usr[i])) + ")" + skl[j] + "增加了" + skill + "级，现在等级" + skills[skl[j]] + "级。\n");
				}
			}	
			else	skills_old = ([]);

			if (sizeof(skills_old) > 0)
			skl = keys(skills_old);
	       		for (j=sizeof(skills_old)-1;j>=0;j--)
	       			map_delete(skills_old,skl[j]);
			if (sizeof(skills) > 0)
			{
				skl = keys(skills);
				for (j=0;j<sizeof(skills);j++)
					skills_old += ([skl[j]:skills[skl[j]]]);
			}
	       		usr[i]->set_temp("last_skill_checked",skills_old);
		}
*/
	}
}

//icer added to reduce redundant link_obs
/*void check_zeroid()
{
        object *usr;
        int i, j, found;
        found = 1;

        while (found)
        {        
                found = 0;
                usr = users();
                for (i=0; i < sizeof(usr); i++)
                {
                        for (j=0; j < sizeof(usr); j++)
                        {
                                if (query_ip_name(usr[j]) == query_ip_name(usr[i]))
                                        if (!(usr[i] == usr[j]))
                                                if (usr[i]->query("id") == 0 )
                                                {       
                                                        destruct(usr[i]);
                                                        found = 1;
                                                        break;
                                                }
                                                else 
                                                if (usr[i]->query("id") == usr[j]->query("id"))
                                                {
                                                        if (usr[i]->query_temp("link_ob")==0)
                                                        {        
                                                                destruct(usr[i]);
                                                                found = 1;
                                                                break;
                                                        }       
                                                }
                        }
                        if (found)
                        break;
                }
        }

        call_out("check_zeroid",100);
     return;
}
*/

void init_day_phase()
{
	mixed *local;
	int i, t;

	// Get minutes of today.
	local = localtime(TIME_TICK);
	t = local[2] * 60 + local[1];		// hour * 60 + minutes

	// Find the day phase for now.
	for( i=0; i < sizeof(day_phase); i++)
		if( t >= day_phase[i]["length"] )
			t -= (int)day_phase[i]["length"];
		else
			break;

	current_day_phase = (i==0? sizeof(day_phase)-1: i - 1);
	current_month = local[4];
           
	// Since in our time scale, 1 minute == 1 second in RL, so we don't need
	// any conversion before using this number as call_out dalay, if you 


	// changed the time scale, be sure to convert it.

	call_out("update_day_phase",
		(int)day_phase[(current_day_phase+1) % sizeof(day_phase)]["length"] - t);
	//暂不考虑降世仇了。
//       call_out("jiang_shichou",86400);

}

string gametime()
{
    return CHINESE_D->chinese_date(time() );
}

void xiakeling()
{
	object zs;
	zs = find_object("/d/xiakedao/npc/zhangsan.c");
	if ( !zs )
		zs = new("/d/xiakedao/npc/zhangsan.c");
	zs->FaLing();
}
void do_event()
{
	if(random(15)==0) 
	{
		do_event6();
		return ;
	}
	switch (random(5)){
	case 0:
		do_event1();
		break;
	case 1:
		do_event2();
		break;
	case 2:
		do_event3();
		break;
	case 3:
		do_event4();
		break;
	case 4:
		do_event5();
		break;
	}
}

void do_event1()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一粒仙豆从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
		if(ob->name())
	{
         message_vision(HIW"仙豆不偏不倚，恰好砸在$N的脑袋上，$N被砸的头破血流，倒在地上。\n"NOR, ob);
        if( ob->query("eff_qi") * 4 > ob->query("max_qi") * 3 )
                ob->receive_wound("qi", ob->query("max_qi") * 3 / 4);
        else ob->unconcious();
          if( obj = new("/d/wizard/obj/xiandou.c") )
                obj->move(ob);
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被仙豆砸到了。\n");
	}
}

void do_event2()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一粒幸运星从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
		if(ob->name())
	{
         message_vision(MAG"幸运星不偏不倚，恰好落在$N的身上，$N感到浑身是力!\n"NOR, ob);
        ob->add("eff_qi",ob->query("max_qi"));
		ob->add("qi",ob->query("max_qi"));
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被幸运星砸到了。\n");
	}
}

void do_event3()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一颗小福星从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
		if(ob->name())
	{
         message_vision(MAG"小福星不偏不倚，恰好落在$N的身上，$N感到全身通泰!\n"NOR, ob);
        ob->add("eff_jing",ob->query("max_jing"));
		ob->add("jing",ob->query("max_jing"));
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被小福星砸到了。\n");
	}
}

void do_event4()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一颗天护星从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
		if(ob->name())
	{
         message_vision(MAG"天护星不偏不倚，恰好落在$N的身上，$N感到自己防御大增!\n"NOR, ob);
        ob->add_temp("apply/armor",100);
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被天护星砸到了。\n");
	}
}

void do_event5()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一颗天伤星从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
		if(ob->name())
	{
         message_vision(MAG"天伤星不偏不倚，恰好落在$N的身上，$N感到自己攻击大增!\n"NOR, ob);
        ob->add_temp("apply/damage",100);
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被天伤星砸到了。\n");
	}
}

void do_event6()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一本天书从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
		if(ob->name())
	{
         message_vision(HIW"天书不偏不倚，恰好砸在$N的脑袋上，$N被砸的头破血流，倒在地上。\n"NOR, ob);
        if( ob->query("eff_qi") * 4 > ob->query("max_qi") * 3 )
                ob->receive_wound("qi", ob->query("max_qi") * 3 / 4);
        else ob->unconcious();
//          if( obj = new("/d/private/obj/stone") )
                switch (random(4)){
		case 0:
			obj=new("/d/wizard/obj/kaitian_book.c");
			break;
		case 1:
			obj=new("/d/wizard/obj/tongbi_book.c");
			break;
		case 2:
			obj=new("/d/wizard/obj/lxmw_book.c");
			break;
		case 3:
			obj=new("/d/wizard/obj/guishoushe_book.c");
			break;
		default:
			obj=new("/d/wizard/obj/cikebi_book.c");
			break;
		}
          if( obj )
                obj->move(ob);
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被天书砸到了。\n");
	}
}
void jiang_shichou()
{       
        string *menpai = ({
              "峨嵋派",
              "少林派",
              "武当派",
              "丐帮",
              "华山派", 
              "明教",
              "星宿派", 
              "桃花岛",
              "全真派",
              "白驼山",
           "日月神教",
             "侠客岛",
             "天龙寺",
             "古墓派",
             "天地会",
             "神龙教",
             "朝廷",
             "灵鹫宫",
             "姑苏慕容",
        });
        string allstr,str,menpai_name;
        int i,j,k; 
        for(i=0;i<sizeof(menpai);i++)
          {
          str = ""; 
          for(j=0;j<sizeof(menpai)-1;j++) 
            { 
              allstr = "";
              menpai_name = "";
              k = 0; 
              allstr = read_file("/hate/"+menpai[i],j+1,1);
              sscanf(allstr,"%s %d",menpai_name,k);
              if(k<700)k+=5;
              allstr = "";
              allstr = menpai_name + " " +k+"\n"; 
              str += allstr;
            }
	  write_file("/hate/"+menpai[i], str, 1);		 	
          }
          call_out("jiang_shichou",86400);
}

//获得当前的游戏的天色阶段
//added by icer
string get_current_day_phase()
{
	switch (current_day_phase)
	{
		case 0:
			return "凌晨";
			break;
		case 1:
			return "早晨";
			break;
		case 2:
			return "晌午";
			break;
		case 3:
			return "正午";
			break;
		case 4:
			return "下午";
			break;
		case 5:
			return "傍晚";
			break;
		case 6:
			return "晚上";
			break;
		case 7:
			return "午夜";
			break;
		default:
			return "未知，请报告巫师";
	}
}

//触发侠客岛事件
void event_xkl()
{
        string ctime;
        mixed *local1;
// added by whuan 每周六晚上张三在11:00左右出现，照顾一些工作日没法玩的玩家
        local1 = localtime(time());
        if( local1[6] == 6 && local1[2]==23 && local1[1]>=50)
  	    {
            CHANNEL_D->do_channel(this_object(), "jh", BBLU+HIW+"听说侠客岛赏善使者张三驾临中原，寻找武林高手前往侠客岛一聚！", -1);
		        remove_call_out("xiakeling");
		        call_out("xiakeling",600);
        }
// added by whuan 周五加一次张三，因现在人多
        if( local1[6] == 5 && local1[2]==21 && local1[1]>=50)
  	    {
            CHANNEL_D->do_channel(this_object(), "jh", BBLU+HIW+"听说侠客岛赏善使者张三驾临中原，寻找武林高手前往侠客岛一聚！", -1);
            remove_call_out("xiakeling");
            call_out("xiakeling",600);
        }

// add by aiai
	      ctime = gametime();
        if ( strsrch(ctime,"月一日戌时一刻") != -1||
        	   strsrch(ctime,"月七日巳时一刻") != -1||
        	   strsrch(ctime,"月十四日未时一刻") != -1||
        	   strsrch(ctime,"月二十一日申时一刻") != -1||
        	   strsrch(ctime,"月二十五日戌时一刻") != -1||
        	   strsrch(ctime,"月十一日巳时二刻") != -1||
        	   strsrch(ctime,"月十八日未时三刻") != -1||
        	   strsrch(ctime,"月三日戌时一刻") != -1||
        	   strsrch(ctime,"月十五日申时三刻") != -1 )
        {
            if(random(4)<1) {
                CHANNEL_D->do_channel(this_object(), "jh", HIW+"听说侠客岛赏善使者莅临中原，邀请有缘人前往侠客岛一游！", -1);
            }
            remove_call_out("xiakeling");
            call_out("xiakeling",3600);
        }

//end.
}

//每周日判断是否需要重启
void event_reboot()
{
        mixed *local1;
        int uplen;
        
        local1 = localtime(time());
        uplen=uptime();
        
        if ( local1[6] == 0 &&
             uplen>=60*60*24*3 && 
             query("can_reboot") &&
             !query("rebooted") )
  	    {
  	      set("rebooted",1);
  	      delete("can_reboot");
  	      remove_call_out("sys_reboot");
  	      call_out("sys_reboot", 1, (20-local1[2])*60-local1[1]+29 );
  	    }
  	    
  	    if ( local1[6]>=1 &&
  	         query("rebooted") )
  	      delete("rebooted");
}

void sys_reboot(int interval)
{
        object npc;
        npc = new("/d/wizard/npc/god.c");
        npc->set("shutdown_time", interval);
        shout( HIW"\n北大侠客行再过" + chinese_number(interval+1) + "分钟将重新启动 ...\n"NOR );
        npc->move("/d/city/idleroom");
        npc->shut_down();
}

void update_day_phase()
{

        int hslj_num,num,ntime,num1;
        string temp,temp1,temp2;
        string timer;
        object obj;
        object ob, where, *ob_list;
        int old_size, user_count;

        remove_call_out("update_day_phase");

        current_day_phase = (++current_day_phase) % sizeof(day_phase);
        switch (day_phase[current_day_phase]["outcolor"])
        {
              case "BLK":
                   CHANNEL_D->do_channel(this_object(), "jh", BLK + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "RED":
                   CHANNEL_D->do_channel(this_object(), "jh", RED + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "HIR":
                   CHANNEL_D->do_channel(this_object(), "jh", HIR + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "GRN":
                   CHANNEL_D->do_channel(this_object(), "jh", GRN + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "HIG":
                   CHANNEL_D->do_channel(this_object(), "jh", HIG + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "YEL":
                   CHANNEL_D->do_channel(this_object(), "jh", YEL + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "HIY":
                   CHANNEL_D->do_channel(this_object(), "jh", HIY + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "BLU":
                   CHANNEL_D->do_channel(this_object(), "jh", BLU + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "HIB":
                   CHANNEL_D->do_channel(this_object(), "jh", HIB + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "MAG":
                   CHANNEL_D->do_channel(this_object(), "jh", MAG + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "HIM":
                   CHANNEL_D->do_channel(this_object(), "jh", HIM + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "CYN":
                   CHANNEL_D->do_channel(this_object(), "jh", CYN + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "HIC":
                   CHANNEL_D->do_channel(this_object(), "jh", HIC + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "WHT":
                   CHANNEL_D->do_channel(this_object(), "jh", WHT + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              case "HIW":
                   CHANNEL_D->do_channel(this_object(), "jh", HIW + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
              default:
                   CHANNEL_D->do_channel(this_object(), "jh", HIG + day_phase[current_day_phase]["time_msg"] + NOR, -1);
                   break;
        }

        if( !undefinedp(day_phase[current_day_phase]["event_fun"]) )
            call_out(day_phase[current_day_phase]["event_fun"],1);

        event_xkl();//触发侠客岛赏善使者
        
        event_reboot(); //触发重启事件

// added by pretty
        timer = read_file("/adm/etc/meteoric");
        if( !timer ) {
                 timer = sprintf("%d", time() + 3600);
                 write_file("/adm/etc/meteoric", timer, 1);
        }
        
        if( atoi(timer) <= time() ) {
                 write_file("/adm/etc/meteoric", sprintf("%d",
                         time() + 86400 + random(43200)), 1);
                 do_event();
        }
// end

//backup user data
        timer = read_file("/adm/etc/backuptime");
        if (!timer || atoi(timer) <= time()) 
        {
            if  ( (file_size("/adm/etc/beginbackup") != -1)||
		              (file_size("/adm/etc/backuping") != -1))
            {}
            else if (file_size("/adm/etc/backupok") != -1)
            {}
            else
            {
                write_file("/adm/etc/backuptime",sprintf("%d",time() + 604800),1);
                write_file("/adm/etc/beginbackup","ok",1);
                shout(HIW"开始备份所有玩家档案及系统文件，系统速度可能稍受影响，请耐心等待。\n"NOR);
            }
        }

        ntime =time();
        temp = read_file("/hslj/huashanlunjian", 1, 1);
        temp1 = read_file("/hslj/huashanlunjian", 2, 1);
        temp2 = read_file("/hslj/huashanlunjian", 3, 1);
        hslj_num = atoi(temp);
        num = atoi(temp1);
        num1 = atoi(temp2);
	
        if( (num1 > 0) && !find_living("hslj zhuchi"))
        {
            hslj_num = ntime + 604800;  //7天一次 
            obj = new("/hslj/hslj");
            obj->move("/hslj/biwu");
            obj->set("hslj",1);
            obj->set("num",num);	
            obj->set("hslj_num",hslj_num);
            obj->start(obj);	
        }

        if( (ntime > hslj_num))
        {
            hslj_num = ntime + 604800;  //7天一次
            temp = hslj_num + "\n" + num +"\n1\n huashanlunjian";
            write_file("/hslj/huashanlunjian",temp, 1);

            obj = new("/hslj/hslj");
            obj->move("/hslj/biwu");
            obj->set("hslj",1);
            obj->set("num",num);	
            obj->set("hslj_num",hslj_num);
            obj->do_order(obj);	
        }

//added by icer to clean up user_ob without environment
        ob_list = children(USER_OB);
        old_size = sizeof(ob_list);
        ob_list->clean_up();
        for(user_count=sizeof(ob_list)-1;user_count>=0;  user_count--)
                if( ob_list[user_count] && clonep(ob_list[user_count]) && !environment(ob_list[user_count]) )
                        destruct(ob_list[user_count]);
        ob_list -= ({ 0 });

//added by icer to reload im_d periodically
        remove_call_out("check_im_d");
        call_out("check_im_d",1);

        call_out("update_day_phase", day_phase[current_day_phase]["length"]);
}

//check if im_d is loaded
void check_im_d()
{
	string err;
	object imd;
	this_object()->add("imd_dec",-1);
	if (this_object()->query("imd_dec") < 0)
	{
		this_object()->set("imd_dec",50);
		imd = find_object("/adm/daemons/im_d");
		if (objectp(imd))
			imd->auto_login();
		else
			err = catch(call_other("/adm/daemons/im_d","???"));
	}
}

// This is called everyday noon by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase
void event_noon()
{
	object *ob;
	int i, skill;

	ob = users();
	for(i=0; i<sizeof(ob); i++) {
		if( !environment(ob[i]) ) continue;
		if( !environment(ob[i])->query("outdoors") ) continue;
	}
}

void event_night()
{

}
void event_dawn()
{

}
string outdoor_room_description()
{
//	return "    " + day_phase[current_day_phase]["desc_msg"] + "。\n";
	return "    " + month_desc[current_month] + day_phase[current_day_phase]["desc_msg"] +  "。\n";
}

string outdoor_room_event()
{
        return day_phase[current_day_phase]["event_fun"];
}
string outdoor_room_outcolor()
{
        return day_phase[current_day_phase]["outcolor"];
}
string game_time()
{
	return CHINESE_D->chinese_date(TIME_TICK);
}

// This function is to read a regular type of data table for day_phase and
// etc.
mapping *read_table(string file)
{
	string *line, *field, *format;
	mapping *data;
	int i, rn, fn;

	line = explode(read_file(file), "\n");
	data = ({});
	for(i=0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !pointerp(field) ) {
			field = explode( line[i], ":" );
			continue;
		}
		if( !pointerp(format) ) {
			format = explode( line[i], ":" );
			continue;
		}
		break;
	}

	for( rn = 0, fn = 0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !fn ) data += ({ allocate_mapping(sizeof(field)) });
		sscanf( line[i], format[fn], data[rn][field[fn]] );
		fn = (++fn) % sizeof(field);
		if( !fn ) ++rn;
	}
	return data;
}


mapping *query_day_phase() { return day_phase; }
void event_morning()
{
	int money,ok;

        if(!random(5))
                return;
        money=10+random(50);
	ok="/adm/daemons/dropmoney"->move_money(money);
}
void event_afternoon()
{       
/*有PKUXKX启动，by whuan
object ob, where;
object ob1;

if(random(4))
       return;
ob = new("/d/wizard/npc/feizei");
where = TASK_D->random_place();
ob->move(where);
message("channel:rumor", HIW"【江湖谣传】"+HIR"听说"HIY +TASK_D->place_belong(where)+HIR"有飞贼横行，据说身携重宝！\n"NOR,users() );

if(random(3))
       return;
ob1=new("/d/reborn/jinyong/npc/sj_huo");
ob1->move("/d/xingxiu/saimachang");



*/
}
