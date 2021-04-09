//地图生成工具。
#include <ansi.h>　//by mudy
//Created by quqing
inherit ROOM;
void create()
{
        set("short", "浩然居");
        set("long", ""
/*DESCRIBE*/"LONGNAME"+"\n"
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//OVERDESCRIBE
        );
        set("exits", ([
"east":"/u/canexpand/seed",
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//OVER
                 ]));
set("objects", ([
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OVEROBJECT           
            ]));
        setup();
/*DEL*/		if(!sizeof(query("exits"))&&file_name(this_object())!=__DIR__"sample") rm(file_name(this_object())+".c");//如果该房间没有出口自动会被删除！

}
//CUTHERE
//为以后cut做一个记号

int do_write(string arg,string dir,object me);
int get_shortname(string arg);
int get_longname(string arg);
int get_npcname(string arg);
int get_npctitle(string arg);
int get_npcnickname(string arg);
int get_npcdescribe(string arg);
int get_npcid(string arg);
int get_npcgender(string arg);
int get_npcage(string arg);
int get_npcstr(string arg);
int get_npcint(string arg);
int get_npccon(string arg);
int get_npcdex(string arg);
int get_npcmaxqi(string arg);
int get_npcmaxjing(string arg);
int get_npcmaxneili(string arg);
int get_npcjiali(string arg);
int get_npcexp(string arg);
int get_npcmsgchat(string arg);
int get_npcskill(string arg);
int get_npcmap(string arg);
int get_npcprepare(string arg);
int get_npcweapon(string arg);
int get_itemname(string arg);
int get_itemid(string arg);
int get_itemdescribe(string arg);
string convert_dir(string dir);
int insert_string(string this_filename,string mark,string str,string over_mark);//在this_filename中寻找一次mark，以str替换之，遇到over_mark替换停止。
int delete_dir(string this_filename,string dir);
int change_string(string this_filename,string mark,string str);//在this_filename中寻找以mark为格式(只含有一个%S)的行，并将此行替换成str
int is_granted(object player);
string shortname,longname,filename;
string *banned_id = ({
    "none","donkey","halt","save","hitall","sleep","guest","letter","paper",
});
string *banned_name = ({
	"你", "我", "他", "她", "它", "自己", "云开颜",
        "江泽民","三个代表","共产党","邓小平","毛泽东","胡锦涛","三讲",
        "萧峰", "乔峰", "慕容博", "慕容复", "王语嫣", "张无忌",
        "无名", "东方不败", "李逍遥", "金庸","风清扬","冰冰",
        "岳不群", "宁中则", "岳灵珊", "令狐冲", "张三丰", "洪七公",
        "丁春秋", "鲁有脚", "彭有敬", "宋远桥", "俞莲舟", "张松溪","柳残阳",
        "欧阳锋", "欧阳克", "黄药师", "黄蓉", "郭靖", "杨过", "小龙女","宋青书的剑","珍珠项链",
        });
mapping valid_types = 
([
	"finger":   "指法",
	"hand" :     "手法",
	"cuff":     "拳法",
	"claw":     "爪法",
	"strike":   "掌法",
    "throwing": "暗器",
    "unarmed":   "基本拳脚",
	"blade":   "刀法",
	"sword":   "剑法",
	"whip":"鞭法",
	"spear":"枪法",
]);
void init()
{
	set("canexpand",1);
	add_action("do_cut","cut");
	add_action("do_maken","maken");
	add_action("do_makes","makes");
	add_action("do_makew","makew");
	add_action("do_makee","makee");
	add_action("do_makenw","makenw");
	add_action("do_makene","makene");
	add_action("do_makesw","makesw");
	add_action("do_makese","makese");
	add_action("do_enter","makeenter");
	add_action("do_out","makeout");
	add_action("do_makenu","makenu");
	add_action("do_makend","makend");
	add_action("do_makesu","makesu");
	add_action("do_makesd","makesd");
	add_action("do_makewu","makewu");
	add_action("do_makewd","makewd");
	add_action("do_makeeu","makeeu");
	add_action("do_makeed","makeed");
	add_action("do_link","link");
	add_action("do_makeup","makeu");
	add_action("do_maked","maked");
	add_action("do_del","del");
	add_action("do_help","help");
	add_action("do_add_describe","add_describe");
	add_action("do_del_describe","del_describe");
	add_action("do_create_npc","create_npc");
	add_action("do_create_item","create_item");

}
int do_create_item(string arg)
{
	int filelength;
	string sample_filename,sample_file,this_file;
	object me;
	me=this_player();
//	if(!is_granted(me)) return notify_fail("你没有被授权!\n");
	if(!__DIR__"userchecker.c"->is_granted(me)) return notify_fail("你没有被授权!\n");
	if(!arg) return notify_fail("请你在create_npc 后面加上文件名！\n");
	filelength=strwidth(arg);
	if(file_size(__DIR__+"obj")!=-2)
	{
		mkdir(__DIR__+"obj");
	}
	if(filelength<2)
	{
		tell_object(me,HIW"对不起，你输入的文件名太短了!\n"NOR);
		return 1;
	}
	while(filelength--)
	{
		if(arg[filelength]<='9'&&arg[filelength]>='0') continue;
		if(arg[filelength]<'a'||arg[filelength]>'z')
		{
			tell_object(me,HIW"请用英文和数字做文件名!\n"NOR);
			return 1;
		}
	}
	sample_filename="/u/mudy/sampleitem.c";
	if(file_size(sample_filename)<0)
	{
		sample_filename=__DIR__+"sampleitem.c";
		if(file_size(sample_filename)<0)
		{
			tell_object(me,"样本文件丢失!\n");
			return 1;
		}
	}
	filename=__DIR__+"obj/"+arg;
	if(sscanf(filename,"%s.c",this_file)!=1)
		filename=filename+".c";
	if(file_size(filename)>0) 
	{
		tell_object(me,"此文件已存在，且不为空，请更换文件名！\n");
		return 1;
	}
	sample_file=read_file(sample_filename);
	write_file(filename,sample_file,1);
	insert_string(file_name(this_object())+".c","//OBJECT","\""+filename+"\" : 1,","//OVEROBJECT");
	change_string(filename,"//Created by%s","//Created by "+me->query("id"));
	tell_object(me,HIW"请输入物品的名字：\n"NOR);
	input_to((:get_itemname:));
	return 1;
}
int get_itemname(string arg)
{
	object me;
	int i;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"请输入物品的名字:\n"NOR+arg);
		input_to("get_itemname",me);
		return 1;
	}
	i = strwidth(arg);
	if( i < 1 || i > 10  )
	{
		tell_object(me,HIW"对不起，物品的名字必须是 1 到 １０ 个中文字。\n"NOR);
		input_to("get_itemname",me);
		return 1;
	}
	while(i--) {
		if( arg[i]<=' ' ) {
			tell_object(me,HIW"物品的名字不能用控制字元。\n"NOR);
			input_to("get_itemname",me);
			return 1;
		}
		if( !is_chinese(arg[i..<0]) ) {
			tell_object(me,HIW"对不起，请您用「中文」取名字。\n"NOR);
			input_to("get_itemname",me);
			return 1;
		}
	}
	if( member_array(arg, banned_name)!=-1 ) {
		tell_object(me,HIW"这种名字会造成其他人的困扰。请重新输入!\n"NOR);
		input_to("get_itemname",me);
		return 1;
	}
	change_string(filename,"/*ITEM_NAME*/%s","/*ITEM_NAME*/set_name(\""+arg+"\"");
	tell_object(me,HIW"请输入物品的id：\n"NOR);
	input_to((:get_itemid:));
	return 1;
}

int get_itemid(string arg)
{
	int i,sign;
	object me;
	string idstr,*ids;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"请输入物品的id：\n"NOR);
		input_to((:get_itemid:));
		return 1;
	}
	i=strwidth(arg);
	if(i<2)
	{
		tell_object(me,HIW"对不起，你输入物品的id太短了，请重新输入!\n"NOR);
		input_to((:get_itemid:));
		return 1;
	}
	sign=0;
	while(i--)
	{
		if(arg[i]==',') continue;
		if(arg[i]==' ') continue;
		if(arg[i]<'a'||arg[i]>'z')
		{
			tell_object(me,HIW"请用英文做id!\n"NOR);
			input_to((:get_itemid:));
			return 1;
		}
		sign=1;
	}
	if(sign==0)
	{
		tell_object(me,HIW"怎么能全部是逗号呢？\n"NOR);
		input_to((:get_itemid:));
		return 1;
	}
    if( member_array( arg, banned_id ) != -1 )
    {
        tell_object(me,"这个ＩＤ会引起不必要的麻烦。\n");
		input_to((:get_itemid:));
        return 1;
    }
	ids=explode(arg,",");
	idstr="";
	for(i=0;i<sizeof(ids);i++)
	{
		idstr=idstr+"\""+ids[i]+"\", ";
	}
	change_string(filename,"/*ITEM_ID*/%s",idstr);
	tell_object(me,HIW"请输入物品的描述(直接回车取消。):\n"NOR);
	input_to((:get_itemdescribe:));
	return 1;
}

int get_itemdescribe(string arg)
{
	object me,obj;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"物品创建成功！\n"NOR);
		obj=new(filename);
		obj->move(this_object());
		return 1;
	}
	insert_string(filename,"//LONG","/*LONG*/+\""+arg+"\\n\"","//OVERLONG");
	tell_object(me,HIW"(直接回车表示结束。)：\n"NOR);
	input_to((:get_itemdescribe:));
	return 1;
}
int do_create_npc(string arg)
{
	string sample_filename,sample_file,this_file;
	object me;
	int filelength;
	me=this_player();
	if(!__DIR__"userchecker.c"->is_granted(me)) return notify_fail("你没有被授权!\n");
	if(!arg) return notify_fail("请你在create_npc 后面加上文件名！\n");
	filelength=strwidth(arg);
	if(file_size(__DIR__+"npc")!=-2)
	{
		mkdir(__DIR__+"npc");
	}
	if(filelength<2)
	{
		tell_object(me,HIW"对不起，你输入的文件名太短了!\n"NOR);
		return 1;
	}
	while(filelength--)
	{
		
		if(arg[filelength]<='9'&&arg[filelength]>='0') continue;
		if(arg[filelength]<'a'||arg[filelength]>'z')
		{
			tell_object(me,HIW"请用英文和数字做文件名!\n"NOR);
			return 1;
		}
	}
	sample_filename="/u/mudy/samplenpc.c";
	if(file_size(sample_filename)<0)
	{
		sample_filename=__DIR__+"samplenpc.c";
		if(file_size(sample_filename)<0)
		{
			tell_object(me,"样本文件丢失!\n");
			return 1;
		}
	}
	filename=__DIR__+"npc/"+arg;
	if(sscanf(filename,"%s.c",this_file)!=1)
		filename=filename+".c";
	if(file_size(filename)>0) 
	{
		tell_object(me,"此文件已存在，且不为空，请更换文件名！\n");
		return 1;
	}
	sample_file=read_file(sample_filename);
	write_file(filename,sample_file,1);
	insert_string(file_name(this_object())+".c","//OBJECT","\""+filename+"\" : 1,","//OVEROBJECT");
	change_string(filename,"//Created by%s","//Created by "+me->query("id"));
	tell_object(me,HIW"请输入NPC的姓名:\n"NOR);
	input_to((:get_npcname:));
	return 1;
}
int get_npcname(string arg)
{
	object me;
	int i;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"请输入NPC的姓名:\n"NOR+arg);
		input_to("get_npcname",me);
		return 1;
	}
	i = strwidth(arg);
	if( i <1|| i > 7  )
	{
		tell_object(me,HIW"对不起，NPC的中文名字必须是 1 到 7 个中文字。\n"NOR);
		input_to("get_npcname",me);
		return 1;
	}
	while(i--) {
		if( arg[i]<=' ' ) {
			tell_object(me,HIW"NPC的中文名字不能用控制字元。\n"NOR);
			input_to("get_npcname",me);
			return 1;
		}
		if( !is_chinese(arg[i..<0]) ) {
			tell_object(me,HIW"对不起，请您用「中文」取名字。\n"NOR);
			input_to("get_npcname",me);
			return 1;
		}
	}
	if( member_array(arg, banned_name)!=-1 ) {
		tell_object(me,HIW"这种名字会造成其他人的困扰。请重新输入!\n"NOR);
		input_to("get_npcname",me);
		return 1;
	}
	if(CNAME_D->query_cname(arg)==1)
	{
		tell_object(me,HIW"这个名字是某一个玩家的名字，请换用其他的中文名字。\n"NOR);
		input_to("get_npcname",me);
		return 1;
	}
	change_string(filename,"/*NAME*/%s","/*NAME*/set_name(\""+arg+"\"");
	tell_object(me,HIW"请输入NPC的id：\n"NOR);
	input_to((:get_npcid:));
	return 1;
}
int get_npcid(string arg)
{
	int i,sign;
	object me;
	string idstr,*ids;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"请输入NPC的id：\n"NOR);
		input_to((:get_npcid:));
		return 1;
	}
	i=strwidth(arg);
	if(i<2)
	{
		tell_object(me,HIW"对不起，你输入NPC的id太短了，请重新输入!\n"NOR);
		input_to((:get_npcid:));
		return 1;
	}
	sign=0;
	while(i--)
	{
		if(arg[i]==',') continue;
		if(arg[i]==' ') continue;
		if(arg[i]<'a'||arg[i]>'z')
		{
			tell_object(me,HIW"请用英文名做id!\n"NOR);
			input_to((:get_npcid:));
			return 1;
		}
		sign=1;
	}
	if(sign==0)
	{
		tell_object(me,HIW"怎么能全部是逗号呢？\n"NOR);
		input_to((:get_npcid:));
		return 1;
	}
    if( member_array( arg, banned_id ) != -1 )
    {
        tell_object(me,"这个ＩＤ会引起不必要的麻烦。\n");
		input_to((:get_npcid:));
        return 1;
    }
	ids=explode(arg,",");
	idstr="";
	for(i=0;i<sizeof(ids);i++)
	{
		idstr=idstr+"\""+ids[i]+"\", ";
	}
	change_string(filename,"/*ID*/%s",idstr);
	tell_object(me,HIW"请输入NPC的头衔(直接回车取消。):\n"NOR);
	input_to((:get_npctitle:));
	return 1;
}
int get_npctitle(string arg)
{
	object me;
	int i;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"请输入NPC的昵称(直接回车取消。)：\n"NOR);
		input_to((:get_npcnickname:));
		return 1;
	}
	i = strwidth(arg);
	if( i < 1 || i > 10  )
	{
		tell_object(me,HIW"对不起，NPC的头衔必须是 1 到 １０ 个中文字。\n"NOR);
		input_to((:get_npctitle:));
		return 1;
	}
	while(i--) {
		if( arg[i]<=' ' ) {
			tell_object(me,HIW"NPC的头衔名字不能用控制字元。\n"NOR);
			input_to((:get_npctitle:));
			return 1;
		}
		if(!is_chinese(arg[i..<0]) ) {
			tell_object(me,HIW"对不起，请您用「中文」取头衔。\n"NOR);
			input_to((:get_npctitle:));
			return 1;
		}
	}
	change_string(filename,"//TITLE%s","/*TITLE*/ set(\"title\",\""+arg+"\");");
	tell_object(me,HIW"请输入NPC的昵称(直接回车取消。)：\n"NOR);
	input_to((:get_npcnickname:));
	return 1;
}
int get_npcnickname(string arg)
{
	object me;
	int i;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"请输入NPC的描述(直接回车表示结束。)：\n"NOR);
		input_to((:get_npcdescribe:));
		return 1;
	}
	i = strwidth(arg);
	if( i < 1 || i > 10  )
	{
		tell_object(me,HIW"对不起，NPC的昵称必须是 1 到 １０ 个中文字。\n"NOR);
		input_to("get_npcnickname",me);
		return 1;
	}
	while(i--) {
		if( arg[i]<=' ' ) {
			tell_object(me,HIW"NPC的昵称名字不能用控制字元。\n"NOR);
			input_to("get_npcnickname",me);
			return 1;
		}
		if( !is_chinese(arg[i..<0]) ) {
			tell_object(me,HIW"对不起，请您用「中文」取昵称。\n"NOR);
			input_to("get_npcnickname",me);
			return 1;
		}
	}
	change_string(filename,"//NICKNAME%s","/*NICKNAME*/ set(\"nickname\",\""+arg+"\");");
	tell_object(me,HIW"请输入NPC的描述(直接回车表示结束。)：\n"NOR);
	input_to((:get_npcdescribe:));
	return 1;
}
int get_npcdescribe(string arg)
{
	object me;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"请输入NPC的性别(默人表示男性。)男／女：\n"NOR);
		input_to((:get_npcgender:));
		return 1;
	}
	insert_string(filename,"//DESCRIBE","/*DESCRIBE*/+\""+arg+"\\n\"","//OVERDESCRIBE");
	tell_object(me,HIW"(直接回车表示结束。)：\n"NOR);
	input_to((:get_npcdescribe:));
	return 1;
}
int get_npcgender(string arg)
{
	object me;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object(me,HIW"请输入NPC的年龄(默认为40):\n"NOR);
		input_to((:get_npcage:));
		return 1;
	}
	if(arg!="男"&&arg!="女"&&arg!="男性"&&arg!="女性")
	{
		tell_object(me,HIW"请输入NPC的性别(默人表示男性。)男／女：\n"NOR);
		input_to((:get_npcgender:));
		return 1;
	}
	if(arg=="男"||arg=="男性")
	{
		change_string(filename,"/*GENDER*/%s","/*GENDER*/  set(\"gender\",\"男性\");");
	}
	else
	{
		change_string(filename,"/*GENDER*/%s","/*GENDER*/  set(\"gender\",\"女性\");");
	}
	tell_object(me,HIW"请输入NPC的年龄(默认为40):\n"NOR);
	input_to((:get_npcage:));
	return 1;
}
int get_npcage(string arg)
{
	object me;
	int age;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的先天臂力(20~50):\n"NOR);
		input_to((:get_npcstr:));
		return 1;
	}
	if(sscanf(arg,"%d",age)!=1)
	{
		tell_object(me,HIW"请输入NPC的年龄(默认为40):\n"NOR);
		input_to((:get_npcage:));
		return 1;
	}
	if(age<1||age>150)
	{
		tell_object(me,HIW"请输入NPC的年龄(1~150岁):\n"NOR);
		input_to((:get_npcage:));
		return 1;
	}
	change_string(filename,"/*AGE*/%s","/*AGE*/ set(\"age\","+age+");");
	tell_object( me,HIW"请输入NPC的先天臂力(20~50):\n"NOR);
	input_to((:get_npcstr:));
	return 1;
}
int get_npcstr(string arg)
{
	object me;
	int str;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的先天悟性(20~50):\n"NOR);
		input_to((:get_npcint:));
		return 1;
	}
	if(sscanf(arg,"%d",str)!=1)
	{
		tell_object(me,HIW"请输入NPC的先天臂力(20~50):\n"NOR);
		input_to((:get_npcstr:));
		return 1;
	}
	if(str<20||str>50)
	{
		tell_object(me,HIW"请输入NPC的先天臂力(20~50):\n"NOR);
		input_to((:get_npcstr:));
		return 1;
	}
	change_string(filename,"/*STR*/%s","/*STR*/ set(\"str\","+str+");");
	tell_object( me,HIW"请输入NPC的先天悟性(20~50):\n"NOR);
	input_to((:get_npcint:));
	return 1;
}

int get_npcint(string arg)
{
	object me;
	int wuxing;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的先天根骨(20~50):\n"NOR);
		input_to((:get_npccon:));
		return 1;
	}
	if(sscanf(arg,"%d",wuxing)!=1)
	{
		tell_object(me,HIW"请输入NPC的先天悟性(20~50):\n"NOR);
		input_to((:get_npcint:));
		return 1;
	}
	if(wuxing<20||wuxing>50)
	{
		tell_object(me,HIW"请输入NPC的先天悟性(20~50):\n"NOR);
		input_to((:get_npcint:));
		return 1;
	}
	change_string(filename,"/*INT*/%s","/*INT*/ set(\"int\","+wuxing+");");
	
	return 1;
}
int get_npccon(string arg)
{
	object me;
	int con;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的先天身法(20~50):\n"NOR);
		input_to((:get_npcdex:));
		return 1;
	}
	if(sscanf(arg,"%d",con)!=1)
	{
		tell_object(me,HIW"请输入NPC的先天根骨(20~50):\n"NOR);
		input_to((:get_npccon:));
		return 1;
	}
	if(con<20||con>50)
	{
		tell_object(me,HIW"请输入NPC的先天根骨(20~50):\n"NOR);
		input_to((:get_npccon:));
		return 1;
	}
	change_string(filename,"/*CON*/%s","/*CON*/ set(\"con\","+con+");");
	tell_object( me,HIW"请输入NPC的先天身法(20~50):\n"NOR);
	input_to((:get_npcdex:));
	return 1;
}
int get_npcdex(string arg)
{
	object me;
	int dex;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的气(100~10000):\n"NOR);
		input_to((:get_npcmaxqi:));
		return 1;
	}
	if(sscanf(arg,"%d",dex)!=1)
	{
		tell_object(me,HIW"请输入NPC的先天身法(20~50):\n"NOR);
		input_to((:get_npcdex:));
		return 1;
	}
	if(dex<20||dex>50)
	{
		tell_object(me,HIW"请输入NPC的先天身法(20~50):\n"NOR);
		input_to((:get_npcdex:));
		return 1;
	}
	change_string(filename,"/*DEX*/%s","/*DEX*/ set(\"dex\","+dex+");");
	tell_object( me,HIW"请输入NPC的气(100~10000):\n"NOR);
	input_to((:get_npcmaxqi:));
	return 1;
}

int get_npcmaxqi(string arg)
{
	object me;
	int value;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的精(100~10000):\n"NOR);
		input_to((:get_npcmaxjing:));
		return 1;
	}
	if(sscanf(arg,"%d",value)!=1)
	{
		tell_object(me,HIW"请输入NPC的气(100~10000):\n"NOR);
		input_to((:get_npcmaxqi:));
		return 1;
	}
	if(value<100||value>10000)
	{
		tell_object(me,HIW"请输入NPC的气(100~10000):\n"NOR);
		input_to((:get_npcmaxqi:));
		return 1;
	}
	change_string(filename,"/*MAX_QI*/%s","/*MAX_QI*/ set(\"max_qi\","+value+");");
	tell_object( me,HIW"请输入NPC的精(100~10000):\n"NOR);
	input_to((:get_npcmaxjing:));
	return 1;
}

int get_npcmaxjing(string arg)
{
	object me;
	int value;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的内力(0~6000):\n"NOR);
		input_to((:get_npcmaxneili:));
		return 1;
	}
	if(sscanf(arg,"%d",value)!=1)
	{
		tell_object(me,HIW"请输入NPC的精(100~10000):\n"NOR);
		input_to((:get_npcmaxjing:));
		return 1;
	}
	if(value<100||value>10000)
	{
		tell_object(me,HIW"请输入NPC的精(100~10000):\n"NOR);
		input_to((:get_npcmaxjing:));
		return 1;
	}
	change_string(filename,"/*MAX_JING*/%s","/*MAX_JING*/ set(\"max_jing\","+value+");");
	tell_object( me,HIW"请输入NPC的内力(0~6000):\n"NOR);
	input_to((:get_npcmaxneili:));
	return 1;
}
int get_npcmaxneili(string arg)
{
	object me;
	int value;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的加力(0~300):\n"NOR);
		input_to((:get_npcjiali:));
		return 1;
	}
	if(sscanf(arg,"%d",value)!=1)
	{
		tell_object(me,HIW"请输入NPC的内力(0~6000):\n"NOR);
		input_to((:get_npcmaxneili:));
		return 1;
	}
	if(value<0||value>6000)
	{
		tell_object(me,HIW"请输入NPC的内力(0~6000):\n"NOR);
		input_to((:get_npcmaxneili:));
		return 1;
	}
	change_string(filename,"/*MAX_NEILI*/%s","/*MAX_NEILI*/ set(\"max_neili\","+value+");");
	change_string(filename,"/*NEILI*/%s","/*NEILI*/ set(\"neili\","+value+");");
	tell_object( me,HIW"请输入NPC的加力(0~300):\n"NOR);
	input_to((:get_npcjiali:));
	return 1;
}

int get_npcjiali(string arg)
{
	object me;
	int value;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的经验(0~10000000):\n"NOR);
		input_to((:get_npcexp:));
		return 1;
	}
	if(sscanf(arg,"%d",value)!=1)
	{
		tell_object(me,HIW"请输入NPC的加力(0~300):\n"NOR);
		input_to((:get_npcjiali:));
		return 1;
	}
	if(value<0||value>300)
	{
		tell_object(me,HIW"请输入NPC的加力(0~300):\n"NOR);
		input_to((:get_npcjiali:));
		return 1;
	}
	change_string(filename,"/*JIALI*/%s","/*JIALI*/ set(\"jiali\","+value+");");
	tell_object( me,HIW"请输入NPC的经验(0~10000000):\n"NOR);
	input_to((:get_npcexp:));
	return 1;
}

int get_npcexp(string arg)
{
	object me;
	int value;
	me=this_player();
	if(sscanf(arg,"%d",value)!=1)
	{
		tell_object(me,HIW"请输入NPC的经验(0~10000000):\n"NOR);
		input_to((:get_npcexp:));
		return 1;
	}
	if(value<0||value>10000000)
	{
		tell_object(me,HIW"请输入NPC的经验(0~10000000):\n"NOR);
		input_to((:get_npcexp:));
		return 1;
	}
	change_string(filename,"/*EXP*/%s","/*EXP*/ set(\"combat_exp\","+value+");");
	tell_object( me,HIW"请输入NPC平时发呆时所说的语言（直接输入回车表示结束）:\n"NOR);
	input_to((:get_npcmsgchat:));
	return 1;
}
int get_npcmsgchat(string arg)
{
	object me;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的掌握的技能和级数(eg.parry,50)直接回车表示结束:\n"NOR);
		input_to((:get_npcskill:));
		return 1;
	}
	insert_string(filename,"//MSG_CHAT","/*MSG_CHAT*/\""+arg+"\",","//OVERMSG_CHAT");
	tell_object(me,HIW"请输入本NPC的下一条语言（直接输入回车表示结束）：\n"NOR);
	input_to((:get_npcmsgchat:));
	return 1;
}
int get_npcskill(string arg)
{
	int level;
	string skill;
	object me;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC的激发的武功(eg.parry,taiji-quan)直接回车表示结束:\n"NOR);
		input_to((:get_npcmap:));
		return 1;
	}
	if(sscanf(arg,"%s,%d",skill,level)!=2)
	{
		tell_object( me,HIW"请按格式：parry,50 输入NPC的掌握的技能和级数(直接回车表示结束):\n"NOR);
		input_to((:get_npcskill:));
		return 1;
	}
	if(level>450||level<1)
	{
		tell_object( me,HIW"武功的级数不能小于1级大于450级:\n"NOR);
		input_to((:get_npcskill:));
		return 1;
	}
	if(file_size("/kungfu/skill/"+skill+".c")<1)
	{
		tell_object( me,HIW"哪里存在这种武功？\n"NOR);
		input_to((:get_npcskill:));
		return 1;
	}
	insert_string(filename,"//SKILL","/*SKILL*/  set_skill(\""+skill+"\","+level+");","//OVERSKILL");
	add("npc",([skill:level]));
	tell_object( me,HIW"请输入NPC的掌握的技能和级数(eg.parry,50)直接回车表示结束:\n"NOR);
	input_to((:get_npcskill:));
	return 1;
}
int get_npcmap(string arg)
{
	string base_skill,advance_skill,*skills;
	object me;
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC打斗时用的武功(eg.taiji-quan)直接回车表示结束:\n"NOR);
		input_to((:get_npcprepare:));
		return 1;
	}
	if(sscanf(arg,"%s,%s",base_skill,advance_skill)!=2)
	{
		tell_object( me,HIW"请按格式：parry,taiji-quan输入NPC激发的武功！（直接回车表示结束）:\n"NOR);
		input_to((:get_npcmap:));
		return 1;
	}
	skills=keys(query("npc"));
    if( member_array( base_skill, skills ) == -1 )
    {
        tell_object(me,HIW"这个NPC不会"+base_skill+"!。\n"NOR);
		input_to((:get_npcmap:));
        return 1;
    }
    if( member_array( advance_skill, skills ) == -1 )
    {
        tell_object(me,HIW"这个NPC不会"+advance_skill+"!。\n"NOR);
		input_to((:get_npcmap:));
        return 1;
    }
	if( !SKILL_D(advance_skill)->valid_enable(base_skill) )
	{
		tell_object(me,HIW+to_chinese(advance_skill)+"不能激发成"+to_chinese(base_skill)+"!\n"NOR);
		input_to((:get_npcmap:));
		return 1;
	}
	insert_string(filename,"//MAP","/*MAP*/   map_skill(\""+base_skill+"\",\""+advance_skill+"\");","//OVERMAP");
	add("npcmap",([base_skill:advance_skill]));
	tell_object( me,HIW"请输入下一个NPC的激发的武功(eg.parry,taiji-quan)直接回车表示结束:\n"NOR);
	input_to((:get_npcmap:));
	return 1;
}
int get_npcprepare(string arg)
{
	string *skills,basic,*valid_base;
	int i;
	mapping npcmap;
	object me;
	valid_base=({
		"finger","hand","cuff","claw","strike","throwing","unarmed","blade","sword","whip","spear",
	});
	me=this_player();
	if(!arg||arg=="")
	{
		tell_object( me,HIW"请输入NPC所拿的兵器：钢刀/长剑／钢杖/方天画戟/飞镖/长枪/长鞭/直接回车表示不拿任何武器:\n"NOR);
		input_to((:get_npcweapon:));
		return 1;
	}
	skills=keys(query("npc"));
    if( member_array( arg, skills ) == -1 )
    {
        tell_object(me,HIW"这个NPC不会"+arg+"!。\n"NOR);
		input_to((:get_npcprepare:));
        return 1;
    }
//	skills=keys(valid_types);
	npcmap=query("npcmap");
	for(i=0;sizeof(valid_base);i++)
	{
		//if(query("npcmap/"+skills[i])==arg) basic=skills[i];
		if(npcmap[valid_base[i]]==arg)
		{
			basic=valid_base[i];
			tell_object(me,valid_base[i]+"\n");
			break;
		}
	}
	if(!basic)
	{
		tell_object(me,HIW"本技能不能准备或此NPC没有激发！\n"NOR);
		input_to((:get_npcprepare:));
		return 1;
	}
	if(i<=6)
		insert_string(filename,"//PREPARE","/*PREPARE*/   prepare_skill(\""+basic+"\",\""+arg+"\");","//OVERPREPARE");
	else
		insert_string(filename,"//PREPARE","/*PREPARE*/   prepare_wskill(\""+basic+"\",\""+arg+"\");","//OVERPREPARE");

	
	tell_object( me,HIW"请输入NPC打斗时用的武功(eg.taiji-quan)直接回车表示结束:\n"NOR);
	input_to((:get_npcprepare:));
	return 1;
}
int get_npcweapon(string arg)
{
	object npc,me;
	me=this_player();
	if(!arg||arg=="")
	{
	}
	else if(arg=="钢刀")
	{
		change_string(filename,"//WEAPON%s","/*WEAPON*/  carry_object(\"/clone/weapon/gangdao.c\")->wield();");
	}
	else if(arg=="长剑")
	{
		change_string(filename,"//WEAPON%s","/*WEAPON*/  carry_object(\"/clone/weapon/changjian.c\")->wield();");
	}
	else if(arg=="钢杖")
	{
		change_string(filename,"//WEAPON%s","/*WEAPON*/  carry_object(\"/clone/weapon/gangzhang.c\")->wield();");
	}
	else if(arg=="长鞭")
	{
		change_string(filename,"//WEAPON%s","/*WEAPON*/  carry_object(\"/clone/weapon/changbian.c\")->wield();");
	}
	else if(arg=="方天画戟")
	{
		change_string(filename,"//WEAPON%s","/*WEAPON*/  carry_object(\"/clone/weapon/fangtianji.c\")->wield();");
	}
	else if(arg=="飞镖")
	{
		change_string(filename,"//WEAPON%s","/*WEAPON*/  carry_object(\"/clone/weapon/dart.c\")->wield();");
	}
	else
	{
		tell_object( me,HIW"可以输入的兵器有：钢刀/长剑／钢杖/方天画戟/飞镖/长枪/长鞭/直接回车表示不拿任何武器:\n"NOR);
		input_to((:get_npcweapon:));
		return 1;
	}
	tell_object( me,HIW"NPC创建成功！\n"NOR);
	npc=new(filename);
	npc->move(this_object());
	return 1;
}
int do_del_describe(string arg)
{
	if(!__DIR__"userchecker.c"->is_granted(this_player())) return notify_fail("你没有被授权!\n");
	change_string(file_name(this_object())+".c","/*DESCRIBE*/%s","//DESCRIBE");
	set("long","");
	tell_object(this_player(),HIW"本房间所有描述信息全部删除!\n"NOR);
	return 1;
}
int do_add_describe(string arg)
{
	if(!__DIR__"userchecker.c"->is_granted(this_player())) return notify_fail("你没有被授权!\n");
	if(!arg) return notify_fail("请输入你想给本房间添加的信息！\n");
	insert_string(file_name(this_object())+".c","//DESCRIBE","/*DESCRIBE*/\""+arg+"\\n\"","//OVERDESCRIBE");
	set("long",query("long")+arg+"\n");
	tell_object(this_player(),HIW"信息成功添加!\n"NOR);
	return 1;
}/*
int is_granted(object me)
{
	if(me->query("id")=="mudy"||me->query("id")=="male")
		return 1;
	else
		return 0;
}*/
int do_help(string arg)
{
	object me;
	me=this_player();
if(SECURITY_D->get_status(me)== "(admin)")
{
tell_object(me,
HIY"　　　  　地图扩充系统
系统说明：
sample\samplenpc\sampleitem三个文件是模板文件
，请慎重在里面做任何操作！你可以将sample重命
名为其他文件做为种子，在种子房间中来发展地图。
userchecker为检查器
负责判断使用者是否被授权，授权命令:

grant: 赋予某个玩家永久开辟权力；
tempgrant: 赋予玩家暂时开辟权力；

ungrant: 剥夺玩家所有开辟权力；
"NOR);
}
else
{
	tell_object(me,
"　　　　　　　　地图扩充系统
系统说明：
这个系统旨在发挥所有人的创造性来尽可能地扩充我们
的mud世界，任何有兴趣为mud作出贡献的玩家都可以到
天神出要求赋予开辟地图的权力，开始您会被赋予临时
开辟权，（每一次赋予，会给你１０次操作的机会，）
如果你确实做的比较好，就可以在天神处得到开辟地图
的永久权！知道天神剥夺为止，在这里要事先声明，天神
负有管理整个mud协调性的责任，所以如果认为你创造的
地图拥不符合本mud的总体思路，拥有修改或删除您所写
的地图的权力，请您谅解！");
}
tell_object(this_player(),
"\n\n用法：
make系列：输入make* 文件名　之后会提示你输入房
间名和房间描述。这时就会出现相应方向的时间，其
文件保存在种源房间同一个目录下。

link 命令：在你相连接的一个房间输入：link 方向
<north\south\southeast....>之后，到另一个房间
输入link，之后两个房间就会相连。\n");
tell_object(this_player(),
"
del 命令：输入del 方向，即会删除该方向上的路径，
于此路径相连的两个房间将会割断。此时如果另外一间
房屋中没有路径与其相连，则房间内所有的npc和物品
都将被删除！

cut 命令：通过上述方法产生的房间，是一种有特殊
功能的房间，要想使其成为普通房间，即去除上述命令
的功能，当在此房间中使用此命令。<此命令只有天神
才能使用>\n");
tell_object(this_player(),
"
add_describe命令：<add_describe 描述内容>此命令
将会在该房间的描述中加入一行描述内容．

del_describe命令：此命令将清除该房间所有的描述，
以便重写．\n");

tell_object(this_player(),
"
create_npc命令，此命令将在该房间加入一个NPC，你需
要在其后确定NPC的诸多参数，按提示输入即可这些参数
一旦确定无法更改！想更改的唯一途径就是利用del命令，
删除与该房间相联系的文件，从而删除该NPC，然后重写．

create_item命令，此命令将给该房间加入一个物品，该
物品没有任何特殊用途，只是需要你给其确定名字、ID、
描述而已。\n");
tell_object(this_player(),
"
补充说明：
makee　 向东创建一个房间；　  makenw　向西北创建一个房间；
makes 　向南创建一个房间；  　makene　向东北创建一个房间；
makew 　向西创建一个房间；  　makesw　向西南创建一个房间；
maken　 向北创建一个房间；  　makese　向东南创建一个房间；
makenu　向北上创建一个房间；　makend　向北下创建一个房间；
makesu　向南上创建一个房间；　makesd　向南下创建一个房间；
makewu　向西上创建一个房间；　makewd　向西下创建一个房间；
makeeu　向东上创建一个房间；　makeed　向东下创建一个房间；
makeu　 向上创建一个房间；  　maked　 向下创建一个房间；
makeout 向外创建一个房间； makeenter  向里创建一个房间；
");
tell_object(me,"\n\n\n             　　　　　　　　　　　　  mudy 11-21-02\n");
return 1;
}

int do_del(string arg)
{
	string this_filename,that_filename,*objects,npcfile;
	object to_room;
	this_filename=file_name(this_object())+".c";
	if(!__DIR__"userchecker.c"->is_granted(this_player())) return notify_fail("你没有被授权!\n");
	if(!arg) return notify_fail("请加入你要del的路径：del dir!\n");
	if(!query("exits/"+arg)) return notify_fail("这里没有这一条路径!\n");
	to_room=load_object(query("exits/"+arg));
	if(!to_room)
	{
		change_string(this_filename,"\""+arg+"\"%s","//EXIT");
		return notify_fail("路径那一头的房间已经不在了！\n");
	}
	if(!to_room->query("canexpand")) return notify_fail("这条路径不属于本系统，不能删除!\n");
	if(sizeof(this_object()->query("exits"))==1&&file_name(this_object())!=__DIR__+"sample") return notify_fail("再删这里就没有路径了!\n");
	change_string(this_filename,"\""+arg+"\"%s","//EXIT");
	that_filename=file_name(to_room)+".c";
	change_string(that_filename,"\""+convert_dir(arg)+"\"%s","//EXIT");
	delete("exits/"+arg);
	to_room->delete("exits/"+convert_dir(arg));
	tell_object(this_object(),HIW"路径成功删除!\n"NOR);
	if(sizeof(to_room->query("exits"))<1)
	{
		objects=keys(load_object(that_filename)->query("objects"));
		for(int i=0;i<sizeof(objects);i++)
		{
			if(load_object(objects[i])->query("canexpand"))
			{
				rm(objects[i]);
			}
		}
		rm(that_filename);
		tell_object(this_player(),"由于"+to_room->query("short")+"没有出口，已经被删除了!(与其相关联的npc和物品也将被删除！)\n");
	}
	return 1;
}
int change_string(string this_filename,string mark,string str)
{
	string *line,*des_line,this_file,remainder;
	int i;
	this_file=read_file(this_filename);
	if(!this_file) 
	{
		tell_object(this_player(),"read error!\n");
		return 1;
	}
		des_line=({});
		line=explode(this_file,"\n");
		for(i=0;i<sizeof(line);i++)
		{
			if(sscanf(line[i],mark,remainder)==1)
			{
				des_line+=({str});
				continue;
			}
			des_line+=({line[i]});
		}
		this_file=implode(des_line,"\n");
		write_file(this_filename,this_file,1);
	return 1;
}

int do_link(string arg)
{
	object me;
	string this_filename,from_filename,link_dir;
	me=this_player();
	if(!__DIR__"userchecker.c"->is_granted(this_player())) return notify_fail("你没有被授权!\n");
	if(arg)
	{
		this_filename=file_name(this_object())+".c";
		me->set_temp("makeroom/filename",this_filename);
		me->set_temp("makeroom/dir",arg);
		tell_object(me,HIW"你预备从这里往"+arg+"连到哪里呢？\n请在要连的地方在下一次link命令!\n"NOR);
		return 1;
	}
	else
	{
		from_filename=me->query_temp("makeroom/filename");
		link_dir=me->query_temp("makeroom/dir");
		if(!from_filename||!link_dir)
		{
			tell_object(me,HIW"请先在房间里用link dir命令指出你想从那个房间往哪个方向连!\n"NOR);
			return 1;
		}
		if(file_size(from_filename)<0)
		{
			tell_object(me,HIW"请重新用link dir命令，你先前指定的地方已经不存在了！\n");
			return 1;
		}
		this_filename=file_name(this_object())+".c";
		insert_string(from_filename,"//EXIT","\""+link_dir+"\" : \""+this_filename+"\",","//OVER");
		insert_string(this_filename,"//EXIT","\""+convert_dir(link_dir)+"\" : \""+from_filename+"\",","//OVER");
		tell_object(me,HIW+load_object(from_filename)->query("short")+HIW"通过"+link_dir+HIW"与这里相连!\n"NOR);
		add("exits/"+convert_dir(link_dir),from_filename);
		load_object(from_filename)->add("exits/"+link_dir,this_filename);
		return 1;
	}

}
int insert_string(string this_filename,string mark,string str,string over_mark)
{
	string *line,*des_line,this_file;
	int i;
	this_file=read_file(this_filename);
	if(!this_file) 
	{
		tell_object(this_player(),"read error!\n");
		return 1;
	}
		des_line=({});
		line=explode(this_file,"\n");
		for(i=0;i<sizeof(line);i++)
		{
		//		tell_object(this_player(),line[i]+"\n");
			if(line[i]==mark)
			{
				des_line+=({str});
				break;
			}
			if(line[i]==over_mark)
			{
				tell_object(this_player(),"超过限制！\n");
				return 1;
			}
			des_line+=({line[i]});
		}
		for(i=i+1;i<sizeof(line);i++)
		{
			des_line+=({line[i]});
		}
		this_file=implode(des_line,"\n");
		write_file(this_filename,this_file,1);
	return 1;
}
int do_makeup(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"up",me);
	return 1;
}
int do_maked(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"down",me);
	return 1;
}
int do_makeed(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"eastdown",me);
	return 1;
}
int do_makeeu(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"eastup",me);
	return 1;
}
int do_makewd(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"westdown",me);
	return 1;
}
int do_makewu(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"westup",me);
	return 1;
}
int do_makesd(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"southdown",me);
	return 1;
}
int do_makesu(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"southup",me);
	return 1;
}
int do_makend(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"northdown",me);
	return 1;
}
int do_makenu(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"northup",me);
	return 1;
}
int do_makeout(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"out",me);
	return 1;
}
int do_enter(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"enter",me);
	return 1;
}
int do_makese(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"southeast",me);
	return 1;
}

int do_makesw(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"southwest",me);
	return 1;
}

int do_makene(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"northeast",me);
	return 1;
}

int do_makenw(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"northwest",me);
	return 1;
}

int do_maken(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"north",me);
	return 1;
}
int do_makes(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"south",me);
	return 1;
}
int do_makew(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"west",me);
	return 1;
}

int do_makee(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"east",me);
	return 1;
}

int do_cut(string arg)
{
	string this_file,this_filename,*line,*des_line,temp1,temp2;
	int i;
	object me;
	me=this_player();
	if(SECURITY_D->get_status(me)!= "(admin)")
	{
		tell_object(me,"此命令只能由天神才能执行!\n");
		return 1;
	}
	if(!__DIR__"userchecker.c"->is_granted(this_player())) return notify_fail("你没有被授权!\n");
	
	this_filename=file_name(this_object())+".c";
	this_file=read_file(this_filename);
	if(!this_file) 
	{
		tell_object(this_player(),"read error!\n");
		return 1;
	}
	des_line=({});
	line=explode(this_file,"\n");
	for(i=0;i<sizeof(line);i++)
	{
		if(line[i]=="//EXIT"||line[i]=="//OVER") continue;
		if(sscanf(line[i],"/*%s*/%s",temp1,temp2)==2) continue;
		if(line[i]=="//CUTHERE") break;
		if(sscanf(line[i],"//%s",temp1)==1) continue;
		des_line+=({line[i]});
	}
	this_file=implode(des_line,"\n");
	write_file(this_filename,this_file,1);
	tell_object(me,HIW"文件已被精简!\n"NOR);

	return 1;
}
int do_write(string arg,string dir,object me)
{
	string this_file,this_filename,*line,*des_line,sample_file,sample_filename;
	int i,filelength;
	filename=__DIR__+arg;
	sample_filename="/u/mudy/sample.c";
	if(file_size(sample_filename)<0)
	{
		sample_filename=__DIR__+"sample.c";
		if(file_size(sample_filename)<0)
		{
			tell_object(me,"样本文件丢失!\n");
			return 1;
		}
	}
	if(sscanf(filename,"%s.c",this_file)!=1)
		filename=filename+".c";
	if(file_size(filename)>0) 
	{
		tell_object(me,"此文件已存在，且不为空，请更换文件名！\n");
		return 1;
	}
	if(!__DIR__"userchecker.c"->is_granted(this_player())) 
	{
		tell_object(this_player(),"你没有被授权!\n");
		return 1;
	}
	if(query("exits/"+dir)) 
	{
		tell_object(me,"这条路径已然存在，请del之后，再进行创建!\n");
		return 1;
	}
	filelength=strwidth(arg);
	if(filelength<2)
	{
		tell_object(me,HIW"对不起，你输入的文件名太短了!\n"NOR);
		return 1;
	}
	while(filelength--)
	{
		
		if(arg[filelength]<='9'&&arg[filelength]>='0') continue;
		if(arg[filelength]<'a'||arg[filelength]>'z')
		{
			tell_object(me,HIW"请用英文和数字做文件名!\n"NOR);
			return 1;
		}
	}
	set("temp_dir",dir);
	this_filename=file_name(this_object())+".c";
	this_file=read_file(this_filename);
	if(!this_file) 
	{
		tell_object(this_player(),"read error!\n");
		return 1;
	}
		des_line=({});
		line=explode(this_file,"\n");
		for(i=0;i<sizeof(line);i++)
		{
			if(line[i]=="//EXIT")
			{
				des_line+=({"\""+dir+"\":\""+filename+"\","});
				break;
			}
			if(line[i]=="//OVER")
			{
				tell_object(this_player(),"这里的路径太多了。\n");
				return 1;
			}
			des_line+=({line[i]});
		}
		for(i=i+1;i<sizeof(line);i++)
		{
			des_line+=({line[i]});
		}
		this_file=implode(des_line,"\n");
	sample_file=read_file(sample_filename);
		write_file(this_filename,this_file,1);
	tell_object(me,HIW"请输入房间名字：\n"NOR);
	input_to((:get_shortname:));
	write_file(filename,sample_file,1);
	insert_string(filename,"//EXIT","\""+convert_dir(dir)+"\":\""+file_name(this_object())+"\",","//OVER");
	change_string(filename,"//Created by%s","//Created by "+me->query("id"));
	tell_object(this_object(),HIW"路径成功添加!\n"NOR);
	return 1;
}
int get_shortname(string arg)
{
	string file;
	int namelength;
	object me;
	me=this_player();
	file=read_file(filename);
	if(!arg)
	{
		tell_object(this_player(),HIW"请输入房间名字：\n"NOR);
		input_to((:get_shortname:));
		return 1;
	}
	namelength = strwidth(arg);
	while(namelength--) {
		if( arg[namelength]<=' ' ) {
			tell_object(me,HIW"房间的名字不能用控制字元。\n"NOR);
			input_to((:get_shortname:));
			return 1;
		}
		if(!is_chinese(arg[namelength..<0]) ) {
			tell_object(me,HIW"对不起，请您用「中文」取名字。\n"NOR);
			input_to((:get_shortname:));
			return 1;
		}
	}
	shortname=arg;
	file=replace_string(file,"SHOR"+"TNAME",shortname);
	write_file(filename,file,1);	
	tell_object(this_player(),HIW"请输入房间描述：\n"NOR);
	input_to((:get_longname:));
	return 1;
}
int get_longname(string arg)
{
	string file,dir;
	object *rooms;
	dir=query("temp_dir");
	file=read_file(filename);
	if(!arg)
	{
		tell_object(this_player(),HIW"请输入房间描述：\n"NOR);
		input_to((:get_longname:));
		return 1;
	}
	longname=arg;
	file=replace_string(file,"LONG"+"NAME",longname);
	write_file(filename,file,1);
	add("exits/"+dir,filename);
	rooms=children(filename);
	for(int i=0;i<sizeof(rooms);i++)
	{
		rooms[i]->add("exits/"+convert_dir(dir),file_name(this_object())+".c");
		rooms[i]->set("canexpand",1);
	}
	delete("temp_dir");;
	return 1;
}
string convert_dir(string dir)
{
	if(dir=="north")
		return "south";
	else if(dir=="south")
		return "north";
	else if(dir=="east")
		return  "west";
	else if(dir=="west")
		return "east";
	else if(dir=="northwest")
		return "southeast";
	else if(dir=="southeast")
		return "northwest";
	else if(dir=="northeast")
		return "southwest";
	else if(dir=="southwest")
		return "northeast";
	else if(dir=="out")
		return "enter";

	else if(dir=="northup")
		return "southdown";
	else if(dir=="southdown")
		return "northup";

	else if(dir=="southup")
		return "northdown";
	else if(dir=="northdown")
		return "southup";

	else if(dir=="westup")
		return "eastdown";
	else if(dir=="eastdown")
		return "westup";

	else if(dir=="westdown")
		return "eastup";
	else if(dir=="eastup")
		return "westdown";

	else if(dir=="up")
		return "down";
	else if(dir=="down")
		return "up";


	else if(dir=="enter")
		return "out";
	else if(dir=="out")
		return "enter";
	else
		return "none";
}