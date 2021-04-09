#include <ansi.h>
inherit NPC;

string ask_for_jiangli();
string ask_for_gongshi();

void create()  
{       set_name(RED "郭靖" NOR, ({ "guo jing","jing","guo" }));
        set("nickname", GRN"威震中原,名贯漠北"NOR);
        set("nocleanup", 1);
        set("id", "guo jing");
        set("title",YEL"北侠"NOR);
        set("gender", "男性");
        set("age", 40);
        set("str", 30);
        set("dex", 60);
        set("long", "这就是一代大侠郭靖。\n");
        set("combat_exp", 1800000);
        set("shen_type",1);
        set("attitude", "peaceful");
        set_skill("strike", 220);
        set_skill("force", 200);
        set_skill("xianglong-zhang", 250);
        set_skill("xiaoyaoyou", 300);        // 逍遥游
        set_skill("huntian-qigong", 300);    // 混天气功
        set_skill("dodge", 200);
        set_skill("parry", 300);                

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("parry", "xianglong-zhang"); 
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("strike", "xianglong-zhang");
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("neili", 4000); 
        set("qi", 6000); 
        set("max_qi", 6000); 
        set("max_neili", 4000);
        set("jingli", 4000); 
        set("max_jingli", 4000);

        set("inquiry",([ 
        "奖励"  : (: ask_for_jiangli :),
        "工事" : (: ask_for_gongshi :)
        ]));
        set("chat_chance",1);
        set("chat_msg", ({
        "听说有蒙古奸细混进城中，不知是真是假？\n",
        "蒙古大军终于来了，大家一定要把城门守好！\n"
        }) );
        setup();
        carry_object("/clone/armor/tiejia")->wear();
}
int unconcious()
{
	return 1;
}
int die()
{
	if(!query("killed")) return 1;
	::die();
}
string ask_for_gongshi()
{
        object xytask,tieqiao;
        object me;
        me=this_player();
        xytask=load_object("/adm/daemons/xytaskd.c");
        
        if (xytask->query("victory"))
                return "这次保卫已经成功了，"+ RANK_D->query_respect(me) + "若是有心报国请下次保卫开始时再来。\n";
        if (me->query_temp("xytaskd/tieqiao"))
                return "战争时期资源有限，" + RANK_D->query_respect(me) + "已经领取过铁锹，就不要再领了。\n";
        message_vision("郭靖令手下军士给$N一把铁锹。\n",me);
        tieqiao = new("/d/xytaskd/obj/tieqiao");
        tieqiao->set("taskid",xytask->query("taskid"));
        me->set_temp("xytaskd/taskid",xytask->query("taskid"));
        tieqiao->move(me);
        me->set_temp("xytaskd/tieqiao",1);
        return "希望" + RANK_D->query_respect(me) + "能好好利用这把铁锹，为保卫襄阳进一份力！\n";
}

string ask_for_jiangli()
{
	int jiangli,bonus,times;
        int jiangli1,jiangli2,jiangli3,jiangli4;
	object xytask;
	object me;
	me=this_player();
	xytask=load_object("/adm/daemons/xytaskd.c");
	bonus=4-xytask->query("occupied");
	times = xytask->query("times");
	//if(!xytaskd->query("victory"))
	if(!query("killed"))
	{
		command("faint");
		command("chat* zt2 "+me->query("id"));
		tell_object(me,HIW"郭靖怒道：襄阳现在正在水深火热之中，你跑来领赏，真是岂有此理!\n"NOR);
		me->delete_temp("xytaskd");
		return "请自重!\n";
	}
	else if( (!me->query_temp("xytaskd/qianhuzhang")&&!me->query_temp("xytaskd/gongshi")&&!me->query_temp("xytaskd/number"))
        || query("taskid")!=me->query_temp("xytaskd/taskid"))
	{
	command("faint");
	command("chat* zt2 "+me->query("id"));
	return "你寸功未建，还想来领赏？\n";
	}
	else
	{
                  if (me->query("age") < 15)
                return RANK_D->query_respect(me) + "年龄太小，保卫襄阳太危险，以后不要来了。";
		command("chat* admire "+me->query("id"));
		//领取奖励
                message( "channel:" + "chat",HIW + "【任务奖励】"+me->query("name")+HIW"在保卫襄阳的战斗中杀敌军士卒"+chinese_number(me->query_temp("xytaskd/number"))+"人，杀蒙古奸细"+chinese_number(me->query_temp("xytaskd/jianxi"))+"人，杀蒙古千户长"+chinese_number(me->query_temp("xytaskd/qianhuzhang"))+"人，修筑防御工事"+chinese_number(me->query_temp("xytaskd/gongshi")) + "次，特此嘉奖!\n"NOR,users());
/*
		jiangli=(me->query_temp("xytaskd/qianhuzhang")*(4000+bonus*500)+me->query_temp("xytaskd/jianxi")*(1000+bonus*500)+me->query_temp("xytaskd/number")*(600+bonus*400))*times*3/5+me->query_temp("xytaskd/gongshi")*random(200+bonus*200);
*/
jiangli1=me->query_temp("xytaskd/gongshi")*random(200+bonus*200);//修建工事
jiangli2=me->query_temp("xytaskd/qianhuzhang")*(4000+bonus*500);//千户长
jiangli3=pow(me->query_temp("xytaskd/jianxi"),0.5)*4*(1000+bonus*500);//奸细
//以16为基数，16之前的提高奖励，16之后的降低降低
jiangli4=pow(me->query_temp("xytaskd/number"),0.5)*6*(600+bonus*400);//普通士兵
//以36为基数
jiangli=jiangli1+to_int((jiangli2+jiangli3+jiangli4)*times*3/5);
                if (me->query("age") > 14)
		{
		CHANNEL_D->do_channel(this_object(), "sys",sprintf("%s在保卫襄阳中获得经验：%d、潜能：%d。", me->name(),jiangli,jiangli/12));
		tell_object(me,HIR"你共得到"+chinese_number(jiangli)+"点经验，和"+chinese_number(jiangli/12)+"点潜能的奖励!\n"NOR);
		me->add("combat_exp",jiangli);
		me->add("exp/xytask",jiangli);
		me->add("potential",jiangli/12);
		me->add("pot/xytask",jiangli/12);
		jiangli = me->query_temp("xytaskd/qianhuzhang") * 100   //千户长一个100声望
	        + me->query_temp("xytaskd/number") * 3          //普通兵一个3点声望
		+ me->query_temp("xytaskd/jianxi") * 30;        //奸细一个30点声望
		if(jiangli)
		{
		me->add("repute",jiangli);
		tell_object(me,HIR"由于你在战斗中的突出表现，你的江湖声望上升了"+chinese_number(jiangli)+"点!\n"NOR);
		       }
		}
		me->delete_temp("xytaskd");
		return "谢谢你为保护襄阳出了一分力！";
		}
	}
int accept_object(object me, object ob)
{
        object xytask,obj;
        xytask=load_object("/adm/daemons/xytaskd.c");
        if(!xytask->query("begin"))
        {
                command("haha");
                command("hoho "+me->query("id"));
                if(!ob->is_character()) 
                {
                        remove_call_out("des");
                        call_out("des",1,ob);
                }
                else
                {
                        command("faint");
                        remove_call_out("return_ob");
                        call_out("return_ob",1,me,ob);                  
                }
                return 1;
        }
        if(ob->query("id")=="yingxiong tie")
        {
                command("haha");
                command("say 你收到我的信了？这里是一把钢刀和一个铁甲，英雄拿去用吧！");
                command("say 希望能够对你杀敌有所帮助!");
                message_vision("郭靖给$N一把钢刀和一个铁甲.\n",me);
                obj=new("/clone/armor/tiejia.c");
                obj->set_weight(0);
                obj->move(me);
                obj=new("/clone/weapon/gangdao.c");
                obj->set_weight(0);
                obj->move(me);
                if(!ob->is_character()) 
                {
                        remove_call_out("des");
                        call_out("des",1,ob);
                }
                else
                {
                        command("faint");
                        remove_call_out("return_ob");
                        call_out("return_ob",1,me,ob);
                }
                return 1;
        }
        if(!ob->is_character()) 
                {
                        remove_call_out("des");
                        call_out("des",1,ob);
                }
        else
                {
                        command("faint");
                        remove_call_out("return_ob");
                        call_out("return_ob",1,me,ob);
                }
        return 1;
}
int des(object obj)
{
        destruct(obj);
        return 1;
}
int return_ob(object me,object ob)
{
        command("faint "+me->query("id"));
        command("give "+ob->query("id")+" to "+me->query("id"));
        return 1;
}
