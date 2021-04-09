/*
* /cmds/skill/createskill.c
*
* write by maxim@nju_fengxue
* mail address is to see: maxim jiang of bbs.nju.edu.cn
* 1997.12.21
*
* vast@pkuxkx 修改并做部分注释 2003.3
* deWolf(vax)@pkuxkx<deWolf_maTri_X@msn.com> 修改并加入自动领悟perform 2005.11
*
*/

#include <ansi.h>

inherit F_CLEAN_UP;

#define QUOTE_MARK "\""
#define HEADER_END 16
#define SPE_PRA_LINES 34

//开放的自创武功基本类型
 string *valid_types = ({
//基本空手功夫
	"unarmed",
    "finger",
    "hand",
    "cuff",
    "claw",
    "strike",
//基本兵器功夫
	"sword",
	"blade",
	"staff",
	"spear", //"hammer", 锤子功夫太少了, by deWolf
	"whip",
});

//禁用名称列表,请在发现问题后及时添加
string *banned_name=({
	"  ", // 空名称是禁止的
});

mapping spe_skill = ([
    "action" : ({" "}),
    "force" : ({"10"}),
    "dodge" : ({"10"}),
    "parry": ({"10"}),
    "damage_type" : ({"瘀伤"}),
    "damage_type2" : ({"瘀伤"}),
    "lvl" : ({"10"}),
    "skill_name" : ({"横空出世"}),
    "skill_total_num" : ({"0"}),
    "skill_en_name" : ({" "}),
    "skill_ch_name" : ({" "}),
]);

mapping performs = ([
	"name" : ({"chan"}),
    "usage" : ({" "}),
    "action" : ({" "}),
	"ch_name" :  ({"无"}),
	"need_level" : ({"50"}),
	"amount" : ({"5"}),
	"jingli_cost" : ({"10"}),
	"neili_cost" : ({"100"}),
]);

int redo_action;
int spe_skillnum;

string spe_skill_name;
//基本技能名称
string spe_skill_basename;

int loge(int exp);
int hasquote(string targets);
int	check_legal_id(string id);
int	check_legal_name(string name);
int	check_action_name(string yn);
int	check_legal_basename(string name);
void	skill_init_header(string skill_en_name,string skill_ch_name);
void	get_zhaoshi_ch_name(string yn, object ob);
void	get_zhaoshi_ch_action(string yn, object ob);
int	check_skillnum_exist(object me,string skill_en_name,int skill_num);
void	modify_skill_param(mapping spe_skill);
void	finish_write_skill(object ob);
int	check_owner_skill(object me,string skill_en_name);
string	get_header_skillchname(string file);
string	get_header_skillbasename(string file);

void get_perform_zhaoshi_ch_name(string yn, object ob);
void get_perform_zhaoshi_ch_action(string yn, object ob);
void finish_write_perform(object ob);

int main(object me, string arg)
{
//1. exp limit,so skill lvl is according to the exp,if exp low,lvl is low
//2. first create the unarmed as a test,and the same will be sword,blade
//etc....
//3. arg is the skillname player want to create
//all create skill will be write as a log file
//so wizard can know what is the player's skill
//指令格式：createskill foliage_unarmed 招式数
//1)check if the exp is enough to the 招式数
//2)check if the 招式 have been enough
//3)ask player to input the skill_spe_name
//4)ask player to input the action
//so let's do it!

int skill_num, skill_num_result, i, flag;
string *skillmaxim;
string skill_en_name, skill_ch_name, file, cur_translation;
string skill_base_name;
object env=environment(me);

spe_skill_basename="";
spe_skill_name="";
spe_skillnum=0;
redo_action = 0;

//判断输入的命令格式是否正确
if(!arg || sscanf(arg, "%s %s %s %d", skill_base_name,skill_en_name,skill_ch_name,skill_num)!=4)
    return notify_fail("指令格式：createskill <武功基本技能> <武功英文名字> <武功中文名字> <第几招>\n");
/*///// 简化指令，将判断条件合并上去了。 deWolf  2005.11
*if( sscanf(arg, "%s %s %s %d", skill_base_name,skill_en_name,skill_ch_name,skill_num)!=4)
*    return notify_fail("指令格式：createskill <武功基本技能> <武功英文名字> <武功中文名字> <第几招>\n");
*/

if(!env->query("createskill_room"))
	return notify_fail("只有在侠客岛或自创帮派的闭关室中，清心寡欲，忘却俗事才能自创武功!\n");

//将玩家输入的英文名称转化为小写
skill_en_name = lower_case(skill_en_name);

spe_skill_basename = skill_base_name;

//检查玩家输入的武功基本技能是否允许自创
if(check_legal_basename(skill_base_name)==0)
    return notify_fail("你输入的基本技能不存在，或者暂时不能自创这种武功。\n");

//检查玩家是否会这种基本技能
if(me->query_skill(skill_base_name, 1) < 1)
    return notify_fail("你并不熟悉这种基本功夫啊，怎么创得出特殊功夫的呢？\n");

//检查玩家输入的武功英文名字是否符合条件(2-12个英文字母)
if(check_legal_id(skill_en_name)==0)
	return 1;

//检查玩家输入的武功英文名字是否符合条件(1-6个汉字)
if(check_legal_name(skill_ch_name)==0)
	return 1;

//检查招数
if(skill_num > 9)
	return notify_fail("自创武功最多九招。\n");
if(skill_num < 1)
	return notify_fail("你需要从第一招开始创建。\n");

//自动将武功的英文名称改为标准格式
spe_skill_name=skill_en_name+"-"+skill_base_name;
spe_skill["skill_en_name"]=spe_skill_name+".c";
spe_skill["skill_ch_name"]=skill_ch_name;

/// deWolf : 
cur_translation = CHINESE_D->chinese(spe_skill_name);
if (cur_translation != spe_skill_name && cur_translation != skill_ch_name) 
{
	// translation collision
	return notify_fail("你输入的中文武功名称和所选的英文武功代号与现有功夫相冲突。\n");
};

// 玩家不得中途改变功夫 id 和 名称
if( skill_num!=1 && get_header_skillchname(spe_skill["skill_en_name"])!=skill_ch_name)
    return notify_fail("你输入的中文武功名称和所选的英文武功代号有矛盾。\n");

if( skill_num!=1 && get_header_skillbasename(spe_skill["skill_en_name"])!=skill_base_name)
    return notify_fail("你输入的基本技能名和所选的英文武功代号有矛盾。\n");

//每个玩家最多创建3种特殊功夫
if(mapp(me->query("skillmaxim")) && sizeof(skillmaxim=keys(me->query("skillmaxim/"))) >= 3 )
{
	for (i = sizeof(keys(me->query("skillmaxim/"))) - 1; i >= 0; i--)
		if (skill_base_name == skillmaxim[i])
			flag = 1;
	if (flag != 1)
    	return notify_fail("你最多只能创建三种高级功夫。\n");
}

switch(check_owner_skill(me,spe_skill["skill_en_name"]))
{
	case 2:
		return notify_fail("这个功夫在江湖中已经存在，你无法再有创新。\n");
	case 0: //this is right
		break;
	case 1:
		return notify_fail("你目前只能针对这个基本技能创建一个功夫。\n");
	default:
		return notify_fail("请和巫师联系，所创功夫不对。\n");
}

//经验值至少需要5M，此值应根据不同的情况修改
if((int)me->query("combat_exp") < 5000000)
       return notify_fail("你的经验值不够。\n");

//武林声望至少需要10w，此值应根据不同的情况修改
if((int)me->query("repute") < 100000)
       return notify_fail("你的武林声望不够。\n");

//5M以上每多1M经验，可以多创一招
if((int)me->query("combat_exp") < (skill_num-1) * 1000000 + 5000000)
       return notify_fail("你的经验值还不够。\n");

//10w以上每多5w声望，可以多创一招
if((int)me->query("repute") < (skill_num-1) * 50000 + 100000)
       return notify_fail("你的武林声望还不够。\n");

//if (mapp(me->query("skillmaxim")))
//if(me->query("combat_exp") < (sizeof(keys(me->query("skillmaxim"))) + 1) * 5000000)
//	return notify_fail("你的经验不够创建新的功夫。\n");

//现有的武功必须练到(50*招式)的级别才能继续创下一招
if((int)me->query_skill(spe_skill_name, 1)!=0
     && (int)me->query_skill(spe_skill_name, 1) < (skill_num-1)*50)
       return notify_fail("你已经有的招式还不够熟练，先提高它们，然后再想新招吧。\n");

file=read_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]));
if(!file)
{
	if( mapp( me->query("skillmaxim") )
	&& me->query("combat_exp") < (sizeof(keys(me->query("skillmaxim"))) + 1) * 5000000)
		return notify_fail("你的经验不够，不能创建新的武功。\n");
	if(mapp( me->query("skillmaxim") )
	&& me->query("repute")< (sizeof(keys(me->query("skillmaxim"))) + 1) * 100000)
		return notify_fail("你的声望不够，不能创建新的武功。\n");
}

skill_num_result = check_skillnum_exist(me,spe_skill["skill_en_name"],skill_num);

if(skill_num_result > 1)
	write("\r请给招式起个汉语名字(不要此时断线，否则永远无法再正确创建):");
else if(skill_num_result==1)
{
	//第一次创建
	write("你现在开始创建"+skill_ch_name+"("+spe_skill_name+")"+"的第一招.\n");
	write("\r请给招式起个汉语名字(不要此时断线，否则永远无法再正确创建):");
}
else if(skill_num_result==-1)
{
	return notify_fail("这一招已经创建好了。\n");
}
else if(skill_num_result==-2)
{
	return notify_fail("上一招尚未创建，请逐招创建功夫。\n");
}
else
	return notify_fail("你所要创建功夫的招式数有误。\n");

spe_skillnum=skill_num;

if(skill_num==1)
{
	rm(PLAYER_SKILL_D(spe_skill["skill_en_name"]));
	skill_init_header(spe_skill["skill_en_name"],skill_ch_name);
}

// 准备输入招式
input_to( (: get_zhaoshi_ch_name :), this_player() );

return 1;
}

//若武功文件已经存在，此函数返回这种自创武功的中文名，否则返回0
string get_header_skillchname(string file)
{
	string result, content, *list;
	
	//
	content = 
	
	content = read_file(PLAYER_SKILL_D(file));
	if((int)content == 0)
		return 0;
	list = explode(content, "\n");
	if(sizeof(list) < 8)
		return 0;
	else
	{
		if(sscanf(list[7],"// %s",result)!=1)
			return 0;
		else
			return result;
	}
	return 0;
}

//若武功文件已经存在，此函数返回这种自创武功的基本功夫的英文名，否则返回0
string get_header_skillbasename(string file)
{
string result;

string content,*list;
content=read_file(PLAYER_SKILL_D(file));
if((int)content==0)
 return 0;
list = explode(content, "\n");
if(sizeof(list) < 7)
 return 0;
else {
    if(sscanf(list[6],"// %s",result)!=1)
               return 0;
    else
         return result;

  }
return 0;
}

//创建功夫文件头部信息
void skill_init_header(string skill_en_name,string skill_ch_name)
{
string header;

object me;
int i;
string result;

result="";
me=this_player();
header="";

header="// THIS IS PLAYER'S OWN SKILL (write by maxim@nju_fengxue)\n";
header+="// "+geteuid(me)+"\n";                //玩家id
header+="// "+me->query("name")+"\n";          //玩家中文名
header+="// "+me->query("title")+"\n";         //玩家title
header+="// "+me->query("combat_exp")+"\n";    //玩家exp
header+="// "+me->query("gender")+"\n";        //玩家性别
header+="// "+spe_skill_basename+"\n";         //基本功夫名称，list[6]
header+="// "+spe_skill["skill_ch_name"]+"\n"; //功夫中文名称，list[7]

//here seem bug ...not check
//
for(i=10;i<15;i++)
    header+="\n";
write_file(PLAYER_SKILL_D(skill_en_name),header);
write_file(PLAYER_SKILL_D(skill_en_name),"inherit SKILL;\n");
write_file(PLAYER_SKILL_D(skill_en_name),"\n////////////////////////////////\n");

//here add the first skill string
write_file(PLAYER_SKILL_D(skill_en_name),"\nmapping *action = ({\n");

write_file(PLAYER_SKILL_D(skill_en_name),"\n"+"// ZHAOSHI : 0");
//this is only a id check of it,no other use
//but is important
}

//接收玩家输入的中文功夫名称
void get_zhaoshi_ch_name(string yn, object ob)
{
if( yn=="" )
{
	write("\r请给招式起个名字(不要此时断线，否则永远无法再正确创建):");
	input_to( (: get_zhaoshi_ch_name :), ob );
	return;
}
if( !check_legal_name(yn) )
{
	write("招式名称：");
	input_to( (: get_zhaoshi_ch_name :), ob );
	return;
}

spe_skill["skill_name"]=yn;

write(HIR"\n描述中不能出现控制符，不然将删除!\n"NOR);
write("\n想象一下你和敌人的打斗，\n");
write("请看以下例句：（“敌人”，“你”，“某部位”，“武器”带有普遍性）\n");
write("\n你前腿踢出，后腿脚尖点地，一式「横空出世」，二掌直出，攻向敌人的上中下三路\n");
write("你纵身一跃，手中武器一招「金光泻地」对准敌人的某部位斜斜刺出一剑\n\n");
write("提示：必须要有"HIY"你"NOR"和"HIY"敌人"NOR"字样出现！而且句末不要带句号\n");
write("\n请输入你的招式描述：\n");

input_to("get_zhaoshi_ch_action", 1, ob);
}

//接收玩家输入的中文功夫招式
void get_zhaoshi_ch_action(string yn, object ob)
{
if(check_action_name(yn)==0)
{
	input_to( (: get_zhaoshi_ch_action :), ob );
	return;
}
if(CHINESE_D->check_length(yn) > 160)
{
	write(HIR"描述太长。\n"NOR);
	input_to( (: get_zhaoshi_ch_action :), ob );
	return;
}

if(hasquote(yn)>=0)
{
	write(HIR"你的武功描述不能用控制字元。\n"NOR);
	input_to( (: get_zhaoshi_ch_action :), ob );
	return;
}

if(CHINESE_D->check_control(yn))
{
	write(HIR"你的武功描述不能用控制字元。\n"NOR);
	input_to( (: get_zhaoshi_ch_action :), ob );
	return;
}
if( yn=="" )
{
	write(HIR"\n描述中不能出现控制符，不然将删除!\n"NOR);
	write("\n想象一下你和敌人的打斗，\n");
	write("请看以下例句：（“敌人”，“你”，“某部位”，“武器”带有普遍性）\n");
	write("\n你前腿踢出，后腿脚尖点地，一式「横空出世」，二掌直出，攻向敌人的上中下三路\n");
	write("你纵身一跃，手中武器一招「金光泻地」对准敌人的某部位斜斜刺出一剑\n\n");
	write("提示：必须要有"HIY"你"NOR"和"HIY"敌人"NOR"字样出现！而且句末不要带句号\n");
	write("\n请输入你的招式描述：\n");
	
	input_to( (: get_zhaoshi_ch_action :), ob );
	return;
}

spe_skill["action"]=yn;

finish_write_skill(ob);
ob->set("skillmaxim/"+spe_skill_basename,1);
if(spe_skillnum==1)
{
	ob->set_skill(spe_skill_name,1);

	// 记录日志
	log_file("CREATESKILL",
		sprintf("%s(%s) %s(%s): %d (%s)\n",
				ob->query("name"),
				ob->query("id"),
				spe_skill["skill_ch_name"],
				spe_skill_name,
				spe_skillnum,
				ctime(time()))
	);
	
	//中文翻译
	CHINESE_D->add_translate(spe_skill_name,spe_skill["skill_ch_name"]);
}
}

//first header
//then action
//then 35 lines of practice or other thing

//here should determain the file is: over wirte or appetine something
void finish_write_skill(object ob)
{
int mystr, mycon, mydex;

string action;
string file,*list;
string content;
int before_skillnum,i, exp_factor;
string *list2;
string header2;
string result;

header2="";
result="";
content="";
action="";
exp_factor=0;

switch(spe_skill_basename)
{
	// 扩展伤害为二选一的随机伤害，deWolf 2005.11
	// pkuxkx 有效伤害： 割伤，刺伤，瘀伤，内伤，点穴，抓伤，反弹伤
	case "unarmed":
		spe_skill["damage_type"]="瘀伤";
		spe_skill["damage_type2"]="内伤";
		break;	
	case "finger":
		spe_skill["damage_type"]="点穴";
		spe_skill["damage_type2"]="刺伤";
		break;
	case "claw":
		spe_skill["damage_type"]="瘀伤";
		spe_skill["damage_type2"]="抓伤";
		break;
	case "sword":
	case "spear":
		spe_skill["damage_type"]="割伤";
		spe_skill["damage_type2"]="刺伤";
		break;	
	case "blade":
		spe_skill["damage_type"]="割伤";
		spe_skill["damage_type2"]="割伤";
		break;	
	default:
		spe_skill["damage_type"]="瘀伤";
		spe_skill["damage_type2"]="内伤";
		break;
}

/// deWolf : 从 5M附近开始，exp每增加 2.71828倍，伤害+15+random(15), 在100M 可望+45+ random(45)
exp_factor = (loge((int)this_player()->query("combat_exp"))-loge(5000000))*30;
exp_factor = (exp_factor + random(exp_factor))/2;

spe_skill["force"]	=exp_factor+20+spe_skillnum*25;
spe_skill["damage"]	=exp_factor+5+spe_skillnum*15;
spe_skill["parry"]	=exp_factor-10+spe_skillnum*10;
spe_skill["dodge"]	=exp_factor-10+spe_skillnum*3;

spe_skill["lvl"]=spe_skillnum-1;

/// deWolf : 空手武功加强force,damage,减少 dodge ,parry,  目的是弥补兵器damage上的缺陷
if(!(spe_skill_basename=="sword"
         || spe_skill_basename=="blade"
         || spe_skill_basename=="staff"
         || spe_skill_basename=="spear"
         || spe_skill_basename=="whip"))
{
	spe_skill["force"]+=30+random(60);
	spe_skill["damage"]+=20+random(20);
	spe_skill["dodge"]-=5+random(10);
	spe_skill["parry"]-=10+random(30);
}

/// deWolf : 修正伤害数据，补足玩家属性弱项，削弱强项。
modify_skill_param(spe_skill);

//here replace 你 and 敌人 to ....
if(CHINESE_D->check_length(spe_skill["action"]) > 160)
{
	write(HIR"描述太长。\n"NOR);
	return;
}

if(CHINESE_D->check_control(spe_skill["action"]))
{
	write(HIR"你的武功描述不能用控制字元。\n"NOR);
	return;
}

if(hasquote(spe_skill["action"])>=0)
{
	write(HIR"你的武功描述不能用控制字元。\n"NOR);
	return;
}

spe_skill["action"]= replace_string(spe_skill["action"], "'"," ");
spe_skill["action"]= replace_string(spe_skill["action"], "你","$N");
spe_skill["action"]= replace_string(spe_skill["action"], "敌人","$n");
spe_skill["action"]= replace_string(spe_skill["action"], "某部位","$l");

if(spe_skill_basename=="sword"
         || spe_skill_basename=="blade"
         || spe_skill_basename=="staff"
         || spe_skill_basename=="spear"
         || spe_skill_basename=="whip")
	spe_skill["action"]= replace_string(spe_skill["action"], "武器","$w");

action="\n([\n"
	+QUOTE_MARK+"action"+QUOTE_MARK+" : "+QUOTE_MARK+spe_skill["action"]+QUOTE_MARK+",\n"
	+QUOTE_MARK+"force"+QUOTE_MARK+" : "+ spe_skill["force"]+",\n"
	+QUOTE_MARK+"damage"+QUOTE_MARK+" : "+ spe_skill["damage"]+",\n"
	+QUOTE_MARK+"dodge"+QUOTE_MARK+" : "+ spe_skill["dodge"]+",\n"
	+QUOTE_MARK+"parry"+QUOTE_MARK+" : "+ spe_skill["parry"]+",\n"
	+QUOTE_MARK+"damage_type"+QUOTE_MARK+" : random(2)?"+QUOTE_MARK+spe_skill["damage_type"]
			+QUOTE_MARK+":"+QUOTE_MARK+spe_skill["damage_type2"]+QUOTE_MARK+",\n"
	+QUOTE_MARK+"lvl"+QUOTE_MARK+" : "+spe_skill["lvl"]+",\n"
	+QUOTE_MARK+"skill_name"+QUOTE_MARK+" : "+QUOTE_MARK+spe_skill["skill_name"]+QUOTE_MARK+"\n]),"
	+"\n});"
	+"\n// ZHAOSHI :"+spe_skillnum;

file=read_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]));
if((int)file!=0)
    list = explode(file, "\n");

////////////////////////////////////////////////////////////////////
 //here replace the string SKILL_CH_NAME and SKILL_EN_NAME
if(spe_skill_basename=="unarmed"
         || spe_skill_basename=="strike"
         || spe_skill_basename=="finger"
         || spe_skill_basename=="hand"
         || spe_skill_basename=="cuff"
         || spe_skill_basename=="claw")
    header2=read_file(SKILL_MODEL_UNARMED);
else if(spe_skill_basename=="sword"
         || spe_skill_basename=="blade"
         || spe_skill_basename=="staff"
         || spe_skill_basename=="hammer"
         || spe_skill_basename=="whip")
    header2=read_file(SKILL_MODEL_WEAPON);
else
    header2=read_file(SKILL_MODEL_DEFAULT);

list2 = explode(header2, "\n");
for(i=0;i < sizeof(list2);i++)
{
//this is not the arg!!!
//spe_skill_name!=skill_en_name...
	list2[i]= replace_string(list2[i], "SKILL_EN_NAME",QUOTE_MARK+spe_skill_name+QUOTE_MARK );
	list2[i]= replace_string(list2[i], "SKILL_CH_NAME",QUOTE_MARK+spe_skill["skill_ch_name"]+QUOTE_MARK );
	list2[i]= replace_string(list2[i], "SKILL_BASE_NAME",QUOTE_MARK+spe_skill_basename+QUOTE_MARK );
}
//result contain the practice and exert information
for(i=0;i < sizeof(list2);i++)
{
	result+=list2[i]+"\n";
}
///////////////////////////////////////////////
//now only a few be created,so the end is zhaoshi : 0
if(spe_skillnum==1)
{
	if(sscanf(list[sizeof(list)-1],"// ZHAOSHI :%d",before_skillnum)!=1)
	{
		write("可能出现异常了，如不能解决请通知巫师。\n");
		return;
	}
}
else
{
	if(sscanf(list[sizeof(list)-1-SPE_PRA_LINES],"// ZHAOSHI :%d",before_skillnum)!=1)
	{
		write("可能出现异常了，如不能解决可通知巫师。\n");
		return;
	}
}
//this will be excuted if total get correctly
{
	//remove the old action
	if( before_skillnum==spe_skillnum)
	{
		//  write("\nremove the old action\n");
		for(i=0;i < sizeof(list)-13-SPE_PRA_LINES;i++)
			content+=list[i]+"\n";
		content+=action;
		rm(PLAYER_SKILL_D(spe_skill["skill_en_name"]));
		write_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]),content);
	}
	else
	{
		//add a new action
		//if it is a new create first
		//then should be:
		rm(PLAYER_SKILL_D(spe_skill["skill_en_name"]));
		if(spe_skillnum!=1)
		{
			for(i=0;i < sizeof(list)-SPE_PRA_LINES-2;i++)
				content+=list[i]+"\n";
			//      write("see list :"+sizeof(list));
			content+="// ZHAOSHI :"+(string)before_skillnum+"\n";
			content+=action;
			write_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]),content);
			//    write("\nadd a  action1\n");
		}
		else if(spe_skillnum==1)
		{
			for(i=0;i < HEADER_END+3;i++)
				content+=list[i]+"\n";
			content+="// ZHAOSHI :"+(string)before_skillnum+"\n";
			content+=action;
			write_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]),content);
			//     write("\nadd a  action2\n");
		}
	
	}
	//at last wirte the practice and other exert information
	write_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]),"\n"+result);
}
children(PLAYER_SKILL_D(spe_skill["skill_en_name"]))->clean_up();

write("「"+spe_skill["skill_ch_name"]+"」的招式「"+HIY+spe_skill["skill_name"]+NOR+"」创建完成。\n");

if (!redo_action && spe_skillnum%3 == 0 && spe_skillnum>0)
{
	// 第一次创建 3 6 9招
	
	if (this_player()->query("int")
			+this_player()->query("kar")/2
			-this_player()->query("per")/2 > random(100))
	{
		// 漂亮的领悟概率低，grin
		
		if (spe_skillnum == 9 && random(10)>4)
		{
			return;
		}
		// 最后一招再降低一半概率
		mystr = this_player()->query_str();
		mycon = this_player()->query_con();
		mydex = this_player()->query_dex();	
		
		if (mystr>=mycon && mystr>=mydex)
		{
			performs["name"] = "critical";
			performs["usage"] = "一击重创敌人";
		}
		else if (mycon>=mystr && mycon>=mydex)
		{
			performs["name"] = "chan";
			performs["usage"] = "使敌人忙乱";
		}
		else
		{
			performs["name"] = "multiple";
			performs["usage"] = "连续打击敌人";
		}
		
		if (spe_skillnum==3)
		{
			performs["need_level"]="50";
			performs["jingli_cost"]="20";
			performs["neili_cost"]="80";
			if (performs["name"] == "critical")
			{
				performs["amount"] ="400";
			}
			else if (performs["name"] == "chan")
			{
				performs["amount"] ="4";
			}
			else
			{
				performs["amount"] ="3";
			}
		}
		else if (spe_skillnum==6)
		{
			performs["need_level"]="150";
			performs["jingli_cost"]="40";
			performs["neili_cost"]="160";
			if (performs["name"] == "critical")
			{
				performs["amount"] ="600";
			}
			else if (performs["name"] == "chan")
			{
				performs["amount"] ="6";
			}
			else
			{
				performs["amount"] ="5";
			}
		}
		else if (spe_skillnum==9)
		{
			performs["need_level"]="250";
			performs["jingli_cost"]="60";
			performs["neili_cost"]="240";
			if (performs["name"] == "critical")
			{
				performs["amount"] ="800";
			}
			else if (performs["name"] == "chan")
			{
				performs["amount"] ="8";
			}
			else
			{
				performs["amount"] ="7";
			}
		}
		else
		{
			return;
		}
		
		write("\n你突然福至心灵，顿悟出一招可以"+HIY+performs["usage"]+NOR+"的招数，请为该招数命名：（例如：梅花六出）\n");
		
		input_to( (: get_perform_zhaoshi_ch_name :), ob );
	}
}
}

int check_legal_basename(string name)
{
int i;

for(i=0;i<sizeof(valid_types);i++)
     if(valid_types[i]==name)
        return 1;

return 0;
}

int check_legal_id(string id)
{
	int i;
	i = strwidth(id);
	
	if( (strwidth(id) < 3) || (strwidth(id) > 12 ) )
	{
		write("你的武功代号必须是 3 到 12 个英文字母。\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z' )
		{
			write("你的武功代号只能用小写英文字母。\n");
			return 0;
		}
	
	return 1;
}

int check_legal_name(string name)
{
	int i;
	i = strwidth(name);
	if( i < 1 || i > 6 )
	{
		write("武功的中文名称必须是 1 到 6 个中文字。\n");
		return 0;
	}
	while(i--)
	{
		if( name[i] <= ' ' )
		{
			write("你的武功中文名称不能用控制字元。\n");
			return 0;
		}
		if( !is_chinese(name[i..<0]) )
		{
			write("你的武功中文名要用「中文」!\n");
			return 0;
		}
	}
	if( member_array(name,banned_name)!=-1 )
	{
		write("你的武功中文名称会造成其他人的困扰。\n");
		return 0;
	}
	
	return 1;
}

//file header of the skill for each file
//0:// THIS IS PLAYER'S OWN SKILL (write by maxim@nju_fengxue)
//1:// file owner id
//2:// file owner Chinese name
//3:// owner title
//4:// owner exp
//5:// owner gender
//6:// skill Chinese name
//7:// skill 性质 of unarmed or sword or blade....etc
//8://
//9
//10
//11
//12
//13
//14 //reserved

int check_skillnum_exist(object me,string skill_en_name,int skill_num)
{
	string file,*list;
	string playername;
	int total_zhaoshi_num;
	
	file=read_file(PLAYER_SKILL_D(skill_en_name));
	if(!file)
	{
		//若已经自创了相同类型的功夫，则返回0
		if(me->query("skillmaxim/" + spe_skill_basename) != 0)
			return 0;
		else
			return 1;
	}
	else
		list = explode(file, "\n");
	
	playername=geteuid(me);
	if(list[1]!="// "+playername)
		return 0;
	if(list[0]!="// THIS IS PLAYER'S OWN SKILL (write by maxim@nju_fengxue)")
		return 0;
	
	if(sscanf(list[sizeof(list)-1-SPE_PRA_LINES],"// ZHAOSHI :%d",total_zhaoshi_num)!=1)
		return 0;
	if(total_zhaoshi_num==0)
		return 0;
	if(total_zhaoshi_num+1 == skill_num)
		return skill_num;
	else if (total_zhaoshi_num==skill_num)
	{
		redo_action = 1;
		return skill_num;
	}
	else if (total_zhaoshi_num > skill_num)
		return -1;
	else
		return -2;
	
	return 0;
}

int check_owner_skill(object me,string skill_en_name)
{
	///return num:
	/// error : 1,2,3,4,5
	/// OK     : 0
	string file,*list;
	string playername;

	/// deWolf 检查非自创功夫
	file=read_file(SKILL_D(skill_en_name));
	if(file)
	{
		return 2;
    }
	
	file=read_file(PLAYER_SKILL_D(skill_en_name));
	if(!file)
	{
        //have create another skill of unarmed,so can't create this
		if(me->query("skillmaxim/"+spe_skill_basename)!=0)
			return 1;
		else
			return 0;
	}
	else
		list = explode(file, "\n");
	playername=geteuid(me);

	if(strcmp(list[1],"// "+playername)) /// 使用strcmp 比较字符串, deWolf 2005.11
		return 2;
	if(list[0]!="// THIS IS PLAYER'S OWN SKILL (write by maxim@nju_fengxue)")
		return 2;
	
	return 0;
}

int check_action_name(string yn)
{
	int i;
	
	if(CHINESE_D->check_control(yn))
	{
		write("你的武功描述不能用控制字元。\n");
		return 0;
	}
	if(CHINESE_D->check_length(yn) > 160)
	{
		write("你的武功描述不能超过80个汉字。\n");
		return 0;
	}

	if(hasquote(yn)>=0)
	{
		write("你的武功描述不能用控制字元。\n");
		return 0;
	}
	
	i = strwidth(yn);
	while(i--)
	{
		if( yn[i]<=' ' )
		{
			write("你的武功描述不能用控制字元。\n");
			return 0;
		}
	}
	return 1;
}

void	modify_skill_param(mapping spe_skill)
{
	/*   deWolf 2005.11
	*
	*2 自创武功的招式伤害数据设定不能千篇一律，高经验者的功夫要略微比
	*低经验的强一点点，例如定为增加log10(exp)*10-40。另外需要根据玩家
	*创招时候的后天臂力、根骨、身法择弱在此基础上予以弱项弥补：
	*  2.1 后天臂力低者+damage,-force,-parry,-dodge；
	*  2.2 后天根骨低者-damage,+force,-parry,-dodge；
	*  2.3 后天身法低者-damage,-force,+parry,+dodge。
	*  以上2.1-2.3修正上限在基数*1.5，下限在基数*0.5，变更尺度正比
	*于最低属性偏离3项平均值的距离，具体系数待定。
	*
	*/
	int modi_factor, mystr, mycon, mydex, myavg;
	int modi_amount, modi_upper_bound;
	object me;
	
	modi_factor = 0;
	me = this_player();
	
	mystr = me->query_str();
	mycon = me->query_con();
	mydex = me->query_dex();
	myavg = (mystr + mycon + mydex)/3;
	
	/*
	* 伤害计算 和 damage, force 都有关，因此即使有人放弃拳脚，例如 str=20,con=70,dex=70
	* avg=53, 由于ubound限制，dam偏差最多不会超过100
	*/
	modi_upper_bound = 50+random(50);
	if (mystr <= mycon && mystr <= mydex)
	{
		// str 最小
		modi_factor = (myavg - mystr)*100/myavg; // 偏差的整数百分比
		if (modi_factor > 50)
			modi_factor = 50;
		modi_amount = spe_skill["damage"]*modi_factor/150;
		if (modi_factor > modi_upper_bound)
			modi_factor = modi_upper_bound;
				
		spe_skill["damage"]+=modi_amount;
		spe_skill["force"]-=modi_amount/2;
		spe_skill["dodge"]-=modi_amount/3;
		spe_skill["parry"]-=modi_amount/3;
	}
	else if (mycon <= mystr && mycon <= mydex)
	{
		// con 最小
		modi_factor = (myavg - mycon)*100/myavg; // 偏差的整数百分比
		if (modi_factor > 50)
			modi_factor = 50;
		modi_amount = spe_skill["force"]*modi_factor/100;
		if (modi_factor > modi_upper_bound)
			modi_factor = modi_upper_bound;
		
		spe_skill["damage"]-=modi_amount/2;
		spe_skill["force"]+=modi_amount;
		spe_skill["dodge"]-=modi_amount/4;
		spe_skill["parry"]-=modi_amount/4;
	}
	else
	{
		// dex 最小
		modi_factor = (myavg - mydex)*100/myavg; // 偏差的整数百分比
		if (modi_factor > 50)
			modi_factor = 50;
		modi_amount = (200+2*spe_skill["dodge"])*modi_factor/100; // dodge 一般比较小
		if (modi_factor > modi_upper_bound)
			modi_factor = modi_upper_bound;
		
		spe_skill["damage"]-=modi_amount/2;
		spe_skill["force"]-=modi_amount/2;
		spe_skill["dodge"]+=modi_amount;
		spe_skill["parry"]+=modi_amount;
	}
	
	return;
}

int hasquote(string tar)
{
	///返回 b在a中的位置
	/// -1: none 
	/// 0+: 位置
	int a_len, i;
	a_len = strwidth(tar);
	for (i=0; i<a_len; i++)
	{
		if (tar[i]=='"' || tar[i]=='\\')
		{
			return i;
		}
	}
	return -1;
}

int loge(int exp)
{
	int ex,res;
	res=0;
	for (;ex>2.71828 && res<500;)
	{
		ex/=2.71828;
		res++;
	}
	return res;
}

//接收玩家输入的中文perform名称
void get_perform_zhaoshi_ch_name(string yn, object ob)
{
if( yn=="" )
{
	write("\r请给招式起个名字(不要此时断线，否则永远无法再正确创建):");
	input_to( (: get_perform_zhaoshi_ch_name :), ob );
	return;
}
if( !check_legal_name(yn) )
{
	write("招式名称：");
	input_to( (: get_perform_zhaoshi_ch_name :), ob );
	return;
}

performs["ch_name"]=yn;

write(HIR"\n描述中不能出现控制符，不然将删除!\n"NOR);
write(" 此描述只能一次性输入，不可再次修改！\n");
write("请看以下例句：（“敌人”，“你”带有普遍性）\n");
write("\n你沉肩滑步，自丹田中升起一股阴柔之气顺着血脉经络传至双手，对着敌人激射而出\n");
write("提示：必须要有"HIY"你"NOR"和"HIY"敌人"NOR"字样出现，输入“武器”“某部位”无效！\n");
write("\n请输入你的招式描述：\n");

input_to("get_perform_zhaoshi_ch_action", 1, ob);
}

//接收玩家输入的中文perform招式
void get_perform_zhaoshi_ch_action(string yn, object ob)
{
if(check_action_name(yn)==0)
{
	write("\n请输入你的招式描述：\n");
	input_to( (: get_perform_zhaoshi_ch_action :), ob );
	return;
}
if(CHINESE_D->check_length(yn) > 160)
{
	write(HIR"描述太长。\n"NOR);
	write("\n请输入你的招式描述：\n");
	input_to( (: get_perform_zhaoshi_ch_action :), ob );
	return;
}

if(hasquote(yn)>=0)
{
	write(HIR"你的武功描述不能用控制字元。\n"NOR);
	write("\n请输入你的招式描述：\n");
	input_to( (: get_perform_zhaoshi_ch_action :), ob );
	return;
}

if(CHINESE_D->check_control(yn))
{
	write(HIR"你的武功描述不能用控制字元。\n"NOR);
	write("\n请输入你的招式描述：\n");
	input_to( (: get_perform_zhaoshi_ch_action :), ob );
	return;
}
if( yn=="" )
{
	write(HIR"\n描述中不能出现控制符，不然将删除!\n"NOR);
	write(" 此描述只能一次性输入，不可再次修改！\n");
	write("请看以下例句：（“敌人”，“你”带有普遍性）\n");
	write("\n你沉肩滑步，自丹田中升起一股阴柔之气顺着血脉经络传至双手，对着敌人激射而出\n");
	write("提示：必须要有"HIY"你"NOR"和"HIY"敌人"NOR"字样出现，输入“武器”“某部位”无效！\n");
	write("\n请输入你的招式描述：\n");
	
	input_to( (: get_perform_zhaoshi_ch_action :), ob );
	return;
}

performs["action"]=yn;

finish_write_perform(ob);
// 记录日志
log_file("CREATESKILL_PERFORM",
	sprintf("%s(%s)--%s(%s) %s(%s): %d (%s)\n",
			performs["ch_name"],
			performs["name"],
			ob->query("name"),
			ob->query("id"),
			spe_skill["skill_ch_name"],
			spe_skill_name,
			spe_skillnum,
			ctime(time()))
);
}

void finish_write_perform(object ob)
{
int i;
string *list2;
string file;
string result;

	performs["action"]= replace_string(performs["action"], "'"," ");
	performs["action"]= replace_string(performs["action"], "你","$N");
	performs["action"]= replace_string(performs["action"], "敌人","$n");
	
	if(spe_skill_basename=="sword"
			 || spe_skill_basename=="blade"
			 || spe_skill_basename=="staff"
			 || spe_skill_basename=="spear"
			 || spe_skill_basename=="whip")
	
	file = read_file("/kungfu/vast/perform_model_"+performs["name"]+".c");
	
	if ((int)file!=0)
		list2 = explode(file, "\n");
	else
		return notify_fail("错误：报告巫师出错，找不到perform_model_"+performs["name"]+".c。\n");
		
	for(i=0;i < sizeof(list2);i++)
	{
		list2[i]= replace_string(list2[i], "SKILL_EN_NAME",spe_skill_name );
		list2[i]= replace_string(list2[i], "SKILL_CH_NAME",spe_skill["skill_ch_name"] );
		list2[i]= replace_string(list2[i], "SKILL_BASE_NAME",spe_skill_basename );
		list2[i]= replace_string(list2[i], "PERFORM_CH_NAME",performs["ch_name"] );
		list2[i]= replace_string(list2[i], "PERFORM_NEED_LEVEL",performs["need_level"] );
		list2[i]= replace_string(list2[i], "PERFORM_NEED_NEILI",performs["neili_cost"] );
		list2[i]= replace_string(list2[i], "PERFORM_NEED_JINGLI",performs["jingli_cost"] );
		list2[i]= replace_string(list2[i], "PERFORM_ACTION",performs["action"] );
		list2[i]= replace_string(list2[i], "PERFORM_AMOUNT",performs["amount"] );
	}
	
	result="";
	for(i=0;i < sizeof(list2);i++)
	{
		result+=list2[i]+"\n";
	}
	
	mkdir(PLAYER_SKILL_D(spe_skill_name));
	rm(PLAYER_SKILL_D(spe_skill_name)+"/"+performs["name"]+"."+(string)spe_skillnum+".c");
	write_file(PLAYER_SKILL_D(spe_skill_name)+"/"+performs["name"]+"."+(string)spe_skillnum+".c", result);

	//children(PLAYER_SKILL_D(spe_skill["skill_en_name"]))->clean_up();
	
	write("你长出了一口气，「"+spe_skill["skill_ch_name"]+"」的绝招「"+HIY+performs["ch_name"]+NOR+"」领悟好了。\n");
}


int help (object me)
{
	write(@HELP
指令格式：createskill <武功基本技能> <武功英文名字> <武功中文名字> <第几招>

    这是用来创建自己风格武功的指令，随着经验值的增长，所可以实现的招式越来
越多，招式的威力也越来越大。玩家增加招式的熟练程度的方式是使用两个专用指令：
selfpractice，selfthinking，后一个命令要消耗潜能，但是速度比第一个快。
这几个指令都只能在侠客岛或者自创帮派的闭关室使用。

    玩家如果觉得当前招式的描述不太好，可以继续用本命令修改。即对已有5招的武功
可以修改第5招，或者加入第6招，而不能修改1-4招。由于是自己摸索招式，所以难度要
大些。玩家只能修改当前的招式，对以前的招式无法改动。所以玩家要事先规划好6-7招，
边练边修改，以免到时侯无法改动以前的基本招式。

    可以利用的基本功夫有：
基本空手功夫: "unarmed","finger","hand","cuff","claw","strike"
基本兵器功夫: "sword","blade","staff","spear","whip"

    注意:
	1 招式的英文名称后面将被加上基本技能的几个标识，玩家要事先想好，
一旦开始创建则无法随意改动中英文名称。
	2 招式描述中不要加入控制字符。
	3 玩家最多只能创建三种不同高级功夫。

例如：createskill unarmed kong 空手道 1
就会创建一个英文名字为kong-unarmed，中文名字是空手道的功夫

    招式描述中的：
“敌人”，“你”，“某部位”，“武器”带有普遍性，
实际应用中将会被替换成相应的字符。
招式的描述不要带有对自己或对手状态的描写，不要不负责的乱写。
巫师将检查玩家所创建的功夫，如不符合规定，将被删除。
例如：你大喝一声，运起「七诀剑气」，只见数道剑气直逼敌人的某部位而上，剑风过后，
地表赫然出现三道斑驳的气痕

自创武功，至少需要5M以上的经验，10万以上武林声望，
        10M经验、20万武林声望可以自创两种武功，
        15M以上经验、30万以上武林声望可以自创三种武功，
        每种功夫的招数最多9招，
        5M经验、10万武林声望只能自创一招，
        6M经验、15万武林声望两招，以此类推，
        每一招必须练习40级，才能继续自创新招。

    功夫的每招都受制于天时地利、招式数量、历练经验、功夫类别和自身属性等因素。
其中，为在战斗中保护自己的弱点，招式会自动根据创造者自身属性的最弱项的偏离程度
予以在予以额外注重，同时等量削弱强项。
		
    在第3，6，9招第一次创建完成时有机缘领悟到可以 3种不同绝招，如果有缘，就
可以领悟并借助这些绝招在战斗中以己之长攻敌之短。同样的，也可以为之命名和制作
描述，不过名称和描述仅能一次性输入，之后无法变更。与普通招式护短不同，绝招是
利用创造者的自身长处来攻击对手。由于每个人的最强项不同，所领悟出来的绝招自然
也会不同。

    希望自创武功的玩家，请向龙亦凡打听“自创武功”，然后按提示做既可，除了以上的
经验、武林声望的要求外，还需要至少1000两黄金，并且每次开关出室要降低10000点武林
声望，所以一旦进入闭关室，请务必潜心钻研武功。

    自创武功的主要目的是让玩家发挥想象力，创作出自己的独特功夫，请玩家不要误入
歧途；自创武功目前处于测试阶段，有任何问题请与巫师联系。
HELP
);
	return 1;
}
