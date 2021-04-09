// food.c
// Modified by iszt@pkuxkx, 2007-05-21

#include <dbase.h>
#include <name.h>


//这个地方反复激发callouts，对系统负担很大 -- J


void init()//jason你把add_action也注释了，所有update过的food都吃不了，现在只注释callout的部分，Zine
{
    object me = this_player(),env=environment();
    if( env == me || me->query("env/food"))
    {
        add_action("do_eat", "chi");
        add_action("do_eat", "eat");
    }
  /*if ( objectp(env) && userp(env) )
    	set("player_item",1);
    if ( environment()->isroom() &&
    	   query("player_item") )
    	call_out("dest_food",60);
	*/
}

/*
void dest_food()
{
	if ( environment()->isroom() )
		destruct(this_object());
}
*/

int do_eat(string arg)
{
	object me = this_player();
	object obj = this_object();
	if( !obj->id(arg) )
		return 0;
		
	if( me->is_busy() )
		return notify_fail("你上一个动作还没有完成。\n");
	
	if( !query("food_remaining") &&
	    !obj->query_amount() )
		return notify_fail( name() + "已经没什么好吃的了。\n");
	
	if( (int)me->query("food") >= (int)me->max_food_capacity() )
		return notify_fail("你已经吃太饱了，再也塞不下任何东西了。\n");

	me->add("food", query("food_supply"));
	if( me->is_fighting() )
		me->start_busy(2);

	// This allows customization of drinking effect.
	if( query("eat_func") ) return 1;

	// 吃食物可以提供短时buff效果. lordstar 20180423
	// 函数定义在 inherit/char/char.c
	me->apply_food_effect(obj);

	if((int)obj->query("food_busy"))
		me->start_busy(obj->query("food_busy"));
	if (me->query("myVeins/手阳明大肠经/completed")&&!me->query_condition("shouyangming"))
	me->apply_condition("shouyangming","feature/vein/BasicVein/shouyangming.c"->benefit_times(me));
  if ( obj->query_amount()>0 )
  {
    if((string)obj->query("eat_msg"))
		  message_vision(obj->query("eat_msg"), me, obj);
		else
		  message_vision("$N拿起$n咬了几口。\n", me, obj);
    obj->add_amount(-1);
  }
  else 
  {
	  set("value", 0);
	  add("food_remaining", -1);

	  if( !query("food_remaining") )
	  {
		  if((string)obj->query("finish_msg"))
			  message_vision(obj->query("finish_msg"), me, obj);
		  else
			  message_vision("$N将剩下的$n吃得干干净净。\n", me, obj);
		  if( !this_object()->finish_eat() )
			  destruct(this_object());
	  }
	  else
	  {
		  if((string)obj->query("eat_msg"))
			  message_vision(obj->query("eat_msg"), me, obj);
		  else
			  message_vision("$N拿起$n咬了几口。\n", me, obj);
	  }
	}

	return 1;
}

int is_food()
{
	return 1;
}