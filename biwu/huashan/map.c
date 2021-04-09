inherit F_DBASE;

void create()
{
	set("name","华山之巅");
	set("family_entries",
		({
			([
				"entry":"eastgate.c",
				"number":3
			]),
			([
				"entry":"westgate.c",
				"number":3
			]),
		})
	);
	set("flag_numbers",4);
    set("reward_factor",2);
}