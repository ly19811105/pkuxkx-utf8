#include <ansi.h>

#define MAKE_SET(key,value)     write_file(file,"\tset(\""+(key)+"\"," +(intp(value) ? sprintf("%d",(value)) : ("\""+value+"\""))+");\n");
#define MAKE_SKILL(key,value)   write_file(file,"\tset_skill(\""+(key)+"\"," +sprintf("%d",(value))+");\n");
#define MAKE_SKILL_MAP(from,to) write_file(file,"\tmap_skill("+"\""+from+"\","+"\""+to+"\");\n" );
#define MAKE_HEAD               write_file(file,"\#include <ansi.h>\ninherit NPC;\nvoid create()\n{\n\tset_name(\""+ob->query("name")+"\",({\""+arg+" npc"+"\"}));\n");
#define MAKE_TAIL               write_file(file,"\tsetup();\n\}\n");

inherit F_CLEAN_UP;

string* attributes=({"long","title","age","str","con","int","spi","per",
        "job_title","nickname","combat_exp","max_qi","max_jing","gender",
        "max_neili","max_jingli","jiali","race","class","repute","score",
        "family/family_name",});
int help();
int main(object me, string arg)
{
	string file,*skill_names,to;
	object ob;
	mapping skills;
	if (! arg)
		return help();

	if (! wizardp(me))
		return notify_fail("只有巫师才可以复制。\n");

/*
	if (! ob = find_player(arg) )
		return help();
*/
        if (wizardp(me)) 
           {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob|| !me->visible(ob)) return notify_fail("你要察看谁的状态？\n");
           }
        else return help();

	file = "/d/wizard/laxiang/"+arg+"_npc.c";
	if( file_size(file) > 0 )
		return notify_fail("已经存在文件"+file+"\n");

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
	tell_object(me,HIW "\n成功制造NPC成功，文件为:"+file+"\n" HIW );
	return 1;
}


int help()
{
write( @TEXT
指令格式：make_npc <id>

这个指令让你制作一个和玩家一样的npc。
TEXT
);
return 1 ;
}




