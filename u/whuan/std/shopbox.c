

#include <ansi.h>

inherit ITEM;

void create()
{
     set_name("聚宝盒",({"treasure box", "box"}));     
     set("short", "聚宝盒");
     set("env/invisibility",1);
     set_max_encumbrance(50000000);
//     set_max_items(10000);
     set_weight(100);
     set("no_get",1);
     set("no_magic", 1);
     set("no_fight", 1);
     seteuid(getuid());
     setup();

}

int clean_up()
{
    return 0;
}    

void reset()
{
    mapping numbers=query_temp("numbers");
    string *key;
    int *value, i;
    
    if(!numbers) return;

    key=keys(numbers);
    value=values(numbers);
    i=sizeof(numbers);
    
    while(i--) {
	if(value[i]>50)
	    set_temp("numbers/"+key[i],value[i]-2);
    }

    return;
}    


