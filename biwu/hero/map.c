inherit F_DBASE;

void create()
{
	set("name","英雄");
	set("family_entries",
		({
			([
				"entry":"eastgate.c",
				"number":5
			]),
			([
				"entry":"westgate.c",
				"number":5
			]),
		})
	);
	set("flag_numbers",1);
    set("reward_factor",1);
}

//this function will be called everytime by the biwud when game is over
void finish_task_call_back(object user)
{
    //remove all temp bonus
    user->add_temp("apply/armor",-user->query_temp("hero/defense_bonus"));
    user->add_temp("apply/damage",-user->query_temp("hero/defense_bonus"));
    user->delete_temp("hero");
}