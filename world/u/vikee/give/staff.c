// budd_staff.c

#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
	set_name( HIY "��ͭ����" NOR, ({ "huangtong chanzhang", "staff" }) );
	set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ���ִ��ֳ����ǳ����صĻ�ͭ���ȣ�������������ͭ����\n");
		set("value", 10000);
		set("material", "brass");
		set("wield_msg", "$N�ó�һ������Ȼ��$n�������С�\n");
		set("unwield_msg", "$N�������е�$n��\n");
		set("no_sell",1);
				set("no_drop","ȥ�����Ѷ��ɣ����ӻ���Ⱦ����!\n");
				set("no_give","�ܹܷ���װ�����ɲ���������Ӵ��\n");
				set("no_get","�����ܹ�һҶ֪�﷢��װ�������ΰ�!\n");
	}

	init_staff(36);
	setup();
}
