// gold.c

inherit MONEY;

void create()
{
          set_name("��ʯ", ({"damond", "ingot", "gold_money"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
                 set("money_id", "damond");
set("long", "��Ө��͸�Ĵ���ʯ��\n");
set("unit", "����");
                set("base_value", 5000000 );
                set("base_unit", "����");
		set("base_weight", 37);
	}
	set("special_effects", "��");
	set_amount(1);
}

