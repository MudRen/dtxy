// gold-cash.c

inherit MONEY;
int is_gold_cash() {
	return 1;
}

void create()
{
	set_name("��Ʊ", ({"gold-cash", "gold-cash_money"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("money_id", "gold-cash");
		set("long", "����Ǯׯ���еĽ�Ʊ, ��Ȼ��������������ͨ, ���Ƿ���Я��, ������Ǯׯ�һ�. \n�ܶ�����ݵ���Ҳֻ�Ͻ�Ʊ, �����ֽ�, �Ժ���߹���������\n");
		set("unit", "Щ");
		set("base_value", 10000);
		set("base_unit", "��");
		set("base_weight", 0);
		set("no_sell", 1);
	}
	set("special_effects", "��");  // emotion
	set_amount(1);
}

