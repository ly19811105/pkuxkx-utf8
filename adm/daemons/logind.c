// logind.c
//last modified by leon 11/21/1997 09:51:36
// a).增加banname中的wizname;
// b).去掉了"**名巫师在线上"这一句;
// Modified by iszt@pkuxkx, 2007-04-14, judge money, and some small problems
//by seagate 2014/02/05
//增加密码复杂度校验

#include <ansi.h>
#include <mxp.h>
#include <command.h>
#include <login.h>
#include <localtime.h>

#define HELPNEW_LST "/log/helpnew/helpnew_lst"
#define HELPNEW_BAD_LST "/log/helpnew/helpnew_bad_lst"
#define HELPNEW_COUNT "/log/helpnew/helpnew_count"

//最大单ip重复登陆数目
#define MAX_MULTIPLE_LOGIN 8

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
string *banned_name = ({
	"你", "我", "他", "她", "它", "自己", "云开颜","草泥马","和谐",
	"江泽民","三个代表","共产党","邓小平","毛泽东","胡锦涛","三讲",
        "萧峰", "乔峰", "慕容博", "慕容复", "王语嫣", "张无忌","法轮功",
        "无名", "东方不败", "李逍遥", "金庸","风清扬","冰冰","无欢",
	"岳不群", "宁中则", "岳灵珊", "令狐冲", "张三丰", "洪七公",
	"丁春秋", "鲁有脚", "彭有敬", "宋远桥", "俞莲舟", "张松溪","柳残阳",
	"欧阳锋", "欧阳克", "黄药师", "黄蓉", "郭靖", "杨过", "小龙女","宋青书的剑","珍珠项链",
        "飞天","他自己","北大侠客行","北大侠客行","北侠","静电清水","十兆","某人","无欢","北侠","毫毛","红豆",
		"蒙古骑兵","土匪","残叶","凤凰羽","法轮","薄熙来","王立军","谷开来","薄谷开来",
	});
 
string *banned_id = ({
    "none","donkey","halt","save","hitall","sleep","guest","letter","paper",
});

string *allowed_id = ({});

string *allowed_sites = ({"127.0.0.1",
	});
string *disallowed_sites = ({});
mapping ip_limits;

mapping create_new_id_from_ip = ([]);
mapping ip_login  = ([]);
mapping xiuxian_ip = ([]);

void get_newid(string arg, object ob);
void confirm_id(string yn, object ob);
void get_name(string arg, object ob);
void new_password(string pass, object ob);
void confirm_password(string pass, object ob);
void get_email(string email, object ob, mapping my);
void get_gender(string gender, object ob, mapping my);
void get_id(string arg, object ob);
/*
用户登录以后会校验用户密码复杂度
玩家密码复杂度大于等于5
导师密码复杂度大于等于6
巫师密码复杂度大于等于10
天神密码复杂度大于等于11
*/
void get_passwd(string pass, object ob);
void change_passwd(string pass, object ob, int pass_comp);
void confirm_password2(string pass, object ob, int pass_comp);
int valid_pass(string pass, object ob);
void get_fakepass(string arg, object ob);
void confirm_relogin(string yn, object ob, object user);
void reallogon(object ob);
void PostDetect(object ob);
void get_fakeid(string arg,object ob);
object make_body(object ob);
//private
void init_new_player(object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
int check_multiple_login(object ob,int special_ip);
void add_ip_numbers(string ip);
void sub_ip_numbers(string ip);
int get_ip_numbers(string ip);
int ShowReward();
int LoginNotify(object user);

void check_security_code(string security_code,string pass, object ob);
void post_authentication(string pass,object ob);

/*
检验密码复杂度
复杂性分为四种情况：小写字母，大写字母，数字，特殊字符
复杂度根据这四种情况定义出以下几个级别：
第0级：长度小于6位或者长度大于等于6位但是密码组成字符都是一个类型
第5级：长度大于等于6位但是不足8位，密码组成字符由两种类型组成
第6级：长度8位并且密码组成字符由两种类型组成
第10级：长度大于等于6位但是不足8位，密码组成字符由三种类型组成
第11级：长度8位并且密码组成字符由三种类型组成
第15级：长度大于等于6位但是不足8位，密码组成字符由四种类型组成
第16级：长度8位并且密码组成字符由四种类型组成

函数返回结果是密码的复杂度级别
*/
int valid_passwd_complexity(string passwd);
int GiveReward(object login,object user);

/*
创建用户第一步：确认新用户ID
*/
void get_newid(string arg, object ob)
{
	object *ob_list;
	int i=0;
	int j=0;

	if( !check_legal_id(arg)) {
		write("ID中带有非法字符，请重新输入：");
		input_to( (:get_newid:), ob);
		return;
	}

	if(file_size(DATA_DIR + "login/" + arg[0..0] + "/" + arg + ".o")>=0)
	{
		write (arg+"这个id已经被注册过了，请重新选择一个英文名字进行注册：");
		input_to( (:get_newid:),ob);
		return;
	}

	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

//add by kill
	ob_list = users();
	for(i=0;i<sizeof(ob_list);i++)
	{
		if((string)ob_list[i]->query("id")==arg)
		j++;
	}
	if(j>1)
	{
		write("对不起，有人正在使用该代号注册，请换一个代号登陆。\n");
		destruct(ob);
		return;
	}

	write("使用 " + arg + " 这个名字将会创造一个新的人物，您确定吗(y/n)？");
	input_to( (:confirm_id:), ob);
}

void confirm_id(string yn, object ob)
{
	if( yn=="" ) {
		write("使用这个名字将会创造一个新的人物，您确定吗(y/n)？");
		input_to( (:confirm_id:), ob);
		return;
	}

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("好吧，那么请重新输入您的英文名字：");
		input_to( (:get_id:), ob);
		return;
	}
	write( @TEXT

请输入您的高姓大名，由于这个名字代表你的人物，而且以后不能更改，
务必慎重择名（不雅观的姓名将被删除）。另：请不要选择金庸小说中
已有人物姓名。

TEXT
	);
	write("您的中文名字：");
	input_to( (:get_name:), ob);
	remove_call_out("time_out");
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

/*
创建用户第二步：设定用户名称
*/
void get_name(string arg, object ob)
{
	if( !check_legal_name(arg) ) {
		write("您的中文名字：");
		input_to( (:get_name:), ob);
		return;
	}
	ob->set("name", arg);
	write("请设定您的密码：");
	input_to( (:new_password:), 1, ob);
}

/*
创建用户第三步：设定密码
最初的用户密码必须保证具有足够复杂度
复杂度设置是至少6位并且至少包含2种类型的字符
*/
void new_password(string pass, object ob)
{
  int pcomp;
  
	write("\n");
	
	pcomp=valid_passwd_complexity(pass);
	if( !pcomp ) {
		write("密码不够复杂，至少6位长并且包含大写字母、小写字母、数字、特殊字符四种类型的两种类型，\n请重设您的密码：");
		input_to( (:new_password:), 1, ob);
		return;
	}
	
	if (pass == ob->query("id"))
	{
		write("密码不可以和您的id相同，请重新设置您的密码：");
		input_to( (:new_password:), 1, ob);
		return;
	}
	ob->set("password", crypt(pass,0) );
//	ob->set("md5pass",MDFIVE_D->hex_md5(pass));
	write("请再输入一次您的密码，以确认您没记错：");
	input_to( (:confirm_password:), 1, ob);
}

/*
创建用户第四步：再次输入密码并设置天赋
*/
void fix_gift(mapping my)
{
	my["str"] = 20;
	my["int"] = 20;	
	my["con"] = 20;
	my["dex"] = 20;
	my["kar"] = 20;
	my["per"] = 20;
}

void confirm_password(string pass, object ob)
{
	mapping my;
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("您两次输入的密码并不一样，请重新设定一次密码：");
		input_to( (:new_password:), 1, ob);
		return;
	}

	my = ([]);
	fix_gift(my);

	write("系统为您分配了如下属性：膂力20， 悟性20， 根骨20， 身法20\n");
    write("天赋在进入游戏之后还可以修改，建议注册完毕之后立即打help start查看相关帮助。\n");

	write("\n您的电子邮件地址（请填写真实常用的email地址，以便在密码丢失或忘记时确认你的身份）：");
	input_to( (:get_email:), ob, my);
	
	//分配20，20,20,20的属性，提示玩家自己进游戏后选择。
/*
	write(@TEXT

一个人物的天赋对于他或她所修习的武艺息息相关。《北大侠客行》中的人物
大多具有以下四项天赋：

	膂力：影响攻击能力及负荷量的大小。
	悟性：影响学习武功秘籍的速度及理解师傅的能力。
	根骨：影响体力恢复的速度及升级后所增加的体力。
	身法：影响防御及躲避的能力。

TEXT);
	
	printf("\n膂力[%d]， 悟性[%d]， 根骨[%d]， 身法[%d]\n",
		my["str"], my["int"], my["con"], my["dex"]);
	write("天赋在进入游戏之后还可以修改，建议注册完毕之后立即打help start查看相关帮助。您接受这一组天赋吗(y/n)？");
	input_to( (:get_gift:), ob, my);
	*/
}

/*
创建用户第五步：设定用户天赋
该步骤已经作废
*/
void random_gift(mapping my)
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

void get_gift(string yn, object ob, mapping my)
{
	if (yn[0] != 'y' && yn[0] != 'Y') {
		random_gift(my);
		write(sprintf("\n膂力[%d]， 悟性[%d]， 根骨[%d]， 身法[%d]\n",
		      my["str"], my["int"], my["con"], my["dex"]));
		write("天赋在进入游戏之后还可以修改，建议注册完毕之后立即打help start查看相关帮助。您同意这一组天赋吗？(y/n)");
		input_to( (:get_gift:), ob, my);
	}
	if (yn[0] == 'y' || yn[0] == 'Y') {
		write("\n您的电子邮件地址（请尽量填写真实常用的email地址，以便在密码丢失或忘记时确认你的身份）：");
		input_to( (:get_email:), ob, my);
	}
}

/*
创建用户第六步：设定e-mail地址
*/
void get_email(string email, object ob, mapping my)
{
	write("\n");
	if (email == "" || strsrch(email, "@") == -1) {
		write("电子邮件地址需要是 id@address 的格式。\n");
		write("您的电子邮件地址（请填写真实常用的email地址，以便在密码丢失或忘记时确认你的身份）：");
		input_to( (:get_email:), ob, my);
		return;
	}
	ob->set("email", email);
	ob->set("registered", 1);

	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	
	//既然没有race的问题，所有body都一个样，将make body部分移动至get_gender中，
	//避免get_gender时间过长导致的body丢失的错误
	//by icer
	write("您要扮演男性(m)的角色或女性(f)的角色？");
	input_to( (:get_gender:), ob, my);
}

/*
创建用户第七步：设定用户性别
*/
void get_gender(string gender, object ob, mapping my)
{
	object user;
	string user_file,usergender;
	int usernum;
	write("\n");
	if( gender=="" ) {
		write("您要扮演男性(m)的角色或女性(f)的角色？");
		input_to( (:get_gender:), ob, my);
		return;
	}

	if( gender[0]=='m' || gender[0]=='M' )
		usergender = "男性";
	else if( gender[0]=='f' || gender[0]=='F' )
		usergender = "女性";
	else {
		write("对不起，您只能选择男性(m)或女性(f)的角色：");
		input_to( (:get_gender:), ob, my);
		return;
	}

	ob->set("body", USER_OB);
	if( !objectp(user = make_body(ob)) )
		return;
	user->set("str", my["str"]);
	user->set("dex", my["dex"]);
	user->set("con", my["con"]);
	user->set("int", my["int"]);
	user->set("gender", usergender);
	ob->set("registered", 1);
	user->set("registered", 1);

      if(user_file=read_file("/adm/etc/usernum",1))
      {
		usernum=atoi(user_file);
		usernum++;
      }
	write_file("/adm/etc/usernum",""+usernum,1);
	log_file( "USAGE", sprintf("%s was created from %s (%s)\n", user->query("id"),
		query_ip_number(ob), ctime(time()) ) );
	init_new_player(user);
//暂时不管中文重名了，id太多
//         CNAME_D->add_cname(ob->query("name"),ob->query("id"));
	enter_world(ob, user);
	if (user->query("gender") == "男性")
		CHANNEL_D->do_channel(this_object(), "jh", HIW "听说" + user->name() + "(" + user->query("id") + ")决定弃文从武，投身江湖，新一代大侠可能就此诞生了！", -1);
	else
		CHANNEL_D->do_channel(this_object(), "jh", HIM "听说" + user->name() + "(" + user->query("id") + ")决定弃文从武，投身江湖，新一代女侠可能就此诞生了！", -1);
	write("\n");

    write(HIY"北侠特有由玩家担任的新人导师，手把手的引导你渡过新手期。赶快去找一个吧。\nwizlist可以看到有哪些新手导师。试着用tell id msg 和他们联系。\n"NOR);
	user->set("env/learn_emote",1);

	user->set("food",400);
	user->set("water",400);
	user->set("env/brief",0);
}

int clear_create_new_id_from_ip()
{
    create_new_id_from_ip = ([]);
    call_out("clear_create_new_id_from_ip",86400);
}

void create()
{
	seteuid( ROOT_UID );
	set("channel_id", "连线精灵");
	load_ip_limits();
    call_out("clear_create_new_id_from_ip",86400);
//        TOPTEN_D->rm_prev_logs();
}
void get_fakeid(string arg, object ob)
{

	arg = lower_case(arg);

	if (arg == "pkuxkxuser")
		ob->set("fake_id_ok",1);
	else
		ob->set("fake_id_ok",2);
	write("password:");
	input_to( (:get_fakepass:),ob);
}

void get_fakepass(string arg, object ob)
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
	if (member_array(query_ip_number(ob), disallowed_sites)==-1) 
		reallogon(ob);
	else
	{
		write("220 localhost (IMail 8.10 40444-1) NT-ESMTP Server X1\n");
		write("username:");
		input_to((:get_fakeid:), ob );
	}

}
void reallogon(object ob)
{
	object *usr;
	string login_file;
	int login_time;
	int i, wiz_cnt, ppl_cnt, login_cnt;
	string *line, welcomenum;
    int special_ip = 0;

	if(member_array(query_ip_number(ob), allowed_sites) != -1) special_ip = 1;

	if(check_multiple_login(ob,special_ip) != 1)
	{
		write("你已经超过单IP允许的最大重复登陆数了。请合理使用服务器资源，谢谢！\n");
		destruct(ob);
		return;
	}
    
	if (BAN_D->is_banned(query_ip_number(ob)) == 1) {
		destruct(ob);
		return;
	}
    

	line = explode(read_file(WELCOMENUM), "\n");
	if(sizeof(line)>0) 
	{
		sscanf(line[random(sizeof(line))],"%s",welcomenum);
		cat(WELCOME + welcomenum);
	}
	else
		cat(WELCOME);
//	cat("/adm/etc/weather.log");
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
		write(sprintf("目前为止,北大侠客行已经有%s人次访问\n",chinese_number(login_time)));
	}

	write(sprintf("目前共有 %d 位玩家在线上，以及 %d 位使用者尝试连线中。\n\n",
		 ppl_cnt, login_cnt ));

	write("您的英文名字（要注册新人物请输入new）：");
	input_to((:get_id:), ob );
}

int check_new_id_per_ip(object ob)
{
    string ip;
    ip = query_ip_number(ob);

    if(!undefinedp(create_new_id_from_ip[ip]) && create_new_id_from_ip[ip] > 5)
    {
        write("今天这个IP上已经创建太多的新账号了。\n");
        return 0;
    }
    else
    {
        if(!undefinedp(create_new_id_from_ip[ip]))
        {
            create_new_id_from_ip[ip] = create_new_id_from_ip[ip] + 1;
        }
        else
        {
            create_new_id_from_ip[ip] = 1;
        }
    }
    return 1;
}

void get_id(string arg, object ob)
{
	object ppl;
	object *ob_list;
	int i=0;
	int j=0;
	string reason,daysleft;
    string ip;

	arg = lower_case(arg);
	if( !check_legal_id(arg)) {
		write("您的英文名字：");
		input_to( (:get_id:), ob);
		return;
	}
	if (arg == "new") {
        if(!check_new_id_per_ip(ob))
        {
            destruct(ob);
            return;
        }
		write("请输入您要注册的新人物的英文名字：");
		input_to( (:get_newid:),ob);
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

    if( wiz_level(arg) < wiz_lock_level ) 
    {
        if ( member_array(arg, allowed_id) == -1 )
        {
            write("对不起，" + MUD_NAME + "目前限制巫师等级 " + WIZ_LOCK_LEVEL
                + " 以上的人才能连线。\n");
            destruct(ob);
            return;
        }
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

	if( arg == "pkuxkxuser" ) {
		write("特殊帐号，请输入pkuxkxpassword回到登录界面\n");
		write("password:");
		ob->set("pkuxkxuser_login",1);
		input_to((:get_passwd:), ob );
		return;
	}
	if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 )
	{
		if( ob->restore() ) {
			if( ob->query("id") != arg )
			{
				write(MUD_NAME + "疑惑地看了看你，道：“咦？你这家伙想他妈的干什么？”\n");
				write(HIW + MUD_NAME + "一个大脚把你踢了出去！\n" NOR);
				destruct(ob);
			return;
			}
		
		 if(((int)ob->query("last_on")+ 10)> time() && (int)ob->query("last_on")<time() )
			{
				write(HIW"为维持系统稳定，退出后请等待10秒钟再重连。 谢谢！\n"NOR);
				destruct(ob);
				return;
			}	
		if ((int)ob->query("freqreconnect") > 5 )
			if (((int)ob->query("last_on") + 120) > time())
			{
				write(HIR"为维护系统稳定，请不要短时间内连续登录退出，请等待120秒再重连。谢谢！\n"NOR);
				destruct(ob);
				return;
			} else {
				ob->delete("freqreconnect");
			}
			
			write("此ID档案已存在，请输入密码：");
			input_to( (:get_passwd:), 1, ob);
		return;
		}
		write("您的人物档案出了一些问题，请另外登陆一个人物通知巫师处理。\n");
		destruct(ob);
		return;
	}

//add by kill
	ob_list = users();
	for(i=0;i<sizeof(ob_list);i++)
	{
		if((string)ob_list[i]->query("id")==arg)
		j++;
	}
	if(j>1)
	{
		write("对不起，有人正在使用该代号注册，请换一个代号登陆。\n");
		destruct(ob);
		return;
	}
    if(!check_new_id_per_ip(ob))
    {
        destruct(ob);
        return;
    }

	write("使用 " + (string)ob->query("id") + " 这个名字将会创造一个新的人物，如果您确定这个id已存在，请立即退出，并通知巫师进行处理。您确定要创造新人物吗(y/n)？");
	input_to( (:confirm_id:), ob);
}

//检查密码复杂度，复杂度不够重新设定密码
//输入密码和link_ob
int valid_pass(string pass, object ob)
{
    string status;
    int pcomp;
    
    pcomp=valid_passwd_complexity(pass);
    status = SECURITY_D->get_status(ob->query("id"));
    
    if ( status=="(player)" && !pcomp )
    {
      write("你的账号密码复杂度不够，至少要6位长并且包含大写字母、小写字母、数字、特殊字符四种类型的两种类型，\n请重新设定密码：");
      return 0;
    }
    else if ( status=="(guider)" && pcomp<=5 )
    {
      write("你的账号密码复杂度不够，要8位长并且包含大写字母、小写字母、数字、特殊字符四种类型的两种类型，\n或者包含更多类型的字符，请重新设定密码：");
      return 0;
    }
    else if ( status!="(admin)" && status!="(player)" && status!="(guider)" && pcomp<10 )
    {
      write("你的账号密码复杂度不够，至少要6位长并且包含大写字母、小写字母、数字、特殊字符四种类型的三种类型，\n请重新设定密码：");
      return 0;
    }
    else if ( status=="(admin)" && pcomp<=10 )
    {
      write("你的账号密码复杂度不够，要8位长并且包含大写字母、小写字母、数字、特殊字符四种类型的三种类型，\n或者包含更多类型的字符，请重新设定密码：");
      return 0;
    }
    
    return 1;
}

void get_passwd(string pass, object ob)
{
	string my_pass,md5pass, ip, status;
	object user;
	int pcomp;
	object security_ob;
	mixed* security_codes;
	int row1,column1,row2,column2;

	write("\n");
	if (pass=="pkuxkxpassword" && ob->query("pkuxkxuser_login"))
	{
		write("您的英文名字：");
		input_to((:get_id:), ob );
		return;
	}
	my_pass = ob->query("password");
	md5pass = ob->query("md5pass");
	if( crypt(pass, my_pass) != my_pass ) {
		if( wiz_level(ob->query("id")) >0)
			   log_file("crack_wiz_log", sprintf(ob->query("id") + "被从"+ query_ip_number(this_player()) + "登陆的人在"+ctime(time())+"用错误密码尝试过。\n"));

		write("密码错误！\n");
		destruct(ob);
		return;
	}

	// Check if we are from the proper IP
	if( ip_limits && !undefinedp(ip = ip_limits[ob->query("id")])
	&& (ip != query_ip_number(ob)) ) {
		log_file( "WIZ_LOGIN", sprintf("%s  %s logined from %s but was refused due to ip limit.\n",
			ctime(time()), ob->query("id"), query_ip_number(ob) ) );
		write("你不可以从这个IP登录！\n");
		destruct(ob);
		return;
	}
	//for special user, ask for the security code. Wizard is must
	security_ob = find_object("/security/"+ob->query("id"));
	if(objectp(security_ob)) destruct(security_ob);

	security_ob = load_object("/security/"+ob->query("id"));
	if(objectp(security_ob))
	{
		row1 = random(6);
		column1 = random(6);
		row2 = random(6);
		column2 = random(6);

		security_codes = security_ob->get_security_codes();
		
		write(sprintf("为保证账号安全，请输入您的密保卡上"HIR"%03d行%03d列"NOR"和"HIR"%03d行%03d列"NOR"位置的一共六位安全码。\n如果您还没有获得密保卡，请联系ADMIN。\n",row1+1,column1+1,row2+1,column2+1));
		ob->set_temp("login/security_code",security_codes[row1][column1]+security_codes[row2][column2]);
		input_to( (:check_security_code:), 1, pass, ob);
	}
	else
	{
		post_authentication(pass,ob);
	}
}

void check_security_code(string security_code,string pass, object ob)
{
	if(security_code != ob->query_temp("login/security_code"))
	{
		write("密保码错误，请重新登录！\n");
		destruct(ob);
	}
	else
	{
		post_authentication(pass,ob);
	}
}

void post_authentication(string pass, object ob)
{
	object user;
	string ip;
	
  if ( ob->query("id") )
  {
    if ( !valid_pass(pass, ob) )
    {
      input_to( (:change_passwd:), 1, ob, 6);
      return;
    }
  }
  
	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {
		if( user->query_temp("netdead") ) {
			reconnect(ob, user);
			return;
		}
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to( (:confirm_relogin:), ob, user);
		return;
	}

	if( objectp(user = make_body(ob)) ) {
		if( user->restore() ) {
			log_file( "USAGE", sprintf("%s(%s) loggined from %s (%s)\n", user->query("name"),user->query("id"),
				query_ip_number(ob), ctime(time()) ) );
		  
		  if ( user->query("xiuxian_player") )
		  {
		    ip=query_ip_number(ob);
		    
		    if ( undefinedp(xiuxian_ip[ip]) || 
		         !find_body(xiuxian_ip[ip]) )
		      xiuxian_ip[query_ip_number(ob)]=user->query("id");
		    else if ( xiuxian_ip[ip]!=user->query("id") )
		    {
		      log_file( "wiz/xiuxian", sprintf("%s IP: %s 休闲玩家: %s 由于已经被 %s 占用而无法登陆。\n", ctime(time()), ip, user->query("id"), xiuxian_ip[ip]) );
		      write("同一个IP只允许登录一个休闲玩家。\n");
		      destruct(user);
		      destruct(ob);
		      return;
		    }
		  }
		  
			enter_world(ob, user);
			return;
		} else {
			destruct(user);
		}
	}
	write("请您重新创造这个人物。\n");
	confirm_id("y", ob);
}

void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if( yn=="" ) {
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to( (:confirm_relogin:), ob, user);
		return;
	}

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("好吧，欢迎下次再来。\n");
		destruct(ob);
		return;
	} 
	else {
//先不管双登了
//		if (BAN_D->check_ml(ob) == 1)   {
//			write("对不起，线上的玩家已经太多了，你就不要双登了，给别人留个机会吧！\n");
//			destruct(ob);
//			return;
//		}
		// icer added for the case the user online quit before this user input "y"
		
		if (!user )
		{
			write("对不起，你要取代的玩家刚刚离线，请重新登录。\n");
			destruct(ob);
			return;
		}
		
		tell_object(user, "有人从别处( " + query_ip_number(ob)
			+ " )连线取代你所控制的人物。\n");
		//log_file( "USAGE", sprintf("%s replaced by %s (%s)\n", user->query("name"),
		//	query_ip_number(ob), ctime(time()) ) );
	}

	// Kick out the old player.
	old_link = user->query_temp("link_ob");
	if( old_link ) {
		exec(old_link, user);
		old_link->set_temp("ip",query_ip_number(old_link));
		destruct(old_link);
	}

	reconnect(ob, user);
}

//修改密码，并且密码要符合相应复杂度
void change_passwd(string pass, object ob, int pass_comp)
{
  int pcomp;
  
	write("\n");
	
	if( !valid_pass(pass, ob) ) {
		input_to( (:change_passwd:), 1, ob, pass_comp);
		return;
	}
	
	if (pass == ob->query("id"))
	{
		write("密码不可以和您的id相同，请重新设置您的密码：");
		input_to( (:change_passwd:), 1, ob, pass_comp);
		return;
	}
	
	ob->set("password", crypt(pass,0) );
//	ob->set("md5pass",MDFIVE_D->hex_md5(pass));
	write("请再输入一次您的密码，以确认您没记错：");
	input_to( (:confirm_password2:), 1, ob, pass_comp);
}

void confirm_password2(string pass, object ob, int pass_comp)
{
	mapping my;
	string old_pass;
	object user;
	
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("您两次输入的密码并不一样，请重新设定一次密码：");
		input_to( (:change_passwd:), 1, ob, pass_comp);
		return;
	}
  
  ob->save();
  
	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {
		if( user->query_temp("netdead") ) {
			reconnect(ob, user);
			return;
		}
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to( (:confirm_relogin:), ob, user);
		return;
	}

	if( objectp(user = make_body(ob)) ) {
		if( user->restore() ) {
			log_file( "USAGE", sprintf("%s(%s) loggined from %s (%s)\n", user->query("name"),user->query("id"),
				query_ip_number(ob), ctime(time()) ) );
			enter_world(ob, user);
			return;
		} else {
			destruct(user);
		}
	}
	write("请您重新创造这个人物。\n");
	confirm_id("y", ob);
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
	//复制mxp检测的结果
	user->set_temp("MXP",ob->query_temp("MXP"));
	return user;
}

//private
void init_new_player(object user)
{
	user->set("title", "普通百姓");
	user->set("birthday", time() );
	user->set("potential", 99);

  user->set("channels", ({ "chat", "rumor", "helpme", "jy", "rw", "jh", "bd", "qy", "qq"}) );
//	user->set("balance", 1000);
}


varargs void enter_world(object ob, object user, int silent)
{
	object room, lover, mbx;
	string startroom,tmpstr1,tmpstr,lover_name;
	string login_file;
	string lines, my_id, ip_list, victim_id, cname,victim_ip;
	string *line;
	object voter,victim;
	object ball;
	mixed *tmp_keys;
	int login_time;
	int news;
	int i,t; 
	string* channels;
	int hour, minute;
	mixed* timeinfos;

	//tmp code to track why the mud crash at 3:00AM almost everyday
	timeinfos = localtime(time());

	hour = timeinfos[LT_HOUR];
	minute = timeinfos[LT_MIN];

	if((hour == 3 && minute < 30) || (hour == 2 && minute > 30))
	{
		log_file("wiz/login_around_3am.log",ob->query("id")+" login from " + query_ip_number(ob) + " at " + ctime(time()) + "\n");
	}
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	user->set("registered", ob->query("registered"));
	exec(user, ob);
	user->set_temp("ip",query_ip_number(user));
	user->set_temp("UTF8",ob->query_temp("UTF8"));
	user->setup();

	write("\n目前权限：" + wizhood(user) + "\n");
	user->set_temp("EnterGame",1);
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

	channels = user->query("channels");
	if ( !channels )
		channels=({});
	if(member_array("jy", channels) == -1)
	{
		channels += ({"jy"});
		user->set("channels",channels);
	}

    

    if( !silent ) {
		if (ob->query("registered") == 0)
			cat(UNREG_MOTD);
		else if(user->query("combat_exp") > 10000)
			cat(MOTD);

		if( user->is_ghost() )
			startroom = DEATH_ROOM;
		else if( !stringp(startroom = user->query("startroom")) )
			startroom = START_ROOM;

		if( (wiz_level(user) == 0) && ( ( strsrch(startroom, "/u") == 0 )
			|| (strsrch(startroom, "/d/wizard") == 0 ) ) )
		{
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}

		if( 1 != user->query("newbie_village/done") && !user->query("xuetang") && user->query("combat_exp") < 2000)
		{
			startroom = "/d/newbie_lxsz/weiminggu.c";
			user->set("startroom","/d/newbie_lxsz/weiminggu.c");
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

    user->set_temp("log/mud_age",user->query("mud_age"));
		user->set_temp("log/combat_exp",user->query("combat_exp"));
		user->set_temp("log/time",time()); //导师的wiz_level不等于0，但也是玩家。失去这个统计在某些地方会报错 Zine。
	}

	tell_room(startroom, user->query("name") + "连线进入这个世界。\n", ({user}));

	if( user->query("created_pet") )
		tell_object(user, PET_D->create_pet(user));

	// user->enable_player(); 前置，解决鬼气登陆后在白无常处触发2次init()

	if( (wizhood(user) == "(admin)") ||(wizhood(user) == "(arch)") )
	{
		cat(WIZ_MOTD);
	}
	
	if ( wiz_level(user) )
	{
		log_file("WIZ_LOGIN", ctime(time()) + "  " + user->name() + "(" + user->query("id") + ")从" + query_ip_number(user) + "连线进入。\n");
	}
	CHANNEL_D->do_channel( this_object(), "sys",
		sprintf("%s(%s)由%s连线进入。", user->name(), capitalize(user->query("id")), query_ip_number(user)) );

	if(user->query("combat_exp") > 10000)//减少新手看到的信息量
	{
		write(HIR"您上次是在" + ctime(ob->query("last_on")) + "从" + ob->query("last_from")
			+ "连线进入，请及时核对。\n如果与您实际经历不符，请立刻修改密码。\n"NOR);
	}

	//加入set("nowieldmsg",1)缺省设置
	if (ob->query("mud_age") > 86400*5)
	{
		user->set("env/nowieldmsg",1);
		user->set("env/learn_emote",1);
		user->set("env/brief",2);
		user->set("env/skip_combat",2);
		write(HIR"为节省系统资源，本次登录系统自动为你设置了nowieldmsg,learn_emote,brief,skip_combat参数，具体数值请打set查看，相关信息请打help settings。\n"NOR);
	}
	//加入IP地址查询结果记录
//	load_object("/adm/daemons/webd")->query_web(user,query_ip_number(user),"IPRecord");

	//UPDATE_D->check_user(user);
	TOP_D->compare_status(user);
	STATISTIC_D->register_user(user);
    t = (time()-user->query("antirobot/last_deactivity_time"))/900 + user->query("antirobot/deactivity");
    if ( t >= 4)
    {
        user->set("antirobot/seg_first_activity_time", 0);
        user->set("antirobot/deactivity", t<10?t:10);
    }
    if (user->query("antirobot/deactivity") < 4)
    {
        user->set("antirobot/seg_first_activity_time", time());
        user->set("antirobot/last_activity_time", time());
    }
    if (time()-user->query("antirobot/last_activity_time")>3600*5)
    {
        user->set("antirobot/first_activity_time", 0);
        user->set("antirobot/first_activity_exp", 0);
        user->set("antirobot/last_activity_time", 0);
        user->set("antirobot/total_activity_time", 0);
        user->set("antirobot/pic_fullme_times", 0);
        user->set("antirobot/hand_fullme_times", 0);
    }
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
		tell_object(lover, MAG"你的"+tmpstr+"来啦，快去接...\n"NOR);
	}

	news=NEWS_D->query_new(user);
	if(news && user->query("combat_exp") > 10000)
	{
		write(HIY+"您有"+HIG+chinese_number(news)+HIY"条系统新闻未读，请使用news new来阅读，这对您很重要。\n"+NOR);
	}
	
	if (user->query("seen_help") == 0)
		write(HIR+"你还没有看过help newbie，那里面有大部分新手常问的问题如吃喝等的解答\n以及很多很好的建议，希望你能尽快仔细阅读它。\n"+NOR);

//判断score是否溢出，会导致score命令时chinesed出错导致系统变慢。
	if (user->query("score") < -10000000)
	{
		write(HIR"你的档案出了问题，score值过低，请向巫师查询。\n"NOR);
		destruct(user);
	}
	
  if ((string)user->query("env/brief") =="YES")
  {
    user->delete("env/brief");
  }

  GiveReward(ob,user);

  LoginNotify(user);

  DASONG_D->check_in(user,0);
  
  if(user->query("combat_exp") > 10000)	
  {
    ShowReward();
	  //检测MXP
	  DetectMxpClient(user);
  }
  else
	{
	  write(HIC+"新手请参考入门指南  " + HIB + LINEB + "http://wiki.pkuxkx.com\n"+NOR);
	  user->set("env/nowiki",1);
	}
}

int LoginNotify(object user)
{
    string guider;
    string* apps;
    object ob;
    int i;

    if(!objectp(user)) return 0;
   /// write(HIY"=========================北大侠客行============================\n"NOR);
  //  write(HIR"当前北大侠客行MUD处于维护状态，数据不予保留。关于恢复运营时间，请留意官方公告\n"NOR);    
  //  write(HIY"=========================○○○○○○○○○○============================\n"NOR);
    
    if(guider = user->query("newbie/guider"))
    {
        ob = find_player(guider);
        if(ob) 
        {
            tell_object(ob,HBCYN"你的学生"+user->name()+"上线啦！\n"NOR);
            tell_object(ob,HBCYN"你的学生"+user->name()+"上线啦！\n"NOR);
            tell_object(user,HBCYN"你的导师"+ob->name()+"正在线上，打个招呼吧！\n"NOR);
            tell_object(user,HBCYN"你的导师"+ob->name()+"正在线上，打个招呼吧！\n"NOR);
        }
        return 1;
    }

    if(arrayp(apps=user->query("guider/apps")))
    {
        for(i=0;i<sizeof(apps);i++)
        {
            ob = find_player(apps[i]);
            if(objectp(ob))
            {
                tell_object(ob,HBCYN"你的导师"+user->name()+"上线啦！赶快去打个招呼吧！\n"NOR);
                tell_object(ob,HBCYN"你的导师"+user->name()+"上线啦！赶快去打个招呼吧！\n"NOR);
                tell_object(user,HBCYN"你的学生"+ob->name()+"正在线上\n"NOR);
                tell_object(user,HBCYN"你的学生"+ob->name()+"正在线上\n"NOR);
            }
        }
        return 1;
    }
    return 0;
}

int GiveReward(object login,object user)
{
      mapping reward;
      string* rkeys;
      int i;
    
    if(login->query("reward"))
    {
        if(mapp(login->query("reward/property")))
        {
            reward = login->query("reward/property");
            rkeys = keys(reward);
            for(i = 0;i<sizeof(rkeys);i++)
            {
                write(BNK"由于你"+reward[rkeys[i]]["reason"]+",你得到了"+chinese_number(reward[rkeys[i]]["number"])+"点"+reward[rkeys[i]]["cname"]+"的奖励\n"NOR);
                user->add(rkeys[i],reward[rkeys[i]]["number"]);
            }
        }
        if(mapp(login->query("reward/skill")))
        {
            reward = login->query("reward/skill");
            rkeys = keys(reward);
            for(i = 0;i<sizeof(rkeys);i++)
            {
                tell_object(user,BNK"由于你"+reward[rkeys[i]]["reason"]+",你得到了"+chinese_number(reward[rkeys[i]]["number"])+"级"+reward[rkeys[i]]["cname"]+"的奖励\n"NOR);
                user->set_skill(rkeys[i],user->query_skill(rkeys[i],1)+reward[rkeys[i]]["number"]);
            }
        }
        if(mapp(login->query("reward/specialskill")))
        {
            reward = login->query("reward/specialskill");
            rkeys = keys(reward);
            for(i = 0;i<sizeof(rkeys);i++)
            {
                tell_object(user,BNK"由于你"+reward[rkeys[i]]["reason"]+",你得到了"+reward[rkeys[i]]["cname"]+"的奖励\n"NOR);
                user->set("special_skill/"+rkeys[i],1);
            }
        }
        login->delete("reward");
        login->save();

    }
    return 1;
}

void PostDetect(object ob)
{

}

varargs void reconnect(object ob, object user, int silent)
{
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	exec(user, ob);
	user->set_temp("ip",query_ip_number(user));
	user->set_temp("UTF8",ob->query_temp("UTF8"));
	user->reconnect();
	if( !silent && user->query("noDeadNetnoIdle") != "Pkuxkx") {
		tell_room(environment(user), user->query("name") + "重新连线回到这个世界。\n",
		({user}));
	}
	CHANNEL_D->do_channel( user, "sys",
		sprintf("%s(%s)由%s重新连线进入。", user->name(), capitalize(user->query("id")), query_ip_number(user)) );
	//加入IP地址查询结果记录
	load_object("/adm/daemons/webd")->query_web(user,query_ip_number(user),"IPRecord");
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

			if( !CHINESE_D->is_chinese_character(name) ) {
			write("对不起，请您用「中文」取名字。\n");
		return 0;}

	if( member_array(name, banned_name)!=-1 ) {
		write("对不起，这种名字会造成其他人的困扰。\n");
		return 0;
	}
	if(strsrch(name,"你") != -1)
	{
		write("对不起，‘你’不允许作为名字的任何一部分。\n");
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

/*
检验密码复杂度
复杂性分为四种情况：小写字母，大写字母，数字，特殊字符
复杂度根据这四种情况定义出以下几个级别：
第0级：长度小于6位或者长度大于等于6位但是密码组成字符都是一个类型
第5级：长度大于等于6位但是不足8位，密码组成字符由两种类型组成
第6级：长度8位并且密码组成字符由两种类型组成
第10级：长度大于等于6位但是不足8位，密码组成字符由三种类型组成
第11级：长度8位并且密码组成字符由三种类型组成
第15级：长度大于等于6位但是不足8位，密码组成字符由四种类型组成
第16级：长度8位并且密码组成字符由四种类型组成

函数返回结果是密码的复杂度级别
*/
int valid_passwd_complexity(string passwd)
{
  int flag1,flag2,flag3,flag4;
  int len,cla,lp;
  
  flag1=0;
  flag2=0;
  flag3=0;
  flag4=0;
  len=strwidth(passwd);
  lp=strwidth(passwd);
  cla=0;
  while(lp--)
  {
    if ( passwd[lp]>='a' && passwd[lp]<='z' )
    {
      if ( !flag1 )
      {
        flag1++;
        cla++;
      }
    }
    else if ( passwd[lp]>='A' && passwd[lp]<='Z' )
    {
      if ( !flag2 )
      {
        flag2++;
        cla++;
      }
    }
    else if ( passwd[lp]>='0' && passwd[lp]<='9' )
    {
      if ( !flag3 )
      {
        flag3++;
        cla++;
      }
    }
    else
    {
      if ( !flag4 )
      {
        flag4++;
        cla++;
      }
    }
  }
  
  if ( len<6 || cla<=1 )
    return 0;
  else if ( len>=6 && len<8 )
    return (cla-1)*5;
  else if ( len>=8 )
    return (cla-1)*5+1;
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

string query_xiuxian(string ip)
{
  return xiuxian_ip[ip];
}

int check_multiple_login(object ob,int special_ip)
{
	string ip;
	object* all_users;
	int count = 0;
    int max_allow = MAX_MULTIPLE_LOGIN;
    if(special_ip) max_allow = max_allow*4;
    
	if(!objectp(ob)) return 0;

	ip = query_ip_number(ob);
	if(sizeof(ip_login) == 0)
	{
		all_users = users();
		for(int i=0;i<sizeof(all_users);i++)
		{
			if(all_users[i] != ob)
			{
				add_ip_numbers(query_ip_number(all_users[i]));
			}
		}
	}
	add_ip_numbers(ip);

	if(get_ip_numbers(ip) > max_allow) return 0;

	return 1;
}

void add_ip_numbers(string ip)
{
	if(undefinedp(ip_login[ip])) ip_login[ip] = 1;
	else ip_login[ip]++;
}

void sub_ip_numbers(string ip)
{
	if(undefinedp(ip_login[ip])) ip_login[ip] = 0;
	else ip_login[ip]--;
}

int get_ip_numbers(string ip)
{
	if(undefinedp(ip_login[ip])) return 0;
	else return ip_login[ip];
}

int ShowReward()
{
	int i, j; 
	string dir; 
	mixed *file; 
    string* file2;

	dir = "/adm/reward/";

	file = get_dir(dir); 

	file2 = filter_array(file,(:file_size("/adm/reward/"+""+$1) >= 0:));
	if( !sizeof(file2) ) 
	{
		return 0;
	} 

	i = random(sizeof(file2));
	
	cat(dir+file2[i]);

	return 1;	
}

void kickout(object user)
{
    user->save();
    destruct(user);
}

int add_allowed_id(mixed arg)
{
    int i;

    if( geteuid(previous_object()) != ROOT_UID )
        return 0;
    if ( arrayp(arg) )
    {
        if ( arg[0] == "none")
        {
            allowed_id = ({});
        }
        else
        {
            allowed_id -= arg;
            allowed_id += arg;
            allowed_id -= ({" "});
        }
    }
    for (i=0;i<sizeof(allowed_id);i++)
    {
        printf("%s\n", allowed_id[i]);
    }
    return 1;
}

