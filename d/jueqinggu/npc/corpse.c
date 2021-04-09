// corpse.c

inherit ITEM;
#include <ansi.h>
#include "/d/jueqinggu/npc/distortString.h"
int decayed;

void create()
{
	set_name("无名尸体", ({ "corpse" }) );
	set("long", "这是一具无名尸体。\n");
	set("unit", "具" );
	decayed = 0;
	if( clonep(this_object()) ) 
	{
	  call_out("init_task",1);
	  call_out("decay", 150, 1);
	}
}
void set_corpse(object me)
{
	set_name(me->name()+"的尸体", ({ "corpse" }) );
	set("long", "这是一"+me->name()+"的尸体。\n");
	set("pin",me->query("pin"));
}
int is_skeleton() { return decayed >= 2; }
int is_corpse() { return decayed < 2; }
int is_character() { return decayed < 1; }
int is_container() { return 1; }
void init()
{
	add_action("do_chakan","chakan");
}
int do_chakan()
{
	string *masters=({"wudang/zhang","shaolin/wuming","huashan/feng","mingjiao/zhang","tianlong/kurong","gaibang/hong","riyuejiao/ren","murong/murongbo","btshan/ouyangfeng",
	"xingxiu/li","gumu/yang","lingjiu/tonglao","quanzhen/wang","taohua/huang","shenlong/hong","dalunsi/laozu"});
	string mp,master,*masters2=({"emei/houshan/npc/miejue","hangzhou/npc/menggong","lingxiao/npc/baizizai"}),*sks,*spec_sks=({}),skill;
	object me=this_player(),npc,env;
	mapping skills,*action;
	mapping menpai=(["明教":"/d/mingjiao/damen","日月神教":"/d/riyuejiao/yaxia","武当派":"/d/wudang/shanmen","少林派":"/d/shaolin/shanmen","华山派":"/d/huashan/path1",
	"天龙寺":"/d/tianlong/duanhe","丐帮":"/d/city/pomiao","峨嵋派":"/d/emei/shmdian","姑苏慕容":"/d/murong/ygate","白驼山":"/d/baituo/damen","星宿派":"/d/xingxiu/xxgate",
	"古墓派":"/d/gumu/duanlongshi","灵鹫宫":"/d/lingjiu/jian","全真派":"/d/quanzhen/gongmen","桃花岛":"/d/taohuadao/haigang1",
	"神龙教":"/d/shenlongdao/damen","朝廷":"/d/hangzhou/beimen","大轮寺":"/d/dalunsi/guangchang","雪山派":"/d/lingxiao/bridgew"]);
	if (me!=query("owner")||!me->query_temp("gongsun/job")||me->query_temp("gongsun/finish"))
	{
		tell_object(me,"一具尸体有什么好看的。\n");
		return 1;
	}	
	if (random(20)>4)
	master="/kungfu/class/"+masters[random(sizeof(masters))];
	else
	master="/d/"+masters2[random(sizeof(masters2))];
	if (!npc=new(master))
	{
		log_file("user/jqg_error",sprintf("%s",master+"\n"));
		tell_object(me,"任务出错，已经提交，请等待巫师修复。\n");
		return 1;
	}
	skills=npc->query_skills();
	sks=keys(skills);
	for (int i=0;i<sizeof(sks);i++)
	{
		if ("/cmds/skill/skills.c"->query_skill_type(sks[i])=="special")
			spec_sks+=({sks[i]});
	}
	skill=spec_sks[random(sizeof(spec_sks))];
	message_vision(HIC+"$N仔细检查$n。\n"+NOR,me,this_object());
	tell_object(me,"这似乎是某种武功造成的伤痕。你脑海中出现了这几个字……\n");
	tell_object(me,cipher_name(me,to_chinese(skill)));
	me->set_temp("gongsun/finish",1);
	mp=npc->query("family/family_name");
	destruct(npc);
	npc=new(__DIR__"target2");
	npc->owner(me,mp,query("pin"));
	if (!npc->move(menpai[mp]))
		log_file("user/gongsun_err",sprintf("%s\n","/GONGSUN/"+menpai[mp]+"/"+mp+"cant move"));
	me->set_temp("gongsun/where",environment(npc));
	if (!npc||!npc->JQG_target())
	tell_object(me,"追查到这一步也差不多了，你可以回去和公孙谷主复命了。\n");
	else
	tell_object(me,"你灵机一动，或许可以到拥有这个武功的门派去看看。\n");
	return 1;
}
string short() { return name() + "(" + capitalize(query("id")) + ")"; }
int re_make()
{
	set("re_maked",1);
	remove_call_out("decay");
	call_out("decay",180,1);
	return 1;
}
void decay(int phase)
{
	decayed = phase;
	switch(phase) {
		case 1:
			message_vision("$N开始腐烂了，发出一股难闻的恶臭。\n",this_object());
			switch(query("gender")) {
				case "男性":
					set_name("腐烂的男尸", ({ "corpse", "尸体" }) );
				case "女性":
					set_name("腐烂的女尸", ({ "corpse", "尸体" }) );
				default:
					set_name("腐烂的尸体", ({ "corpse", "尸体" }) );
			}
			set("long",	"这具尸体显然已经躺在这里有一段时间了，正散发著一股腐尸的味道。\n");
			call_out("decay", 5, phase + 1);
			break;
		case 2:
			message_vision("$N被风吹乾了，变成一具骸骨。\n",this_object());
                          set_name("枯乾的骸骨", ({ "skeleton", "骸骨" }) );
			set("long", "这副骸骨已经躺在这里很久了。\n");
			call_out("decay", 5, phase + 1);
			break;
		case 3:
			message_vision("一阵风吹过，把$N化成骨灰吹散了。\n",this_object());
			if( environment() ) {
				object *inv;
				int i;
				
				inv = all_inventory(this_object());
//                                for(i=0; i<sizeof(inv); i++) inv[i]->move(environment());
                                for(i=0; i<sizeof(inv); i++) {
                                    if (inv[i]->query("no_get")) 
                                         destruct(inv[i]);
                                    else if (!inv[i]->query("value") && !inv[i]->value() && !inv[i]->query("task_owner"))
                                         destruct(inv[i]);
                                    else 
                                         inv[i]->move(environment());
                                }
			}
			destruct(this_object());
			break;
	}
}

void init_task()
{
  object *inv=all_inventory(this_object());
  
  for(int lp=0;lp<sizeof(inv);lp++)
    if ( inv[lp]->is_task() )
      inv[lp]->ext_calldest();
}