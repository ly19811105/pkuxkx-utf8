// wangtiejiang.c
//
// Modified by pretty (09/16/98)
//   -- add "ding" action

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
inherit F_MASTER;

string *weapons = ({
        "axe", "blade", "club", "dagger", "fork", "halberd", "hammer",
        "pestle", "spear", "staff", "sword", "whip",
});

int do_ding(string arg);
int do_compensate();
string checkstr(string arg);
string ask_work();
string ask_compensate();

void create()
{
        set_name("王铁匠", ({ "wang tiejiang", "wang" }));
        set("title", "打铁铺");
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 45);
        set("long",
                "王铁匠是外地人，刚刚在此开了个打铁铺，买卖倒也红火。\n你可以在他这里劳动(ask wang about work)，\n也可以定做(make_weapon)或购买(buy)趁手的兵器。\n");
        set_skill("unarmed", 10);
        set_skill("dodge", 10);
        set_temp("apply/damage", 15);
        set("combat_exp", 1000);
        set("attitude", "friendly");
        set("inquiry", ([
		"补偿":(:ask_compensate:),
        ]));
        set("vendor_goods", ({
                "/d/city/obj/gangdao",
                "/d/city/obj/tiejia",
                "/d/city/obj/changjian",
                "/d/city/obj/duanjian",
                "/clone/weapon/dart",
                "/clone/weapon/changbian",
                "/clone/weapon/bishou",
                "/clone/weapon/tiefu",
                "/clone/weapon/wuyingzhen",
                "/d/xingxiu/npc/obj/tiegun",
                "/d/village/npc/obj/hammer",    
        }));
        setup();
}
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_ding", "make_weapon");
        add_action("do_ding", "ding");
        add_action("do_compensate", "compensate");
}

int do_ding(string arg)
{
        string cat, color, name, id;
        string wield_msg, unwield_msg;
        string desc;
        object me, ob, gold;
        string file, fname;

        me = this_player();
        if ( !arg || sscanf(arg, "%s %s %s %s %s %s %s", cat, color, name, id, wield_msg, unwield_msg, desc) != 7)
                 return notify_fail(HIY"指令格式：make_weapon <种类> <颜色> <中文名> <英文名> <装备时的描述> <解除装备时的描述> <武器的描述>\n"
                 +HIW"装备时的描述和解除装备时的描述必须还有$W$和$M$字样，注意不能设置颜色。\n"
                 +HIW"$M$代表使用者，$W$代表武器，例如“$M$缓缓抽出一把$W$。”\n"
                 +HIW"装备时候的描述可以支持多行，用\\"+HIW"n隔开，但限制总字数在150字符以内。\n"
                 +HIW"武器的描述不能含有$M$或者$W$，只能由文字组成，描述在150字符以内。\n"
                 +HIR"订的兵器可以使用enhance命令(详见help enhance)增强。\n"NOR);

        if ( me->query("balance") < 2000000 )
                return notify_fail("你的存款不够！至少需要200两黄金才可以自定兵器！\n");

        if ( member_array( cat, weapons ) == -1 )
                return notify_fail("这里没有你想要的兵器。\n");

        if ( !LOGIN_D->check_legal_name(name) )
                return notify_fail("这个中文名字不合法，请重新输入。\n");

        if ( !LOGIN_D->check_legal_id(id) )
                return notify_fail("这个英文名字不合法，请重新输入。\n");
        
        if ( !LOGIN_D->check_legal_describe(wield_msg))
                            return notify_fail("装备的描述不合法！可能导致ｂｕｇ！\n");

        if ( !LOGIN_D->check_legal_describe(unwield_msg))
                            return notify_fail("解除装备的描述不合法！可能导致ｂｕｇ！\n");
                    
                    if ( !LOGIN_D->check_legal_describe(desc))
                            return notify_fail("武器的描述不合法！可能导致ｂｕｇ！\n");
 
        if ( strwidth(wield_msg) > 150 )
                            return notify_fail("装备时的描述太长了，限制是150个字符以内！\n");
        
        if ( strwidth(unwield_msg) > 150 )
                            return notify_fail("解除装备时的描述太长了，限制是150个字符以内！\n");
        
        if ( strwidth(desc) > 150 )
                            return notify_fail("武器的描述太长了，限制是150个字符以内！\n");
        
        if ( me->is_busy() )
                return notify_fail("你现在正忙着呢！\n");

        if (strsrch(wield_msg,"$W$")<0||strsrch(unwield_msg,"$W$")<0)
                return notify_fail("装备和解除装备时的描述必须含有$W$（代表兵器）的字样，注意W是大写的！\n");
        
        if (strsrch(wield_msg,"$M$")<0||strsrch(unwield_msg,"$M$")<0)
                return notify_fail("装备和解除装备时的描述必须含有$M$（代表使用者）的字样，注意M是大写的！\n");        
        
        if ( !(file = read_file("/clone/self_weapon/stdweapon/" + cat + ".c")) )
                return notify_fail("读文件出错。\n");

        if (color == "$BLK$") file = replace_string(file, "color", "BLK");
        else
        if (color == "$RED$") file = replace_string(file, "color", "RED");
        else
        if (color == "$GRN$") file = replace_string(file, "color", "GRN");
        else
        if (color == "$YEL$") file = replace_string(file, "color", "YEL");
        else
        if (color == "$BLU$") file = replace_string(file, "color", "BLU");
        else
        if (color == "$MAG$") file = replace_string(file, "color", "MAG");
        else
        if (color == "$CYN$") file = replace_string(file, "color", "CYN");
        else
        if (color == "$WHT$") file = replace_string(file, "color", "WHT");
        else
        if (color == "$HIR$") file = replace_string(file, "color", "HIR");
        else
        if (color == "$HIG$") file = replace_string(file, "color", "HIG");
        else
        if (color == "$HIY$") file = replace_string(file, "color", "HIY");
        else
        if (color == "$HIB$") file = replace_string(file, "color", "HIB");
        else
        if (color == "$HIM$") file = replace_string(file, "color", "HIM");
        else
        if (color == "$HIC$") file = replace_string(file, "color", "HIC");
        else
        if (color == "$HIW$") file = replace_string(file, "color", "HIW");
        else
        if (color == "$NOR$") file = replace_string(file, "color", "NOR");
        else return notify_fail("没有你想要的颜色！\n");
        
        desc=checkstr(desc);
        desc=desc+"\n";
        
        wield_msg=checkstr(wield_msg);
        wield_msg=replace_string(wield_msg,"$M$","$N");
        wield_msg=replace_string(wield_msg,"$W$","$n");
        wield_msg=wield_msg+"\n";
        
        unwield_msg=checkstr(unwield_msg);
        unwield_msg=replace_string(unwield_msg,"$M$","$N");
        unwield_msg=replace_string(unwield_msg,"$W$","$n");
        unwield_msg=unwield_msg+"\n";
        
        

        file = replace_string(file, "名字", name);
        file = replace_string(file, "ＩＤ", id);
        file = replace_string(file, "(dam)", "(30)");
        file = replace_string(file, "$wield_msg$", wield_msg);
        file = replace_string(file, "$unwield_msg$", unwield_msg);
        file = replace_string(file, "$long$", desc);
        file = replace_string(file, "$owner$", me->query("id"));

        seteuid(ROOT_UID);
        fname = PRIVATE_DIR + me->query("id")[0..0] + "/" + me->query("id") + time() + ".c";
        if (!write_file(fname, file))
                return notify_fail("无法写入文件。\n");
        if ( !objectp(ob = new(fname)) || !ob->move(me))
                return notify_fail("无法创建文件。\n");
        message_vision("$N叮叮铛铛的敲了一阵后说道：好了！\n", this_object());
        message_vision("$N交给$n一" + ob->query("unit") + ob->name() + "。\n", this_object(), me);
        me->add("auto_load", ({ base_name(ob) + ".c" }) );
        me->add("balance",-2000000);
        me->save();
        return 1;
}

string checkstr(string arg)
{
        arg=replace_string(arg,"/","");
        arg=replace_string(arg,"'","");
        arg=replace_string(arg,"/*","");
        arg=replace_string(arg,"*","");
        arg=replace_string(arg,"~","");
        arg=replace_string(arg,"!","");
        arg=replace_string(arg,"|","");
        arg=replace_string(arg,"||","");
        arg=replace_string(arg,"&","");
        arg=replace_string(arg,"^","");
        arg=replace_string(arg,"%","");
        arg=replace_string(arg,";","");
        arg=replace_string(arg,")","");
        arg=replace_string(arg,"}","");
        arg=replace_string(arg,"]","");
        return arg;
}


string ask_work()
{
        object me = this_player();
        string respect = RANK_D->query_respect(me);
        int reward;
        object ob;

        if(query("startroom") != file_name(environment(this_object())))
                return "我现在身有要事，还望"+respect+"见谅。";
        if(me->is_busy())
                return respect+"还是先忙完了吧。";
        if(me->query_temp("apply/strength") < 30)
                return "好吧，"+respect+"就在此地劳动(work)吧。";
        if(me->query("gift/20070501"))
                return respect+"辛苦了，不用劳动了。";
        if(me->query("20070501/str"))
                return respect+"不妨去别处看看有没有需要帮忙劳动的。";
        command("thank " + query("id"));
        command("say 多谢"+respect+"，请下去休息休息吧。");
        write(HIW"你被奖励了：\n");
        reward = me->query_skill("force") + me->query_skill("parry");
        reward *= 5;
        write("\t"+chinese_number(reward)+"点经验；\n");
        me->add("combat_exp", reward);
        write("\t"+chinese_number(reward/5)+"点潜能。\n"NOR);
        me->add("potential", reward/5);

        me->set("20070501/str", 1);
        if(sizeof(me->query("20070501")) >= 4)
                me->set("gift/20070501", 1);
        if(me->query("gift/20070501"))
        {
                ob = new("/d/wizard/obj/xiandou2");
                ob->set("no_store", 1);
                ob->set("no_sell", 1);
                ob->set("no_pawn", 1);
                message_vision(HIM"$N交给$n一颗仙豆。\n"NOR, this_object(), me);
                ob->move(me);
                me->delete("20070501");
                command("chat* hoho "+me->query("id"));
                return "这是你用辛勤劳动换来的五一礼物，祝你五一快乐！劳动光荣！";
        }
        else
                return respect+"不妨去别处看看有没有需要帮忙劳动的。";
}

//补偿升级服务器丢失的自制武器,by all @2013/04/10
int do_compensate()
{
        object me = this_player();
	string *autoloads,filename;
        int i, dam, jing_li;
//        int total_jingli, auto_gold, auto_num=0;
        object obj;
	if(!me->query_temp("autoload_compensate"))
		return notify_fail("先找人问问吧。\n");
        if( me->query("reborn/all") && me->query("ludingshan") )
                dam = 180;
        else if(  me->query("ludingshan") )
                dam = 150;
        else dam = 120;
        if (dam > ((int)me->query_skill("force")/3+1))
        	dam = (int)me->query_skill("force")/3+1;
        if (dam < 30) dam = 30;
	jing_li=(30+dam)*(dam-30)/4;
	if ( arrayp(autoloads = me->query("auto_load")) )
	{
		for (i = sizeof(autoloads)-1; i >= 0; i--)
		{
			filename = autoloads[i];
			if(autoloads[i][0..2]=="/u/"&&!wizardp(me)) continue;
			if ( objectp(obj = new(autoloads[i])) )
				write("\n" + obj->name() + "  没有问题.\n\n");
			else
			{
				autoloads -= ({ filename });
				me->set("auto_load", autoloads);
//				auto_num+=1;
//				me->add_temp("autoload_num",1);
				me->add("max_jingli",jing_li);
				me->add("balance",2000000);
				if(!me->query("marks/autoload_compensate"))
					me->set("marks/autoload_compensate",time());
				me->delete_temp("autoload_compensate",1);
				tell_object(me,"你修理了1件自制兵器物品\n"+"共补偿"+chinese_number(jing_li)+"点最大精力,\n"
					"共补偿200两黄金。\n");
				log_file("user/compensate_weapon",sprintf("%s于%s修理1件自制兵器，获得最大精力补偿%d点，金钱补偿200两gold。\n",
					me->query("id"),ctime(time()),jing_li));
			return 1;
			}
		}
	} 

/*	total_jingli=auto_num*jing_li;
	auto_gold=200*auto_num;
       	tell_object(me,"你总共修理了"+chinese_number(auto_num)+"件自制兵器物品\n"+"共补偿"+chinese_number(total_jingli)+"点最大精力,\n"
			"共补偿"+chinese_number(auto_gold)+"两黄金。\n");
	log_file("user/compensate_weapon",sprintf("%s于%s修理%d件自制兵器，获得最大精力补偿%d点，金钱补偿%d两gold。\n",
		me->query("id"),ctime(time()),auto_num,total_jingli,auto_gold));
        me->set("marks/autoload_compensate",time());
        me->delete_temp("autoload_compensate",1);
*/        
	if(me->query("marks/autoload_compensate"))
		tell_object(me,"你的自制兵器都已经补偿过了。\n");
	else tell_object(me,"你的自制兵器没有问题。\n");
	me->delete_temp("autoload_compensate",1);
	return 1;
}

string ask_compensate()
{
        object me = this_player();
        string respect = RANK_D->query_respect(me);
        if(query("startroom") != file_name(environment(this_object())))
                return "我现在身有要事，还望"+respect+"见谅。";
        if(me->is_busy())
                return respect+"还是先忙完了吧。";
        if(me->query("marks/autoload_compensate") && time()-me->query("marks/autoload_compensate")>3*86400)
                return respect+"已经补偿过了吧。";                
        me->set_temp("autoload_compensate",1);
        write(HIW"由于服务器升级引起的自制兵器丢失，补偿相应的精力和金钱，需要重新定制，
        		自制兵器需要在线一次性enhance到最大值，切记！\n");
        write(HIW"一次补偿1把自制兵器，请务必在3天之内补偿完毕！\n");
	return respect+"找个合适的时间补偿(compensate)吧。";
}
