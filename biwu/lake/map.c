inherit F_DBASE;

void create()
{
	set("name","湖光山色");
	set("family_entries",
		({
			([
				"entry":"eastgate.c",
				"number":8
			]),
			([
				"entry":"westgate.c",
				"number":8
			]),
		})
	);
	set("flag_numbers",1);
    set("reward_factor",3);
}