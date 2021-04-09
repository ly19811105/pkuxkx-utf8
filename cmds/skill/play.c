// play.c
inherit F_SSERVER;
#include <combat/music.h>

int main(object me, string arg)
{
  object target, weapon;
  string music, oppid, instrument;
  
  if( me->is_busy() ) return notify_fail("( 你上一个动作还没有完成，不能运用内功弹奏乐器。)\n");
  if( me->query_temp("no_exert")>0 ) return notify_fail("( 你现在处于闭气状态，无法运用内功。)\n");
  if( environment(me)->query("no_exert") ||
  	  environment(me)->query("no_perform") ) return notify_fail("这里无法运转内功。\n");
  if( !arg ) return notify_fail("指令格式：play <曲目> [<施用对象>]\n");

  if( !stringp(me->query_skill_mapped("force")) ) 
      return notify_fail("你请先用 enable 指令选择你要使用的内功。\n");

  if( sscanf(arg, "%s %s", music, oppid)==2 )
  {
      target = present(oppid, environment(me));
      if( !target ) return notify_fail("这里没有 " + oppid + "。\n");
  }
  else music = arg;
  
  weapon=me->query_temp("weapon");
  if ( !objectp(weapon) )
  	return notify_fail("你先拿着乐器才能开始弹奏曲子。\n");
  
  if ( !stringp(instrument=weapon->query("music")) )
  	return notify_fail("你先拿着乐器才能开始弹奏曲子。\n");
  
  if ( !subskill_info[music] || subskill_info[music]["class"]!=3 )
  	return notify_fail("你输入的曲谱并不存在。\n");
  
  if ( me->query_sub_skill("music::"+instrument+"::"+music)<=100 )
  	return notify_fail("你对"+ SKILL_D("music")->skill_name(music)+"的掌握并不足以弹奏该曲子。\n");
  
  if ( file_size( MUSIC_D(music)+".c" )<=0 )
  	return notify_fail("该乐谱并没有提供弹奏特效。\n");

  if(target && !target->is_character() )
      return notify_fail(target->name()+"并不是生物，你不能对他弹奏曲子。\n");

  if(target && target->query("uni_target") && target->query("uni_target") != me)
      return notify_fail(target->name()+"没有与你理会。\n");

//输入谁对什么人用什么乐器弹奏什么曲目。  
  return MUSIC_D(music)->play_music(me, target, instrument, music);
}

int help (object me)
{
    write(@HELP
指令格式：play <曲目> [<施用对象>]
用内力弹奏一个曲目，主手必须装备乐器，乐器可以从长安购买
或者通过其他渠道解谜获得。大多数曲谱都对施用对象没有任何
要求，作用对象都是本地房间除本人或者本队伍以外的所有人，
具体效果不同曲目效果差别很大。
HELP
    );
    return 1;
}
