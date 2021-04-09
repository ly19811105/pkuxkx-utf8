//lxguan.c
//自助蜡像馆
//by all@pkuxkx, 2012/11/11

#include <ansi.h>
#include <room.h>
inherit ROOM;

string* attributes=({"long","title","age","str","con","int","spi","per",
        "job_title","nickname","combat_exp","max_qi","max_jing","gender",
        "max_neili","max_jingli","jiali","race","class","repute","score",
        "family/family_name",});

int block_cmd();
void create()
{
	set("short", HIY"北侠BT蜡像馆"NOR);
	set("long",
HIC"这里是北侠的蜡像馆，玩家达到一定水准之后可以在这里有一座蜡像，
以供后人瞻仰。这里记载着北侠的荣誉和欢乐。如果想了解更多，请上二楼
去参观这些蜡像吧。\n"NOR
	);
        set("exits", ([
                "up":"/d/wizard/nlaxiang",
                "out":"/d/wizard/mingren",
        ]));
        set("room_location", "/d/city/");
        set("objects", ([
                "/d/wizard/npc/lxmaster": 1,
        ]));
	setup();
}

void init()
{
	object me = this_player();
	add_action("do_make", "make_lx");
        if (!wizardp(this_player()))
          add_action("block_cmd","",1);   
}

#define MAKE_SET(key,value)     write_file(file,"\tset(\""+(key)+"\"," +(intp(value) ? sprintf("%d",(value)) : ("\""+value+"\""))+");\n");
#define MAKE_SKILL(key,value)   write_file(file,"\tset_skill(\""+(key)+"\"," +sprintf("%d",(value))+");\n");
#define MAKE_SKILL_MAP(from,to) write_file(file,"\tmap_skill("+"\""+from+"\","+"\""+to+"\");\n" );
#define MAKE_HEAD               write_file(file,"\#include <ansi.h>\ninherit NPC;\nvoid create()\n{\n\tset_name(\""+ob->query("name")+"\",({\""+arg+" npc"+"\"}));\n");
#define MAKE_TAIL               write_file(file,"\tsetup();\n\}\n");

int do_make(string arg)
{
	string file,*skill_names,to;
	int lx_location, score_num;
	object ob;
	object me = this_player();
	string lx_id=me->query("id");
	string lx_class, chushi_mp, lx_num;
	mapping skills;

	//各门派蜡像文件序号初始化
	if (!LAXIANG_D->get_location("init"))
	{
		LAXIANG_D->set_location("白驼山",1);
		LAXIANG_D->set_location("百姓",1);		
		LAXIANG_D->set_location("朝廷",1);
		LAXIANG_D->set_location("大轮寺",1);
		LAXIANG_D->set_location("峨嵋派",1);
		LAXIANG_D->set_location("丐帮",1);
		LAXIANG_D->set_location("古墓派",1);
		LAXIANG_D->set_location("华山派",1);
		LAXIANG_D->set_location("灵鹫宫",1);
		LAXIANG_D->set_location("雪山派",1);
		LAXIANG_D->set_location("明教",1);
		LAXIANG_D->set_location("姑苏慕容",1);
		LAXIANG_D->set_location("全真派",1);
		LAXIANG_D->set_location("日月神教",1);
		LAXIANG_D->set_location("少林派",1);
		LAXIANG_D->set_location("神龙教",1);
		LAXIANG_D->set_location("桃花岛",1);
		LAXIANG_D->set_location("天地会",1);
		LAXIANG_D->set_location("天龙寺",1);
		LAXIANG_D->set_location("武当派",1);
		LAXIANG_D->set_location("星宿派",1);
		LAXIANG_D->set_location("init",1);
	}	

	//获取蜡像存放的门派
	if (!(me->query("chushi/last_family")||me->query("family")))
		chushi_mp="百姓";
	else if	(me->query("chushi/last_family"))
		chushi_mp=me->query("chushi/last_family");
	else 	chushi_mp=me->query("family/family_name");
	lx_location = LAXIANG_D->get_location(chushi_mp);	
	if (chushi_mp=="百姓")
		lx_class="baixing";
	else if (chushi_mp=="白驼山")
		lx_class="baituo";
	else if (chushi_mp=="朝廷")
		lx_class="chaoting";
	else if (chushi_mp=="大轮寺")
		lx_class="dalun";
	else if (chushi_mp=="峨嵋派")
		lx_class="emei";
	else if (chushi_mp=="丐帮")
		lx_class="gaibang";
	else if (chushi_mp=="古墓派")
		lx_class="gumu";
	else if (chushi_mp=="华山派")
		lx_class="huashan";
	else if (chushi_mp=="灵鹫宫")
		lx_class="lingjiu";
	else if (chushi_mp=="雪山派")
		lx_class="lingxiao";
	else if (chushi_mp=="明教")
		lx_class="mingjiao";
	else if (chushi_mp=="姑苏慕容")
		lx_class="murong";
	else if (chushi_mp=="全真派")
		lx_class="quanzhen";
	else if (chushi_mp=="日月神教")
		lx_class="riyuejiao";
	else if (chushi_mp=="少林派")
		lx_class="shaolin";
	else if (chushi_mp=="神龙教")
		lx_class="shenlongjiao";
	else if (chushi_mp=="桃花岛")
		lx_class="taohua";
	else if (chushi_mp=="天地会")
		lx_class="tiandihui";
	else if (chushi_mp=="天龙寺")
		lx_class="tianlong";
	else if (chushi_mp=="武当派")
		lx_class="wudang";
	else if (chushi_mp=="星宿派")
		lx_class="xingxiu";

	score_num=20000;
	if (me->query("family/family_name")=="朝廷")
		score_num=10000;//朝廷门忠要求减半
	if (!(me->query("chushi/last_family")||me->query("family")))
		score_num=0;
	if (! arg)
		return notify_fail("你要制作什么？\n");
        if (userp(me)) 
           {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob|| !(arg == me->query("id"))) return notify_fail("你只能制作自己的蜡像。\n");
           }
        else return notify_fail("想好了自己想要干什么再说吧。\n");

	lx_num=sprintf("%d",lx_location);
	file = "/d/wizard/laxiang2/"+lx_class+lx_num+".c";  //蜡像npc文件
	if( file_size(file) > 0 || me->query("laxiang/done")==1)
		return notify_fail("你已经制作过蜡像了。\n");
	if(me->query_temp("laxiang/make")!= 1)
		return notify_fail("想制作蜡像，先找人问问吧。\n");
	if(!me->query("laxiang/tiaozhan"))		
		return notify_fail("你还没有挑战成功，不能制作蜡像。\n");
	if(me->query("combat_exp")< 200000000)
		return notify_fail("你的经验太低了，不能制作蜡像。\n");
	if(me->query("repute")< 5000000)
		return notify_fail("你的声望太低了，制作蜡像恐怕大家不服。\n");
	if (me->query("score")< score_num)
			return notify_fail("你对师门的贡献太少了，制作蜡像不大好吧。\n");
	if(me->query("balance")< 200000000)
		return notify_fail("你的存款太少了，不够制作蜡像。\n");	

	//制作蜡像，生成npc文件，程序取自/cmds/arch/make_npc.c	
	MAKE_HEAD;
	foreach(string temp in attributes)
	{
		MAKE_SET(temp,ob->query(temp) );
	}
	skills = ob->query_skills();
	skill_names=keys(skills);
	
	foreach(string temp in skill_names)
	{
		MAKE_SKILL(temp,ob->query_skill(temp,1) );

	}
	foreach(string temp in skill_names)
	{
		if( to=ob->query_skill_mapped(temp) )
			MAKE_SKILL_MAP(temp,to);
	}
	MAKE_TAIL;
	tell_object(me,HIW "\n制作蜡像成功，过几天就会给您放到相应的馆里！\n" HIW );
	me->add("balance", -200000000);
	me->add("repute", -2000000);	
	me->add("score", -score_num/2);				
	me->set("laxiang/done",1);
	me->set("laxiang/file","/d/wizard/laxiang2/"+lx_class+lx_num+".c");
	LAXIANG_D->add_location(chushi_mp,1);//门派蜡像序号更新
	log_file("static/laxiang",sprintf("%s(%s) 于%s制作蜡像，当前经验(%d)！\n",
         me->query("name"),me->query("id"),ctime(time()),me->query("combat_exp"))); 
	CHANNEL_D->do_channel(this_object(), "jh", this_player()->name()+"成功制作蜡像！", -1);
	return 1;
}

int block_cmd()
{        
       string verb = query_verb();  
       if (verb=="say") return 0; //allow say     
       if (verb=="chat") return 0;                
       if (verb=="quit") return 0;                                                         
       if (verb=="look") return 0;                
       if (verb=="out") return 0;
       if (verb=="up") return 0; 
       if (verb=="go") return 0;        
       if (verb=="hp") return 0;      
       if (verb=="score") return 0;                    
       if (verb=="ask") return 0;                
       if (verb=="make_lx") return 0;                       
       return 1;                                  
}
