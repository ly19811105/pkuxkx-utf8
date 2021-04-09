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
        HIY"第七重楼"NOR,HIG"第七重楼"NOR,HIR"第七重楼"NOR,
MAG"第七重楼"NOR,
        HIY"第八重楼"NOR,HIG"第八重楼"NOR,HIR"第八重楼"NOR,
MAG"第八重楼"NOR,
        HIY"第九重楼"NOR,HIG"第九重楼"NOR,HIR"第九重楼"NOR,
MAG"第九重楼"NOR,
        HIW"十二重楼"NOR,
            });
string *knowledge_level_desc = ({
        BLU "新学乍用" NOR,BLU "初窥门径" NOR,HIB "略知一二" NOR,HIB "半生不熟" NOR,
        CYN "马马虎虎" NOR,CYN "已有小成" NOR,HIC "融会贯通" NOR,HIC "心领神会" NOR,
        GRN "了然於胸" NOR,GRN "已有大成" NOR,YEL "非同凡响" NOR,YEL "举世无双" NOR,
        HIY "震古铄今" NOR,RED "无与伦比" NOR,WHT "超凡入圣" NOR,HIW "深不可测" NOR,
});

string skill_level(string type, int level,string skill);
void show_special_skill(object ob);

mixed main(object me, string arg)
{
        object ob;
        mapping skl, lrn, map,aa;
        string *sname, *mapped,skill,msg,type;
        int i,j;
        string usage, *sk;
        int opt_spec,opt_base;

        seteuid(getuid());

        if(!arg)
                ob = me;
        else{
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
        if (wizardp(me))  {
        if( !ob ) ob = LOGIN_D->find_body(arg);
        }
                if (!ob) return notify_fail("周围有这个人吗？只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");
        }

        if( ob!=me && !wizardp(me) && !ob->is_apprentice_of(me)
        && !me->is_apprentice_of(ob) && me->query("marry/lover") != ob->query("id") )
                return notify_fail("周围有这个人吗？只有巫师，夫妻，或有师徒关系的人能察看他人的技能。\n");

        skl = ob->query_skills();
        if(!sizeof(skl)) {
                write( (ob==me ? "你" : ob->name()) + "目前并没有学会任何技能。\n");
				show_special_skill(ob);
                return 1;
        }
        write( "[44;1m[1;33m"+(ob==me ? "你" : ob->name()) +"[44;1m[1;33m目前所学过的技能：（共"+chinese_number(sizeof(skl))+"项技能）[37;0m\n\n");
			sname  = sort_array( keys(skl), (: strcmp :) );

        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        if(userp(ob)) lrn = ob->query_learned();
        else {
                if(!mapp(ob->query("learned")))
                ob->set("learned",([]));
                lrn=ob->query("learned");
        }
        if( !mapp(lrn) ) lrn = ([]);

 sk = keys(skl);
	for(i=0; i<sizeof(skl); i++) {
	if( skl[sk[i]]<=0 )
{
	map_delete(skl, sk[i]);
}
}
        for(i=0; i<sizeof(skl); i++)
		{
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
			continue;
       if(SKILL_D(sname[i])->type()=="knowledge") j=j+1;
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项知识");}
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
				continue;
        	if(SKILL_D(sname[i])->type()=="knowledge"){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n",
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}

	j=0;
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
			continue;
                if(SKILL_D(sname[i])->type() != "knowledge" && (sname[i] == "array" || sname[i] == "axe" || sname[i] == "blade" || sname[i] == "claw"
|| sname[i] == "club" || sname[i] == "cuff" || sname[i] == "dagger" || sname[i] == "dodge" || sname[i] == "finger" || sname[i] == "force" || sname[i] == "fork"
|| sname[i] == "halberd" || sname[i] == "hammer" || sname[i] == "hand" || sname[i] == "hook" || sname[i] == "iron-cloth" || sname[i] == "leg" || sname[i] == "magic" 
|| sname[i] == "move" || sname[i] == "parry" || sname[i] == "pestle" || sname[i] == "spear" || sname[i] == "spells" || sname[i] == "staff" || sname[i] == "stick" 
|| sname[i] == "strike" || sname[i] == "sword" || sname[i] == "throwing" || sname[i] == "unarmed" || sname[i] == "whip"|| sname[i] == "checking" || sname[i] == "digging" 
|| sname[i] == "swimming"))
		{
        	j=j+1;
                }
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项基本功夫");}
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
				continue;
                if(SKILL_D(sname[i])->type() != "knowledge" && (sname[i] == "array" || sname[i] == "axe" || sname[i] == "blade" || sname[i] == "claw"
|| sname[i] == "club" || sname[i] == "cuff" || sname[i] == "dagger" || sname[i] == "dodge" || sname[i] == "finger" || sname[i] == "force" || sname[i] == "fork"
|| sname[i] == "halberd" || sname[i] == "hammer" || sname[i] == "hand" || sname[i] == "hook" || sname[i] == "iron-cloth" || sname[i] == "leg" || sname[i] == "magic" 
|| sname[i] == "move" || sname[i] == "parry" || sname[i] == "pestle" || sname[i] == "spear" || sname[i] == "spells" || sname[i] == "staff" || sname[i] == "stick" 
|| sname[i] == "strike" || sname[i] == "sword" || sname[i] == "throwing" || sname[i] == "unarmed" || sname[i] == "whip"|| sname[i] == "checking" || sname[i] == "digging" 
|| sname[i] == "swimming"))
		{
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n",
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}

	j=0;
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
		{
                if(PLAYER_SKILL_D(sname[i])->type() != "knowledge" && (sname[i] != "array" && sname[i] != "axe" && sname[i] != "blade" && sname[i] != "claw"
&& sname[i] != "club" && sname[i] != "cuff" && sname[i] != "dagger" && sname[i] != "dodge" && sname[i] != "finger" && sname[i] != "force" && sname[i] != "fork"
&& sname[i] != "halberd" && sname[i] != "hammer" && sname[i] != "hand" && sname[i] != "hook" && sname[i] != "iron-cloth" && sname[i] != "leg" && sname[i] != "magic" 
&& sname[i] != "move" && sname[i] != "parry" && sname[i] != "pestle" && sname[i] != "spear" && sname[i] != "spells" && sname[i] != "staff" && sname[i] != "stick" 
&& sname[i] != "strike" && sname[i] != "sword" && sname[i] != "throwing" && sname[i] != "unarmed" && sname[i] != "whip"&& sname[i] != "checking" && sname[i] != "digging" 
&& sname[i] != "swimming"))
		{
        	j=j+1;
			}
				continue;
		}
        	if(SKILL_D(sname[i])->type() != "knowledge" && (sname[i] != "array" && sname[i] != "axe" && sname[i] != "blade" && sname[i] != "claw"
&& sname[i] != "club" && sname[i] != "cuff" && sname[i] != "dagger" && sname[i] != "dodge" && sname[i] != "finger" && sname[i] != "force" && sname[i] != "fork"
&& sname[i] != "halberd" && sname[i] != "hammer" && sname[i] != "hand" && sname[i] != "hook" && sname[i] != "iron-cloth" && sname[i] != "leg" && sname[i] != "magic" 
&& sname[i] != "move" && sname[i] != "parry" && sname[i] != "pestle" && sname[i] != "spear" && sname[i] != "spells" && sname[i] != "staff" && sname[i] != "stick" 
&& sname[i] != "strike" && sname[i] != "sword" && sname[i] != "throwing" && sname[i] != "unarmed" && sname[i] != "whip"&& sname[i] != "checking" && sname[i] != "digging" 
&& sname[i] != "swimming")){
        	j=j+1;
                }
        }
        if(j>0) { printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m"+chinese_number(j)+"项特殊功夫");}
        for(i=0; i<sizeof(skl); i++) {
       	if( !find_object(SKILL_D(sname[i])) && file_size(SKILL_D(sname[i])+".c") < 0)//判断是否是自创武功
		{
                if(PLAYER_SKILL_D(sname[i])->type() != "knowledge" && (sname[i] != "array" && sname[i] != "axe" && sname[i] != "blade" && sname[i] != "claw"
&& sname[i] != "club" && sname[i] != "cuff" && sname[i] != "dagger" && sname[i] != "dodge" && sname[i] != "finger" && sname[i] != "force" && sname[i] != "fork"
&& sname[i] != "halberd" && sname[i] != "hammer" && sname[i] != "hand" && sname[i] != "hook" && sname[i] != "iron-cloth" && sname[i] != "leg" && sname[i] != "magic" 
&& sname[i] != "move" && sname[i] != "parry" && sname[i] != "pestle" && sname[i] != "spear" && sname[i] != "spells" && sname[i] != "staff" && sname[i] != "stick" 
&& sname[i] != "strike" && sname[i] != "sword" && sname[i] != "throwing" && sname[i] != "unarmed" && sname[i] != "whip"&& sname[i] != "checking" && sname[i] != "digging" 
&& sname[i] != "swimming")){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n",
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(PLAYER_SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
			}
				continue;
		}
                if(SKILL_D(sname[i])->type() != "knowledge" && (sname[i] != "array" && sname[i] != "axe" && sname[i] != "blade" && sname[i] != "claw"
&& sname[i] != "club" && sname[i] != "cuff" && sname[i] != "dagger" && sname[i] != "dodge" && sname[i] != "finger" && sname[i] != "force" && sname[i] != "fork"
&& sname[i] != "halberd" && sname[i] != "hammer" && sname[i] != "hand" && sname[i] != "hook" && sname[i] != "iron-cloth" && sname[i] != "leg" && sname[i] != "magic" 
&& sname[i] != "move" && sname[i] != "parry" && sname[i] != "pestle" && sname[i] != "spear" && sname[i] != "spells" && sname[i] != "staff" && sname[i] != "stick" 
&& sname[i] != "strike" && sname[i] != "sword" && sname[i] != "throwing" && sname[i] != "unarmed" && sname[i] != "whip"&& sname[i] != "checking" && sname[i] != "digging" 
&& sname[i] != "swimming")){
                printf("[32m│[37;0m%s%s%-40s" NOR " - %-10s %3d/%6d[32m│[37;0m\n",
                        (member_array(sname[i], mapped)==-1? "  ": "[1;32m□[37;0m"),
                        ((lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : ""),
                        (to_chinese(sname[i]) + " (" + sname[i] + ")"),
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]],sname[i]),
                        skl[sname[i]], (int)lrn[sname[i]]
                );
                }
        }
        if(j>0) { write("[32m└────────────────────────────────┘[37;0m\n");}

		show_special_skill(ob);
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
        grade = level / 10;
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
                        skl[sname[i]], (int)lrn[sname[i]],
                );
        }
        return desc +"\n";
}

void show_special_skill(object ob)
{
	if (!userp(ob)) return;
	
	printf("[32m┌[42m%21s    [40m[32m──────────────────────┐[37;0m\n", "[37m特别生活技能");
	printf("[32m│[37;0m   支配少阴  支配太阴  支配纯阴  支配少阳  支配太阳  支配纯阳   [32m│[37;0m\n");
	printf("[32m│[37;0m     (%2d)      (%2d)      (%2d)      (%2d)      (%2d)      (%2d)     [32m│[37;0m\n",
		SPECIAL_D->query_level(ob, "master-shaoyin"),
		SPECIAL_D->query_level(ob, "master-taiyin"),
		SPECIAL_D->query_level(ob, "master-chunyin"),
		SPECIAL_D->query_level(ob, "master-shaoyang"),
		SPECIAL_D->query_level(ob, "master-taiyang"),
		SPECIAL_D->query_level(ob, "master-chunyang"));
	printf("[32m│[37;0m                                                                [32m│[37;0m\n");
	printf("[32m│[37;0m   天地无用  身强力壮  聪敏好学  固本培元  身轻如燕  房中秘术   [32m│[37;0m\n");
	printf("[32m│[37;0m     (%2d)      (%2d)      (%2d)      (%2d)      (%2d)      (%2d)     [32m│[37;0m\n",
		SPECIAL_D->query_level(ob, "resist-yinyang"),
		SPECIAL_D->query_level(ob, "master-str"),
		SPECIAL_D->query_level(ob, "master-int"),
		SPECIAL_D->query_level(ob, "master-con"),
		SPECIAL_D->query_level(ob, "master-dex"),
		SPECIAL_D->query_level(ob, "loving-skill"));
	
	if (ob->query("nation")=="游牧民族")
	{
/*
        /   |        |                 |
       /    |        |                 |    
支配拳脚  内力深厚  裁缝技术           花容月貌  
  (00)     (00)     (00)              (00)  
*/
	printf("[32m│[37;0m            /   |         |                   |                 [32m│[37;0m\n");
	printf("[32m│[37;0m           /    |         |                   |                 [32m│[37;0m\n");
	printf("[32m│[37;0m   支配拳脚  内力深厚  裁缝技术            花容月貌             [32m│[37;0m\n");
	printf("[32m│[37;0m     (%2d)      (%2d)      (%2d)                (%2d)               [32m│[37;0m\n",
		SPECIAL_D->query_level(ob, "master-unarmed"),
		SPECIAL_D->query_level(ob, "master-neili"),
		SPECIAL_D->query_level(ob, "master-clothing"),
		SPECIAL_D->query_level(ob, "beauty-culture"));
	}
	else if (ob->query("nation")=="天竺部族")
	{
	/*
            |        |        |        |
            |        |        |        |    
         支配棍杖  百草药理  点石成金  花容月貌
          (00)     (00)     (00)      (00)  */
	printf("[32m│[37;0m                |         |         |         |                 [32m│[37;0m\n");
	printf("[32m│[37;0m                |         |         |         |                 [32m│[37;0m\n");
	printf("[32m│[37;0m             支配棍杖  百草药理  点石成金  花容月貌             [32m│[37;0m\n");
	printf("[32m│[37;0m               (%2d)      (%2d)      (%2d)      (%2d)               [32m│[37;0m\n",
		SPECIAL_D->query_level(ob, "master-staff"),
		SPECIAL_D->query_level(ob, "chinese-medicine"),
		SPECIAL_D->query_level(ob, "master-combine"),
		SPECIAL_D->query_level(ob, "beauty-culture"));
	}
	else if (ob->query("nation")=="苗家部族")
	{
	/*
           /  \                        |
          /    \                       |
     支配长枪  支配软鞭               花容月貌  传音搜魂*/
	printf("[32m│[37;0m               /  \\                           |                 [32m│[37;0m\n");
	printf("[32m│[37;0m              /    \\                          |                 [32m│[37;0m\n");
	printf("[32m│[37;0m        支配长枪  支配软鞭                 花容月貌  传音搜魂   [32m│[37;0m\n");
	printf("[32m│[37;0m          (%2d)      (%2d)                     (%2d)      (%2d)     [32m│[37;0m\n",
		SPECIAL_D->query_level(ob, "master-spear"),
		SPECIAL_D->query_level(ob, "master-whip"),
		SPECIAL_D->query_level(ob, "beauty-culture"),
		SPECIAL_D->query_level(ob, "mind-searching"));
	}
	else if (ob->query("nation")=="东瀛浪人")
	{
	/*
        /   |    \                     |
       /    |     \                    |
冶炼技术  支配刀刃  锻造技术           花容月貌*/
	printf("[32m│[37;0m            /   |    \\                        |                 [32m│[37;0m\n");
	printf("[32m│[37;0m           /    |     \\                       |                 [32m│[37;0m\n");
	printf("[32m│[37;0m   冶炼技术  支配刀刃  锻造技术            花容月貌             [32m│[37;0m\n");
	printf("[32m│[37;0m     (%2d)      (%2d)      (%2d)                (%2d)               [32m│[37;0m\n",
		SPECIAL_D->query_level(ob, "master-forge"),
		SPECIAL_D->query_level(ob, "master-blade"),
		SPECIAL_D->query_level(ob, "master-enchase"),
		SPECIAL_D->query_level(ob, "beauty-culture"));
	}
	else if (ob->query("nation")=="中原人士")
	{
	/*
        /   |        |                 |
       /    |        |                 |
强身健体，支配长剑，五行数术           花容月貌*/
	printf("[32m│[37;0m            /   |         |                   |                 [32m│[37;0m\n");
	printf("[32m│[37;0m           /    |         |                   |                 [32m│[37;0m\n");
	printf("[32m│[37;0m   强身健体  支配长剑  五行数术            花容月貌             [32m│[37;0m\n");
	printf("[32m│[37;0m     (%2d)      (%2d)      (%2d)                (%2d)               [32m│[37;0m\n",
		SPECIAL_D->query_level(ob, "master-hp"),
		SPECIAL_D->query_level(ob, "master-sword"),
		SPECIAL_D->query_level(ob, "wuxing-divination"),
		SPECIAL_D->query_level(ob, "beauty-culture"));
	}
	else
	{
	}

	write("[32m└────────────────────────────────┘[37;0m\n");
}

int help(object me)
{
        write(@HELP
指令格式 : skills|cha [<某人>]

这个指令可以让你(你)查询所学过的技能。

你也可以指定一个和你有师徒关系的对象或你的配偶，用 skills 可以查知对方的
技能状况。

巫师可以查询任何人或 NPC 的技能状况。

HELP
    );
    return 1;
}
