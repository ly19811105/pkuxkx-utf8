//D:\xkx\d\liuxiu-shanzhuang\npc\wushi.c武师
// labaz 2012/10/23

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "../newbie_village.h"

string *skill_level_desc = ({
        BLU "不堪一击" NOR,BLU "毫不足虑" NOR,BLU "不足挂齿" NOR,BLU "初学乍练" NOR,BLU "勉勉强强" NOR,
        HIB "初窥门径" NOR,HIB "初出茅庐" NOR,HIB "略知一二" NOR,HIB "普普通通" NOR,HIB "平平淡淡" NOR,
        CYN "平淡无奇" NOR,CYN "粗通皮毛" NOR,CYN "半生不熟" NOR,CYN "马马虎虎" NOR,CYN "略有小成" NOR,
        HIC "已有小成" NOR,HIC "鹤立鸡群" NOR,HIC "驾轻就熟" NOR,HIC "青出于蓝" NOR,HIC "融会贯通" NOR,
        GRN "心领神会" NOR,GRN "炉火纯青" NOR,GRN "了然于胸" NOR,GRN "略有大成" NOR,GRN "已有大成" NOR,
        YEL "豁然贯通" NOR,YEL "出类拔萃" NOR,YEL "无可匹敌" NOR,YEL "技冠群雄" NOR,YEL "神乎其技" NOR,
        HIY "出神入化" NOR,HIY "非同凡响" NOR,HIY "傲视群雄" NOR,HIY "登峰造极" NOR,HIY "无与伦比" NOR,
        RED "所向披靡" NOR,RED "一代宗师" NOR,RED "精深奥妙" NOR,RED "神功盖世" NOR,RED "举世无双" NOR,
        WHT "惊世骇俗" NOR,WHT "撼天动地" NOR,WHT "震古铄今" NOR,WHT "超凡入圣" NOR,WHT "威镇寰宇" NOR,
        HIW "空前绝后" NOR,HIW "天人合一" NOR,MAG "深藏不露" NOR,HIM "深不可测" NOR,HIR "返璞归真" NOR
});
string *force_skill =({
        HIG"第一重楼"NOR,HIY"第一重楼"NOR,HIR"第一重楼"NOR,
        HIG"第二重楼"NOR,HIY"第二重楼"NOR,HIR"第二重楼"NOR,
        HIY"第三重楼"NOR,HIG"第三重楼"NOR,HIR"第三重楼"NOR,
        HIY"第四重楼"NOR,HIG"第四重楼"NOR,HIR"第四重楼"NOR,
        HIY"第五重楼"NOR,HIG"第五重楼"NOR,HIR"第五重楼"NOR,
        HIY"第六重楼"NOR,HIG"第六重楼"NOR,HIR"第六重楼"NOR,
        HIY"第七重楼"NOR,HIG"第七重楼"NOR,HIR"第七重楼"NOR,MAG"第七重楼"NOR,
        HIY"第八重楼"NOR,HIG"第八重楼"NOR,HIR"第八重楼"NOR,MAG"第八重楼"NOR,
        HIY"第九重楼"NOR,HIG"第九重楼"NOR,HIR"第九重楼"NOR,MAG"第九重楼"NOR,
        HIY"第十重楼"NOR,HIG"第十重楼"NOR,HIR"第十重楼"NOR,MAG"第十重楼"NOR,
        HIY"十一重楼"NOR,HIG"十一重楼"NOR,HIR"十一重楼"NOR,MAG"十一重楼"NOR,
        HIY"十二重楼"NOR,HIG"十二重楼"NOR,HIR"十二重楼"NOR,MAG"十二重楼"NOR,HIW"十二重楼"NOR,
            });
string *knowledge_level_desc = ({
        BLU "新学乍用" NOR,BLU "初窥门径" NOR,HIB "略知一二" NOR,HIB "半生不熟" NOR,
        CYN "马马虎虎" NOR,CYN "已有小成" NOR,HIC "融会贯通" NOR,HIC "心领神会" NOR,
        GRN "了然於胸" NOR,GRN "已有大成" NOR,YEL "非同凡响" NOR,YEL "举世无双" NOR,
        HIY "震古铄今" NOR,RED "无与伦比" NOR,WHT "超凡入圣" NOR,HIW "深不可测" NOR,
});

string *reject_msg = ({
	"说道：您太客气了，这怎么敢当？\n",
	"像是受宠若惊一样，说道：请教？这怎么敢当？\n",
	"笑着说道：您见笑了，我这点雕虫小技怎够资格「指点」您什么？\n",
});

string skill_level(string, int,string);

int do_bai(string);
int do_halt();
int do_give(string);
int do_cha(string);
int do_learn(string);

void create()
{
	set_name(HIC"武师"NOR, ({ "wu shi", "wushi" }));
	set("title", "柳秀山庄");
	set("nickname", "太乙教头");
	set("shen_type", 1);

	set("gender", "男性");
	set("age", 35);
	set("long",
		"他是柳秀山庄的武师。\n");

	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 2000);
	set("max_jingli", 2000);
	set("max_jing", 2000);
	set("max_neili", 500);
	set("combat_exp", 4000);
	
	set_skill("dodge", 30);
	set_skill("force", 30);
	set_skill("taiyi-shengong", 30);
	set_skill("taiyi-you", 30);
	set_skill("taiyi-zhang", 30);
	set_skill("parry", 30);
	set_skill("sword", 20);
	set_skill("strike", 30);
	set_skill("taiyi-jian", 20);

	map_skill("force", "taiyi-shengong");
	map_skill("dodge", "taiyi-you");
	map_skill("strike", "taiyi-zhang");
	map_skill("parry", "taiyi-jian");
	map_skill("sword", "taiyi-jian");

	prepare_skill("strike", "taiyi-zhang");

    // set("attitude", "friendly");
    
	setup();
	
	carry_object(__DIR__"obj/jian")->wield();
}

void init()
{
	add_action("do_halt","halt");
	add_action("do_bai","bai");
	add_action("do_bai","apprentice");
	add_action("do_give","give");
	add_action("do_learn","xue");
	add_action("do_learn","learn");
	add_action("do_cha","cha");
	add_action("do_cha","skills");
}

int do_halt()
{
	object who;
	who=this_player();
    if (who->is_fighting())
    {
        who->set_temp("newbie/halt",1);
    }
	return 0;
}

int accept_fight(object who)
{
	object ob;
	ob=this_object();
	
	if (ob->is_fighting()) return 0;
	call_out("checking",1,ob,who);
	return 1;
}

int checking(object ob,object who)
{
    int eff_qi;
	if (!who) return 1;
	if ((!ob->is_fighting()) && (present(who, environment())))
	{
		if (0==who->query_temp("newbie/halt"))
		{
			who->set_temp("newbie/fight",1);
            if (1==check_questindex(who,"尚武堂找武师比武，fight wushi"))
            {
                eff_qi=0.8*who->query("max_qi");
                who->set("eff_qi",eff_qi);
            }
			if (living(who))
			{
				set_nextquest(who,"尚武堂找武师比武，fight wushi","这场比试消耗了你不少的体力，回厢房去休息(sleep)一下吧。", 20, 100);
                if (1==check_questindex(who,"尚武堂找武师再次比武"))
                {
                    tell_object(who, GRN"经过这场比试，你对基本剑法有了更深的领悟！\n" NOR);
                    tell_object(who, HIC "你的「" + to_chinese("sword") + "」进步了！\n" NOR);
                    // SKILL_D("sword")->skill_improved(who);
                    who->set_skill("sword",6);
                    set_nextquest(who,"尚武堂找武师再次比武","你颇有慧根，竟悟出了剑法的剑意。\n趁热打铁去练习一级太乙剑法，一定能有收获的。\n可通过lian sword <次数>，来提高你当前enable的剑法\n", 50, 250);
                    message_vision(GRN"武师对$N说道：”能教的我都传授给你了，其他的就靠你自己领悟和努力了！“\n"NOR, who);
                }
			}
		}
        who->set_temp("newbie/halt",0);
        return 1;
	}
	remove_call_out("checking");
	call_out("checking",1,ob,who);
}

int do_bai(string arg)
{
	object ob, old_app, me, wuqi;
	mapping family, skills;
	int i;
	string *skname;

	me=this_player();
	ob=this_object();

	if( !arg ) 
    {
		tell_object(me,"指令格式：apprentice | bai [cancel]|<对象>\n");
        return 1;
    }

	if( ("wushi"!=arg)&&("wu shi"!=arg) )
		return 0;

	if (me->is_busy())
		{
            tell_object(me,"你现在正忙着呢。\n");
            return 1;
        }

	if( !living(ob) ) 
        {
            tell_object(me,"你必须先把" + ob->name() + "弄醒。\n");
            return 1;
        }
        
	if( arg=="cancel" ) {
		old_app = me->query_temp("pending/apprentice");
		if( !objectp(old_app) )
		{
            tell_object(me,"你现在并没有拜任何人为师的意思。\n");
            return 1;
        }
		write("你改变主意不想拜" + old_app->name() + "为师了。\n");
		tell_object(old_app, me->name() + "改变主意不想拜你为师了。\n");
		me->delete_temp("pending/apprentice");
		return 1;
	}

		
	if (0==check_questindex(me,"找武师拜师学艺，bai wushi"))
	{
		tell_object(me, "武师现在并没有收任何人为徒的意思。\n",1);
		return 1;
	}
    if (1==check_questindex(me,"找武师拜师学艺，bai wushi"))
	{
		tell_object(me, "武师说道：”好吧，看你是个习武的料，便教你两手，不过先得帮我做点事。“
武师趴在你耳边轻轻说道：“我需要一壶烧刀子和一把钢剑，你去酒铺、铁匠铺给我买回来。”\n\n");
		me->set_temp("newbie/needmoney",1);
		return 1;
	}
	if (2==check_questindex(me,"找武师拜师学艺，bai wushi") )
	{
		if (0==check_questindex(me,"bai wushi,查看武师技能，cha wushi"))
		{
			message_vision(GRN"$N恭恭敬敬地向$n磕头请安，叫道：「师父！」\n武师忙道：“先别急着叫师傅，东西给我买来了没。”\n\n"NOR, me, ob);
		}
		else
		{
			message_vision(GRN"$N恭恭敬敬地向$n磕头请安，叫道：「师父！」\n"NOR, me, ob);
            if ( 1==check_questindex(me,"bai wushi,查看武师技能，cha wushi") && 0==me->query("newbie_village/master") )
            {
                message_vision(GRN"武师笑道：“为师退隐江湖已久，早已不收徒弟。只传你武功，今后莫要对外人提起及我。\n跟我学艺这段时间，你就用这把太乙剑吧。”\n"NOR,me);
                me->set("newbie_village/master",1);
                wuqi=new(__DOMAIN_DIR__"weapon/taiyijian");
                if (wuqi->move(me)) message_vision(GRN"武师从兵器架上拿给了$N一把太乙剑。(wield jian 可以装备这把剑)\n"NOR,me);
                me->save();
            }
		}
		return 1;
	}
	return 0;
}

void dest_ob()
{
	object ob;
	if(objectp(ob=present("jian"))) destruct(ob);
	if(objectp(ob=present("shaodaozi"))) destruct(ob);
	if(objectp(ob=present("shi he"))) destruct(ob);
}

int accept_object(object who, object ob)
{
	object *inv;
	int i;
	
	call_out("dest_ob",2);

	// if (ob->query("id")=="hulu" && ob->qurery("name")=="[33m"+"葫芦")
	if (1==check_questindex(who,"帮武师去铁匠铺买一把钢剑，去酒铺买一壶烧刀子酒，回来交给武师"))
	{
		if (ob->query("id")=="jian") who->set_temp("newbie/jian",1);
		if (ob->query("id")=="shaodaozi") who->set_temp("newbie/shaodaozi",1);
		if (2 == who->query_temp("newbie/jian")+who->query_temp("newbie/shaodaozi"))
		{
			message_vision(GRN"$N向武师做了个揖，道：“还望您能指点在下几招！”\n武师嘿嘿笑道：“痴老汉这酒还是那么够劲，直勾老子肚子里的馋虫，你去买根鸡腿给我下下酒。\n记住我要吃热得，去杂货铺买个食盒，把鸡腿放进去带回来。(pu jitui in shi he)”\n\n"NOR, who);
			set_nextquest(who,"帮武师去铁匠铺买一把钢剑，去酒铺买一壶烧刀子酒，回来交给武师","没办法，继续跑腿去买东西吧，要有诚意。(put jitui in shi he)", 20, 100);
			return 1;
		}
		else if (1==who->query_temp("newbie/jian")+who->query_temp("newbie/shaodaozi"))
		{
			return 1;
		}
	}
	if (1==check_questindex(who,"再去酒铺买个鸡腿，去杂货铺买个食盒，把鸡腿放到食盒里交给武师"))
	{
		if (ob->query("id")=="shi he")
		{
			inv = all_inventory(ob);
			for(i=0; i<sizeof(inv); i++) 
			{
				if (inv[i]->query("id")=="jitui")
				{
					message_vision(GRN"武师对$N说道：“看你这么有诚意，我就来教你几招。”\n\n"NOR, who);
					set_nextquest(who,"再去酒铺买个鸡腿，去杂货铺买个食盒，把鸡腿放到食盒里交给武师","还等什么，赶紧拜师(bai wushi)吧，再看看师傅都会些什么功夫(cha wushi)。", 20, 100);
					return 1;
				}
			}
			message_vision(GRN"武师对$N皱起了眉头，问道：“你怎么没把鸡腿装到食盒里呢？空盒子你自己留着吧。”\n"NOR,who);
			return 0;
		}
		if (ob->query("id")=="jitui")
		{
			message_vision(GRN"武师对$N皱起了眉头，说道：“把它装到食盒里再给我。”\n"NOR,who);
			return 0;
		}
	}
	return 0;
}

int do_cha(string arg)
{
        object ob,me;
        mapping skl, lrn, map,aa;
        string *sname, *mapped,skill,msg,type;
        int i,j;
        string usage, *sk;
        int opt_spec,opt_base;

        me=this_player();

        if(!arg)
                ob = me;
        else{
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
        if (wizardp(me))  {
        if( !ob ) ob = LOGIN_D->find_body(arg);
        }
                if (!ob) 
                {
                    tell_object(me,"周围有这个人吗？只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");
                    return 1;
                }
        }

        if( ob!=me && !wizardp(me) && !(me->query("newbie_village/master") && "wu shi" == ob->query("id")) )
        {
            tell_object(me,"周围有这个人吗？只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");
            return 1;
        }

        call_out("set_nextquest",2,me,"bai wushi,查看武师技能，cha wushi","你问清楚了武师学了哪些技能，赶紧向他学点功夫吧！\n要求学习武师身上所有基本功夫到5级，所有高级功夫到5级。\n请输入xue [师父id] for [技能id] [学习的次数]\n学习消耗精神，在现阶段只能通过睡觉来恢复。\n内功是一切武学之根基！建议先学基本内功和特殊内功！", 20, 100);
                
        skl = ob->query_skills();
        if(!sizeof(skl)) {
                write( (ob==me ? "你" : ob->name()) + "目前并没有学会任何技能。\n");
                return 1;
        }
        write( "[44;1m[1;33m"+(ob==me ? "你" : ob->name()) +"[44;1m[1;33m目前所学过的技能：（共"+chinese_number(sizeof(skl))+"项技能）[37;0m\n\n");
			sname  = sort_array( keys(skl), (: strcmp :) );

        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        if(userp(ob)) lrn = ob->query_learned();
        else {
                if(!mapp(ob->query("learned")))
                ob->set("learned",([]));
                lrn=ob->query("learned");
        }
        if( !mapp(lrn) ) lrn = ([]);

 sk = keys(skl);
	for(i=0; i<sizeof(skl); i++) {
	if( skl[sk[i]]<=0 )
{
	map_delete(skl, sk[i]);
}
}
        for(i=0; i<sizeof(skl); i++)
		{
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
			continue;
       if(SKILL_D(sname[i])->type()=="profession") j=j+1;
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项职业技能");}
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
				continue;
        	if(SKILL_D(sname[i])->type()=="profession"){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n",
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}
        	
        for(i=0; i<sizeof(skl); i++)
		{
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
			continue;
       if(SKILL_D(sname[i])->type()=="knowledge") j=j+1;
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项基本知识");}
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
				continue;
        	if(SKILL_D(sname[i])->type()=="knowledge"){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n",
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}

	j=0;
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
			continue;
                if(SKILL_D(sname[i])->type() != "knowledge" && SKILL_D(sname[i])->type() != "profession" && (sname[i] == "array" || sname[i] == "axe" || sname[i] == "blade" || sname[i] == "claw"
|| sname[i] == "club" || sname[i] == "cuff" || sname[i] == "dagger" || sname[i] == "dodge" || sname[i] == "finger" || sname[i] == "force" || sname[i] == "fork"
|| sname[i] == "halberd" || sname[i] == "hammer" || sname[i] == "hand" || sname[i] == "hook" || sname[i] == "iron-cloth" || sname[i] == "leg" || sname[i] == "magic" 
|| sname[i] == "move" || sname[i] == "parry" || sname[i] == "pestle" || sname[i] == "spear" || sname[i] == "spells" || sname[i] == "staff" || sname[i] == "stick" 
|| sname[i] == "strike" || sname[i] == "sword" || sname[i] == "throwing" || sname[i] == "unarmed" || sname[i] == "whip"|| sname[i] == "checking" || sname[i] == "digging" 
|| sname[i] == "swimming"))
		{
        	j=j+1;
                }
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项基本功夫");}
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
				continue;
                if(SKILL_D(sname[i])->type() != "knowledge" && SKILL_D(sname[i])->type() != "profession" &&  (sname[i] == "array" || sname[i] == "axe" || sname[i] == "blade" || sname[i] == "claw"
|| sname[i] == "club" || sname[i] == "cuff" || sname[i] == "dagger" || sname[i] == "dodge" || sname[i] == "finger" || sname[i] == "force" || sname[i] == "fork"
|| sname[i] == "halberd" || sname[i] == "hammer" || sname[i] == "hand" || sname[i] == "hook" || sname[i] == "iron-cloth" || sname[i] == "leg" || sname[i] == "magic" 
|| sname[i] == "move" || sname[i] == "parry" || sname[i] == "pestle" || sname[i] == "spear" || sname[i] == "spells" || sname[i] == "staff" || sname[i] == "stick" 
|| sname[i] == "strike" || sname[i] == "sword" || sname[i] == "throwing" || sname[i] == "unarmed" || sname[i] == "whip"|| sname[i] == "checking" || sname[i] == "digging" 
|| sname[i] == "swimming"))
		{
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n",
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}

	j=0;
        for(i=0; i<sizeof(skl); i++) {
       	if(SKILL_D(sname[i])->type() != "knowledge" && SKILL_D(sname[i])->type() != "profession" &&  (sname[i] != "array" && sname[i] != "axe" && sname[i] != "blade" && sname[i] != "claw"
&& sname[i] != "club" && sname[i] != "cuff" && sname[i] != "dagger" && sname[i] != "dodge" && sname[i] != "finger" && sname[i] != "force" && sname[i] != "fork"
&& sname[i] != "halberd" && sname[i] != "hammer" && sname[i] != "hand" && sname[i] != "hook" && sname[i] != "iron-cloth" && sname[i] != "leg" && sname[i] != "magic" 
&& sname[i] != "move" && sname[i] != "parry" && sname[i] != "pestle" && sname[i] != "spear" && sname[i] != "spells" && sname[i] != "staff" && sname[i] != "stick" 
&& sname[i] != "strike" && sname[i] != "sword" && sname[i] != "throwing" && sname[i] != "unarmed" && sname[i] != "whip"&& sname[i] != "checking" && sname[i] != "digging" 
&& sname[i] != "swimming")){
        	j=j+1;
                }
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项特殊功夫");}
        for(i=0; i<sizeof(skl); i++) {
				if(SKILL_D(sname[i])->type() != "knowledge" && SKILL_D(sname[i])->type() != "profession" &&  (sname[i] != "array" && sname[i] != "axe" && sname[i] != "blade" && sname[i] != "claw"
&& sname[i] != "club" && sname[i] != "cuff" && sname[i] != "dagger" && sname[i] != "dodge" && sname[i] != "finger" && sname[i] != "force" && sname[i] != "fork"
&& sname[i] != "halberd" && sname[i] != "hammer" && sname[i] != "hand" && sname[i] != "hook" && sname[i] != "iron-cloth" && sname[i] != "leg" && sname[i] != "magic" 
&& sname[i] != "move" && sname[i] != "parry" && sname[i] != "pestle" && sname[i] != "spear" && sname[i] != "spells" && sname[i] != "staff" && sname[i] != "stick" 
&& sname[i] != "strike" && sname[i] != "sword" && sname[i] != "throwing" && sname[i] != "unarmed" && sname[i] != "whip"&& sname[i] != "checking" && sname[i] != "digging" 
&& sname[i] != "swimming")){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n",
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}

        return 1;
}


string skill_level(string type, int level,string skill)
{
        int grade;

        grade = level / 30;
        if(!type) type="martial";
	    if(SKILL_D(skill)->valid_enable("force") ) 
			{
					if(grade >=sizeof(force_skill))
							grade=sizeof(force_skill)-1;
					return force_skill[grade];
			}
		    
        grade = level / 30;
        switch(type) 
        {
                case "knowledge":
                        grade = level /50;
                        if( grade >= sizeof(knowledge_level_desc) )
                                grade = sizeof(knowledge_level_desc)-1;
                        return knowledge_level_desc[grade];
                default:
                        if( grade >= sizeof(skill_level_desc) )
                                grade = sizeof(skill_level_desc)-1;
                        return skill_level_desc[grade];
        }
}

int do_learn(string arg)
{
	string skill, teacher, master, skill_name, slow_msg;
	object ob,me;
	int master_skill, my_skill, gin_cost, slow_factor;
  	int i, tmp, learn_times;

	me=this_player();

	if (me->is_busy())
    {
		tell_object(me,"你现在正忙着呢。\n");
        return 1;
    }
    
	if(!arg)
	{
        tell_object(me,"指令格式：learn|xue <某人> for <技能> [次数]\n");
        return 1;
    }
  	if (sscanf(arg, "%s for %s %d", teacher, skill, learn_times)!=3 )
    {
        tell_object(me,"指令格式：learn|xue <某人> for <技能> [次数]\n");
	}
	if (learn_times < 1) 
		{
            tell_object(me,"指令格式：learn|xue <某人> for <技能> [次数]\n");
            return 1;
        }

	if( me->is_fighting() )
		{
            tell_object(me,"临阵磨枪？来不及啦。\n");
            return 1;
        }

	if( !(ob = present(teacher, environment(me))) || !ob->is_character())
		{
            tell_object(me,"你要向谁求教？\n");
            return 1;
        }

	if( !living(ob) )
		{
            tell_object(me,"嗯....你得先把" + ob->name() + "弄醒再说。\n");
            return 1;
        }

	if( me->query("potential")-me->query("learned_points") < learn_times )
		{
            tell_object(me,"你的潜能不够，没有办法再成长了。\n");
            return 1;
        }

	// HACK: recognize_apprentice takes care of the payment 
	// for literate.  We have to do this learn_times.
	for (i=0; i<learn_times; i++) 
    {
	    if( !me->query("newbie_village/master") || "wu shi" != ob->query("id") ) 
        {
            tell_object(me, ob ->name() + reject_msg[random(sizeof(reject_msg))] );
            return 1;
	    }
	}

	slow_factor = 1;
	slow_msg = "";

	if( !master_skill = ob->query_skill(skill, 1) )
	    {
            tell_object(me,"这项技能你恐怕必须找别人学了。\n");
            return 1;
        }

	
	if( ob->prevent_learn(me, skill) ) 
    {
        tell_object(me,ob->name() + "不愿意教你这项技能。\n");
        return 1;
    }

	my_skill = me->query_skill(skill, 1);

    if (5==me->query_skill("dodge",1) && 5==me->query_skill("force",1) && 5==me->query_skill("parry",1) && 5==me->query_skill("strike",1) && 5==me->query_skill("sword",1)
&& 5==me->query_skill("taiyi-shengong",1) && 5==me->query_skill("taiyi-you",1) && 5==me->query_skill("taiyi-zhang",1) && 5==me->query_skill("taiyi-jian",1))
    {
        set_nextquest(me,"学习武师身上所有基本功夫到5级，所有高级功夫到5级","把学到的功夫都激发起来吧！\njifa force taiyi-shengong 将太乙神功作为你使用的内功
jifa dodge taiyi-you 将太乙神游作为你使用的轻功\njifa sword taiyi-jian 将太乙剑法作为你使用的剑法\njifa parry taiyi-jian 将太乙剑法作为你使用的招架\njifa strike taiyi-zhang 将太乙掌法作为你使用的掌法", 50, 250);
		return 1;
	}	

	if ( my_skill>=5 && (skill == "dodge" || skill == "force" || skill == "parry" || skill == "strike" || skill == "sword"))
	{
		tell_object(me,"你只能学到五级的基本功夫。\n");
        return 1;
	}

	if ( my_skill>=5 && (skill == "taiyi-shengong" || skill == "taiyi-you" || skill == "taiyi-zhang" || skill == "taiyi-jian")) 
	{
		tell_object(me,"你只能学到五级的高级功夫。\n");
        return 1;
	}

	// if (me->is_spouse_of(ob) )
	    // if (my_skill >= master_skill - 20*(me->query("married_times")-1))
		// return notify_fail(ob->name() + "想到你和以前" 
			// + me->query("spouse/title") 
			// + "在一起的情形，有点不大愿意教你这项技能。\n");
	    // else if ( (ob->query("combat_exp") < 10000 
	    	       // || me->query("combat_exp") < 10000 )
			// && (string)SKILL_D(skill)->type() == "martial" ) 
		// return notify_fail("你们夫妇实战经验还不足，不能互相传授武艺！\n");
		
	// notify_fail("依你目前的能力，没有办法学习这种技能。\n");
	// if (me->is_spouse_of(ob)) me->add_temp("mark/朱", learn_times);
	// if( !SKILL_D(skill)->valid_learn(me) ) return 0;
	// if (me->is_spouse_of(ob)) me->add_temp("mark/朱", -learn_times);

	gin_cost = 60 / (int)me->query("int");

	if( !my_skill ) {
	    gin_cost *= 2;
	    me->set_skill(skill,0);
	}

	printf("你向%s请教有关「%s」的疑问。\n", ob->name(), to_chinese(skill));

	if( ob->query("env/no_teach") )
		{
            tell_object(me,"但是" + ob->name() + "现在并不准备回答你的问题。\n");
            return 1;
        }

	tell_object(ob, sprintf("%s向你请教有关「%s」的问题。\n", me->name(), to_chinese(skill)));

	if( (int)ob->query("jing") > learn_times*gin_cost/5 + 1 ) {
		if( userp(ob) ) ob->receive_damage("jing", learn_times*gin_cost/5 + 1);
	} else {
		write("但是" + ob->name() + "显然太累了，没有办法教你什么。\n");
		tell_object(ob, "但是你太累了，没有办法教" + me->name() + "。\n");
		return 1;
	}
		
	gin_cost = learn_times * gin_cost*3/2;
	
	if( (int)me->query("jing") > gin_cost ) {
		if( (string)SKILL_D(skill)->type()=="martial"
		&&	my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) {
			printf("也许是缺乏实战经验，你对%s的回答总是无法领会。\n", ob->name() );
		} else {
		    if(skill_name = SKILL_D(skill)->query_skill_name(my_skill)) {
			if ( skill=="linji-zhuang" )
			    printf("你听了%s的指导，%s对「%s」的修养似乎有所提高。\n", 
				    ob->name(), slow_msg, skill_name);
			else
			    printf("你听了%s的指导，%s对「%s」这一招似乎有些心得。\n", 
				    ob->name(), slow_msg, skill_name);
		    }
		    else
			printf("你听了%s的指导，%s似乎有些心得。\n", ob->name(), slow_msg);
			
            me->add("learned_points", learn_times );

		    tmp = 0;
		    for (i=0; i<learn_times; i++)  tmp += random(me->query_int());
	
		    me->improve_skill(skill, tmp/slow_factor);

		}
	} else {
		gin_cost = me->query("jing") > 0 ? (int)me->query("jing") : 0;
		write("你今天太累了，结果什么也没有学到。去睡一觉再来学吧。\n");
	}

	me->receive_damage("jing", gin_cost);
    
    if (5==me->query_skill("dodge",1) && 5==me->query_skill("force",1) && 5==me->query_skill("parry",1) && 5==me->query_skill("strike",1) && 5==me->query_skill("sword",1)
&& 5==me->query_skill("taiyi-shengong",1) && 5==me->query_skill("taiyi-you",1) && 5==me->query_skill("taiyi-zhang",1) && 5==me->query_skill("taiyi-jian",1))
    {
        set_nextquest(me,"学习武师身上所有基本功夫到5级，所有高级功夫到5级","把学到的功夫都激发起来吧！\njifa force taiyi-shengong 将太乙神功作为你使用的内功
jifa dodge taiyi-you 将太乙神游作为你使用的轻功\njifa sword taiyi-jian 将太乙剑法作为你使用的剑法\njifa parry taiyi-jian 将太乙剑法作为你使用的招架\njifa strike taiyi-zhang 将太乙掌法作为你使用的掌法", 50, 250);
    }

	return 1;
}