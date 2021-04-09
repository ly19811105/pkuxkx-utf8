// perform.c
//del poti
#include <ansi.h>
#include <char.h>
#include <weapon.h>
inherit F_SSERVER;

int old_main(object me, string arg)
{
        object weapon,weapon2;
        object target_ob,anqi_ob;
        int ret, disorder;
        string martial, action, target, anqi, buff, family, myfamily;
        string skill, force_skill, perform_file;
        //空手功夫，判断perform与持兵器状态是否相符用，如果加入新的空手功夫，需要在下面列表中添加
         string *kongshou_skill = ({"claw","finger","strike","cuff","unarmed","hand","throwing","spells","leg"});
        //可以在parry上使用perform的功夫，暂时只有flatter的qiurao和慕容的xingyi
        string *parry_skill = ({"qiurao","xingyi","bishen","yihua","xunxia","xuli","danuoyi","buzhen"});
    //可以用在非战斗对象上的perform
        string *perform_nofighting =  ({
        "danuoyi","tan","fuxue","cuiming","shoot","shuai","zhong","lianzhong","jie","liao","zhi","escape","an","pingsha"
        });
		//可以无对象使用的pfm。
        string *perform_notarget=({
		"danuoyi",
		});
		//buffer叠加检查，列表内的buffer自己本门内buffer可以叠加，跨门派buff不允许叠加
        //也就是说如果你先用了一个非本门的buffer，那么本门的buffer也叠加不上了。
        mapping buffer_check = ([
		"qiankun-danuoyi.danuoyi":"明教",
        "quanzhen-jian.tonggui":"全真派", 
        "quanzhen-jian.jianqi":"全真派", 
        "zui-gun.zuida":"少林派",
        "riyue-bian.fumoquan":"少林派",
        "ranmu-daofa.fenxin":"少林派",
        "fuliu-jian.juejian":"峨嵋派",
        "xianglong-zhang.xiao":"丐帮",
        "xueshan-jianfa.fengjian":"雪山派",
        "xueshan-jianfa.meijian":"雪山派",
        "xueshan-jianfa.shuangjian":"雪山派",
        "xueshan-jianfa.xuejian":"雪山派",
        "xueshan-jianfa.yuejian":"雪山派",
        "dugu-jiujian.pobing":"华山派",
        "lingbo-weibu.luoshen":"天龙寺",
        "tiyunzong.zong":"武当派",
        "taiji-jian.sui":"武当派",
        "pixie-jian.feiying":"日月神教",
        "pomo-jianfa.luanpomo":"日月神教",
        "yunu-jianfa.suxin":"古墓派",
        "canhe-zhi.canshang":"姑苏慕容",
        "shenghuo-lingfa.jindou":"明教",
		"qimen-baguazhen.buzhen":"桃花岛",
        "taiyi-you.lingxu":"百姓",
        "luoxuan-jiuying.xuan":"公共武学"]);


        //必须激发对应内功的 武功-内功 对照
        mapping skill_force_map = ([
        "murong-jianfa"     : "shenyuan-gong",
        //"yiyang-zhi"        : "xiantian-gong",
        "pixie-jian"        : "kuihua-shengong",
        "wuxian-jianfa"        : "riyue-shengong",
        "feihua-zhuyue"        : "beiming-shengong",
        "xianglong-zhang"   : "huntian-qigong",
        //"yunlong-zhua"      : "cangming-gong",
        "wuying-jian"       : "yijin-jing",
        "taiji-zhao"        : "taiji-shengong",
        "xingxiu-duzhang"   : "huagong-dafa",
        "xueshan-jianfa"   : "xueshan-neigong",
    ]);
        //判断bei的 mapping
        mapping prepare_skill_map;

        seteuid(getuid());

        if( environment(me)->query("no_perform") ) return notify_fail("这里禁止使用 perform 。\n");
        if( me->is_busy() ) return notify_fail("( 你上一个动作还没有完成，不能施用外功。)\n");
        if( me->query_temp("no_perform")>0 ) return notify_fail("( 你现在处于疯魔状态，无法使用外功。)\n");
        if( !arg ) return notify_fail("指令格式 perform martial.action [target]\n");
    //blind 的效果暂时没有使用
    //if( me->query_temp("blind"))
        //      return notify_fail("你什么也看不清，无法施展特殊功夫!\n");

        weapon = me->query_temp("weapon");
        weapon2 = me->query_temp("secondary_weapon");
    // 必须使用 perform martial.action [target] 的格式
        if( sscanf(arg, "%s.%s", martial, arg)!=2 ) 
        return notify_fail("指令格式 perform martial.action [target]\n");
        
		if ( sscanf(arg, "%s with %s", action, anqi)==2 ) 
		{
			if( sscanf(action, "%s %s", action, target)==2 ) 
			{
				if( me->query("id")==target ) return notify_fail("你要自杀吗？\n");
				target_ob = present(target, environment(me));
			}
			else
			{
				target_ob = offensive_target(me);
			}
			anqi_ob = F_KUNGFU->find_throwing(me, anqi); 
			// 找到暗器之后，把它挪到 me 的口袋里。
			// 1.如果暗器是在暗器袋里，这一步会把它提取出来，放在口袋里；
			// 2.如果暗器在身上，这一步会调整顺序，把它放到所有暗器的最上端，如果没有定义perform_with()函数，在perform()函数里
			// 抓取随机暗器时会优先获取到该暗器（因为它在所有暗器最上端，所以会第一个被获取到）
			// 在丢暗器的perform文件里有两个办法使用指定暗器，一个是在perform()函数里使用 "perform_use_anqi"，一个是单独定义perform_with()函数。
			// 推荐使用第二个办法。 by lordstar 2017/8/31
			if (objectp(anqi_ob))  
				anqi_ob->move(me); 
			me->set_temp("perform_use_anqi", anqi);
		}
        else if( sscanf(arg, "%s %s", action, target)==2 ) 
        {
            if( me->query("id")==target ) return notify_fail("你要自杀吗？\n");
            target_ob = present(target, environment(me));
        }
        else
        {
            action = arg;
            target_ob = offensive_target(me);
        }
        if( me == target_ob ) return notify_fail("你要自杀吗？\n");
  
        if ( sscanf(base_name(environment(me)),"/d/%*s") &&
             !sscanf(base_name(environment(me)),"/d/wizard/%*s") &&
             userp(me) )
        {
          if ( objectp(target_ob) && userp(target_ob) && me->query("xiuxian_player") && target_ob != me )
            return notify_fail("你已经退隐江湖，还是不要再惹江湖上的恩恩怨怨。\n");

          if ( objectp(target_ob) && userp(target_ob) && target_ob->query("xiuxian_player") && target_ob != me )
            return notify_fail("对方已经退隐江湖，你还忍心打搅他的清修？\n");
        }
    
		//如果是notarget的pfm就不检查target了。
        if (member_array(action,perform_notarget) == -1)
        {
			if( !target_ob) 
				return notify_fail("这里没有你要攻击的对象。\n");
			if( !target_ob->is_character()) 
				return notify_fail("你想要攻击"+target_ob->name()+"吗？这可不是个活物。\n");
			
			if (target_ob->query("uni_target"))
			if (target_ob->query("uni_target") != me)
				return notify_fail(target_ob->name()+"不想与你较量。\n");
		}
        if( !stringp(skill = me->query_skill_mapped(martial)) ) 
            return notify_fail("你请先用 enable 指令选择你要使用的外功。\n");

//buff叠加检查，非本门buff同一时间内有且只能一种，本门buff不参与叠加检查
//如果使用了本门buff，那么不能叠加其他门派的buff
//by seagate@pkuxkx
        buff=sprintf("%s.%s", skill, action);
        //如果取消buffer，则清理门派标志，防止出现错误判定
        if ( mapp(me->query_temp("active_buffer")) &&
        	   sizeof(me->query_temp("active_buffer"))==1 &&
        	   me->query_temp("active_buffer/family") )
          me->delete_temp("active_buffer");
        family=me->query_temp("active_buffer/family");
        myfamily=me->query("family/family_name");
        if ( !myfamily )
        	myfamily="百姓";
        if ( buffer_check[buff] &&
        	   stringp(family) &&
        	   ( family!=myfamily ||
        	     family!=buffer_check[buff] ) &&
        	   family!="公共武学" &&
        	   buffer_check[buff]!="公共武学" )
            return notify_fail("你的真气还未平息，请稍等再运转真气增强自身能力。\n");
        if (member_array(action,perform_notarget) == -1)
        if (objectp(target_ob) && target_ob->query_temp("dazhi-wuding") && (action!="poqi") && (action!="po"))
        {
            tell_object(target_ob,me->name()+"刚想出手，却被你防御的滴水不漏，无从下手。\n"+HIR+"你却也消耗了大量内力！\n"NOR);
            target_ob->add("neili",-400);
            tell_object(me,"你想动手，却又觉得"+target_ob->name()+"防守得一丝不漏，全无机会！\n");
            return 1;
        }
		if (objectp(target_ob) && target_ob->query_temp("zhen-douzhuan") && (action=="poqi" || action=="po"))
		{
			tell_object(target_ob,me->name()+"剑出入神，毫无招式，一不经意间，在你某处穴位上轻轻一点，你气息一滞，身形停顿了下来。\n"NOR);	
			target_ob->delete_temp("zhen-douzhuan");
			target_ob->delete_temp("active_buffer/douzhuan-xingyi.douzhuan");
			return 1;
		}

    //判定使用的内功是否符合
    if (member_array(skill,keys(skill_force_map)) != -1)
    {
        if (skill_force_map[skill] != me->query_skill_mapped("force"))
            return notify_fail(sprintf("使用%s必须激发%s为内功才能使出这个绝招。\n",
                to_chinese(skill), to_chinese(skill_force_map[skill]) ));
    }
    //判断perform是否存在            
        if( !stringp(perform_file = SKILL_D(skill)->perform_action_file(action) ) 
        ||      file_size(perform_file + ".c") <= 0 )
        return notify_fail(to_chinese(skill)+"没有 "+action+" 这个武功招式。\n");
        
    if( !me->is_fighting(target_ob) )
        if (member_array(action,perform_nofighting) == -1)
            return notify_fail(to_chinese(skill) +"的 "+action+" 只能对战斗中的对手使用。\n");

    if (me->query_temp("pfmnotallow"))
    {
        return notify_fail("你被穿心诀打碎心脉，暂时不能使用任何特殊攻击。\n"); //Zine 20101106 穿心诀
    }

    //紊乱效果，有几率perform失败
    disorder=me->query_temp("apply/disorder_percent");
    if ( disorder && random(100)<disorder )
    {
        me->start_busy(2);
        return notify_fail("你内息紊乱，施展特殊攻击失败。\n");
    }

    //判断所用perform与持兵器状态、种类是否相符
    //使用空手功夫perform，至少需要空一只手
    if (member_array(martial,kongshou_skill) != -1) 
    {
            if ( (weapon && weapon2) || (weapon && weapon->query("flag") & TWO_HANDED))      
                    return notify_fail("你必须空出一只手才能使出"+to_chinese(skill)+"的绝技。\n");
            //必须bei空手功夫才能使出空手perform，否则可能引起打task等copy skill npc时的bug
            //by icer 20050608
            prepare_skill_map = me->query_skill_prepare();
            if ( !prepare_skill_map || member_array(skill,values(prepare_skill_map)) == -1)
                    return notify_fail("你必须先prepare " + skill + "才能使出" + to_chinese(skill) + "的绝技。\n");
            if (weapon && !weapon2)
            {       //某些空手连击perform中没判断是否空手，使用兵器连击，如六脉
                    me->changewield();
                    me->set_temp("weapon_changed_for_perform",1);
            }
    }
    //判断parry.xxx是否满足要求
    else if (martial == "parry")
    {
        if (member_array(action,parry_skill) == -1)
            return notify_fail(to_chinese(skill)+"激发成招架后不能使用 "+ action +" 这个绝技。\n");
    }
    //兵器perform，需判断兵器种类和功夫种类是否相符
    else if ( martial != "dodge" && martial != "dagger")
    {
        if ( inherits(NPC, me) )
        {
            if ( (!objectp(weapon) || weapon->query("skill_type") != martial)
                  && objectp(weapon2) && weapon2->query("skill_type") == martial )
            {
                me->changewield();
                me->set_temp("weapon_changed_for_perform",1);
            }
        }

        if ( !(weapon = me->query_temp("weapon")) || ((string)weapon->query("skill_type") != martial) )
//            if (!weapon2 || ((string)weapon2->query("skill_type") != martial)) 
                return notify_fail("你要拿着 "+martial+" 类武器才能使出这种绝技。\n");

    }
	if (objectp(anqi_ob))
	{
		ret = perform_file->perform_with(me,target_ob,anqi_ob);
	}
	else
	{
		ret = 0;
	}
	if (!ret)
		ret = perform_file->perform(me,target_ob);
	me->delete_temp("perform_use_anqi");
    if (me->query_temp("weapon_changed_for_perform"))
    {
        me->changewield();
        me->delete_temp("weapon_changed_for_perform");
    }
    return ret;
}


int main(object me, string arg)
{
    //buffer叠加检查，列表内的buffer自己本门内buffer可以叠加，跨门派buff不允许叠加
    //也就是说如果你先用了一个非本门的buffer，那么本门的buffer也叠加不上了。
    mapping buffer_check = ([
    "qiankun-danuoyi.danuoyi":"明教",
    "quanzhen-jian.tonggui":"全真派", 
    "quanzhen-jian.jianqi":"全真派", 
    "zui-gun.zuida":"少林派",
    "riyue-bian.fumoquan":"少林派",
    "ranmu-daofa.fenxin":"少林派",
    "fuliu-jian.juejian":"峨嵋派",
    "xianglong-zhang.xiao":"丐帮",
    "xueshan-jianfa.fengjian":"雪山派",
    "xueshan-jianfa.meijian":"雪山派",
    "xueshan-jianfa.shuangjian":"雪山派",
    "xueshan-jianfa.xuejian":"雪山派",
    "dugu-jiujian.pobing":"华山派",
    "lingbo-weibu.luoshen":"天龙寺",
    "tiyunzong.zong":"武当派",
    "taiji-jian.sui":"武当派",
    "pixie-jian.feiying":"日月神教",
    "pomo-jianfa.luanpomo":"日月神教",
    "yunu-jianfa.suxin":"古墓派",
    "canhe-zhi.canshang":"姑苏慕容",
    "shenghuo-lingfa.jindou":"明教",
	"qimen-baguazhen.buzhen":"桃花岛",
    "taiyi-you.lingxu":"百姓",
    "luoxuan-jiuying.xuan":"公共武学"]);

    //必须激发对应内功的 武功-内功 对照
    mapping skill_force_map = ([
    "murong-jianfa"     : "shenyuan-gong",
    "douzhuan-xingyi"     : "shenyuan-gong",
    "pixie-jian"        : "kuihua-shengong",
    "wuxian-jianfa"        : "riyue-shengong",
    "feihua-zhuyue"        : "beiming-shengong",
    "xianglong-zhang"   : "huntian-qigong",
    "yunlong-zhua"      : "cangming-gong",
    "wuying-jian"       : "yijin-jing",
    "taiji-zhao"        : "taiji-shengong",
    "xingxiu-duzhang"   : "huagong-dafa",
    "xueshan-jianfa"   : "xueshan-neigong",
    ]);

    object weapon_r, weapon_l;
    object target_ob, pobj, anqi_ob;
    int ret, disorder, para, ignore;
    string martial, action, target, anqi, pfm, family, myfamily, m_mart;
    string skill, force_skill, perform_file;
    string *bs, *es, *ks;
    mixed valid_weapon;
    //判断bei的 mapping
    mapping prepare_skill_map;
    seteuid(getuid());

    /* 命令arg格式的检查 */
    // 检查perform有无入参
    if( !arg ) return notify_fail("指令格式 perform xxx.yyy [zzz]\n");
    // 检查是否符合 perform xxx.yyy [zzz] 的格式
    if( sscanf(arg, "%s.%s", skill, arg)!=2 ) return notify_fail("指令格式 perform xxx.yyy [zzz]\n");
    // 检查xxx技能是否存在
    if ( !me->query_skill(skill, 1) ) return notify_fail("你没有这个技能！\n");
    if ( me->query_skill_mapped(skill) ) 
    {
     /* if ( !userp(me) )*/
	    return old_main(me, skill+"."+arg);
/*      else
        return notify_fail("命令格式错误，请使用perform 特殊技能.外功特效。\n");*/
    }
        
    // 检查perform是否存在action和暗器
	if ( sscanf(arg, "%s with %s", action, anqi)==2 ) 
	{
			// 找到暗器之后，把它挪到 me 的口袋里。
			// 1.如果暗器是在暗器袋里，这一步会把它提取出来，放在口袋里；
			// 2.如果暗器在身上，这一步会调整顺序，把它放到所有暗器的最上端，如果没有定义perform_with()函数，在perform()函数里
			// 抓取随机暗器时会优先获取到该暗器（因为它在所有暗器最上端，所以会第一个被获取到）
			// 在丢暗器的perform文件里有两个办法使用指定暗器，一个是在perform()函数里使用 "perform_use_anqi"，一个是单独定义perform_with()函数。
			// 推荐使用第二个办法。 by lordstar 2017/8/31
		anqi_ob = F_KUNGFU->find_throwing(me, anqi); 
		if (objectp(anqi_ob))  
			anqi_ob->move(me); 
		me->set_temp("perform_use_anqi", anqi);
	}
	else
		action = arg;
	sscanf(action, "%s %s", action, target);
    if( !stringp(perform_file = SKILL_D(skill)->perform_action_file(action) ) || file_size(perform_file + ".c") <= 0 )
        return notify_fail(to_chinese(skill)+"没有 "+action+" 这个武功招式。\n");
/*    if ( perform_file->valid_target_arg("version") != 2 ) 
      return notify_fail(to_chinese(skill)+"暂时还不支持新格式。\n");;*/
    
    pobj=load_object(perform_file);
    
    pfm=sprintf("%s.%s", skill, action);
    prepare_skill_map = me->query_skill_prepare();
    
    if ( perform_file->valid_target_arg("version") != 2 )
    {
      ks=SKILL_D(skill)->query_base_kongshou();
      if ( sizeof(ks)>0 )
      {
        for(int lp=0;lp<sizeof(ks);lp++)
          if ( prepare_skill_map[ks[lp]]==skill )
            m_mart=ks[lp];
      }
    }
    
    /* 检查target及其对象是否存在、合法性，确定target_ob类型、合法性 */
    if( nullp(target) || target == "" )
    {
        // target对象对于pfm的合法性
        if( function_exists("valid_target_arg",pobj) && 
            !perform_file->valid_target_arg("null") )
            return notify_fail("请设定此招的目标对象。\n");
        para=0;
    }
    else if ( target_ob=present(target, environment(me)) )
    {	/*if (target_ob->query("safari_skill/mr1"))
		{
		target_ob=me;
		}*/
        if ( target_ob==me ) 
        {	
			
            if( function_exists("valid_target_arg",pobj) &&
                !perform_file->valid_target_arg("self") )
				{
				if (!target_ob->query("safari_skill/mr1"))
	              return notify_fail("此招的目标对象不能是自己。\n");
				}
            para=1;
			
        }
        else 
        {
            if( function_exists("valid_target_arg",pobj) &&
                !perform_file->valid_target_arg("other") )
                return notify_fail("此招不能指定其他人作为目标对象。\n");
            para=2;
            if( !target_ob->is_character() )
                return notify_fail("看清楚了！"+target_ob->name()+"可不是个活物。\n");
            if (target_ob->query("uni_target") && target_ob->query("uni_target") != me ) 
                return notify_fail(target_ob->name()+"不想与你较量。\n");
        }
    }
    else
        return notify_fail("这里没有这个对象。\n");

    if ( para==0 && 
         function_exists("valid_target_arg",pobj) &&
         !perform_file->valid_target_arg("self") && 
         sizeof(me->query_enemy())==1 ) 
      target_ob = offensive_target(me);

    if ( sscanf(base_name(environment(me)),"/d/%*s") &&
        !sscanf(base_name(environment(me)),"/d/wizard/%*s") &&
         userp(me) )
    {
      if ( objectp(target_ob) && userp(target_ob) && me->query("xiuxian_player") && target_ob != me )
        return notify_fail("你已经退隐江湖，还是不要再惹江湖上的恩恩怨怨。\n");

      if ( objectp(target_ob) && userp(target_ob) && target_ob->query("xiuxian_player") && target_ob != me )
        return notify_fail("对方已经退隐江湖，你还忍心打搅他的清修？\n");
    }

    ignore = me->query_temp("ignore_pfm_limit");
    /* 对me进行以下这些标准检查，会提供接口以便某些特定NPC可以不满足检查规则时也能通过 */
    if ( !(ignore & IGNORE_PFM_LIMIT_DEBUFF) )
    {
        if ( me->query_temp("no_perform")>0 ) return notify_fail("( 你现在处于疯魔状态，无法使用外功。)\n");//华山剑法效果？
        if ( me->query_temp("pfmnotallow") ) return notify_fail("你被穿心诀打碎心脉，暂时不能使用任何特殊攻击。\n"); //Zine 20101106 穿心诀
        disorder=me->query_temp("apply/disorder_percent");//紊乱效果，有几率perform失败
        if ( disorder && random(100)<disorder )
        {
            me->start_busy(2);
            return notify_fail("你内息紊乱，施展特殊攻击失败。\n");
        }
    }
    //房间限制
    if ( !(ignore & IGNORE_PFM_LIMIT_ROOM) )//如果“与”IGNORE_PFM_LIMIT_ROOM不为零，则无视限制
    {
        if ( environment(me)->query("no_perform") ) return notify_fail("这里禁止使用任何特殊攻击。\n");
    }
    //busy限制
    if ( !(ignore & IGNORE_PFM_LIMIT_BUSY) )
    {
        if ( me->is_busy() ) return notify_fail("( 你上一个动作还没有完成，不能施用外功。)\n");
    }
    //判定使用的内功是否符合
    if ( !(ignore & IGNORE_PFM_LIMIT_FORCE) )
    {
        if (member_array(skill,keys(skill_force_map)) != -1)
        {
            if (skill_force_map[skill] != me->query_skill_mapped("force"))
                return notify_fail(sprintf("使用%s必须激发%s才能使出这个绝招。\n",to_chinese(skill), to_chinese(skill_force_map[skill]) ));
        }
        //如果存在active_buffer，但是只有family信息，则清除active_buffer，防止异常发生
        if ( mapp(me->query_temp("active_buffer")) && sizeof(me->query_temp("active_buffer"))==1 && me->query_temp("active_buffer/family") )
            me->delete_temp("active_buffer");
        family = me->query_temp("active_buffer/family");
        myfamily = me->query("family/family_name");
        //因为没有百姓这个门派，所以myfamily为空时要赋值成 "百姓"
        if ( !myfamily ) myfamily = "百姓";
        if ( buffer_check[pfm] && stringp(family) && ( family!=myfamily || family!=buffer_check[pfm] ) && family!="公共武学" && buffer_check[pfm]!="公共武学" )
            //buff叠加检查，非本门buff同一时间内有且只能一种，本门buff不参与叠加检查，如果使用了本门buff，那么不能叠加其他门派的buff by seagate@pkuxkx
            return notify_fail("你的真气还未平息，请稍等再运转真气增强自身能力。\n");
    }
    //大智无定对作为特定目标或者唯一目标的pfm有效果，对自身和群体pfm不限制
    if ( !(ignore & IGNORE_PFM_LIMIT_BUFF) )
    {//fix下，大智对独孤九剑的poqi，pobing无效
        if ( para!=1 && objectp(target_ob) && target_ob->query_temp("dazhi-wuding") && (action!="poqi") && (action!="po"))
        {
            tell_object(target_ob,me->name()+"刚想出手，却被你防御的滴水不漏，无从下手。\n"+HIR+"你却也消耗了大量内力！\n"NOR);
            target_ob->add("neili",-400);
            tell_object(me,"你想动手，却又觉得"+target_ob->name()+"防守得一丝不漏，全无机会！\n");
            return 1;
        }
		if (para!=1 && objectp(target_ob) && target_ob->query_temp("zhen-douzhuan") && (action=="poqi" || action=="po"))
		{
			tell_object(target_ob,me->name()+"剑出入神，毫无招式，一不经意间，在你某处穴位上轻轻一点，你气息一滞，身形停顿了下来。\n"NOR);	
			target_ob->delete_temp("zhen-douzhuan");
			target_ob->delete_temp("active_buffer/douzhuan-xingyi.douzhuan");
			return 1;
		}
    }
    /* 对me进行以上这些标准检查，会提供接口以便某些特定NPC可以不满足检查规则时也能通过 */
    weapon_r = me->query_temp("weapon");
    weapon_l = me->query_temp("secondary_weapon");
    valid_weapon = perform_file->valid_weapon();

    /* 检查pfm对应的基本功夫是否存在 */
    if ( userp(me) )
    {
        bs = SKILL_D(skill)->query_base_skills(); 
        if ( arrayp(bs) )
            es = filter_array(bs, (: this_player()->query_skill($1, 1)>0 :));
        if ( !sizeof(es) )
            return notify_fail("你连"+to_chinese(skill)+"的基本功夫都不会，还想使出这个绝技？\n");
    }

    /* pfm进行规范，严格要求按右手来判断 */
    if ( objectp(weapon_r) && !SKILL_D(skill)->valid_action_wield(weapon_r, perform_file) )
    {
        if ( inherits(NPC, me) && ( !objectp(weapon_l) || ( objectp(weapon_l) && SKILL_D(skill)->valid_action_wield(weapon_l, perform_file)) )  )
        { 
            me->set_temp("weapon_changed_for_perform", 1);
            me->changewield();
        }
        else if ( userp(me) && (!objectp(weapon_l) && me->check_hand()<2) )
        {
            /* 检查pfm对应的基本功夫是否存在 */
            if( !arrayp(valid_weapon) || member_array("all", valid_weapon)==-1 )
            {
                ks = SKILL_D(skill)->query_base_kongshou();
                if ( sizeof(es-ks) == sizeof(es) )
                    return notify_fail("你连"+to_chinese(skill)+"的基本功夫都不会，还想使出这个绝技？\n");
            }
            me->set_temp("weapon_changed_for_perform", 1);
            me->changewield();
        }
        else 
        {
            martial = weapon_r->query("skill_type");
            return notify_fail("你拿着 "+martial+" 类武器无法使出这个绝技。\n");
        }
    }
    if ( !objectp(weapon_r) )
    {
        /* 检查pfm对应的基本功夫是否存在 */
        if( !arrayp(valid_weapon) || member_array("all", valid_weapon)==-1 )
        {
            ks = SKILL_D(skill)->query_base_kongshou();
            if ( sizeof(es-ks) == sizeof(es) )
                return notify_fail("你要拿着武器才能使出这种绝技。\n");
        }

        /* 检查右手空手是否为空闲状态 */
        if ( userp(me) && me->check_hand()>=2 )
        {
            valid_weapon = perform_file->valid_weapon();
            if( !arrayp(valid_weapon) || member_array("all", valid_weapon)==-1 )
                return notify_fail("你右手拿着其他东西，无法使出这个绝技。\n");
        }

        if ( inherits(NPC, me) && objectp(weapon_l) && SKILL_D(skill)->valid_action_wield(weapon_l, perform_file) )
        {
            me->set_temp("weapon_changed_for_perform", 1);
            me->changewield();
        }
    }
    
    if ( userp(me) && 
         perform_file->valid_target_arg("version") != 2 && 
         ( ( objectp(weapon_r) && me->query_skill_mapped(weapon_r->query("skill_type"))!=skill ) ||
           ( !objectp(weapon_r) && !m_mart ) ) )
      return notify_fail("该特技还不能支持新格式，想要兼容新格式，该技能必须处于激发或者准备状态。\n");

    /* 在pfm文件中需要做的：战斗状态确认、目标选择、基本技能确定、该pfm特定限制、 */

	if (objectp(anqi_ob))
	{
		ret = perform_file->perform_with(me,target_ob,anqi_ob);
	}
	else
	{
		ret = 0;
	}
	if (!ret)
		ret = perform_file->perform(me,target_ob);
	me->delete_temp("perform_use_anqi");

    if ( me->query_temp("weapon_changed_for_perform") )
    {
        me->delete_temp("weapon_changed_for_perform");
        me->changewield();
    }
	if (userp(me) && objectp(target_ob) && userp(target_ob))
	{
//先出手的做个标记，被杀的话杀人者不增加杀气，by all@2015/1/21
		if ( !environment(target_ob)->query("no_die") && !(target_ob->query("attack_player/id")==me->query("id") && time()-target_ob->query("attack_player/time")<300)
		&& !(me->query("attack_by_player/id")==target_ob->query("id") && time()-me->query("attack_by_player/time")<300))
		{
		me->set("attack_player/id",target_ob->query("id"));
		me->set("attack_player/time",time());
		target_ob->set("attack_by_player/id",me->query("id"));
		target_ob->set("attack_by_player/time",time());		
		}			
	}	
    return ret;
}

int help (object me)
{
    write(@HELP
指令格式：perform <特殊功夫>.<招式名称> [<施用对象>]

暗器攻击：perform <特殊功夫>.<招式名称> [<施用对象>] [with <暗器>]

如果你所学的特殊功夫有一些特殊的攻击方式或招式，可以用这个指令来使用。
例如太极剑法的缠字决可以用：
perform taiji-jian.chan
或
perform taiji-jian.chan xxx

再比如摘星手的弹字诀使用暗器攻击时，如果身上有很多种暗器，可以用：
perform zhaixing-shou.tan xxx with fei biao
以with <暗器>的格式来指定使用某种暗器进行攻击。
如果不指定暗器，会优先选择门派专属暗器攻击。没有携带门派专属暗器时，
使用身上携带的第一种暗器进行攻击。

HELP
    );
    return 1;
}
