// exert.c
// 加入全真派归元效果,可以在busy状态下使用。by yhzzyahoo @2015.4.21
#include <ansi.h>
inherit F_SSERVER;

int main(object me, string arg)
{
    string force,func,target,exert_file;
    object target_ob;
    int disorder;
    int wrpct;
    //对象只能是自己的
    string *target_me = ({"recover","regenerate","qi","jing", "refresh","heal","powerup","jingang","xiulian",
            "inspire","longxiang","dianhuo","taiji","xinjing",
            "shield","qudu","reverse","tiandi","zhixin","longhe","fengyun","youming","guangming","guiyuan",
            });
    //对象只能是敌人的
    string *target_enemy = ({"qisuck","jingsuck","neilisuck","maxsuck","puji","yihun","force","yinyang"});
    //无对象的
    string *target_no = ({"roar","bhcs","chang","qimen"});
    //内功的buffer仅作为资料使用，并不参与buffer叠加检查
    mapping buffer_check=([
    "taiji-shengong.powerup":"武当派",
    "taiji-shengong.taiji":"武当派",
    "yijin-jing.jingang":"少林派",
    "yijin-jing.powerup":"少林派",
    "linji-zhuang.fengyun":"峨嵋派",
    "linji-zhuang.longhe":"峨嵋派",
    "linji-zhuang.zhixin":"峨嵋派",
    "huntian-qigong.powerup":"丐帮",
    "huashan-neigong.powerup":"华山派",
    "zixia-shengong.powerup":"华山派",
    "xiantian-gong.powerup":"全真派",
	"xiantian-gong.guiyuan":"全真派",
    "cangming-gong.powerup":"天地会",
    "hamagong.reverse":"白驼山",
    "longxiang-boruo.longxiang":"大轮寺",
    "longxiang-boruo.trans":"大轮寺",
    "riyue-shengong.guangming":"日月神教",
    "kuihua-shengong.guangming":"日月神教",
    "kuihua-shengong.powerup":"日月神教",
    "shenlong-xinfa.chang":"神龙教",
    "shenlong-xinfa.powerup":"神龙教",
    "xiaowuxiang-gong.powerup":({"星宿派","灵鹫宫"}),
    "xiaowuxiang-gong.shield":({"星宿派","灵鹫宫"}),
    "bixue-xinfa.powerup":"朝廷",
    "yunu-xinfa.xinjing":"古墓派",
    "bahuang-gong.powerup":"灵鹫宫",
    "jiuyang-shengong.powerup":"明教",
    "shenyuan-gong.powerup":"姑苏慕容",
    "bihai-shengong.powerup":"桃花岛",
    "bihai-shengong.qimen":"桃花岛",       //兼有buff和debuff功效
    "taiyi-shengong.powerup":"百姓",
    "taiyi-shengong.yangjing":"百姓",
    "xiake-shengong.powerup":"公共武学",
    "jiuyin-shengong.powerup":"公共武学",
    "xixing-dafa.guangming":"日月神教"
    ]);
    seteuid(getuid());

    if( !arg ) return notify_fail("指令格式：exert|yun <功能名称> [<施用对象>]\n");
    if( sscanf(arg, "%s %s", func, target)==2 )
    {
        target_ob = present(target, environment(me));
		if( !target_ob ) return notify_fail("这里没有 " + target + "。\n");
    }
    else func = arg;

    if( me->is_busy() ) 
	{	
		if ((func=="guiyuan") && (me->query("family/family_name")=="全真派") && (me->query_skill("xiantian-gong", 1)>500))
			{
			 if( environment(me)->query("no_exert") )
				 return notify_fail("这里无法使用内功。\n");
			 if( !arg ) 
				 return notify_fail("指令格式：exert|yun <功能名称> [<施用对象>]\n");
			 if( !stringp(force = me->query_skill_mapped("force")) ) 
				 return notify_fail("你请先用 enable 指令选择你要使用的内功。\n");
			}
		else
			{
			return notify_fail("( 你上一个动作还没有完成，不能施用内功。)\n");
			}
	}
    if( me->query_temp("no_exert")>0 ) return notify_fail("( 你现在处于闭气状态，无法运用内功。)\n");
    if( environment(me)->query("no_exert") ) return notify_fail("这里无法使用内功。\n");

    if( !stringp(force = me->query_skill_mapped("force")) ) 
        return notify_fail("你请先用 enable 指令选择你要使用的内功。\n");

    /*if( sscanf(arg, "%s %s", func, target)==2 )
    {
        target_ob = present(target, environment(me));
		if( !target_ob ) return notify_fail("这里没有 " + target + "。\n");
    }
    else func = arg;
    
     */ 
    if ( time()-me->query("wrong_status")<0 )
      return notify_fail("你体力真气混乱，短时间内无法运转真气。\n");

    if (member_array(func,target_me) != -1)
        target_ob = me;
    else if (member_array(func,target_enemy) != -1)
    {
        target_ob = offensive_target(me);
        if( !target_ob ) return notify_fail(func+" 只能对战斗中的对手使用。\n");
    }
    else if (member_array(func,target_no) == -1 && !target_ob)
        return notify_fail(func+" 必须指明作用对象才能使用。\n");
    
    if ( sscanf(base_name(environment(me)),"/d/%*s") &&
         !sscanf(base_name(environment(me)),"/d/wizard/%*s") &&
         userp(me) )
    {
      if ( objectp(target_ob) && userp(target_ob) && me->query("xiuxian_player") && target_ob != me )
        return notify_fail("你已经退隐江湖，还是不要再惹江湖上的恩恩怨怨。\n");

      if ( objectp(target_ob) && userp(target_ob) && target_ob->query("xiuxian_player") && target_ob != me )
        return notify_fail("对方已经退隐江湖，你还忍心打搅他的清修？\n");
    }
        
    if(target_ob && !target_ob->is_character() )
        return notify_fail(target_ob->name()+"并不是生物，你的内功没有起到什么作用。\n");

    if(target_ob && target_ob->query("uni_target") && target_ob->query("uni_target") != me)
        return notify_fail(target_ob->name()+"没有与你理会。\n");

//紊乱效果，有几率perform失败
    disorder=me->query_temp("apply/disorder_percent");
    if ( disorder && random(100)<disorder )
    {
    	me->start_busy(1);
    	return notify_fail("你内息紊乱，施展特殊内功效果失败。\n");
    }
    
    wrpct=to_int(ceil(F_KUNGFU->kungfu_wrongpct(me)*10000));
    if ( wrpct>0 && random(10000)<wrpct ) 
    {
      me->start_busy(3);
      me->set("wrong_status",time()+60);
      message_vision( HIG"突然之间$N失去了对真气的控制，看来短时间内再也无法运转真气了。\n"NOR, me );
      return 0;
    }

    if(!stringp(exert_file=SKILL_D(force)->exert_function_file(func)) 
            || file_size(exert_file + ".c") <= 0 )
        if(!stringp(exert_file=SKILL_D("force")->exert_function_file(func)) 
                || file_size(exert_file + ".c") <= 0 )
            return notify_fail(to_chinese(force)+"没有 "+func+" 这个功能。\n");

    return exert_file->exert(me,target_ob);            
}

int help (object me)
{
    write(@HELP
指令格式：exert|yun <功能名称> [<施用对象>]
用内力进行一些特异功能，你必需要指定<功能名称>，<施用对象>则可有可无。
在你使用某一种内功的特异功能之前，你必须先用 enable 指令来指定你要使用
的内功。
如果你改变自己的内功，你原本蓄积的内力并不能直接转换过去，必须从０开始。
HELP
    );
    return 1;
}
