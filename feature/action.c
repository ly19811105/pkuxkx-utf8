// action.c
// From ES2
// Adapted for XKX
// Modified by iszt@pkuxkx, 2007-03-12, added exert & perform delay

// busy
nosave mixed busy, interrupt;
nosave string thefile;

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
	string f = "";

//	if( !new_busy ) return;
	if( !intp(new_busy) && !stringp(new_busy) )
		error("action: Invalid busy action type.\n");
	if( stringp(new_busy) && !(f = function_exists(new_busy, previous_object())) )
		error("action: No such function (" + new_busy + ") in previous object.\n");
	busy = new_busy;
	if( f ) thefile = f;
	if( !intp(new_interrupt) && !stringp(new_interrupt) )
		error("action: Invalid busy action interrupt handler type.\n");
	if( stringp(new_interrupt) && !function_exists(new_interrupt, previous_object()) )
		error("action: No such function (" + new_interrupt + ") in previous object.\n");
	interrupt = new_interrupt;
	set_heart_beat(1);
	
	this_object()->busy_started();
}

void add_busy(int morebusy)
{
	if(intp(busy)) busy += morebusy;
	set_heart_beat(1);
	this_object()->busy_started();
}


nomask mixed query_busy() { return busy; }
nomask int is_busy() { return busy != 0; }

// exert delay
nosave int exert_time;
nosave string exert_type = "内功";

varargs void start_exert(int new_exert, string new_type)
{
	if (!intp(new_exert))
		error("action: Invalid exert time.\n");
	exert_time = new_exert;
	if (!stringp(new_type))
		new_type = "内功";
	exert_type = new_type;
	set_heart_beat(1);
}

nomask string query_exert() { return exert_type; }
nomask int is_exert() { return exert_time; }

//perform delay
nosave int perform_time;
nosave string perform_type = "外功";

varargs void start_perform(int new_perform, string new_type)
{
	if (!intp(new_perform))
		error("action: Invalid perform time.\n");
	perform_time = new_perform;
	if (!stringp(new_type))
		new_type = "外功";
	perform_type = new_type;
	set_heart_beat(1);
}

nomask string query_perform() { return perform_type; }
nomask int is_perform() { return perform_time; }

// This is called by heart_beat() instead of attack() when a ppl is busy
// doing something else.
void continue_action()
{
	string err;
	int res;

	if( intp(busy) && (busy > 0) )
	{
		busy--;
		if(busy == 0)
		{
		    this_object()->busy_stopped();
		}
		return;
	}
	else if( stringp(busy) )
	{
		err = catch(res = (int)call_other(thefile, busy, this_object()));
		if( err )
		{
			busy = 0;
			interrupt = 0;
			error("error occurs while evaluating function: " + 
				busy + " of " + thefile + "\n");
		}
		if( !res )
		{
			busy = 0;
			interrupt = 0;
		}
	}
	else
	{
		busy = 0;
		interrupt = 0;
	}
}

void continue_exert()
{
	if (exert_time > 0)
		exert_time--;
	else
		exert_time = 0;
}

void continue_perform()
{
	if (perform_time > 0)
		perform_time--;
	else
		perform_time = 0;
}

void interrupt_me(object who, string how)
{
	string err;
	int res;
	object me;

	me = this_object();
	if( !busy ) return;

	if( intp(busy) && intp(interrupt) ) {
		if( busy < interrupt ) busy = 0;
	} else if( stringp(interrupt) ) {
		err = catch(res = (int)call_other(thefile, interrupt, this_object(), who, how));
		if( err ) {
			busy = 0;
			interrupt = 0;
			error("error occurs while evaluating function: " + 
				interrupt + " of " + thefile + "\n");
		}
		if( res ) {
			busy = 0;
			interrupt = 0;
		}
		
		me->set_temp("exercise_cost",0);
		me->set_temp("pending/exercise", 0);
		me->set_temp("respirate_cost",0);
		me->set_temp("pending/respirate", 0);

		me->set_temp("cooking_cost",0);
		me->set_temp("pending/cooking", 0);
	}
	else if( functionp(interrupt) ) 
		{
			err = catch(res = (int) evaluate(interrupt, this_object(), who, how) );
			if( err ) {
				busy = 0;
				interrupt = 0;
				error("error occurs while evaluating function: " + 
					interrupt + " of " + thefile + "\n");
				}
			else{
				busy = 0;
				interrupt = 0;
			}
			me->set_temp("exercise_cost",0);
			me->set_temp("pending/exercise", 0);
			me->set_temp("respirate_cost",0);
			me->set_temp("pending/respirate", 0);

			me->set_temp("cooking_cost",0);
			me->set_temp("pending/cooking", 0);
		}
		
    //通知对象，busy已经结束，可以用于npc智能		    
    me->busy_stopped();
}

// This function is for temporary conditions's recovery call_outs, bcz
// such recovery function call_out might be destroyed if some wizard
// destructed the object that is reponsible of it, so we let users launch
// the call_out themself. Thus we can make sure the recovery call_out.
//
// Because this could cause a serious security problem, so we need highest
// security check here.

//20080429 by icer: 增加start_call_out第三个参数，以适应perform时需要三个参数的情况，避免使用call_other
varargs int start_call_out(string file, string fun, int delay, mixed arg1, mixed arg2, mixed arg3)
{
	if( !previous_object()
	||  (geteuid(previous_object()) != ROOT_UID
	    && userp(this_object())
	    && this_player(1) != this_object()))
		return 0;

	call_out("eval_function", delay, file, fun, arg1, arg2, arg3);

	return 1;
}

int stop_call_out(string fun)
{
	if( !previous_object()
	||  (geteuid(previous_object()) != ROOT_UID
	    && userp(this_object())
	    && this_player(1) != this_object()))
		return 0;
	
	return remove_call_out(fun);
}

void eval_function(string file, string fun, mixed arg1, mixed arg2, mixed arg3)
{
	if (arg1 && arg2 && arg3)
		call_other(file, fun, arg1, arg2, arg3);
	else if( arg1 && arg2 )
		call_other(file, fun, arg1, arg2);
	else if( arg1 )
		call_other(file, fun, arg1);
	else
		call_other(file, fun);
}


