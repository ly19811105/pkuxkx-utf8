// 宝石

inherit ROOM;
#include <ansi.h>

void create()
{
        set ("short",  HIW "炼丹房" NOR );
         set ("long", @LONG

这里是方士们练丹的地方，房间里烟雾(fog)缭绕，处处透出一股神秘的味道。

LONG);  
        set("exits", 
        ([ //sizeof() == 1
                "south" : __DIR__"droproom",
        ]));
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
        mapping diablo,num,obj;
        string  msg,name,*slot;
        int     i,amount;
        me = this_player();
	if(!arg)
		return 0;
	if(arg!="fog")
		return 0;
	
        
	if(!mapp(diablo=me->query("diablo_baoshi_slot")))
		  {
		  	tell_object(me,"你的宝石库里空空荡荡，用"+HIY"put <宝石id> "NOR+"将宝石放入其中！\n");
		  	return 1;
		}
	if(!mapp(num=me->query("diablo_baoshi_number")))
		  {
		  	tell_object(me,"你的宝石库里空空荡荡，用"+HIY"put <宝石id> "NOR+"将宝石放入其中！\n");
		  	return 1;
		}
	if(sizeof(diablo)!=sizeof(num))
	{
		 tell_object(me,HIR "\n你的宝石库遭劫了，请和巫师联系。\n" NOR);
		return 1;
	}
        
       if(!sizeof(diablo)) 
	 {
		  	tell_object(me,"你的宝石库里空空荡荡，用"+HIY"put <物品id> "NOR+"将宝石放入其中！\n");
		  	return 1;
	}
        slot = keys(diablo);    
	
        msg = CYN"\n★★★★★★★★★★"HIW"大"MAG"·"HIM"唐"MAG"·"HIC"皇"MAG"·"HIR"家"MAG"·"HIB"炼"MAG"·"HIG"丹"MAG"·"HIY"房"NOR+CYN"★★★★★★★★★★★\n\n" NOR;

        for(i = 0; i < sizeof(slot); i++) {
        	
        	amount = num[slot[i]];
                obj = diablo[slot[i]];
                msg = sprintf("%s" HIG "%3d、" NOR "%15s  %s                    " HIW "%d\n"NOR,
                                msg,
                                i+1,
                                " ",
                                slot[i],amount);
        }
        msg += CYN"\n★★★★★★★★★★★★"HIY"X"HIR"·"HIY"L"HIR"·"HIY"Q"HIR"·"HIY"Y"NOR+CYN"★★★★★★★★★★★★★★★★★★★\n"NOR;
        msg+="\n用"+HIY"put <物品id>"NOR+"将宝石放入其中，用"+HIC"pick <序号>"NOR+"取出其中的某一宝石。\n"NOR;     
       
      	me->start_more(msg);
      	return 1;


}

int do_pick(string arg)
{
          object  me,ob,*inv;
        int   i,  index,amount;
        string files,slot;
        mapping diablo_ob,dbase,num;
        string *list,*prop;

        me = this_player();
	
        if( !arg ) return notify_fail("你要取回哪样物品？\n");
        
        i=atoi(arg);
        if(!i) return notify_fail("你要取回哪样物品？\n");
	if(!mapp(diablo_ob=me->query("diablo_baoshi_slot")))
		return notify_fail("你的宝石库里空空荡荡！\n");
		
       if(sizeof(all_inventory(me))>48)
                return notify_fail("笨阿，身上东西满了，小心一天劫你的宝石！\n");
       if(!mapp(num = me->query("diablo_baoshi_number")))
		return notify_fail("你的宝石库里空空荡荡！\n");
	
	if(sizeof(diablo_ob)!=sizeof(num))
	  return notify_fail(HIR "\n你的宝石库遭劫了，请和巫师联系。\n" NOR);
	
	list=keys(diablo_ob);
	
	if(i < 1)
		return notify_fail("你的宝石库里没有这件宝石！\n");
	if(sizeof(num) < i)
		return notify_fail("你的宝石库里没有这件宝石！\n");
	slot = list[i-1];
	files=diablo_ob[list[i-1]];
		
	if(!ob=new(files))
	{
	      destruct(ob);
              return notify_fail("取得宝石失败，请联系巫师。\n");
        }
	
	else{
		ob=new(files);
		
		if(!ob->move(me))
			ob->move(environment(me));
		
	
	}
	
                message_vision("朦朦烟雾中突然霞光一闪，一颗"+ ob->name() +"落入$N手中。\n", me);
                me->add("diablo_baoshi_number/"+slot,-1);
                if(!me->query("diablo_baoshi_number/"+slot))
                 {	me->delete("diablo_baoshi_number/"+slot);
                 	me->delete("diablo_baoshi_slot/"+slot);
                 
                }
                return 1;
     
}

int do_put(string arg)
{
         object  me, ob;
        int   amount;
	string files,slot;
	mapping num,ob_dbase;
	string *list;
        me = this_player();
	if( !arg ) return notify_fail("你要把什么东西放进宝石库？\n");
        if( !objectp(ob = present(arg, me) ) )
                {tell_object(me,"你要把什么东西放进宝石库？\n");
		 return 1;
		}
       if(!ob->query("is_baoshi"))
        {
                tell_object(me,"这样东西不能放进宝石库。\n");
                return 1;
        }
       if(ob->query("can't_putin_fog"))
        {
                tell_object(me,"给的礼物就别放了吧，唉...\n");
                return 1;
        }
        if(ob->is_character())
       	{
         		tell_object(me,"活物可不能放进去^_^\n");
         	return 1;
        }

        files=base_name(ob)+".c";
        slot = ob->query("name"); 
        me->set("diablo_baoshi_slot/"+slot,files);
        me->add("diablo_baoshi_number/"+slot,1);
	message_vision("$N手中"+ob->query("name")+"突然霞光一闪，竟在朦朦烟雾中消失了。\n",me);
	ob->move("/obj/void");
        destruct(ob);
        return 1;
}

