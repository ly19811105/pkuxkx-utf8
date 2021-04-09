//created by pal
//cometh@tom.com
//2003.10.12
//店小二模板头文件
//last modify 2003.10.14
#include "/data/home/std_file/npc/hotelmoney.c"
string query_save_file()
{
	string filename,*fname;
	filename=file_name();
	fname=explode(filename,"#");
	filename=fname[0];
	return replace_string(filename,"/file/","/save/");
}

int save()
{
        string file;
		int result;
        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file+ __SAVE_EXTENSION__);
                result = save_object(file,1);
                return result;
        }
        return 0;
}

int restore()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) )
        if(restore_object(file,1))
        {
                return 1;
        }
        return 0;
}

string check_str(string str)
{ 
    str=replace_string(str,"\"","");
    str=replace_string(str,";","");
    str=replace_string(str,"\\","");
    str=replace_string(str,"/","");
    str=replace_string(str,"'","");
    str=replace_string(str,"`","");
    str=replace_string(str,",","");
    str=replace_string(str,"!","");
    str=replace_string(str,"~","");
    str=replace_string(str,"{","");
    str=replace_string(str,"}","");
    str=replace_string(str,"$","");
    str=replace_string(str,"&","");
    return str;
}

void init()
{
	object ob;
//	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_look","look");
	add_action("set_price","set_price");
	add_action("do_ask","ask");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	write("这位"+RANK_D->query_respect(ob)+"，欢迎光临"+environment(ob)->query("short")+"。\n");
}

string value_string(int value)
{
    if( value < 1 ) value = 1;
    else if( value < 100 )
	return chinese_number(value) + "文钱";
    else if( value < 10000)
	return chinese_number(value/100) + "两白银"
	+ (value%100? "又" + chinese_number(value%100) + "文钱": "");
    else
	return chinese_number(value/10000) + "两黄金" + (value%10000?chinese_number((value%10000)/100) + "两白银":"")
	+ (value%100? "又" + chinese_number(value%100) + "文钱": "");
}

int do_look( string arg )//可以看到客栈的基本信息
{
	string msg;
	msg=environment()->query("short")+"的基本信息如下：\n";
	if( arg=="sign" || arg=="board" )
	{
		msg+="房价为："+value_string((int)query("roomprice"))+"\n";
		tell_object(this_player(),msg);
		return 1;
	}
	if( arg=="waiter" || arg=="dian xiaoer" )
		tell_object(this_player(),"房价为："+value_string((int)query("roomprice"))+"\n");
	return 0;
}

int set_price(string arg)
{
	int roomprice;
	if( !arg || !sscanf(arg,"%d",roomprice) )
		return notify_fail("set_price 数字（单位coin）\n");
	tell_object(this_player(),"你将房价改为"+value_string(roomprice)+"\n");
	set("roomprice",roomprice);
	save();
	restore();
	return 1;
}

int give_money()//收帐
{
	int moneyearned,totalearned,gain,checktime;
	object me;
	me=this_player();
	if( me->query("id")!=query("owner") )
		return 0;
	moneyearned=(int)query("money/earned");
	totalearned=(int)query("moeny/total");
	if( !moneyearned )//从玩家那里赚的
		tell_object(me,"没有从玩家那里赚到一分钱。\n");
	else
	{
		tell_object(me,"这次共从玩家手中赚到"+value_string(moneyearned)+"，\n已经直接放入你的银行帐户了。\n");
		delete("money/earned");
		me->add("balance",moneyearned);
	}
	//npc赚的钱，需要考虑山庄关闭的情况。看来还是要改logined和user.c和quit.c
	earnmoney(me,this_object(),query("roomprice"),query("checktime"));
	save();
	restore();
	return 1;
}

int upgrade()//装修客栈（提高豪华程度）
{
	return 1;
}

int repaire()//修理客栈
{
	return 1;
}

int put_up()//玩家住店
{
	return 1;
}

int accept_object(object who, object ob)
{
	int gain,totalearn;
	if ( ob->query("money_id") && (gain=ob->value()) >= query("roomprice") )
	{
		tell_object(who, "小二一哈腰，说道：多谢您老，客官请上楼歇息。\n");
		who->set_temp("selfcreate/hotelfee",1);
		//这里将钱存在店小二身上，日后玩家可以调用give_money()取得
		totalearn=(int)query("money/earned");//这个是已得的，give_money()后设为0
		totalearn+=gain;
		set("money/earned",totalearn);
		totalearn=(int)query("money/total");//这个总数不清0
		totalearn+=gain;
		set("money/total",totalearn);
		save();
		restore();
		return 1;
	}
	return 0;
}

int do_ask(string arg)
{
	string arg1,question;
	if(!arg || !sscanf(arg,"%s about %s",arg1,question) )
		return 0;
	if(arg1!="waiter" && arg1!="dian xiaoer")
		return 0;
	switch(question)
	{
		case "收入":
			give_money();
			break;
		case "装修":
			upgrade();
			break;
		case "修理":
			repaire();
			break;
		case "住店":
			put_up();
			break;
		case "休息":
			put_up();
			break;
		default:
			return 0;
	}
	return 1;
}