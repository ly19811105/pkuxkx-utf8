inherit F_DBASE;

void create()
{
	set("name","杀戮");
	set("family_entries",
		({
			([
				"entry":"eastgate.c",
				"number":2
			]),
			([
				"entry":"westgate.c",
				"number":2
			]),
		})
	);
	set("flag_numbers",1);
    set("reward_factor",1);
}