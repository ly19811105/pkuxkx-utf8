#include <ansi.h>
#include <title.h>
#include <gene_map.h>
#include <command.h>
#include "/d/jueqinggu/npc/distortString.h"
inherit ITEM;	

//北侠地图分六大块
#define ZHONGYUAN 1        //中原区域 
#define CHANGJIANGNAN 2    //长江以南
#define HUANGHEBEI 3       //黄河以北 
#define XIYU 4             //西域
#define XINAN 5            //西南
#define XIANGYANGNAN 6     //中原地区的襄阳南部
#define QUESTREG 0         //任务区域，实际上指的是未知区域

//玩家划分为4个等级，越高等级，地图越大。第一等级集中在很小的区域内
//第零等级就在扬州
#define USER_LEVEL0 0
#define USER_LEVEL1 1
#define USER_LEVEL2 2
#define USER_LEVEL3 3
#define USER_LEVEL4 4
//暂时不对玩家开放5
#define USER_LEVEL5 5

void create()
{
        set_name(HIC"测试包"NOR,({ "test package","bao"}) );
        set_weight(4000);
        set("unit", "个");
        set("value", 10);
        set("material", "steel");
        set("long", "这是一个测试包。\n");                
        set("no_drop",1);
        set("no_get",1);
		
        setup();
}

void init()
{

    add_action("do_test","test");
    add_action("do_rehash","rehash");
    add_action("do_t2","t2");
    add_action("do_t1","t1");
	add_action("do_t3","t3");
	

}
int sort_increase(mapping list1,mapping list2)
{
	return list2["exp"]-list1["exp"];
}
int do_t5(int flag)
{
	object pl;
	string msg;
	string *title=({"10-50M","50-100M","100-400M","400-800M","800M+"});
	string *querys=({"_10_50","_50_100","_100_400","_400_800","_800"});
	mapping *list;
	if (flag<0||flag>4)
	{
		write("暂无此榜\n");
		return 1;
	}
	msg="pkuxkx "+title[flag]+"高手\n";
	list=STATISTIC_D->query("Players"+querys[flag]);
	list=sort_array(list,"sort_increase");
	for (int i=0;i<sizeof(list);i++)
	{
		if (pl=find_player(list[i]["id"]))
		msg+="第"+(i+1)+"名 "+(pl->query("title")?pl->query("title"):"")+pl->query("name")+"("+capitalize(pl->query("id"))+") <在线>\n";
		else
		msg+="第"+(i+1)+"名 ("+capitalize(list[i]["id"])+") <离线>\n";
	}
	write(msg);
	return 1;
}
int del(string arg,object *ob)
{
	if (arg=="y")
	for (int i=0;i<sizeof(ob);i++)
	destruct(ob[i]);
	return 1;
}
int do_t3()
{
	object *ob=children("/d/hangzhou/yewai");
	write("一个:"+sizeof(ob)+"个\ndel?");
	this_player()->set("ttt",ob);
	input_to((:del:),ob);
	return 1;
}
int do_t4()
{
	object *ob;
	ob =filter_array(children(USER_OB), (: userp :));
	ob = filter_array(ob, (: environment :));
	for (int i=0;i<sizeof(ob);i++)
	{
		if (ob[i]->query_temp("vein_through"))
		ob[i]->delete_temp("vein_through");
	}
	return 1;
}
int do_t2(int no,int flag)
{
	string *masters=({"wudang/zhang","shaolin/wuming","huashan/feng","mingjiao/zhang","tianlong/kurong","gaibang/hong","riyuejiao/ren","murong/murongbo","btshan/ouyangfeng",
	"xingxiu/li","gumu/yang","lingjiu/tonglao","quanzhen/wang","taohua/huang","shenlong/hong","dalunsi/laozu"});
	string mp,master,*masters2=({"emei/houshan/npc/miejue","hangzhou/npc/menggong","lingxiao/npc/baizizai"}),*sks,*spec_sks=({}),skill;
	object npc;
	mapping skills,*action;
	if (flag)
	npc=load_object("/kungfu/class/"+masters[no]);
	else
	npc=load_object("/d/"+masters2[no]);	
	skills=npc->query_skills();
	sks=keys(skills);
	for (int i=0;i<sizeof(sks);i++)
	{
		if ("/cmds/skill/skills.c"->query_skill_type(sks[i])=="special")
			spec_sks+=({sks[i]});
	}
	for (int i=0;i<sizeof(spec_sks);i++)
	tell_object(this_player(),cipher_name(this_player(),to_chinese(spec_sks[i])));
	return 1;
}
int do_t1()
{
	object *ob;
	ob =filter_array(children(USER_OB), (: userp :));
	ob = filter_array(ob, (: environment :));
	for (int i=0;i<sizeof(ob);i++)
	{
		if (wizardp(ob[i])) continue;
		if (F_PRO->pro_class(ob[i])!="fighter")
		write(HIR+F_PRO->pro_class(ob[i])+NOR+":");
		if (ob[i]->query_skill("alchemy",1)>1)
		write(ob[i]->query("id")+" ALCHEMY:"+ob[i]->query_skill("alchemy",1)+"\n");
		if (ob[i]->query_skill("herbalism",1)>1)
		write(ob[i]->query("id")+" HERB:"+ob[i]->query_skill("herbalism",1)+"\n");
		if (ob[i]->query_skill("smithing",1)>1)
		write(ob[i]->query("id")+" SMITH:"+ob[i]->query_skill("smithing",1)+"\n");
		if (ob[i]->query_skill("mining",1)>1)
		write(ob[i]->query("id")+" MINE:"+ob[i]->query_skill("mining",1)+"\n");
	}
	return 1;
 }
