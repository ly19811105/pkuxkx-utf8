// logind.c
//last modified by leon 11/21/1997 09:51:36
// a).增加banname中的wizname;
// b).去掉了"**名巫师在线上"这一句;

#include <ansi.h>
#include <command.h>
#include <login.h>
#define HELPNEW_LST "/log/helpnew/helpnew_lst"
#define HELPNEW_BAD_LST "/log/helpnew/helpnew_bad_lst"
#define HELPNEW_COUNT "/log/helpnew/helpnew_count"

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
string *banned_name = ({
	"你", "我", "他", "她", "它", "自己", "云开颜",
        "江泽民","三个代表","共产党","邓小平","毛泽东","胡锦涛","三讲",
        "萧峰", "乔峰", "慕容博", "慕容复", "王语嫣", "张无忌",
        "无名", "东方不败", "李逍遥", "金庸","风清扬","冰冰",
        "岳不群", "宁中则", "岳灵珊", "令狐冲", "张三丰", "洪七公",
        "丁春秋", "鲁有脚", "彭有敬", "宋远桥", "俞莲舟", "张松溪","柳残阳",
        "欧阳锋", "欧阳克", "黄药师", "黄蓉", "郭靖", "杨过", "小龙女","宋青书的剑","珍珠项链",
        "飞天","他自己","北大侠客行",
        });

string *banned_id = ({
    "none","donkey","halt","save","hitall","sleep","guest","letter","paper",
});

mapping ip_limits;

protected void get_id(string arg, object ob);
void reallogon(object ob);
protected void get_fakeid(string arg,object ob);
protected void confirm_id(string yn, object ob);
object make_body(object ob);
//private
void init_new_player(object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);

protected void random_gift(mapping my)
{
	int i;
	int tmpstr, tmpint, tmpcon, tmpdex;
	tmpstr = tmpint = tmpcon = tmpdex = 10;

	for (i = 0; i < 40; i++) {
		switch (random(4)) {
		case 0: if (tmpstr < 30) tmpstr++; else i--; break;
		case 1: if (tmpint < 30) tmpint++; else i--; break;
		case 2: if (tmpcon < 30) tmpcon++; else i--; break;
		case 3: if (tmpdex < 30) tmpdex++; else i--; break;
//		case 0: tmpstr++; break;
//		case 1: tmpint++; break;
//		case 2: tmpcon++; break;
//		case 3: tmpdex++; break;
		}
	}
	if (tmpstr <= 30) my["str"] = tmpstr; else my["str"] = 30;
	if (tmpint <= 30) my["int"] = tmpint; else my["int"] = 30;
	if (tmpcon <= 30) my["con"] = tmpcon; else my["con"] = 30;
	if (tmpdex <= 30) my["dex"] = tmpdex; else my["dex"] = 30;
	// next 2 are randomly selected
	my["kar"] = 10 + random(21);
	my["per"] = 10 + random(21);
}

void load_ip_limits()
{
	string *iplist;
	string user_id, user_ip;

	if( file_size(IPLIST) <= 0 ) return;

	iplist = explode(read_file(IPLIST), "\n");
	ip_limits = allocate_mapping(sizeof(iplist));
	for( int i=0; i<sizeof(iplist); i++) {
		if( iplist[i][0]=='#'
		|| sscanf(iplist[i], "%s %s", user_id, user_ip)!=2 ) continue;
		ip_limits[user_id] = user_ip;
	}
}

void create()
{
	seteuid( ROOT_UID );
	set("channel_id", "连线精灵");
	load_ip_limits();
        TOPTEN_D->rm_prev_logs();
}
protected void get_fakeid(string arg, object ob)
{

	arg = lower_case(arg);

	if (arg == "pkuxkxuser")
		ob->set("fake_id_ok",1);
	else
		ob->set("fake_id_ok",2);
	write("password:");
	input_to("get_fakepass",ob);
}

protected void get_fakepass(string arg, object ob)
{
	arg = lower_case(arg);
	if (ob->query("fake_id_ok") == 1)
	{
		if (arg != "pkuxkxpassword")
		{
			write("\nLogin incorrect! \nIf you have an account, please check your system administrator or the website.\n");
			destruct(ob);
			return;
		} else
		{
			ob->delete("fake_id_ok");
			reallogon(ob);
		}
	}
	else if (ob->query("fake_id_ok") == 2)
		{
			write("\nLogin incorrect! \nIf you have an account, please check your system administrator or the website.\n");
			destruct(ob);
			return;
		}
}

void logon(object ob)
{
	write("220 localhost (IMail 8.10 40444-1) NT-ESMTP Server X1\n");
                write("username:");
	input_to( "get_fakeid", ob );
}
void reallogon(object ob)
{
	object *usr;
	string login_file;
	int login_time;
	int i, wiz_cnt, ppl_cnt, login_cnt;

	if (BAN_D->is_banned(query_ip_name(ob)) == 1) {
		destruct(ob);
		return;
	}

	cat(WELCOME);
//    cat("/adm/etc/weather.log");
      write("     公网玩家建议连接" + BNK + "pkuxkx.net 8080" + NOR+ "或者" +BNK + "proxy.pkuxkx.net 8080" + NOR
             + "进入本Mud\n" NOR);

      write("         北大侠客行启用域名：" HIR "PKUXKX.NET" NOR "，主页：" HIR "http://www.pkuxkx.net\n" NOR);
     write("         欢迎大家到  "+ BNK +"bbs.pku.edu.cn " + NOR + "的娱乐休闲(6区)->Mud版发表文章\n" NOR);
	UPTIME_CMD->main();

	usr = users();
	wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
	for(i=0; i<sizeof(usr); i++) {
		if( !environment(usr[i]) ) login_cnt++;
		else if( wizardp(usr[i]) ) wiz_cnt++;
		else ppl_cnt++;
	}
	if(login_file=read_file("/adm/etc/login_times",1))
        {
		login_time=atoi(login_file);
		printf("目前为止,北大侠客行已经有%s人次访问\n",chinese_number(login_time));
        }

	printf("目前共有 %d 位玩家在线上，以及 %d 位使用者尝试连线中。\n\n",
		 ppl_cnt, login_cnt );


	write("您的英文名字：");
        input_to( "get_id", ob );
}

protected void get_id(string arg, object ob)
{
	object ppl;
	object *ob_list;
   	int i=0;
   	int j=0;
   	string reason,daysleft;


	arg = lower_case(arg);
	if( !check_legal_id(arg)) {
		write("您的英文名字：");
		input_to("get_id", ob);
		return;
	}

          if(file_size(DATA_DIR + "user/" + arg[0..0] + "/" + arg + ".o")<0)
{
               write ("档案不存在！\n");
          if(file_size(DATA_DIR + "login/" + arg[0..0] + "/" + arg + ".o")>=0)
          rm(DATA_DIR + "login/" + arg[0..0] + "/" + arg + ".o");
}
	if (BAN_D->user_is_banned(arg) != "")
	{
		daysleft = explode(BAN_D->user_is_banned(arg)," ")[0];
		reason = explode(BAN_D->user_is_banned(arg)," ")[1];
		write("对不起，您由于" + reason + "的原因还需要被封禁" + daysleft + "。专心忙您的事情吧。\n");
		destruct(ob);
		return;
	}

#ifdef MAX_USERS
	if( (string)SECURITY_D->get_status(arg)=="(player)"
	&& sizeof(users()) >= MAX_USERS ) {
		ppl = find_body(arg);
		// Only allow reconnect an interactive player when MAX_USERS exceeded.
		if( !ppl || !interactive(ppl) ) {
			write("对不起，" + MUD_NAME + "的使用者已经太多了，请待会再来。\n");
			destruct(ob);
			return;
		}
	}
#endif

	if( wiz_level(arg) < wiz_lock_level ) {
		write("对不起，" + MUD_NAME + "目前限制巫师等级 " + WIZ_LOCK_LEVEL
			+ " 以上的人才能连线。\n");
		destruct(ob);
		return;
	}

	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

/*
	if( arg=="guest" ) {
		// If guest, let them create the character.
		confirm_id("Yes", ob);
		return;
	} else
*/
	 if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 ) {
		if( ob->restore() ) {
            if( ob->query("id") != arg )
             {
             write(MUD_NAME + "疑惑地看了看你，道：“咦？你这家伙想他妈的干什么？”\n");
             write(HIW + MUD_NAME + "一个大脚把你踢了出去！\n" NOR);
             destruct(ob);
             return;
             }
               write("请输入密码：");
			input_to("get_passwd", 1, ob);
			return;
		}
		write("您的人物储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
		destruct(ob);
		return;
	}

//add by kill
   ob_list = users();
   for(i=0;i<sizeof(ob_list);i++)
     {    if((string)ob_list[i]->query("id")==arg)
            j++;
     }
     if(j>1)
     {  write("对不起，有人正在使用该代号注册，请换一个代号登陆。\n");
               destruct(ob);
               return;
          }

	write("使用 " + (string)ob->query("id") + " 这个名字将会创造一个新的人物，您确定吗(y/n)？");
	input_to("confirm_id", ob);
}

protected void get_passwd(string pass, object ob)
{
	string my_pass,md5pass, ip;
	object user;

	write("\n");
	my_pass = ob->query("password");
	md5pass = ob->query("md5pass");
	if( crypt(pass, my_pass) != my_pass ) {
			if( wiz_level(ob->query("id")) >0)
                                   log_file("crack_wiz_log", sprintf(ob->query("id") + "被从"+ query_ip_name(this_player()) + "登陆的人在"+ctime(time())+"用错误密码尝试过。\n"));

                write("密码错误！\n");
		destruct(ob);
		return;
	}
	if (!md5pass)
	{
		ob->set("md5pass",MDFIVE_D->hex_md5(pass));
	}
	// Check if we are from the proper IP
	if( ip_limits && !undefinedp(ip = ip_limits[ob->query("id")])
	&& (ip != query_ip_name(ob)) ) {
		log_file( "WIZ_LOGIN", sprintf("%s  %s logined from %s but was refused due to ip limit.\n",
			ctime(time()), ob->query("id"), query_ip_name(ob) ) );
		write("你不可以从这个IP登录！\n");
		destruct(ob);
		return;
	}
//先不管双登了
//            if (BAN_D->check_ml(ob) == 1)   {
//                write("对不起，线上的玩家已经太多了，你就不要双登了，给别人留个机会吧！\n");
//                    destruct(ob);
//                    return;
//                  }

	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {
		if( user->query_temp("netdead") ) {
			reconnect(ob, user);
			return;
		}
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}


	if( objectp(user = make_body(ob)) ) {
		if( user->restore() ) {
                        log_file( "USAGE", sprintf("%s(%s) loggined from %s (%s)\n", user->query("name"),user->query("id"),
				query_ip_name(ob), ctime(time()) ) );
			enter_world(ob, user);
			return;
		} else {
			destruct(user);
		}
	}
	write("请您重新创造这个人物。\n");
	confirm_id("y", ob);
}

protected void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if( yn=="" ) {
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("好吧，欢迎下次再来。\n");
		destruct(ob);
		return;
	} 
	else {
//先不管双登了
//              if (BAN_D->check_ml(ob) == 1)   {
//             write("对不起，线上的玩家已经太多了，你就不要双登了，给别人留个机会吧！\n");
//          destruct(ob);
//          return;
//         }
    // icer added for the case the user online quit before this user input "y"
    /*
                                  if (!find_player(ob->query("id")) )
                                  {
                                      write("对不起，你要取代的玩家刚刚离线，请重新登录。\n");
                         destruct(ob);
                                      return;
                                   }
    */
		tell_object(user, "有人从别处( " + query_ip_number(ob)
			+ " )连线取代你所控制的人物。\n");
		log_file( "USAGE", sprintf("%s replaced by %s (%s)\n", user->query("name"),
			query_ip_name(ob), ctime(time()) ) );
	}

	// Kick out the old player.
	old_link = user->query_temp("link_ob");
	if( old_link ) {
		exec(old_link, user);
		destruct(old_link);
	}

	reconnect(ob, user);
}

protected void confirm_id(string yn, object ob)
{


if( yn=="" ) {
	   write("使用这个名字将会创造一个新的人物，您确定吗(y/n)？");
		input_to("confirm_id", ob);
		return;
	}

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("好吧，那么请重新输入您的英文名字：");
		input_to("get_id", ob);
		return;
	}
	write( @TEXT

请输入您的高姓大名，由于这个名字代表你的人物，而且以后不能更改，
务必慎重择名（不雅观的姓名将被删除）。另：请不要选择金庸小说中
已有人物姓名。

TEXT
	);
	write("您的中文名字：");
	input_to("get_name", ob);
remove_call_out("time_out");
}

protected void get_name(string arg, object ob)
{
	if( !check_legal_name(arg) ) {
		write("您的中文名字：");
		input_to("get_name", ob);
		return;
	}
	printf("%O\n", ob);
	ob->set("name", arg);
	write("请设定您的密码：");
	input_to("new_password", 1, ob);
}

protected void new_password(string pass, object ob)
{
	write("\n");
	if( strwidth(pass)<5 ) {
		write("密码的长度至少要五个字元，请重设您的密码：");
		input_to("new_password", 1, ob);
		return;
	}
	if (pass == ob->query("id"))
	{
		write("密码不可以和您的id相同，请重新设置您的密码：");
		input_to("new_password", 1, ob);
		return;
	}
	ob->set("password", crypt(pass,0) );
//        ob->set("md5pass",MDFIVE_D->hex_md5(pass));
	write("请再输入一次您的密码，以确认您没记错：");
	input_to("confirm_password", 1, ob);
}

protected void confirm_password(string pass, object ob)
{
	mapping my;
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("您两次输入的密码并不一样，请重新设定一次密码：");
		input_to("new_password", 1, ob);
		return;
	}

	write(@TEXT

一个人物的天赋对于他或她所修习的武艺息息相关。比如高膂力的人物对阳性
内功有辅助作用，高身法则对阴性内功有辅助作用，高根骨配合前两者则可以
兼修部分阴阳内功。《侠客行》中的人物大多具有以下四项天赋：

	膂力：影响攻击能力及负荷量的大小。
	悟性：影响学习武功秘籍的速度及理解师傅的能力。
	根骨：影响体力恢复的速度及升级后所增加的体力。
	身法：影响防御及躲避的能力。

TEXT);
	my = ([]);
	random_gift(my);
	printf("\n膂力[%d]， 悟性[%d]， 根骨[%d]， 身法[%d]\n",
                my["str"], my["int"], my["con"], my["dex"]);
        write("您接受这一组天赋吗？");
        input_to("get_gift", ob, my);
}

protected void get_gift(string yn, object ob, mapping my)
{
	if (yn[0] != 'y' && yn[0] != 'Y') {
		random_gift(my);
		printf("\n膂力[%d]， 悟性[%d]， 根骨[%d]， 身法[%d]\n",
                      my["str"], my["int"], my["con"], my["dex"]);
                write("您同意这一组天赋吗？");
		input_to("get_gift", ob, my);
	}
	
	if (yn[0] == 'y' || yn[0] == 'Y')
	{
          	write("\n\n");
			write(@TEXT

民族直接决定了对人物所能学习的专有特技。《侠客行》中的民族有以下五种：

 [ 1 ] 游牧民族 专有：内力深厚，支配拳脚，裁缝技术
 [ 2 ] 天竺部族 专有：百草药理，支配棍杖，点石成金
 [ 3 ] 苗家部族 专有：传音搜魂，支配长枪，支配软鞭
 [ 4 ] 东瀛浪人 专有：冶炼技术，支配刀刃，锻造技术
 [ 5 ] 中原人士 专有：强身健体，支配长剑，五行数术
	
请输入你所选择的民族代号：
TEXT);
        	input_to("get_nation", ob, my);
	}
}

// Dewolf/vax@pkuxkx 2006  choose nation
protected void get_nation(string num, object ob, mapping my)
{
	if (num[0] != '1' && num[0] != '2' && num[0] != '3' && num[0] != '4' && num[0] != '5')
	{
        write("请输入民族代号：");
		input_to("get_nation", ob, my);
	}
	else
	{
		switch (num[0] - '0')
		{
			case 1 :
				ob->set("nation", "游牧民族");
				break;
			case 2 :
				ob->set("nation", "天竺部族");
				break;
			case 3 :
				ob->set("nation", "苗家部族");
				break;
			case 4 :
				ob->set("nation", "东瀛浪人");
				break;
			case 5 :
				ob->set("nation", "中原人士");
				break;
        }
		write("\n您的电子邮件地址：");
        input_to("get_email", ob, my);
		
	}
}

protected void get_email(string email, object ob, mapping my)
{
	object user;

	write("\n");
	if (email == "" || strsrch(email, "@") == -1) {
		write("电子邮件地址需要是 id@address 的格式。\n");
		write("您的电子邮件地址：");
		input_to("get_email", ob, my);
		return;
	}
	ob->set("email", email);
	ob->set("registered", 1);

	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	ob->set("body", USER_OB);
	if( !objectp(user = make_body(ob)) )
		return;
	user->set("str", my["str"]);
	user->set("dex", my["dex"]);
	user->set("con", my["con"]);
	user->set("int", my["int"]);
	ob->set("registered", 1);
	user->set("registered", 1);

	write("您要扮演男性(m)的角色或女性(f)的角色？");
	input_to("get_gender", ob, user);
}

protected void get_gender(string gender, object ob, object user)
{
	string user_file, ext_msg;
	int usernum;
	write("\n");
	if( gender=="" ) {
		write("您要扮演男性(m)的角色或女性(f)的角色？");
		input_to("get_gender", ob, user);
		return;
	}

	if( gender[0]=='m' || gender[0]=='M' )
		user->set("gender", "男性");
	else if( gender[0]=='f' || gender[0]=='F' )
		user->set("gender", "女性" );
	else {
		write("对不起，您只能选择男性(m)或女性(f)的角色：");
		input_to("get_gender", ob, user);
		return;
	}

      if(user_file=read_file("/adm/etc/usernum",1))
      {
		usernum=atoi(user_file);
		usernum++;
      }
	write_file("/adm/etc/usernum",""+usernum,1);
	log_file( "USAGE", sprintf("%s was created from %s (%s)\n", user->query("id"),
		query_ip_name(ob), ctime(time()) ) );
	init_new_player(user);
//暂时不管中文重名了，id太多
//         CNAME_D->add_cname(ob->query("name"),ob->query("id"));
	enter_world(ob, user);
	
	ext_msg = "";
	// 天地无用概率出现
	if (random(1000) == 888)
	{
		// lucky enough
		user->set("special/resist-yinyang", 1);
		write(HIY "\n\n朦胧之中，你拾起了一些残碎的记忆片断：\n  金瓦、云河、三銮殿……\n\n" NOR);
		ext_msg = "武曲星从天庭坠落人间，";
	}
	if (user->query("gender") == "男性")
		message("rumor", HIW "【江湖传闻】：听说" + ext_msg + user->name() + "(" + user->query("id") + ")决定弃文从武，投身江湖，新一代大侠可能就此诞生了！\n"NOR, users());
	else
		message("rumor", HIM "【江湖传闻】：听说" + ext_msg + user->name() + "(" + user->query("id") + ")决定弃文从武，投身江湖，新一代女侠可能就此诞生了！\n"NOR, users());
	write("\n");
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

	//if (previous_object() && getuid(previous_object()) != ROOT_UID) return 0;
	user = new(ob->query("body"));
	if(!user) {
		write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name( ob->query("name"), ({ ob->query("id")}) );
	user->set("nation", ob->query("nation"));
	return user;
}

//private
void init_new_player(object user)
{
	user->set("title", "普通百姓");
	user->set("birthday", time() );
	user->set("potential", 99);

     user->set("channels", ({ "chat", "rumor", "new", "tt", "hslj", "baowei" }) );
//	user->set("balance", 1000);
}


varargs void enter_world(object ob, object user, int silent)
{
        object cloth, room, lover, mbx, shoe, guider;
	string startroom,tmpstr1,tmpstr,lover_name;
	string *autoloads,login_file;
	string *sname;//sname加来返老还童用的
        string lines, my_id, ip_list, victim_id, cname,victim_ip;
        string *line;
        object voter,victim;
        object ball;
	object obj;
	int login_time;
	int news;
	int *svalue;
        mapping skill_status;    //灵鹫宫返老还童用
        int i, level; 
        float exper;


	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	user->set("registered", ob->query("registered"));
	exec(user, ob);

	write("\n目前权限：" + wizhood(user) + "\n");
	user->setup();
	user->set_temp("EnterGame",1);
/*	if (query_ip_name(user) == "127.0.0.1")
		user->set("position","webuser");
	else
		user->set("position","zmuduser");
*/
	user->set("position","zmuduser");
        if(user->query("block_login")>time()
       && !wizardp(user))
        {
        	if((user->query("block_login")-time())>3600*24)
        	    user->set("block_login",time()+3600*24);
        	write(sprintf("对不起，您被暂时禁止访问本Mud，请等候%s分钟以后再来。\n",chinese_number((int)(user->query("block_login")-time())/60+1)));
        	user->save();
        	ob->save();
        	destruct(user);
        	destruct(ob);
        	return;
        }

	if (!user->query("food") && !user->query("water") && ob->query("age") == 14) {
	        user->set("food", user->max_food_capacity());
        	user->set("water", user->max_water_capacity());
	}

	// In case of new player, we save them here right aftre setup
	// compeleted.

        if(user->query("age") < 15 && (user->query("combat_exp") < 2000) )
        {
                  guider = new("/clone/misc/guider");
          	    guider->move(user);
          }
		if (user->query("class")=="bonze")
		{
			if (user->query("gender")=="女性")
			{
				cloth = new("/clone/cloth/ni-cloth.c");
				shoe = new("/clone/cloth/ni-xie.c");
			}
			else
			{
				cloth = new("/clone/cloth/seng-cloth.c");
				shoe = new("/clone/cloth/seng-xie.c");
			}
		}
		else
		{
			if (user->query("class")=="taoist")
			{
				if ( user->query("gender")=="女性")
				{
					cloth = new("/clone/cloth/daogu-cloth.c");
					shoe = new("/clone/cloth/dao-xie.c");
				}
				else
				{
					cloth = new("/clone/cloth/dao-cloth.c");
					shoe = new("/clone/cloth/dao-xie.c");
				}
			}
			else
			{
				if ( user->query("gender")=="女性")
				{
					switch (random(2))
					{
						case 0:
					shoe = new("/clone/cloth/female-shoe.c");
						break;
						case 1:
					shoe = new("/clone/armor/womanshoes");
						break;
					}
					switch (random(9))
					{
						case 1:
					cloth = new("/clone/cloth/female1-cloth.c");
						break;
						case 2:
					cloth = new("/clone/cloth/female2-cloth.c");
						break;
						case 3:
					cloth = new("/clone/cloth/female3-cloth.c");
						break;
						case 4:
					cloth = new("/clone/cloth/female4-cloth.c");
						break;
						case 5:
					cloth = new("/clone/cloth/female5-cloth.c");
						break;
						case 6:
					cloth = new("/clone/cloth/female6-cloth.c");
						break;
						case 7:
					cloth = new("/clone/cloth/female7-cloth.c");
						break;
						case 8:
					cloth = new("/clone/armor/skirt");
						break;
						default:
					cloth = new("/clone/cloth/female8-cloth.c");
					}
				}
				else
				{
					switch (random(2))
					{
						case 0:
					shoe = new("/clone/cloth/male-shoe.c");
						break;
						case 1:
					shoe = new("/clone/armor/manshoes");
						break;
					}
					switch (random(10))
					{
						case 1:
					cloth = new("/clone/cloth/male1-cloth.c");
						break;
						case 2:
					cloth = new("/clone/cloth/male2-cloth.c");
						break;
						case 3:
					cloth = new("/clone/cloth/male3-cloth.c");
						break;
						case 4:
					cloth = new("/clone/cloth/male4-cloth.c");
						break;
						case 5:
					cloth = new("/clone/cloth/male5-cloth.c");
						break;
						case 6:
					cloth = new("/clone/cloth/male6-cloth.c");
						break;
						case 7:
					cloth = new("/clone/cloth/male7-cloth.c");
						break;
						case 8:
					cloth = new("/clone/armor/jinzhuang");
						break;
						case 9:
					cloth = new("/clone/armor/cloth");
						break;
						default:
					cloth = new("/clone/cloth/male8-cloth.c");
					}
				}
			}
		}
		cloth->move(user);
		cloth->wear();
		shoe->move(user);
		shoe->wear();
		if( !silent ) {
		if (ob->query("registered") == 0)
			cat(UNREG_MOTD);
		else
			cat(MOTD);

		if( user->is_ghost() )
			startroom = DEATH_ROOM;
		else if( !stringp(startroom = user->query("startroom")) )
			startroom = START_ROOM;

		if( (wiz_level(user) == 0) && ( ( strsrch(startroom, "/u") == 0 ) || ( 			strsrch(startroom, "/d/wizard") == 0 ) ) )
		{
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
if(!user->query("xuetang"))
{
        startroom = "/d/newbie/entrance.c";
        user->set("startroom","/d/newbie/entrance.c");
}


                 if( objectp(load_object(startroom)) )
			user->move(startroom);
		else {
			user->move(START_ROOM);
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
                user->save();
                ob->save();
		if(login_file=read_file("/adm/etc/login_times",1))
		{
			login_time=atoi(login_file);
			login_time++;
			write_file("/adm/etc/login_times",""+login_time,1);
		}

		if( user->query("new_mail") ) {
              		message_vision( HIG + "\n一个驿站的伙计匆匆跑过来，交给$N一个信箱，说道：「有您的信！」然后头也不回地走了。\n" + NOR, user);
                	mbx = new("/clone/misc/mailbox");
                	mbx->move(user);
		}

		if ( !wiz_level(user) ) { user->set_temp("log/mud_age",user->query("mud_age"));
		user->set_temp("log/combat_exp",user->query("combat_exp"));
		user->set_temp("log/time",time()); }

		}

		tell_room(startroom, user->query("name") + "连线进入这个世界。\n", ({user}));

       if(user->query("int",1)>40&&!wizardp(user)) user->set("int",40);
       if(user->query("str",1)>40&&!wizardp(user)) user->set("str",40);
       if(user->query("con",1)>40&&!wizardp(user)) user->set("con",40);
       if(user->query("dex",1)>40&&!wizardp(user)) user->set("dex",40);
       if(user->query("int",1)<10&&!wizardp(user)) user->set("int",10);
       if(user->query("str",1)<10&&!wizardp(user)) user->set("str",10);
       if(user->query("con",1)<10&&!wizardp(user)) user->set("con",10);
       if(user->query("dex",1)<10&&!wizardp(user)) user->set("dex",10);
	   if(user->query("eff_jing",1)>user->query("max_jing")&&!wizardp(user)) user->set("eff_jing",user->query("max_jing"));

	   // Dewolf, compactable with old file
	   if(!user->query("nation")) user->set("nation", "中原人士");
	   
	if ( arrayp(autoloads = user->query("auto_load")) )
	{
                for (i = sizeof(autoloads)-1; i >= 0; i--)
            {
                     if(autoloads[i][0..2]=="/u/"&&!wizardp(user)) continue;
			if ( objectp(obj = new(autoloads[i])) && obj->move(user) )
				write("\n" + obj->name() + "  loaded.\n\n");
			else
				write(HIY "你觉得好象失落了什么重要的东西，赶快通知巫师吧！\n\n" NOR);
            }
	}

        if( user->query("created_pet") )
                tell_object(user, PET_D->create_pet(user));

        user->enable_player();

	 if( (wizhood(user) == "(admin)") ||(wizhood(user) == "(arch)") )
		{
			cat(WIZ_MOTD);
		}
	if ( wiz_level(user) )
	{
		log_file("WIZ_LOGIN", ctime(time()) + "  " + user->name() + "(" + user->query("id") + ")从" + query_ip_name(user) + "连线进入。\n");
	}
	CHANNEL_D->do_channel( this_object(), "sys",
		sprintf("%s(%s)由%s连线进入。", user->name(), capitalize(user->query("id")), query_ip_name(user)) );
		write(HIR"您上次是在" + ctime(ob->query("last_on")) + "从" + ob->query("last_from")
+ "连线进入，请及时核对。\n如果与您实际经历不符，请立刻修改密码。\n"NOR);
        //UPDATE_D->check_user(user);
        TOP_D->compare_status(user);
        TOPTEN_D->topten_checkplayer(user);
         ONLINE_D->listuser();

                if(!undefinedp(lover_name=user->query("marry/lover"))
                    &&(lover=find_object(lover_name)))
                  {
                       if ((string)lover->query("gender") != "女性")
                          {
                           tmpstr1 = "老公";
                           tmpstr = "老婆";
                          }
                       else
                          {
                           tmpstr1 = "老婆";
                           tmpstr = "老公";
                          }

                       write(MAG"你的"+tmpstr1+"也在这里，快去找啦...\n"NOR);
                       tell_object(lover ,
                              MAG"你的"+tmpstr+"来啦,快去接...\n"NOR);
                 }
	//检查玩家job_title
	lines = read_file(HELPNEW_COUNT);
	if (lines)
		line = explode(lines,"\n");
	if (user->query("job_title") == HIW"本周最受欢迎玩家"NOR)
		if (user->query("helpnew_count") != line[0])
			user->delete("job_title");
	if (user->query("job_title") == HIY"本月最受欢迎玩家"NOR)
		if (user->query("helpnew_count") != line[0])
			user->delete("job_title");
	//检查helpnew投票
        lines = read_file(HELPNEW_LST);
        if(lines)
        {
        	line = explode(lines, "\n");
	        for(i=0;i<sizeof(line);i++)
        	{
              		sscanf(line[i],"%s,%s,%s,%s,%s", my_id, ip_list, victim_id, cname,victim_ip);
              		if ( (user->query("id") == my_id) || (user->query("id") == victim_id) )
              		if ( objectp(voter = find_player(my_id)) && objectp(victim = find_player(victim_id)))
              			if (query_ip_name(voter) == query_ip_name(victim))
              			{
              				tell_object(voter,HIR"你所选择的最爱帮助新手的玩家：" + cname + "(" + 
              					victim_id + ")" + "现在的ip与你相同，请到中央广场post解释原因，" +
              					"否则本周投票将不计" + cname + "的票数。\n"NOR);
              				tell_object(victim,HIR"玩家" + voter->name() + "(" + 
              					my_id + ")" + "现在的ip与你相同，他本周曾投票选你为最爱帮助新手的" +
              					"玩家。请到中央广场post解释原因，否则本周投票将不计你的票数。\n"NOR);
					write_file(HELPNEW_BAD_LST, "voter:" + voter->query("id") + ",vote_target:" +
						victim_id + " 于" + ctime(time()) + " 在同一IP:" + query_ip_name(voter) + "登录。\n");
					break;
				}
		}
	}
//灵鹫宫的返老还童
        if ((string)user->query("family/family_name") == "灵鹫宫"  && 		user->query_skill("bahuang-gong",1)>0 )
	{
		if (((user->query("age")>29) && !user->query("lingjiu/huantong1"))||
		   ((user->query("age")>59) && !user->query("lingjiu/huantong2"))||
		   ((user->query("age")>89) && !user->query("lingjiu/huantong3")))
		{
			skill_status = user->query_skills();
	//		user->set("lingjiu/skill_status",skill_status);  //记录返老还童时的功夫
//上面这样记录总记录不好，不止到问题何在
			//记录原来的经验，气，精，精力，内力
			user->set("lingjiu/combat_exp",user->query("combat_exp"));
			user->set("lingjiu/qi",user->query("qi"));
			user->set("lingjiu/max_qi",user->query("max_qi"));
			user->set("lingjiu/jing",user->query("jing"));
			user->set("lingjiu/max_jing",user->query("max_jing"));
			user->set("lingjiu/jingli",user->query("jingli"));
			user->set("lingjiu/max_jingli",user->query("max_jingli"));
			user->set("lingjiu/neili",user->query("neili"));
			user->set("lingjiu/max_neili",user->query("max_neili"));
			//记录需要练习的次数
			user->set("lingjiu/need_xiulian",(int)(user->query("age")/30)*30);
			//记录mudage
			user->set("lingjiu/mud_age",user->query("mud_age"));

        		sname  =keys(skill_status);
			svalue=values(skill_status);
                         for(i=0; i<sizeof(skill_status); i++)
			{
			    user->set("lingjiu/skill_status/"+sname[i],svalue[i]);
        	    	    if( sname[i] != "literate") user->set_skill(sname[i], 1);
			}

			if (user->query("age")>29) user->set("lingjiu/huantong1",1);
			if (user->query("age")>59) user->set("lingjiu/huantong2",1);
			if (user->query("age")>89) user->set("lingjiu/huantong3",1);
               		user->set("combat_exp",0);
			user->set("mud_age",0);
			user->set("age",14);
			user->set("jing",100);
			user->set("max_jing",100);
			user->set("eff_jing",100);
			user->set("qi",100);
			user->set("max_qi",100);
			user->set("eff_qi",100);
			user->set("jingli",0);
			user->set("max_jingli",0);
			user->set("neili",0);
			user->set("max_neili",0);
			write(HIY "你突然觉得自己的功夫和经验全部消失了，原来是修炼八荒六合唯我独尊功返老还童了，赶紧去练习恢复功力吧！\n" NOR);
			//记录是否处于修炼（返老还童）状态
			user->set("lingjiu/xiulian",1);


        	}

	}

//

    	if ( user->query("riyue_drug")
		&& (user->query("age") > user->query("riyue_drug")))
	{
		write(HIY "你的三尸脑神丹的毒还有十分钟就要发作了！赶快去要解药吧！\n" NOR);
		call_out("poison",600,user);
	}
        news=NEWS_D->query_new(user);
	if(news)
	{
		write(HIY+"您有"+HIG+chinese_number(news)+HIY"条系统新闻未读，请使用news new来阅读，这对您很重要。\n"+NOR);
	}
//功夫等级检查
        exper = to_float(user->query("combat_exp"));

        if (wizardp(user)) return;

        if ( !(skill_status = user->query_skills()) ) {}
        else
        {
        	sname  = keys(skill_status);

	        for(i=0; i<sizeof(skill_status); i++) 
	        {
	                level = skill_status[sname[i]];
	              if( pow(to_float(level-2), 3.0) / 10.0 > exper 
	                && exper > 100.0
	                && SKILL_D(sname[i])->type() != "knowledge") 
	                {
	                        level = ceil( pow( exper*10.0, 0.333333) );
	                        user->set_skill(sname[i], level+1);
	                          write(HIR+BNK+"你的" + sname[i] + "等级超出经验支持的能力范围，已经恢复到" + (level+1) + "级。\n"+NOR);
	                }
	        }
	}
        if (user->query("seen_help") == 0)
                write(HIR+"你还没有看过help newbie，那里面有大部分新手常问的问题如吃喝等的解答\n以及很多很好的建议，希望你能尽快仔细阅读它。\n"+NOR);
	if ( (user->query("combat_exp") < 500000) && (user->query("combat_exp") > 5000))
		write(HIR+"如果你觉得其他人对你帮助很大，可以使用votehelpnew来感谢他。请打help votehelpnew看详细用法。\n"+NOR);
}

void poison(object user)
{
        if( !user ) return;
	if (!(user->query("age") > user->query("riyue_drug")))
		return;
	user->add_temp("riyue/poison",1);
	if (user->query_temp("riyue/poison") == 2)
	{
		message_vision(HIR "$N由于三尸脑神丹毒发时间过长，无药可救，倒地而亡。\n" NOR,user);
		user->set("riyue_drug",999);
		user->die();
		user->save();
		return;
	}

	user->set("max_qi",50);
	user->set("max_jing",50);
	message_vision(HIR "$N的三尸脑神丹毒发作了！$N痛得满地打滚，咬牙切齿，状如疯狗一般。\n" NOR,user);
	user->set("attitude","aggressive");
	call_out("poison",300,user);
}


varargs void reconnect(object ob, object user, int silent)
{
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	exec(user, ob);

	user->reconnect();
	if( !silent && user->query("noDeadNetnoIdle") != "Pkuxkx") {
		tell_room(environment(user), user->query("name") + "重新连线回到这个世界。\n",
		({user}));
	}
	CHANNEL_D->do_channel( user, "sys",
		sprintf("%s(%s)由%s重新连线进入。", user->name(), capitalize(user->query("id")), query_ip_name(user)) );
//	UPDATE_D->check_user(user);
}

int check_legal_id(string id)
{
	int i;

	i = strwidth(id);

    if( member_array( id, banned_id ) != -1 )
    {
        write("这个ＩＤ会引起不必要的麻烦。\n");
        return 0;
    }

	if( (strwidth(id) < 3) || (strwidth(id) > 12 ) ) {
		write("对不起，你的英文名字必须是 3 到 12 个英文字母。\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) {
			write("对不起，你的英文名字只能用英文字母。\n");
			return 0;
		}

	return 1;
}
int check_legal_describe(string name)
{
	int i;

	i = strwidth(name);
	while(i--)
	{
		if( name[i]<=' ' )	return 0;
		if(	name[i]=='"'||name[i]=='('||name[i]==')') return 0;
	}
	return 1;
}
int check_legal_name(string name)
{
	int i;

	i = strwidth(name);

	if( (strwidth(name) < 1) || (strwidth(name) > 6 ) ) {
		write("对不起，你的中文名字必须是 1 到 6 个中文字。\n");
		return 0;
	}
	while(i--) {
		if( name[i]<=' ' ) {
			write("对不起，你的中文名字不能用控制字元。\n");
			return 0;
		}
		if( !is_chinese(name[i..<0]) ) {
			write("对不起，请您用「中文」取名字。\n");
			return 0;
		}
	}
	if( member_array(name, banned_name)!=-1 ) {
		write("对不起，这种名字会造成其他人的困扰。\n");
		return 0;
	}
//暂时不管中文重名了，id太多
/*
         if(CNAME_D->query_cname(name)==1)
         {
		write("对不起，这个名字已经有人使用了，请换用其他的中文名字。\n");
		return 0;
	}

*/
	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	for(int i=0; i<sizeof(body); i++)
		if( clonep(body[i])
		&&	getuid(body[i]) == name ) return body[i];

	return 0;
}

int set_wizlock(int level)
{
	if( wiz_level(this_player(1)) <= level )
		return 0;
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;
	wiz_lock_level = level;
	return 1;
}
