// File         : killer.c
// Created By   : iszt@pkuxkx, 2006-12-07

inherit NPC;
#include <ansi.h>

string *skill = ({ 
	"taiji-jian", "dagou-bang", "lingshe-zhangfa", "murong-daofa",
		"dagou-bang", "fuliu-jian", "shenghuo-lingfa", "pixie-jian",
		"xuantie-jian", "tianyu-qijian", "quanzhen-jian", "yuxiao-jian",
		"kuangfeng-dao", "jiulong-bian", "dulong-bi", "wuxian-jianfa",
});

string *force = ({
	"taiji-shengong", "huntian-qigong", "hamagong", "shenyuan-gong",
		"huntian-qigong", "linji-zhuang", "jiuyang-shengong", "kuihua-shengong",
		"jiuyin-shengong", "bahuang-gong", "xiantian-gong", "bihai-shengong",
		"bixue-xinfa", "cangming-gong", "shenlong-xinfa", "riyue-shengong",
});

string *perform = ({
	"chan", "chan", "saoluoye", "daoying",
		"zhuan", "fuliu", "fenxin", "fenxin", "cimu",
		"xiongyong", "fenfei", "xiantian-gong", "qixing", "xiaohua",
		"kuang", "baibi", "meiren", "boxian",
});

string *base = ({
	"sword", "staff", "staff", "blade",
		"staff", "sword", "sword", "sword",
		"sword", "sword", "sword", "sword",
		"blade", "whip", "dagger", "sword",
}); 

string *weapon1 = ({
	"sword/qingfeng", "zhubang", "staff/tieguai", "blade/gudingdao",
		"zhubang", "sword/qingfeng", "sword/qingfeng", "sword/xiuhua",
		"sword/qingfeng", "sword/yudi", "gangjian", "yuxiao",
		"blade/gudingdao", "whip/jueqingwhip", "bishou","sword/guqin",
});

void create()
{
	set_name("黑衣杀手", ({ "heiyi shashou", "shashou", "killer"}));

	set("init",0);








	set("gender", "男性");
	set("age", 20 + random(60));
	set("long", "这是一名黑衣杀手。\n" );
	set("str", 30 + random(15));
	set("int", 30 + random(15));
	set("con", 30 + random(15));
	set("dex", 30 + random(15));
	set("max_qi",6000);
	set("eff_qi",6000);
	set("qi",6000);
	set("neili",8000);
	set("max_neili",6000);
	set("jingli",4000);
	set("max_jingli",4000);
	set("eff_jingli",4000);
	set("max_jing",4000);
	set("jing",4000);
	set("shen", -100000);
	set("no_get", 1);
	if (!random(4))
		set("double_attack",1);

	setup();

	call_out("remove_ob",300,this_object());
}

void remove_ob(object ob)
{
	if(!ob) return;
	message_vision("黑衣杀手一闪身不见了。\n", ob);
	destruct(ob);
}

void init()
{
	object ob=this_object();
	object dashi = query("dashi");
	add_action("block_cmd", "",1);

	::init();
	if (!dashi)
	{
		if(ob)
			destruct(ob);
		return;
	}
//	remove_all_enemy();
//	start_busy(0);
//	dashi->hit_ob(ob);
//	command("kill " + dashi->query("id"));
//	kill_ob(dashi);
	if(!is_fighting())
		command("kill " + dashi->query("id"));

}

int block_cmd(string args)
{
	object ob, dashi, *people;
	int i, teamsize, is_robber, is_husong_player;
	string verb;
	ob = this_player();
	verb = query_verb();
	dashi = query("dashi");
	people = all_inventory( environment( ob ));
  is_husong_player = 0;
  is_robber = 0;
	if(!dashi) return 0;


	teamsize = dashi->query_temp("teamsize");
	for(i = 0; i < teamsize; i++)
	{
		if(dashi->query_temp("team"+i) == ob)
		{
			is_husong_player = 1;
			break;
		}
	}

  for(i = 0; i<sizeof(people); i++)
	{
		if(people[i]->query("id")=="cart robber")
			{
			is_robber = 1;
			break;
		}
	}
	
  if(is_husong_player == 0 && is_robber == 0)
	{
			if( verb == "kill" || verb == "killall" || verb == "hit" || verb == "hitall" || verb == "exert" ||
			verb == "perform" || verb == "steal")
		{
			tell_object(ob, "这事跟你没关系，你还是不要插手的好。\n");
			return 1;
		}
		else return 0;
	}

	return 0;
}
void die()
{
	object ob1 = query("dashi"), me;

	if( !ob1 || !present(ob1)) {
		::die();
		return;
	}

	me = get_damage_origin_object();
	if (!me || !objectp(me)) 
		//objectp()函数的参数不能为零
	{
		::die();
		return;
	}

	me->add_temp("sljob/killed",1);
  if (!random(3)) GEM_D->drop(this_object(),me);
	::die();
}

int do_copy1(object me)
{
	object ob = this_object();
	object dashi = query("dashi");
	int teamsize_eff = 115;
	string s_skill,s_force,s_perform,s_base,s_weapon;
	int lvl,index;

	if(dashi)
		teamsize_eff += ((int)dashi->query_temp("teamsize")) * 5;
	if(dashi) teamsize_eff = teamsize_eff + ((int)(dashi->query_temp("sljob/total") /10 )) * 5;      //杀得越多，杀手越强

	ob->set("combat_exp", me->query("combat_exp") / 100 * teamsize_eff);   


	lvl = pow(query("combat_exp")/100, 1.0/3)*10;
	index = random(sizeof(skill));

	s_skill = skill[index];
	s_force = force[index];
	s_perform = perform[index];
	s_base = base[index];
	s_weapon = weapon1[index];

	set("attribude", "peaceful");

	set("max_qi", me->query("max_qi")*2);
	set("eff_qi", me->query("max_qi"));
	set("qi", me->query("max_qi"));
	set("max_jing", 23000);
	set("max_neili", lvl*15);
	set("max_jingli", 24000);
	set("jiali",lvl/3);

	if (random(10)==0)
	{
		set("no_yizhaoyun",1);
	}

	set_skill(s_skill, lvl );
	set_skill(s_force, lvl );
	set_skill(s_base, lvl);
	set_skill("dodge", lvl);
	set_skill("force", lvl);
	set_skill("parry", lvl);
	set_skill("tiyunzong", lvl);
	set_skill("qimen-bagua",500);
	set_skill("poison",500);
	set_skill("buddhism",500);
	set_skill("cuff",lvl);
	set_skill("qiankun-danuoyi",500);
	set_skill("music",lvl);
	set_skill("daguangming-xinfa",lvl);
	set_skill("poyu-quan",lvl);
	set_skill("xingyi-zhang",lvl);
	set_skill("strike",lvl);


	map_skill("force", s_force);
	map_skill("dodge", "tiyunzong");
	map_skill("parry", s_skill);
	map_skill("cuff","poyu-quan");
	map_skill("strike","xingyi-zhang");
	map_skill(s_base, s_skill);
	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "xingyi-zhang");

	set("dagou-bang/zhuan", 1);
	set("chat_chance_combat", 150);
	set("chat_msg_combat", ({
		(: perform_action, s_base + "." + s_perform :)
	}) );
	setup();
	reincarnate(); 
	carry_object("/clone/cloth/male3-cloth.c")->wear();
	carry_object("/clone/weapon/"+s_weapon)->wield();
	add_money("silver",20+random(20));
	add_money("gold",random(3));
	set("eff_neili", query("max_neili"));
	set("neili",query("max_neili")*3/2);
	
//	command("kill " + dashi->query("id"));
}
void unconcious()
{
	object ob = this_object();
	if(ob->query("qi")>=0 && random(2)==1)
		return;
	//        ::unconcious();
	die();   //晕倒后立即死亡，否则晕倒后block_cmd无效，别人也可以杀，不明白为什么block_cmd会无效，所以直接die()算了
}
