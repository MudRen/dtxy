// bank.c

inherit ROOM;

string money_str(int amount);
int pay_player(object who, int amount);

void init()
{
	add_action("do_convert", "convert");
	add_action("do_deposit", "deposit");
	add_action("do_check", "account");
	add_action("do_withdraw", "withdraw");
	add_action("do_quit", "quit");
    add_action("do_vaultin", "vaultin");
    add_action("do_vaultout", "vaultout");
    add_action("do_vaultdeposit", "vaultdeposit");
    add_action("do_vaultwithdraw", "vaultwithdraw");
}

int do_convert(string arg)
{
	string from, to;
	int amount, bv1, bv2;
	object from_ob, to_ob;

	if( !arg || sscanf(arg, "%d %s to %s", amount, from, to)!=3 )
		return notify_fail("指令格式：convert <数量> <货币种类> to <货币种类>\n");

	if ( from == "gold-cash" || to == "gold-cash")
			return notify_fail("金票不可以转换!\n");

	if( this_player()->is_busy() )
	    return notify_fail("你现在正忙着呢...。\n");

	from_ob = present(from + "_money", this_player());
	to_ob = present(to + "_money", this_player());
	if( !to_ob && file_size("/obj/money/" + to + ".c") < 0 )
		return notify_fail("你想兑换哪一种钱？\n");

	if( !from_ob )		return notify_fail("你身上没有这种货币。\n");
	if ( from_ob->is_gold_cash() )
		return notify_fail("金票不可以转换!\n");
	if( amount < 1 )	return notify_fail("兑换货币一次至少要兑换一个。\n");

	if( (int)from_ob->query_amount() < amount )
		return notify_fail("你身上没有那么多" + from_ob->query("name") + "。\n");

	bv1 = from_ob->query("base_value");
	if( !bv1 ) return notify_fail("这种东西不值钱。\n");

	bv2 = to_ob ? to_ob->query("base_value") : call_other("/obj/money/" + to, "query", "base_value" );

	if( bv1 < bv2 ) amount -= amount % (bv2 / bv1);
	if( amount==0 )	return notify_fail("这些" + from_ob->query("name") + "的价值太低了，换不起。\n");
	this_player()->start_busy(1);

	if( !to_ob ) {
		to_ob = new("/obj/money/" + to);
		if(!(to_ob->move(this_player())))
		    return 0;
		to_ob->set_amount(amount * bv1 / bv2);
	} else
		to_ob->add_amount(amount * bv1 / bv2);

	message_vision( sprintf("$N从身上取出%s%s%s，换成%s%s%s。\n",
		chinese_number(amount), from_ob->query("base_unit"), from_ob->query("name"),
		chinese_number(amount * bv1 / bv2), to_ob->query("base_unit"), to_ob->query("name")),
		this_player() );
        if( (int)from_ob->query_amount() == amount )
             destruct(from_ob);
        else
           from_ob->add_amount(-amount);

        this_player()->save();

	return 1;
}


int do_deposit(string arg)
{
	string what;
	int amount;
	object what_ob, me;

	me = this_player();

	if(!arg || sscanf(arg, "%d %s", amount, what) !=2)
	{
		return notify_fail("命令格式：deposit <数量> <货币单位>\n");
	}
	if ( what == "gold-cash" )
			return notify_fail("金票必须用vaultdeposit指令存!\n");

	if( this_player()->is_busy() )
	    return notify_fail("你现在正忙着呢...。\n");


	        what_ob = present(what + "_money", me);
        if (!what_ob)
        {
                return notify_fail("你身上没有带这种钱。\n");
        }
        if (amount < 1)
        {
		return notify_fail("你想存多少" + what_ob->query("name") + "？\n");
        }
        if ((int)what_ob->query_amount() < amount)
        {
                return notify_fail("你带的" + what_ob->query("name") + "不够。\n");
        }


	me->start_busy(1);
        message_vision(sprintf("$N拿出%s%s%s，存进了钱庄。\n",
        	chinese_number(amount), what_ob->query("base_unit"),
        	what_ob->query("name")), me);
	me->add("balance", what_ob->query("base_value") * amount);
        if ((int)what_ob->query_amount() == amount)
            destruct(what_ob);
        else
            what_ob->add_amount(-amount);

        me->save();

	return 1;
}


int do_check()
{
   int total = (int)this_player()->query("balance");

   if(!total || total < 0)  {
        this_player()->set("balance", 0);
	return notify_fail("您在敝银庄没有存钱。\n");
   }
   write("您在敝银庄共存有" +
         money_str(total) + "\n");

   return 1;
}

int do_withdraw(string arg)
{
	int amount, v, rv;
	string what;
	object me;

	me = this_player();

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
        {
                return notify_fail("命令格式：withdraw <数量> <货币单位>\n");
        }
	if ( what == "gold-cash" )
			return notify_fail("金票必须用vaultwithdraw指令取!\n");

	if( this_player()->is_busy() )
	    return notify_fail("你现在正忙着呢...。\n");
 if(time()-(int)me->query("withdraw_time")<60)
            return notify_fail("你取钱不能这么频繁。\n");

        if (amount < 1)
        {
                return notify_fail("你想取出多少钱？\n");
        }
        if (file_size("/obj/money/" + what + ".c") < 0)
        {
                return notify_fail("你想取出什么钱？\n");
        }
        what = "/obj/money/" + what;
        if ((v = amount * what->query("base_value")) > me->query("balance"))
        {
                return notify_fail("你存的钱不够取。\n");
        }
		if( v < what->query("base_value") )    {
				return notify_fail("Don't try, or I will purge you!\n");
		}

	me->start_busy(1);
me->set("withdraw_time",time());
	/*
        if( me->query("balance") > me->query("combat_exp")*100)
            rv = v*8/10;
        else
        */
        //cuz there is upper limit now, disabled
        //discount...weiqi,971226.
        rv = v;

	// player may not be able to carry the money.
	// so what get out maybe less than he expected.
	// mon 6/13/98
        v=v-pay_player(me, rv);
        me->add("balance",  -v);
if (!me->save())  {
           write("档案存储失败！\n");
                   destruct(me);
                     }

        message_vision(sprintf("$N从银号里取出%s。\n", money_str(v)),
                me);

	return 1;
}


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
        if (amount || sizeof(output)<2)
                return output + chinese_number(amount) + "文铜板";
        return output;
}


// return value is the amount which doesnot paid.
// mon 6/13/98
int pay_player(object who, int amount)
{
        int v;
        object ob;

        seteuid(getuid());
        if (amount < 1)
                amount = 0;
        if (v = amount / 10000) {
                ob = new("/obj/money/gold");
                ob->set_amount(amount / 10000);
                if(!(ob->move(who)))
		    return amount;
                amount %= 10000;
        }
        if (amount / 100) {
                ob = new("/obj/money/silver");
                ob->set_amount(amount / 100);
                if(!(ob->move(who)))
		    return amount;
                amount %= 100;
        }
        if (amount) {
                ob = new("/obj/money/coin");
                ob->set_amount(amount);
                if(!(ob->move(who)))
		    return amount;
        }
	return 0;
}

int do_quit()
{
	this_player()->move("/cmds/std/quitroom");
    	return 1;
}


int do_vaultin(string arg) {
	int amount;
	object me, player;
	me = this_object();
	player = this_player();
	if (!arg || sscanf(arg, "%d", amount)!=1) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 应该用vaultin <数量>指令来将黄金换成金票存入金库\n", player);
		return 1;
	}
	if (amount <= 0) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你想将多少黄金换成金票存入金库?\n", player);
		return 1;
	}
	if ( player->query("balance")/10000 < amount ) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你的黄金不够吧?\n", player);
		return 1;
	}
	player->add("balance", -amount * 10000);
	player->add("g_balance", amount);
	player->save();
	message_vision("铁算盘的魂魄笑眯眯地对$N说: 我已经把你的黄金换成" + chinese_number(amount) + "张金票存到金库里了!\n", player);
	return 1;
}
int do_vaultout(string arg) {
	int amount;
	object me, player;
	me = this_object();
	player = this_player();
	if (!arg || sscanf(arg, "%d", amount)!=1) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 应该用vaultout <数量>指令来将金库内的金票换成黄金\n", player);
		return 1;
	}
	if (amount <= 0) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你想将多少金票换成黄金?\n", player);
		return 1;
	}
	if ( player->query("g_balance") < amount ) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你的金票不够吧?\n", player);
		return 1;
	}
	if (to_float(player->query("balance")) + to_float(amount*10000) > 2000000000.0) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 换得太多当心溢出!\n", player);
		return 1;
	}
	player->add("balance", amount * 10000);
	player->add("g_balance", -amount);
	player->save();
	message_vision("铁算盘的魂魄笑眯眯地对$N说: 我已经把你的" + chinese_number(amount) + "张金票换成黄金存到你的帐户里了!\n", player);
	return 1;
}
int do_vaultdeposit(string arg) {
	int amount;
	object me, player, cash;
	me = this_object();
	player = this_player();
	if (!arg || sscanf(arg, "%d", amount)!=1) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 应该用vaultdeposit <数量>指令来将金票存入金库\n", player);
		return 1;
	}
	if (amount <= 0) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你想将多少金票存入金库?\n", player);
		return 1;
	}
	cash = present("gold-cash", player);
	if ( !objectp(cash) || !cash->is_gold_cash()) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你身上没有金票吧?\n", player);
		return 1;
	}
	if ( amount > cash->query_amount()) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你身上没有带那么多金票吧?\n", player);
		return 1;
	}
	if (amount == cash->query_amount())
	    destruct (cash);
	else
	    cash->add_amount(-amount);
	player->add("g_balance", amount);
	player->save();
	message_vision("铁算盘的魂魄笑眯眯地对$N说: 我已经把你的" + chinese_number(amount) + "张金票存到金库里了!\n", player);
	return 1;
}
int do_vaultwithdraw(string arg) {
	int amount;
	object me, player, cash;
	me = this_object();
	player = this_player();
	if (!arg || sscanf(arg, "%d", amount)!=1) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 应该用vaultwithdraw <数量>指令来将从金库中提取金票\n", player);
		return 1;
	}
	if (amount <= 0) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你想将多少金票存入从金库中拿出来?\n", player);
		return 1;
	}
	if ( amount > player->query("g_balance")) {
		message_vision("铁算盘的魂魄笑眯眯地对$N说: 你在金库中没有那么多金票吧?\n", player);
		return 1;
	}
	player->add("g_balance", -amount);
	player->save();
	cash = new("/obj/money/gold-cash");
	cash->set_amount(amount);
	cash->move(player);
	if ( environment(cash) != player )
		cash->move(environment(player));
	message_vision("铁算盘的魂魄笑眯眯地对$N说: 我已经把" + chinese_number(amount) + "张金票给你了!\n", player);
	return 1;
}