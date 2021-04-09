// File         : silver.c 门派的例银系统
// Created By   : iszt@pkuxkx, 2007-01-14
// 在掌管发放例银的NPC中继承这个文件，inquiry中加上 (: ask_silver :) 即可使用
// 上次领取例银之后mud_age增长一个月之后按月领取，满足三个条件之一即可
// 门忠增加奖励的例银最多，武功次之，经验最少
// 经验越高，每月例银越多，数量与经验的立方根成正比
// 玩家身上相关记录在query("silver")
// 最好进行下面若干参数的定义，以便体现门派特色：
// set("sivler_name") 例银的名称，默认为“例银”
// set("silver_factor") 例银的数量因子，默认为1
// set("silver_family_skill") 门派武功，提升此武功时可以领取例银，默认为parry
// set("msg_silver_firsttime") 第一次打听例银的时候说的话
// set("msg_silver_record") 作记录时的描述\n
// set("msg_silver_check") 检查记录时的描述\n
// set("msg_silver_mudage") 时间未到不能领取时说的话
// set("msg_silver_paid") 领取成功时说的话
// set("msg_silver_score") 由于提升师门忠诚而领取例银时的描述\n
// set("msg_silver_skill") 由于提升师门武功而领取例银时的描述\n
// set("msg_silver_exp") 由于提升经验而领取例银时的描述\n
// set("msg_silver_none") 领取例银条件均不满足时说的话
//加入门派盈余加成，Zine
#include <ansi.h>

object get_user_family(object user)
{
    string family = user->query("family/family_name");
    string surplus;
    object ob;
    switch(family)
	{
		case "少林派": surplus = "/d/family-private/shaolin/shimen"; break;
		case "大轮寺": surplus = "/d/family-private/dalunsi/shimen"; break;
		case "武当派": surplus = "/d/family-private/wudang/shimen"; break;
		case "丐帮": surplus = "/d/family-private/gaibang/shimen"; break;
		case "桃花岛": surplus = "/d/family-private/taohua/shimen"; break;
		case "星宿派": surplus = "/d/family-private/xingxiu/shimen"; break;	
		case "峨嵋派": surplus = "/d/family-private/emei/shimen"; break;
		case "白驼山": surplus = "/d/family-private/baituo/shimen"; break;
		case "华山派": surplus = "/d/family-private/huashan/shimen"; break;
		case "明教": surplus = "/d/family-private/mingjiao/shimen"; break;
		case "日月神教": surplus = "/d/family-private/riyue/shimen"; break;
		case "古墓派": surplus = "/d/family-private/gumu/shimen"; break;
		case "灵鹫宫": surplus = "/d/family-private/lingjiu/shimen"; break;
		case "全真派": surplus = "/d/family-private/quanzhen/shimen"; break;
		case "天龙寺": surplus = "/d/family-private/tianlong/shimen"; break;
		case "姑苏慕容": surplus = "/d/family-private/murong/shimen"; break;
		case "天地会": surplus = "/d/family-private/tiandi/shimen"; break;
		case "神龙教": surplus = "/d/family-private/shenlong/shimen"; break;
		case "雪山派": surplus = "/d/family-private/xueshan/shimen"; break;
        case "朝廷": surplus = "/d/family-private/chaoting/shimen"; break;
		case "大理段家": surplus = "/d/family-private/shaolin/shimen"; break;
	    case "红花会": surplus = "/d/family-private/shaolin/shimen"; break;
	}
    if (surplus&&load_object(surplus))
    {
        ob=load_object(surplus);
    }
    return ob;
}

int get_surplus(object ob)
{
    if (!ob)
    {
        return 0;
    }
    ob->restore();
    if (ob->query("family_surplus")>20000000)//盈余大于2000金，门派例银额外增加1成，到500金为止。
    {
        ob->set("extra_salary",1);
        ob->save();
        return 1;
    }
    else if (ob->query("family_surplus")<5000000)
    {
        ob->delete("extra_salary");
        ob->save();
        return 0;
    }
    else if (ob->query("extra_salary"))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

float party_percent(string family)
{
        object* ob = users();
        object me = this_player();
        int i;
        int family_member_number = 0;

        for(i=sizeof(users())-1; i>=0; i--)
                if(ob[i]->query("family/family_name") == family)
                        family_member_number ++;
        return family_member_number * 100 / (float)sizeof(users());
}

void do_record(int mudage, int exp, int score, int skill)
{
        object me = this_player();
        object ob = this_object();
        string msg;
        me->set("silver/last_mud_age", mudage);
        me->set("silver/last_exp", exp);
        me->set("silver/last_score", score);
        if(skill > me->query("silver/last_family_skill"))
                me->set("silver/last_family_skill", skill);

        msg = ob->query("msg_silver_record");
        if(!msg)
                msg = "$N取出一本小册子，在上边记下了些什么。\n";
        message_vision(YEL + msg + NOR, ob);
}

void do_givesilver(int salary, int month, string silvername)
{
        object me = this_player();
        object ob = this_object();
        object party;
        int pp; //party_percent
        string msg;

        if(!ob->query("silver_factor"))
                ob->set("silver_factor", 1);
        salary *= ob->query("silver_factor");
        pp=(200 - 14 * party_percent(me->query("family/family_name")));
        if (pp<=1) pp=1;
        if (pp>=200) pp=200;
        salary /= 100;
        salary *= pp ;
        if(salary < 5000)
                salary = 5000;
        party=get_user_family(me); //找到门派金库
        if (get_surplus(party))//门派有盈余，加发一成
        {
            salary=salary+salary/10;
            tell_object(me,HIR+"因为你的门派获得盈余，例银加发一成。\n"+NOR);
            party->add("family_surplus",-salary/10);
            party->save();//门派金库减少加发金额。
        }
        msg = "$N交给$n" + chinese_number(month) + "个月的" + silvername;
        msg += MONEY_D->money_str(salary) + "。\n";
        message_vision(WHT + msg + NOR, ob, me);

        MONEY_D->pay_player(me, salary);
        me->add("silver/got", salary);
        CHANNEL_D->do_channel(this_object(), "sys",
                        sprintf("%s领%s%s。", me->name(), silvername, MONEY_D->money_str(salary)));
        if(salary > 100000)
        {
                CHANNEL_D->do_channel(this_object(), "jh",
                        sprintf("%s领%s%s。", me->name(), silvername, MONEY_D->money_str(salary)));
                CHANNEL_D->do_channel(this_object(), "jh", "shuang " + me->query("id"), 1);
        }
        log_file("static/silver", sprintf("%s(%s)\t领取%s个月的%s\t%d\n",
                me->name(), me->query("id"), chinese_number(month), silvername, salary));
}

string ask_silver()
{
        object me = this_player();
        object ob = this_object();
        string msg;

        int mudage = me->query("mud_age");
        int exp = me->query("combat_exp");
        int score = me->query("score");
        string familyskill = ob->query("silver_family_skill");
        int skill;
        int salary;
        int month;

        string silvername = ob->query("silver_name");

        if(!familyskill)
                familyskill = "parry";
        skill = me->query_skill(familyskill, 1);

        if(!silvername)
                silvername = "例银";
        if (score < 0) score = 0;
        if(me->query("family/family_name") != ob->query("family/family_name"))
                return 0;

        //不允许不停的问
        if(mudage - me->query_temp("last_ask_silver") < 60)
                return "问来问去，你烦不烦啊？";
        me->set_temp("last_ask_silver", mudage);

        //第一次问，没有标记的情况
        if(!me->query("silver"))
        {
                me->set("silver/got", 0);
                do_record(mudage, exp, score, skill);
                msg = ob->query("msg_silver_firsttime");
                if(!msg)
                        msg = "好，记下了。回头就来领你的" + silvername + "吧。";
                return msg;
        }

        //间隔时间
        salary = mudage - me->query("silver/last_mud_age");
        month = salary / 7200;
        if(month < 1)
        {
                msg = ob->query("msg_silver_check");
                if(!msg)
                        msg = "$N取出一本小册子翻了翻。\n";
                message_vision(CYN + msg + NOR, ob);
                msg = ob->query("msg_silver_mudage");
                if(!msg)
                        msg = "急什么？一月不到，还不是发" + silvername + "的时候。";
                return msg;
        }

        //score有提升
        if(score - me->query("silver/last_score") > salary / 100) //每小时36 score
        {
                msg = ob->query("msg_silver_score");
                if(!msg)
                        msg = "$N轻轻拍了拍$n的肩头道：「不错，最近你为本门出力甚多。」\n";
                message_vision(CYN + msg + NOR, ob, me);

                do_record(mudage, exp, score, skill);

                salary = 1000 * pow((float)me->query("silver/last_exp")*1.0, 1.0/3);
                //50k exp每月350 silver，1M exp每月10 gold，100M exp每月不到50 gold
                salary *= month;

                do_givesilver(salary, month, silvername);

                msg = ob->query("msg_silver_paid");
                if(!msg)
                        msg = "拿去吧，继续为本门努力，师父绝不会亏待你的。";
                return msg;
        }

        //skill有提升
        if(skill - me->query("silver/last_family_skill") > salary /1800) //每小时2 level
        {
                msg = ob->query("msg_silver_skill");
                if(!msg)
                {
                        msg = "$N轻轻拍了拍$n的肩头道：「不错，你的";
                        msg += CHINESE_D->chinese(familyskill);
                        msg += "又精进了。」\n";
                }
                message_vision(CYN + msg + NOR, ob, me);

                do_record(mudage, exp, score, skill);

                salary = 600 * pow((float)me->query("silver/last_exp")*1.0, 1.0/3);
                //50k exp每月2 gold，1M exp每月6 gold，100M exp每月不到30 gold
                salary *= month;

                do_givesilver(salary, month, silvername);

                msg = ob->query("msg_silver_paid");
                if(!msg)
                        msg = "拿去吧，继续为本门努力，师父绝不会亏待你的。";
                return msg;
        }

        //exp有提升
        if(exp - me->query("silver/last_exp") > salary * 3 / 2) //每小时5.4k exp
        {
                msg = ob->query("msg_silver_exp");
                if(!msg)
                        msg = "$N轻轻拍了拍$n的肩头道：「不错，你的武功又精进了。」\n";
                message_vision(CYN + msg + NOR, ob, me);

                do_record(mudage, exp, score, skill);

                salary = 200 * pow((float)me->query("silver/last_exp")*1.0, 1.0/3);
                //50k exp每月70 silver，1M exp每月2 gold，100M exp每月不到10 gold
                salary *= month;

                do_givesilver(salary, month, silvername);

                msg = ob->query("msg_silver_paid");
                if(!msg)
                        msg = "拿去吧，继续为本门努力，师父绝不会亏待你的。";
                return msg;
        }

        do_record(mudage, exp, score, skill);
        msg = ob->query("msg_silver_none");
        if(!msg)
                msg = "你自问这" + chinese_number(month) + "个月做什么去了？罢了，你去吧。";
        return msg;
}

