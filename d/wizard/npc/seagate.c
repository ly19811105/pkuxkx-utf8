//by whuan
#include <ansi.h>
#include <title.h>
inherit NPC;

string ask_tasktitle();
string ask_gift2017();
void confirm_huigui(string yn, object me, string hg_type, string *exc_sks, string *inc_sks);

void create()
{
        set_name(HIC"西部数据"NOR, ({"westernd npc"}));
        set("long", "这就是西部数据，侠客行的巫师。专门负责新任务。\n");
        set("gender", "男性");
        set("age", 14);
        set("per", 10);
        set_skill("literate", 2000);
        set_skill("dodge", 2000);
        set_skill("unarmed", 2000);
        set_skill("parry", 2000);
        set("combat_exp",500000000);
        set("inquiry",([
				"新年礼物": (: ask_gift2017 :),
                "侠客榜头衔": (: ask_tasktitle :),
                "拆卸宝石" : @LONG
所有在新版宝石效果上线之前（护甲的木宝石效果修改为普通伤害抗性）的随机护甲，包括掉落的和打造的装备（藏经阁
装备请人工联系本人，可以通过论坛内私信或者qq联系），只要孔中镶嵌有木宝石，具有吸收伤害转换成内力消耗效
果的，都可以将disload以后的装备使用命令「chaixie <装备ID>」，会自动拆卸宝石后返回给本人，拆卸前请保留足
够的负重，防止出现意外。本功能会在下一次开放装备升级功能之前开放，请大家尽快修复自己的装备。
LONG,
                "回归师门" : @LONG
对于星宿，天龙，大轮寺，华山弟子，不管出师离开或者出师到以上四个门派的，都可以使用此功能回到你出师前的门派，
回归师门使用命令：huigui [all|part]。其中huigui all命令表示你要放弃除公共武学以外的所有其他特殊武学，返
回你用过的所有潜能，无损回到出师前门派，huigui part命令仅对你回到以上四个门派有效，表示你保留本门武学和
公共武学，不返回潜能，无损回到出师前门派。天龙弟子出师的如果不想回归本门，则可以到藏经阁或者铜雀台兑换枯
荣神功秘籍。
LONG
             ]));
        set("shen_type",1);
        set("score",500000);setup();          
        carry_object("/d/pker/npc/obj/pifeng")->wear();       
}

void init()
{
          ::init();
          add_action("do_chaixie", "chaixie");
//          add_action("do_huigui", "huigui");
}

//查询技能对应的技能类型
protected int query_skill_type(string sk_id)
{
	string *base_list=
	  ({"array", "axe", "blade", "claw", "club", "cuff", "dagger", "dodge", "finger", "force",
		  "fork", "halberd", "hammer", "hand", "hook", "iron-cloth", "leg", "magic", "move", 
		  "parry", "pestle", "spear", "spells", "staff", "stick", "strike", "sword", "throwing", 
		  "unarmed", "whip", "checking", "digging", "swimming"});
  
  if( member_array(sk_id, base_list)>=0 )
  	return 0; //base
  	
  if( !find_object(SKILL_D(sk_id)) && file_size(SKILL_D(sk_id)+".c") < 0 ) //判断是否是自创武功
    return 1; //special
  
  if ( SKILL_D(sk_id)->type()=="profession" )
  	return 0; //profession
  
  if ( SKILL_D(sk_id)->type()=="knowledge" )
  	return 0; //knowlledge
  
  return 1;      //special
}

int do_huigui(string arg)
{
  printf("这项功能没了，您请回！\n");

/*  mapping skl;
  int lp;
  object me=this_player();
  string fam, cs_fam, *sname, *p_sname, *exc_sks, *inc_sks;
  string *pub_sks=({"zui-quan","yuejia-qiangfa","xuantie-jian","jiuyin-shengong","wuxian-bianfa","leizhendang",
                    "qianzhu-wandu","liuxing-chui","chilian-shenzhang","sanwu-shou","luoxuan-jiuying","tianmo-jieti",
                    "hujia-daofa","bizhen-qingzhang","hero-jianfa","jinshe-jian","jinshe-zhui","jinshe-zhang",
                    "panguan-bifa","qishang-quan","chuforce","shenxing-baibian","xiake-daofa","xiake-jianfa",
                    "xiake-quanjiao","xiake-shenfa","xiake-shengong","xiake-strike","pipa-shou","yanqing-quan",
                    "qinna-shou"});
  string *gumu_sks=({"xuantie-jian","jiuyin-shengong"});
  mapping mp_sks=([ "天龙寺":({"beiming-shengong","feihua-zhuyue","kurong-shengong","liumai-shenjian","shanjue","yiyang-zhi","lingbo-weibu","duanshi-shenfa","duanjia-jian"}),
  "大轮寺":({"xuedao-jing","huoyan-dao","xiangfu-lun","dashou-yin","longxiang-boruo","yuxue-dunxing","tianwang-zhua","wushang-dali"}),
  "星宿派":({"zhaixing-shou", "xingxiu-duzhang", "tianshan-zhang", "huagong-dafa", "zhaixinggong", "xiaowuxiang-gong", "mingtian-jiushi"}),
  "华山派":({"huashan-jianfa", "dugu-jiujian", "fanliangyi-dao", "hunyuan-zhang", "huashan-neigong", "zixia-shengong", "poyu-quan", "yangwu-jian", "yunushijiu-jian", "huashan-shenfa", "kuangfeng-kuaijian", "xiyi-jian"}) ]);
  
  skl = me->query_skills();
  sname = sort_array( keys(skl), (: strcmp :) );
  p_sname = filter_array( sname, (: query_skill_type :) );
  
  if ( !arg || (arg!="all" && arg!="part") )
    return notify_fail("错误的命令格式，命令格式为：huigui [all|part]。\n");
  
  //对于2015-02-01日以后注册或者出师的玩家不提供补偿
  if ( me->query("birthday")>1422720000 ||
       me->query("biography/chushi")>1422720000 )
    return notify_fail("只对2015-02-01日以前出师的玩家提供回归师门功能。\n");
    
  if ( !me->query("chushi/done") )
    return notify_fail("你没有出过师，也不需要回归师门。\n");
    
  fam=me->query("family/family_name");
  cs_fam=me->query("chushi/last_family");
  
  if ( ( arg=="part" || 
         ( fam!="星宿派" && fam!="华山派" && fam!="天龙寺" && fam!="大轮寺" ) ) &&
       cs_fam!="星宿派" && cs_fam!="华山派" && cs_fam!="天龙寺" && cs_fam!="大轮寺"  )
    return notify_fail("从你的学艺经历来看，似乎不需要回到原来师门。\n");
  
  if ( !fam || !cs_fam )
    return notify_fail("从你的学艺经历来看，似乎不需要回到原来师门。\n");
  
  if ( arg=="all" && fam=="古墓派" )
  {
    exc_sks=p_sname-(pub_sks-gumu_sks);
    inc_sks=(pub_sks-gumu_sks)-(pub_sks-p_sname);
  }
  else if ( arg=="all" )
  {
    exc_sks=p_sname-pub_sks;
    inc_sks=pub_sks-(pub_sks-p_sname);
  }
  else
  {
    if ( fam=="古墓派" )
      inc_sks=pub_sks+mp_sks[cs_fam]-gumu_sks;
    else 
      inc_sks=pub_sks+mp_sks[cs_fam];
    inc_sks=inc_sks-(inc_sks-p_sname);
    exc_sks=p_sname-inc_sks;
  }
  
  if ( sizeof(exc_sks)>0 )
  {
    printf("下列技能将被删除：\n");
    for(lp=0;lp<sizeof(exc_sks);lp++)
      printf("    %s(%s)\n", to_chinese(exc_sks[lp]), exc_sks[lp]);
  }
  
  if ( sizeof(inc_sks)>0 )
  {
    printf("\n\n下列技能将被保留：\n");
    for(lp=0;lp<sizeof(inc_sks);lp++)
      printf("    %s(%s)\n", to_chinese(inc_sks[lp]), inc_sks[lp]);
  }
  
  printf("请确认你是否回归师门，回归师门上述删除技能列表中的技能将会收回：(y--回归/n--放弃)\n");
  input_to((:confirm_huigui:), me, arg, exc_sks, inc_sks); */
  return 1;
}

void confirm_huigui(string yn, object me, string hg_type, string *exc_sks, string *inc_sks)
{
  int lp;
  
  if ( yn!="y" && yn!="Y" )
  {
    tell_object(me, "你在最后关头放弃了回归自己原来的师门。\n");
    return;
  }
  
  if ( !objectp(me) )
    return;
  
  me->set("huigui/family", me->query("family"));
  me->set("huigui/chushi", me->query("chushi"));
  me->set("huigui/class", me->query("class"));
  me->set("huigui/delete_skills", exc_sks);
  me->set("huigui/score", me->query("score"));
  me->delete("family");
  me->set("family/family_name", me->query("chushi/last_family"));
  me->set("family/generation", 99); //初始化的第几代弟子，统一先设定为99代弟子
  me->delete("chushi");
  me->delete("reborn/chushi");
  me->delete("class");
  if ( me->query("score")<20000 )
    me->set("score", 20000);
  if ( hg_type=="all" )
  {
    me->set("huigui/delete_pots", me->query("learned_points") );
    me->delete("learned_points");
  }
  
  if ( sizeof(exc_sks)>0 )
  {
    for(lp=0;lp<sizeof(exc_sks);lp++)
      me->delete_skill(exc_sks[lp]);
  }
}

int do_chaixie(string arg)
{
  object ob, who, gem;
  int capacity, lp, lev;
  string material, yinyang, *prefix;
  
  who = this_player();
  if(!userp(who))
    return 0;
  
  if(!arg)
    return notify_fail("你取出哪个装备的宝石？\n");
  
  if(!ob=present(arg,who))
    return notify_fail("你要取消哪个自动加载物品？\n");
  
  if( ob->query("equipped") )
  {
    tell_object(who,"你必须先放下这样东西方能取消自动加载。\n");
    return 1;
  }
  
  if(ob->query("gem_ob_autoloaded"))
    return notify_fail("请取消自动加载后再拆卸该物品！\n");
  
  if(!ob->is_gems() ||
     (base_name(ob)!="/obj/gem/armor" &&
      base_name(ob)!="/obj/smith/products/armor" ) )
    return notify_fail("这件东西不能拆卸宝石！\n");
  
  if ( !ob->query("armor_prop") ||
       !ob->query("armor_prop/armor_effect_armor_vs_force") ||
       (!ob->query("armor/armor") && !ob->query("armor/defence")) )
    return notify_fail("这件东西不能拆卸宝石！\n");
  
  if ( ob->query("forge/times")!=1 ||
       ob->query("forge/capacity")<=0 )
    return notify_fail("这件东西不能拆卸宝石！\n");
  
  capacity = ob->query("forge/capacity");
  for (lp=1; lp<capacity+1; lp++)
  {
    material = ob->query(sprintf("forge/material%d",lp));
    lev = ob->query(sprintf("forge/material%d_level",lp));
    yinyang = ob->query(sprintf("forge/material%d_yinyang",lp));
    
    if ( F_GEMS->valid_gem(material, lev) )
    {
      gem=F_GEMS->new_gem(material, lev, yinyang);
      gem->move(who);
      tell_object(who, query("name")+"从"+ob->query("name")+"上拆卸下一个"+gem->query("name")+"。\n");
    }
    ob->delete(sprintf("forge/material%d",lp));
    ob->delete(sprintf("forge/material%d_level",lp));
    ob->delete(sprintf("forge/material%d_yinyang",lp));
    ob->delete(sprintf("forge/material%d_type",lp));
  }
  
  ob->delete("forge/times");
  ob->delete("forge/capacity");
  ob->delete("forge/bonus");
  ob->delete("is_forging");
  ob->delete("armor_prop");
  if ( stringp(ob->query("armor/name")) )
  {
    prefix=explode(ob->query("armor/name")," ");
    ob->set("name", prefix[sizeof(prefix)-1]);
  }
  ob->delete("armor/name");
  ob->set("long","随机装备\n"+"★★★★★★"+ob->query("name")+"★★★★★★\n");
  if ( ob->query("armor/armor") )
    ob->set("armor_prop/armor", ob->query("armor/armor") );
  else if ( ob->query("armor/defence") )
    ob->set("armor_prop/armor", ob->query("armor/defence") );
  
  tell_object(who, query("name")+"将"+ob->query("name")+"上面的宝石都拆卸了下来。\n");
  who->start_busy(1);
  return 1;
}

string ask_tasktitle()
{
  object me=this_player();
  int exp=me->query("exp/task")/1000000;
  string title;
  
  if ( exp<5 )
    return "你对侠客榜任务还没有足够熟悉，不能授予你任何头衔。\n";
  else if ( exp<20 )
    title=CYN"追风"BLU"逐月"NOR;
  else if ( exp<60 )
    title=HIY"心有"HIC"灵犀"NOR;
  else
    title=HIC"风行"HIB"天下"NOR;
  
  me->set_title(({TITLE_MJOB1, TITLE_MJOB2, TITLE_MJOB3}), title, ({CYN"追风"BLU"逐月"NOR, HIY"心有"HIC"灵犀"NOR, HIC"风行"HIB"天下"NOR}));
  return "你获得了侠客榜头衔："+title+"。\n";
}

string ask_gift2017()
{
  object me=this_player();
  object newgift;

if (time()<1485446401)
{
	 return "新年还早你这么着急干啥?\n";

}

  if (time() > 1486828799)
  {
	 return "新年早过了你还来要礼物?\n";
  }
  if (me->query("age")< 18 )
  {
	return "你年纪太小了，不给礼物。\n";
  }
	if (me->query("combat_exp")< 1000000 )
  {
	return "你经验太低了，不给礼物。\n";
  }
  if (me->query("gift/2016give"))
	  {
		  me->delete("gift/2016give");
	  }
if (me->query("bonus2016"))
{
		  me->delete("bonus2016");
}


  if (me->query("gift/2017give"))
  {
	  me->start_busy(10);
	 return "已经给过你了你还来，做人不要太贪心。\n";
  }
  else
	{
		newgift=new("/d/gift/mudy/xmas/giftbag2017.c");	
		newgift->set("owner",me->query("id"));
		newgift->move(me);
		tell_object(me,HIY"你得到了"+newgift->query("name")+"!\n"NOR);	
		me->set("gift/2017give",1);
	}
}
