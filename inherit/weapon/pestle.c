// spear.c

#include <weapon.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

varargs void init_pestle(int damage, int flag)
{
        if( clonep(this_object()) ) return;

        set("weapon_prop/damage", damage);
        set("flag", (int)flag | EDGED);
	set("skill_type", "pestle");
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "thrust", "pierce", "impale" }) );
        }
}
