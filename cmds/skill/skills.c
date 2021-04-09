// skills.c

#include <ansi.h>

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
string *force_skill =({
        HIG"第一重楼"NOR,HIY"第一重楼"NOR,HIR"第一重楼"NOR,
        HIG"第二重楼"NOR,HIY"第二重楼"NOR,HIR"第二重楼"NOR,
        HIY"第三重楼"NOR,HIG"第三重楼"NOR,HIR"第三重楼"NOR,
        HIY"第四重楼"NOR,HIG"第四重楼"NOR,HIR"第四重楼"NOR,
        HIY"第五重楼"NOR,HIG"第五重楼"NOR,HIR"第五重楼"NOR,
        HIY"第六重楼"NOR,HIG"第六重楼"NOR,HIR"第六重楼"NOR,
        HIY"第七重楼"NOR,HIG"第七重楼"NOR,HIR"第七重楼"NOR,MAG"第七重楼"NOR,
        HIY"第八重楼"NOR,HIG"第八重楼"NOR,HIR"第八重楼"NOR,MAG"第八重楼"NOR,
        HIY"第九重楼"NOR,HIG"第九重楼"NOR,HIR"第九重楼"NOR,MAG"第九重楼"NOR,
        HIY"第十重楼"NOR,HIG"第十重楼"NOR,HIR"第十重楼"NOR,MAG"第十重楼"NOR,
        HIY"十一重楼"NOR,HIG"十一重楼"NOR,HIR"十一重楼"NOR,MAG"十一重楼"NOR,
        HIY"十二重楼"NOR,HIG"十二重楼"NOR,HIR"十二重楼"NOR,MAG"十二重楼"NOR,HIW"十二重楼"NOR,
            });
string *knowledge_level_desc = ({
        BLU "新学乍用" NOR,BLU "初窥门径" NOR,HIB "略知一二" NOR,HIB "半生不熟" NOR,
        CYN "马马虎虎" NOR,CYN "已有小成" NOR,HIC "融会贯通" NOR,HIC "心领神会" NOR,
        GRN "了然於胸" NOR,GRN "已有大成" NOR,YEL "非同凡响" NOR,YEL "举世无双" NOR,
        HIY "震古铄今" NOR,RED "无与伦比" NOR,WHT "超凡入圣" NOR,HIW "深不可测" NOR,
});

string skill_level(string type, int level,string skill);
string query_skill_type(string sk_id);
int query_type_cnt(string *sk_keys, string skill_type);
string show_skill_info(object ob, string sk_id, string *mapped, int type);
string show_subskill(object ob, string root_sk);
nosave int skmod;
nosave string root_skill;

int show_skill(object me,object ob)
{
	mapping skl, map,aa;
    string *sname, *mapped,skill,msg,type;
    int i,j;
    string usage, *sk, *pars;
    int opt_spec,opt_base;
	skl = ob->query_skills();
    if(!sizeof(skl) && ! ob->query_temp("apply_skills")) {
        write( (ob==me ? "你" : ob->name()) + "目前并没有学会任何技能。\n");
        return 1;
    }
   
    map = ob->query_skill_map();
    if( mapp(map) ) mapped = values(map);
    if( !mapped ) mapped = ({});

    sk = keys(skl);
	  for(i=0; i<sizeof(skl); i++) {
	    if( intp(skl[sk[i]]) && skl[sk[i]]<=0 )
      {
	      map_delete(skl, sk[i]);
      }
      else if ( mapp(skl[sk[i]]) && skl[sk[i]]["level"]<=0 )
      {
	      map_delete(skl, sk[i]);
      }
    }
		sname  = sort_array( keys(skl), (: strcmp :) );

//显示某个多层技能的具体技能细节
    if ( skmod )
    {
    	if ( !mapp(skl[root_skill]) )
    		return notify_fail("技能"+root_skill+"并不是多层技能。\n");
    	
    	write( "[44;1m[1;33m"+(ob==me ? "你" : ob->name()) +"[44;1m[1;33m学习的"+to_chinese(root_skill)+" ("+root_skill+")详细技能组成情况：[37;0m\n\n");
    	write("[32m┌------------------------------------------------------------------┐[37;0m\n");
    	write("[32m│[37;0m技能名称                         有效等级 ( 技能等级 / 技能经验 ) [32m│[37;0m\n");
    	write(sprintf( show_skill_info(ob, root_skill, mapped, 1) ));
    	write(sprintf( show_subskill(ob, root_skill) ));
    	write("[32m└------------------------------------------------------------------┘[37;0m\n");
    	return 1;
    }    	
    
    write( "[44;1m[1;33m"+(ob==me ? "你" : ob->name()) +"[44;1m[1;33m目前所学过的技能：（共"+chinese_number(sizeof(skl))+"项技能，你的技能等级最多能达到"+chinese_number(ob->query_skill_limit())+"级）[37;0m\n\n");    
    j=query_type_cnt( sname, "profession" );
    if(j>0) { write(sprintf("[32m┌[42m%21s    [40m[32m-------------------------------------------┐[37;0m\n", "[37m"+chinese_number(j)+"项职业技能"));}
    for(i=0; i<sizeof(skl); i++) {
      if( query_skill_type(sname[i])=="profession" ) {
        write(sprintf( show_skill_info(ob, sname[i], mapped, 0) ));
      }
    }    
    if(j>0) { write("[32m└-------------------------------------------------------------------┘[37;0m\n");}
    
    j=query_type_cnt( sname, "knowledge" );   	
    if(j>0) { write(sprintf("[32m┌[42m%21s    [40m[32m-------------------------------------------┐[37;0m\n", "[37m"+chinese_number(j)+"项基本知识"));}
    for(i=0; i<sizeof(skl); i++) {
     	if( query_skill_type(sname[i])=="knowledge" ) {
     	
        write(sprintf( show_skill_info(ob, sname[i], mapped, 0) ));
      }
    }    
    if(j>0) { write("[32m└--------------------------------------------------------------------┘[37;0m\n");}
	  
	  j=query_type_cnt( sname, "base" );    
    if(j>0) { write(sprintf("[32m┌[42m%21s    [40m[32m-------------------------------------------┐[37;0m\n", "[37m"+chinese_number(j)+"项基本功夫"));}
    for(i=0; i<sizeof(skl); i++) {
      if( query_skill_type(sname[i])=="base" ) {
        write(sprintf( show_skill_info(ob, sname[i], mapped, 0)) );
      }
    }    
    if(j>0) { write("[32m└--------------------------------------------------------------------┘[37;0m\n");}

	  j=query_type_cnt( sname, "special" );
    if(j>0) { write(sprintf("[32m┌[42m%21s    [40m[32m------------------------------------------┐[37;0m\n", "[37m"+chinese_number(j)+"项特殊功夫"));}
    for(i=0; i<sizeof(skl); i++) 
	{
		if (find_object(PLAYER_SKILL_D(sname[i])))
      //if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
		{
			if( query_skill_type(sname[i])=="special" ) 
			{
				write(sprintf( show_skill_info(ob, sname[i], mapped, 1) ));
			}
			continue;
		}
		if( query_skill_type(sname[i])=="special"&&find_object(SKILL_D(sname[i]))) 
		write(sprintf( show_skill_info(ob, sname[i], mapped, 0)) );
    }    
    if(j>0) { write("[32m└-------------------------------------------------------------------┘[37;0m\n");}

	skl= ob->query_temp("apply_skills");
	if (mapp(skl)){
		sk = keys(skl);
		for(i=0; i<sizeof(skl); i++) {
			if( intp(skl[sk[i]]) && skl[sk[i]]<=0 )
			{
				map_delete(skl, sk[i]);
			}
			else if ( mapp(skl[sk[i]]) && skl[sk[i]]["level"]<=0 )
			{
				map_delete(skl, sk[i]);
			}
			else if ( !ob->temp_skill_valid(sk[i]))
			{
				map_delete(skl, sk[i]);
			}
		}
		sk = keys(skl);
		j = sizeof(sk);
		if (j>0)
		{
			sname  = sort_array( sk, (: strcmp :) );
			write(sprintf("[32m┌[42m%21s    [40m[32m----------------------------------------------┐[37;0m\n", "[37m"+chinese_number(j)+"项临时技能"));
			for(i=0; i<sizeof(sk); i++) {
				write(sprintf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %4d/%7d[32m│[37;0m\n",
				(member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
				"",(to_chinese(sname[i]) + " (" + sname[i] + ")"),
				skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
				skl[sname[i]], 0 ));
			}
			write("[32m└------------------------------------------------------------------┘[37;0m\n");
		}	
	}
    return 1;
}
mixed main(object me, string arg)
{
	object ob;
    string *pars;

    seteuid(getuid());
    
    skmod=0;
    if(!arg)
        ob = me;
    else {
        pars=explode(arg," ");
        if ( sizeof(pars)>=2 && pars[0]=="-sub" )
        {
        	skmod=1;
        	root_skill=pars[1];
        	if ( sizeof(pars)==3 )
        	{
        		ob=present(pars[2], environment(me));
        		if (!ob) ob = find_player(pars[2]);
            if (!ob) ob = find_living(pars[2]);
            if (wizardp(me))  
            {  
              if( !ob ) ob = LOGIN_D->find_body(pars[2]);
            }
            if (!ob) 
    	        return notify_fail("周围有这个人吗？只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");
    	    }
    	    else if ( sizeof(pars)==4 )
    	    {
        		ob=present(pars[2]||" "||pars[3], environment(me));
            if (!ob) ob = find_living(pars[2]||" "||pars[3]);
            if (!ob) 
    	        return notify_fail("周围有这个人吗？只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");
    	    }
    	    else
    	    	ob=me;
    	  }
    	  else
    	  {
          ob = present(arg, environment(me));
          if (!ob) ob = find_player(arg);
          if (!ob) ob = find_living(arg);
    
          if (wizardp(me))  
          {
            if( !ob ) ob = LOGIN_D->find_body(arg);
          }
    
          if (!ob) 
    	      return notify_fail("周围有这个人吗？只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");
    	  }
    }

    if ( ob!=me && !wizardp(me) && 
    	   !ob->is_apprentice_of(me) && 
    	   !me->is_apprentice_of(ob) && 
    	   me->query("marry/lover") != ob->query("id") &&
		     me->query("suicongdizi/npc") != ob )
      return notify_fail("周围有这个人吗？只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");
	return show_skill(me,ob);
}

string skill_level(string type, int level,string skill)
{
    int grade;

    grade = level / 30;
    if(!type) type="martial";
    if( !find_object(PLAYER_SKILL_D(skill)) && file_size(PLAYER_SKILL_D(skill)+".c") < 0)//判断是否是非自创武功
		{
        if(SKILL_D(skill)->valid_enable("force") ) 
        {
                if(grade >=sizeof(force_skill))
                        grade=sizeof(force_skill)-1;
                return force_skill[grade];
        }
		}
		
    grade = level / 30;
    switch(type) 
    {
        case "knowledge":
                grade = level /50;
                if( grade >= sizeof(knowledge_level_desc) )
                        grade = sizeof(knowledge_level_desc)-1;
                return knowledge_level_desc[grade];
        default:
                if( grade >= sizeof(skill_level_desc) )
                        grade = sizeof(skill_level_desc)-1;
                return skill_level_desc[grade];
    }
}

string pet_skill(object ob)
{
	  string desc;
    object  *list, couple_ob;
    mapping skl, lrn, map;
    string *sname, *mapped,target,cardname;
    int i, marry_flag;
    skl = ob->query_skills();
    if(!sizeof(skl)) {
        desc =  ob->name() + "目前并没有学会任何技能。\n";
        return desc;
    }
    desc =  ob->name() +"目前所学过的技能：\n\n";
    sname  = sort_array( keys(skl), (: strcmp :) );

    map = ob->query_skill_map();
    if( mapp(map) ) mapped = values(map);
    if( !mapped ) mapped = ({});

    lrn = ob->query_learned();
    if( !mapp(lrn) ) lrn = ([]);

    for(i=0; i<sizeof(skl); i++) {
        desc +=  sprintf("%s%s%-40s" NOR " - %-10s %3d/%5d\n",
           (lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
           (member_array(sname[i], mapped)==-1? "  ": "＊"),
           to_chinese(sname[i]) + " (" + sname[i] + ")",
           skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
           skl[sname[i]], (int)lrn[sname[i]]);
    }
    return desc +"\n";
}

//查询技能对应的技能类型
string query_skill_type(string sk_id)
{
	string *base_list=
	  ({"array", "axe", "blade", "claw", "club", "cuff", "dagger", "dodge", "finger", "force",
		  "fork", "halberd", "hammer", "hand", "hook", "iron-cloth", "leg", "magic", "move", 
		  "parry", "pestle", "spear", "spells", "staff", "stick", "strike", "sword", "throwing", 
		  "unarmed", "whip", "checking", "digging", "swimming"});
  
  if( member_array(sk_id, base_list)>=0 )
  	return "base";
  	
  if( !find_object(SKILL_D(sk_id)) && file_size(SKILL_D(sk_id)+".c") < 0 ) //判断是否是自创武功
    return "special";
  
  if ( SKILL_D(sk_id)->type()=="profession" )
  	return "profession";
  
  if ( SKILL_D(sk_id)->type()=="knowledge" )
  	return "knowledge";
  
  return "special";
}

//统计指定类型的技能数量
int query_type_cnt(string *sk_keys, string skill_type)
{
	  int cnt=0;
	  
    for(int i=0; i<sizeof(sk_keys); i++)
		{
      if( skill_type!="special" && 
      	  !find_object(SKILL_D(sk_keys[i])) && 
      	  file_size(SKILL_D(sk_keys[i])+".c") < 0 )//判断是否是自创武功
			  continue;
      
      if( query_skill_type(sk_keys[i])==skill_type) 
      	cnt++;
    }
    
    return cnt;
}

//显示技能信息，type为是否玩家技能标志 0-一般技能 1-玩家自定义技能
string show_skill_info(object ob, string sk_id, string *mapped, int type)
{
	mapping skl,lrn;
	
	skl = ob->query_skills();
  if(userp(ob)) 
  	lrn = ob->query_learned();
  else {
    if(!mapp(ob->query("learned")))
      ob->set("learned",([]));
    lrn=ob->query("learned");
  }
  if( !mapp(lrn) ) lrn = ([]);
	
	if ( !mapp(skl[sk_id]) && !type )
	  return sprintf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %4d/%7d[32m│[37;0m\n",
            (member_array(sk_id, mapped)==-1? "  ": "[1;32m□[37;0m"),
            ((lrn[sk_id] >= (skl[sk_id]+1) * (skl[sk_id]+1)) ? HIM : ""),
            (to_chinese(sk_id) + " (" + sk_id + ")"),
            skill_level(SKILL_D(sk_id)->type(), skl[sk_id],sk_id),
            skl[sk_id], (int)lrn[sk_id]);
  else if ( !mapp(skl[sk_id]) && type )
	  return sprintf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %4d/%7d[32m│[37;0m\n",
            (member_array(sk_id, mapped)==-1? "  ": "[1;32m□[37;0m"),
            ((lrn[sk_id] >= (skl[sk_id]+1) * (skl[sk_id]+1)) ? HIM : ""),
            (to_chinese(sk_id) + " (" + sk_id + ")"),
            skill_level(PLAYER_SKILL_D(sk_id)->type(), skl[sk_id],sk_id),
            skl[sk_id], (int)lrn[sk_id]);
  else
	  return sprintf("[32m│[37;0m%-58s" NOR " - %-10s %4d/%7d[32m│[37;0m\n",
            (type?HIM"[-]"NOR:HIY"[+]"NOR)+(to_chinese(sk_id) + " (" + sk_id + ")"),
            skill_level(SKILL_D(sk_id)->type(), skl[sk_id]["level"], sk_id ),
            skl[sk_id]["level"], 0 );
}

//显示多层技能根技能下面子技能信息
string show_subskill(object ob, string root_sk)
{
	mapping skl, rt_skl;
	string *rt_key, *sub_key, *delkey, output;
	int lp,p2;
	
	skl = ob->query_skills();
	rt_skl=skl[root_sk];
	rt_key=keys(rt_skl);
	delkey=({});
	for(lp=0;lp<sizeof(rt_key);lp++)
	{
    if ( !mapp(rt_skl[rt_key[lp]]) )
   	  delkey+=({rt_key[lp]});
  }
  rt_key-=delkey;
  rt_key = sort_array( rt_key, (: strcmp :) );
  output="";
  for(lp=0;lp<sizeof(rt_key);lp++)
  {
  	output+=sprintf("[32m│[37;0m%-42s" NOR " - %4d"YEL "( %4d/%7d )"NOR" [32m│[37;0m\n",
            "①.."+(SKILL_D(root_sk)->skill_name(rt_key[lp]) + " (" + rt_key[lp] + ")"),
            rt_skl[rt_key[lp]]["level"], rt_skl[rt_key[lp]]["self_level"],
            rt_skl[rt_key[lp]]["learned"] );
    sub_key=keys(rt_skl[rt_key[lp]]);
    delkey=({});
    for(p2=0;p2<sizeof(sub_key);p2++)
	  {
      if ( !mapp(rt_skl[rt_key[lp]][sub_key[p2]]) )
   	    delkey+=({sub_key[p2]});
    }
    sub_key-=delkey;
    sub_key = sort_array( sub_key, (: strcmp :) );
    for(p2=0;p2<sizeof(sub_key);p2++)
      output+=sprintf("[32m│[37;0m%-42s" NOR " - %4d"YEL "( %4d/%7d )"NOR" [32m│[37;0m\n",
            "②...."+(SKILL_D(root_sk)->skill_name(sub_key[p2]) + " (" + sub_key[p2] + ")"),
            rt_skl[rt_key[lp]][sub_key[p2]]["level"], rt_skl[rt_key[lp]][sub_key[p2]]["level"],
            rt_skl[rt_key[lp]][sub_key[p2]]["learned"] );
  }
  return output;
}

int help(object me)
{
        write(@HELP
指令格式 : skills|cha [<某人>]

这个指令可以让你(你)查询所学过的技能。

指令格式 : skills|cha -sub <某多层技能> [<某人>]

这个指令格式可以查看上一个格式中显示带"[+]"字样的多层技能的里面具体子技
能的等级情况，在这里不同层级的子技能前面有层级编号，每个子技能显示有两个
等级，左边的等级是有效等级，右边括号里面的等级是技能自身的级别。

你也可以指定一个和你有师徒关系的对象或你的配偶，用 skills 可以查知对方的
技能状况。

巫师可以查询任何人或 NPC 的技能状况。

HELP
    );
    return 1;
}
