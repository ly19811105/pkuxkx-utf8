// drunk.c

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	int limit;
      if(me->query_condition("wannianzui")>0)
        {
          me->add_temp("wannianzui_timer",1);
          if(me->query_temp("wannianzui_timer")<5)
          {
             me->apply_condition("drunk", duration - 1);
        if( !duration ) return 0;
        return 1;
           }
        me->set_temp("wannianzui_timer",0);
        } 

	limit = (me->query("con") + (int)me->query("max_neili") / 50) * 2;

	if( duration > limit
	&&	living(me) ) {
		me->unconcious();
		return 0;
	} else if( !living(me) ) {
		message("vision", me->name() + "打了个嗝，不过依然烂醉如泥。\n",
			environment(me), me);
	} else if( duration > limit/2 ) {
		tell_object(me, "你觉得脑中昏昏沉沉，身子轻飘飘地，大概是醉了。\n");
		message("vision", me->name() + "摇头晃脑地站都站不稳，显然是喝醉了。\n",
                        environment(me), ({me}));
		me->receive_damage("jing", 10);
	} else if( duration > limit/4 ) {
		tell_object(me, "你觉得一阵酒意上冲，眼皮有些沉重了。\n");
		message("vision", me->name() + "脸上已经略显酒意了。\n",
			environment(me), me);
		me->receive_healing("jing", 10);
		me->receive_healing("qi", 15);
	}

	me->apply_condition("drunk", duration - 1);
	if( !duration ) return 0;
	return 1;
}
