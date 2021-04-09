// 宝石库

inherit ROOM;
#include <ansi.h>
string replace_color(string arg);
void create()
{
        set ("short",  HIW "新宝石库" NOR );
        set ("long", @LONG

这里是新的宝石库，每个人都有一个自己的宝石箱(box)。

LONG);  
        set("exits", 
        ([
                "south" : __DIR__"mingren",
//                "north" : __DIR__"gemroom",	
        ]));
        set("room_location", "/d/city/");
	set("no_fight",1);
	set("no_magic",1);
	set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_pick", "pick");
        add_action("do_put",  "put");     
        add_action("do_look","look");
        
}

int do_look(string arg)
{
	object  me;
  mapping gembox,num,obj;
  string  msg,name,*slot;
  int     i,amount;
  me = this_player();
	if(!arg)
		return 0;
	if(arg!="box")
		return 0;
	
        
	if(!mapp(gembox=me->query("gembox_slot")))
		  {
		  	tell_object(me,"你的宝石箱里空空荡荡，用"+HIY"put <宝石id> "NOR+"将宝石放入其中！\n");
		  	return 1;
		}
	if(!mapp(num=me->query("gembox_number")))
		  {
		  	tell_object(me,"你的宝石箱里空空荡荡，用"+HIY"put <宝石id> "NOR+"将宝石放入其中！\n");
		  	return 1;
		}
	if(sizeof(gembox)!=sizeof(num))
	{
		 tell_object(me,HIR "\n你的宝石箱遭劫了，请和巫师联系。\n" NOR);
		return 1;
	}
        
  if(!sizeof(gembox)) 
	 {
		  	tell_object(me,"你的宝石箱里空空荡荡，用"+HIY"put <物品id> "NOR+"将宝石放入其中！\n");
		  	return 1;
	}
        slot = keys(gembox);    
	
        msg = CYN"\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n" NOR;

        for(i = 0; i < sizeof(slot); i++) {
        	
        	amount = num[slot[i]];
                obj = gembox[slot[i]];
                msg = sprintf("%s" HIG "%3d、" NOR "%15s  %s                    " HIW "%d\n"NOR,
                                msg,
                                i+1,
                                " ",
                                slot[i],amount);
        }
        msg += CYN"\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n"NOR;
        msg+="\n用"+HIY"put <物品id>"NOR+"将宝石放入其中，用"+HIC"pick <序号>"NOR+"取出其中的某一宝石。\n"NOR;     
       
      	me->start_more(msg);
      	return 1;


}

int do_pick(string arg)
{
  object  me,ob,*inv;
  int   i,  index,amount;
  string files,slot,gem_type,yinyang;
  mapping diablo_ob,dbase,num;
  string *list,*prop,*gem, *gem2, *gem3;
  int gem_level;
  me = this_player();
	
  if( !arg ) return notify_fail("你要取回哪样物品？\n");
  i=atoi(arg);
  if(!i) return notify_fail("你要取回哪样物品？\n");
	if(!mapp(diablo_ob=me->query("gembox_number")))
		return notify_fail("你的宝石箱里空空荡荡！\n");
		
  if(sizeof(all_inventory(me))>200)
           return notify_fail("笨阿，身上东西满了，小心无欢打劫你的宝石！\n");
  if(!mapp(num = me->query("gembox_number")))
		return notify_fail("你的宝石箱里空空荡荡！\n");
	
	if(sizeof(diablo_ob)!=sizeof(num))
	  return notify_fail(HIR "\n你的宝石箱遭劫了，请和巫师联系。\n" NOR);
	
	list=keys(diablo_ob);
	
	if(i < 1)
		return notify_fail("你的宝石箱里没有这件宝石！\n");
	if(sizeof(num) < i)
		return notify_fail("你的宝石箱里没有这件宝石！\n");
	slot = list[i-1];
//	files=diablo_ob[list[i-1]];
  
  gem=explode(slot,"☆");
  gem2=explode(slot,"★");
  gem3=explode(slot,"◎");
  if (sizeof(gem)!=2 && sizeof(gem2) !=2 && sizeof(gem3) != 2)
  	return notify_fail("好像出错了，通知虫子吧。\n");
  if (sizeof(gem)==2)
 {
 	yinyang = "yin";
  switch (replace_color(gem[1]))
  {
	  case "精金"   :gem_type="jin"	;break; 
	  case "玄冰"   :gem_type="bing";break;  
	  case "日魂"   :gem_type="ri"	;break; 
	  case "月魄"   :gem_type="yue"	  ;break;
	  case "神龙骨" :gem_type="gu"	  ;break;
	  case "凤凰羽" :gem_type="yu"	  ;break;
	  case "麒麟角" :gem_type="jiao"	  ;break;
	  case "玄武甲" :gem_type="jia"	  ;break;
	  default:       gem_type="bing"    ;break;   
  }
  switch (replace_color(gem[0]))
  {
  	case "地"  :gem_level=1; break;
    case "山"  :gem_level=2; break;
    case "水"  :gem_level=3; break;
    case "风"  :gem_level=4; break;
    case "雷"  :gem_level=5; break;
    case "火"  :gem_level=6; break;
    case "泽"  :gem_level=7; break;
    case "天"  :gem_level=8; break;
    default:      gem_level=1; break;
  }
}

else if (sizeof(gem2)==2)
 {
 	yinyang = "yang";
  switch (replace_color(gem2[1]))
  {
	  case "炎晶"   :gem_type="yan"	;break; 
	  case "木灵"   :gem_type="mu";break;  
	  case "日魂"   :gem_type="ri"	;break; 
	  case "月魄"   :gem_type="yue"	  ;break;
	  case "神龙骨" :gem_type="gu"	  ;break;
	  case "凤凰羽" :gem_type="yu"	  ;break;
	  case "麒麟角" :gem_type="jiao"	  ;break;
	  case "玄武甲" :gem_type="jia"	  ;break;
	  default:       gem_type="bing"    ;break;   
  }
  switch (replace_color(gem2[0]))
  {
  	case "地"  :gem_level=1; break;
    case "山"  :gem_level=2; break;
    case "水"  :gem_level=3; break;
    case "风"  :gem_level=4; break;
    case "雷"  :gem_level=5; break;
    case "火"  :gem_level=6; break;
    case "泽"  :gem_level=7; break;
    case "天"  :gem_level=8; break;
    default:    gem_level=1; break;
  }
}	

else
 {
 	yinyang = "zhong";
  switch (replace_color(gem3[1]))
  {
	  case "玉髓"   :gem_type="sui"	;break; 
	  case "神龙骨" :gem_type="gu"	  ;break;
	  case "凤凰羽" :gem_type="yu"	  ;break;
	  case "麒麟角" :gem_type="jiao"	  ;break;
	  case "玄武甲" :gem_type="jia"	  ;break;
	  default:       gem_type="bing"    ;break;   
  }
  switch (replace_color(gem3[0]))
  {
  	case "地"  :gem_level=1; break;
    case "山"  :gem_level=2; break;
    case "水"  :gem_level=3; break;
    case "风"  :gem_level=4; break;
    case "雷"  :gem_level=5; break;
    case "火"  :gem_level=6; break;
    case "泽"  :gem_level=7; break;
    case "天"  :gem_level=8; break;
    default:    gem_level=1; break;
  }
}	
	
//  tell_object(me,replace_color(gem[0])+replace_color(gem[1]+"\n"));
//  tell_object(me,gem_type+gem_level+"\n");  
  ob=F_GEMS->new_gem(gem_type,gem_level,yinyang);
		
	if(!ob)
    return notify_fail("取得宝石失败，请联系巫师。\n");
	if(!ob->move(me))
			ob->move(environment(me));
	
   message_vision("$N从宝石箱里面取出一颗"+ ob->name() +"。\n", me);
   me->add("gembox_number/"+slot,-1);
   me->add("baoshi_number",-1);
   if(me->query("baoshi_number")<=0) 
   	me->delete("baoshi_number");
   if(!me->query("gembox_number/"+slot))
   {	
   	 me->delete("gembox_number/"+slot);
     me->delete("gembox_slot/"+slot);
   }
   return 1;     
}

int newbie_task_finish(object me)
{
    int result=0;
    if (me->query("xxnewbiequest3")
        ||me->query("mingjiaonewbiejobdone")
        ||me->query("emeinewbiejobdone")
        ||me->query("huashannewbiejobdone")
        ||me->query("gaibangnewbiejobdone")
        ||me->query("gaibangnewbiejobdone_2")
        ||me->query("exp/gmnewbiejob")>50000
        ||me->query("exp/taohuanewbie")>50000
        ||me->query("tlnewbiejobdone")
        ||me->query("exp/qznewbiejob")>50000
        ||me->query("rynewbiejobdone"))//新手任务完成，暂缺少林武当
    {
        result=1;
    }
    return result;
}

int do_put(string arg)
{
  object  me, ob;
  int amount;
	string files,slot;
	mapping num,ob_dbase;
	string *list;
  me = this_player();
	if( !arg ) return notify_fail("你要把什么东西放进宝石箱？\n");
  if( !objectp(ob = present(arg, me) ) )
  {
  	 tell_object(me,"你要把什么东西放进宝石箱？\n");
		 return 1;
	}
  if(!ob->is_gem())
  {
     tell_object(me,"这样东西不能放进宝石箱。\n");
     return 1;
  }
  if(ob->query("newgem") != 1)
  {
     tell_object(me,"这是哪个年代的化石啊？\n");
     return 1;
  }
  if (me->query("baoshi_number") >= me->query("level")*4)
  {
  	tell_object(me,"以你目前的级别，你放不了更多宝石。\n");
  	return 1;
  }
  if (me->query("level")<10)
  {
      if (me->query("combat_exp")>400000&&(newbie_task_finish(me)||me->query("statistics/fullme/total_fullme_times")>50))
      {
            files=base_name(ob)+".c";
            slot = ob->query("name"); 
            me->set("gembox_slot/"+slot,files);
            me->add("gembox_number/"+slot,1);
            me->add("baoshi_number",1);
            message_vision("$N将手中"+ob->query("name")+"放进了宝石箱。\n",me);
            ob->move("/obj/void");
            destruct(ob);
            return 1;
      }
  	tell_object(me,"在这里存放宝石，至少需要10级。\n");
  	return 1;
  }

        files=base_name(ob)+".c";
        slot = ob->query("name"); 
        me->set("gembox_slot/"+slot,files);
        me->add("gembox_number/"+slot,1);
        me->add("baoshi_number",1);
	message_vision("$N将手中"+ob->query("name")+"放进了宝石箱。\n",me);
	ob->move("/obj/void");
  destruct(ob);
  return 1;
}

#define OLD_BLK ESC+"[0;30m"          /* Black    */
#define OLD_RED ESC+"[0;31m"          /* Red      */
#define OLD_GRN ESC+"[0;32m"          /* Green    */
#define OLD_YEL ESC+"[0;33m"          /* Yellow   */
#define OLD_BLU ESC+"[0;34m"          /* Blue     */
#define OLD_MAG ESC+"[0;35m"          /* Magenta  */
#define OLD_CYN ESC+"[0;36m"          /* Cyan     */
#define OLD_WHT ESC+"[0;37m"          /* White    */



string replace_color(string arg)
{
	string str;
	str = arg;
	str = replace_string(str,BLK,"");
	str = replace_string(str,RED,"");
	str = replace_string(str,GRN,"");
	str = replace_string(str,YEL,"");
	str = replace_string(str,BLU,"");
	str = replace_string(str,MAG,"");
	str = replace_string(str,CYN,"");
	str = replace_string(str,WHT,"");
	
	str = replace_string(str,HIR,"");
	str = replace_string(str,HIG,"");
	str = replace_string(str,HIY,"");
	str = replace_string(str,HIB,"");
	str = replace_string(str,HIM,"");
	str = replace_string(str,HIC,"");
	str = replace_string(str,HIW,"");
	str = replace_string(str,NOR,"");
	str = replace_string(str,BNK,"");   
	str = replace_string(str,REV,"");
	str = replace_string(str,U,"");
	
	str = replace_string(str,OLD_WHT,"");
	str = replace_string(str,OLD_RED,"");
	str = replace_string(str,OLD_GRN,"");
	str = replace_string(str,OLD_YEL,"");
	str = replace_string(str,OLD_BLU,"");
	str = replace_string(str,OLD_MAG,"");
	str = replace_string(str,OLD_CYN,"");
		
	return str;
}
