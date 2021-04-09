// logind.c
// Modify by Yu Jue 1997.8.6
// Modify by Yu Jue 1999.6.21

#include <ansi.h>
#include <command.h>
#include <login.h>

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
int ppls = 0;

string *banned_name = ({
        "自己", "杀手", "闪电", "寒雨","逍遥","雪人","祈雨",
        "某人", "尸体", "金庸", "我们","你们", "他们", "大家", 
        "他妈的", "去你的", "毛泽东", "邓小平", "江泽民", "巫师",
        "中神通", "书剑", "操你妈", "干你娘"
});

protected void get_id(string arg, object ob);
protected void confirm_id(string yn, object ob);
object make_body(object ob);
protected void init_new_player(object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(object, string arg);

protected void random_gift(mapping my, int select)
{
        int i = 10, j;
        int tmpstr, tmpint, tmpcon, tmpdex;

        tmpstr = tmpint = tmpcon = tmpdex = 10;

        switch (select) {
                case 1: tmpstr = i = my["str"]; break;
                case 2: tmpint = i = my["int"]; break;
                case 3: tmpcon = i = my["con"]; break;
                case 4: tmpdex = i = my["dex"];
        }
        i = 50 - i;
        while (i--) {
                j = random(4);
                if (j == select - 1) {
                        i++;
                        continue;
                }
                switch (j) {
                        case 0: tmpstr++; break;
                        case 1: tmpint++; break;
                        case 2: tmpcon++; break;
                        case 3: tmpdex++;
                }
        }
        if (tmpstr <= 30) my["str"] = tmpstr; else my["str"] = 30;
        if (tmpint <= 30) my["int"] = tmpint; else my["int"] = 30;
        if (tmpcon <= 30) my["con"] = tmpcon; else my["con"] = 30;
        if (tmpdex <= 30) my["dex"] = tmpdex; else my["dex"] = 30;
        // next 3 are randomly selected
        my["kar"] = 10 + random(21); // 福缘
        my["per"] = 10 + random(21); // 容貌
        my["pur"] = 10 + random(21); // 
        my["bos"] = 1  + random(25); // 内性练不同的内功就一些特性。分为8个等级，
        my["des"] = 1  + random(1000); // 不同事件的命运的关系
}

void create() 
{
        seteuid(getuid());
        set("channel_id", "连线精灵");
        if (file_size("/log/ppls") > 0) sscanf(read_file("/log/ppls"), "%d", ppls);
}

void logon(object ob)
{
        object *usr;
        int i, wiz_cnt, ppl_cnt, login_cnt;

        write_file("/log/ppls", sprintf("%d", ++ppls), 1);
// 防止有恶意的玩家用 KMUD 等工具捣乱
        usr = filter_array(children(LOGIN_OB), (: interactive :));
        i = sizeof(usr);
        login_cnt = 0;
        while (i--) if (query_ip_number(usr[i]) == query_ip_number(ob)) login_cnt++;
        if (login_cnt > 3) {
                destruct(ob);
                return;
        }
// Add by Yu Jue 1997.8.6
//      write("\n我们建议使用 800 * 600 的分辨率进入"+MUD_NAME+"。\n");
//      write("\nAre you using BIG5 font [Y|N]?\n\n");
//        input_to("gb_big5", ob);
// }
// void gb_big5(string arg, object ob)
// {
//        object *usr;
//        int i, wiz_cnt, ppl_cnt, login_cnt;
//      if( arg[0]=='y' || arg[0]=='Y' ) ob->set_temp("big5", 1);

        if (BAN_D->is_banned(query_ip_number(ob)) == 1) {
                write("您的地址在" + MUD_NAME + "不受欢迎。\n");
                destruct(ob);
                return;
        }
//add by look
/* no need by yuj
			if (file_size("/log/anti_autologin") > 0) sscanf(read_file("/log/anti_autologin"), "%s", ipaddress);
			if(ipaddress==query_ip_number(ob)) 
			{
				write("请勿恶意登录。\n");
                		destruct(ob);
                		return;
                	}
                        write_file( "/log/anti_autologin",sprintf("%s",query_ip_number(ob)),1);
*/
        write(sprintf("\n%76|s\n", MUD_NAME));
        write(sprintf("%76|s\n", "- " __VERSION__ " -"));
        cat("/adm/etc/welcome"+random(8));
        "/cmds/usr/mudlist"->main();
        
        write("本站总共访问人次：" HIY + chinese_number(ppls));
        write(NOR "\n目前人数限制：" HIY + chinese_number(MAX_USERS) + NOR);
        write("\n");
        UPTIME_CMD->main(1);

        usr = users();
        wiz_cnt = 0;
        ppl_cnt = 0;
        login_cnt = 0;
        for(i=0; i<sizeof(usr); i++) {
                if( !environment(usr[i]) ) login_cnt++;
                else if( wizardp(usr[i])) {if (!usr[i]->query("env/invisibility")) wiz_cnt++;}
                else ppl_cnt++;
        }
        write(sprintf("目前共有%s位巫师、%s位玩家在线上，以及%s位玩家尝试连线中。\n\n",
        chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) ));

        write("您的英文名字(ID)是：");
        input_to( (: get_id :), ob );
}

protected void get_id(string arg, object ob)
{
        int i;
        object ppl, *usr;
        string ip = query_ip_number(ob);

        arg = lower_case(arg);
        if( !check_legal_id(arg)) {
                write("您的英文名字(ID)是：");
                input_to("get_id", ob);
                return;
        }

        if (!"/adm/daemons/sited"->is_valid(arg, ip)) {
                log_file("SITE", sprintf("%-9s从 %-16s被拒绝(%s)\n", arg, ip, ctime(time())));
                write("对不起，这个英文名字不能从当前地址登录。\n");
                confirm_id("n", ob);
                return;
        }

        if( (string)ob->set("id", arg) != arg ) {
                write("Failed setting user name.\n");
                destruct(ob);
                return;
        }

#ifdef MAX_USERS
        ppl = find_body(arg);
        usr = filter_array(users(), (: environment :));
        usr -= filter_array(usr, (: wiz_level :));
        if( !ppl && !wiz_level(arg)
        && sizeof(usr) >= MAX_USERS ) {
                // Only allow reconnect an player in MUD when MAX_USERS exceeded.
                write("对不起，目前" + MUD_NAME + "的玩家已经太多了，请待会再来。\n");
                destruct(ob);
                return;
        }
// check multilogin Yu Jue 1999-03-23
        if (!ppl && "/adm/daemons/sited"->is_multi(arg, ip)) {
                destruct(ob);
                return;
        }
#endif

        if( wiz_level(arg) < wiz_lock_level ) {
                write("对不起，" + MUD_NAME + "目前限制巫师等级 "+wiz_lock_level+" 以上的人才能连线。\n");
//              write("北京新浪站已经准备就绪，请玩家连接到 210.72.224.184 5555 继续游戏。\n");
                destruct(ob);
                return;
        }

        if( arg=="guest" ) {
                // If guest, let them create the character.
                ob->set("password", "SJGUEST");
                write("您的中文名字：");
                input_to("get_name", ob);
                return;
        }

        if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 ) {
                if( ob->restore() ) {
                        write("英文 ID 已经存在，请输入密码或者直接回车重新选择 ID。\n");
                        write("请您输入这个人物的识别密码(passwd)：");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("您的人物档案出了一些问题，请利用 guest 人物通知巫师处理。\n");
                destruct(ob);
                return;
        }

// 防止两个以上的玩家用同一 id
        usr = filter_array(children(LOGIN_OB), (: interactive :));
        i = sizeof(usr);
        while (i--) if (usr[i] != ob && usr[i]->query("id") == arg) break;
        if (i >= 0) {
                write("有其他玩家也在使用这个 ID 创造新人物，请重新输入。\n您的英文名字(ID)是：");
                input_to("get_id", ob);
                return;
        }
// Add by Yu Jue 1998.8.24

        write("使用 " + arg + " 这个名字将会在此创造一个新的人物，您确定吗(y/n)？");
        input_to("confirm_id", ob);
}

protected void get_passwd(string pass, object ob)
{
        string my_pass;
        object user;

        write("\n");
        if (pass == "") {
                write("您的英文名字(ID)是：");
                input_to("get_id", ob);
                return;
        }
        
        my_pass = ob->query("password");
        if( crypt(pass, my_pass) != my_pass ) {
                write("\n密码错误！\n");
                destruct(ob);
                return;
        }
        ob->set("password", crypt(pass, "SJ"));
        ob->save();


        // Check if we are already playing.
        user = find_body(ob->query("id"));
        if (user) {
                if( user->query_temp("netdead") ) {
                        reconnect(ob, user);
                        return;
                }
                write("人物目前正在游戏当中，您可以取而代之，确定请打 Y ，否则请打 N 。确定吗？(y/n)");
                input_to("confirm_relogin", ob, user);
                return;
        }

        if (objectp(user = make_body(ob))) {
                if( user->restore() ) {
                        log_file( "USAGE", sprintf("%-19s从 %-16s登录(%s)\n",
                                user->query("name")+"("+capitalize(""+user->query("id"))+")",
                                query_ip_number(ob), ctime(time())));

                        enter_world(ob, user);
                        return;
                }
                destruct(user);
        }
        write("请您重新创造这个人物。\n");
        confirm_id("y", ob);
}

protected void confirm_relogin(string yn, object ob, object user)
{
        object old_link;

        if (!user) {
                write("您要取代的人物已经退出游戏，请重新登录。\n");
                destruct(ob);
                return;
        }
        if (yn[0]!='y' && yn[0]!='Y') {
                write("好吧，欢迎下次再来" + MUD_NAME + "。\n");
                destruct(ob);
                return;
        }
        tell_object(user, "\n有人从别处(" + query_ip_name(ob)+ ")连线取代你所控制的人物。\n\n");
        log_file( "USAGE", sprintf("%-19s被 %-16s代替(%s)\n",
                user->query("name")+"("+capitalize(""+user->query("id"))+")",
                query_ip_number(ob), ctime(time())));

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
                write("请重新输入您的英文名字：");
                input_to("get_id", ob);
                return;
        }
        write("密码的长度要在五到八个字符之间，并且必须包含数字和英文大写字母。\n请设定您的密码：");
        input_to("new_password", 1, ob);
}

protected void new_password(string pass, object ob)
{
        int i = strwidth(pass), j = 0 ,k = 0;
        
        write("\n");
        if( (strwidth(pass)<5) || (strwidth(pass) > 8 )) {
                write("密码的长度要在五到八个字符之间，\n请重设您的密码：");
                input_to("new_password", 1, ob);
                return;
        }
        while(i--) {
                if( pass[i]>='0' && pass[i]<='9' ) j++;
                if( pass[i]>='A' && pass[i]<='Z' ) k++;
        }
        if( j < 1 || k < 1 ) {
                write("对不起，您的密码必须包含数字和英文大写字母。\n");
                write("请重设您的密码：");
                input_to("new_password", 1, ob);
                return;
                }
  
        ob->set("password", crypt(pass,0) );              
//      ob->set("password", crypt(pass, "SJ") );
        write("\n请再输入一次您的密码，以确认您没记错：");
        input_to("confirm_password", 1, ob);
}

protected void confirm_password(string pass, object ob)
{
        string old_pass;
        write("\n");
        old_pass = ob->query("password");
        if( crypt(pass, old_pass)!=old_pass ) {
                write("您两次输入的密码不一样，请重新设定密码：");
                input_to("new_password", 1, ob);
                return;
        }
        write(
"\n"
"请输入您的高姓大名，由于这个名字代表你的人物，而且以后不能随意更改，\n"
"务必慎重择名（不雅观的姓名将被删除）。\n"
HIY "另请注意：不要选择金庸小说中的人物姓名和常用称呼。\n" NOR
"\n"
);
        write("您的中文名字：");
        input_to("get_name", ob);
}

protected string display_attr(int gift)
{
        if (gift > 24) return HIY + gift + NOR;
        if (gift < 16) return CYN + gift + NOR;
        return "" + gift;
}

protected void get_name(string arg, object ob)
{
        if( !check_legal_name(ob, arg) ) {
                write("您的中文名字：");
                input_to("get_name", ob);
                return;
        }
        ob->set("name", arg);

        write("\n\n"
                "一个人物的天赋对于他或她所修习的武艺息息相关。\n"
                + MUD_NAME + "中的人物具有以下四项天赋：\n\n"
                " 1. 膂力：影响伤害力、防御能力、饭量、负荷量和气的增量。\n"
                " 2. 悟性：影响学习速度、理解师傅的能力和精的增量。\n"
                " 3. 根骨：影响体力恢复速度、受伤承受能力和其它三项的增量。\n"
                " 4. 身法：影响攻击、躲避能力和精力的增量。\n\n"
                "您可以自己指定其中一项的值，或者输入 0 由系统随机产生。\n"
                "请输入您的选择(0-4)："
        );
        input_to("select_gift", ob);
}

protected void get_gift(string yn, object ob, mapping my, int select)
{
        if (yn[0] != 'y' && yn[0] != 'Y') {
                random_gift(my, select);
                write(sprintf("\n膂力[%s]，悟性[%s]，根骨[%s]，身法[%s]\n您同意这一组天赋吗？",
                        display_attr(my["str"]),
                        display_attr(my["int"]),
                        display_attr(my["con"]),
                        display_attr(my["dex"])));
                input_to("get_gift", ob, my, select);
                return;
        }
        write("\n您的电子邮件地址：");
        input_to("get_email", ob, my);
}

protected void select_gift(string yn, object ob)
{
        int i;

        if (!sscanf(yn, "%d", i) || i < 0 || i > 4) {
                write("\n输入错误，请重新选择：");
                input_to("select_gift", ob);
                return;
        }
        if (i) {
                write("\n请输入您想要的数值(10-30)：");
                input_to("set_gift", ob, ([]), i);
        } else get_gift(" ", ob, ([]), i);
}

protected void set_gift(string yn, object ob, mapping my, int select)
{
        int i;

        if (!sscanf(yn, "%d", i) || i < 10 || i > 30) {
                write("\n数值错误，请重新输入：");
                input_to("set_gift", ob, my, select);
                return;
        }
        switch (select) {
                case 1: my["str"] = i; break;
                case 2: my["int"] = i; break;
                case 3: my["con"] = i; break;
                case 4: my["dex"] = i;
        }
        get_gift(" ", ob, my, select);
}

protected void get_email(string email, object ob, mapping my)
{
        object user;

        write("\n");
        if (email == "" || strsrch(email, "@") < 2) {
                write("电子邮件地址必须是 id@address 的格式。\n您的电子邮件地址：");
                input_to("get_email", ob, my);
                return;
        }
        ob->set("email", email);

        // If you want do race stuff, ask player to choose one here, then you can
        // set the user's body after the question is answered. The following are
        // options for player's body, so we clone a body here.
        ob->set("body", USER_OB);
        if (!objectp(user = make_body(ob))) {
                destruct(ob);
                return;
        }
        user->set("str", my["str"]);
        user->set("dex", my["dex"]);
        user->set("con", my["con"]);
        user->set("int", my["int"]);
        user->set("kar", my["kar"]);
        user->set("per", my["per"]);

        if (ob->query("id") != "guest") {
                ob->set("registered", 1);
                user->set("registered", 1);
        }

        write("您要扮演男性(m)的角色或女性(f)的角色？");
        input_to("get_gender", ob, user);
}

protected void get_gender(string gender, object ob, object user)
{
        write("\n");
        if( gender=="" ) {
                write("您要扮演男性(m)的角色或女性(f)的角色？");
                input_to("get_gender", ob, user);
                return;
        }

        if( gender[0]=='m' || gender[0]=='M' ) user->set("gender", "男性");
        else if( gender[0]=='f' || gender[0]=='F' ) user->set("gender", "女性" );
        else {
                write("对不起，您只能选择男性(m)或女性(f)的角色：");
                input_to("get_gender", ob, user);
                return;
        }

        log_file( "USAGE", sprintf("%-19s从 %-16s创建(%s)\n",
                user->query("name")+"("+capitalize(""+user->query("id"))+")",
                query_ip_number(ob), ctime(time())));
        init_new_player(user);
        enter_world(ob, user);
}

object make_body(object ob)
{
        object user;

        if (previous_object() && getuid(previous_object()) != ROOT_UID) return 0;
        user = new(ob->query("body"));
        if(!user) {
                write("现在可能有人正在修改使用者物件的程序，无法进行复制。\n\n");
                return 0;
        }
        seteuid(ob->query("id"));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
        user->set_name( ob->query("name"), ({ ob->query("id")}) );
        return user;
}

protected void init_new_player(object user)
{
        user->set("title", "普通百姓");
        user->set("birthday", time() );
        user->set("potential", 99);
        user->set("food", 200);
        user->set("water", 200);
        user->set("env/wimpy", 50);
//      user->set("enter_wuguan", 1);
        user->set("channels", ({ "chat", "rumor", "party" ,"new" }) );
}
                
varargs void enter_world(object ob, object user, int silent)
{
        object mbx;
        string startroom;
        int num;

        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        // user->set_temp("big5", ob->query_temp("big5"));
        user->set("registered", ob->query("registered"));

        exec(user, ob);
        tell_object(user, "\n您目前的权限是：" + wizhood(user) + "\n");
        user->setup();

        // In case of new player, we save them here right aftre setup 
        // compeleted.
        user->save();
        ob->save();


        UPDATE_D->get_cloth(user);
                if( !silent ) {
                if (ob->query("registered") == 0) 
                        cat(UNREG_MOTD);
                else 
                        cat(MOTD);
                user->set_temp("last_damage_from", "莫名其妙地");
                user->set_temp("combat_exp", user->query("combat_exp"));
                user->set_temp("mud_age", user->query("mud_age"));
                if( !stringp(startroom = user->query("startroom")) )
                                {
                                   startroom = START_ROOM;
                            // add  log system code in here @by wzfeng
                                   rm( LOG_D->query_log_file( user->query("id") ) );
                                   LOG_D->do_log( user, sprintf("你充满武侠色彩的书剑由%s开始。", 
                                   load_object( startroom )->query("short") ));
                                }
                if ( ! user->query("离馆")) 
                        startroom = "/d/wuguan/menlang";

                if( user->is_ghost() )
                        startroom = DEATH_ROOM;
  
                if (wizardp(user) && file_size("/u/"+user->query("id")+"/workroom.c") > 0)
                        startroom = "/u/"+user->query("id")+"/workroom";

                if( file_size(startroom+".c") > 0 )
                        user->move(startroom);
                else {
                        write("您上次退出的地方已经消失了。\n");
                        user->move(START_ROOM);
                        startroom = START_ROOM;
                        user->set("startroom", START_ROOM);
                }
                                
                if (ob->query("last_on"))
                        write("您上次连线地址是 " HIR + ob->query("last_from") + NOR 
                                " 在 " HIR + ctime(ob->query("last_on")) + NOR "\n");
                tell_room(environment(user), user->short() + "连线进入这个世界。\n",
                        ({user}));

                mbx=user->query_temp("mbox_ob");
                if (!mbx) {
                        mbx=new(MAILBOX_OB);
                        mbx->set_owner(user->query("id"));
                }
                num=mbx->query_new_mail();
                if( num>0 ) {
                        write( HIR + "\n书剑网络游戏通知你：有您"
                        +chinese_number(num)+
                        "封信！请到驿站来一趟．．．\n\n" + NOR);
                }
                destruct(mbx);
        }

        user->set_temp("combat_exp", user->query("combat_exp"));
        user->set_temp("time", time());
        CHANNEL_D->do_channel( this_object(), "sys",
                sprintf(NOR "%s" HIR " 由 " HIG "%s" HIR " 连线进入。", user->short(1), query_ip_name(user)) );
}

varargs void reconnect(object ob, object user, int silent)
{
        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        // user->set_temp("big5", ob->query_temp("big5"));
        exec(user, ob);
        user->reconnect();
        if( !silent ) tell_room(environment(user), user->name() + "重新连线回到这个世界。\n", ({user}));
        CHANNEL_D->do_channel( this_object(), "sys",
                sprintf(NOR "%s" HIR " 由 " HIG "%s" HIR " 重新连线进入。", user->short(1), query_ip_name(user)) );
}

int check_legal_id(string id)
{
        int i;

        i = strwidth(id);

        if( (strwidth(id) < 3) || (strwidth(id) > 8 ) ) {
                write("对不起，您的英文名字必须是 3 到 8 个英文字母。\n");
                return 0;
        }

        while(i--)
                if( id[i] < 'a' || id[i] > 'z' ) {
                        write("对不起，您的英文名字只能用英文字母。\n");
                        return 0;
                }

        return 1;
}

int check_legal_name(object ob, string name)
{
        int i;

        i = strwidth(name);

        if (i < 2 || i > 4 ) {
                write("对不起，您的中文名字必须是 2 到 4 个中文字。\n");
                return 0;
        }

        while(i--)
                if(!is_chinese(name[i..<0]) ) {
                        write("对不起，请您用「中文」取名字。\n");
                        return 0;
                }

        if( !wiz_level(ob->query("id"))
        && member_array(name, banned_name)!=-1 ) {
                write("对不起，这种名字会造成其他人的困扰。\n");
                return 0;
        }

        return 1;
}

object find_body(string name)
{
        object ob, *body;

        if( objectp(ob = find_player(name)) )
                return ob;
        body = children(USER_OB);
        for(int i=0; i<sizeof(body); i++)
                if( userp(body[i]) && getuid(body[i]) == name ) return body[i];

        return 0;
}

int set_wizlock(int level)
{
        if( wiz_level(this_player(1)) < level )
                return 0;
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        wiz_lock_level = level;
        return 1;
}
