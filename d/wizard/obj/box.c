// 储存箱 by whuan，用来存放装备
//copy from zjuxlqy

#define MAX_SIZE_BOX 10
#include <ansi.h>

inherit ITEM;

string check_blank_slot(object me);
void create()
{
        set_name(HIW"储存箱"NOR, ({ "deposit box","box"}));
        set_weight(9999999);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("material", "wood");
                set("value", 99);
                set("no_get", 1);
        }
        setup();
}

void init()
{
        add_action("do_pick", "pick");
        add_action("do_put",  "putin");
  
}
string short()
{
	 return HIW + this_player()->name(1) + HIW "的储存箱" NOR "(Deposit Box)"; 
}
string long()
{
	object  me;
        mapping diablo,obj,numbers;
       
        string  msg,*slot;
        int     i;
        me = this_player();
	
        
	if(!mapp(diablo=me->query("diablo_box_slot")))
		  return ("你的储存箱里没有任何东西！请用"+HIY"putin <物品id> "NOR+"将物品放入其中！\n");
	if(!mapp(numbers=me->query("diablo_box_num")))
		  return ("你的储存箱里没有任何东西！请用"+HIY"putin <物品id> "NOR+"将物品放入其中！\n");
	if(sizeof(diablo)!=sizeof(numbers))
	  return (HIR "\n你的储存箱坏了，请和巫师联系。\n" NOR);
       
       if(!sizeof(diablo)) 
	  return ("你的储存箱里没有任何东西！请用"+HIY"putin <物品id> "NOR+"将物品放入其中！\n");
       slot = keys(diablo);

        msg = "\n里面有：\n"
              HIW "───────────────────────────\n" NOR;

        for(i = 0; i < sizeof(slot); i++) {
             	 obj = diablo[slot[i]];
                msg = sprintf("%s" HIG "%3d、" NOR "%10s%-2s   %-15s:%-3d\n",
                                msg,
                                i+1,
                                " ",
                                obj["name"],
                                " ",numbers[slot[i]]);
        }
        msg += HIW "───────────────────────────\n"NOR;
        msg+="用"+HIY"putin <物品id> "NOR+"将物品放入其中，用"+HIC"pick <序号>"NOR+"取出其中的某一物品。\n\n"  ;     
        return msg;

}


int do_pick(string arg)
{
        object  me,ob;
        int   i,  index,amount;
        string files;
        mapping num,diablo_ob,dbase;
        string *list,*prop;

        me = this_player();
	
        if( !arg ) return notify_fail("你要取回哪样物品？\n");
        
        i=atoi(arg);
        if(!i) return notify_fail("你要取回哪样物品？\n");
	if(!mapp(diablo_ob=me->query("diablo_box_slot")))
		return notify_fail("你的储存箱里没有任何东西！\n");
       if(!mapp(num=me->query("diablo_box_num")))
		return notify_fail("你的储存箱里没有任何东西！\n");
	if(sizeof(diablo_ob)!=sizeof(num))
	  return notify_fail(HIR "\n你的储存箱坏了，请和巫师联系。\n" NOR);
	
	list=keys(diablo_ob);

	if(sizeof(num)<i)
		return notify_fail("你的储存箱里没有这个东西！\n");
	dbase=diablo_ob[list[i-1]];
	files=dbase["files"];
	prop=keys(dbase);
	amount=(int)num[list[i-1]];
	if(!ob=new(files))
	{
	      destruct(ob);
              return notify_fail("取得物品失败。\n");
        }
	if(amount==0)
		{
		    return notify_fail("取得物品失败。\n");
		}
	else{
		ob=new(files);
		for(int z=0;z<sizeof(prop);z++)
			ob->set(prop[z],dbase[prop[z]]);
		if(!ob->query_amount())
		  {
		  	if(!ob->move(me))
		  	ob->move(environment(me));
		  if(amount>10) amount=10; //防止bug
		 for(int k=0;k<amount-1;k++)
			{
			ob=new(files);
			for(int w=0;w<sizeof(prop);w++)
				ob->set(prop[w],dbase[prop[w]]);
			ob->move(me);
			}
		}
		else {
			ob->set_amount(amount);
			if(!ob->move(me))
		  	ob->move(environment(me));
		}
	
	}
	
    
                message_vision("$N从储存箱里取出了" + ob->name() + "。\n", me);
                me->delete("diablo_box_num/"+list[i-1]);
                me->delete("diablo_box_slot/"+list[i-1]);
                return 1;
    
}

int do_put(string arg)
{
        object  me, ob;
        int   amount;
	      string files,slot,what;
	      mapping num,ob_dbase;
	      string *list;
        me = this_player();
 	      if( !arg ) return notify_fail("你要把什么东西放进储存箱？\n");
 	      if( !objectp(ob = present(arg, me) ) )
         {
         	sscanf(arg,"%s in box",what);
         	
	 	if(what)
		 {
		 	if(!objectp(ob = present(what, me) ) )
		         {		         	
		         	tell_object(me,"你要把什么东西放进储存箱？\n");
				 return 1;
			}
		      
		}
		else  
	      {
	         	tell_object(me,"你要把什么东西放进储存箱？\n");
			 return 1;
			 }
       }
    if( !ob->is_gems())
    	{
        tell_object(me,"这种宝箱不能存放普通物品。\n");			 
	      return 1;
	      }
       if(ob->query("no_put")&&!ob->query("can_putin_box"))
        {
                tell_object(me,"这样东西不能放进储存箱。\n");
                return 1;
        }
       if(ob->query("no_store"))
        {
                tell_object(me,"这样东西不能放进储存箱。\n");
                return 1;
        }    
   
       if(ob->query_unique())
       {
       		tell_object(me,"这样东西不能放进储存箱。\n");
                return 1;
        }
       
       if(ob->is_character())
        {
         		tell_object(me,"活物可不能放进去^_^\n");
         	return 1;
        }
        
       if( ob->query("money_id") )       
       {
         		tell_object(me,"钱放在这里可不保险，还是存银行吧。\n");
         	  return 1;
        }
       if( (int)ob->query("skill_type") && (int)ob->query("rigidity")<50)
       	{
       		tell_object(me,"兵器太破了，放在这里有可能会烂掉。\n");
         	  return 1;
       		}         
       if(ob->query("task_owner"))
         {
       		tell_object(me,"task物件不能存放。\n");
         	  return 1;
       		}   
        if( first_inventory(ob))
         {
       		tell_object(me,"还是先把"+ob->name()+"里面的东西取出来再往柜子里放吧。\n");
         	  return 1;
       		}      
       if(mapp(num=me->query("diablo_box_num")))
        {
        	list=keys(num);
        if(sizeof(list)>MAX_SIZE_BOX -1)
        	{tell_object(me,"储存箱里放了太多东西啦！\n");
        	 return 1;
        	}
        }
         slot = check_blank_slot(me);
        if(slot == "none")
        {
       		 tell_object(me,"你的储存箱可能有点问题，请联系巫师。\n");
        	 return 1;	
        }
        ob->delete("skill_type");
        ob_dbase=ob->query_entire_dbase();
        files=base_name(ob)+".c";
        ob_dbase+=(["files":files]);
        
        me->set("diablo_box_slot/"+slot,ob_dbase);
        amount=ob->query_amount();
        if(amount)
    	{
    	
	me->add("diablo_box_num/"+slot,amount);
	}
	else me->set("diablo_box_num/"+slot,1);
	message_vision("$N将"+ob->query("name")+"放入到储存箱中。\n",me);
        destruct(ob);
        return 1;
}

string check_blank_slot(object me)
{
	
	if(!me->query("diablo_box_slot/A"))	
		return "A";
	else if(!me->query("diablo_box_slot/B"))	
		return "B";
	else if(!me->query("diablo_box_slot/C"))	
		return "C";
	else if(!me->query("diablo_box_slot/D"))	
		return "D";
	else if(!me->query("diablo_box_slot/E"))	
		return "E";
	else if(!me->query("diablo_box_slot/F"))	
		return "F";
	else if(!me->query("diablo_box_slot/G"))	
		return "G";
	else if(!me->query("diablo_box_slot/H"))	
		return "H";
	else if(!me->query("diablo_box_slot/I"))	
		return "I";
	else if(!me->query("diablo_box_slot/J"))	
		return "J";
	else return "none";
	
	
	
	
}

