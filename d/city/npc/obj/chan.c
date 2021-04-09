#include <ansi.h>                                                                        
inherit ITEM;                                                                            
int do_dig();                                                                 
                                                                                        
void create()                                                                            
{                                                                                        
        set_name(HIY"铁铲"NOR, ({"tie chan", "chan"}));                       
        set_weight(1000);                                                               
        if (clonep())                                                                    
                set_default_object(__FILE__);                                            
        else {                                                                           
                set("long", "一把精致的铁铲。\n");                                     
                set("unit", "把");                                                       
                set("no_drop",1);                        
                set("no_put",1);                                                        
                set("no_store",1);
                set("no_pawn",1);
                set("no_sell",1);
        }                                                                                
}                                                                                        
                                                                                         
void init()                                                                              
{                                                                                        
   add_action("do_dig","dig");
   add_action("do_dig","wa"); 
}

int do_dig()
{
	object room, me,master,book;
	string name;
	me=this_player();
	master=query("owner");
  if(master!=me->query("id"))
	  return notify_fail("什么？\n");
	 
	if(me->query("qi")<=50)
	  return notify_fail("你太累了，休息一下在挖吧。\n"); 

	if(me->is_busy())
	  return notify_fail("你忙着呢，等下再挖吧。\n"); 
  
  if ( query("dig_num") > 2)
  {
    message_vision(HIY"只听“铛”的一声，铁铲断成两节!\n"NOR,me); 
    destruct(this_object());
    return 1;
  }
  
  room=environment(me);	  	     
	if(file_name(room)+".c"!=query("file_name"))
	{
		message_vision(HIR"$N俯下身来，小心翼翼的挖着，生怕弄坏了什么。\n"NOR,me);
		tell_object(me,HIR+"你挖了半天，发现什么都没有，似乎找错地方了。\n"NOR);
		me->start_busy(5);
		me->receive_damage("qi",30);
		add("dig_num",1);
		return 1;
	}	
	
		message_vision(HIR"$N俯下身来，小心翼翼的挖着，生怕弄坏了什么。\n"NOR,me);
		message_vision(HIY"$N过了一会儿，从土里掏出一本古书，不禁欢呼起来。\n"NOR,me);
		book=new("/d/city/npc/obj/qbook");
		book->set("owner",me->query("id"));
		book->move(me);
		me->start_busy(5);
	  me->receive_damage("qi",30);
	  destruct(this_object());
    return 1;  
}	                                                                                          
