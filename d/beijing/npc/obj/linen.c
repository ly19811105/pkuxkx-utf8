/*  <SecCrypt CPL V3R05>  */
 
//  linen.c

#include  <armor.h>

inherit  CLOTH;

void  create()
{
	set_name("粗布衣",  ({  "linen"  })  );
set_weight(3000);
	if(  clonep()  )
		set_default_object(__FILE__);
	else  {
		set("material",  "cloth");
		set("unit",  "件");
		set("value",  0);
set("armor_prop/armor",  1);

	}
	setup();
}
