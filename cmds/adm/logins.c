//list all the logins

#include <command.h>
inherit F_CLEAN_UP;

int sort_login_by_ip(mixed ob1,mixed ob2)
{
    object login1,login2;
    login1 = ob1;
    login2 = ob2;
    reset_eval_cost();
    if(!objectp(login1) || !stringp(query_ip_number(login1))) return -1;
    if(!objectp(login2) || !stringp(query_ip_number(login2))) return 1;
    
    return strcmp(query_ip_number(login1),query_ip_number(login2));    
}
int main(object me, string arg)
{
    object* logins;
    int i;
    logins = children("/clone/user/login.c");
    for(i=0;i<sizeof(logins);i++)
    {
        //销毁无ip，无body,或者body无ip的login ob
        if(!stringp(query_ip_number(logins[i])) && (!objectp(logins[i]->query_temp("body_ob")) || !stringp(query_ip_number(logins[i]->query_temp("body_ob"))) ))
        {            
            if(objectp(logins[i]->query_temp("body_ob")))
            {
                destruct(logins[i]->query_temp("body_ob"));
            }
            destruct(logins[i]);
        }
    }
    
    logins = children("/clone/user/login.c");
    logins = sort_array(logins,(:sort_login_by_ip:));
    for(i=0;i<sizeof(logins);i++)
    {
        printf("%s\n",query_ip_number(logins[i]));
    }

    return 1;
}