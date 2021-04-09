//	skill.c
//
// 	This is the standard skill daemon object. All objects defining a skill
//	should inherit this as its skeleton.

inherit F_SSERVER;


void create()
{
	seteuid(getuid());
}

//
// valid_learn()
//
// This function is to check if a character should be able to 
// learn/study/practice the skill. The default function just
// returns 1 to allow any characters improve the skill. However,
// a good skill should has its own feature and restriction. Redefine
// this function in your skill object and make it reasonable 
// according to the power of the skill.

int valid_learn(object me) { return 1; }

int valid_effect(object me, object weapon, string action_name, int skill) 
{ 
	return 1;
}

// 
// type()
//
// This function should return the type of the skill. The skill type now
// affects if the skill requires combat exp in order to be learned (see
// /cmds/std/learn.c ) and the ranking of a skill level (see 
// /cmds/usr/skills.c )。
// Currently we have only 2 types of skill: "martial" and "knowledge".

string type() { return "martial"; }

//
// skill_improved()
//
// This function is called when a character's skill has gained a new level.
// You can make some modify to a character according to the skill.

void skill_improved(object me) {}

//
// exert_function()
//
//     This function is used by the "exert" command as specific skill's 
// command parser. This function parses the arguments in the standard form
// (that is, exert <function> [<target>]). When <target> is not present,
// use the character himself as default.
//     In order to use this default exert command parser, you must define
// a function called exert_function_file(string func) in the skill object
// that takes the function name as argument and return the file name that
// defines the specified function. 

int exert_function(object me, string arg)
{
	string func, target, file;
	object target_ob;

	if( sscanf(arg, "%s %s", func, target)==2 ) {
		target_ob = present(target, environment(me));
		if( !target_ob ) return notify_fail("这里没有 " + target + "。\n");
	} else {
		func = arg;
		target_ob = me;
	}

            if (target_ob != me)
         if (target_ob->query("uni_target"))
            if (target_ob->query("uni_target") != me)
            {
                write("对方不愿和你较量。\n");
                return 0;}

	if( !stringp(file = (string)this_object()->exert_function_file(func))
	||	file_size(file + ".c") <= 0 ) {
		if(wizardp(me)) write("no such exert\n");
		return 0;}
	return (int)call_other( file, "exert", me, target_ob);
}

int perform_action(object me, string arg)
{
	string action, target, file;
	object target_ob;

    if( me->query_temp("blind"))
		return notify_fail("你什么也看不清，无法施展特殊功夫!\n");
	if( sscanf(arg, "%s %s", action, target)==2 ) 
    {
        if( me->query("id")==target ) return notify_fail("你要自杀吗？\n");
		target_ob = present(target, environment(me));
	}
    else
    {
		action = arg;
        target_ob = offensive_target(me);
	}
    if( !target_ob || !target_ob->is_character()) 
        return notify_fail("这里没有你要攻击的对象。\n");
	
    if (target_ob->query("uni_target"))
        if (target_ob->query("uni_target") != me)
            return notify_fail("对方不想与你较量。\n");

	if( !stringp(file = (string)this_object()->perform_action_file(action))
	||	file_size(file + ".c") <= 0 )
        return notify_fail("没有这个武功招式。\n");

	return (int)call_other( file, "perform", me, target_ob);
}
// The following two functions are used to modify the random function
// for shaolin wugong.

int sum(int n,int base,int d)
{
  return (n*(2*base+(n-1)*d)/2);
}

int NewRandom(int n,int base,int d)
{ 
  int i = 1;
  int randnum = random(sum(n,base,d));

  if (sum(6,base,d) < randnum)
   {
    i = 7;
    while (sum(i,base,d) < randnum)
          i++;
    }
  else {
    while (sum(i,base,d) < randnum)
        i++;
   } 
  return (i-1);
}

// Dewolf 20051125 for YINYANG_D
string query_yinyang()
{
	return "没有";
}
