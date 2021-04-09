// moneyd.c  钱的功能

// by Xiang@XKX (95/12/22)

string money_str(int amount)
{
        // returns a chinese string of `amount` of money
        string output;

        if (amount / 10000) {
                output = chinese_number(amount / 10000) + "两黄金";
                amount %= 10000;
        }
        else
                output = "";
        if (amount / 100) {
                output = output + chinese_number(amount / 100) + "两白银";
                amount %= 100;
        }
        if (amount)
                return output + chinese_number(amount) + "文铜板";
        return output;
}

string price_str(int amount)
{
        // returns a chinese string of `amount` of money
	string output;

        if (amount < 1)
                amount = 1;

        if (amount / 10000) {
                output = chinese_number(amount / 10000) + "两黄金";
                amount %= 10000;
        }
        else
                output = "";
        if (amount / 100) {
		if (output != "")
                	output += "又" + chinese_number(amount / 100) + "两白银";
		else
			output = chinese_number(amount / 100) + "两白银";
                amount %= 100;
        }
        if (amount)
		if (output != "")
                	return output + "又" + chinese_number(amount) + "文铜板";
		else
			return chinese_number(amount) + "文铜板";
        return output;
}

void pay_player(object who, int amount)
{
        int v;
        object ob;

	seteuid(getuid());
        if (amount < 1)
                amount = 1;
        if( amount/100000 ) 
			{
                ob = new("/clone/money/thousand-cash");
                ob->set_amount(amount/100000);
				if(!ob->move(who))
				ob->move(environment(who));
                amount %= 100000;
			}
        if (v = amount / 10000) {
                ob = new(GOLD_OB);
                ob->set_amount(amount / 10000);
				if(!ob->move(who))
				ob->move(environment(who));
                amount %= 10000;
        }
        if (amount / 100) {
                ob = new(SILVER_OB);
                ob->set_amount(amount / 100);
				if(!ob->move(who))
				ob->move(environment(who));
                amount %= 100;
        }
        //不给coin了，节省对象
       /* if (amount) {
                ob = new(COIN_OB);
                ob->set_amount(amount);
				if(!ob->move(who))
				ob->move(environment(who));
        }*/
}

int player_pay(object who, int amount)
{
	object cash_ob, g_ob, s_ob, c_ob;
	int cash_c, gc, sc, cc, left;

	seteuid(getuid());

	if (cash_ob = present("cash_money", who))
		cash_c = cash_ob->query_amount();
	else
		cash_c = 0;

	if (g_ob = present("gold_money", who))
		gc = g_ob->query_amount();
	else
		gc = 0;
	if (s_ob = present("silver_money", who))
		sc = s_ob->query_amount();
	else
		sc = 0;
	if (c_ob = present("coin_money", who))
		cc = c_ob->query_amount();
	else
		cc = 0;
	
	if (cc + sc * 100 + gc * 10000 + cash_c * 100000 < amount) 
			return 0;
	else {
		left = cc + sc * 100 + gc * 10000  + cash_c * 100000 - amount;
        cash_c = left / 100000;
		left = left % 100000;
        gc = left / 10000;
		left = left % 10000;
		sc = left / 100;
		cc = left % 100;

		if (cash_ob)
			cash_ob->set_amount(cash_c);
		else gc += (cash_c * 10);

		if (g_ob)
			g_ob->set_amount(gc);
		else sc += (gc * 100);
		if (s_ob)
		 	s_ob->set_amount(sc);
		else if (sc) {
			s_ob = new(SILVER_OB);
			s_ob->set_amount(sc);
			s_ob->move(who);
		}
		if (c_ob)
			c_ob->set_amount(cc);
		else if (cc) {
            //不找coin，节省对象
			//c_ob = new(COIN_OB);
			//c_ob->set_amount(cc);
			//c_ob->move(who);
		}

		return 1;
	}
}

