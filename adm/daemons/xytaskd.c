//xytaskd.c
//Made by mudy
//#define NUMBER1 20
//#define NUMBER2 30
//2002.11.4
inherit F_DBASE;
#include <ansi.h>
#include <localtime.h>
object startroom;
int NUMBER,number_mgb,NUMBER1,NUMBER2;
int cheater_number;
int increase_number;

int sentnotice1,sentnotice2,sentnotice3;

nosave object *mgbing1=({});
nosave object *mgbing2=({});
nosave object *mgbing3=({});
nosave object *mgbing4=({});
string *occur_file=({
              "/d/xiangyang/westr5.c",
              "/d/xiangyang/westr4.c",
              "/d/xiangyang/westr3.c",
              "/d/xiangyang/westr2.c",
              "/d/xiangyang/westr1.c",
              "/d/xiangyang/mroad1.c",
              "/d/xiangyang/mroad2.c",
              "/d/xiangyang/mroad3.c",
              "/d/xiangyang/mroad4.c",
              "/d/xiangyang/eroad1.c",
              "/d/xiangyang/caiyuan.c",
              "/d/xiangyangnan/jingmen.c"
           });
string *mgb_file=({
     "/d/xytaskd/cheatern1.c",
     "/d/xytaskd/cheatern2.c",
     "/d/xytaskd/cheaters1.c",
     "/d/xytaskd/cheaters2.c",
     "/d/xytaskd/cheaterw1.c",
     "/d/xytaskd/cheaterw2.c",
     "/d/xytaskd/cheatere1.c",
     "/d/xytaskd/cheatere2.c",
     "/d/xytaskd/guojing.c",
     "/d/xytaskd/huangrong.c",
     "/d/xytaskd/lvwende.c",
     "/d/xiangyang/npc/lvwende.c",
     "/d/xytaskd/mgbn2.c",
     "/d/xytaskd/mgbs1.c",
     "/d/xytaskd/mgbs2.c",
     "/d/xytaskd/mgbe1.c",
     "/d/xytaskd/mgbe2.c",
     "/d/xytaskd/mgbw1.c",
     "/d/xytaskd/mgbw2.c",
     "/d/xytaskd/qianhuzhangn.c",
     "/d/xytaskd/qianhuzhangs.c",
     "/d/xytaskd/qianhuzhangw.c",
     "/d/xytaskd/qianhuzhange.c",
     "/d/xytaskd/mgqbn1.c",
     "/d/xytaskd/mgqbn2.c",
     "/d/xytaskd/mgqbs1.c",
     "/d/xytaskd/mgqbs2.c",
     "/d/xytaskd/mgqbw1.c",
     "/d/xytaskd/mgqbw2.c",
     "/d/xytaskd/mgqbe1.c",
     "/d/xytaskd/mgqbe2.c",
     "/d/xytaskd/shoujun.c",
     "/d/xytaskd/mgbn1.c"
});
string *key_spot=({
     "/d/xiangyang/sgate.c",
     "/d/xiangyang/egate.c",
     "/d/xiangyang/wgate.c",
     "/d/xiangyang/sfdating.c",
     "/d/xiangyang/ngate.c"
     });
void start_task(int times);
void task_done();
void pre_destruct();
void checkstarttime();

void create()
{
	seteuid(getuid());

    set("channel_id",HIW"保卫襄阳"NOR);
    set("begin",0);
    set("victory",0);
	  set("times",0);

	sentnotice1 = 0;
	sentnotice2 = 0;
	sentnotice3 = 0;
  set_temp("channel_environment", "/d/xiangyang/sfdating");

	remove_call_out("checkstarttime");
	call_out("checkstarttime",60);	

}
void start_task(int times)
{
	object *mgb_list=({});
	object guojing;
	object huangrong,lvwende,obj;
	set("times",times);
	set("begin",1);
    set("victory",0);
	increase_number = this_object()->query("occupied");
	increase_number = 4 - increase_number;
    set("occupied",0);
    set("xyoccupied",0);
    set("east",0);
    set("south",0);
    set("west",0);
    set("north",0);
    set("east_qb",0);
    set("south_qb",0);
    set("west_qb",0);
    set("north_qb",0);
	set("taskid",10+random(50));
	for(int j=0;j<sizeof(key_spot);j++)
		{
		 (load_object(key_spot[j]))->set("no_reset", 2);
         (load_object(key_spot[j]))->set("no_clean_up", 1);
		 }
	if( objectp( guojing = present("guo jing", load_object("/d/xiangyang/sfdating.c")) ))
		{
		destruct(guojing);
		}
		if (query("times") == 1)
		{
		    NUMBER1 = 5;
		    NUMBER2 = 5;
			//task 前的描述
            CHANNEL_D->do_channel(this_object(), "rw", HIY + "保卫襄阳任务启动！"NOR, -1);
            CHANNEL_D->do_channel(this_object(), "rw", HIY + "请大家在襄阳打开bd频道，否则看不见保卫信息。"NOR ,-1);
            CHANNEL_D->do_channel(this_object(), "rw", HIR + "参加保卫时请尽量set skip_combat 2,在不影响提示信息的前提下减轻系统负担。\n"NOR, -1);
		}
		else if (query("times") == 2)
		{
               cheater_number = cheater_number+4;
                NUMBER1 = NUMBER1 + 8 + 4*increase_number;
                NUMBER2 = NUMBER2 + 8 + 4*increase_number;
		}
		else 
		{
               cheater_number = cheater_number+6;
                NUMBER1 = NUMBER1 + 12 + 6*increase_number;
                NUMBER2 = NUMBER2 + 12 + 6*increase_number;
		}
	set("cheater_number",cheater_number);
	set("number1",NUMBER1);
	set("number2",NUMBER2);
    CHANNEL_D->do_channel(this_object(), "sys", HIR + "现在设置cheater_number,number1,number2可调整难度。" NOR);
	for(int j=0;j<sizeof(mgb_file);j++)
		{
		mgb_list = children(mgb_file[j]);
		for(int k=0; k<sizeof(mgb_list); k++)
			destruct(mgb_list[k]);
		}
	lvwende=new("/d/xytaskd/lvwende");
	lvwende->move("/d/xiangyang/sfdating.c");
	guojing=new("/d/xytaskd/guojing.c");
	guojing->move("/d/xiangyang/sfdating.c");
	guojing->set("taskid",query("taskid"));
	guojing->set("no_clean_up",1);
	(load_object("/d/xiangyang/sfdating.c"))->set("shuaifu",1);
	(load_object("/d/xiangyang/ngate.c"))->set("gate",1);
	(load_object("/d/xiangyang/wgate.c"))->set("gate",1);
	(load_object("/d/xiangyang/sgate.c"))->set("gate",1);
	(load_object("/d/xiangyang/egate.c"))->set("gate",1);
	(load_object("/d/xiangyang/sfdating.c"))->set("destroy",0);
	(load_object("/d/xiangyang/ngate.c"))->set("destroy",0);
	(load_object("/d/xiangyang/wgate.c"))->set("destroy",0);
	(load_object("/d/xiangyang/sgate.c"))->set("destroy",0);
	(load_object("/d/xiangyang/egate.c"))->set("destroy",0);
	huangrong=new("/d/xytaskd/huangrong.c");
	huangrong->move("/d/xiangyang/sfdating.c");
	for(int j=0;j<30;j++)
		{
		obj=new("/d/xytaskd/shoujun");
		obj->move(load_object("/d/xiangyang/xycenter"));
		}
	//remove_call_out("init_data");
	//call_out("init_data",1);
	if (query("times") == 1)
	{
		remove_call_out("pre_message1");
		call_out("pre_message1",1);
	}
	else
	{
		remove_call_out("pre_message8");
		call_out("pre_message8",1);
	}
	set("begin_time",time());
	set("can_dig",1);


	return;
}

int init_data()
{
	object obj;
	int i;
	string err;
	
	//************************************派兵函数名数组，每次init_data时重置，调用派兵时修改其内容
	string* paibings;
	paibings = ({"pai_bing0","pai_bing1","pai_bing2","pai_bing3"});
	
	
	
	for(int j=0;j<sizeof(mgbing1);j++)
		{
		if(!undefinedp(mgbing1[j])&&objectp(mgbing1[j]))
			destruct(mgbing1[j]);
		}
	for(int j=0;j<sizeof(mgbing2);j++)
		{
		if(!undefinedp(mgbing2[j])&&objectp(mgbing2[j]))
			destruct(mgbing2[j]);
		}
	for(int j=0;j<sizeof(mgbing3);j++)
		{
		if(!undefinedp(mgbing3[j])&&objectp(mgbing3[j]))
			destruct(mgbing3[j]);
		}
	for(int j=0;j<sizeof(mgbing4);j++)
		{
		if(!undefinedp(mgbing4[j])&&objectp(mgbing4[j]))
			destruct(mgbing4[j]);
		}
	mgbing1=({});
	mgbing2=({});
	mgbing3=({});
	mgbing4=({});
    CHANNEL_D->do_channel(this_object(), "sys", HIR + "停止设置难度。" NOR);
	set("can_dig",0);
	NUMBER1 = query("number1");
	NUMBER2 = query("number2");
	cheater_number = query("cheater_number");
	//******************************************随机方向派兵
	
	i=random(sizeof(paibings));
	remove_call_out(paibings[i]);
	call_out(paibings[i],1);
	paibings -= ({paibings[i]});
	i=random(sizeof(paibings));
	remove_call_out(paibings[i]);
	call_out(paibings[i],6);
	paibings -= ({paibings[i]});
	i=random(sizeof(paibings));
	remove_call_out(paibings[i]);
	call_out(paibings[i],16);
	paibings -= ({paibings[i]});
	i=random(sizeof(paibings));
	remove_call_out(paibings[i]);
	call_out(paibings[i],21);


	//派奸细
	remove_call_out("pai_cheater");
	call_out("pai_cheater",26);	
	return 1;
}
int pai_bing3()//北门
{
    object obj;
    string err;
    int i;

    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古发兵攻打襄阳北门！" NOR, -1);
	for(i=0;i<NUMBER1;i++)
    {
        err=catch(obj=new("/d/xytaskd/mgbn1"));
        if (err) 
        {
            CHANNEL_D->do_channel(this_object(), "sys", HIY + "创建失败！\n" NOR);
            return 1;
        }
        obj->set("taskid",query("taskid"));
        mgbing1+=({obj});
        mgbing1[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
    }
	for(i=NUMBER1;i<NUMBER2;i++)
		{
		obj=new("/d/xytaskd/mgbn2");
		obj->set("taskid",query("taskid"));
		mgbing1+=({obj});
		mgbing1[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
		}
	obj=new("/d/xytaskd/qianhuzhangn");
	obj->set("taskid",query("taskid"));
	mgbing1+=({obj});
	mgbing1[NUMBER2]->move(load_object("/d/xiangyang/caoyuan4.c"));
//	remove_call_out("pai_bing");
//	call_out("pai_bing",5);
	return 1;
	}
int pai_bing0()
{
	object obj;
	int i;
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古发兵攻打襄阳南门！" NOR, -1);
	for(i=0;i<NUMBER1;i++)
    {
        obj=new("/d/xytaskd/mgbs1");
        obj->set("taskid",query("taskid"));
        mgbing2+=({obj});
        mgbing2[i]->move(load_object("/d/xiangyangnan/jingmen.c"));
    }
	for(i=NUMBER1;i<NUMBER2;i++)
    {
        obj=new("/d/xytaskd/mgbs2");
        obj->set("taskid",query("taskid"));
        mgbing2+=({obj});
        mgbing2[i]->move(load_object("/d/xiangyangnan/jingmen.c"));
    }
	obj=new("/d/xytaskd/qianhuzhangs");
	obj->set("taskid",query("taskid"));
	mgbing2+=({obj});
	mgbing2[NUMBER2]->move(load_object("/d/xiangyangnan/jingmen.c"));
//	remove_call_out("pai_bing1");
//	call_out("pai_bing1",10);
	return 1;
}

int pai_bing1()
{
	object obj;
	int i;
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古发兵攻打襄阳西门！" NOR, -1);
	for(i=0;i<NUMBER1;i++)
    {
        obj=new("/d/xytaskd/mgbw1");
        obj->set("taskid",query("taskid"));
        mgbing3+=({obj});
        mgbing3[i]->move(load_object("/d/xiangyang/westr5.c"));
    }
	for(i=NUMBER1;i<NUMBER2;i++)
    {
        obj=new("/d/xytaskd/mgbw2");
        obj->set("taskid",query("taskid"));
        mgbing3+=({obj});
        mgbing3[i]->move(load_object("/d/xiangyang/westr5.c"));
    }
	obj=new("/d/xytaskd/qianhuzhangw");
	obj->set("taskid",query("taskid"));
	mgbing3+=({obj});
	mgbing3[NUMBER2]->move(load_object("/d/xiangyang/westr5.c"));
//	remove_call_out("pai_bing2");
//	call_out("pai_bing2",5);
	return 1;
}

int pai_bing2()
{
	object obj;
	int i;
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古发兵攻打襄阳东门！" NOR, -1);
	for(i=0;i<NUMBER1;i++)
    {
        obj=new("/d/xytaskd/mgbe1");
        obj->set("taskid",query("taskid"));
        mgbing4+=({obj});
        mgbing4[i]->move(load_object("/d/xiangyang/caiyuan.c"));
    }
	for(i=NUMBER1;i<NUMBER2;i++)
    {
        obj=new("/d/xytaskd/mgbe2");
        obj->set("taskid",query("taskid"));
        mgbing4+=({obj});
        mgbing4[i]->move(load_object("/d/xiangyang/caiyuan.c"));
    }
	obj=new("/d/xytaskd/qianhuzhange");
	obj->set("taskid",query("taskid"));
	mgbing4+=({obj});
	mgbing4[NUMBER2]->move(load_object("/d/xiangyang/caiyuan.c"));
//	remove_call_out("pai_cheater");
//	call_out("pai_cheater",5);
	return 1;
}


int pai_cheater()
{
	object obj;
	int number_random_occur;
	int i;
	number_random_occur=sizeof(occur_file);
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "蒙古将派出大量奸细混进襄阳！" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "蒙哥嘿嘿嘿的奸笑了几声..." NOR, -1);
	number_mgb=sizeof(mgbing1);
	for(i=number_mgb;i<number_mgb+cheater_number;i++)
    {
        obj=new("/d/xytaskd/cheatern1.c");
        obj->set("taskid",query("taskid"));
        obj->start_move();
        mgbing1+=({obj});
        mgbing1[i]->move(load_object(occur_file[random(number_random_occur)]));
    }
	number_mgb=sizeof(mgbing1);
	for(i=number_mgb;i<number_mgb+cheater_number;i++)
    {
        obj=new("/d/xytaskd/cheatern2.c");
        obj->set("taskid",query("taskid"));
        obj->start_move();
        mgbing1+=({obj});
        mgbing1[i]->move(load_object(occur_file[random(number_random_occur)]));
    }
	number_mgb=sizeof(mgbing2);
	for(i=number_mgb;i<number_mgb+cheater_number;i++)
    {
        obj=new("/d/xytaskd/cheaters1.c");
        obj->set("taskid",query("taskid"));
        obj->start_move();
        mgbing2+=({obj});
        mgbing2[i]->move(load_object(occur_file[random(number_random_occur)]));
    }
	number_mgb=sizeof(mgbing2);
	for(i=number_mgb;i<number_mgb+cheater_number;i++)
    {
        obj=new("/d/xytaskd/cheaters2.c");
        obj->set("taskid",query("taskid"));
        obj->start_move();
        mgbing2+=({obj});
        mgbing2[i]->move(load_object(occur_file[random(number_random_occur)]));
    }
	number_mgb=sizeof(mgbing3);
	for(i=number_mgb;i<number_mgb+cheater_number;i++)
    {
        obj=new("/d/xytaskd/cheaterw1.c");
        obj->set("taskid",query("taskid"));
        obj->start_move();
        mgbing3+=({obj});
        mgbing3[i]->move(load_object(occur_file[random(number_random_occur)]));
    }
	number_mgb=sizeof(mgbing3);
	for(i=number_mgb;i<number_mgb+cheater_number;i++)
    {
        obj=new("/d/xytaskd/cheaterw2.c");
        obj->set("taskid",query("taskid"));
        obj->start_move();
        mgbing3+=({obj});
        mgbing3[i]->move(load_object(occur_file[random(number_random_occur)]));
    }
	number_mgb=sizeof(mgbing4);
	for(i=number_mgb;i<number_mgb+cheater_number;i++)
    {
        obj=new("/d/xytaskd/cheatere1.c");
        obj->set("taskid",query("taskid"));
        obj->start_move();
        mgbing4+=({obj});
        mgbing4[i]->move(load_object(occur_file[random(number_random_occur)]));
    }
	number_mgb=sizeof(mgbing4);
	for(i=number_mgb;i<number_mgb+cheater_number;i++)
    {
        obj=new("/d/xytaskd/cheatere2.c");
        obj->set("taskid",query("taskid"));
        obj->start_move();
        mgbing4+=({obj});
        mgbing4[i]->move(load_object(occur_file[random(number_random_occur)]));
    }
	remove_call_out("inspect_victory");
	call_out("inspect_victory",1);
	return 1;
}

int inspect_victory()
{
	int i,sign;
	object guojing,huangrong,obj;
	if(!query("begin"))
		{
		for(i=0;i<sizeof(mgbing1);i++)
			{
			if(!undefinedp(mgbing1[i])&&objectp(mgbing1[i]))
				{
				mgbing1[i]->set("victory",1);
				mgbing1[i]->delete("no_clean_up");
				}
			}
		for(i=0;i<sizeof(mgbing2);i++)
			{
			if(!undefinedp(mgbing2[i])&&objectp(mgbing2[i]))
				{
				mgbing2[i]->set("victory",1);
				mgbing2[i]->delete("no_clean_up");
				}
			}
		for(i=0;i<sizeof(mgbing3);i++)
			{
			if(!undefinedp(mgbing3[i])&&objectp(mgbing3[i]))
				{
				mgbing3[i]->set("victory",1);
				mgbing3[i]->delete("no_clean_up");
				}
			}
		for(i=0;i<sizeof(mgbing4);i++)
			{
			if(!undefinedp(mgbing4[i])&&objectp(mgbing4[i]))
				{
				mgbing4[i]->set("victory",1);
				mgbing4[i]->delete("no_clean_up");
				}
			}
		for(int j=0;j<sizeof(key_spot);j++)
			{
			(load_object(key_spot[j]))->delete("no_reset");
			(load_object(key_spot[j]))->delete("no_clean_up");
			}
		if( objectp(huangrong= present("huang rong", load_object("/d/xiangyang/sfdating.c")) ))
			huangrong->delete("no_clean_up");
		if( objectp( guojing = present("guo jing", load_object("/d/xiangyang/sfdating.c")) ))
			{
			guojing->set("killed",1);
			guojing->delete("no_clean_up");
			}
		task_done();
		return 1;
		}
	sign=0;
	if(!sign) 
	{
		for(i=0;i<sizeof(mgbing1);i++)
				{
				if(!undefinedp(mgbing1[i])&&objectp(mgbing1[i]))
				{
					sign=1;
					break;
					}
				}
		if(!sign) mgbing1=({});
	}
	if(!sign) 
	{
		for(i=0;i<sizeof(mgbing2);i++)
				{
				if(!undefinedp(mgbing2[i])&&objectp(mgbing2[i]))
					{
					sign=1;
					break;
					}
				}
		if(!sign) mgbing2=({});
	}
	if(!sign) 
	{
		for(i=0;i<sizeof(mgbing3);i++)
				{
				if(!undefinedp(mgbing3[i])&&objectp(mgbing3[i]))
					{
					sign=1;
					break;
					}
				}
		if(!sign) mgbing3=({});
	}
	if(!sign)
	{
		for(i=0;i<sizeof(mgbing4);i++)
				{
				if(!undefinedp(mgbing4[i])&&objectp(mgbing4[i]))
					{
					sign=1;
					break;
					}
				}
		if(!sign) mgbing4=({});
	}
	if(!sign)
    {
        set("victory",1);
        set("begin",0);
        CHANNEL_D->do_channel(this_object(), "bd", HIR + "来犯蒙古兵全军覆没，襄阳保卫战取得胜利!" NOR, -1);
        if (!query("occupied"))
            CHANNEL_D->do_channel(this_object(), "rw", HIR + "襄阳各处城门均挡住了敌军的攻击。" NOR, -1);
        else
            CHANNEL_D->do_channel(this_object(), "rw", HIR + "襄阳共有"+chinese_number(query("occupied"))+"处城门被敌军攻破!" NOR, -1);
        if (query("times") == 3)
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙哥仰天长叹：我有生之年再不踏足中原一步以告慰众将士在天之灵!" NOR, -1);
        CHANNEL_D->do_channel(this_object(), "rw", HIY + "请保卫襄阳战斗中作出贡献的侠士，到郭靖处领取奖励!" NOR, -1);
        for(int j=0;j<sizeof(key_spot);j++)
            {
            //         (load_object(key_spot[j]))->delete("no_reset");
            (load_object(key_spot[j]))->delete("no_clean_up");
            }
        remove_call_out("clean_reset");
        if (query("times") == 3)
            call_out("clean_reset",300);//5分钟后清除标志
        if( objectp(huangrong= present("huang rong", load_object("/d/xiangyang/sfdating.c")) ))
            huangrong->delete("no_clean_up");
        if( objectp( guojing = present("guo jing", load_object("/d/xiangyang/sfdating.c")) ))
            {
            guojing->delete("no_clean_up");
            guojing->set("killed",1);
            }
        task_done();
        return 1;
    }
	else
    {
        //如果城门被破，加入骑兵入城！
        if(query("north")&&!query("north_qb"))
        {
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙哥大喜：襄阳北门已破，众将士再接再厉，骑兵从北门入城杀敌!" NOR, -1);
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古发骑兵从北面入城！\n" NOR, -1);
            number_mgb=sizeof(mgbing1);
            for(int j=number_mgb;j<number_mgb+20;j++)
            {
                if(random(2)==0) obj=new("/d/xytaskd/mgqbn1");
                else obj=new("/d/xytaskd/mgqbn2");
                obj->set("taskid",query("taskid"));
                mgbing1+=({obj});
                mgbing1[j]->move(load_object("/d/xiangyang/caoyuan4.c"));
            }
            set("north_qb",1);
        }
        else if(query("south")&&!query("south_qb"))
        {
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙哥大喜：襄阳南门已破，众将士再接再厉，骑兵从南门入城杀敌!" NOR, -1);
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古发骑兵从南面入城！\n" NOR, -1);
            number_mgb=sizeof(mgbing2);
            for(int j=number_mgb;j<number_mgb+20;j++)
            {
                if(random(2)==0) obj=new("/d/xytaskd/mgqbs1");
                else obj=new("/d/xytaskd/mgqbs2");
                obj->set("taskid",query("taskid"));
                mgbing2+=({obj});
                mgbing2[j]->move(load_object("/d/xiangyang/caoyuan4.c"));
            }
            set("south_qb",1);
        }
        else if(query("west")&&!query("west_qb"))
        {
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙哥大喜：襄阳西门已破，众将士再接再厉，骑兵从西门入城杀敌!" NOR, -1);
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古发骑兵从西面入城！\n" NOR, -1);
            number_mgb=sizeof(mgbing3);
            for(int j=number_mgb;j<number_mgb+20;j++)
            {
                if(random(2)==0) obj=new("/d/xytaskd/mgqbw1");
                else obj=new("/d/xytaskd/mgqbw2");
                obj->set("taskid",query("taskid"));
                mgbing3+=({obj});
                mgbing3[j]->move(load_object("/d/xiangyang/caoyuan4.c"));
            }
            set("west_qb",1);
        }
        else if(query("east")&&!query("east_qb"))
        {
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙哥大喜：襄阳东门已破，众将士再接再厉，骑兵从东门入城杀敌!" NOR, -1);
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古发骑兵从东面入城！\n" NOR, -1);
            number_mgb=sizeof(mgbing4);
            for(int j=number_mgb;j<number_mgb+20;j++)
            {
                if(random(2)==0) obj=new("/d/xytaskd/mgqbe1");
                else obj=new("/d/xytaskd/mgqbe2");
                obj->set("taskid",query("taskid"));
                mgbing4+=({obj});
                mgbing4[j]->move(load_object("/d/xiangyang/caoyuan4.c"));
            }
            set("east_qb",1);
        }
        else
        {}
        remove_call_out("inspect_victory");
        call_out("inspect_victory",5);
        return 1;
    }
}

//保卫襄阳之前交代历史背景
int pre_message1()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1234年，蒙古取蔡州，金灭。同年，宋出兵收复汴京，败还." NOR, -1);
    remove_call_out("pre_message2");
    call_out("pre_message2",10);
    return 1;
}

int pre_message2()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1251年，蒙哥即大汗位，统军西征。" NOR, -1);
	remove_call_out("pre_message3");
	call_out("pre_message3",6);
	return 1;
}

int pre_message3()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1257年，蒙哥亲征南宋。" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "........" NOR, -1);
	remove_call_out("pre_message4");
	call_out("pre_message4",8);
	return 1;
}

int pre_message4()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙哥：襄阳乃南宋门户，取之,南宋可灭!" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙哥：众将士听令，不日我军将兵分四路围攻襄阳!" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古大军斗志昂扬...." NOR, -1);
	remove_call_out("pre_message5");
	call_out("pre_message5",12);
	return 1;
}

int pre_message5()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "三日后......" NOR, -1);
	remove_call_out("pre_message6");
	call_out("pre_message6",5);
	return 1;
}

int pre_message6()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIR + "探子：报～～～～～～～～蒙古率数万大军直逼襄阳，三日内即将攻城，十万火急!" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "郭靖：全体将士，听令！从今天开始，全城戒备!" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "郭靖：蓉儿，你马上广发英雄帖，让各路英雄聚集襄阳，共御强敌!" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "黄蓉：嗯，靖哥哥。" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "吕文徳：......" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "某人想溜了...." NOR, -1);
	remove_call_out("pre_message7");
	call_out("pre_message7",12);
	remove_call_out("yingxiongtie");
	call_out("yingxiongtie",1);
	return 1;
}

int yingxiongtie()
{
	object *players,tie;
	players=users();
	for(int i=0;i<sizeof(players);i++)
	{
		if(players[i]->query("env/invisibility")) continue;
		if(players[i]->is_ghost()) continue;
                if(wizardp(players[i])) continue;
//	    if(!living(players[i])) continue;
		if(players[i]->query("combat_exp")<1000000) continue;
/*		tell_object(players[i],HIW"突然一只白雕飞到你身旁落下，嘴里叼着一张帖子\n你从白雕的嘴里一取下帖子，白雕就噗噗地飞走了．\n你一看竟然是一张英雄帖，上面写着："+players[i]->query("name")+HIW"亲启.\n"NOR);
		message_vision(MAG"$N收到一张英雄帖!\n"NOR,players[i]);
		tie=new("/d/xytaskd/yxtie.c");
		tie->set("invitedname",players[i]->query("name"));
		tie->move(players[i]);
*/
		NUMBER += 1;
		call_out("songtie",1+random(10),players[i]);
	}
	if (NUMBER <= 4){}
	else if (NUMBER <= 8)
	{
               cheater_number = 2;
                 NUMBER1 = 6;
                 NUMBER2 = 6;
	}
	else if (NUMBER <=12)
	{
               cheater_number = 3;
                 NUMBER1 = 9;
                 NUMBER2 = 9;
	}
	else
	{
               cheater_number = 4;
                 NUMBER1 = 15;
                 NUMBER2 = 15;
	}
	set("number1",NUMBER1);
	set("number2",NUMBER2);
	set("cheater_number",cheater_number);
	return 1;
}
int songtie(object player)
{
	object tie;
    if (!player) return 1;
	tell_object(player,HIW"突然一只白雕飞到你身旁落下，嘴里叼着一张帖子\n你从白雕的嘴里一取下帖子，白雕就噗噗地飞走了．\n你一看竟然是一张英雄帖，上面写着："+player->query("name")+HIW"亲启.\n"NOR);
	message_vision(MAG"$N收到一张英雄帖!\n"NOR,player);
	tie=new("/d/xytaskd/yxtie.c");
	tie->set("invitedname",player->query("name"));
	tie->move(player);
	return 1;
}
int pre_message7()
{
	set("cheater_number",cheater_number);
	remove_call_out("songtie");
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "吕文徳：郭……郭大侠，守不住啦，咱……咱们出城南退罢！" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "郭靖：安抚使何出此言？襄阳在，咱们人在，襄阳亡，咱们人亡！汝再多言..." NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIC + "郭靖非常确定的认为吕文徳就是一个大猪头!" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "黄蓉：你要是再说一声弃城退兵，我先在你身上刺三个透明窟窿！ " NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIY + "吕文徳：......" NOR, -1);
	remove_call_out("pre_message8");
	call_out("pre_message8",10);
	return 1;
}

int pre_message8()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古传令官：众官兵听着：大汗有旨，哪一个最先攻登城墙，便封他为襄阳城的城主。" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古兵大声欢呼..." NOR, -1);
	remove_call_out("pre_message9");
	call_out("pre_message9",15);
	return 1;
}

int pre_message9()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳告急......" NOR, -1);
	remove_call_out("pre_message10");
	call_out("pre_message10",20);
	return 1;
}

int pre_message10()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳告急......" NOR, -1);
	remove_call_out("pre_message11");
	call_out("pre_message11",20);
	return 1;
}

int pre_message11()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳告急......" NOR, -1);
	remove_call_out("pre_message12");
	call_out("pre_message12",20);
	return 1;
}

int pre_message12()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIW + "蒙古开始发兵！" NOR, -1);
	remove_call_out("init_data");
	call_out("init_data",1);
	return 1;
}

//后记
void task_done()
{
	if(query("victory") )
    {
        if (query("times") == 3)
        {
            //call内容
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳之战虽然胜利了，但是这一场屠戮却会很快在历史发展的长河中渐渐被人淡忘......" NOR, -1);
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "南宋的灭亡却是无法挽回......" NOR, -1);
            remove_call_out("post_message1");
            call_out("post_message1",5);
            //start check task time again
            sentnotice1 = sentnotice2 = sentnotice3 = 0;
            remove_call_out("checkstarttime");
            call_out("checkstarttime",60);
            return ;
        }
        else
        {
            CHANNEL_D->do_channel(this_object(), "bd", HIW + "城外传来蒙哥的叫嚣：南宋蛮子们等着！我这就回去集结大军，定要拿下你这小小襄阳城！" NOR, -1);
            call_out("start_task",60,query("times") + 1);
            set("can_dig",2);
            return;
        }
    }
	else
    {
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳之战虽然失败了，但是这一场屠戮却会很快在历史发展的长河中渐渐被人们淡忘......" NOR, -1);
            remove_call_out("post_message3");
            call_out("post_message3",5);
            sentnotice1 = sentnotice2 = sentnotice3 = 0;
            remove_call_out("checkstarttime");
            call_out("checkstarttime",60);
            return ;
    }
}

int post_message1()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1259年，蒙古侵入叙利亚，蒙哥死于四川．忽必烈围鄂州，与南宋议和，北还。" NOR, -1);
	remove_call_out("post_message2");
	call_out("post_message2",5);
	return 1;
}

int post_message2()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1273年，蒙古破樊城，襄阳降。" NOR, -1);
	remove_call_out("post_message3");
	call_out("post_message3",5);
	return 1;
	}
int post_message3()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1274年。蒙古发军二十万征南宋，同年十二月，下鄂州．" NOR, -1);
	remove_call_out("post_message4");
	call_out("post_message4",5);
	return 1;
}

int post_message4()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1275年。元、宋丁家洲会战，宋大败．元连克建康、平江、常州诸地．" NOR, -1);
	remove_call_out("post_message5");
	call_out("post_message5",5);
	return 1;
}

int post_message5()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1276年。南宋幼帝请降，临安破．" NOR, -1);
	remove_call_out("post_message6");
	call_out("post_message6",5);
	return 1;
}

int post_message6()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1278年。宋瑞宗死．同年十二月，文天祥兵败被俘．" NOR, -1);
	remove_call_out("post_message7");
	call_out("post_message7",5);
	return 1;
}

int post_message7()
{
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1279年。正月，元军破崖山，宋帝溺死，宋亡．" NOR, -1);
	remove_call_out("post_message8");
	call_out("post_message8",5);
	return 1;
}

int post_message8()
{
	int i;
	object *usr;

    CHANNEL_D->do_channel(this_object(), "bd", HIM + "公元1368年。朱元璋灭元，改国号大明....." NOR, -1);
    CHANNEL_D->do_channel(this_object(), "rw", HIY + "保卫襄阳任务全部结束！" NOR, -1);

	usr = users();
	for (i = 0;i <sizeof(usr);i++)
		usr[i]->delete_temp("xytaskd");
	//remove_call_out("start_task");
	//call_out("start_task",14400);//更新时间四小时
	return 1;
}

int clean_reset()
{
	for(int j=0;j<sizeof(key_spot);j++)
    {
        (load_object(key_spot[j]))->delete("no_reset");
    }
    CHANNEL_D->do_channel(this_object(), "bd", HIM + "襄阳保卫战的胜利好像渐渐的被人们所淡忘了........" NOR, -1);
	return 1;
}

void bd_notice1()
{
    CHANNEL_D->do_channel(this_object(), "rw", HIM+ "郭靖(Guo jing)：据探子来报，蒙古最近动向可疑，意图对襄阳不利！ " NOR, -1);
	return;
}

void bd_notice2()
{
    CHANNEL_D->do_channel(this_object(), "rw", HIY+ "郭靖(Guo jing)：据探子来报，蒙古厉兵秣马，大军正开往襄阳！" NOR, -1);
	return;
}

void bd_notice3()
{
    CHANNEL_D->do_channel(this_object(), "rw", HIR+ "郭靖(Guo jing)：据探子来报，蒙古大军已逼近襄阳，请各位江湖儿女做好保卫准备！" NOR, -1);
	return;
}

//每天固定的3,7,11,15,19,23点开始
void checkstarttime()
{
	mixed* timeinfos;
	int hour;
	int minute;
	int mday;
	int flag = 0;

	timeinfos = localtime(time());

	hour = timeinfos[LT_HOUR];
	minute = timeinfos[LT_MIN];
	mday = timeinfos[LT_MDAY];
	
	if(hour == 2 || hour == 6 || hour == 10 || hour == 14 || hour == 18 || hour == 22)
	//if(hour == 6 || hour == 10 || hour == 14 || hour == 18 || hour == 22)
	{
		if (minute >= 30 && minute <= 32 && sentnotice1 == 0)
		{
			bd_notice1();
			sentnotice1 = 1;
		}
		else if(minute >= 40 && minute <= 42 && sentnotice2 == 0)
		{
			bd_notice2();
			sentnotice2 = 1;
		}
		else if(minute >= 50 && minute <= 52 && sentnotice3 == 0)
		{
			bd_notice3();
			sentnotice3 = 1;
		}
	}
	else if((hour == 3 || hour == 7 || hour == 11 || hour == 15 || hour == 19 || hour == 23) && minute >= 0 && minute <= 3)
	//else if((hour == 7 || hour == 11 || hour == 15 || hour == 19 || hour == 23) && minute >= 0 && minute <= 3)
	{
		remove_call_out("checkstarttime");
		start_task(1);
		return;
	}

	remove_call_out("checkstarttime");
	call_out("checkstarttime",60);
}