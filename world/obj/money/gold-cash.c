// gold-cash.c

inherit MONEY;
int is_gold_cash() {
	return 1;
}

void create()
{
	set_name("金票", ({"gold-cash", "gold-cash_money"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("money_id", "gold-cash");
		set("long", "长安钱庄发行的金票, 虽然不能在世面上流通, 但是方便携带, 并可在钱庄兑换. \n很多有身份的人也只认金票, 不收现金, 以和其高贵的身份相配\n");
		set("unit", "些");
		set("base_value", 10000);
		set("base_unit", "张");
		set("base_weight", 0);
		set("no_sell", 1);
	}
	set("special_effects", "无");  // emotion
	set_amount(1);
}

