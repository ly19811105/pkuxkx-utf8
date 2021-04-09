//主要作用是玩家login前的通用检查流程相关功能
#include <title.h>
#include <ansi.h>
nosave int last_age_set;

protected void apply_buffer(object me, mapping buffer_map);

// This function updates player's age, called by heart_beat()
void update_age()
{
    int hour,age,reduce;
    object user=this_object();
    // Update the time we spend on mudding, using method from TMI-2 mudlib.
    if( !last_age_set ) 
    	last_age_set = time();
    if (!user->query("env/oldman") && 
    	  user->query("mud_age") > 86400*4 && 
    	  (int)user->query("antirobot/deactivity") > 3)
    {
        //18岁以后，不fullme的时间不增加年龄。这样发呆或者fullskill就没事。除非玩家主动要求变老
        last_age_set = time();
        return;
    }
    user->add("mud_age", time() - last_age_set);
    if( user->query("pet_died") )
	    user->add("pet_died", time() - last_age_set);
    last_age_set = time();
    hour=user->query("mud_age") / 3600;
    if ( hour<=24*36 )
      age=14 + (int)user->query("age_modify") + hour/24;
    else
//当年龄大于50岁以后按照公式年龄^2/(25+年龄/2)来计算每一岁的小时数
//mudage_reduce在50岁以后起作用，作为小时数减项存在。
    {
    	hour=hour-36*24-user->query("mudage_reduce")/3600-50;
    	age=50 + (int)user->query("age_modify");
    	while(hour>=0)
    	{
    		age++;
    		hour=hour-(age*age)/(25+age/2);
    	}
    }
    user->set("age", age);    
}

//脸谱初始化，设置原始脸谱，如果存在脸谱则会自动跳过
void init_face(object login)
{
	object user=this_object();
	
  if(objectp(login))
  {
      user->set_face(FACE_ORIGIN, login->query("name"),login->query("id"));
      user->set_face(FACE_FACT, user->query("name"));
      user->restore_face(FACE_FACT);
  }
}

//初始化头衔
void init_title()
{
	object user=this_object();
	
  //设置掌门大弟子的title
  user->set_title(TITLE_MASTER);
  if(user->query("id") == FAMILY_D->get_dadizi(user->query("family/family_name")))
  {
	  user->set_temp("apply/title",user->query("title")+ " " + HIY"掌门大弟子"NOR);
	  user->set_title(TITLE_MASTER, "『"HIM+user->query("family/family_name")+NOR"』"HIY"掌门大弟子"NOR);
  }
}

//自动装载随机装备
void create_autoload_equip()
{
	int		i;
	object	obj;
	object user=this_object();
	string *autoloads;
	object uitem;
  
  uitem=new(UITEM_OB);
  uitem->set("id", user->query("id"));
//  if ( uitem->check_save() )
    uitem->restore();

//对autoload装备进行数据转换，旧数据暂时不清楚，但是设置了版本
//等以后确定需要清理再更新版本。
//itemsave_ver版本编号v1作用就是升级随机装备存储到useritem对象中。
//以后木有需要请清除版本为v1的以下数据
//  gem_weapon_autoload_num、gem_armor_autoload_num
//  gem_weapon_autoload、gem_armor_autoload
//
  if ( ( user->query("gem_weapon_autoload_num") ||
         user->query("gem_armor_autoload_num") ) &&
       !user->query("itemsave_ver") )
  {
    uitem->levelup_autoload(user);
    user->set("itemsave_ver",1 );
    destruct(uitem);
  }
	
//自制兵器加载	
	if ( arrayp(autoloads = user->query("auto_load")) )
	{
		for (i = sizeof(autoloads)-1; i >= 0; i--)
		{
			if(autoloads[i][0..2]=="/u/"&&!wizardp(user)) continue;
			if ( objectp(obj = new(autoloads[i])) && obj->move(user) )
				write("\n" + obj->name() + "  loaded.\n\n");
			else
				write(HIY "你觉得好象失落了什么重要的东西，赶快通知巫师吧！\n\n" NOR);
		}
	}
}

//基本物品创建
void create_base_item()
{
  object bag, anqidai, cloth,ring, shoe, guider, mbx,my_own_item;
  object user=this_object();
  string fm;

//宝石袋子创建	
	bag=new("/clone/obj/gemlocker");
	bag->move(this_object());

//暗器袋创建
  fm=(string)user->query("family/family_name");
  if( fm == "峨嵋派" || fm == "星宿派" || fm == "桃花岛" || fm == "古墓派" || fm == "明教" )
  {
	anqidai=new("/clone/obj/anqidai");
	anqidai->move(user);
  }
  
//新手指南创建
  if(user->query("age") < 15 && (user->query("combat_exp") < 2000) &&  user->query("newbie_village/done") == 1 )
	{
		guider = new("/clone/misc/guider");
		guider->move(user);
	}
	
//裹体的一般衣服创建
	if (F_PRO->pro_class(user)!="fighter")
	{
		if (user->query("ProfessionalClass/herbalism"))
		{
			my_own_item=new("/obj/remedy/kuang");
			my_own_item->move(user);
		}
		if (F_PRO->pro_class(user)=="alchemy")
		{
			if (user->query_skill("alchemy",1)>120)
			{
				cloth=new("/clone/cloth/ycloth2");
				shoe=new("/clone/cloth/yshoe2");
				if (user->query_skill("alchemy",1)>200)
				ring=new("/clone/cloth/yring");
			}
			else
			{
				cloth=new("/clone/cloth/ycloth");
				shoe=new("/clone/cloth/yshoe");
			}
		}
		else if (F_PRO->pro_class(user)=="herbalism")
		{
			if (user->query_skill("herbalism",1)>200)
			{
				cloth=new("/clone/cloth/ycloth2");
				shoe=new("/clone/cloth/yshoe2");
			}
			else
			{
				cloth=new("/clone/cloth/ycloth");
				shoe=new("/clone/cloth/yshoe");
			}
		}
		else if (F_PRO->pro_class(user)=="smithing")
		{
			if (user->query_skill("smithing",1)>120)
			{
				cloth=new("/clone/cloth/gcloth2");
				shoe=new("/clone/cloth/gshoe2");
				if (user->query_skill("smithing",1)>200)
				{
					my_own_item=new("/clone/cloth/ghead");
					my_own_item->move(user);
					my_own_item->wear();
				}
			}
			else
			{
				cloth=new("/clone/cloth/gcloth");
				shoe=new("/clone/cloth/gshoe");
			}
		}
		else if (F_PRO->pro_class(user)=="mining")
		{
			if (user->query_skill("mining",1)>200)
			{
				cloth=new("/clone/cloth/gcloth2");
				shoe=new("/clone/cloth/gshoe2");
			}
			else
			{
				cloth=new("/clone/cloth/gcloth");
				shoe=new("/clone/cloth/gshoe");
			}
		}
		else
		{
			cloth=new("/clone/cloth/cloth");
			if (user->query("gender")=="女性")
			shoe=new("/clone/armor/womanshoes");
			else
			shoe=new("/clone/armor/manshoes");
		}
	}
	else if (user->query("class")=="bonze")
	{
		if (user->query("gender")=="女性")
		{
			cloth = new("/clone/cloth/ni-cloth.c");
			shoe = new("/clone/cloth/ni-xie.c");
		}
		else
		{
			cloth = new("/clone/cloth/seng-cloth.c");
			shoe = new("/clone/cloth/seng-xie.c");
		}
	}
	else
	{
		if (user->query("class")=="taoist")
		{
			if ( user->query("gender")=="女性")
			{
				cloth = new("/clone/cloth/daogu-cloth.c");
				shoe = new("/clone/cloth/dao-xie.c");
			}
			else
			{
				cloth = new("/clone/cloth/dao-cloth.c");
				shoe = new("/clone/cloth/dao-xie.c");
			}
		}
		else
		{
			if ( user->query("gender")=="女性")
			{
				switch (random(2))
				{
				case 0:
					shoe = new("/clone/cloth/female-shoe.c");
					break;
				case 1:
					shoe = new("/clone/armor/womanshoes");
					break;
				}
				switch (random(9))
				{
				case 1:
					cloth = new("/clone/cloth/female1-cloth.c");
					break;
				case 2:
					cloth = new("/clone/cloth/female2-cloth.c");
					break;
				case 3:
					cloth = new("/clone/cloth/female3-cloth.c");
					break;
				case 4:
					cloth = new("/clone/cloth/female4-cloth.c");
					break;
				case 5:
					cloth = new("/clone/cloth/female5-cloth.c");
					break;
				case 6:
					cloth = new("/clone/cloth/female6-cloth.c");
					break;
				case 7:
					cloth = new("/clone/cloth/female7-cloth.c");
					break;
				case 8:
					cloth = new("/clone/armor/skirt");
					break;
				default:
					cloth = new("/clone/cloth/female8-cloth.c");
				}
			}
			else
			{
				switch (random(2))
				{
				case 0:
					shoe = new("/clone/cloth/male-shoe.c");
					break;
				case 1:
					shoe = new("/clone/armor/manshoes");
					break;
				}
				switch (random(10))
				{
				case 1:
					cloth = new("/clone/cloth/male1-cloth.c");
					break;
				case 2:
					cloth = new("/clone/cloth/male2-cloth.c");
					break;
				case 3:
					cloth = new("/clone/cloth/male3-cloth.c");
					break;
				case 4:
					cloth = new("/clone/cloth/male4-cloth.c");
					break;
				case 5:
					cloth = new("/clone/cloth/male5-cloth.c");
					break;
				case 6:
					cloth = new("/clone/cloth/male6-cloth.c");
					break;
				case 7:
					cloth = new("/clone/cloth/male7-cloth.c");
					break;
				case 8:
					cloth = new("/clone/armor/jinzhuang");
					break;
				case 9:
					cloth = new("/clone/armor/cloth");
					break;
				default:
					cloth = new("/clone/cloth/male8-cloth.c");
				}
			}
		}
	}
	cloth->move(user);
	cloth->wear();
	shoe->move(user);
	shoe->wear();
	if (ring)
	{
		ring->move(user);
		ring->wear();
	}
	
//邮箱创建
	if( user->query("new_mail") ) {
		message_vision( HIG + "\n一个驿站的伙计匆匆跑过来，交给$N一个信箱，说道：「有您的信！」然后头也不回地走了。\n" + NOR, user);
		mbx = new("/clone/misc/mailbox");
		mbx->move(user);
	}
}

//基本属性检查
int MyGift(int giftpoint)
{
	if (giftpoint>50)
	return giftpoint;
	else
	return 50;
}
void check_attribute()
{
	object user=this_object();
	int limit, advlimit, golds, incr;
	
//新手食物自动full	
	if (!user->query("food") && !user->query("water") && user->query("age") == 14) {
		user->set("food", user->max_food_capacity());
		user->set("water", user->max_water_capacity());
	}
//先天属性10-50浮动范围检查	,MaxGift定义在attribute.c，可突破50，MyGift在这里做双重保险，Zine
//暂时先不开放50以上先天by yhzzyahoo
	if(user->query("combat_exp")<0) user->set("combat_exp",0);
 /* if(user->query("int",1)>MyGift(user->MaxGift("int"))&&!wizardp(user)) user->set("int",MyGift(user->MaxGift("int")));
  if(user->query("str",1)>MyGift(user->MaxGift("str"))&&!wizardp(user)) user->set("str",MyGift(user->MaxGift("str")));
  if(user->query("con",1)>MyGift(user->MaxGift("con"))&&!wizardp(user)) user->set("con",MyGift(user->MaxGift("con")));
  if(user->query("dex",1)>MyGift(user->MaxGift("dex"))&&!wizardp(user)) user->set("dex",MyGift(user->MaxGift("dex")));*/
	if(user->query("int",1)>50&&!wizardp(user)) user->set("int",50);
	if(user->query("str",1)>50&&!wizardp(user)) user->set("str",50);
	if(user->query("con",1)>50&&!wizardp(user)) user->set("con",50);
	if(user->query("dex",1)>50&&!wizardp(user)) user->set("dex",50);

	if(user->query("int",1)<10&&!wizardp(user)) user->set("int",10);
	if(user->query("str",1)<10&&!wizardp(user)) user->set("str",10);
	if(user->query("con",1)<10&&!wizardp(user)) user->set("con",10);
  if(user->query("per",1)<10&&!wizardp(user)) user->set("per",10);
  if(user->query("kar",1)<10&&!wizardp(user)) user->set("kar",10);
	if(user->query("dex",1)<10&&!wizardp(user)) user->set("dex",10);
	if(user->query("eff_jing",1)>user->query("max_jing")&&!wizardp(user)) user->set("eff_jing",user->query("max_jing"));

//存钱上限防溢出检查
  if (!user->query("lingjiu/xiulian"))
 	{
    if     (user->query("combat_exp")>=80000000) limit=2000000000;
    else   limit = user->query("combat_exp") * 25;
  }
  else
 	{
    if     (user->query("lingjiu/combat_exp")>=80000000) limit=2000000000;
    else   limit = user->query("lingjiu/combat_exp") * 25;  		
 	}

	if ( limit > 2000000000 || limit < 0 )
		limit = 2000000000;
	if ( limit < 500000 )
		limit = 500000;
	
	if ( limit < 1000000 )
		advlimit=1000000;
	else if ( limit > 1000000000 )
		advlimit=1000000000;
	else
		advlimit=limit;
//存款过大的时候自动将存款转换成金条 by seagate
	if ( user->query("balance")>advlimit )
	{
		if ( (user->query("balance")-advlimit)%1000000==0 )
			golds=(user->query("balance")-advlimit)/1000000;
		else
		  golds=(user->query("balance")-advlimit)/1000000+1;
		user->add("advance_balance", golds);
		user->add("balance", -1000000*golds );
		tell_object(user, "你在钱庄存款太多了，钱庄自动将你的存款转换成金条。\n");
	}

//等级超过110增益，增加对技能或者普通伤害的抗性
  if ( user->query("level")>110 )
  {
    incr=user->query("level")-110;
    if ( incr>50 )
      incr=50;
    user->add_temp("apply/kf_def_wound", incr);
    user->add_temp("apply/week_injure", incr);
  }

	if(TOPTEN_D->how_many_money(user) > limit )
	{
		user->set("balance", limit);
		if(objectp(present("gold",user)))
			destruct(present("gold",user));
		if(objectp(present("silver",user)))
			destruct(present("silver",user));
		if(objectp(present("coin",user)))
			destruct(present("coin",user));
		if(objectp(present("thousand-cash",user)))
			destruct(present("thousand-cash",user));
		write(HIR"在北侠打倒地主分田地的运动中，你损失惨重……\n"NOR);
	}
}

//技能、经验等检查
void check_skills()
{
	mapping skill_status, skill_map, bufmap, skp;
	string *sname;
	int i,level, lvlimit;
	object user=this_object();
	
//功夫等级检查
	lvlimit = user->query_skill_limit();

	if ( !(skill_status = user->query_skills()) ) {}
	else
	{
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) 
		{
			level = skill_status[sname[i]];
			if( intp(level) 
				&& level > lvlimit
				&& user->query("combat_exp") > 100
				&& SKILL_D(sname[i])->type() != "knowledge") 
			{
        user->set_skill(sname[i], lvlimit);
				write(HIR+BNK+"你的" + sname[i] + "等级超出经验支持的能力范围，已经恢复到" + lvlimit + "级。\n"+NOR);
			}
		}
	}
	
  if (user->query_skill("emei-jiuyanggong",1)>60) //峨嵋九阳功不许大过60级Zine
  {
    user->set_skill("emei-jiuyanggong",60);
    write(HIR+BNK+"你的峨嵋九阳功被恢复到六十级。\n"+NOR);
  }
//记录经验历史痕迹 by seagate	
	if ( user->query("combat_exp")>=10000 )
		user->set("exp_hist/"+gctime(0,1)[0..6], user->query("combat_exp") );
  
//检查并剔除无效的技能激发和准备 by lordstar 2017/9/16
  skp = user->query_skill_prepare();
  if (mapp(skp))
  {
	  sname=keys(skp);
	  for (i=0; i<sizeof(sname);i++)
	  {
		if (!user->query_skill(sname[i],1) || !user->query_skill(skp[sname[i]], 1))
			user->prepare_skill(sname[i]);
	  }
  }
  skp = user->query_wprepare();
  if (mapp(skp))
  {
	  sname=keys(skp);
	  for (i=0; i<sizeof(sname);i++)
	  {
		if (!user->query_skill(sname[i],1) || !user->query_skill(skp[sname[i]], 1))
			user->prepare_wskill(sname[i]);
	  }
  }
  
  //被动技能特效自动装载
  skill_map=user->query_skill_map();
  if ( mapp(skill_map) )
  {
    sname=keys(skill_map);
    for(i=0;i<sizeof(sname);i++)
    {
		if (!user->query_skill(sname[i],1) || !user->query_skill(skill_map[sname[i]], 1))
			user->map_skill(sname[i]);
		else  if ( stringp(skill_map[sname[i]]) )
       {
        bufmap=SKILL_D(skill_map[sname[i]])->buffer_removed(user);
        if ( mapp(bufmap) )
          apply_buffer(user, bufmap);
        bufmap=SKILL_D(skill_map[sname[i]])->buffer_applied(user);
        if ( mapp(bufmap) )
          apply_buffer(user, bufmap);
       }
    }
  }
}

//初始化毒药作用，目的是有些毒药relogin以后还会产生中毒效果。
void init_poison()
{
	object user=this_object();
//定义在 /feature/condition
	user->inspect_irregular_conditions();
//三尸脑神丹	
	if ( user->query("riyue_drug")
		&& (user->query("age") > user->query("riyue_drug")))
	{
		write(HIY "你的三尸脑神丹的毒还有十分钟就要发作了！赶快去要解药吧！\n" NOR);
		call_out("riyue_poison",600,user);
	}
}

//旧数据转换
void transfer_olddata()
{
	mapping sks, gemnum;
	mixed *vlist;
	object gnlist, ob, user=this_object();
	int old_music, loop, total = 0;
	
	//清理北侠数据，开启北侠新时代	
	if (!user->query("pkuxkxlife_ver"))
	{
		user->delete("silver");
		user->delete("gem_armor_autoload_num");
		user->delete("gem_weapon_autoload_num");
		user->delete("gembox_slot");
		user->delete("gembox_number");
		user->set("baoshi_number", 0);
		user->delete("pawn");
		user->delete("fpawn");
		user->delete("vpawn");
		user->delete("ipawn");
		user->delete("apawn");
		user->delete("npawn");
		user->delete("pawns");
		user->delete("fpawns");
		user->delete("vpawns");
		user->delete("ipawns");
		user->delete("tpawns");
		user->delete("autoload");
		user->delete("store_ob");
		user->delete("cjg");
		user->delete("gem_armor_autoload");
		user->delete("gem_weapon_autoload");
		user->delete("hockshop_100");
		user->delete("hockshop_101");
		user->delete("hockshop_200");
		user->delete("hockshop_201");
		user->delete("hockshop_202");
		user->delete("hockshop_203");
		user->delete("hockshop_204");
		user->delete("hockshop_205");
		user->delete("hockshop_206");
		user->delete("hockshop_211");
		user->delete("hockshop_219");
		user->delete("hockshop_281");
		user->delete("hockshop_300");
		user->delete("hockshop_400");
		user->delete("hockshop_500");
		//force levelup
		user->set("repute", 999999);
		user->set("balance", 999999);
		user->set("advance_balance", 999999);
		while(1)
		{
			int level = (int)user->query("level") + 1;
			if ( level>0 && level <= 100 && user->query("combat_exp")<level*level*level*400 )
			{
				break;
			}
			else if ( level>100 && user->query("combat_exp")/1000000<400+(level-100)*(level-100)+10 )
			{
				break;
			}
			call_other("/cmds/usr/levelup.c","level_up", "yes", user);
		}
		
		user->delete("repute");
		user->delete("balance");
		user->delete("advance_balance");
		
		
		if(objectp(ob = present("thousand-cash", user)))
			destruct(ob);
		if(objectp(ob = present("gold", user)))
			destruct(ob);
		if(objectp(ob = present("silver", user)))
			destruct(ob);
		if(objectp(ob = present("coin", user)))
			destruct(ob);
		
		user->set("pkuxkxlife_ver",1 );
	}
	if (user->query("pkuxkxlife_ver") < 2)//修复锦囊宝石数量
	{
		user->set("baoshi_number", 0);
		gemnum = user->query("gembox_number");
	
		if(gemnum && mapp(gemnum))
		{
			vlist = values(gemnum);
			if(vlist && sizeof(vlist))
			{
				for(loop=0; loop<sizeof(vlist); loop++)  
				{
					total += vlist[loop];
				}
				user->set("baoshi_number", total);
			}
		}
		user->set("pkuxkxlife_ver", 2);
	}
	
	sks=user->query_skills();
//桃花岛旧版music技能自动转换
	if ( sks &&
		   sks["music"] && 
		   intp(sks["music"]) )
	{
		old_music=sks["music"];
		if ( sks["music"]<=200 )
		{
			user->add("potential",  sks["music"]*200);
			user->delete_skill("music");
			tell_object(user, "你的旧版音乐技能被取消了，赠送你"+sks["music"]*200+"点潜能。\n");
		}
		else
		{
			user->delete_skill("music");
		  user->set_skill("music::music-theory", 250);
	    user->set_skill("music::shaw", 250);
	    user->set_skill("music::shaw::meihua-sannong", 200);
	    user->set_skill("music::shaw::yuqiao-wenwan", 200);
//仅桃花岛或者出师前是桃花岛弟子补偿的时候赠送碧海潮生曲
	    if ( user->query("chushi/last_family")=="桃花岛" ||
	    	   user->query("family/family_name")=="桃花岛" )
	      user->set_skill("music::shaw::bihai-chaosheng", old_music/2 );
		  tell_object(user, "你的旧版音乐技能被取消了，提供了你新版的箫类音乐知识。\n");
		}
	}
}

protected void riyue_poison(object user)
{
	if( !user ) return;
	if (!(user->query("age") > user->query("riyue_drug")))
		return;
	user->add_temp("riyue/poison",1);
	if (user->query_temp("riyue/poison") == 2)
	{
		message_vision(HIR "$N由于三尸脑神丹毒发时间过长，无药可救，倒地而亡。\n" NOR,user);
		user->set("riyue_drug",999);
        user->receive_damage("qi", 0, "三尸脑神丹毒发");
		user->die();
		user->save();
		return;
	}

	user->set("max_qi",50);
	user->set("max_jing",50);
	message_vision(HIR "$N的三尸脑神丹毒发作了！$N痛得满地打滚，咬牙切齿，状如疯狗一般。\n" NOR,user);
	user->set("attitude","aggressive");
	call_out("riyue_poison",300,user);
}

//玩家状态的被动加载
protected void apply_buffer(object me, mapping buffer_map)
{
  string *apply=keys(buffer_map);
  int lp;
  
  for(lp=0;lp<sizeof(apply);lp++)
  {
    me->add_temp("apply/"+apply[lp], buffer_map[apply[lp]]);
    if ( userp(me) &&
         apply[lp]=="max_qi" )
    {
      me->set("max_qi", me->query_max_qi() );
      if ( me->query("eff_qi") > me->query("max_qi") )
        me->set("eff_qi", me->query("max_qi") );
      
      if ( me->query("eff_qi")>0 &&
           buffer_map[apply[lp]]>0 &&
           me->query("max_qi")-me->query("eff_qi")<=buffer_map[apply[lp]] )
        me->set("eff_qi", me->query("max_qi") );
      else if ( me->query("eff_qi")>0 &&
           buffer_map[apply[lp]]>0 &&
           me->query("max_qi")-me->query("eff_qi")>buffer_map[apply[lp]] )
        me->add("eff_qi", buffer_map[apply[lp]] );
    }
      
    if ( userp(me) &&
         apply[lp]=="max_jing" )
    {
      me->set("max_jing", me->query_max_jing() );
      if ( me->query("eff_jing") > me->query("max_jing") )
        me->set("eff_jing", me->query("max_jing") );
        
      if ( me->query("eff_jing")>0 &&
           buffer_map[apply[lp]]>0 &&
           me->query("max_jing")-me->query("eff_jing")<=buffer_map[apply[lp]] )
        me->set("eff_jing", me->query("max_jing") );
      else if ( me->query("eff_jing")>0 &&
           buffer_map[apply[lp]]>0 &&
           me->query("max_jing")-me->query("eff_jing")>buffer_map[apply[lp]] )
        me->add("eff_jing", buffer_map[apply[lp]] );
    }
  }
}
