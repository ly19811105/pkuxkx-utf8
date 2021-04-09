// natured.c

#include <ansi.h>

#define TIME_TICK (time())

nosave int current_day_phase;
mapping *day_phase;

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
string gametime();
void do_event1();
void do_event2();
void do_event3();
void do_event4();
void do_event5();
void do_event6();

void create()
{
        seteuid(ROOT_UID);
	day_phase = read_table("/adm/etc/nature/day_phase");
      init_day_phase();
//    check_zeroid();
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
           
	// Since in our time scale, 1 minute == 1 second in RL, so we don't need
	// any conversion before using this number as call_out dalay, if you 


	// changed the time scale, be sure to convert it.

	call_out("update_day_phase",
		(int)day_phase[(current_day_phase+1) % sizeof(day_phase)]["length"] - t);
       call_out("jiang_shichou",3600);
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
        message("vision", HIW "\n一粒臭狗屎从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
         message_vision(HIW "臭狗屎不偏不倚，恰好砸在$N的脑袋上，$N被砸的头破血流，倒在地上。\n" NOR, ob);
        if( ob->query("eff_qi") * 4 > ob->query("max_qi") * 3 )
                ob->receive_wound("qi", ob->query("max_qi") * 3 / 4);
        else ob->unconcious();
//          if( obj = new("/d/private/obj/stone") )
          if( obj = new("/d/xingxiu/obj/goushi.c") )
                obj->move(ob);
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被狗屎砸到了。\n");
}

void do_event2()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一粒幸运星从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
         message_vision(MAG "幸运星不偏不倚，恰好落在$N的身上，$N感到浑身是力!\n" NOR, ob);
        ob->add("eff_qi",ob->query("max_qi"));
		ob->add("qi",ob->query("max_qi"));
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被幸运星砸到了。\n");
}

void do_event3()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一颗小福星从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
         message_vision(MAG "小福星不偏不倚，恰好落在$N的身上，$N感到全身通泰!\n" NOR, ob);
        ob->add("eff_jing",ob->query("max_jing"));
		ob->add("jing",ob->query("max_jing"));
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被小福星砸到了。\n");
}

void do_event4()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一颗天护星从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
         message_vision(MAG "天护星不偏不倚，恰好落在$N的身上，$N感到自己防御大增!\n" NOR, ob);
        ob->add_temp("apply/armor",100);
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被天护星砸到了。\n");
}

void do_event5()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一颗天伤星从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
         message_vision(MAG "天伤星不偏不倚，恰好落在$N的身上，$N感到自己攻击大增!\n" NOR, ob);
        ob->add_temp("apply/damage",100);
         log_file("meteoric", ctime(time()) + " " + ob->name() + "(" + ob->query("id") + ")被天伤星砸到了。\n");
}

void do_event6()
{
        object *u;
        object ob, obj;

        if( !(u = users()) ) return;
        message("vision", HIW "\n一本天书从天际划过，划出一道长长的弧线....\n\n" NOR, u);
        ob = u[random(sizeof(u))];
         message_vision(HIW "天书不偏不倚，恰好砸在$N的脑袋上，$N被砸的头破血流，倒在地上。\n" NOR, ob);
        if( ob->query("eff_qi") * 4 > ob->query("max_qi") * 3 )
                ob->receive_wound("qi", ob->query("max_qi") * 3 / 4);
        else ob->unconcious();
//          if( obj = new("/d/private/obj/stone") )
		switch (random(5)){
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
          call_out("jiang_shichou",3600);
}

void update_day_phase()
{

	int hslj_num,num,ntime,num1;
	string temp,temp1,temp2;
        string timer;
	object obj;
	string ctime;
        object ob, where, *ob_list;
        int old_size, user_count;

	remove_call_out("update_day_phase");

	current_day_phase = (++current_day_phase) % sizeof(day_phase);
	message("outdoor:vision", day_phase[current_day_phase]["time_msg"] + "\n", users());
	if( !undefinedp(day_phase[current_day_phase]["event_fun"]) )
		call_other(this_object(), day_phase[current_day_phase]["event_fun"]);

// add by aiai
	ctime = gametime();
	if ( strsrch(ctime,"月一日戌时一刻") != -1 )
	{
		remove_call_out("xiakeling");
		call_out("xiakeling",1800);
	}
	if ( strsrch(ctime,"月七日巳时一刻") != -1 )
	{
		remove_call_out("xiakeling");
		call_out("xiakeling",1800);
	}
	if ( strsrch(ctime,"月十四日未时一刻") != -1 )
	{
		remove_call_out("xiakeling");
		call_out("xiakeling",1800);
	}
	if ( strsrch(ctime,"月二十一日申时一刻") != -1 )
	{
		remove_call_out("xiakeling");
		call_out("xiakeling",1800);
	}
      if ( strsrch(ctime,"月二十五日戌时一刻") != -1 )
     {
        remove_call_out("xiakeling");
        call_out("xiakeling",1800);
     }
     if ( strsrch(ctime,"月十一日巳时二刻") != -1 )
    {
        remove_call_out("xiakeling");
        call_out("xiakeling",1800);
    }
    if ( strsrch(ctime,"月十八日未时三刻") != -1 )
    {
        remove_call_out("xiakeling");
        call_out("xiakeling",1800);
    }
    if ( strsrch(ctime,"月三日戌时一刻") != -1 )
    {
        remove_call_out("xiakeling");
        call_out("xiakeling",1800);
    }
       if ( strsrch(ctime,"月十五日申时三刻") != -1 )
      {
          remove_call_out("xiakeling");
          call_out("xiakeling",1800);
      }

//end.

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
        for(user_count=0; user_count<sizeof(ob_list); user_count++)
                if( ob_list[user_count] && clonep(ob_list[user_count]) && !environment(ob_list[user_count]) )
                        destruct(ob_list[user_count]);
        ob_list -= ({ 0 });


	call_out("update_day_phase", day_phase[current_day_phase]["length"]);
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

string outdoor_room_description()
{
	return "    " + day_phase[current_day_phase]["desc_msg"] + "。\n";
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
