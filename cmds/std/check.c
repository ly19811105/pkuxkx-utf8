// skills.c

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string *skill_level_desc = ({
        BLU "不堪一击" NOR,BLU "毫不足虑" NOR,BLU "不足挂齿" NOR,BLU "初学乍练" NOR,BLU "勉勉强强" NOR,
        HIB "初窥门径" NOR,HIB "初出茅庐" NOR,HIB "略知一二" NOR,HIB "普普通通" NOR,HIB "平平淡淡" NOR,
        CYN "平淡无奇" NOR,CYN "粗通皮毛" NOR,CYN "半生不熟" NOR,CYN "马马虎虎" NOR,CYN "略有小成" NOR,
        HIC "已有小成" NOR,HIC "鹤立鸡群" NOR,HIC "驾轻就熟" NOR,HIC "青出于蓝" NOR,HIC "融会贯通" NOR,
        GRN "心领神会" NOR,GRN "炉火纯青" NOR,GRN "了然于胸" NOR,GRN "略有大成" NOR,GRN "已有大成" NOR,
        YEL "豁然贯通" NOR,YEL "出类拔萃" NOR,YEL "无可匹敌" NOR,YEL "技冠群雄" NOR,YEL "神乎其技" NOR,
        HIY "出神入化" NOR,HIY "非同凡响" NOR,HIY "傲视群雄" NOR,HIY "登峰造极" NOR,HIY "无与伦比" NOR,
        RED "所向披靡" NOR,RED "一代宗师" NOR,RED "精深奥妙" NOR,RED "神功盖世" NOR,RED "举世无双" NOR,
        WHT "惊世骇俗" NOR,WHT "撼天动地" NOR,WHT "震古铄今" NOR,WHT "超凡入圣" NOR,WHT "威镇寰宇" NOR,
        HIW "空前绝后" NOR,HIW "天人合一" NOR,MAG "深藏不露" NOR,HIM "深不可测" NOR,HIR "返璞归真" NOR
});

string *knowledge_level_desc = ({
        BLU "新学乍用" NOR,BLU "初窥门径" NOR,HIB "略知一二" NOR,HIB "半生不熟" NOR,
        CYN "马马虎虎" NOR,CYN "已有小成" NOR,HIC "融会贯通" NOR,HIC "心领神会" NOR,
        GRN "了然於胸" NOR,GRN "已有大成" NOR,YEL "非同凡响" NOR,YEL "举世无双" NOR,
        HIY "震古铄今" NOR,RED "无与伦比" NOR,WHT "超凡入圣" NOR,HIW "深不可测" NOR,
});
string *force_skill =({
        HIG"第一重楼"NOR,HIY"第一重楼"NOR,HIR"第一重楼"NOR,
        HIG"第二重楼"NOR,HIY"第二重楼"NOR,HIR"第二重楼"NOR,
        HIY"第三重楼"NOR,HIG"第三重楼"NOR,HIR"第三重楼"NOR,
        HIY"第四重楼"NOR,HIG"第四重楼"NOR,HIR"第四重楼"NOR,
        HIY"第五重楼"NOR,HIG"第五重楼"NOR,HIR"第五重楼"NOR,
        HIY"第六重楼"NOR,HIG"第六重楼"NOR,HIR"第六重楼"NOR,
        HIY"第七重楼"NOR,HIG"第七重楼"NOR,HIR"第七重楼"NOR,
        MAG"第七重楼"NOR,HIY"第八重楼"NOR,HIG"第八重楼"NOR,
        HIR"第八重楼"NOR,MAG"第八重楼"NOR,HIY"第九重楼"NOR,
        HIG"第九重楼"NOR,HIR"第九重楼"NOR,MAG"第九重楼"NOR,
        HIW"十二重楼"NOR,
            });
string skill_level(string type, int level,string skill);

int main(object me, string arg)
{
	object ob, man, *all,weapon;
	mapping fam, skl, lrn, map, prepare;
	string *sname, *mapped, opp, skill_type;
	int sp, dp, attack_points, parry_points, dodge_points;
	int i, cost;

	seteuid(getuid());

	all = all_inventory(environment(me));
	for(i=0; i<sizeof(all); i++) {
		if( living(all[i]) && !userp(all[i]) ) 
			man = all[i];
	}

	if ( !arg )
		return notify_fail("你要打听谁的技能？\n");
	else if ( sscanf(arg, "-g %s", opp )==1 )
	{
		ob=present(opp, environment(me));
		if ( !objectp(ob) || !ob->is_character() || !living(ob) )
			return notify_fail("附近没有你要观察的对象。\n");
		
		if ( ob==me )
			return notify_fail("你还需要观察你自己？\n");
		
    prepare = ob->query_skill_prepare();
	  if (!mapp(prepare)) 
		  prepare = ([]);
	  if( objectp(weapon = ob->query_temp("weapon")) )
		  skill_type = weapon->query("skill_type");
	  else if (!sizeof(prepare))
		  skill_type = "unarmed";
	  else if ( sizeof(prepare))
		  skill_type = (keys(prepare))[0];

	  attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	  parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	  dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
	  me->set("last_attack_info/id", ob->query("id") );
	  me->set("last_attack_info/name", ob->query("name") );
	  me->set("last_attack_info/attack", attack_points );
	  me->set("last_attack_info/parry", parry_points );
	  me->set("last_attack_info/dodge", dodge_points );
	  me->set("last_attack_info/time", time());
	  if ( ob->query("zyhb") || ob->query_temp("can_zyhb") )
	  	me->set("last_attack_info/hubo" , 1);
	  else
	  	me->set("last_attack_info/hubo" , 0);

	  if ( ob->query_skill("qiankun-danuoyi", 1 )>=200 )
	  {
	  	me->set("last_attack_info/absorb/skill" , "qiankun-danuoyi");
	  	me->set("last_attack_info/absorb/level" , ob->query_skill("qiankun-danuoyi", 1 ) );
	  }
	  else if ( ob->query_skill("iron-cloth") >= 300 )
	  {
	  	me->set("last_attack_info/absorb/skill" , "iron-cloth");
	  	me->set("last_attack_info/absorb/level" , ob->query_skill("iron-cloth") );
	  }
 	  else if ( ob->query_skill("douzhuan-xingyi") >= 300 )
	  {
	  	me->set("last_attack_info/absorb/skill" , "douzhuan-xingyi");
	  	me->set("last_attack_info/absorb/level" , ob->query_skill("douzhuan-xingyi") );
	  }

	  
	  tell_object(me , "你仔细的观察了对方，将对方的情况记录下来，可以用status_me -a命令来查看结果。\n");
	  return 1;
	}

  if ( present(arg, environment(me)) )
		return notify_fail("你要打听的人就在边上，在这里问不大妥当吧？\n");

	if ( !objectp(man) )
		return notify_fail("周围没人能帮你去了解别人的技能！\n");

  if ( (!(fam = me->query("family")) || fam["family_name"] != "丐帮") )
		return notify_fail("只有乞丐才能打探别人的技能！\n");

  if ( me->query_skill("checking",1) < 10 )
		return notify_fail("你的打探本领尚未纯熟，无法了解别人的技能！\n");

	ob = find_player(arg);
	if (!ob) ob = find_living(arg);
        if (wiz_level(ob) > 0) return notify_fail("你要打听谁的技能？\n");
	if (!ob) return notify_fail("你要打听谁的技能？\n");

	if ( ob == me )
		return notify_fail("你没这麽笨吧，要别人告诉你自己的技能？\n");

	cost = me->query("max_jing")/(me->query_skill("checking",1)/10) - 10;

	if ( me->query("jing") <= cost )
		return notify_fail("现在你太累了，无法去打听别人的技能。\n");

	tell_object(me, "你走上前去，小心翼翼地向" + man->name() + "打听关于" + ob->name() + "的情况 ...\n\n");
	message("vision", "只见" + me->name() + "陪着笑脸跟" + man->name() + "说着话，好象在打听些什么。\n\n", 
		environment(me), ({ me, man }) );

	sp = me->query_skill("checking")*10 + me->query("kar")*5 + me->query("jing") + man->query("jing");
	dp = ob->query("kar")*5 + ob->query("jing")*2;
	
        if ( random(sp) < random(dp) || 
        	(int)me->query("combat_exp")<(int)ob->query("combat_exp")/6 )
		return notify_fail( man->name() + "摇了摇头，说道：这事我可不清楚，"
		 	+ RANK_D->query_respect(me) + "还是去向别人打听一下吧！\n");

	me->receive_damage("jing", cost );

	skl = ob->query_skills();
	if(!sizeof(skl)) {
		write( man->name() + "告诉你： " + ob->name() + "目前并没有学会任何技能。\n");
		return 1;
	}
	if(random(2) )
	   tell_object(ob,"你打了一个哆嗦，皱了皱眉，感觉"+me->name()+"正在打听你的技能。\n");
	write( man->name() + "告诉你： " + ob->name() +"目前所学过的技能：\n\n");
	sname  = sort_array( keys(skl), (: strcmp :) );
	
	map = ob->query_skill_map();
	if( mapp(map) ) mapped = values(map);
	if( !mapped ) mapped = ({});

	lrn = ob->query_learned();
	if( !mapp(lrn) ) lrn = ([]);
	
	i = random(sizeof(skl));

	printf("%s%s%-40s" NOR " - %-10s %3d/%5d\n", 
		(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
		(member_array(sname[i], mapped)==-1? "  ": "□"),
		to_chinese(sname[i]) + " (" + sname[i] + ")",
		skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
		skl[sname[i]], (int)lrn[sname[i]],
	);

	write("\n");
	return 1;
}

string skill_level(string type, int level,string skill)
{
        int grade;

        grade = level / 10;
        if(!type) type="martial";
       	if( !find_object(PLAYER_SKILL_D(skill)) && file_size(PLAYER_SKILL_D(skill)+".c") < 0)//判断是否是非自创武功
		{
        if(SKILL_D(skill)->valid_enable("force") ) {
                if(grade >=sizeof(force_skill))
                grade=sizeof(force_skill)-1;
                return force_skill[grade];
        }
		}
        grade = level / 12;
        switch(type) {
                case "knowledge":
                     grade = level /20;
                     if( grade >= sizeof(knowledge_level_desc) )
                     grade = sizeof(knowledge_level_desc)-1;
                     return knowledge_level_desc[grade];
                default:
                     if( grade >= sizeof(skill_level_desc) )
                     grade = sizeof(skill_level_desc)-1;
                     return skill_level_desc[grade];
        }
}

int help(object me)
{
	write(@HELP
指令格式 : check [<某人>]

这个指令可以让你打听别人所学过的技能。

你也可以指定一个和你有师徒关系的对象，用 skills|cha 可以查知对方的技能状况。

此命令为丐帮弟子专用，并需学习相应的技能。

指令格式：check -g <某人>

查询对方的一般信息，所有人都可以使用，查询后score命令就会显示出查询结果。

HELP
    );
    return 1;
}

