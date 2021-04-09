//给玩家用来寄存和赠送东西的。以避免玩家必须同时在线
//当机丢失

inherit NPC;
#include <ansi.h>
#include <localtime.h>

void send_mail(string rcvr, string title,string text,string time,string from,string to);
void create()
{
	set_name("晓晓",({"lxiao npc"}));
    set("title",HIY"散财龙女"NOR);
	set("long",
	"这是一个娇小的女孩子，身穿粉红柔衫，一头黑发梳成两条长长的辩子垂在胸前，\n点漆双眸、樱红小口、肤色白皙，真如一个可爱至极的娃娃。\n"
	);
	set("inquiry", ([
			"转交":"如果你得到了巫师的认可，你可以让我帮你转交任何东西给其他玩家，不过当机就会丢失哦。(xforward sth to sb as reason)\n比如 xforward gem to xxx as 征文奖励\n如果你想取回来，输入 xgetback 序号 就可以。xlist 可以查看属于你的东西。\nxaccept可以拿走所有别人转交给你的东西\n不过，你自己要注意放的东西，如果你放块冰，化了可就没了。如果你放个人，会怎么样你知道。。\n",
			"广告":"如果你得到了巫师的认可，你可以让我帮发广告哦。xad 内容。内容里支持颜色，如 $HIY$。xreset命令全部清空。重启信息丢失。用xtest命令可以测试广告。\n",
			"生日":"你可以用xregister命令来登记你的实际生日。\n",
			"生日礼物":"实名用户可以在生日当月用xgetgift命令领取生日礼物。\n",
       ]));
   	set_max_encumbrance(100000000);
    set("gender","女性");
    set("age",22);
    set("per",40);
    set("no_steal",1);
    set("no_beg",1);
	set("str", 35);
	set("int", 23);
	set("con", 24);
	set("dex", 38);

	set("jiali", 100);
	set("combat_exp", 18000000);
	set("level",40);
	set("score",1000);
	set("chat_chance", 30);
	set("max_neili", 10000);

	set_skill("force", 350);
	set_skill("riyue-shengong", 350);
	set_skill("dodge", 250);
	set_skill("parry", 250);
	set_skill("sword",350);
	set_skill("qixian-jian",350);
	set_skill("feitian-shenfa", 250);
	set_skill("literate",300);
	map_skill("force", "riyue-shengong");
	map_skill("parry", "qixian-jian");
	map_skill("dodge", "feitian-shenfa");
	map_skill("sword","qixian-jian");
	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: perform_action, "sword.kaishan" :),
		(: perform_action, "sword.kaishan" :),
		(: perform_action, "sword.kaishan" :),
		(: perform_action, "sword.kaishan" :),
		(: perform_action, "sword.kaishan" :),
	}) );
    carry_object("/clone/cloth/female3-cloth")->wear();
    carry_object("/clone/cloth/female-shoe")->wear();
    carry_object("/clone/weapon/sword/guqin")->wield();

	setup();
    set_temp("oblist",({}));
    set("allowed",({"lzkd"}));
    set("ads",({}));
    call_out("post_ad",30);
}

void init()
{
    if(member_array(this_player()->query("id"),query("allowed")) != -1 || wizardp(this_player()))
    {
        add_action("do_forward","xforward");
        add_action("do_list","xlist");      
        add_action("do_getback","xgetback");
        add_action("do_ad","xad");
		add_action("do_reset","xreset");
		add_action("do_test","xtest");
    }
    add_action("do_accept","xaccept");
    add_action("do_register","xregister");
    add_action("do_getcake","xgetgift");    
}

//登记生日
int birth_input(string arg,object me)
{
	int month,day;
	if(!arg)
	{
		tell_object(me,WHT"你输入了一个无效的参数！\n"NOR);
		return 1;
	}
	if (sscanf(arg,"%d %d",month,day)!=2)
	{
		tell_object(me,WHT"你输入了一个无效的参数！\n"NOR);
		return 1;
	}
	if (month<1||month>12)
	{
		tell_object(me,WHT"请正确输入月份！\n"NOR);
		return 1;
	}
	if (day<1||day>31)
	{
		tell_object(me,WHT"请正确输入日期！\n"NOR);
		return 1;
	}
	me->set("birthdaycake/month",month);
	me->set("birthdaycake/day",day);	
	write("你的生日登记好了，到时来领礼物吧。\n");
	return 1;	
}

int do_register(object me)
{
	me=this_player();
	if (me->query("birthdaycake/month"))
		return notify_fail("你已经登记过了！\n");
	tell_object(me,"请用阿拉伯数字输入你生日的月份和日期：<月> <日>");
	input_to( (: birth_input :),me);
	return 1;
}

//实名用户生日当月领取蛋糕
int do_getcake()
{
	object me=this_player();
	object ob;
    	object* oblist = query_temp("oblist");	
	mixed date_local, year, month;
	int time;
	time=time();
	date_local=localtime(time);
	year=date_local[LT_YEAR];
	month=date_local[LT_MON]+1;

	if(!me->query("birthdaycake/month")||!me->query("birthdaycake/day"))
		return notify_fail("只有登记生日才能领取生日礼物！\n");    
	if(!me->is_realuser() && !wizardp(me))
		return notify_fail("只有实名制玩家才能领取生日蛋糕！\n");    
	if ( month != me->query("birthdaycake/month"))
		return notify_fail("你好像不是这个月的生日吧！\n");
        if(me->query("birthdaycake/last_get") == year)
		return notify_fail("你今年的生日礼物已经领过了！\n");
	ob = new("/clone/gift/birthday");
	ob->move(this_object());
	ob->set_temp("tt_forward/owner","北大侠客行");
	ob->set_temp("tt_forward/to",me->query("id"));
	ob->set_temp("tt_forward/reason","生日礼物");
	oblist += ({ob});
	set_temp("oblist",oblist);
    	me->set("birthdaycake/last_get",year);
	write("你可以用xaccept领取你的生日礼物。\n");
	return 1;    
}


int do_forward(string arg)
{
    string id,sb,reason;
    object ob,jinbi;
    string msg;
    object* oblist = query_temp("oblist");
    object pl=this_player();
	if(!stringp(arg) || sizeof(arg) == 0) return 0;
    if(sscanf(arg,"%s to %s as %s",id,sb,reason) != 3) return 0;
    if(sb == pl->query("id")) return notify_fail("给你自己？\n");
    ob = present(id,pl);
    if(!objectp(ob)) return notify_fail("你身上没有这样东西\n");

//    if(file_size("/data/login/"+sb[0..0]+"/"+sb+".o") == -1) return notify_fail("没有这个玩家\n");
    if(ob->query("no_give") && !wizardp(pl)) return notify_fail("这个东西可不能转交\n");

	if(ob->query("money_id"))
	{
		write("金钱奖励自动转换为活动专用金币。\n");
		jinbi = new("/clone/misc/jinbi.c");
		jinbi->set("value",ob->value()/80*100);
		destruct(ob);
		ob = jinbi;
	}
    ob->move(this_object());
    ob->set_temp("tt_forward/owner",pl->query("id"));
    ob->set_temp("tt_forward/to",sb);
    ob->set_temp("tt_forward/reason",reason);
    oblist += ({ob});
    set_temp("oblist",oblist);
    write("好的，我会把"+ob->query("name")+"转交给"+sb+"的。你可以用xgetback取回来。\n");
    msg = pl->query("name")+"托我把"+ob->query("name")+"转交给你，作为"+reason+"\n";
    send_mail(ob->query_temp("tt_forward/to"),"请来取你的物品",msg,ctime(time()),query("name"),ob->query_temp("tt_forward/to"));
    return 1;    
}

int do_list()
{
    int i;
    object ob;
    object* oblist = query_temp("oblist");
    write("以下是你托我转交还没有被取走的东西。\n");
    for(i=0;i<sizeof(oblist);i++)
    {
        ob = oblist[i];
        if(objectp(ob) && ob->query_temp("tt_forward/owner") == this_player()->query("id"))
        {
            write(sprintf("%d",i+1)+":"+ob->query("name")+"("+ob->query("id")+")给"+ob->query_temp("tt_forward/to")+"作为"+ob->query_temp("tt_forward/reason")+"\n");
        }
    }
    return 1;
}

int do_getback(string arg)
{
    int i,j=0;
    object ob;
    object* oblist = query_temp("oblist");

    int seq = -1;
	if(!stringp(arg) || sizeof(arg) == 0) return 0;
    if(sscanf(arg,"%d",seq) != 1) return 0;
    if(seq < 1) return 0;    
    for(i=0;i<sizeof(oblist);i++)
    {
        ob = oblist[i];
        if(objectp(ob) && ob->query_temp("tt_forward/owner") == this_player()->query("id"))
        {
            j++;
            if(j == seq)
            {
                write(ob->query("name")+"("+ob->query("id")+")你拿回去吧。\n");
                if(!ob->move(this_player()))
                {
                    ob->move(environment(this_object()));
                }
                oblist -= ({ob});
                set_temp("oblist",oblist);
                return 1;
            }
        }
    }
    write("没有这个序号的物品。\n");
    return 1;
    
}

int do_accept()
{
    int i;
    object ob;
    string msg;
    object* oblist = query_temp("oblist");
    write("以下是别人托我转交给你的东西。\n");
    for(i=sizeof(oblist)-1;i>=0;i--)
    {
        ob = oblist[i];
        if(objectp(ob) && ob->query_temp("tt_forward/to") == this_player()->query("id"))
        {
            msg = ob->query_temp("tt_forward/owner")+"给"+ob->query_temp("tt_forward/to")+"作为"+ob->query_temp("tt_forward/reason")+"的"+ob->query("name")+"("+ob->query("id")+")"+"被取走了\n";
            CHANNEL_D->do_channel(this_object(), "bd", msg);
            if(!ob->move(this_player()))
            {
                 ob->move(environment(this_object()));
            }
            send_mail(ob->query_temp("tt_forward/owner"),"物品转交成功",msg,ctime(time()),query("name"),ob->query_temp("tt_forward/owner"));
            oblist -= ({ob});
            set_temp("oblist",oblist);
        }
    }
    return 1;
}

void send_mail(string rcvr, string title,string text,string time,string from,string to)
{
	object ob, mbx,body;
    mapping mail;

	mail = ([]);
	mail["title"] = title;
	mail["text"] = text;
	mail["time"] = time;
	mail["to"] = to;
   	mail["from"] = from;

	if (objectp(ob = find_player(rcvr)))
	{
			mbx = ob->query_temp("mbox_ob");
			if( !mbx ) {
				mbx = new(MAILBOX_OB);
				mbx->set_owner(rcvr);
           		mbx->move(ob);
			}
			mbx->receive_mail(mail);
			ob->save();
			if (!ob->query("env/invisibility")||(int)ob->query("env/invisibility")==0)
			{
				message_vision("忽然一个驿站伙计急匆匆地走过来，交给$N一个邮箱，说道：您的信！然后头也不回的走掉了。\n",ob);
			}
			else
			{
                tell_object(ob,HIY"忽然一个驿站伙计急匆匆地走过来，交给你一个邮箱，说道：您的信！然后头也不回的走掉了。\n"NOR);    
			}
		return;
	}

	ob = new(LOGIN_OB);
	ob = FINGER_D->acquire_login_ob(rcvr);
	if( !ob ) {
		return;
	}
	if (objectp(body = LOGIN_D->make_body(ob)))
	if ( body->restore())
	{
                if (body->query("new_mail")>5)
                {
                    return;
                }
		body->add("new_mail",1);
		mbx = new(MAILBOX_OB);
		mbx->set_owner(rcvr);
		mbx->receive_mail(mail);
		body->save();
		destruct(body);
		destruct(ob);
		destruct(mbx);
	}	
}

int do_ad(string arg)
{
	string* ads;
	if(!arg) return 0;
	
	ads = query("ads");
	arg = F_NAME->replace_color(arg);
	ads += ({arg});
	set("ads",ads);
	write("广告添加成功！\n");
	return 1;
}

int do_reset()
{
	delete("ads");
	set("ads",({}));
	write("广告内容清空！\n");
	return 1;
}

int do_test()
{
	int i;
	string* ads = query("ads");
	for(i=0;i<sizeof(ads);i++)
	{
		write(ads[i]+"\n");
	}
	
	return 1;
}

int post_ad()
{
	int i;
	string* ads = query("ads");
	for(i=0;i<sizeof(ads);i++)
	{
		shout(ads[i]+"\n");
	}
	
	call_out("post_ad",300);
}
void unconcious()
{
   fullme();
   return;
}

void die()
{
   fullme();
   return;
}
