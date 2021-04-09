#include <ansi.h>
#include <title.h>
inherit F_SAVE;
inherit F_CLEAN_UP;
inherit F_DBASE;
string query_save_file()
{
	return "/data/business/vein_record";
}

#define Divide sprintf("%-190s","_____________________________________________________________________________________________\n")
#define ResponseTime 15//通穴状态下一些特殊时间（识图）的反应时间
#define VeinSkillLimit 800
#define BASICVEIN "/feature/vein/BasicVein/"

string DIVIDE()
{
	return Divide;
}
string *PointStatus()
{	
	return({"○","◎","⊕","●"});
}
mapping transfile()
{	
	return (["手阳明大肠经":"shouyangming","手太阴肺经":"shoutaiyin","足阳明胃经":"zuyangming","足太阴脾经":"zutaiyin","手少阴心经":"shoushaoyin","手太阳小肠经":"shoutaiyang","足太阳膀胱经":"zutaiyang","足少阴肾经":"zushaoyin","手厥阴心包经":"shouqueyin","手少阳三焦经":"shoushaoyang","足少阳胆经":"zushaoyang","足厥阴肝经":"zuqueyin","任脉":"renmai","督脉":"dumai",
	"冲脉":"chongmai","带脉":"daimai","阴跷脉":"yinqiaomai","阳跷脉":"yangqiaomai","阴维脉":"yinweimai","阳维脉":"yangweimai",]);
}
int family_id(object me)
{
	mapping f_id=(["少林派":1,"武当派":2,"丐帮":3,"白驼山":4,"星宿派":5,"华山派":6,"峨嵋派":7,"明教":8,"日月神教":9,"古墓派":10,
"灵鹫宫":11,"全真派":12,"天龙寺":13,"桃花岛":14,"姑苏慕容":15,"朝廷":16,"天地会":17,"神龙教":18,"大轮寺":19,"雪山派":20,]);
	if (!me||!me->query("family/family_name")||member_array(me->query("family/family_name"),keys(f_id))==-1) return -1;
	return f_id[me->query("family/family_name")];
}
string *veins()
{
	return ({"手太阴肺经","手阳明大肠经","足阳明胃经","足太阴脾经","手少阴心经",
	"手太阳小肠经","足太阳膀胱经","足少阴肾经","手厥阴心包经","手少阳三焦经",
	"足少阳胆经","足厥阴肝经","任脉","督脉","冲脉","带脉","阴跷脉","阳跷脉","阴维脉","阳维脉",});
}
//me->query("myVeins/"+ThisVein(me)+"/status")是通穴状态，一组数组，总数和AcuPoint_list(me)相同，0的状态是未通，1是正在通穴，3是已通，2是走火
object GetFile(object me)
{
	object target;
	mapping transfile=transfile();
	string *veins=veins();
	if (!me)
	return target;
	if (objectp(me->query_temp("vein_through")))
	return me->query_temp("vein_through");
	else if (!me->query("env/vein")||member_array(me->query("env/vein"),veins)==-1)
	tell_object(me,"请参考help，正确设定目标经脉set vein。");
	else
	target=load_object(BASICVEIN+transfile[me->query("env/vein")]+".c");
	return target;
}
string * AcuPoint_list(object me)
{
	return GetFile(me)->AcuPoint_list();
}
string ThisVein(object me)
{
	return GetFile(me)->ThisVein();
}
string vein(object me)
{
	return GetFile(me)->vein();
}
string veintitle(object me)
{
	return GetFile(me)->VeinTitle();
}
int DailyLimit(object me)
{
	return GetFile(me)->DailyLimit(me);
}
int Period(object me)
{
	return GetFile(me)->Period(me);
}
int RecoverRequire(object me)
{
	return GetFile(me)->recover_require();
}
int ExpConsume(object me)
{
	return GetFile(me)->ExpConsume();
}
int Level(object me)
{
	return GetFile(me)->Level();
}
int VeinDifficulty(object me)
{
	return GetFile(me)->Difficulty();
}
int Purify(object me)
{
	return GetFile(me)->Purify();
}
int PureNeili(object me)
{
	return GetFile(me)->PureNeili();
}
int ExpBonus(object me)//全部贯通以后一段时间的经验加成%
{
	return GetFile(me)->ExpBonus();
}
int BonusPeriod(object me)//持续多少小时
{
	return GetFile(me)->BonusPeriod();
}
int MaxGift(object me,string type)
{
	int res=0;
	mapping gift_vein2=(["int":"手少阴心经","str":"手太阳小肠经","dex":"足太阳膀胱经","con":"足少阴肾经"]);
	mapping gift_vein3=(["int":"手厥阴心包经","str":"手少阳三焦经","dex":"足少阳胆经","con":"足厥阴肝经"]);
	if (me->query("myVeins/"+gift_vein2[type]+"/completed"))
	res+=2;
	if (me->query("myVeins/"+gift_vein3[type]+"/completed"))
	res+=3;
	return res;
}
int AttrBonus(object me,string type)
{
	int res=0,vein3=10,tmp;
	mapping gift_vein=(["str":"手太阳小肠经","int":"手少阴心经","con":"足少阴肾经","dex":"足太阳膀胱经"]);
	if (query(gift_vein[type]+"/fastest/player")==me->query("id")||query(gift_vein[type]+"/earliest/player")==me->query("id"))
	res+=vein3;
	if (type=="int"&&tmp="/feature/vein/BasicVein/shoushaoyin.c"->benefit_effect(me))
	res+=tmp*me->query("int")/20;
	if (type="dex"&&tmp="/feature/vein/BasicVein/shoutaiyang.c"->benefit_effect(me))
	res+=tmp*me->query("dex")/20;
	return res;
}
int * init_vein(object me)
{
	int *myThisVein;
	if (!objectp(GetFile(me)))
	return ({});
	myThisVein=me->query("myVeins/"+ThisVein(me)+"/status");
	if (sizeof(myThisVein)==sizeof(AcuPoint_list(me)))
	return myThisVein;
	else if (!me->query("myVeins/"+ThisVein(me)+"/completed"))
	{
		myThisVein=({});
		for (int i=0;i<sizeof(AcuPoint_list(me));i++)
		myThisVein+=({0});
		me->set("myVeins/"+ThisVein(me)+"/status",myThisVein);
		return myThisVein;
	}
	else return ({});
}
float FinishDegree(object me,string vein)
{
	mapping transfile=transfile();
	int total_step;
	float percent,part_percent;
	if (!objectp(me)) return 0.0;
	if (!me->query("myVeins/"+vein+"/direction"))
	return 0.0;
	total_step=sizeof(load_object(BASICVEIN+transfile[vein]+".c")->AcuPoint_list());
	part_percent=to_float(me->query("myVeins/"+vein+"/CurPt"))/to_float(load_object(BASICVEIN+transfile[vein]+".c")->DailyLimit()*2)/to_float(total_step);
	percent=(me->query("myVeins/"+vein+"/direction"))>0?to_float(me->query("myVeins/"+vein+"/step"))/to_float(total_step):to_float(total_step-(me->query("myVeins/"+vein+"/step")+1))/to_float(total_step);
	percent+=part_percent;
	percent*=100.0;
	if (wizardp(me)) write("total step:"+total_step+"part_percent:"+part_percent+"percent:"+percent+"\n");
	return percent;
}
int show_vein(object me)
{
	mapping transfile=transfile();
	string myVein,vein,*PointStatus=PointStatus(),remain_time;
	int * myThisVein;
	if (!objectp(GetFile(me)))
	{
		tell_object(me,"你必须设定一个目标经脉。vein -h获得帮助。\n");
		return 1;
	}
	myVein=vein(me);
	myThisVein=init_vein(me);
	if (me->query("myVeins/"+ThisVein(me)+"/completed"))
	{
		for (int i=0;i<sizeof(AcuPoint_list(me));i++)
		myVein=replace_string(myVein,AcuPoint_list(me)[i],HIY+"●"+AcuPoint_list(me)[i]+"●"+NOR);
	}
	else if (me->query_temp("myVeins/HidePoint"))
	{
		vein=me->query_temp("myVeins/HidePoint");
		myVein=replace_string(myVein,vein,"");
		me->set_temp("myVeins/HiddenPoint/vein",vein);
		for (int i=0;i<sizeof(AcuPoint_list(me));i++)
		myVein=replace_string(myVein,AcuPoint_list(me)[i],PointStatus[myThisVein[i]]+AcuPoint_list(me)[i]);
	}
	else
	{
		for (int i=0;i<sizeof(AcuPoint_list(me));i++)
		myVein=replace_string(myVein,AcuPoint_list(me)[i],PointStatus[myThisVein[i]]+AcuPoint_list(me)[i]);
	}
	for (int i=0;i<sizeof(AcuPoint_list(me));i++)
	myVein=replace_string(myVein,AcuPoint_list(me)[i],AcuPoint_list(me)[i]+"["+(i+1)+"]");
	remain_time=CHINESE_D->chinese_period(to_int(Period(me)*(DailyLimit(me)*2-50)*sizeof(load_object(BASICVEIN+transfile[ThisVein(me)]+".c")->AcuPoint_list())*(1.0-FinishDegree(me,ThisVein(me))/100.0)));
	myVein=replace_string(myVein,veintitle(me),veintitle(me)+NOR+" 始于"+HBWHT+HIR+AcuPoint_list(me)[0]+"穴"+NOR+"  终于"+HBWHT+HIR+AcuPoint_list(me)[sizeof(AcuPoint_list(me))-1]+"穴"+NOR+" <第"+chinese_number(Level(me))+"层> "+NOR+"\n"+sprintf("%|190s",U+"单次冲穴"+NOR+HIR+Period(me)+NOR+"秒"+HIW+"|"+NOR+U+"通脉预计"+NOR+remain_time+HIW+"|"+NOR+U+"本日剩余"+NOR+HIG+((1000-me->query("myVeins/attempts"))>0?(1000-me->query("myVeins/attempts")):0)+NOR+"次"));
	myVein+=Divide;
	myVein+="○：未尝试穴道，◎：正在贯通穴道，⊕：受损穴道，●：已贯通穴道。"+HIY"金色"+NOR+"为经脉全部贯通。\n";
	tell_object(me,myVein);
	return 1;
}
int overall_vein(object me)
{
	float percent;
	string status,msg,*veins=veins();
	msg=sprintf("\n%|64s\n","╭────────────────────────────────╮");
	msg+=sprintf("%s%|64s%s\n","│","『十二正经及奇经八脉通脉情况』","│");
	msg+=sprintf("%|64s\n","├────────────────────────────────┤");
	for (int i=0;i<sizeof(veins);i++)
	{
		if (me->query("myVeins/"+veins[i]+"/completed"))
		{
			if (me->query("myVeins/"+veins[i]+"/completed")==2) 
			status="已通：正";
			else
			status="已通：逆";
		}
		else if (!me->query("myVeins/"+veins[i]+"/direction"))
			status="未尝试";
		else
		{
			percent=FinishDegree(me,veins[i]);
			status="完成度："+sprintf("%.2f%s",percent,"%");
		}
		if (i%2==0)
		msg+="│";
		msg+=sprintf("%-16s%-16s","【"+veins[i]+"】",status,);
		if (i%2==1)
		msg+="│\n";
		if (i==11)
		msg+=sprintf("%|64s\n","├────────────────────────────────┤");
	}
	msg+=sprintf("%|64s\n","╰────────────────────────────────╯");
	tell_object(me,msg);
	return 1;
}
string NextAccPoint(object me,string AccPoint)
{
	int * myThisVein;
	if (!objectp(GetFile(me)))
	{
		tell_object(me,"你必须设定一个目标经脉。vein -h获得帮助。\n");
		return "";
	}
	myThisVein=init_vein(me);
	if (me->query("myVeins/"+ThisVein(me)+"/completed"))
	{
		tell_object(me,ThisVein(me)+"已经贯通了。\n");
		return "";
	}
	if (!me->query("myVeins/"+ThisVein(me)+"/direction"))
	return "你还没有开始尝试冲击"+ThisVein(me)+"呢。\n";
	if (me->query("myVeins/"+ThisVein(me)+"/direction")==1)
	return AcuPoint_list(me)[member_array(AccPoint,AcuPoint_list(me))+1];
	else
	return AcuPoint_list(me)[member_array(AccPoint,AcuPoint_list(me))-1];
}
int Reward(object me,int vein_no,string gift)
{
	string *veins=veins();
	mapping gifts=(["int":"悟性","str":"膂力","con":"根骨","dex":"身法"]),other_gifts=(["kar":"福源","per":"容貌","spi":"灵性"]);
	if (me->query("myVeins/"+veins[vein_no]+"/completed"))
	{
		me->add(gift,1);
		me->add("xiantian/"+gift+"/vein",1);
		tell_object(me,"通脉之后，你觉得自己在"+gifts[gift]+"方面获得了增长。\n");
	}
	else
	{
		if (!me->query("env/NoVeinOtherGift"))
		{
			gift=keys(other_gifts)[random(sizeof(other_gifts))];
			me->add(gift,1);
			me->add("xiantian/"+gift+"/vein",1);
			tell_object(me,"通脉之后，你觉得自己在"+other_gifts[gift]+"方面获得了增长。\n");
		}
	}
	return 1;
}
int reward_random_gift(object me,int vein_no)
{
	mapping gifts=(["int":"悟性","str":"膂力","con":"根骨","dex":"身法","kar":"福源","per":"容貌","spi":"灵性"]);
	string g, *gift=({ });
	string *veins=veins();
	int vein_no2;
	vein_no2 = (vein_no%2==0)?(vein_no-2):(vein_no);
	if (!me->query("myVeins/"+veins[vein_no2]+"/completed"))
		return 1;
	if (me->query("str")<50) gift += ({"str"});
	if (me->query("int")<50) gift += ({"int"});
	if (me->query("con")<50) gift += ({"con"});
	if (me->query("dex")<50) gift += ({"dex"});
	if (sizeof(gift)<=0 && !me->query("env/NoVeinOtherGift"))
		gift = ({"kar","per","spi"});
	if (sizeof(gift)>0)
	{
		g = gift[random(sizeof(gift))];
		me->add(g, 1);
		me->add("xiantian/"+g+"/vein", 1);
		tell_object(me,"通脉之后，你觉得自己在"+gifts[g]+"方面获得了增长。\n");
	}
	return 1;
}
void EXTRA_REWARD(object me,int vein_no)
{
	int time=time()+3600,bonus=15;
	string wx,*wuxings=({HIW"金"NOR,HIG"木"NOR,HIB"水"NOR,HIR"火"NOR,YEL"土"NOR});
	if (vein_no==1||vein_no==5)
	Reward(me,vein_no,"int");
	if (vein_no==2||vein_no==6)
	Reward(me,vein_no-2,"con");
	if (vein_no==3||vein_no==7)
	Reward(me,vein_no,"dex");
	if (vein_no==4||vein_no==8)
	Reward(me,vein_no-2,"str");
	if (vein_no>=9)
		reward_random_gift(me,vein_no);
	if (me->query("myVeins/"+ThisVein(me)+"/Chance"))//激活经脉五行属性，识图全部完成
	{
		wx=wuxings[random(sizeof(wuxings))];
		me->delete("myVeins/"+ThisVein(me)+"/Chance");
		me->set("myVeins/wuxing/"+ThisVein(me),COLOR_D->uncolor(wx));
		tell_object(me,HIG+"恭喜，你的"+ThisVein(me)+"的隐藏五行属性——"+wx+HIG+"属性，被激活！\n"+NOR);
		CHANNEL_D->do_channel(this_object(), "jh", HIW+me->query("name")+HIW+"("+capitalize(me->query("id"))+")"+ThisVein(me)+"通脉成功后，激活"+wx+HIW+"属性！\n"+NOR,-1);
	}
	if (Level(me)>=4)
	{
		me->add("myVeins/LevelupDiscount",1);
		if (ExpBonus(me)) bonus=ExpBonus(me);
		if (BonusPeriod(me)) time=time()+3600*BonusPeriod(me);
		me->set_temp("apply/gainexp",(["bonus":bonus,"due":time]));
	}
}
void improveChance(object me,int flag)
{
	string vein;
	if (!objectp(GetFile(me))) return;
	vein=AcuPoint_list(me)[random(sizeof(AcuPoint_list(me)))];
	if (flag==1)
	{
		tell_object(me,HBCYN+HIW+"你有处穴道，内力导入，竟似泥牛入海。\n"+HIW+"对照经脉图(vein detail)，对此处穴道催发内力(vein enforce <穴道名>)，将会事半功倍。\n\n"+NOR);
		me->set_temp("myVeins/HidePoint",vein);
		show_vein(me);
		me->delete_temp("myVeins/HidePoint");
		return;
	}
	else if (flag==2)
	{
		me->set_temp("myVeins/HiddenPoint/thevein",vein);
		tell_object(me,HBCYN+HIW+"你此处穴道，内力导入，竟似泥牛入海。\n\n"+NOR);
		ANTIROBOT_D->mxpantirobot_ex(me,vein);
		return;
	}
}
int finish_through_vein(object me,string AccPoint)
{
	int * myThisVein=me->query("myVeins/"+ThisVein(me)+"/status"),flag,difficulty=7,exp,neili;
	string *color=({HIY,HIG,HIM,HIC,HIR,HIW});
	if (!me||!living(me))
	return 1;
	me->delete_temp("myVeins/HiddenPoint");
	if (!me->query_temp("myVeins/SuccHidePoint"))
	me->set("myVeins/"+ThisVein(me)+"/Chance",0);
	me->delete_temp("myVeins/SuccHidePoint");
	me->set("myVeins/"+ThisVein(me)+"/step",member_array(AccPoint,AcuPoint_list(me)));
	if (Level(me)>=2&&me->query_skill("jingmai",1)<VeinSkillLimit)
	me->improve_skill("jingmai",10+random(5*Level(me)*Level(me)));
	if (me->is_fighting())
	{
		if (random(100)>=69||wizardp(me))//三成可能走火,wiz肯定走火for test
		{
			myThisVein[member_array(AccPoint,AcuPoint_list(me))]=2;
			me->set("myVeins/"+ThisVein(me)+"/status",myThisVein);
			me->set("myVeins/"+ThisVein(me)+"/stepdetail",-1);
			me->set("myVeins/"+ThisVein(me)+"/NonBarrierPt",0);
			tell_object(me,RED+"战斗中让你精神不能集中，内力在"+ThisVein(me)+"间乱窜。\n"+NOR);
		}
		else
		{
			tell_object(me,"战斗中尝试强行通脉十分危险，你差一点就要走火入魔了。\n");
		}
		me->delete_temp("vein_through");
		return 1;
	}
	else//	正常结束
	{
		me->add("myVeins/"+ThisVein(me)+"/CurPt",1+random(2));
		message_vision("$N已将内力纳入"+AccPoint+"穴。\n",me);
		myThisVein[member_array(AccPoint,AcuPoint_list(me))]=1;
		me->set("myVeins/"+ThisVein(me)+"/status",myThisVein);
		if (me->query("myVeins/"+ThisVein(me)+"/CurPt")>DailyLimit(me)*2-random(100))
		{
			if (VeinDifficulty(me)) difficulty=VeinDifficulty(me);
			if (10+me->query("myVeins/"+ThisVein(me)+"/NonBarrierPt")*difficulty>random(100)&&time()>me->query("tianmuQuests/dashigu/kanli_effect"))
			{//走火
				myThisVein[member_array(AccPoint,AcuPoint_list(me))]=2;
				me->set("myVeins/"+ThisVein(me)+"/status",myThisVein);
				me->set("myVeins/"+ThisVein(me)+"/stepdetail",-1);
				me->set("myVeins/"+ThisVein(me)+"/NonBarrierPt",0);
				me->set("myVeins/"+ThisVein(me)+"/CurPt",me->query("myVeins/"+ThisVein(me)+"/CurPt")/2);
				tell_object(me,RED+"突然之间你的精神不能集中，内力在"+ThisVein(me)+"间乱窜。\n"+NOR);
			}
			else
			{
				myThisVein[member_array(AccPoint,AcuPoint_list(me))]=3;
				me->set("myVeins/"+ThisVein(me)+"/status",myThisVein);
				me->delete("myVeins/"+ThisVein(me)+"/CurPt");
				if (me->query("myVeins/"+ThisVein(me)+"/direction")==1)
					me->add("myVeins/"+ThisVein(me)+"/step",1);
				else
					me->add("myVeins/"+ThisVein(me)+"/step",-1);
				if ((me->query("myVeins/"+ThisVein(me)+"/direction")==1&&me->query("myVeins/"+ThisVein(me)+"/step")==sizeof(AcuPoint_list(me)))
				||(me->query("myVeins/"+ThisVein(me)+"/direction")==-1&&me->query("myVeins/"+ThisVein(me)+"/step")==-1))
				{
					flag=me->query("myVeins/"+ThisVein(me)+"/direction");
					me->delete("myVeins/"+ThisVein(me));
					if (flag==1)
					me->set("myVeins/"+ThisVein(me)+"/completed",2);
					if (flag==-1)
					me->set("myVeins/"+ThisVein(me)+"/completed",random(4)?1:3);
					tell_object(me,HIG+"恭喜，你的"+ThisVein(me)+"彻底贯通！\n"+NOR);
					show_vein(me);
					CHANNEL_D->do_channel(this_object(), "jh", HIW+me->query("name")+HIW+"("+capitalize(me->query("id"))+")经过不断尝试，"+ThisVein(me)+"通脉成功！\n"+NOR,-1);
					if (me->query("myVeins/level")<Level(me))
					me->set("myVeins/level",Level(me));
					EXTRA_REWARD(me,RecoverRequire(me));
					restore();
					if (!this_object()->query(ThisVein(me)+"/fastest/time"))
					{
						this_object()->set(ThisVein(me)+"/fastest/time",(time()-me->query("myVeins/"+ThisVein(me)+"/init_time")));
						this_object()->set(ThisVein(me)+"/fastest/player",me->query("id"));
						this_object()->set(ThisVein(me)+"/fastest/player_name",me->query("name"));
						CHANNEL_D->do_channel(this_object(), "jh", HIW+me->query("name")+HIW+"("+capitalize(me->query("id"))+")成为历史上"+ThisVein(me)+"通脉最快的高手！\n"+NOR,-1);
					}
					else if (time()-me->query("myVeins/"+ThisVein(me)+"/init_time")<this_object()->query(ThisVein(me)+"/fastest/time"))
					{
						this_object()->set(ThisVein(me)+"/fastest/time",(time()-me->query("myVeins/"+ThisVein(me)+"/init_time")));
						this_object()->set(ThisVein(me)+"/fastest/player",me->query("id"));
						this_object()->set(ThisVein(me)+"/fastest/player_name",me->query("name"));
						CHANNEL_D->do_channel(this_object(), "jh", HIW+me->query("name")+HIW+"("+capitalize(me->query("id"))+")成为历史上"+ThisVein(me)+"通脉最快的高手！\n"+NOR,-1);
					}
					if (!this_object()->query(ThisVein(me)+"/earliest/player"))
					{
						this_object()->set(ThisVein(me)+"/earliest/player",me->query("id"));
						this_object()->set(ThisVein(me)+"/earliest/player_name",me->query("name"));
						CHANNEL_D->do_channel(this_object(), "jh", HIW+me->query("name")+HIW+"("+capitalize(me->query("id"))+")成为历史上第一位打通"+ThisVein(me)+"的高手！\n"+NOR,-1);
						exp=1000000+Level(me)*200000;
						me->add("exp_dep",exp);
						tell_object(me,HIG+"你获得了"+chinese_number(exp)+"点修行经验的奖励。\n"+NOR);
						if (Level(me)>=2&&Level(me)<=7)
						me->set_title(({TITLE_QUEST1,TITLE_QUEST2,TITLE_QUEST3,TITLE_QUEST4,TITLE_QUEST5,TITLE_QUEST6,TITLE_QUEST7,TITLE_QUEST8,TITLE_QUEST9,TITLE_QUEST10}), color[Level(me)-2]+"翩若惊鸿 婉若游龙"+NOR, ({"翩若惊鸿 婉若游龙"}));
					}
					me->delete_temp("vein_through");
					save();
					return 1;
				}
				me->add("myVeins/"+ThisVein(me)+"/NonBarrierPt",1);
				if (Purify(me))
				{
					neili=Purify(me);
					me->add("exercised_neili",neili);
					tell_object(me,HIW+"你的内息在"+ThisVein(me)+"内涤荡，共有"+chinese_number(neili)+"点内力变得更加精纯。\n"+NOR);
				}
				if (PureNeili(me))
				{
					neili=PureNeili(me);
					me->add("exercised_neili",neili);
					me->add("max_neili",neili);
					tell_object(me,HIW+"你获得了"+chinese_number(neili)+"点精纯的内力。\n"+NOR);
				}
				tell_object(me,HIG+"你"+ThisVein(me)+"上"+AccPoint+"穴已经充盈，你可以尝试下一个穴道"+HIC+NextAccPoint(me,AccPoint)+"穴"+HIG+"了。\n"+NOR);
			}
			me->delete_temp("vein_through");
			return 1;
		}
		me->delete_temp("vein_through");
		return 1;
	}
}
int process_through_vein(object me,string AccPoint)
{
	mixed *tm=localtime(time());
    string date=sprintf("%d-%d-%d", tm[5], tm[4]+1, tm[3]);
	int exp,neili;
	if (me->query("myVeins/attempts")>=1000)
	{
		tell_object(me,"过多尝试通脉次数，有害无益。今天就到此为止吧。\n");
		return 1;
	}
	if (me->query("neili")<me->query("max_neili")*21/20||me->query("max_neili")<10000)
	{
		tell_object(me,"你现在内力不足，强行通脉，有害无益。\n");
		return 1;
	}
	if (ExpConsume(me)>0&&me->query("exp_dep")<ExpConsume(me))
	{
		tell_object(me,"你现在修行经验不足，无法强行通脉！\n");
		return 1;
	}
	if (me->query("myVeins/"+ThisVein(me)+"/direction")==1)
	message_vision(HIG+"$N尝试将内力灌注"+AccPoint+"穴，在"+ThisVein(me)+"间运转。\n"+NOR,me);
	if (me->query("myVeins/"+ThisVein(me)+"/direction")==-1)
	message_vision(HIW+"$N尝试将内力灌注"+AccPoint+"穴，在"+ThisVein(me)+"间运转。\n"+NOR,me);
	//开始通脉
	me->start_busy(Period(me));
	me->set_temp("vein_through",GetFile(me));
	me->set("myVeins/date",date);
	me->add("myVeins/attempts",1);
	exp=ExpConsume(me)+random(ExpConsume(me)/4);
	me->add("exp_dep",-(exp));
	neili=me->query("max_neili")/20+random(200);
	me->add("neili",-(neili));
	tell_object(me,"你此处冲穴消耗了"+chinese_number(neili)+"点内力。");
	if (exp) tell_object(me,chinese_number(exp)+"点修行经验。");
	tell_object(me,"\n");
	if (Period(me)>=ResponseTime)
	{
		if (!random(50))
		improveChance(me,1);
		else if (!random(300))
		improveChance(me,2);
	}
	call_out("finish_through_vein",Period(me),me,AccPoint);
	return 1;
}
int enforce_vein(object me,string AccPoint)
{
	if (!objectp(GetFile(me)))
	{
		tell_object(me,"你必须设定一个目标经脉。vein -h获得帮助。\n");
		return 1;
	}
	if (me->query("myVeins/"+ThisVein(me)+"/completed"))
	{
		tell_object(me,"你的"+ThisVein(me)+"已经贯通成功了。\n");
		return 1;
	}
	message_vision(HBMAG+HIC+"$N开始将内力强行注入"+AccPoint+"穴。\n"NOR,me);
	if (me->query_temp("myVeins/HiddenPoint/vein")!=AccPoint&&me->query_temp("myVeins/HiddenPoint/thevein")!=AccPoint)
	{
		tell_object(me,"胡乱冲穴，你的经脉略有损伤，好在并不严重。\n");
		me->add("myVeins/"+ThisVein(me)+"/CurPt",-(1+random(2)));
		me->add("myVeins/"+ThisVein(me)+"/NonBarrierPt",1);
		me->delete("myVeins/"+ThisVein(me)+"/Chance");
	}
	else
	{
		me->add("myVeins/"+ThisVein(me)+"/CurPt",(8+random(8)));
		tell_object(me,HIG+"你用内力冲击"+AccPoint+"穴成功，经脉运行更顺畅了一些。\n"+NOR);
		if (me->query_temp("myVeins/HiddenPoint/thevein")==AccPoint)
		me->add("myVeins/"+ThisVein(me)+"/CurPt",20);
		me->set_temp("myVeins/SuccHidePoint",1);
		me->set("myVeins/"+ThisVein(me)+"/Chance",1);
	}
	me->delete_temp("myVeins/HiddenPoint");
	return 1;
}
int through_vein(object me,string AccPoint)
{
	int * myThisVein,*LvLimit=({30,60,80,100,115,130,140});
	if (me->is_busy()||me->is_fighting())
	{
		tell_object(me,"你现在正忙着呢。\n");
		return 1;
	}
	if (me->query_temp("vein_through"))
	{
		tell_object(me,"你正在运转内力贯通经脉中。\n");
		return 1;
	}
	if (!objectp(GetFile(me)))
	{
		tell_object(me,"你必须设定一个目标经脉。vein -h获得帮助。\n");
		return 1;
	}
	myThisVein=init_vein(me);
	if (me->query("myVeins/"+ThisVein(me)+"/stepdetail")==-1)
	{
		tell_object(me,"你的真气在"+ThisVein(me)+"上"+RED+AcuPoint_list(me)[me->query("myVeins/"+ThisVein(me)+"/step")]+"穴"+NOR+"运行受阻，还是尽快想办法把走火的真气理顺吧。\n");
		return 1;
	}
	if (me->query("myVeins/"+ThisVein(me)+"/completed"))
	{
		tell_object(me,"你的"+ThisVein(me)+"已经贯通成功了。\n");
		return 1;
	}
	if (me->query("level")<LvLimit[Level(me)-1])
	{
		tell_object(me,"你的目标经脉"+ThisVein(me)+"是"+Level(me)+"层经脉，必须在人物等级达到"+chinese_number(LvLimit[Level(me)-1])+"级后，才能开始尝试。\n");
		return 1;
	}
	if (Level(me)-me->query("myVeins/level")>=2)
	{
		tell_object(me,"你的目标经脉"+ThisVein(me)+"是"+Level(me)+"层经脉，必须有前一层的经脉贯通为基础，才能尝试。\n");
		return 1;
	}
	if (myThisVein[0]==0&&myThisVein[sizeof(myThisVein)-1]==0)//未开始通脉
	{
		if (Level(me)>=2&&!me->query("myVeins/"+ThisVein(me)+"/direction"))
		me->set("myVeins/"+ThisVein(me)+"/init_time",time());
		if (AccPoint!=AcuPoint_list(me)[0]&&AccPoint!=AcuPoint_list(me)[sizeof(AcuPoint_list(me))-1])//不是起始也不是逆练
		{
			tell_object(me,WHT+"你只能从【"+AcuPoint_list(me)[0]+"穴】开始正向通脉，或者从【"+AcuPoint_list(me)[sizeof(AcuPoint_list(me))-1]+"穴】逆向通脉。\n"+NOR);
			return 1;
		}
		else if (AccPoint==AcuPoint_list(me)[0])//正向开始
		{
			me->set("myVeins/"+ThisVein(me)+"/direction",1);
		}
		else
		{
			me->set("myVeins/"+ThisVein(me)+"/direction",-1);
		}
		process_through_vein(me,AccPoint);
		return 1;
	}
	else //已开始
	{
		if (AccPoint!=AcuPoint_list(me)[me->query("myVeins/"+ThisVein(me)+"/step")])
		{
			tell_object(me,"现在你只能尝试往"+RED+AcuPoint_list(me)[me->query("myVeins/"+ThisVein(me)+"/step")]+"穴"+NOR+"里灌注内力。\n");
			return 1;
		}
		process_through_vein(me,AccPoint);
		return 1;
	}
}

int RecoverAccPoint(object me)
{
	int * myThisVein;
	object *inv,obj;
	if (!objectp(GetFile(me)))
	{
		tell_object(me,"你必须设定一个目标经脉。vein -h获得帮助。\n");
		return 1;
	}
	myThisVein=me->query("myVeins/"+ThisVein(me)+"/status");
	if (me->query("myVeins/"+ThisVein(me)+"/stepdetail")!=-1)
	{
		tell_object(me,"你的"+ThisVein(me)+"毫无滞涨。\n");
		return 0;
	}
	inv=all_inventory(me);
	for (int i=0;i<sizeof(inv);i++)
	if (inv[i]->RecoverRequire()==RecoverRequire(me)&&inv->query("veinRecover"))
	obj=inv[i];
	if (!obj)
	{
		tell_object(me,"恢复受损经脉需要一定的药物来支持。\n");
		return 1;
	}
	myThisVein[me->query("myVeins/"+ThisVein(me)+"/step")]=1;
	me->set("myVeins/"+ThisVein(me)+"/status",myThisVein);
	me->delete("myVeins/"+ThisVein(me)+"/stepdetail");
	tell_object(me,"你消耗了一"+obj->query("unit")+obj->query("name")+"后，成功疏导了"+ThisVein(me)+"里乱窜的真气。\n");
	destruct(obj);
	return 1;
}

int main(object me,string arg)
{
	string action,accpoint,pastSet;
	object target;
	mapping transfile=transfile();
	mixed *tm=localtime(time());
    string date=sprintf("%d-%d-%d", tm[5], tm[4]+1, tm[3]);
	if (me->query("myVeins/date")!=date)
    {
		me->delete("myVeins/date");
		me->delete("myVeins/attempts");
    }
	if (!arg||arg=="-h")
	{
		tell_object(me,"手太阴肺经、手阳明大肠经、足阳明胃经、足太阴脾经、手少阴心经、
手太阳小肠经、足太阳膀胱经、足少阴肾经、手厥阴心包经、手少阳三
焦经、足少阳胆经、足厥阴肝经合称十二正经，而任脉、督脉、冲脉、
带脉、阴跷脉、阳跷脉、阴维脉和阳维脉被称为奇经八脉。可用内力贯
通经脉，贯通之后，将有益于自身修行。具体请用命令vein <经脉名>
来了解。vein detail 现实目标经脉的通脉情况，vein through <穴道>
尝试贯通某经脉，贯通某经脉的命令请注意穴道的正确中文名，用vein 
detail 获得。vein overall 获得整体通脉情况。vein recover尝试修
复受损经脉。set vein <经脉名>来设定目标经脉。\n");
		return 1;
	}
	if (transfile[arg]&&file_size(BASICVEIN+transfile[arg]+".c")>0&&target=load_object(BASICVEIN+transfile[arg]+".c"))
	{
		action=HIC+"【"+arg+"】"+NOR+"："+target->benefit();
		pastSet=me->query("env/vein");
		me->set("env/vein",arg);
		show_vein(me);
		me->set("env/vein",pastSet);
		tell_object(me,action);
		return 1;
	}
	else
	{
		if ((sscanf(arg, "%s %s", action, accpoint)== 2)&&action=="through")//通脉
		through_vein(me,accpoint);
		else if ((sscanf(arg, "%s %s", action, accpoint)== 2)&&action=="enforce")//冲穴
		enforce_vein(me,accpoint);
		else if (arg=="recover")//解除走火状态
		RecoverAccPoint(me);
		else if (arg=="detail")//显示
		show_vein(me);
		else if (arg=="overall")
		overall_vein(me);
		else if (member_array(arg,keys(transfile))==-1)
		tell_object(me,"『"+arg+"』不是任何一条经脉，也不是vein命令的一个参数。\n");
		else
		tell_object(me,arg+"尚未开放，请耐心等待。\n");
		return 1;
	}
}