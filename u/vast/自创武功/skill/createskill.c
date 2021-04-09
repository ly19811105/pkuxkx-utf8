//createskill.c
/////////////////////////
//write by maxim@nju_fengxue
//mail address is to see: maxim jiang of bbs.nju.edu.cn
// 1997.12.21
////////////////////////
//vast@pkuxkx 修改并做部分注释 2003.3

#include <ansi.h>

inherit F_CLEAN_UP;

#define SHUANGYIN_HAO "\""
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
	"hammer",
	"whip",
});

//禁用名称列表,请在发现问题后及时添加
string *banned_name=({
          "  ",});


 string *spe_skill_lvl=({
            "0","12","20","30","40","50","60","80","100",});

 string *spe_skill_force=({
                "50","80","100","130","150","180","200","220","240"
                   });

string *spe_skill_unarmeddodge=({
             "10","-10","-20","-30","-50","-60","-80","-90","-100",
                   });

 string *spe_skill_unarmedparry=({
            "10","-10","-20","-30","-40","-50","-60","-70","-80",
                   });

 string *spe_skill_weapondodge=({
             "20","10","10","5","-5","-5","-10","-10","-10",
                   });

 string *spe_skill_weaponparry=({
            "20","20","10","10","5","5","5","5","5",
                   });


 mapping spe_skill = ([
    "action" : ({" "}),
    "force" : ({"10"}),
    "dodge" : ({"10"}),
    "parry": ({"10"}),
    "damage_type" : ({"瘀伤"}),
    "lvl" : ({"10"}),
    "skill_name" : ({"横空出世"}),
    "skill_total_num" : ({"0"}),
    "skill_en_name" : ({" "}),
    "skill_ch_name" : ({" "}),
   ]);

 int spe_skillnum;


 string spe_skill_name;

//基本技能名称
 string spe_skill_basename;

int check_legal_id(string id);
int check_legal_name(string name);
int check_action_name(string yn);
int check_legal_basename(string name);
void skill_init_header(string skill_en_name,string skill_ch_name);
void get_zhaoshi_ch_name(string yn, object ob);
void get_zhaoshi_ch_action(string yn, object ob);
int check_skillnum_exist(object me,string skill_en_name,int skill_num);
void finish_write_skill(object ob);
int check_owner_skill(object me,string skill_en_name);
string get_header_skillchname(string file);
string get_header_skillbasename(string file);

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

int skill_num,skill_num_result;
string skill_en_name,skill_ch_name;
string skill_base_name;
object env=environment(me);

spe_skill_basename="";
spe_skill_name="";
spe_skillnum=0;

//判断输入的命令格式是否正确
if(!arg)
    return notify_fail("指令格式：createskill <武功基本技能> <武功英文名字> <武功中文名字> <第几招>\n");
if( sscanf(arg, "%s %s %s %d", skill_base_name,skill_en_name,skill_ch_name,skill_num)!=4)
    return notify_fail("指令格式：createskill <武功基本技能> <武功英文名字> <武功中文名字> <第几招>\n");

//巫师测试完成后，请注释以下两行
if (!wizardp(me) )
    return notify_fail("此系统暂不开放，测试中!\n");

if(!env->query("createskill_room")) 
return notify_fail("你只能在侠客岛的闭关室自创武功!\n");

//将玩家输入的英文名称转化为小写
skill_en_name=lower_case(skill_en_name);

spe_skill_basename=skill_base_name;

//检查玩家输入的武功基本技能是否允许自创
if(check_legal_basename(skill_base_name)==0)
    return notify_fail("你输入的基本技能不存在或者暂时不能自创这种武功。\n");

//检查玩家输入的武功英文名字是否符合条件(2-12个英文字母)
if(check_legal_id(skill_en_name)==0)
               return 1;             

//检查玩家输入的武功英文名字是否符合条件(1-6个汉字)
if(check_legal_name(skill_ch_name)==0)
               return 1;  

if(skill_num>9) return notify_fail("自创武功最多九招。\n");

          
//自动将武功的英文名称改为标准格式
spe_skill["skill_en_name"]=skill_en_name+"-"+skill_base_name+".c";
spe_skill_name=skill_en_name+"-"+skill_base_name;
spe_skill["skill_ch_name"]=skill_ch_name;


//so player can change the Chinese skill name when he begin to create
//only 1 招
if( skill_num!=1 
    && get_header_skillchname(spe_skill["skill_en_name"])!=skill_ch_name)
    return notify_fail("你输入的中文武功名称和所选的英文武功代号有矛盾。\n");

if( skill_num!=1 
    && get_header_skillbasename(spe_skill["skill_en_name"])!=skill_base_name)
    return notify_fail("你输入的基本技能名和所选的英文武功代号有矛盾。\n");


//每个玩家最多创建3种高级功夫
if((int)me->query("skillmaxim")!=0
        && sizeof(keys(me->query("skillmaxim/"))) >= 3 )
    return notify_fail("你最多只能创建三种高级功夫。\n");


switch( check_owner_skill(me,spe_skill["skill_en_name"]))
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

if(skill_num < 1)
       return notify_fail("你需要从第一招开始创建。\n");

//经验值至少需要10M，此值应根据不同的情况修改
if((int)me->query("combat_exp") < 10000000)
       return notify_fail("你的经验值不够。\n");

if((int)me->query("repute") < 100000)
       return notify_fail("你的武林声望不够。\n");

//10M以上每多5M经验，可以多创一招
if((int)me->query("combat_exp") < (skill_num-1)*5000000+10000000)
       return notify_fail("你的经验值还不够。\n");

if((int)me->query("repute") < (skill_num-1)*50000+100000)
       return notify_fail("你的武林声望还不够。\n");

//现有的武功必须练到(40*招式)的级别才能继续创下一招
if((int)me->query_skill(spe_skill_name, 1)!=0
     && (int)me->query_skill(spe_skill_name, 1) < (skill_num-1)*40)
       return notify_fail("你已经有的招式还不够熟练，先提高它们，然后再想新招吧。\n");
    

skill_num_result=(check_skillnum_exist(me,spe_skill["skill_en_name"],skill_num));

if(skill_num_result == 2)  return notify_fail("你的经验不够，无法自创新的武功。\n");

if(skill_num_result == 3)  return notify_fail("你的武林声望不够，无法自创新的武功。\n");

if(skill_num_result > 1) {
      write("\r请给招式起个名字(不要此时断线，否则永远无法再正确创建):");
                   }
else if(skill_num_result==1) {
//here always set to 1 if create again
      write("你现在开始创建"+skill_ch_name+"("+spe_skill_name+")"+"的第一招.\n");
      write("\r请给招式起个名字(不要此时断线，否则永远无法再正确创建):");
                         }
else 
        return notify_fail("你所要创建功夫的招式数有误。\n");

spe_skillnum=skill_num;

//bug have been here,so sad...
if(skill_num==1) {
             rm(PLAYER_SKILL_D(spe_skill["skill_en_name"]));
          //  write("here ???\n");
             skill_init_header(spe_skill["skill_en_name"],skill_ch_name);
                      }
input_to( (: get_zhaoshi_ch_name :), this_player() );
return 1;
}

//若武功文件已经存在，此函数返回这种自创武功的中文名，否则返回0
string get_header_skillchname(string file)
{
string result;

string content,*list;
content=read_file(PLAYER_SKILL_D(file));
if((int)content==0)
       return 0;
list = explode(content, "\n");
if(sizeof(list) < 8)
     return 0;
else {
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
 if( yn=="" ) {
      write("\r请给招式起个名字(不要此时断线，否则永远无法再正确创建):");
        input_to( (: get_zhaoshi_ch_name :), ob );
        return;
       }

 if( !check_legal_name(yn) ) {
        write("招式名称：");
        input_to( (: get_zhaoshi_ch_name :), ob );
        return;
           }

  spe_skill["skill_name"]=yn;

write(HIR"\n描述中不能出现控制符，不然将删除!\n"NOR);
write("\n想象一下你和敌人的打斗，(高手指南:必须要有你和敌人字样出现!)\n");
write("请看以下例句：（“敌人”，“你”，“某部位”，“武器”带有普遍性）\n");
write("\n你前腿踢出，后腿脚尖点地，一式「横空出世」，二掌直出，攻向敌人的上中下三路\n");
write("你纵身一跃，手中武器一招「金光泻地」对准敌人的某部位斜斜刺出一剑\n\n");
write("请输入你的招式描述：\n");

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

if(CHINESE_D->check_control(yn))
{
 write(HIR"你的武功描述不能用控制字元。\n"NOR);
 input_to( (: get_zhaoshi_ch_action :), ob );
 return;
}
 if( yn=="" ) {
write(HIR"\n描述中不能出现控制符，不然将删除!\n"NOR);
write("\n注意，一定要写上描述（不然是非法招式，会被删除)写完后，空行打二下回车。\n");
write("\n想象一下你和敌人的打斗，(高手指南:必须要有你和敌人字样出现!)\n");
write("请看以下例句：（“敌人”，“你”，“某部位”，“武器”带有普遍性）\n");
write("\n你前腿踢出，后腿脚尖点地，一式「横空出世」，二掌直出，攻向敌人的上中下三路\n");
write("你纵身一跃，手中武器一招「金光泻地」对准敌人的某部位斜斜刺出一剑\n\n");
write("请输入你的招式描述：\n");

 input_to( (: get_zhaoshi_ch_action :), ob );
 return;
 }

  spe_skill["action"]=yn;


 finish_write_skill(ob);
ob->set("skillmaxim/"+spe_skill_basename,1);
 if(spe_skillnum==1) {
      ob->set_skill(spe_skill_name,1);
       }

 log_file( "CREATESKILL", sprintf("%s(%s) %s(%s): %d (%s)\n",
 ob->query("name"),
 ob->query("id"),
  spe_skill["skill_ch_name"],
 spe_skill_name,
  spe_skillnum,
  ctime(time()) ) );


CHINESE_D->add_translate(spe_skill_name,spe_skill["skill_ch_name"]);


}

//first header
//then action
//then 35 lines of practice or other thing

//here should determain the file is: over wirte or appetine something
void finish_write_skill(object ob)
{
string action;
string file,*list;
string content;
int before_skillnum,i;
string *list2;
string header2;
string result;

header2="";
result="";
content="";
action="";
//spe_skill["force"]=spe_skill_force[spe_skillnum-1];
spe_skill["force"]=30+spe_skillnum*30;

switch(spe_skill_basename){

  case "unarmed":
spe_skill["damage_type"]="瘀伤";
  break;

  case "sword":
  case "spear":
spe_skill["damage_type"]="刺伤";
  break;

  case "blade":
spe_skill["damage_type"]="割伤";
  break;

  case "strike":
spe_skill["damage_type"]="内伤";
  break;

 default:
spe_skill["damage_type"]="瘀伤";
  break;
 }

if(spe_skill_basename=="unarmed"
 || spe_skill_basename=="strike"
 || spe_skill_basename=="finger"
 ) {
spe_skill["damage"]=20+spe_skillnum*20;
spe_skill["parry"]=20+spe_skillnum*20;
 }
else if(spe_skill_basename=="sword"
 || spe_skill_basename=="blade"
 || spe_skill_basename=="rube"
 || spe_skill_basename=="music"
 || spe_skill_basename=="piano"
 || spe_skill_basename=="whip"
          ){
spe_skill["damage"]=20+spe_skillnum*20;
spe_skill["parry"]=20+spe_skillnum*20;
     }
else {
spe_skill["damage"]=20+spe_skillnum*20;
spe_skill["parry"]=20+spe_skillnum*20;
  }




spe_skill["lvl"]=spe_skillnum-1;

   
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

 spe_skill["action"]= replace_string(spe_skill["action"], "'"," ");
 spe_skill["action"]= replace_string(spe_skill["action"], "你","$N");
  spe_skill["action"]= replace_string(spe_skill["action"], "敌人","$n");               
  spe_skill["action"]= replace_string(spe_skill["action"], "某部位","$l");              
if(spe_skill_basename=="sword"
         || spe_skill_basename=="blade"
         || spe_skill_basename=="staff"
         || spe_skill_basename=="hammer"
         || spe_skill_basename=="whip"
      ) 
  spe_skill["action"]= replace_string(spe_skill["action"], "武器","$w");
  
 
action="\n([\n"
             +SHUANGYIN_HAO
           +"action"+SHUANGYIN_HAO
            +" :"
           +SHUANGYIN_HAO+
             spe_skill["action"]
            +SHUANGYIN_HAO
             +",\n"+
 SHUANGYIN_HAO+
  "force"+SHUANGYIN_HAO+" :"+ spe_skill["force"]+",\n"+
 SHUANGYIN_HAO+
  "damage"+SHUANGYIN_HAO+" :"+ spe_skill["damage"]+",\n"+
 SHUANGYIN_HAO+
  "damage_type" +SHUANGYIN_HAO+": "+SHUANGYIN_HAO+spe_skill["damage_type"]+
       SHUANGYIN_HAO+",\n"+
 SHUANGYIN_HAO+
 "lvl"+SHUANGYIN_HAO+" : "+spe_skill["lvl"]+",\n"+
 SHUANGYIN_HAO+
 "skill_name"+SHUANGYIN_HAO+" : "+SHUANGYIN_HAO+spe_skill["skill_name"]+
   SHUANGYIN_HAO 
   +"\n]),"
   +"\n });"
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
         || spe_skill_basename=="claw"
       )
    header2=read_file(SKILL_MODEL_UNARMED);
else if(spe_skill_basename=="sword" 
         || spe_skill_basename=="blade"
         || spe_skill_basename=="staff"
         || spe_skill_basename=="hammer"
         || spe_skill_basename=="whip"
          )
    header2=read_file(SKILL_MODEL_WEAPON);
else 
    header2=read_file(SKILL_MODEL_DEFAULT);

list2 = explode(header2, "\n");
for(i=0;i < sizeof(list2);i++) {
//this is not the arg!!!
//spe_skill_name!=skill_en_name...
         list2[i]= replace_string(list2[i], "SKILL_EN_NAME", 
              SHUANGYIN_HAO+spe_skill_name+SHUANGYIN_HAO );
         list2[i]= replace_string(list2[i], "SKILL_CH_NAME", 
                SHUANGYIN_HAO+spe_skill["skill_ch_name"]+SHUANGYIN_HAO );
         list2[i]= replace_string(list2[i], "SKILL_BASE_NAME", 
              SHUANGYIN_HAO+spe_skill_basename+SHUANGYIN_HAO );
               }
//result contain the practice and exert information
for(i=0;i < sizeof(list2);i++) {
          result+=list2[i]+"\n";
        }
///////////////////////////////////////////////
//write("\nhere slslslls :"+spe_skillnum);
//now only a few be created,so the end is zhaoshi : 0
  if(spe_skillnum==1) {
      if(sscanf(list[sizeof(list)-1],"// ZHAOSHI :%d",before_skillnum)!=1){
             write("可能出现异常了，如不能解决请通知巫师。\n");
            return;
           }
       }
  else {
  if(sscanf(list[sizeof(list)-1-SPE_PRA_LINES],"// ZHAOSHI :%d",before_skillnum)!=1){
             write("可能出现异常了，如不能解决可通知巫师。\n");
                    return;
                  }
           }
        //this will be excuted if total get correctly
           {
              //remove the old action
                  if( before_skillnum==spe_skillnum){
         //  write("\nremove the old action\n");
                for(i=0;i < sizeof(list)-11-SPE_PRA_LINES;i++)
                     content+=list[i]+"\n";
                content+=action;
              rm(PLAYER_SKILL_D(spe_skill["skill_en_name"]));
              write_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]),content);
               }
         else {
            //add a new action
//if it is a new create first
//then should be:
          rm(PLAYER_SKILL_D(spe_skill["skill_en_name"]));

          if(spe_skillnum!=1) {
                for(i=0;i < sizeof(list)-SPE_PRA_LINES-2;i++)
                     content+=list[i]+"\n";
            //      write("see list :"+sizeof(list));
                  content+="// ZHAOSHI :"+(string)before_skillnum
                               +"\n";
                  content+=action;
              write_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]),content);
           //    write("\nadd a  action1\n");
                            }
          else if(spe_skillnum==1) {
                for(i=0;i < HEADER_END+3;i++)
                     content+=list[i]+"\n";
                  content+="// ZHAOSHI :"+(string)before_skillnum
                               +"\n";
                  content+=action;
              write_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]),content);
          //     write("\nadd a  action2\n");
                            }
         
             }    
   //at last wirte the practice and other exert information
        write_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]),"\n"+result);
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

 if( (strwidth(id) < 3) || (strwidth(id) > 12 ) ) {
 write("你的武功代号必须是 3 到 12 个英文字母。\n");
 return 0;
 }
 while(i--)
 if( id[i]<'a' || id[i]>'z' ) {
 write("你的武功代号只能用英文字母。\n");
                        return 0;
                }

        return 1;
}

int check_legal_name(string name)
{
 int i;
 i = strwidth(name);
 if( (strwidth(name) < 1) || (strwidth(name) >6 ) ) {
      write("武功的中文名称必须是 1 到 6 个中文字。\n");
 return 0;
 }
 while(i--) {
      if( name[i]<=' ' ) {
 write("你的武功中文名城不能用控制字元。\n");
 return 0;
 }
  if(  !is_chinese(name[i..<0]) ) {
                        write("你的武功中文名要用「中文」!\n");
                        return 0;
                }
        }

        if( member_array(name,banned_name)!=-1 ) {
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

// write("see the: "+skill_en_name+"\n");
//not reconmend programeing!@!!
file=read_file(PLAYER_SKILL_D(spe_skill["skill_en_name"]));
if(!file) {
//若已经自创了相同类型的功夫，则返回0
          if(me->query("skillmaxim/"+spe_skill_basename)!=0)
              return 0;
          else {
//             write("here be excuted???\n");
				if(!me->query("skillmaxim")) return 1;
				if(me->query("combat_exp") < (sizeof(keys(me->query("skillmaxim"))) + 1) * 10000000)
				return 2;
				if(me->query("repute") < (sizeof(keys(me->query("skillmaxim"))) + 1) * 100000)
				return 3;
				return 1;
			  }
       }
else
    list = explode(file, "\n");

playername=geteuid(me);
if(list[1]!="// "+playername)
      return 0;
if(list[0]!="// THIS IS PLAYER'S OWN SKILL (write by maxim@nju_fengxue)")
           return 0;

//write("see the zhaoshi line:"+list[sizeof(list)-1-SPE_PRA_LINES]);

if(sscanf(list[sizeof(list)-1-SPE_PRA_LINES],"// ZHAOSHI :%d",total_zhaoshi_num)!=1)
           return 0;
//write("see total zhaoshi is:"+total_zhaoshi_num);
if(total_zhaoshi_num==0)
           return 0;
if(total_zhaoshi_num==skill_num)
          return skill_num;
else if(total_zhaoshi_num+1 == skill_num)
          return skill_num;
else 
 return 0;
}
 
//return num:
//error is 1,2,3,4,5
// 0 is the right return num
int check_owner_skill(object me,string skill_en_name)
{
	string file,*list;
	string playername;

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
//this have some problem of not a reconmend programeing... method
//just return 2.
	if(list[1]!="// "+playername)
		return 2;
	if(list[0]!="// THIS IS PLAYER'S OWN SKILL (write by maxim@nju_fengxue)")
		return 2;
	else
		return 0;
}

int check_action_name(string yn)
{
 int i;
 i = strwidth(yn);

                if(CHINESE_D->check_control(yn))
{
 write("你的武功描述不能用控制字元。\n");
 return 0;
}
		if(CHINESE_D->check_length(yn) > 160)
{
 write("你的武功描述不能用控制字元。\n");
 return 0;
 }

 while(i--) {
      if( yn[i]<=' ' ) {
 write("你的武功描述不能用控制字元。\n");
 return 0;
 }
}
 return 1;
}

int help (object me)
{
        write(@HELP
指令格式：createskill <武功基本技能> <武功英文名字> <武功中文名字> <第几招>
 
这是用来创建自己风格武功的指令，随着经验值的增长，所可以实现的招式
越来越多，招式的威力也越来越大。
玩家增加招式的熟练程度的方式是使用两个专用指令：
selfpractice，selfthinking，后一个命令要消耗潜能，但是速度比第一个快
这几个指令都只能在侠客岛的闭关室使用。

玩家如果觉得当前招式的描述不太好，可以继续用这个命令修改。
由于是自己摸索招式，所以难度要大些。玩家只能修改当前的招式，对以前的
招式无法改动。所以玩家要事先规划好6-7招，边练边修改，以免到时侯无法
改动以前的基本招式。

可以利用的基本功夫有：
基本空手功夫: "unarmed","finger","hand","cuff","claw","strike"
基本兵器功夫: "sword","blade","staff","hammer","whip"

注意:
招式的英文名称后面将被加上基本技能的几个标识，玩家要事先想好，一旦
开始创建则无法随意改动英文名称。
招式描述中不要加入控制字符。
玩家最多只能创建三种高级功夫。

例如：createskill unarmed kong 空手道 1
就会创建一个英文名字为kong-unarmed，中文名字是空手道的功夫

招式描述中的：
“敌人”，“你”，“某部位”，“武器”带有普遍性，
实际应用中将会被替换成相应的字符。
招式的描述不要带有对自己或对手状态的描写，不要不负责的乱写。
巫师将检查玩家所创建的功夫，如不符合规定，将被删除。

自创武功，至少需要10M以上的经验，10万以上武林声望，
		  20M经验、20万武林声望可以自创两种武功，
		  30M以上经验、30万以上武林声望可以自创三种武功，
		  每种功夫的招数最多9招，
		  10M经验、10万武林声望只能自创一招，
		  15M经验、15万武林声望两招，以此类推，
		  每一招必须练习40级，才能继续自创新招。

		  希望自创武功的玩家，请向龙亦凡打听“自创武功”，
然后按提示做既可，除了以上的经验、武林声望的要求外，还需要
至少5000两黄金，并且每次开关出室要降低10000点武林声望，所
以一旦进入闭关室，请务必潜心钻研武功。
		
	自创武功的主要目的是让玩家发挥想象力，创作出自己的独特
功夫，请玩家不要误入歧途；自创武功目前处于测试阶段，有任何
问题请与巫师联系。
HELP
);
        return 1;
}
